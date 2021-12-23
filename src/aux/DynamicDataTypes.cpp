//
// Created by Hamza El-Kebir on 12/23/21.
//

#include "DynamicDataTypes.hpp"

namespace ls {
    namespace aux {
        template<>
        struct DynamicDataTypes::type_to_enum<int> {
            static constexpr Types type = Types::intType;
        };

        template<>
        struct DynamicDataTypes::type_to_enum<bool> {
            static constexpr Types type = Types::boolType;
        };

        template<>
        struct DynamicDataTypes::type_to_enum<float> {
            static constexpr Types type = Types::floatType;
        };

        template<>
        struct DynamicDataTypes::type_to_enum<double> {
            static constexpr Types type = Types::doubleType;
        };

        template<>
        struct DynamicDataTypes::type_to_enum<long> {
            static constexpr Types type = Types::longType;
        };

        template<>
        struct DynamicDataTypes::type_to_enum<std::string> {
            static constexpr Types type = Types::stringType;
        };

        template<>
        struct DynamicDataTypes::type_to_enum<char> {
            static constexpr Types type = Types::charType;
        };
    }
}