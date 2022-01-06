//
// Created by Hamza El-Kebir on 5/27/21.
//

#ifndef LODESTAR_CONJUNCTION_HPP
#define LODESTAR_CONJUNCTION_HPP

// std::Conjunction implementation (> C++17)
// https://en.cppreference.com/w/cpp/types/conjunction
// See https://www.fluentcpp.com/2021/04/30/how-to-implement-stdconjunction-and-stddisjunction-in-c11/
template<class...>
struct Conjunction : std::true_type {
};

template<class B1>
struct Conjunction<B1> : B1 {
};

template<class B1, class... Bn>
struct Conjunction<B1, Bn...>
        : std::conditional<bool(B1::value), Conjunction<Bn...>, B1>::type {
};

#endif //LODESTAR_CONJUNCTION_HPP
