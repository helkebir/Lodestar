//
// Created by Hamza El-Kebir on 4/17/21.
//

#ifndef LODESTAR_BILINEARTRANSFORMATION_HPP
#define LODESTAR_BILINEARTRANSFORMATION_HPP

#include <Eigen/Dense>
#include "Lodestar/systems/StateSpace.hpp"
#include "Lodestar/aux/CompileTimeQualifiers.hpp"

namespace ls {
    namespace analysis {
        /**
         * @brief Routines for converting a state space system from continuous-
         * to discrete-time and vice versa.
         *
         * @note
         * Corresponds to SLICOT Routine <a href="http://slicot.org/objects/software/shared/doc/AB04MD.html">AB04MD</a>
         * (<em>Discrete-time <-> continuous-time conversion by bilinear transformation</em>).
         */
        class BilinearTransformation {
        public:
            template<typename TScalar = double, int TStateDim = Eigen::Dynamic, int TInputDim = Eigen::Dynamic, int TOutputDim = Eigen::Dynamic>
            struct mallocStructC2D {
                Eigen::ColPivHouseholderQR<Eigen::Matrix<TScalar, TStateDim, TStateDim>> HH;
                Eigen::ColPivHouseholderQR<Eigen::Matrix<TScalar, TStateDim, TStateDim>> HH2;
                Eigen::Matrix<TScalar, TStateDim, TStateDim> I;
            };

            template<typename TScalar = double, int TStateDim = Eigen::Dynamic, int TInputDim = Eigen::Dynamic, int TOutputDim = Eigen::Dynamic>
            struct mallocStructD2C {
                Eigen::ColPivHouseholderQR<Eigen::Matrix<TScalar, TStateDim, TStateDim>> HH;
                Eigen::Matrix<TScalar, TStateDim, TStateDim> IMAC;
                Eigen::Matrix<TScalar, TStateDim, TStateDim> I;
            };

            /**
             * @brief Generates generalized bilinear transform of a
             * continuous-time state space system.
             *
             * @param A TState matrix.
             * @param B Input matrix.
             * @param C Output matrix.
             * @param D Feedforward matrix.
             * @param dt Sampling period.
             * @param alpha Generalized bilinear transformation parameter; default
             * parameter corresponds to backward differencing transform.
             *
             * @return Transformed discrete-time state space system.
             */
            static systems::StateSpace<>
            c2d(const Eigen::MatrixXd &A, const Eigen::MatrixXd &B,
                const Eigen::MatrixXd &C, const Eigen::MatrixXd &D,
                double dt,
                double alpha = 1);

            /**
             * @brief Generates generalized bilinear transform of a
             * continuous-time state space system.
             *
             * @param A Pointer to state matrix.
             * @param B Pointer to input matrix.
             * @param C Pointer to output matrix.
             * @param D Pointer to feedforward matrix.
             * @param dt Sampling period.
             * @param alpha Generalized bilinear transformation parameter; default
             * parameter corresponds to backward differencing transform.
             *
             * @return Transformed discrete-time state space system.
             */
            static systems::StateSpace<>
            c2d(const Eigen::MatrixXd *A, const Eigen::MatrixXd *B, const Eigen::MatrixXd *C, const Eigen::MatrixXd *D,
                double dt,
                double alpha);

            /**
             * @brief Generates generalized bilinear transform of a
             * continuous-time state space system.
             *
             * @param ss TState space system.
             * @param dt Sampling period.
             * @param alpha Generalized bilinear transformation parameter; default
             * parameter corresponds to backward differencing transform.
             *
             * @return Transformed discrete-time state space system.
             */
            static systems::StateSpace<>
            c2d(const systems::StateSpace<> &ss, double dt, double alpha = 1);

            template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
            static void
            c2d(const systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *ss, double dt, double alpha,
                systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *out,
                mallocStructC2D<TScalar, TStateDim, TInputDim, TOutputDim> *memStruct,
                LS_IS_DYNAMIC_DEFAULT(TStateDim, TInputDim, TOutputDim));

            template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
            static void
            c2d(const systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *ss, double dt, double alpha,
                systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *out,
                mallocStructC2D<TScalar, TStateDim, TInputDim, TOutputDim> *memStruct,
                LS_IS_STATIC_DEFAULT(TStateDim, TInputDim, TOutputDim));

            /**
             * @brief Generates generalized bilinear transform of a
             * discrete-time state space system.
             *
             * @param ss TState space system.
             * @param dt Sampling period.
             * @param alpha Generalized bilinear transformation parameter; default
             * parameter corresponds to backward differencing transform.
             *
             * @return Transformed continuous-time state space system.
             */
            static systems::StateSpace<>
            d2c(const systems::StateSpace<> &ss, double dt,
                double alpha = 1);

