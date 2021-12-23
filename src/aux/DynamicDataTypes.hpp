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
                stringType
            };

            template<typename TType>
            struct type_to_enum {
                //        static_assert(false, "Unknown dynamic type.");
            };

            template<>
            struct type_to_enum<int> {
                static constexpr Types type = Types::intType;
            };

            template<>
            struct type_to_enum<bool> {
                static constexpr Types type = Types::boolType;
            };

            template<>
            struct type_to_enum<float> {
                static constexpr Types type = Types::floatType;
            };

            template<>
            struct type_to_enum<double> {
                static constexpr Types type = Types::doubleType;
            };

            template<>
            struct type_to_enum<long> {
                static constexpr Types type = Types::longType;
            };

            template<>
            struct type_to_enum<std::string> {
                static constexpr Types type = Types::stringType;
            };

            template<>
            struct type_to_enum<char> {
                static constexpr Types type = Types::charType;
            };
        };
    }
}

#endif //LODESTAR_DYNAMICDATATYPES_HPP
