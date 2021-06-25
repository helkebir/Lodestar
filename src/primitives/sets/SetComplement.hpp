//
// Created by Hamza El-Kebir on 6/24/21.
//

#ifndef LODESTAR_SETCOMPLEMENT_HPP
#define LODESTAR_SETCOMPLEMENT_HPP

#include "SetExpression.hpp"
#include <type_traits>
#include <algorithm>

namespace ls {
    namespace primitives {
        namespace sets {
            /**
             * @brief Relative complement of two SetExpressions.
             *
             * @details The syntax is as follows:
             * \code
             * // C = A \ B
             * auto C = SetComplement(A, B);
             * \endcode
             *
             * @tparam TTypeLeft Type of the left SetExpression.
             * @tparam TTypeRight Type of the right SetExpression.
             */
            template<typename TTypeLeft, typename TTypeRight>
            class SetComplement : public SetExpression<SetComplement<TTypeLeft, TTypeRight>> {
            public:
                using Base = SetExpression<SetComplement<TTypeLeft, TTypeRight>>; //! Base class.

                using ltype = TTypeLeft; //! Left type.
                using rtype = TTypeRight; //! Right type.
                using type = SetComplement<TTypeLeft, TTypeRight>; //! Expression type.

                /**
                 * @brief Constructor for the relative complement operation.
                 *
                 * @details The syntax is as follows:
                 * \code
                 * // A \ B
                 * SetComplement(A, B);
                 * \endcode
                 *
                 * @param left The left operand.
                 * @param right The right operand.
                 *
                 * @param empty If true, the expression will be treated as the empty set.
                 */
                SetComplement(const TTypeLeft &left, const TTypeRight &right, bool empty = false) : left_(left),
                                                                                                    right_(right),
                                                                                                    empty_(empty)
                {
//                    if (std::is_same<TTypeLeft, TTypeRight>::value)
//                        Base::sEnum_ = static_cast<TTypeLeft const &>(left).getEnum();
//                    else
                    this->sEnum_ = SetEnum::Complement;
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
                    return left_.contains(el) && (!right_.contains(el));
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
                    return SetUnion<type, TExpression>(*this, *static_cast<const TExpression *>(&expr));
                }

                /**
                 * @brief Returns signed distance to \c p.
                 *
                 * @details The signed distance for the complement is computed as follows:
                 * \code
                 * A \ B = A \cap B\compl = (A\compl \cup B)\compl,
                 * \endcode
                 *
                 * which follows by an application of De Morgan's laws. This yields
                 *
                 * \code
                 * A.relComplement(B).sdf(p) = - min(-A.sdf(p), B.sdf(p));
                 * \endcode
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
                    if (isEmpty())
                        return std::numeric_limits<double>::infinity();
                    else
                        return -std::min(-left_.sdf(p), right_.sdf(p));
                }

//                template<typename TLeft, typename TRight>
//                SetUnion<TLeft, TRight> unionize(const TLeft &left, const TRight &right) const
//                {
//                    return SetUnion<TLeft, TRight>(left, right);
//                }

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

#endif //LODESTAR_SETCOMPLEMENT_HPP
