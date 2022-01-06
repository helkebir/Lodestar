//
// Created by Hamza El-Kebir on 12/26/21.
//

#include "DemangledType.hpp"

#ifdef __GNUG__

#include <cstdlib>
#include <memory>
#include <cxxabi.h>

std::string demangle(const char *name)
{
    static int status = -1;

    std::unique_ptr<char, void (*)(void *)> res{
            abi::__cxa_demangle(name, nullptr, nullptr, &status),
            std::free
    };

    return (status == 0) ? res.get() : name;
}

#else

std::string demangle(const char* name) {
    return name;
}

#endif