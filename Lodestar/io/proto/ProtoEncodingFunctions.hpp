//
// Created by Hamza El-Kebir on 2/10/22.
//

#ifndef LODESTAR_PROTOENCODINGFUNCTIONS_HPP
#define LODESTAR_PROTOENCODINGFUNCTIONS_HPP

#include <pb_encode.h>

namespace ls {
    namespace io {
        bool encode(pb_ostream_t *stream, const pb_field_t *field, void * const *arg)
        {


            return true;
        }
    }
}

#endif //LODESTAR_PROTOENCODINGFUNCTIONS_HPP
