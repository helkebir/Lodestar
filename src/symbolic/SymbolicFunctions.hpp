//
// Created by Hamza El-Kebir on 6/25/21.
//

#ifndef LODESTAR_SYMBOLICFUNCTIONS_HPP
#define LODESTAR_SYMBOLICFUNCTIONS_HPP

#ifdef LS_USE_GINAC

#include <ginac/ginac.h>

namespace GiNaC {
    DECLARE_FUNCTION_2P(max);

    DECLARE_FUNCTION_2P(min);
}

#endif

#endif //LODESTAR_SYMBOLICFUNCTIONS_HPP
