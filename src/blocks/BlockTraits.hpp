//
// Created by Hamza El-Kebir on 12/25/21.
//

#ifndef LODESTAR_BLOCKTRAITS_HPP
#define LODESTAR_BLOCKTRAITS_HPP

#include "BlockType.hpp"
#include <type_traits>

namespace ls {
    namespace blocks {
        template<typename TBlock>
        class BlockTraits {
            static_assert(!::std::is_same<TBlock, TBlock>::value,
                          "BlockTraits is not defined for this type.");
        };
    }
}


#endif //LODESTAR_BLOCKTRAITS_HPP
