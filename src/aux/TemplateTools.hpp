//
// Created by Hamza El-Kebir on 12/22/21.
//

#ifndef LODESTAR_TEMPLATETOOLS_HPP
#define LODESTAR_TEMPLATETOOLS_HPP

#include "TemplateTraits.hpp"

namespace ls {
    namespace aux {
        class TemplateTools {
        public:
            template <typename TType, template <typename ...> class TWrapper, bool isWrapped = TemplateTraits::isInstance<TType, TWrapper>::value>
            struct wrap;

            template <typename TType, template <typename ...> class TWrapper>
            struct wrap<TType, TWrapper, true> {
                using type = TType;
            };

            template <typename TType, template <typename ...> class TWrapper>
            struct wrap<TType, TWrapper, false> {
                using type = TWrapper<TType>;
            };

            // https://stackoverflow.com/a/16853775
            template<typename, typename>
            struct appendToTypeSequence { };

            template<typename T, typename... Ts, template<typename...> class TT>
            struct appendToTypeSequence<T, TT<Ts...>>
            {
                using type = TT<Ts..., T>;
            };

            template<typename T, unsigned int N, template<typename...> class TT>
            struct repeat
            {
                using type = typename
                appendToTypeSequence<
                        T,
                        typename repeat<T, N-1, TT>::type
                >::type;
            };

            template<typename T, template<typename...> class TT>
            struct repeat<T, 0, TT>
            {
                using type = TT<>;
            };

            class Executors {
            public:
                // https://stackoverflow.com/a/6894436
                template<std::size_t I = 0, typename FuncT, typename... Tp>
                static typename std::enable_if<I == sizeof...(Tp), void>::type
                forEach(std::tuple<Tp...> &, FuncT) // Unused arguments are given no names.
                { }

                template<std::size_t I = 0, typename FuncT, typename... Tp>
                static typename std::enable_if<I < sizeof...(Tp), void>::type
                forEach(std::tuple<Tp...>& t, FuncT f)
                {
                    f(std::get<I>(t));
                    forEach<I + 1, FuncT, Tp...>(t, f);
                }

                template<std::size_t I = 0, typename FuncT, typename... Tp>
                static typename std::enable_if<I == sizeof...(Tp), void>::type
                forEachPointer(std::tuple<Tp...> &, FuncT) // Unused arguments are given no names.
                { }

                template<std::size_t I = 0, typename FuncT, typename... Tp>
                static typename std::enable_if<I < sizeof...(Tp), void>::type
                forEachPointer(std::tuple<Tp...>& t, FuncT f)
                {
                    f(&std::get<I>(t));
                    forEachPointer<I + 1, FuncT, Tp...>(t, f);
                }

            protected:
                // https://stackoverflow.com/a/6454211
                template<int...> struct index_tuple{};

                template<int I, typename IndexTuple, typename... Types>
                struct make_indexes_impl;

                template<int I, int... Indexes, typename T, typename ... Types>
                struct make_indexes_impl<I, index_tuple<Indexes...>, T, Types...>
                {
                    typedef typename make_indexes_impl<I + 1, index_tuple<Indexes..., I>, Types...>::type type;
                };

                template<int I, int... Indexes>
                struct make_indexes_impl<I, index_tuple<Indexes...> >
                {
                    typedef index_tuple<Indexes...> type;
                };

                template<typename ... Types>
                struct make_indexes : make_indexes_impl<0, index_tuple<>, Types...>
                {};

            public:
                // Apply variadic function to tuple, wrapped in Wrapper
                // Template template parameter magicks abound!
                template<class Ret, class... Args, template <typename...> class Wrapper, int... Indexes >
                static Ret applyWrapped_helper(std::function<Ret(Args...)> &pf, index_tuple< Indexes... >, std::tuple<Wrapper<Args>...>&& tup)
                {
                    return pf( std::forward<Args>( std::get<Indexes>(tup).object)... );
                }

                template<class Ret, class ... Args, template <typename...> class Wrapper>
                static Ret applyWrapped(std::function<Ret(Args...)> &pf, const std::tuple<Wrapper<Args>...>&  tup)
                {
                    return applyWrapped_helper(pf, typename make_indexes<Args...>::type(), std::tuple<Wrapper<Args>...>(tup));
                }

                template<class Ret, class ... Args, template <typename...> class Wrapper>
                static Ret applyWrapped(std::function<Ret(Args...)> &pf, std::tuple<Wrapper<Args>...>&&  tup)
                {
                    return applyWrapped_helper(pf, typename make_indexes<Args...>::type(), std::forward<std::tuple<Wrapper<Args>...>>(tup));
                }
            };
        };
    }
}

#endif //LODESTAR_TEMPLATETOOLS_HPP
