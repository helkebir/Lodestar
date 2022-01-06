//
// Created by Hamza El-Kebir on 6/25/21.
//

#ifndef LODESTAR_CONTINUOUSSAMPLEDEKF_HPP
#define LODESTAR_CONTINUOUSSAMPLEDEKF_HPP

#include <Eigen/Dense>
#include <Eigen/QR>
#include <functional>
#include <type_traits>

#include "Lodestar/primitives/integrators/IntegratorsEnum.hpp"
#include "Lodestar/primitives/integrators/BogackiShampine.hpp"
#include "Lodestar/primitives/integrators/RungeKuttaFehlberg45.hpp"
#include "Lodestar/primitives/integrators/RungeKuttaFehlberg78.hpp"

#include <iostream>

namespace ls {
    namespace filter {
        class ContinuousSampledEKF {
        public:
            using integrators = ls::primitives::IntegratorsEnum;

            template<ls::primitives::IntegratorsEnum TIntegrator = ls::primitives::IntegratorsEnum::RungeKuttaFehlberg45, typename TScalar = double, int TStateDim = Eigen::Dynamic, int TInputDim = Eigen::Dynamic, int TOutputDim = Eigen::Dynamic>
            struct EKFParameters {
                const ls::primitives::IntegratorsEnum kIntegrator = TIntegrator;
                using scalar_type = TScalar;
                const int kStateDim = TStateDim;
                const int kInputDim = TInputDim;
                const int kOutputDim = TOutputDim;

                typedef Eigen::Matrix<TScalar, TStateDim, TStateDim> TDStateMatrix;
                typedef Eigen::Matrix<TScalar, TStateDim, 1> TDStateVector;
                typedef Eigen::Matrix<TScalar, TStateDim, TInputDim> TDInputMatrix;
                typedef Eigen::Matrix<TScalar, TInputDim, 1> TDInputVector;
                typedef Eigen::Matrix<TScalar, TOutputDim, TStateDim> TDOutputMatrix;
                typedef Eigen::Matrix<TScalar, TOutputDim, 1> TDOutputVector;
                typedef Eigen::Matrix<TScalar, TOutputDim, TInputDim> TDFeedforwardMatrix;

                typedef Eigen::Matrix<TScalar, TStateDim, TOutputDim> TDKalmanGain;

                typedef TDStateMatrix TDProcessCovarianceMatrix;
                typedef Eigen::Matrix<TScalar, TOutputDim, TOutputDim> TDObservationCovarianceMatrix;

                typedef ls::primitives::IntegratorsEnum TDIntegratorsEnum;

                typedef std::function<TDStateVector(TScalar, const TDStateVector &, const TDInputVector &)> TDOde; //! Ordinary differential equation: f(t, x, u)
                typedef std::function<TDStateMatrix(TScalar, const TDStateMatrix &, const TDStateVector &,
                                                    const TDInputVector &)> TDPOde; //! Matrix ordinary differential equation: f(t, P, x, u)
                typedef std::function<TDStateMatrix(const TDStateVector &, const TDInputVector &)> TDStateJacobian; //! Jacobian state matrix: f(x, u)
                typedef std::function<TDOutputMatrix(const TDStateVector &)> TDOutputJacobian; //! Jacobian output matrix: f(x)
                typedef std::function<TDOutputVector(const TDStateVector &)> TDOutputMap; //! Output map: f(x)

                typedef std::function<TDStateVector(TScalar, const TDStateVector &)> TDOdeFunc;
                typedef std::function<TDStateMatrix(TScalar, const TDStateMatrix &)> TDMatrixOdeFunc;

                void initEquations(const TDOde &ordinaryDiffEq, const TDStateJacobian &stateJacobianEq,
                                   const TDOutputJacobian &outputJacobianEq, const TDOutputMap &outputMapEq)
                {
                    ode = ordinaryDiffEq;
                    stateJacobian = stateJacobianEq;
                    outputJacobian = outputJacobianEq;
                    outputMap = outputMapEq;

                    Pdot = [&](TScalar t, const TDStateMatrix &P, const TDStateVector &x, const TDInputVector &u) {
                        const auto F = stateJacobian(x, u);
                        std::cout << "F at t = " << t << ": " << F << std::endl;
                        std::cout << "P at t = " << t << ": " << P << std::endl;
                        std::cout << "Pdot at t = " << t << ": " << F * P + P * F.transpose() + Q << std::endl;

                        // NOTE: The return value must be explicitly cast as type TDStateMatrix, otherwise the copy
                        // constructor in Eigen fails.
                        TDStateMatrix ret;
                        ret = F * P + P * F.transpose() + Q;

                        return ret;
                    };
                }

                void
                initParams(const TDStateVector &x0, const TDStateMatrix &P0 = TDStateMatrix::Zero(), TScalar t0 = 0)
                {
                    xhat = x0;
                    P = P0;
                    time = t0;
                }

                TDOde ode;
                TDStateJacobian stateJacobian;
                TDOutputJacobian outputJacobian;
                TDOutputMap outputMap;

