//
// Created by Hamza El-Kebir on 2/10/22.
//

#ifndef LODESTAR_PROTOMESSAGETYPE_HPP
#define LODESTAR_PROTOMESSAGETYPE_HPP

#include <string>

namespace ls {
    namespace io {
        enum class ProtoMessageType {
            unknown_t,
            bool_t,
            int_t,
            double_t,
            float_t,
            char_t,
            EigenMatrix_t,
            EigenVector_t,
        };
    }
}

#define ADD_TYPE_TO_STRING(TYPE) case ls::io::ProtoMessageType::TYPE : return #TYPE;

namespace std {
    static ::std::string to_string(ls::io::ProtoMessageType type)
    {
        switch (type) {
            default:
                return "unknown_t";
            ADD_TYPE_TO_STRING(bool_t)
            ADD_TYPE_TO_STRING(int_t)
            ADD_TYPE_TO_STRING(double_t)
            ADD_TYPE_TO_STRING(float_t)
            ADD_TYPE_TO_STRING(char_t)
            ADD_TYPE_TO_STRING(EigenMatrix_t)
            ADD_TYPE_TO_STRING(EigenVector_t)
        }
    }
}

#endif //LODESTAR_PROTOMESSAGETYPE_HPP
