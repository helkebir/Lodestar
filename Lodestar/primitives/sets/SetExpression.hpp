//
// Created by Hamza El-Kebir on 6/21/21.
//

#ifndef LODESTAR_SETEXPRESSION_HPP
#define LODESTAR_SETEXPRESSION_HPP

#include "SetEnum.hpp"
#include <Eigen/Dense>

namespace ls {
    namespace primitives {
        namespace sets {
            template<typename TType>
            class SetExpression {
            public:
                using type = TType;

                SetExpression() : sEnum_(SetEnum::Unknown)
                {}

                SetExpression(const SetEnum setEnum) : sEnum_(setEnum)
                {}

                template<typename TElementType>
                bool operator==(const TElementType &el) const
                {
                    return static_cast<TType const &>(*this).operator==(el);
                }

                template<typename TElementType>
                bool operator!=(const TElementType &el) const
                {
                    return static_cast<TType const &>(*this).operator!=(el);
                }

                template<typename TElementType>
                bool contains(const TElementType &el) const
                {
                    return static_cast<TType const &>(*this).contains(el);
                }

                template<typename TElementType>
                bool isSubset(const TElementType &el) const
                {
                    return static_cast<TType const &>(*this).isSubset(el);
                }

                template<typename TElementType>
                bool isSuperset(const TElementType &el) const
                {
                    return static_cast<TType const &>(*this).isSuperset(el);
                }

                bool isEmpty() const
                {
                    return static_cast<TType const &>(*this).isEmpty();
                }

                template<typename TReturnType, typename TElementType>
                SetExpression<TReturnType> relComplement(const TElementType &el) const
                {
                    return static_cast<TType const &>(*this).relComplement(el);
                }

                template<typename TReturnType, typename TOtherExpr>
                SetExpression<TReturnType> unionize(const TOtherExpr &expr)
                {
                    return static_cast<TType const &>(*this).unionize(expr);
                }

                template<typename Derived>
                double sdf(Eigen::MatrixBase<Derived> &p) const
                {
                    return static_cast<TType const &>(*this).sdf(p);
                }

                SetEnum getEnum() const
                {
                    return sEnum_;
                }

            protected:
                SetEnum sEnum_;
            };
        }
    }
}

#endif //LODESTAR_SETEXPRESSION_HPP
