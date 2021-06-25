//
// Created by Hamza El-Kebir on 6/24/21.
//

#ifndef LODESTAR_EMPTYSET_HPP
#define LODESTAR_EMPTYSET_HPP

#include <type_traits>
#include <limits>
#include "SetExpression.hpp"
#include "SetUnion.hpp"
#include "SetComplement.hpp"

namespace ls {
    namespace primitives {
        namespace sets {
            /**
             * @brief The empty set.
             */
            class EmptySet : public SetExpression<EmptySet> {
            public:
                using Base = SetExpression<EmptySet>; //! Base class.
                using type = EmptySet; //! Expression type.

                EmptySet() = default;

                /**
                 * @brief Checks if this expression is equal to \expr.
                 *
                 * @tparam TExpression Type of the other expression.
                 *
                 * @param expr Expression to check equality with.
                 *
                 * @return True if this expression is equal to \c expr, false otherwise.
                 */
                template<typename TExpression>
                bool operator==(const SetExpression <TExpression> &expr) const
                {
                    return std::is_same<TExpression, type>::value || expr.isEmpty();
                }

                /**
                 * @brief Checks if this expression is not equal to \expr.
                 *
                 * @tparam TExpression Type of the other expression.
                 *
                 * @param expr Expression to check inequality with.
                 *
                 * @return True if this expression is not equal to \c expr, false otherwise.
                 */
                template<typename TExpression>
                bool operator!=(const SetExpression <TExpression> &expr) const
                {
                    return !operator==(expr);
                }

                /**
                 * @brief Returns true if this expression contains \c expr.
                 *
                 * @tparam TExpression Type of the other expression.
                 *
                 * @param expr Expression to check containment of.
                 * @param tol Numerical tolerance.
                 *
                 * @return True if this expression contains \c expr, false otherwise.
                 */
                template<typename TExpression>
                bool contains(const SetExpression <TExpression> &expr) const
                {
                    return std::is_same<type, TExpression>::value || expr.isEmpty();
                }

                /**
                 * @brief Returns true if this expression contains \c expr.
                 *
                 * @tparam TElementType Type of the other element.
                 *
                 * @param el Element to check containment of.
                 *
                 * @return True if this expression contains \c el, false otherwise.
                 */
                template<typename TElementType>
                bool
                contains(const TElementType &el) const
                {
                    return std::is_same<type, TElementType>::value ||
                           std::is_same<SetExpression<type>, TElementType>::value;
                }

                /**
                 * @brief Checks if this expression is a subset of \c expr.
                 *
                 * @note The empty set is always considered to be a subset of any set.
                 *
                 * @tparam TElementType Type of the other element.
                 *
                 * @param expr Element to check inclusion on.
                 *
                 * @return True.
                 */
                template<typename TElementType>
                bool
                isSubset(const TElementType &el) const
                {
                    return true;
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
                bool isSuperset(const SetExpression <TExpression> &expr) const
                {
                    return std::is_same<type, TExpression>::value || expr.isEmpty();
                }

//                /**
//                 * @brief Checks if this expression is a superset of \c expr.
//                 *
//                 * @tparam TElementType Type of the other element.
//                 *
//                 * @param expr Element to check subsumption on.
//                 *
//                 * @return True if this \c el is an empty set object, false otherwise.
//                 */
//                template<typename TElementType>
//                bool
//                isSuperset(const TElementType &el) const
//                {
//                    return std::is_same<type, TElementType>::value || std::is_same<Base, TElementType>::value;
//                }

//                /**
//                 * @brief Computes the relative complement of this expression and \c el.
//                 *
//                 * @tparam TElementType Type of the other element.
//                 *
//                 * @param el Element to take relative complement with.
//                 *
//                 * @return Emtpy set.
//                 */
//                template<typename TElementType>
//                SetExpression <EmptySet>
//                relComplement(const TElementType &el) const
//                {
//                    return *this;
//                }

///**
//                 * @brief Computes the relative complement of this expression and \c el.
//                 *
//                 * @tparam TElementType Type of the other element.
//                 *
//                 * @param el Element to take relative complement with.
//                 *
//                 * @return Emtpy set.
//                 */
//                template<typename TElementType>
//                SetExpression <EmptySet>
//                relComplement(const TElementType &el) const
//                {
//                    return *this;
//                }

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
                                                            expr.isEmpty());
                }

                /**
                 * @brief Returns true if the expression is the empty set.
                 *
                 * @return True if expression is the empty set.
                 */
                bool isEmpty() const
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
                SetUnion <type, TExpression> unionize(const SetExpression <TExpression> &expr)
                {
                    return SetUnion<type, TExpression>(*this, *static_cast<const TExpression *>(&expr),
                                                       isEmpty() && expr.isEmpty());
                }

                /**
                 * @brief Returns signed distance to \c p.
                 *
                 * @note This always returns positive infinity, as is the convention for the Hausdorff distance to the
                 * empty set.
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
                    return std::numeric_limits<double>::infinity();
                }
            };
        }
    }
}

#endif //LODESTAR_EMPTYSET_HPP
