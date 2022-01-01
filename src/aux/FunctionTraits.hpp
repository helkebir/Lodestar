//
// Created by Hamza El-Kebir on 12/30/2021.
//

#ifndef LODESTAR_FUNCTIONTRAITS_HPP
#define LODESTAR_FUNCTIONTRAITS_HPP

#include <functional>

namespace ls {
    namespace aux {
        template<typename TType>
        struct FunctionTraits : public FunctionTraits<decltype(&TType::operator())> {
        };

        template<typename TClass, typename TReturn, typename... TArgs>
        struct FunctionTraits<TReturn(TClass::*)(TArgs...) const> {
            enum {
                arity = sizeof...(TArgs)
            };

            using res = TReturn;

            template<int I>
            struct arg {
                static_assert(((I >= 0) && (I < arity)), "Argument index out of range.");
                using type = typename ::std::tuple_element<I, ::std::tuple<TArgs...>>::type;
            };

            using func = ::std::function<TReturn(TArgs...)>;
        };
    }
}

#endif //LODESTAR_FUNCTIONTRAITS_HPP
