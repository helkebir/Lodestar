//
// Created by Hamza El-Kebir on 4/17/21.
//

#ifndef LODESTAR_STATESPACE_HPP
#define LODESTAR_STATESPACE_HPP

#include "SystemStateless.hpp"
#include <Eigen/Dense>
#include "Lodestar/aux/CompileTimeQualifiers.hpp"

namespace ls {
    namespace systems {
        template<typename TScalar = double, const int TStateDim = Eigen::Dynamic, const int TInputDim = Eigen::Dynamic, const int TOutputDim = Eigen::Dynamic>
        class StateSpace : public SystemStateless {
        public:
            typedef Eigen::Matrix<TScalar, TStateDim, TStateDim> TDStateMatrix;
            typedef Eigen::Matrix<TScalar, TStateDim, TInputDim> TDInputMatrix;
            typedef Eigen::Matrix<TScalar, TOutputDim, TStateDim> TDOutputMatrix;
            typedef Eigen::Matrix<TScalar, TOutputDim, TInputDim> TDFeedforwardMatrix;

            /**
             * @brief Default constructor.
             */
            StateSpace() : A_(new TDStateMatrix),
                           B_(new TDInputMatrix),
                           C_(new TDOutputMatrix),
                           D_(new TDFeedforwardMatrix),
                           dt_(-1), isDiscrete_(false)
            {
                A_->setIdentity();
                B_->setIdentity();
                C_->setIdentity();
                D_->setZero();
            };

            /**
             * @brief Construct a state space system with the given matrices.
             *
             * @note TState space systems are assumed to be in continuous time by
             * default.
             *
             * @param A Pointer to state matrix.
             * @param B Pointer to input matrix.
             * @param C Pointer to output matrix.
             * @param D Pointer to feedforward matrix.
             */
            StateSpace(TDStateMatrix *A, TDInputMatrix *B,
                       TDOutputMatrix *C, TDOutputMatrix *D);

            //            /**
            //             * @brief Construct a state space system with the given matrices.
            //             *
            //             * @note TState space systems are assumed to be in continuous time by
            //             * default.
            //             *
            //             * @param A TState matrix.
            //             * @param B Input matrix.
            //             * @param C Output matrix.
            //             * @param D Feedforward matrix.
            //             */
            //            StateSpace(const TDStateMatrix &A, const TDInputMatrix &B,
            //                       const TDOutputMatrix &C, const TDOutputMatrix &D);

            template<typename DerivedA, typename DerivedB, typename DerivedC, typename DerivedD>
            StateSpace(const Eigen::EigenBase<DerivedA> &A, const Eigen::EigenBase<DerivedB> &B,
                       const Eigen::EigenBase<DerivedC> &C, const Eigen::EigenBase<DerivedD> &D);

            /**
             * @brief Copy constructor.
             *
             * @param other TState space object to copy.
             */
            StateSpace(const StateSpace &other);

            /**
             * @brief Gets the state matrix.
             *
             * @return TState matrix.
             */
            const TDStateMatrix &getA() const;

            /**
             * @brief Sets the state matrix.
             *
             * @param A Pointer to state matrix.
             */
            void setA(TDStateMatrix *A);

            template<typename Derived>
            void setA(Eigen::EigenBase<Derived> *A);

            /**
             * @brief Sets the state matrix.
             *
             * @param A TState matrix.
             */
            void setA(const TDStateMatrix &A);

            template<typename Derived>
            void setA(const Eigen::EigenBase<Derived> &A);

            /**
             * @brief Gets the input matrix.
             *
             * @return Input matrix.
             */
            const TDInputMatrix &getB() const;

            /**
             * @brief Sets the input matrix.
             *
             * @param B Pointer to input matrix.
             */
            void setB(TDInputMatrix *B);

            template<typename Derived>
            void setB(Eigen::EigenBase<Derived> *B);

            /**
             * @brief Sets the input matrix.
             *
             * @param B Input matrix.
             */
            void setB(const TDInputMatrix &B);

            template<typename Derived>
            void setB(const Eigen::EigenBase<Derived> &B);

            /**
             * @brief Gets the output matrix.
             *
             * @return Output matrix.
             */
            const TDOutputMatrix &getC() const;

            /**
             * @brief Sets the output matrix.
             *
             * @param C Pointer to output matrix.
             */
            void setC(TDOutputMatrix *C);