            template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
            static void
            d2c(const systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *ss, double dt, double alpha,
                systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *out,
                mallocStructD2C<TScalar, TStateDim, TInputDim, TOutputDim> *memStruct,
                LS_IS_DYNAMIC_DEFAULT(TStateDim, TInputDim, TOutputDim));

            template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
            static void
            d2c(const systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *ss, double dt, double alpha,
                systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *out,
                mallocStructD2C<TScalar, TStateDim, TInputDim, TOutputDim> *memStruct,
                LS_IS_STATIC_DEFAULT(TStateDim, TInputDim, TOutputDim));

            /**
             * @brief Generates generalized bilinear transform of a
             * discrete-time state space system.
             *
             * This method retrieves the sampling period from the state space
             * object.
             *
             * @param ss TState space system.
             * @param alpha Generalized bilinear transformation parameter; default
             * parameter corresponds to backward differencing transform.
             *
             * @return Transformed continuous-time state space system.
             */
            static systems::StateSpace<>
            d2c(const systems::StateSpace<> &ss, double alpha = 1);

            /**
             * @brief Generates generalized bilinear transform of a
             * discrete-time state space system.
             *
             * @param A TState matrix.
             * @param B Input matrix.
             * @param C Output matrix.
             * @param D Feedforward matrix.
             * @param dt Sampling period.
             * @param alpha Generalized bilinear transformation parameter; default
             * parameter corresponds to backward differencing transform.
             *
             * @return Transformed continuous-time state space system.
             */
            static systems::StateSpace<>
            d2c(const Eigen::MatrixXd &A, const Eigen::MatrixXd &B,
                const Eigen::MatrixXd &C, const Eigen::MatrixXd &D, double dt,
                double alpha = 1);

            /**
             * @brief Generates generalized bilinear transform of a
             * discrete-time state space system.
             *
             * @param A Pointer to state matrix.
             * @param B Pointer to input matrix.
             * @param C Pointer to output matrix.
             * @param D Pointer to feedforward matrix.
             * @param dt Sampling period.
             * @param alpha Generalized bilinear transformation parameter; default
             * parameter corresponds to backward differencing transform.
             *
             * @return Transformed continuous-time state space system.
             */
            static systems::StateSpace<>
            d2c(const Eigen::MatrixXd *A, const Eigen::MatrixXd *B, const Eigen::MatrixXd *C, const Eigen::MatrixXd *D,
                double dt,
                double alpha);

            /**
             * @brief Generates Tustin transform of a continuous-time state
             * space system.
             *
             * @param ss TState space system.
             * @param dt Sampling period.
             *
             * @return Transformed discrete-time state space system.
             */
            static systems::StateSpace<>
            c2dTustin(const systems::StateSpace<> &ss, double dt);

            /**
             * @brief Generates Tustin transform of a discrete-time state space
             * system.
             *
             * @param ss TState space system.
             * @param dt Sampling period.
             *
             * @return Transformed continuous-time state space system.
             */
            static systems::StateSpace<>
            d2cTustin(const systems::StateSpace<> &ss, double dt);

            /**
             * @brief Generates Euler transform of a continuous-time state space
             * system.
             *
             * @param ss TState space system.
             * @param dt Sampling period.
             *
             * @return Transformed discrete-time state space system.
             */
            static systems::StateSpace<>
            c2dEuler(const systems::StateSpace<> &ss, double dt);

            /**
             * @brief Generates Euler transform of a discrete-time state space
             * system.
             *
             * @param ss TState space system.
             * @param dt Sampling period.
             *
             * @return Transformed continuous-time state space system.
             */
            static systems::StateSpace<>
            d2cEuler(const systems::StateSpace<> &ss, double dt);

            /**
             * @brief Generates backward differencing transform of a
             * continuous-time state space system.
             *
             * @param ss TState space system.
             * @param dt Sampling period.
             *
             * @return Transformed discrete-time state space system.
             */
            static systems::StateSpace<>
            c2dBwdDiff(const systems::StateSpace<> &ss, double dt);

