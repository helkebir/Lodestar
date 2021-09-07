//
// Created by Hamza El-Kebir on 4/17/21.
//

#ifndef LODESTAR_ZEROORDERHOLD_HPP
#define LODESTAR_ZEROORDERHOLD_HPP

#include <Eigen/Dense>
#include <unsupported/Eigen/MatrixFunctions>
#include "systems/StateSpace.hpp"
#include "aux/CompileTimeQualifiers.hpp"

namespace ls {
    namespace analysis {
        /**
         * @brief Routines for computing zero-order hold transformation on state
         * space systems.
         *
         * @sa <a href="https://theory.ldstr.dev/discretization">theory.ldstr.dev/discretization</a>
         */
        class ZeroOrderHold {
        public:
            template<typename TScalar = double, int TStateDim = Eigen::Dynamic, int TInputDim = Eigen::Dynamic, int TOutputDim = Eigen::Dynamic>
            struct mallocStruct {
                Eigen::Matrix<TScalar, TStateDim, LS_STATIC_UNLESS_DYNAMIC(TStateDim + TInputDim)> upperXM;
                Eigen::Matrix<TScalar, TInputDim, LS_STATIC_UNLESS_DYNAMIC(TStateDim + TInputDim)> lowerXM;
                Eigen::Matrix<TScalar, LS_STATIC_UNLESS_DYNAMIC(TStateDim + TInputDim), LS_STATIC_UNLESS_DYNAMIC(
                        TStateDim + TInputDim)> XM;
                Eigen::Matrix<TScalar, TStateDim, LS_STATIC_UNLESS_DYNAMIC(TStateDim + TInputDim)> XXM;
            };

            /**
             * @brief Generates zero-order hold discretization from a
             * continuous-time state space system.
             *
             * @param A TState matrix.
             * @param B Input matrix.
             * @param C Output matrix.
             * @param D Feedforward matrix.
             * @param dt Sampling period.
             *
             * @return Zero-order hold discrete-time state space system.
             */
            static systems::StateSpace<>
            c2d(const Eigen::MatrixXd &A, const Eigen::MatrixXd &B,
                const Eigen::MatrixXd &C, const Eigen::MatrixXd &D, double dt);

            /**
             * @brief Generates zero-order hold discretization from a
             * continuous-time state space system.
             *
             * @param A TState matrix.
             * @param B Input matrix.
             * @param C Output matrix.
             * @param D Feedforward matrix.
             * @param dt Sampling period.
             *
             * @return Zero-order hold discrete-time state space system.
             */
            static systems::StateSpace<>
            c2d(Eigen::MatrixXd *A, Eigen::MatrixXd *B, Eigen::MatrixXd *C, Eigen::MatrixXd *D, double dt);


            template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
            static void c2d(const systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *ss, double dt,
                            systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *out,
                            mallocStruct<TScalar, TStateDim, TInputDim, TOutputDim> *memStruct,
                            LS_IS_DYNAMIC_DEFAULT(TStateDim, TInputDim, TOutputDim));

            template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
            static void c2d(const systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *ss, double dt,
                            systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *out,
                            mallocStruct<TScalar, TStateDim, TInputDim, TOutputDim> *memStruct,
                            LS_IS_STATIC_DEFAULT(TStateDim, TInputDim, TOutputDim));

            /**
             * @brief Generates zero-order hold discretization from a
             * continuous-time state space system.
             *
             * @param ss TState space system.
             * @param dt Sampling period.
             *
             * @return Zero-order hold discrete-time state space system.
             */
            static systems::StateSpace<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic>
            c2d(const systems::StateSpace<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic> &ss, double dt);

            /**
             * @brief Generates zero-order hold discretization from a
             * continuous-time state space system.
             *
             * @param ss Pointer to state space system.
             * @param dt Sampling period.
             *
             * @return Zero-order hold discrete-time state space system.
             */
            static systems::StateSpace<> c2d(const systems::StateSpace<> *ss, double dt);

