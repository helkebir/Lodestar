//
// Created by Hamza El-Kebir on 6/21/21.
//

#ifndef LODESTAR_SINGLETON_HPP
#define LODESTAR_SINGLETON_HPP

#include <type_traits>
#include <Eigen/Dense>
#include "Lodestar/aux/CompileTimeQualifiers.hpp"

#include "SetExpression.hpp"
#include "SetUnion.hpp"
#include "EmptySet.hpp"
#include "SetComplement.hpp"

namespace ls {
    namespace primitives {
        namespace sets {
            /**
             * @brief A singleton set.
             *
             * @brief A singleton contains a single element, represented by the vector \c value_.
             *
             * @tparam TDimension The dimension of the singleton; if -1, it is dynamically sized.
             * @tparam TScalarType The scalar type.
             */
            template<int TDimension = -1, typename TScalarType = double>
            class Singleton : public SetExpression<Singleton<TDimension, TScalarType>> {
            public:
                template<typename, typename>
                friend
                class SetUnion;

                using Base = SetExpression<Singleton<TDimension, TScalarType>>; //! Base class.
                using type = Singleton<TDimension, TScalarType>; //! Expression type.

                typedef Eigen::Matrix<TScalarType, LS_STATIC_UNLESS_DYNAMIC(TDimension), 1> TDValue; //! Value typedef.

                /**
                 * @brief Default constructor.
                 */
                Singleton() : value_{TDValue::Zero()}
                {
                    this->sEnum_ = SetEnum::Singleton;
                }

                /**
                 * @brief Constructs a Singleton instance from a vector.
                 *
                 * @tparam TDerived Derived EigenBase class.
                 *
                 * @param value Singleton value.
                 */
                template<typename TDerived>
                Singleton(const Eigen::EigenBase<TDerived> &value) : value_(value)
                {
                    this->sEnum_ = SetEnum::Singleton;
                }

                /**
                 * @brief Returns the singleton dimension.
                 *
                 * @details This specialization deals with the static case.
                 *
                 * @tparam T_TDimension Copy of \c TDimension.
                 *
                 * @return Dimension of the singleton instance.
                 */
                template<int T_TDimension = TDimension>
                int
                dimension(typename std::enable_if<(T_TDimension < 0)>::type * = nullptr) const
                {
                    return T_TDimension;
                }

                /**
                 * @brief Returns the singleton dimension.
                 *
                 * @details This specialization deals with the dynamic case.
                 *
                 * @tparam T_TDimension Copy of \c TDimension.
                 *
                 * @return Dimension of the singleton instance.
                 */
                template<int T_TDimension = TDimension>
                int
                dimension(typename std::enable_if<(T_TDimension >= 0)>::type * = nullptr) const
                {
                    return value_.rows();
                }

                /**
                 * @brief Changes the dimension of the singleton.
                 *
                 * @details This specialization raises a static assert since statically type Singleton instances cannot
                 * be resized.
                 *
                 * @tparam T_TDimension Copy of \c TDimension.
                 *
                 * @param dim New dimension.
                 */
                template<int T_TDimension = TDimension>
                void
                setDimension(size_t dim, typename std::enable_if<(T_TDimension < 0)>::type * = nullptr)
                {
                    static_assert(TDimension > -1, "Cannot set dimension of statically sized singleton.");
                }

                /**
                 * @brief Changes the dimension of the singleton.
                 *
                 * @details This specialization conservatively resizes \c value_.
                 *
                 * @tparam T_TDimension Copy of \c TDimension.
                 *
                 * @param dim New dimension.
                 */
                template<int T_TDimension = TDimension>
                void
                setDimension(size_t dim, typename std::enable_if<(T_TDimension >= 0)>::type * = nullptr)
                {
                    value_.conservativeResize(dim);
                }

                /**
                 * @brief Returns true if this expression contains \c expr.
                 *
                 * @details This specialization handles a singleton expression of the same type.
                 *
                 * @tparam TExpression Type of the other expression.
                 *
                 * @param expr Expression to check containment of.
                 * @param tol Numerical tolerance.
                 *
                 * @return True if this expression contains \c expr, false otherwise.
                 */
                template<typename TExpression>
                typename std::enable_if<std::is_same<TExpression, type>::value, bool>::type
                contains(const SetExpression<TExpression> &expr, double tol = 1e-6) const
                {
                    return (value_ - static_cast<const TExpression *>(&expr)->value_).isMuchSmallerThan(tol);
                }

                /**
                 * @brief Returns true if this expression contains \c expr.
                 *
                 * @details This specialization handles all other cases.
                 *
                 * @tparam TExpression Type of the other expression.
                 *
                 * @param expr Expression to check containment of.
                 * @param tol Numerical tolerance.
                 *
                 * @return False.
                 */
                template<typename TExpression>
                typename std::enable_if<!std::is_same<TExpression, type>::value, bool>::type
                contains(const SetExpression<TExpression> &expr, double tol = 1e-6) const
                {
                    return false;
                }

