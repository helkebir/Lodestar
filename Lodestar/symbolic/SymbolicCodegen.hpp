//
// Created by Hamza El-Kebir on 2/6/22.
//

#ifndef LODESTAR_SYMBOLICCODEGEN_HPP
#define LODESTAR_SYMBOLICCODEGEN_HPP

#ifdef LS_USE_GINAC

#include <ginac/ginac.h>

#endif

#include <ersatz/Codegen.hpp>

class SymbolicCodegen {
    static ers::Codegen &
    declareEigenMatrix(ers::Codegen &cg, unsigned int rows, unsigned int cols, const ::std::string &name,
                       const ::std::string &type = "double", bool isStatic = false);
};



#endif //LODESTAR_SYMBOLICCODEGEN_HPP
