//
// Created by Hamza El-Kebir on 6/10/21.
//

#ifndef LODESTAR_REPEAT_HPP
#define LODESTAR_REPEAT_HPP

#include <tuple>
#include "Indices.hpp"

// Structs that serve to construct a template pack with repeated types.
// See https://stackoverflow.com/a/16853853
template<typename TDependent, int TIndex>
using DependOn = TDependent;

template<typename TType, int TTimes, typename TIndices = typename Indices<TTimes>::type>
struct Repeat;

template<typename TType, int TTimes, int... TIndices>
struct Repeat<TType, TTimes, IndexSequence<TIndices...>> {
    using type = std::tuple<DependOn<TType, TIndices>...>;
};

#endif //LODESTAR_REPEAT_HPP
