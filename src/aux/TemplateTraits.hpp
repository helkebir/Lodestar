//
// Created by Hamza El-Kebir on 12/22/21.
//

#ifndef LODESTAR_TEMPLATETRAITS_HPP
#define LODESTAR_TEMPLATETRAITS_HPP

#include <type_traits>

namespace ls {
    namespace aux {
        class TemplateTraits {
        public:
            // See https://stackoverflow.com/a/44013030
            template<class, template<class...> class>
            struct isInstance : public std::false_type {
                static const bool value = false;
            };

            template<class T, template<class...> class U>
            struct isInstance<U<T>, U> : public std::true_type {
                static const bool value = true;
            };

            // https://stackoverflow.com/a/29671981
            template<bool...>
            struct bool_pack;
            template<bool... bs>
            using allTrue = std::is_same<bool_pack<bs..., true>, bool_pack<true, bs...>>;

            template<bool... bs>
            using allFalse = std::is_same<bool_pack<bs..., false>, bool_pack<false, bs...>>;

            template<class R, class... Ts>
            using allConvertible = allTrue<std::is_convertible<Ts, R>::value...>;

            template<class R, class... Ts>
            using allSame = allTrue<std::is_same<Ts, R>::value...>;

            template<bool... bs>
            using anyTrue = std::integral_constant<bool, !allFalse<bs...>::value>;

            template<class R, class... Ts>
            using anyConvertible = anyTrue<std::is_convertible<Ts, R>::value...>;
        };
    }
}

#endif //LODESTAR_TEMPLATETRAITS_HPP
