//
// Created by Hamza El-Kebir on 4/18/21.
//

#ifndef LODESTAR_LODESTARERRORNAMES_HPP
#define LODESTAR_LODESTARERRORNAMES_HPP

#include "LodestarErrors.hpp"
#include <string>

std::string LODESTAR_ERROR_NAME(LODESTAR_ERROR err) {
    switch (err) {
        case ERROR_NONE:
            return "ERROR_NONE";
        case ERROR_IMPROPER_TRANSFER_FUNC:
            return "ERROR_IMPROPER_TRANSFER_FUNC";
    }
}

#endif //LODESTAR_LODESTARERRORNAMES_HPP
