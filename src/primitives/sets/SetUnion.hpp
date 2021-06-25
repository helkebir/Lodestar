//
// Created by Hamza El-Kebir on 6/21/21.
//

#ifndef LODESTAR_SETUNION_HPP
#define LODESTAR_SETUNION_HPP

#include "SetExpression.hpp"
#include <type_traits>
#include <algorithm>

namespace ls {
    namespace primitives {
        namespace sets {
            /**
             * @brief Union of two SetExpressions.
             *
             * @details The syntax is as follows:
             * \code
             * // C = A U B
             * auto C = SetUnion(A, B);
             * \endcode
             *
             * @tparam TTypeLeft Type of the left SetExpression.
             * @tparam TTypeRight Type of the right SetExpression.
             */
            template<typename TTypeLeft, typename TTypeRight>
            class SetUnion : public SetExpression<SetUnion<TTypeLeft, TTypeRight>> {
            public:
                using Base = SetExpression<SetUnion<TTypeLeft, TTypeRight>>; //! Base class.

                using ltype = TTypeLeft; //! Left type.
                using rtype = TTypeRight; //! Right type.
                using type = SetUnion<TTypeLeft, TTypeRight>; //! Expression type.

                /**
                 * @brief Constructor for the union operation.
                 *
                 * @details The syntax is as follows:
                 * \code
                 * // A U B
                 * SetUnion(A, B);
                 * \endcode
                 *
                 * @param left The left operand.
                 * @param right The right operand.
                 *
                 * @param empty If true, the expression will be treated as the empty set.
                 */
                SetUnion(const TTypeLeft &left, const TTypeRight &right, bool empty = false) : left_(left),
                                                                                               right_(right),
                                                                                               empty_(empty)
                {
//                    if (std::is_same<TTypeLeft, TTypeRight>::value)
//                        Base::sEnum_ = static_cast<TTypeLeft const &>(left).getEnum();
//                    else
                    this->sEnum_ = SetEnum::Union;
                }

                /**
                 * @brief Returns true if the expression is the empty set.
                 *
                 * @return True if expression is the empty set.
                 */
                bool isEmpty() const
                {
                    return empty_;
                }

                /**
                 * @brief Returns true if this expression contains \c el.
                 *
                 * @tparam TElementType Type of the element.
                 *
                 * @param el Element.
                 *
                 * @return True if this expression contains \c el, false otherwise.
                 */
                template<typename TElementType>
                bool contains(const TElementType &el) const
                {
                    return left_.contains(el) || right_.contains(el);
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
                template<typename TOtherExpr>
                SetUnion<type, TOtherExpr> unionize(const SetExpression <TOtherExpr> &expr)
                {
                    return SetUnion<type, TOtherExpr>(*this, *static_cast<const TOtherExpr *>(&expr),
                                                      isEmpty() && expr.isEmpty());
                }

                /**
                 * @brief Returns signed distance to \c p.
                 *
                 * @tparam Derived Derived MatrixBase class.
                 *
                 * @param p A point.
                 *
                 * @return Signed distance.
                 */
                template<typename Derived>
                double sdf(Eigen::MatrixBase<Derived> &p) const
                {
                    if (isEmpty())
                        return std::numeric_limits<double>::infinity();
                    else
                        return std::min(left_.sdf(p), right_.sdf(p));
                }

                /**
                 * @brief Gets the left expression.
                 *
                 * @return Left expression.
                 */
                const TTypeLeft &getLeft() const
                {
                    return left_;
                }

                /**
                 * @brief Gets the right expression.
                 *
                 * @return Right expression.
                 */
                const TTypeRight &getRight() const
                {
                    return right_;
                }

            protected:
                const TTypeLeft &left_; //! Left constant reference.
                const TTypeRight &right_; //! Right constant reference.
                bool empty_; //! Empty bool.
            };
        }
    }
}

#endif //LODESTAR_SETUNION_HPP