            template<typename Derived>
            void setC(Eigen::EigenBase<Derived> *C);

            /**
             * @brief Sets the output matrix.
             *
             * @param C Output matrix.
             */
            void setC(const TDOutputMatrix &C);

            template<typename Derived>
            void setC(const Eigen::EigenBase<Derived> &C);

            /**
             * @brief Gets the feedforward matrix.
             *
             * @return Feedforward matrix.
             */
            const TDFeedforwardMatrix &getD() const;

            /**
             * @brief Sets the feedforward matrix.
             *
             * @param D Feedforward matrix.
             */
            void setD(TDFeedforwardMatrix *D);

            template<typename Derived>
            void setD(Eigen::EigenBase<Derived> *D);

            /**
             * @brief Sets the feedforward matrix.
             *
             * @param D Pointer to feedforward matrix.
             */
            void setD(const TDFeedforwardMatrix &D);

            template<typename Derived>
            void setD(const Eigen::EigenBase<Derived> &D);

            /**
             * @brief Copies matrices from one state space object to the current
             * instance.
             *
             * @param ss TState space object to copy matrices from.
             */
            void copyMatrices(const StateSpace &other);

            /**
             * @brief Sets the discrete time system parameters.
             *
             * @param dt Sampling period.
             */
            void setDiscreteParams(double dt);

            /**
             * @brief Sets the discrete time system parameters.
             *
             * @param dt Sampling period.
             * @param discrete If true, the system is treated as a discrete time
             * system.
             */
            void setDiscreteParams(double dt, bool discrete);

            /**
             * @brief Returns a bool that tells if the system is discrete.
             *
             * @return True if the system is discrete.
             */
            inline bool isDiscrete() const;

            /**
             * @brief Returns the sampling period.
             *
             * @return Sampling period.
             */
            inline double getSamplingPeriod() const;

            /**
             * @brief Sets the sampling period.
             *
             * @param dt Sampling period.
             */
            void setSamplingPeriod(double dt);

            /**
             * @brief Returns the state dimension.
             *
             * @return TState dimension.
             */
            IF_DYNAMIC_RETURN(TStateDim, TInputDim, TOutputDim, long)
            inline stateDim() const
            {
                return stateDimDynamic();
            }

            long inline stateDimDynamic() const
            {
                return A_->rows();
            }

            IF_STATIC_RETURN(TStateDim, TInputDim, TOutputDim, long)
            inline stateDim() const
            {
                return stateDimStatic();
            }

            long inline stateDimStatic() const
            {
                return TStateDim;
            }

            /**
             * @brief Returns the input dimension.
             *
             * @return Input dimension.
             */
            IF_DYNAMIC_RETURN(TStateDim, TInputDim, TOutputDim, long)
            inline inputDim() const
            {
                return inputDimDynamic();
            }

            long inline inputDimDynamic() const
            {
                return B_->cols();
            }

            IF_STATIC_RETURN(TStateDim, TInputDim, TOutputDim, long)
            inline inputDim() const
            {
                return inputDimStatic();
            }

            long inline inputDimStatic() const
            {
                return TInputDim;
            }

            /**
             * @brief Returns the output dimension.
             *
             * @return Output dimension
             */
            IF_DYNAMIC_RETURN(TStateDim, TInputDim, TOutputDim, long)
            inline outputDim() const
            {
                return outputDimDynamic();
            }

            long inline outputDimDynamic() const
            {
                return C_->rows();
            }

            IF_STATIC_RETURN(TStateDim, TInputDim, TOutputDim, long)
            inline outputDim() const
            {
                return outputDimStatic();
            }

            long inline outputDimStatic() const
            {
                return TOutputDim;
            }

            /**
             * @brief Appends to state space systems.
             *
             * If the discrete time parameters do not match the current system,
             * the input system is altered to match the current system.
             *
             * @param ss TState space system to append.
             */
            template<int TStateDim2, int TOutputDim2>
            void append(const StateSpace<TScalar, TStateDim2, TOutputDim, TOutputDim2> &ss);

            /**
             * @brief Determines if the system is stable based on its
             * eigenvalues.
             *
             * \p tolerance sets the stability margin that is taken into
             * account during computation.
             *
             * @param tolerance Eigenvalue tolerance.
             * @return True if system is stable.
             */
            inline bool isStable(double tolerance = 0) const;

