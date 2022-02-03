//
// Created by Hamza El-Kebir on 12/22/21.
//

#ifndef LODESTAR_TEMPLATETRAITS_HPP
#define LODESTAR_TEMPLATETRAITS_HPP

#include <type_traits>

#define RETURNS(...) \
  noexcept(noexcept(__VA_ARGS__)) \
    ->decltype(__VA_ARGS__) { \
      return (__VA_ARGS__); \
  }

namespace ls {
    namespace aux {
        class TemplateTraits {
        public:
            // See https://stackoverflow.com/a/44013030
            template<class, template<class...> class>
            struct isInstance : public ::std::false_type {
                static const bool value = false;
            };

            template<class... T, template<class...> class U>
            struct isInstance<U<T...>, U> : public ::std::true_type {
                static const bool value = true;
            };

            // https://stackoverflow.com/a/29671981
            template<bool...>
            struct bool_pack;
            template<bool... bs>
            using allTrue = ::std::is_same<bool_pack<bs..., true>, bool_pack<true, bs...>>;

            template<bool... bs>
            using allFalse = ::std::is_same<bool_pack<bs..., false>, bool_pack<false, bs...>>;

            template<class R, class... Ts>
            using allConvertible = allTrue<::std::is_convertible<Ts, R>::value...>;

            template<class R, class... Ts>
            using allSame = allTrue<::std::is_same<Ts, R>::value...>;

            template<class R, class... Ts>
            using allBasedOf = allTrue<::std::is_base_of<R, Ts>::value...>;

            template<bool... bs>
            using anyTrue = ::std::integral_constant<bool, !allFalse<bs...>::value>;

            template<class R, class... Ts>
            using anyConvertible = anyTrue<::std::is_convertible<Ts, R>::value...>;

            /**
             * @brief Provides binary operator traits.
             */
            class BinaryOperators {
            protected:
                struct addable {
                    template<class T, class U>
                    auto operator()(T t, U u) RETURNS(t + u)
                };

                struct subtractable {
                    template<class T, class U>
                    auto operator()(T t, U u) RETURNS(t - u)
                };

                struct multiplicable {
                    template<class T, class U>
                    auto operator()(T t, U u) RETURNS(t * u)
                };

                struct divisible {
                    template<class T, class U>
                    auto operator()(T t, U u) RETURNS(t / u)
                };

            public:
                // See https://stackoverflow.com/a/29014938
                template<class...>
                struct voider {
                    using type = void;
                };
                template<class...Ts>
                using void_t = typename voider<Ts...>::type;

                template<class T, class U, class BinaryOperation, class Enable = void>
                struct isBinopableImpl : ::std::false_type {
                    using returnType = void;
                };

                template<class T, class U, class BinOp>
                struct isBinopableImpl<T, U, BinOp, void_t<
                        decltype(::std::declval<BinOp>()(
                                ::std::declval<T>(), ::std::declval<U>()))>> :
                        ::std::true_type {
                    using returnType = typename ::std::decay<decltype(::std::declval<BinOp>()(
                            ::std::declval<T>(), ::std::declval<U>()))>::type;
                };

                /**
                 * @brief Extracts data from matrix-like types.
                 *
                 * @details Inherits from @c ::std::false_type if the @c T is
                 * not matrix-like.
                 *
                 * @note This is limited to @a Eigen matrices at the moment.
                 *
                 * @tparam T Purported matrix-like type.
                 */
                template<typename T>
                struct parseMatrixLike : ::std::false_type {
                    using scalar = T;

                    enum {
                        rows = 0,
                        cols = 0
                    };
                };

                /**
                 * @brief Extracts data from matrix-like types.
                 *
                 * @tparam TWrapper Matrix-like wrapper.
                 * @tparam TScalar Scalar type.
                 * @tparam TRows Number of rows.
                 * @tparam TCols Number of columns.
                 * @tparam TOtherParams Parameter pack containing other parameters.
                 */
                template<template<typename, int, int, int...> class TWrapper, typename TScalar, int TRows, int TCols, int... TOtherParams>
                struct parseMatrixLike<TWrapper<TScalar, TRows, TCols, TOtherParams...>>
                        : ::std::true_type {
                    using scalar = TScalar;
                    enum {
                        rows = TRows,
                        cols = TCols
                    };

                    template<typename UScalar, int URows, int UCols, int... UOtherParams>
                    using wrapper = TWrapper<UScalar, URows, UCols, UOtherParams...>;
                };

