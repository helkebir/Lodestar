//
// Created by Hamza El-Kebir on 12/22/21.
//

#ifndef LODESTAR_ANY_HPP
#define LODESTAR_ANY_HPP

#include <iostream>
#include <type_traits>
#include <array>
#include "DynamicDataTypes.hpp"
#include "TemplateTraits.hpp"

namespace ls {
    namespace aux {
        /**
         * Container capable of containing any of the \c TTypes.
         *
         * @note Inspired by
         * https://gist.github.com/Mr-Andersen/cd5f9d8740e03b3a779bd49da281652d
         *
         * @tparam TTypes Types to be included in the Any.
         */
        template<typename... TTypes>
        class Any {
            template<typename T>
            static constexpr T max(const T &a, const T &b)
            {
                return a > b ? a : b;
            }

            // max_size<Ts...>::value
            template<typename T, typename... Ts>
            struct max_size {
                static const size_t value = max(sizeof(T),
                                                max_size<Ts...>::value);
            };

            template<typename T>
            struct max_size<T> {
                static const size_t value = sizeof(T);
            };

            size_t currentType;
            char data[max_size<TTypes...>::value];

            // https://stackoverflow.com/a/27588263
            template<typename T, typename... Ts>
            struct get_index;

            template<typename T, typename... Ts>
            struct get_index<T, T, Ts...>
                    : std::integral_constant<std::size_t, 0> {
                static constexpr bool conclusive = true;
            };

            template<typename T, typename Tail, typename... Ts>
            struct get_index<T, Tail, Ts...>
                    : std::integral_constant<std::size_t,
                            1 + get_index<T, Ts...>::value> {
                static constexpr bool conclusive = true;
            };

            template<typename T>
            struct get_index<T> : std::integral_constant<std::size_t, 0> {
                static constexpr bool conclusive = false;
                // condition is always false, but should be dependent on T
                //        static_assert(sizeof(T) == 0, "Element not found");
            };
        public:
            Any()
                    : currentType(), data(),
                      tags{DynamicDataTypes::type_to_enum<TTypes>::type...}
            {}

            DynamicDataTypes::Types tags[sizeof...(TTypes)];

            DynamicDataTypes::Types tag() const
            {
                return tags[currentType];
            }

            /* This signature is required as per: https://en.cppreference.com/w/cpp/types/enable_if
             * See section on function template equivalence.
             */
            template<typename TType, typename std::enable_if<get_index<TType, TTypes...>::conclusive, bool>::type = true>
            Any(const TType &x):
                    currentType(get_index<TType, TTypes...>::value)
            {
                auto ptr = reinterpret_cast<const char *>(&x);
                std::copy(ptr, ptr + sizeof(TType), data);
            }

            template<typename TType, typename std::enable_if<!get_index<TType, TTypes...>::conclusive, bool>::type = true>
            Any(const TType &x):
                    currentType(get_index<TType, TTypes...>::value)
            {
                static_assert(get_index<TType, TTypes...>::conclusive,
                              "Type not found.");
            }

            template<typename TType, typename std::enable_if<get_index<TType, TTypes...>::conclusive, bool>::type = true>
            const TType &operator=(const TType &x)
            {
                currentType = get_index<TType, TTypes...>::value;
                auto ptr = reinterpret_cast<const char *>(&x);
                std::copy(ptr, ptr + sizeof(TType), data);
                return x;
            }

            template<typename TType, typename std::enable_if<!get_index<TType, TTypes...>::conclusive, bool>::type = true>
            const TType &operator=(const TType &x)
            {
                static_assert(get_index<TType, TTypes...>::conclusive,
                              "Type not found.");
                return x;
            }

            template<typename TType>
            bool is() const
            {
                auto res = get_index<TType, TTypes...>{};
                if (res.conclusive)
                    return currentType == res.value;
                else
                    return false;
            }

            template<typename TType>
            TType &as()
            {
                // TODO: Use safe StatusOr<TType> instead of throwing error.
                if (!is<TType>())
                    throw std::runtime_error("Requested type is not contained");

                return *reinterpret_cast<TType *>(data);
            }

            template<typename TType>
            const TType &as() const
            {
                // TODO: Use safe StatusOr<TType> instead of throwing error.
                if (!is<TType>())
                    throw std::runtime_error("Requested type is not contained");

                return *reinterpret_cast<const TType *>(data);
            }

            template<typename TType>
            bool into(TType &x)
            {
                if (!is<TType>())
                    return false;
                x = *reinterpret_cast<TType *>(data);
                return true;
            }

            template<typename TType>
            bool anyConvertible()
            {
                return TemplateTraits::anyConvertible<TType, TTypes...>::value;
            }
        };
    }
}

#endif //LODESTAR_ANY_HPP
