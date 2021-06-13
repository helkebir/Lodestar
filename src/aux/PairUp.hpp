//
// Created by Hamza El-Kebir on 6/12/21.
//

#ifndef LODESTAR_PAIRUP_HPP
#define LODESTAR_PAIRUP_HPP

#include <tuple>
#include <utility>
#include <type_traits>
#include "Indices.hpp"

// See https://stackoverflow.com/a/56367292
template <typename ... Nodes>
struct CollectionImpl
{
    CollectionImpl(Nodes ... ns) : nodes(ns...){}

    std::tuple<Nodes...> nodes;
};

template <typename Seq, typename Tup>
struct CollectionMaker;

template <int ... Is, typename Tuple>
struct CollectionMaker<IndexSequence<Is...>, Tuple>
{
    using type = CollectionImpl<std::pair<typename std::tuple_element<Is, Tuple>::type,
            typename std::tuple_element<Is + 1, Tuple>::type>...>;
};

template <typename ... Ts>
using Collection = typename CollectionMaker<typename Indices<sizeof...(Ts) - 1>::type,
        std::tuple<Ts...>>::type;

//template <typename>
//struct tag
//{ };
//
//template <typename...>
//struct getTpls;
//
//template <std::size_t ... Is, typename ... Ts>
//struct getTpls<IndexSequence<Is...>, Ts...>
//{
//    using tpl0 = std::tuple<tag<Ts>...>;
//    using ftpl = std::tuple<typename std::tuple_element<Is,    tpl0>::type...>;
//    using stpl = std::tuple<typename std::tuple_element<1u+Is, tpl0>::type...>;
//};
//
//template <typename ... Ts>
//struct Collection
//{
//    static_assert( sizeof...(Ts) > 1u, "more types, please");
//
//    using getT = getTpls<typename Indices<sizeof...(Ts)-1u>::type, Ts...>;
//
//    using ftpl = typename getT::ftpl;
//    using stpl = typename getT::stpl;
//
//    template <typename ... FTs, typename ... STs>
//    using type = std::tuple<std::pair<FTs, STs>...>;
//};

//template <typename TInputsList>
//struct PairUp{};
//
//template <typename TInput1, typename TInput2>
//struct PairUp<std::tuple<TInput1, TInput2>> {
//    using type = std::tuple<std::pair<TInput1, TInput2>>;
//    using pair = std::pair<TInput1, TInput2>;
//};
//
//template <typename TInput1, typename TInput2, typename... TInputs>
//struct PairUp<std::tuple<TInput1, TInput2, TInputs...>> {
//    using type = std::tuple<std::pair<TInput1, TInput2>, PairUp<TInput2, TInputs...>::pair>;
//    using pair = std::pair<TInput1, TInput2>;
//};
//
//{
//    typename PairUp<std::tuple<double, int, double>>::type P;
//}

#endif //LODESTAR_PAIRUP_HPP