                TDProcessCovarianceMatrix Q;
                TDObservationCovarianceMatrix R;
                TDStateMatrix P;

                TDStateVector xhat;
                TScalar time;

                TDPOde Pdot;

                // TODO: Add template parameter for integration scheme;
                //  Add initialization and prediction routines;
                //  Add time member variable;
                //  Implement unit tests.

                template<TDIntegratorsEnum T_TIntegrator = TIntegrator>
                typename std::enable_if<T_TIntegrator == TDIntegratorsEnum::BogackiShampine, void>::type
                predict(TDStateVector &xout, TDStateMatrix &Pout, const TDStateVector &x, const TDInputVector &u,
                        const TScalar h)
                {
                    xout = x;
                    auto f = std::bind(ode, std::placeholders::_1, std::placeholders::_2, u);

                    // FIXME: Make x time-dependent.
                    Pout = P;
                    auto F = std::bind(Pdot, std::placeholders::_1, std::placeholders::_2, x, u);
                    TScalar t = 0;

                    ls::primitives::BogackiShampine<TDStateVector, TScalar>::integrateSimple(f, t, xout, h, 1);

                    t = 0;
                    ls::primitives::BogackiShampine<TDStateMatrix, TScalar>::integrateSimple(F, t, Pout, h, 1);
                }

                template<TDIntegratorsEnum T_TIntegrator = TIntegrator>
                typename std::enable_if<T_TIntegrator == TDIntegratorsEnum::RungeKuttaFehlberg45, void>::type
                predict(TDStateVector &xout, TDStateMatrix &Pout, const TDStateVector &x, const TDInputVector &u,
                        const TScalar h)
                {
                    xout = x;
                    auto f = std::bind(ode, std::placeholders::_1, std::placeholders::_2, u);

                    // FIXME: Make x time-dependent.
                    Pout = P;
                    auto F = std::bind(Pdot, std::placeholders::_1, std::placeholders::_2, x, u);
                    TScalar t = 0;

                    ls::primitives::RungeKuttaFehlberg45<TDStateVector, TScalar>::integrateSimple(f, t, xout, h, 1);

                    t = 0;
                    ls::primitives::RungeKuttaFehlberg45<TDStateMatrix, TScalar>::integrateSimple(F, t, Pout, h, 1);
                }

                template<TDIntegratorsEnum T_TIntegrator = TIntegrator>
                typename std::enable_if<T_TIntegrator == TDIntegratorsEnum::RungeKuttaFehlberg78, void>::type
                predict(TDStateVector &xout, TDStateMatrix &Pout, const TDStateVector &x, const TDInputVector &u,
                        const TScalar h)
                {
                    xout = x;
                    auto f = std::bind(ode, std::placeholders::_1, std::placeholders::_2, u);
                    std::function<TDStateVector(TScalar, const TDStateVector &)> func = [&](TScalar t, const TDStateVector &x)
                    {
                        return ode(t, x, u);
                    };

                    // FIXME: Make x time-dependent.
                    Pout = P;
                    auto F = std::bind(Pdot, std::placeholders::_1, std::placeholders::_2, x, u);
                    std::function<TDStateMatrix (TScalar, const TDStateMatrix &)> Func = [&](TScalar t, const TDStateMatrix &P)
                    {
                        return Pdot(t, P, x, u);
                    };
                    TScalar t = 0;

                    ls::primitives::RungeKuttaFehlberg78<TDStateVector, TScalar>::integrateSimple(func, t, xout, h, 1);

                    t = 0;
                    ls::primitives::RungeKuttaFehlberg78<TDStateMatrix, TScalar>::integrateSimple(Func, t, Pout, h, 1);
                }

                void update(TDStateVector &x, const TDOutputVector &z)
                {
                    const TDOutputMatrix H = outputJacobian(x);
                    const TDKalmanGain K = P * H.transpose() * (H * P * H.transpose() + R).completeOrthogonalDecomposition().pseudoInverse();
                    x = x + K * (z - outputMap(x));
                    P = (TDStateMatrix::Identity() - K * H) * P;
                }

                void step(const TDInputVector &u, const TDOutputVector &z, const TScalar h)
                {
                    TDStateVector xnew;
                    TDStateMatrix Pnew;

                    predict(xnew, Pnew, xhat, u, h);
                    xhat = xnew;
                    P = Pnew;

                    std::cout << "xnew " << xnew << std::endl;
                    std::cout << "Pnew " << Pnew << std::endl;

                    update(xhat, z);

                    time += h;
                }

                void setCovarianceMatrices(const TDProcessCovarianceMatrix &QMatrix, const TDObservationCovarianceMatrix &RMatrix)
                {
                    Q = QMatrix;
                    R = RMatrix;
                }

                const TDStateVector &getStateEstimate() const
                {
                    return xhat;
                }

                TScalar getCurrentTime() const
                {
                    return time;
                }
            };
        };
    }
}


#endif //LODESTAR_CONTINUOUSSAMPLEDEKF_HPP
