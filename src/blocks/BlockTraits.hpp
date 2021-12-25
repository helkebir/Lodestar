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

            static constexpr const BlockType blockType = BlockType::UnknownBlock;
            static constexpr const bool directFeedthrough = false;

            using type = TBlock;
            using Base = typename type::Base;

            static const constexpr int kIns = type::Base::kIns;
            static const constexpr int kOuts = type::Base::kOuts;
            static const constexpr int kPars = type::Base::kPars;
        };
    }
}


#endif //LODESTAR_BLOCKTRAITS_HPP
