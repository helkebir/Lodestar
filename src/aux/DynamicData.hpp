//
// Created by Hamza El-Kebir on 12/22/21.
//

#ifndef LODESTAR_DYNAMICDATA_HPP
#define LODESTAR_DYNAMICDATA_HPP

#include "DynamicDataTypes.hpp"
#include "Any.hpp"

namespace ls {
    namespace aux {
        struct DynamicData {
            Any<int, bool, float, double, long, char, std::string> data;

            template <typename TType>
            DynamicData &operator=(const TType &x)
            {
                data.template operator=(x);
                return *this;
            }
        };

        static std::ostream& operator<<(std::ostream& os, const DynamicData dd)
        {
            switch (dd.data.tag()) {
                default: break;
                case DynamicDataTypes::Types::intType:
                    os << dd.data.as<int>();
                    break;
                case DynamicDataTypes::Types::boolType:
                    os << dd.data.as<bool>();
                    break;
                case DynamicDataTypes::Types::floatType:
                    os << dd.data.as<float>();
                    break;
                case DynamicDataTypes::Types::doubleType:
                    os << dd.data.as<double>();
                    break;
                case DynamicDataTypes::Types::longType:
                    os << dd.data.as<long>();
                    break;
                case DynamicDataTypes::Types::stringType:
                    os << dd.data.as<std::string>();
                    break;
            }

            return os;
        }
    }
}

#endif //LODESTAR_DYNAMICDATA_HPP
