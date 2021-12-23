//
// Created by Hamza El-Kebir on 12/22/21.
//

#ifndef LODESTAR_DYNAMICDATATYPES_HPP
#define LODESTAR_DYNAMICDATATYPES_HPP

#include <string>

namespace ls {
    namespace aux {
        /**
         * Utility struct defining dynamic data types.
         */
        struct DynamicDataTypes {
            enum class Types {
                intType,
                boolType,
                floatType,
                doubleType,
                longType,
                charType,
                stringType,
                unknownType
            };

            template<typename TType>
            struct type_to_enum {
                static constexpr Types type = Types::unknownType;
                static_assert(type == Types::unknownType,
                              "Unknown dynamic type; please define a suitable DynamicDataType.");
            };
        };
    }
}

#endif //LODESTAR_DYNAMICDATATYPES_HPP