                /**
                 * @brief Checks if this expression is equal to \expr.
                 *
                 * @details This specialization deals with singletons of the same type.
                 *
                 * @tparam TExpression Type of the other expression.
                 *
                 * @param expr Expression to check equality with.
                 *
                 * @return True if this expression is equal to \c expr, false otherwise.
                 */
                template<typename TExpression>
                typename std::enable_if<std::is_same<TExpression, type>::value, bool>::type
                operator==(const SetExpression<TExpression> &expr) const
                {
                    return (value_ - static_cast<const TExpression *>(&expr)->value_).isMuchSmallerThan(1e-6);
                }

                // TODO: Add dynamic case.

                /**
                 * @brief Checks if this expression is equal to \expr.
                 *
                 * @details This specialization deals with all other cases.
                 *
                 * @tparam TExpression Type of the other expression.
                 *
                 * @param expr Expression to check equality with.
                 *
                 * @return False.
                 */
                template<typename TExpression>
                typename std::enable_if<!std::is_same<TExpression, type>::value, bool>::type
                operator==(const SetExpression<TExpression> &expr) const
                {
                    return false;
                }

                /**
                 * @brief Checks if this expression is not equal to \expr.
                 *
                 * @details This specialization deals with singletons of the same type.
                 *
                 * @tparam TExpression Type of the other expression.
                 *
                 * @param expr Expression to check inequality with.
                 *
                 * @return True if this expression is not equal to \c expr, false otherwise.
                 */
                template<typename TExpression>
                typename std::enable_if<std::is_same<TExpression, type>::value, bool>::type
                operator!=(const SetExpression<TExpression> &expr) const
                {
                    return !((value_ - static_cast<const TExpression *>(&expr)->value_).isMuchSmallerThan(1e-6));
                }

                /**
                 * @brief Checks if this expression is not equal to \expr.
                 *
                 * @details This specialization deals with all other cases.
                 *
                 * @tparam TExpression Type of the other expression.
                 *
                 * @param expr Expression to check inequality with.
                 *
                 * @return True.
                 */
                template<typename TExpression>
                typename std::enable_if<!std::is_same<TExpression, type>::value, bool>::type
                operator!=(const SetExpression<TExpression> &expr) const
                {
                    return true;
                }

                /**
                 * @brief Creates a union between this expression and another SetExpression.
                 *
                 * @tparam TExpression Type of the other expression.
                 *
                 * @param expr Expression to create a union with.
                 *
                 * @return Union.
                 */
                template<typename TExpression>
                SetUnion<type, TExpression> unionize(const SetExpression<TExpression> &expr)
                {
                    return SetUnion<type, TExpression>(*this, *static_cast<const TExpression *>(&expr));
                }

                /**
                 * @brief Checks if this expression is a subset of \c expr.
                 *
                 * @tparam TExpression Type of the other expression.
                 *
                 * @param expr Expression to check inclusion on.
                 *
                 * @return True if this expression is a subset of \c expr, false otherwise.
                 */
                template<typename TExpression>
                bool isSubset(const SetExpression<TExpression> &expr)
                {
                    return static_cast<const TExpression *>(&expr)->contains(*this);
                }

                /**
                 * @brief Checks if this expression is a superset of \c expr.
                 *
                 * @tparam TExpression Type of the other expression.
                 *
                 * @param expr Expression to check subsumption on.
                 *
                 * @return True if this expression is a superset of \c expr, false otherwise.
                 */
                template<typename TExpression>
                bool isSuperset(const SetExpression<TExpression> &expr)
                {
                    return contains(expr);
                }

                /**
                 * @brief Returns true if the expression is the empty set.
                 *
                 * @note This always returns false, since a singleton always contains one element.
                 *
                 * @return False.
                 */
                bool isEmpty() const
                {
                    return false;
                }

                /**
                 * @brief Computes the relative complement of this expression and \c expr.
                 *
                 * @details The syntax is as follows:
                 * \code
                 * // A \ B
                 * A.relComplement(B);
                 * \endcode
                 *
                 * @tparam TExpression Type of the other expression.
                 *
                 * @param expr Expression to take relative complement with.
                 *
                 * @return Relative complement.
                 */
                template<typename TExpression>
                SetComplement<type, TExpression> relComplement(const SetExpression<TExpression> &expr)
                {
                    return SetComplement<type, TExpression>(*this, *static_cast<const TExpression *>(&expr),
                                                            isSubset(expr));
                }

                /**
                 * @brief Returns signed distance to \c p.
                 *
                 * @tparam TDerived Derived MatrixBase class.
                 *
                 * @param p A point.
                 *
                 * @return Signed distance.
                 */
                template<typename TDerived>
                double sdf(Eigen::MatrixBase<TDerived> &p) const
                {
                    p.resize(dimension());
                    return (value_ - p).norm();
                }

            protected:
                TDValue value_; //! Singleton value.
            };
        }
    }
}

#endif //LODESTAR_SINGLETON_HPP
