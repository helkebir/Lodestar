//
// Created by Hamza El-Kebir on 4/17/21.
//

#ifndef LODESTAR_STATESPACE_HPP
#define LODESTAR_STATESPACE_HPP

#include "SystemStateless.hpp"
#include "Eigen/Dense"
#include "aux/CompileTimeQualifiers.hpp"

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
            StateSpace() : _A(new TDStateMatrix),
                           _B(new TDInputMatrix),
                           _C(new TDOutputMatrix),
                           _D(new TDFeedforwardMatrix),
                           _dt(-1), _isDiscrete(false)
            {};

            /**
             * @brief Construct a state space system with the given matrices.
             *
             * @note State space systems are assumed to be in continuous time by
             * default.
             *
             * @param A Pointer to state matrix.
             * @param B Pointer to input matrix.
             * @param C Pointer to output matrix.
             * @param D Pointer to feedforward matrix.
             */
            StateSpace(TDStateMatrix *A, TDInputMatrix *B,
                       TDOutputMatrix *C, TDOutputMatrix *D);

            /**
             * @brief Construct a state space system with the given matrices.
             *
             * @note State space systems are assumed to be in continuous time by
             * default.
             *
             * @param A State matrix.
             * @param B Input matrix.
             * @param C Output matrix.
             * @param D Feedforward matrix.
             */
            StateSpace(const TDStateMatrix &A, const TDInputMatrix &B,
                       const TDOutputMatrix &C, const TDOutputMatrix &D);

            template<typename DerivedA, typename DerivedB, typename DerivedC, typename DerivedD>
            StateSpace(const Eigen::EigenBase<DerivedA> &A, const Eigen::EigenBase<DerivedB> &B,
                       const Eigen::EigenBase<DerivedC> &C, const Eigen::EigenBase<DerivedD> &D);

            /**
             * @brief Copy constructor.
             *
             * @param other State space object to copy.
             */
            StateSpace(const StateSpace &other);

            /**
             * @brief Gets the state matrix.
             *
             * @return State matrix.
             */
            const TDStateMatrix *getA() const;

            /**
             * @brief Sets the state matrix.
             *
             * @param A Pointer to state matrix.
             */
            void setA(TDStateMatrix *A);

            template <typename Derived>
            void setA(Eigen::EigenBase<Derived> *A);

            /**
             * @brief Sets the state matrix.
             *
             * @param A State matrix.
             */
            void setA(const TDStateMatrix &A);

            template <typename Derived>
            void setA(const Eigen::EigenBase<Derived> &A);

            /**
             * @brief Gets the input matrix.
             *
             * @return Input matrix.
             */
            const TDInputMatrix *getB() const;

            /**
             * @brief Sets the input matrix.
             *
             * @param B Pointer to input matrix.
             */
            void setB(TDInputMatrix *B);

            template <typename Derived>
            void setB(Eigen::EigenBase<Derived> *B);

            /**
             * @brief Sets the input matrix.
             *
             * @param B Input matrix.
             */
            void setB(const TDInputMatrix &B);

            template <typename Derived>
            void setB(const Eigen::EigenBase<Derived> &B);

            /**
             * @brief Gets the output matrix.
             *
             * @return Output matrix.
             */
            const TDOutputMatrix *getC() const;

            /**
             * @brief Sets the output matrix.
             *
             * @param C Pointer to output matrix.
             */
            void setC(TDOutputMatrix *C);

            template <typename Derived>
            void setC(Eigen::EigenBase<Derived> *C);

            /**
             * @brief Sets the output matrix.
             *
             * @param C Output matrix.
             */
            void setC(const TDOutputMatrix &C);

            template <typename Derived>
            void setC(const Eigen::EigenBase<Derived> &C);

            /**
             * @brief Gets the feedforward matrix.
             *
             * @return Feedforward matrix.
             */
            const TDFeedforwardMatrix *getD() const;

            /**
             * @brief Sets the feedforward matrix.
             *
             * @param D Feedforward matrix.
             */
            void setD(TDFeedforwardMatrix *D);

            template <typename Derived>
            void setD(Eigen::EigenBase<Derived> *D);

            /**
             * @brief Sets the feedforward matrix.
             *
             * @param D Pointer to feedforward matrix.
             */
            void setD(const TDFeedforwardMatrix &D);

            template <typename Derived>
            void setD(const Eigen::EigenBase<Derived> &D);

            /**
             * @brief Copies matrices from one state space object to the current
             * instance.
             *
             * @param ss State space object to copy matrices from.
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
            bool isDiscrete() const;

            /**
             * @brief Returns the sampling period.
             *
             * @return Sampling period.
             */
            double getSamplingPeriod() const;

            /**
             * @brief Sets the sampling period.
             *
             * @param dt Sampling period.
             */
            void setSamplingPeriod(double dt);

            /**
             * @brief Returns the state dimension.
             *
             * @return State dimension.
             */
            IF_DYNAMIC_RETURN(TStateDim, TInputDim, TOutputDim, long)
            stateDim() const {
                return _A->rows();
            }

            IF_STATIC_RETURN(TStateDim, TInputDim, TOutputDim, long)
            stateDim() const {
                return TStateDim;
            }

            /**
             * @brief Returns the input dimension.
             *
             * @return Input dimension.
             */
            IF_DYNAMIC_RETURN(TStateDim, TInputDim, TOutputDim, long)
            inputDim() const {
                return _B->cols();
            }

            IF_STATIC_RETURN(TStateDim, TInputDim, TOutputDim, long)
            inputDim() const {
                return TInputDim;
            }

            /**
             * @brief Returns the output dimension.
             *
             * @return Output dimension
             */
            IF_DYNAMIC_RETURN(TStateDim, TInputDim, TOutputDim, long)
            outputDim() const {
                return _C->rows();
            }

            IF_STATIC_RETURN(TStateDim, TInputDim, TOutputDim, long)
            outputDim() const {
                return TOutputDim;
            }

            /**
             * @brief Appends to state space systems.
             *
             * If the discrete time parameters do not match the current system,
             * the input system is altered to match the current system.
             *
             * @param ss State space system to append.
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
            bool isStable(double tolerance = 0) const;

        protected:
            TDStateMatrix *_A; /// State matrix.
            TDInputMatrix *_B; /// Input matrix.
            TDOutputMatrix *_C; /// Output matrix.
            TDFeedforwardMatrix *_D; /// Feedforward matrix.
            double _dt; /// Sampling period.
            bool _isDiscrete; /// Discrete flag.
        };
    }
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::StateSpace(
        const StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> &other)
{
    *_A = *other.getA();
    *_B = *other.getB();
    *_C = *other.getC();
    *_D = *other.getD();
    _dt = other.getSamplingPeriod();
    _isDiscrete = other.isDiscrete();
}


template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::StateSpace(
        TDStateMatrix *A, TDInputMatrix *B,
        TDOutputMatrix *C, TDOutputMatrix *D)
{
    _A = A;
    _B = B;
    _C = C;
    _D = D;
    _dt = -1;
    _isDiscrete = false;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::StateSpace(
        const TDStateMatrix &A, const TDInputMatrix &B,
        const TDOutputMatrix &C, const TDOutputMatrix &D) : _A(new TDStateMatrix(A)), _B(new TDInputMatrix(B)),
                                                            _C(new TDOutputMatrix(C)), _D(new TDFeedforwardMatrix(D))
{
//    *_A = A;
//    *_B = B;
//    *_C = C;
//    *_D = D;
    _dt = -1;
    _isDiscrete = false;
}

template<typename TScalar, const int TStateDim, const int TInputDim, const int TOutputDim>
template<typename DerivedA, typename DerivedB, typename DerivedC, typename DerivedD>
ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::StateSpace(const Eigen::EigenBase<DerivedA> &A,
                                                                               const Eigen::EigenBase<DerivedB> &B,
                                                                               const Eigen::EigenBase<DerivedC> &C,
                                                                               const Eigen::EigenBase<DerivedD> &D):
        _A(new TDStateMatrix(A)),
        _B(new TDInputMatrix(B)),
        _C(new TDOutputMatrix(C)),
        _D(new TDFeedforwardMatrix(D))
{
    _dt = -1;
    _isDiscrete = false;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
const typename ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::TDStateMatrix *
ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::getA() const
{
    return _A;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setA(TDStateMatrix *A)
{
    _A = A;
}

template<typename TScalar, const int TStateDim, const int TInputDim, const int TOutputDim>
template<typename Derived>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setA(Eigen::EigenBase<Derived> *A)
{
    _A = A;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setA(
        const TDStateMatrix &A)
{
    *_A = A;
}

template<typename TScalar, const int TStateDim, const int TInputDim, const int TOutputDim>
template<typename Derived>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setA(const Eigen::EigenBase<Derived> &A)
{
    *_A = A;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
const typename ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::TDInputMatrix *
ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::getB() const
{
    return _B;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setB(TDInputMatrix *B)
{
    _B = B;
}

template<typename TScalar, const int TStateDim, const int TInputDim, const int TOutputDim>
template<typename Derived>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setB(Eigen::EigenBase<Derived> *B)
{
    _B = B;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setB(
        const TDInputMatrix &B)
{
    *_B = B;
}

template<typename TScalar, const int TStateDim, const int TInputDim, const int TOutputDim>
template<typename Derived>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setB(const Eigen::EigenBase<Derived> &B)
{
    *_B = B;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
const typename ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::TDOutputMatrix *
ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::getC() const
{
    return _C;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void
ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setC(TDOutputMatrix *C)
{
    _C = C;
}

template<typename TScalar, const int TStateDim, const int TInputDim, const int TOutputDim>
template<typename Derived>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setC(Eigen::EigenBase<Derived> *C)
{
    _C = C;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setC(
        const TDOutputMatrix &C)
{
    *_C = C;
}

template<typename TScalar, const int TStateDim, const int TInputDim, const int TOutputDim>
template<typename Derived>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setC(const Eigen::EigenBase<Derived> &C)
{
    *_C = C;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
const typename ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::TDFeedforwardMatrix *
ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::getD() const
{
    return _D;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setD(
        TDFeedforwardMatrix *D)
{
    _D = D;
}

template<typename TScalar, const int TStateDim, const int TInputDim, const int TOutputDim>
template<typename Derived>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setD(Eigen::EigenBase<Derived> *D)
{
    _D = D;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setD(
        const TDFeedforwardMatrix &D)
{
    *_D = D;
}

template<typename TScalar, const int TStateDim, const int TInputDim, const int TOutputDim>
template<typename Derived>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setD(const Eigen::EigenBase<Derived> &D)
{
    *_D = D;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
bool ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::isDiscrete() const
{
    return _isDiscrete;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
double ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::getSamplingPeriod() const
{
    return _dt;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setSamplingPeriod(double dt)
{
    _dt = dt;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setDiscreteParams(double dt)
{
    _dt = dt;
    _isDiscrete = true;
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>::setDiscreteParams(double dt, bool discrete)
{
    _dt = dt;
    _isDiscrete = discrete;
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
    auto eig = _A->eigenvalues();

    for (int i = 0; i < eig.size(); i++) {
        if (eig(i).real() > tolerance)
            return false;
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

#endif //LODESTAR_STATESPACE_HPP