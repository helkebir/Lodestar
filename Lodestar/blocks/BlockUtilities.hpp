//
// Created by Hamza El-Kebir on 12/23/21.
//

#ifndef LODESTAR_BLOCKUTILITIES_HPP
#define LODESTAR_BLOCKUTILITIES_HPP

#include "Signal.hpp"

template <typename TObject>
static bool connect(ls::blocks::Signal<TObject> * a, ls::blocks::Signal<TObject> * b)
{
    return a->connect(b);
}

template <typename TObject>
static bool connect(ls::blocks::Signal<TObject> & a, ls::blocks::Signal<TObject> & b)
{
    return a.connect(b);
}

#endif //LODESTAR_BLOCKUTILITIES_HPP