            /**
             * @brief Returns a state space representation that adds integral action to the original system.
             *
             * @details For details on the discrete time case, see [1].
             *
             * @sa D. D. Ruscio, “Discrete LQ optimal control with integral action: A simple controller on incremental
             *  form for MIMO systems,” MIC, vol. 33, no. 2, pp. 35–44, 2012, doi:
             *  <a href="http://dx.doi.org/10.4173/mic.2012.2.1">10.4173/mic.2012.2.1</a>.
             *
             * @note This particular function gets called when the state space system is dynamic.
             *
             * @tparam T_TScalar Copy of \c TScalar.
             * @tparam T_TStateDim Copy of \c TStateDim.
             * @tparam T_TInputDim Copy of \c TInputDim.
             * @tparam T_TOutputDim Copy of \c TOutputDim.
             *
             * @return State space system augmented with integral action.
             */
            template<typename T_TScalar = TScalar, const int T_TStateDim = TStateDim, const int T_TInputDim = TInputDim, const int T_TOutputDim = TOutputDim>
            ls::systems::StateSpace<T_TScalar, LS_STATIC_UNLESS_DYNAMIC(
                    T_TStateDim + T_TOutputDim), T_TInputDim, T_TOutputDim>
            addIntegralAction(LS_IS_DYNAMIC_DEFAULT(T_TStateDim, T_TInputDim, T_TOutputDim)) const;

            /**
             * @brief Returns a state space representation that adds integral action to the original system.
             *
             * @details For details on the discrete time case, see [1].
             *
             * @sa [1] D. D. Ruscio, “Discrete LQ optimal control with integral action: A simple controller on
             * incremental form for MIMO systems,” MIC, vol. 33, no. 2, pp. 35–44, 2012, doi:
             *  <a href="http://dx.doi.org/10.4173/mic.2012.2.1">10.4173/mic.2012.2.1</a>.
             *
             * @note This particular function gets called when the state space system is static.
             *
             * @tparam T_TScalar Copy of \c TScalar.
             * @tparam T_TStateDim Copy of \c TStateDim.
             * @tparam T_TInputDim Copy of \c TInputDim.
             * @tparam T_TOutputDim Copy of \c TOutputDim.
             *
             * @return State space system augmented with integral action.
             */
            template<typename T_TScalar = TScalar, const int T_TStateDim = TStateDim, const int T_TInputDim = TInputDim, const int T_TOutputDim = TOutputDim>
            ls::systems::StateSpace<T_TScalar, LS_STATIC_UNLESS_DYNAMIC(
                    T_TStateDim + T_TOutputDim), T_TInputDim, T_TOutputDim>
            addIntegralAction(LS_IS_STATIC_DEFAULT(T_TStateDim, T_TInputDim, T_TOutputDim)) const;