            /**
             * @brief Reverts a zero-order hold discretization on a
             * discrete-time state space system.
             *
             * @param A TState matrix.
             * @param B Input matrix.
             * @param C Output matrix.
             * @param D Feedforward matrix.
             * @param dt Sampling period.
             *
             * @return Zero-order hold continuous-time state space system.
             */
            static systems::StateSpace<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic>
            d2c(const Eigen::MatrixXd &A, const Eigen::MatrixXd &B,
                const Eigen::MatrixXd &C, const Eigen::MatrixXd &D, double dt);

            /**
             * @brief Reverts a zero-order hold discretization on a
             * discrete-time state space system.
             *
             * @param A TState matrix.
             * @param B Input matrix.
             * @param C Output matrix.
             * @param D Feedforward matrix.
             * @param dt Sampling period.
             *
             * @return Zero-order hold continuous-time state space system.
             */
            static systems::StateSpace<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic>
            d2c(Eigen::MatrixXd *A, Eigen::MatrixXd *B,
                Eigen::MatrixXd *C, Eigen::MatrixXd *D, double dt);

            /**
             * @brief Reverts a zero-order hold discretization on a
             * discrete-time state space system.
             *
             * @param ss TState space system.
             * @param dt Sampling period.
             *
             * @return Continuous-time state space system.
             */
            static systems::StateSpace<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic>
            d2c(const systems::StateSpace<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::Dynamic> &ss, double dt);

            /**
             * @brief Reverts a zero-order hold discretization on a
             * discrete-time state space system.
             *
             * @param ss TState space system.
             * @param dt Sampling period.
             *
             * @return Continuous-time state space system.
             */
            static systems::StateSpace<>
            d2c(const systems::StateSpace<> *ss, double dt);

            /**
             * @brief Reverts a zero-order hold discretization on a
             * discrete-time state space system.
             *
             * @param ss TState space system.
             * @param dt Sampling period.
             *
             * @return Continuous-time state space system.
             */
            template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
            static void d2c(const systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *ss, double dt,
                            systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *out,
                            mallocStruct<TScalar, TStateDim, TInputDim, TOutputDim> *memStruct,
                            LS_IS_DYNAMIC_DEFAULT(TStateDim, TInputDim, TOutputDim));

