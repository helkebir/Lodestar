//
// Created by Hamza El-Kebir on 12/25/21.
//

#ifndef LODESTAR_BLOCKTRAITS_HPP
#define LODESTAR_BLOCKTRAITS_HPP

#include "BlockType.hpp"
#include <type_traits>

namespace ls {
    namespace blocks {
        /**
         * @brief A traits object that exposes information about @c TBlock.
         * @ingroup blocks_module
         *
         * @details All Blocks will have a partial specialization of this class
         * that exposes the following:
         *
         * - Direct feedthrough
         * - BlockType
         * - Base type
         * - Number of input slots
         * - Number of output slots
         * - Number of parameters
         *
         * @note Any custom block class must present a partial specialization
         * to BlockTraits.
         *
         * @tparam TBlock Block type.
         */
        template<typename TBlock>
        class BlockTraits {
            static_assert(!::std::is_same<TBlock, TBlock>::value,
                          "BlockTraits is not defined for this type.");
        public:
            /// Block type.
            static constexpr const BlockType blockType = BlockType::UnknownBlock;
            /// Whether or not the block has direct feedthrough.
            static constexpr const bool directFeedthrough = false;

            /// Current class.
            using type = TBlock;
            /// Base Block class.
            using Base = typename type::Base;

            /// Number of input slots
            static const constexpr int kIns = type::Base::kIns;
            /// Number of output slots.
            static const constexpr int kOuts = type::Base::kOuts;
            /// Number of parameters.
            static const constexpr int kPars = type::Base::kPars;
        };
    }
}


#endif //LODESTAR_BLOCKTRAITS_HPP
