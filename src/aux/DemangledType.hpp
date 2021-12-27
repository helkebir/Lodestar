//
// Created by Hamza El-Kebir on 12/26/21.
//

#ifndef LODESTAR_DEMANGLEDTYPE_HPP
#define LODESTAR_DEMANGLEDTYPE_HPP


#include <string>
#include <typeinfo>

// https://stackoverflow.com/a/4541470

std::string demangle(const char *name);

template<class T>
std::string type(const T &t)
{
    return demangle(typeid(t).name());
}


#endif //LODESTAR_DEMANGLEDTYPE_HPP