            /**
             * @brief Reverts a zero-order hold discretization on a
             * discrete-time state space system.
             *
             * @param ss TState space system.
             * @param dt Sampling period.
             *
             * @return Continuous-time state space system.
             */
            template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
            static void d2c(const systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *ss, double dt,
                            systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *out,
                            mallocStruct<TScalar, TStateDim, TInputDim, TOutputDim> *memStruct,
                            LS_IS_STATIC_DEFAULT(TStateDim, TInputDim, TOutputDim));
        };
    }
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::analysis::ZeroOrderHold::c2d(const ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *ss,
                                      double dt,
                                      ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *out,
                                      ls::analysis::ZeroOrderHold::mallocStruct<TScalar, TStateDim, TInputDim, TOutputDim> *memStruct,
                                      LS_IS_DYNAMIC(TStateDim, TInputDim, TOutputDim))
{
    dt = abs(dt);

    const long n = ss->stateDim();
    const long m = ss->inputDim();

    memStruct->upperXM.block(0, 0, n, n) << (ss->getA());
    memStruct->upperXM.block(0, n, n, m) << (ss->getB());

    memStruct->lowerXM.setZero();

    memStruct->XM.block(0, 0, n, n + m) << memStruct->upperXM;
    memStruct->XM.block(n, 0, m, n + m) << memStruct->lowerXM;

    memStruct->XXM = (memStruct->XM * dt).exp().block(0, 0, n, n + m);

    out->setA(memStruct->XXM.block(0, 0, n, n));
    out->setB(memStruct->XXM.block(0, n, n, m));
    out->setC(Eigen::MatrixXd::Identity(n, n));
    out->setD(Eigen::MatrixXd::Zero(n, m));
    out->setDiscreteParams(dt, true);

}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::analysis::ZeroOrderHold::c2d(const ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *ss,
                                      double dt,
                                      ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *out,
                                      ls::analysis::ZeroOrderHold::mallocStruct<TScalar, TStateDim, TInputDim, TOutputDim> *memStruct,
                                      LS_IS_STATIC(TStateDim, TInputDim, TOutputDim))
{
    dt = abs(dt);

    memStruct->upperXM.block<TStateDim, TStateDim>(0, 0);
    memStruct->upperXM.block<TStateDim, TStateDim>(0, 0) << (ss->getA());
    memStruct->upperXM.block<TStateDim, TInputDim>(0, TStateDim) << (ss->getB());

    memStruct->lowerXM.setZero();

    memStruct->XM.block<TStateDim, TStateDim + TInputDim>(0, 0) << memStruct->upperXM;
    memStruct->XM.block<TInputDim, TStateDim + TInputDim>(TStateDim, 0) << memStruct->lowerXM;

    memStruct->XXM = (memStruct->XM * dt).exp().block<TStateDim, TStateDim + TInputDim>(0, 0);

    out->setA(memStruct->XXM.block<TStateDim, TStateDim>(0, 0));
    out->setB(memStruct->XXM.block<TStateDim, TInputDim>(0, TStateDim));
    out->setDiscreteParams(dt, true);
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::analysis::ZeroOrderHold::d2c(const ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *ss,
                                      double dt,
                                      ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *out,
                                      ls::analysis::ZeroOrderHold::mallocStruct<TScalar, TStateDim, TInputDim, TOutputDim> *memStruct,
                                      LS_IS_DYNAMIC(TStateDim, TInputDim, TOutputDim))
{
    dt = abs(dt);

    const long n = ss->stateDim();
    const long m = ss->inputDim();

    memStruct->upperXM.block(0, 0, n, n) << (ss->getA());
    memStruct->upperXM.block(0, n, n, m) << (ss->getB());

    memStruct->lowerXM.setZero();
    memStruct->lowerXM.block(0, n, m, m).setIdentity();

    memStruct->XM.block(0, 0, n, n + m) << memStruct->upperXM;
    memStruct->XM.block(n, 0, m, n + m) << memStruct->lowerXM;

    memStruct->XXM = (memStruct->XM).log().block(0, 0, n, n + m) / dt;

    out->setA(memStruct->XXM.block(0, 0, n, n));
    out->setB(memStruct->XXM.block(0, n, n, m));
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::analysis::ZeroOrderHold::d2c(const ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *ss,
                                      double dt,
                                      ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *out,
                                      ls::analysis::ZeroOrderHold::mallocStruct<TScalar, TStateDim, TInputDim, TOutputDim> *memStruct,
                                      LS_IS_STATIC(TStateDim, TInputDim, TOutputDim))
{
    dt = abs(dt);

    memStruct->upperXM.block<TStateDim, TStateDim>(0, 0) << (ss->getA());
    memStruct->upperXM.block<TStateDim, TInputDim>(0, TStateDim) << (ss->getB());

    memStruct->lowerXM.setZero();
    memStruct->lowerXM.block<TInputDim, TInputDim>(0, TStateDim)
            << Eigen::Matrix<TScalar, TInputDim, TInputDim>::Identity();

    memStruct->XM.block<TStateDim, TStateDim + TInputDim>(0, 0) << memStruct->upperXM;
    memStruct->XM.block<TInputDim, TStateDim + TInputDim>(TStateDim, 0) << memStruct->lowerXM;

    memStruct->XXM = (memStruct->XM).log().block<TStateDim, TStateDim + TInputDim>(0, 0) / dt;

    out->setA(memStruct->XXM.block<TStateDim, TStateDim>(0, 0));
    out->setB(memStruct->XXM.block<TStateDim, TInputDim>(0, TStateDim));
}

#endif //LODESTAR_ZEROORDERHOLD_HPP
