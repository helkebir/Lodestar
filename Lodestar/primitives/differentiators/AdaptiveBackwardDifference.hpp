//
// Created by Hamza El-Kebir on 6/20/21.
//

#ifndef LODESTAR_ADAPTIVEBACKWARDDIFFERENCE_HPP
#define LODESTAR_ADAPTIVEBACKWARDDIFFERENCE_HPP

#include "BackwardDifference.hpp"
#include "Lodestar/aux/ArrayStack.hpp"
#include <type_traits>
#include <array>

namespace ls {
    namespace primitives {
        template<typename TType, size_t TOrder, typename TScalarType = double>
        class AdaptiveBackwardDifference {

        };

        template<typename TType, typename TScalarType>
        class AdaptiveBackwardDifference<TType, 1, TScalarType> {
        public:
            static const size_t kOrder = 1;

            template<size_t TSamples>
            static typename std::enable_if<(TSamples > kOrder), TType>::type
            compute(TScalarType h, const std::array<TType, TSamples> &a)
            {
                return computeImpl(h, a);
            }

            template<size_t TSamples>
            static typename std::enable_if<(TSamples > kOrder), TType>::type
            compute(TScalarType h, const std::array<TType, TSamples> &a, const size_t size)
            {

                switch (size) {
                    case 0:
                    case 1:
                        return {};
                    case 2:
                        return BackwardDifference<TType, 2, 1>::compute(a[1], a[0], h);
                    case 3:
                        return BackwardDifference<TType, 3, 1>::compute(a[2], a[1], a[0], h);
                    case 4:
                        return BackwardDifference<TType, 4, 1>::compute(a[3], a[2], a[1], a[0], h);
                    case 5:
                        return BackwardDifference<TType, 5, 1>::compute(a[4], a[3], a[2], a[1], a[0], h);
                    case 6:
                        return BackwardDifference<TType, 6, 1>::compute(a[5], a[4], a[3], a[2], a[1], a[0], h);
                }

                return computeImpl(h, a);
            }

            template<size_t TSamples>
            static typename std::enable_if<(TSamples <= kOrder), TType>::type
            compute(TScalarType h, const std::array<TType, TSamples> &a, const size_t size)
            {
                static_assert(TSamples > kOrder, "Number of samples must be greater than the differentiation order.");

                return TType{};
            }

            template<size_t TSamples>
            static typename std::enable_if<(TSamples > kOrder) && (TSamples > 7), TType>::type
            compute(TScalarType h, const std::array<TType, TSamples> &a)
            {
                return BackwardDifference<TType, 7, 1>::compute(a[6], a[5], a[4], a[3], a[2], a[1], a[0], h);
            }

            template<size_t TSamples>
            static typename std::enable_if<(TSamples <= kOrder), TType>::type
            compute(TScalarType h, const std::array<TType, TSamples> &a)
            {
                static_assert(TSamples > kOrder, "Number of samples must be greater than the differentiation order.");

                return TType{};
            }

        protected:
            static inline TType computeImpl(TScalarType h, const std::array<TType, 2> &a)
            {
                return BackwardDifference<TType, 2, 1>::compute(a[1], a[0], h);
            }

            static inline TType computeImpl(TScalarType h, const std::array<TType, 3> &a)
            {
                return BackwardDifference<TType, 3, 1>::compute(a[2], a[1], a[0], h);
            }

            static inline TType computeImpl(TScalarType h, const std::array<TType, 4> &a)
            {
                return BackwardDifference<TType, 4, 1>::compute(a[3], a[2], a[1], a[0], h);
            }

            static inline TType computeImpl(TScalarType h, const std::array<TType, 5> &a)
            {
                return BackwardDifference<TType, 5, 1>::compute(a[4], a[3], a[2], a[1], a[0], h);
            }

            static inline TType computeImpl(TScalarType h, const std::array<TType, 6> &a)
            {
                return BackwardDifference<TType, 6, 1>::compute(a[5], a[4], a[3], a[2], a[1], a[0], h);
            }

            template<size_t TSamples>
            static typename std::enable_if<(TSamples > kOrder) && (TSamples >= 7), TType>::type
            computeImpl(TScalarType h, const std::array<TType, TSamples> &a)
            {
                return BackwardDifference<TType, 7, 1>::compute(a[6], a[5], a[4], a[3], a[2], a[1], a[0], h);
            }
        };
    }
}

#endif //LODESTAR_ADAPTIVEBACKWARDDIFFERENCE_HPP