                /**
                 * @brief Sanitizes a binary operator return type.
                 *
                 * @tparam T Type to be sanitized.
                 * @tparam BinOp Binary operator that produced @c T.
                 */
                template<typename T, class BinOp>
                struct sanitizeTypeBinop : ::std::false_type {
                    using returnType = T;
                };

                /**
                 * @brief Sanitizes lazy binary operation output.
                 *
                 * @details @a Eigen returns lazy wrappers for operations that
                 * can be cast to their explicit counterparts. For example,
                 * a multiplication between a 3x3-matrix and a 3-vector has the
                 * following form:
                 *
                 * @code
                 Eigen::Matrix3d m; Eigen::Vector3d v;
                 auto p = m * v; // -> Eigen::Product<Eigen::Matrix3d, Eigen::Vector3d, 0>;
                 * @endcode
                 *
                 * The operations in this partial specialization are as follows:
                 *
                 * - <b>(1)</b> Check if the underlying scalar types are binopable.
                 *   + <b>(1.a)</b> If so, check if LHS and RHS are matrix-like:
                 *     - <b>(1.a.a)</b> If so, wrap the resulting matrix dimensions and type in the first wrapper.
                 *     - <b>(1.a.b)</b> If not, return original type.
                 *   + <b>(1.b)</b> If not, return original type.
                 *
                 * @tparam BinOp Binary operator functor.
                 * @tparam TWrapper Lazy operator wrapper (e.g., @c Eigen::Product).
                 * @tparam TWrapperInts Integer options for the operator wrapper.
                 * @tparam TWrapperChild1 First operand wrapper.
                 * @tparam TWrapperChild2 Second operand wrapper.
                 * @tparam TScalar First operand scalar type.
                 * @tparam UScalar Second operand scalar type.
                 * @tparam TInts First operand integer parameters.
                 * @tparam UInts Second operand integer parameters.
                 */
                template<class BinOp,
                        template<typename, typename, int...> class TWrapper,
                        int... TWrapperInts,
                        template<typename, int...> class TWrapperChild1,
                        template<typename, int...> class TWrapperChild2,
                        typename TScalar,
                        typename UScalar,
                        int... TInts,
                        int... UInts>
                struct sanitizeTypeBinop<TWrapper<
                        TWrapperChild1<TScalar, TInts...>,
                        TWrapperChild2<UScalar, UInts...>,
                        TWrapperInts...>, BinOp>
                        :
                                ::std::true_type {
                    using condition1 = typename ::std::conditional<
                            isBinopableImpl<TScalar, UScalar, BinOp>::value,
                            ::std::true_type,
                            ::std::false_type>::type;

                    using condition2 = typename ::std::conditional<
                            parseMatrixLike<TWrapperChild1<TScalar, TInts...>>::value &&
                            parseMatrixLike<TWrapperChild2<UScalar, UInts...>>::value,
                            ::std::true_type,
                            ::std::false_type
                    >::type;

                    using input = TWrapper<TWrapperChild1<TScalar, TInts...>, TWrapperChild2<UScalar, UInts...>>;
                    // TODO: Investigate if TOtherParams or UOtherParams matter.
                    using sanitized = TWrapperChild1<typename ::std::decay<typename isBinopableImpl<TScalar, UScalar, BinOp>::returnType>::type, parseMatrixLike<TWrapperChild1<TScalar, TInts...>>::rows, parseMatrixLike<TWrapperChild2<UScalar, UInts...>>::cols>;

                    using returnType = typename ::std::conditional<
                            (allSame<::std::true_type, condition1, condition2>::value),
                            sanitized,
                            input
                    >::type;
                };

                template<typename T>
                using sanitizeTypeMultiplicable = sanitizeTypeBinop<T, multiplicable>;

                template<class T, class U, class BinOp>
                using isBinopable = isBinopableImpl<T, U, BinOp>;

                template<class T, class U = T>
                using isAddable = isBinopable<T, U, addable>;

                template<class T, class U = T>
                using isSubtractable = isBinopable<T, U, subtractable>;

                template<class T, class U = T>
                using isMultiplicable = isBinopable<T, U, multiplicable>;

                template<class T, class U = T>
                using isDivisble = isBinopable<T, U, divisible>;
            };
        };
    }
}

#undef RETURNS

#endif //LODESTAR_TEMPLATETRAITS_HPP
