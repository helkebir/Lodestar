//
// Created by Hamza El-Kebir on 6/12/21.
//

#ifndef LODESTAR_BINOPCHECK_HPP
#define LODESTAR_BINOPCHECK_HPP

#include <type_traits>

// See https://stackoverflow.com/a/29014938
template<class...>
struct voider {
    using type = void;
};
template<class...Ts>
using void_t = typename voider<Ts...>::type;

template<class T, class U, class BinaryOperation, class Enable = void>
struct is_binop_able_ : std::false_type {
};
template<class T, class U, class BinOp>
struct is_binop_able_<T, U, BinOp, void_t<
        decltype(std::declval<BinOp>()(
                std::declval<T>(), std::declval<U>()))>> :
        std::true_type {
};

template<class T, class U, class BinOp>
using is_binop_able = typename is_binop_able_<T, U, BinOp>::type;

#define RETURNS(...) \
  noexcept(noexcept(__VA_ARGS__)) \
    ->decltype(__VA_ARGS__) { \
      return (__VA_ARGS__); \
  }

struct plus {
    template<class T, class U>
    auto operator()(T t, U u) RETURNS(t + u)
};

template<class T, class U = T>
using is_addable = is_binop_able<T, U, plus>;

struct multiplies {
    template<class T, class U>
    auto operator()(T t, U u) RETURNS(t * u)
};

template<class T, class U = T>
using is_multiplicable = is_binop_able<T, U, multiplies>;

#undef RETURNS

#endif //LODESTAR_BINOPCHECK_HPP
