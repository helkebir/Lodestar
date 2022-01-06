//
// Created by Hamza El-Kebir on 4/17/21.
//

#include "LinearSystemInverse.hpp"

ls::systems::StateSpace<> ls::analysis::LinearSystemInverse::inverse(const ls::systems::StateSpace<> *ss)
{
    auto out = ls::systems::StateSpace<>();
    inverse(ss, &out);

    return out;
}

ls::systems::StateSpace<> ls::analysis::LinearSystemInverse::inverse(const ls::systems::StateSpace<> &ss)
{
    auto out = ls::systems::StateSpace<>();
    // FIXME: Check type of D.inverse(), as well as dimension matching.
    inverse(ss, &out);

    return out;
}