//
// Created by Hamza El-Kebir on 12/25/21.
//

#ifndef LODESTAR_BLOCKTRAITS_HPP
#define LODESTAR_BLOCKTRAITS_HPP

#include "BlockType.hpp"
#include "BlockProto.hpp"
#include "Lodestar/aux/DemangledType.hpp"
#include <type_traits>
#include <string>
#include <array>

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
        template<typename TBlock = void>
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

            static const ::std::array<::std::string, kIns> inTypes;
            static const ::std::array<::std::string, kOuts> outTypes;
            static const ::std::array<::std::string, kPars> parTypes;

            static const ::std::array<::std::string, 1> templateTypes;
        };



        template<>
        class BlockTraits<void> {
        public:
            template<typename TType, typename ::std::enable_if<::std::is_base_of<BlockProto, typename ::std::decay<TType>::type>::value>::type* = nullptr>
            static auto get(const TType &blk) -> BlockTraits<typename ::std::decay<TType>::type>
            {
                return BlockTraits<typename ::std::decay<TType>::type>{};
            }

            template<typename TType, typename ::std::enable_if<!::std::is_base_of<BlockProto, typename ::std::decay<TType>::type>::value>::type* = nullptr>
            static auto get(const TType &blk) -> BlockTraits<typename ::std::decay<TType>::type>
            {
                static_assert(
                        ::std::is_base_of<BlockProto, typename ::std::decay<TType>::type>::value,
                        "All elements in BlockPack must be derived from BlockProto."
                );
            }
        };
    }
}


#endif //LODESTAR_BLOCKTRAITS_HPP
