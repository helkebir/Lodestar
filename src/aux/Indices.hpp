//
// Created by Hamza El-Kebir on 6/10/21.
//

#ifndef LODESTAR_INDICES_HPP
#define LODESTAR_INDICES_HPP

// C++11 implementation of std::integer_sequence (https://en.cppreference.com/w/cpp/utility/integer_sequence)
// See https://stackoverflow.com/a/7858971
template<int ...>
struct IndexSequence {
};

template<int N, int ...S>
struct Indices : Indices<N - 1, N - 1, S...> {
};

template<int ...S>
struct Indices<0, S...> {
    typedef IndexSequence<S...> type;
};

#endif //LODESTAR_INDICES_HPP