            /**
             * @brief Generates backward differencing transform of a
             * discrete-time state space system.
             *
             * @param ss TState space system.
             * @param dt Sampling period.
             *
             * @return Transformed continuous-time state space system.
             */
            static systems::StateSpace<>
            d2cBwdDiff(const systems::StateSpace<> &ss, double dt);
        };
    }
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void
ls::analysis::BilinearTransformation::c2d(const ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *ss,
                                          double dt, double alpha,
                                          ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *out,
                                          mallocStructC2D<TScalar, TStateDim, TInputDim, TOutputDim> *memStruct,
                                          LS_IS_DYNAMIC(TStateDim, TInputDim, TOutputDim))
{
    if (alpha < 0 || alpha > 1) alpha = 0;
    dt = abs(dt);

    memStruct->I.setIdentity(ss->stateDim(), ss->stateDim());
    memStruct->HH = Eigen::ColPivHouseholderQR<Eigen::Matrix<TScalar, TStateDim, TStateDim>>(
            memStruct->I - alpha * dt * (ss->getA()));
    memStruct->HH2 = Eigen::ColPivHouseholderQR<Eigen::Matrix<TScalar, TStateDim, TStateDim>>(
            (memStruct->I - alpha * dt * (ss->getA())).transpose());

    out->setA(memStruct->HH.template solve(memStruct->I - (1 - alpha) * dt * (ss->getA())));
    out->setB(memStruct->HH.template solve(dt * (ss->getB())));
    out->setC(memStruct->HH2.template solve((ss->getC()).transpose()).transpose());
    out->setD((ss->getD()) + alpha * (ss->getC()) * (out->getB()));
    out->setDiscreteParams(dt, true);
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void
ls::analysis::BilinearTransformation::c2d(const ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *ss,
                                          double dt, double alpha,
                                          ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *out,
                                          mallocStructC2D<TScalar, TStateDim, TInputDim, TOutputDim> *memStruct,
                                          LS_IS_STATIC(TStateDim, TInputDim, TOutputDim))
{
    if (alpha < 0 || alpha > 1) alpha = 0;
    dt = abs(dt);

    memStruct->I.setIdentity();
    memStruct->HH = Eigen::ColPivHouseholderQR<Eigen::Matrix<TScalar, TStateDim, TStateDim>>(
            memStruct->I - alpha * dt * (ss->getA()));
    memStruct->HH2 = Eigen::ColPivHouseholderQR<Eigen::Matrix<TScalar, TStateDim, TStateDim>>(
            (memStruct->I - alpha * dt * (ss->getA())).transpose());

    out->setA(memStruct->HH.template solve(memStruct->I - (1 - alpha) * dt * (ss->getA())));
    out->setB(memStruct->HH.template solve(dt * (ss->getB())));
    out->setC(memStruct->HH2.template solve((ss->getC()).transpose()).transpose());
    out->setD((ss->getD()) + alpha * (ss->getC()) * (*out->getB()));
    out->setDiscreteParams(dt, true);
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void
ls::analysis::BilinearTransformation::d2c(const ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *ss,
                                          double dt, double alpha,
                                          ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *out,
                                          mallocStructD2C<TScalar, TStateDim, TInputDim, TOutputDim> *memStruct,
                                          LS_IS_DYNAMIC(TStateDim, TInputDim, TOutputDim))
{
    if (alpha < 0 || alpha > 1) alpha = 0;
    dt = abs(dt);

    memStruct->I.setIdentity(ss->stateDim(), ss->stateDim());
    memStruct->HH = Eigen::ColPivHouseholderQR<Eigen::Matrix<TScalar, TStateDim, TStateDim>>(
            alpha * dt * (ss->getA()).transpose() + (1 - alpha) * dt * memStruct->I);
    out->setA(memStruct->HH.template solve((ss->getA()).transpose() - memStruct->I));
    memStruct->IMAC = memStruct->I - alpha * dt * (out->getA());

    out->setB(memStruct->IMAC * (ss->getB()) / dt);
    out->setC((ss->getC()) * memStruct->IMAC);
    out->setD((ss->getD()) - alpha * (out->getC()) * (ss->getB()));
    out->setDiscreteParams(-1, false);
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void
ls::analysis::BilinearTransformation::d2c(const ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *ss,
                                          double dt, double alpha,
                                          ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *out,
                                          mallocStructD2C<TScalar, TStateDim, TInputDim, TOutputDim> *memStruct,
                                          LS_IS_STATIC(TStateDim, TInputDim, TOutputDim))
{
    if (alpha < 0 || alpha > 1) alpha = 0;
    dt = abs(dt);

    memStruct->I.setIdentity();
    memStruct->HH = Eigen::ColPivHouseholderQR<Eigen::Matrix<TScalar, TStateDim, TStateDim>>(
            alpha * dt * (ss->getA()).transpose() + (1 - alpha) * dt * memStruct->I);
    out->setA(memStruct->HH.template solve((ss->getA()).transpose() - memStruct->I));
    memStruct->IMAC = memStruct->I - alpha * dt * (out->getA());

    out->setB(memStruct->IMAC * (ss->getB()) / dt);
    out->setC((ss->getC()) * memStruct->IMAC);
    out->setD((ss->getD()) - alpha * (out->getC()) * (ss->getB()));
    out->setDiscreteParams(-1, false);
}

#endif //LODESTAR_BILINEARTRANSFORMATION_HPP
