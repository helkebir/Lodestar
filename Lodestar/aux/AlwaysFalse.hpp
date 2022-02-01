//
// Created by Hamza El-Kebir on 2/1/22.
//

#ifndef LODESTAR_ALWAYSFALSE_HPP
#define LODESTAR_ALWAYSFALSE_HPP

#include <type_traits>

template <class... T>
struct always_false : ::std::false_type {};

#endif //LODESTAR_ALWAYSFALSE_HPP
