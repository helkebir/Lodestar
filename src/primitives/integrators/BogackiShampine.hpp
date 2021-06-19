//
// Created by Hamza El-Kebir on 6/18/21.
//

#ifndef LODESTAR_BOGACKISHAMPINE_HPP
#define LODESTAR_BOGACKISHAMPINE_HPP

namespace ls {
    namespace primitives {
        template <typename TType, typename TScalarType = double>
        class BogackiShampine {
            typedef TType (*) (TScalarType, TType) TDFunction;

            TType integrate(TDFunction f, TScalarType h, size_t N);
        };

        template<typename TType, typename TScalarType>
        TType BogackiShampine<TType, TScalarType>::integrate(TDFunction f, TScalarType h, size_t N)
        {
            return nullptr;
        }
    }
}

#endif //LODESTAR_BOGACKISHAMPINE_HPP