        protected:
            TDStateMatrix *A_; //! TState matrix.
            TDInputMatrix *B_; //! Input matrix.
            TDOutputMatrix *C_; //! Output matrix.
            TDFeedforwardMatrix *D_; //! Feedforward matrix.
            double dt_; //! Sampling period.
            bool isDiscrete_; //! Discrete flag.
        };
    }
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::StateSpace(
        const StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> &other):
        A_(new TDStateMatrix(other.getA())),
        B_(new TDInputMatrix(other.getB())),
        C_(new TDOutputMatrix(other.getC())),
        D_(new TDFeedforwardMatrix(other.getD())),
        dt_(other.getSamplingPeriod()),
        isDiscrete_(other.isDiscrete())
{}

// TODO: Replace constructors by Eigen::EigenBase<*>
template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::StateSpace(
        TDStateMatrix *A, TDInputMatrix *B,
        TDOutputMatrix *C, TDOutputMatrix *D):
        A_(new TDStateMatrix(*A)),
        B_(new TDInputMatrix(*B)),
        C_(new TDOutputMatrix(*C)),
        D_(new TDFeedforwardMatrix(*D))
{
    //    *A_ = *A;
    //    *B_ = *B;
    //    *C_ = *C;
    //    *D_ = *D;
    dt_ = -1;
    isDiscrete_ = false;
}

//template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
//ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::StateSpace(
//        const TDStateMatrix &A, const TDInputMatrix &B,
//        const TDOutputMatrix &C, const TDOutputMatrix &D) : A_(new TDStateMatrix(A)), B_(new TDInputMatrix(B)),
//                                                            C_(new TDOutputMatrix(C)), D_(new TDFeedforwardMatrix(D))
//{
////    *A_ = A;
////    *B_ = B;
////    *C_ = C;
////    *D_ = D;
//    dt_ = -1;
//    isDiscrete_ = false;
//}

template<typename TScalar, const int TStateDim, const int TInputDim, const int TOutputDim>
template<typename DerivedA, typename DerivedB, typename DerivedC, typename DerivedD>
ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::StateSpace(const Eigen::EigenBase<DerivedA> &A,
                                                                               const Eigen::EigenBase<DerivedB> &B,
                                                                               const Eigen::EigenBase<DerivedC> &C,
                                                                               const Eigen::EigenBase<DerivedD> &D):
        A_(new TDStateMatrix(A)),
        B_(new TDInputMatrix(B)),
        C_(new TDOutputMatrix(C)),
        D_(new TDFeedforwardMatrix(D))
{
    *A_ = A;
    *B_ = B;
    *C_ = C;
    *D_ = D;
    dt_ = -1;
    isDiscrete_ = false;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
const typename ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::TDStateMatrix &
ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::getA() const
{
    return *A_;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setA(TDStateMatrix *A)
{
    *A_ = *A;
}

template<typename TScalar, const int TStateDim, const int TInputDim, const int TOutputDim>
template<typename Derived>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setA(Eigen::EigenBase<Derived> *A)
{
    *A_ = *A;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setA(
        const TDStateMatrix &A)
{
    *A_ = A;
}

template<typename TScalar, const int TStateDim, const int TInputDim, const int TOutputDim>
template<typename Derived>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setA(const Eigen::EigenBase<Derived> &A)
{
    *A_ = A;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
const typename ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::TDInputMatrix &
ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::getB() const
{
    return *B_;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setB(TDInputMatrix *B)
{
    *B_ = *B;
}

template<typename TScalar, const int TStateDim, const int TInputDim, const int TOutputDim>
template<typename Derived>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setB(Eigen::EigenBase<Derived> *B)
{
    *B_ = *B;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setB(
        const TDInputMatrix &B)
{
    *B_ = B;
}

template<typename TScalar, const int TStateDim, const int TInputDim, const int TOutputDim>
template<typename Derived>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setB(const Eigen::EigenBase<Derived> &B)
{
    *B_ = B;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
const typename ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::TDOutputMatrix &
ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::getC() const
{
    return *C_;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void
ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setC(TDOutputMatrix *C)
{
    *C_ = *C;
}

template<typename TScalar, const int TStateDim, const int TInputDim, const int TOutputDim>
template<typename Derived>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setC(Eigen::EigenBase<Derived> *C)
{
    *C_ = *C;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setC(
        const TDOutputMatrix &C)
{
    *C_ = C;
}

template<typename TScalar, const int TStateDim, const int TInputDim, const int TOutputDim>
template<typename Derived>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setC(const Eigen::EigenBase<Derived> &C)
{
    *C_ = C;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
const typename ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::TDFeedforwardMatrix &
ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::getD() const
{
    return *D_;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setD(
        TDFeedforwardMatrix *D)
{
    *D_ = *D;
}

template<typename TScalar, const int TStateDim, const int TInputDim, const int TOutputDim>
template<typename Derived>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setD(Eigen::EigenBase<Derived> *D)
{
    *D_ = *D;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setD(
        const TDFeedforwardMatrix &D)
{
    *D_ = D;
}

template<typename TScalar, const int TStateDim, const int TInputDim, const int TOutputDim>
template<typename Derived>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setD(const Eigen::EigenBase<Derived> &D)
{
    *D_ = D;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
bool ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::isDiscrete() const
{
    return isDiscrete_;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
double ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::getSamplingPeriod() const
{
    return dt_;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setSamplingPeriod(double dt)
{
    dt_ = dt;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setDiscreteParams(double dt)
{
    dt_ = dt;
    isDiscrete_ = true;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setDiscreteParams(double dt, bool discrete)
{
    dt_ = dt;
    isDiscrete_ = discrete;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
template<int TStateDim2, int TOutputDim2>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::append(
        const ls::systems::StateSpace<TScalar, TStateDim2, TOutputDim, TOutputDim2> &ss)
{
    // TODO: Implement state space append function.
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
bool ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::isStable(const double tolerance) const
{
    auto eig = A_->eigenvalues();

    if (isDiscrete()) {
        double tol = (tolerance < 0 ? -tolerance * tolerance : tolerance * tolerance);

        for (int i = 0; i < eig.size(); i++) {
            if (eig(i).real() * eig(i).real() + eig(i).imag() * eig(i).imag() > 1 + tol)
                return false;
        }
    } else {
        for (int i = 0; i < eig.size(); i++) {
            if (eig(i).real() > -tolerance)
                return false;
        }
    }

    return true;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::copyMatrices(
        const ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> &other)
{
    setA(other.getA());
    setB(other.getB());
    setC(other.getC());
    setD(other.getD());

}

template<typename TScalar, const int TStateDim, const int TInputDim, const int TOutputDim>
template<typename T_TScalar, const int T_TStateDim, const int T_TInputDim, const int T_TOutputDim>
ls::systems::StateSpace<T_TScalar, LS_STATIC_UNLESS_DYNAMIC(T_TStateDim + T_TOutputDim), T_TInputDim, T_TOutputDim>
ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::addIntegralAction(
        LS_IS_DYNAMIC(T_TStateDim, T_TInputDim, T_TOutputDim)) const
{
    Eigen::Matrix<TScalar, Eigen::Dynamic, Eigen::Dynamic> A(stateDim() + outputDim(), stateDim() + outputDim());
    A.setZero();
    A.topLeftCorner(stateDim(), stateDim()) = getA();
    A.bottomLeftCorner(outputDim(), stateDim()) = getC();
    A.bottomRightCorner(outputDim(), outputDim()).setIdentity();

    Eigen::Matrix<TScalar, Eigen::Dynamic, Eigen::Dynamic> B(stateDim() + outputDim(), inputDim());
    B.setZero();
    B.topRows(stateDim()) = getB();

    Eigen::Matrix<TScalar, Eigen::Dynamic, Eigen::Dynamic> C(outputDim(), stateDim() + outputDim());
    C.setZero();
    C.leftCols(stateDim()) = getC();
    C.rightCols(outputDim()).setIdentity();

    Eigen::Matrix<TScalar, Eigen::Dynamic, Eigen::Dynamic> D(outputDim(), inputDim());
    D = getD();

    ls::systems::StateSpace<T_TScalar, LS_STATIC_UNLESS_DYNAMIC(
            T_TStateDim + T_TOutputDim), T_TInputDim, T_TOutputDim> ssi{A, B, C, D};

    return ssi;
}

template<typename TScalar, const int TStateDim, const int TInputDim, const int TOutputDim>
template<typename T_TScalar, const int T_TStateDim, const int T_TInputDim, const int T_TOutputDim>
ls::systems::StateSpace<T_TScalar, LS_STATIC_UNLESS_DYNAMIC(T_TStateDim + T_TOutputDim), T_TInputDim, T_TOutputDim>
ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::addIntegralAction(
        LS_IS_STATIC(T_TStateDim, T_TInputDim, T_TOutputDim)) const
{
    Eigen::Matrix<TScalar, TStateDim + TOutputDim, TStateDim + TOutputDim> A{};
    A.setZero();
    A.template topLeftCorner<TStateDim, TStateDim>() = getA();
    A.template bottomLeftCorner<TOutputDim, TStateDim>() = getC();
    A.template bottomRightCorner<TOutputDim, TOutputDim>().setIdentity();

    Eigen::Matrix<TScalar, TStateDim + TOutputDim, TInputDim> B{};
    B.setZero();
    B.template topRows<TStateDim>() = getB();

    Eigen::Matrix<TScalar, TOutputDim, TStateDim + TOutputDim> C{};
    C.setZero();
    C.template leftCols<TStateDim>() = getC();
    C.template rightCols<TOutputDim>().setIdentity();

    Eigen::Matrix<TScalar, TOutputDim, TInputDim> D{};
    D = getD();

    ls::systems::StateSpace<T_TScalar, LS_STATIC_UNLESS_DYNAMIC(
            T_TStateDim + T_TOutputDim), T_TInputDim, T_TOutputDim> ssi{A, B, C, D};

    return ssi;
}

#endif //LODESTAR_STATESPACE_HPP