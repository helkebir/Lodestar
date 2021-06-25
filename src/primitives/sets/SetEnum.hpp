//
// Created by Hamza El-Kebir on 6/21/21.
//

#ifndef LODESTAR_SETENUM_HPP
#define LODESTAR_SETENUM_HPP

namespace ls {
    namespace primitives {
        namespace sets {
            /**
             * @brief An enumeration of Abstract Syntax Tree components for set operations.
             */
            enum class SetEnum {
                Unknown = 0,
                Singleton,
                Union,
                Complement
            };
        }
    }
}

#endif //LODESTAR_SETENUM_HPP
