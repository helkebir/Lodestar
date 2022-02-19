//
// Created by Hamza El-Kebir on 12/25/21.
//

#ifndef LODESTAR_BLOCKTYPE_HPP
#define LODESTAR_BLOCKTYPE_HPP

#define ADD_BLOCKTYPE_CASE(TYPE) case BlockType::TYPE: return #TYPE

#include <string>

namespace ls {
    namespace blocks {
        /**
         * @enum ls::blocks::BlockType
         * @ingroup blocks_module
         * @brief Block type information.
         *
         * @details This enum class servers to aid in runtime identification of
         * block types.
         *
         * @note Any future blocks should aim to declare their own BlockType,
         * otherwise they should be labeled as UnknownBlock.
         */
        enum class BlockType {
            /// Unknown block.
            UnknownBlock,
            /// Generic block (for debug purposes).
            GenericBlock,
            /// Constant block.
            ConstantBlock,
            /// Converter block.
            ConverterBlock,
            /// Demultiplexer block.
            DemuxBlock,
            /// Discrete state-space block.
            DiscreteStateSpaceBlock,
            /// Function block.
            FunctionBlock,
            /// Gain block.
            GainBlock,
            /// Min/max block.
            MinMaxBlock,
            /// Min/max index block.
            MinMaxIdxBlock,
            /// Multiplexer block.
            MuxBlock,
            /// Protocol Buffers output block.
            ProtoMsgOutBlock,
            /// Real and imaginary to complex block.
            ReImToComplexBlock,
            /// Saturation block.
            SaturationBlock,
            /// Signum block.
            SignumBlock,
            /// Summation block.
            SumBlock,
            /// Switch (manual) block.
            SwitchBlock,
            /// Unary absolute value block.
            UnaryAbsBlock,
        };

        static
        ::std::string blockTypeToString(const BlockType type)
        {
            switch (type) {
                default:
                    return "UnknownBlock";
                ADD_BLOCKTYPE_CASE(GenericBlock);
                ADD_BLOCKTYPE_CASE(ConstantBlock);
                ADD_BLOCKTYPE_CASE(ConverterBlock);
                ADD_BLOCKTYPE_CASE(DemuxBlock);
                ADD_BLOCKTYPE_CASE(DiscreteStateSpaceBlock);
                ADD_BLOCKTYPE_CASE(FunctionBlock);
                ADD_BLOCKTYPE_CASE(GainBlock);
                ADD_BLOCKTYPE_CASE(MuxBlock);
                ADD_BLOCKTYPE_CASE(ReImToComplexBlock);
                ADD_BLOCKTYPE_CASE(SaturationBlock);
                ADD_BLOCKTYPE_CASE(SignumBlock);
                ADD_BLOCKTYPE_CASE(SumBlock);
                ADD_BLOCKTYPE_CASE(SwitchBlock);
                ADD_BLOCKTYPE_CASE(ProtoMsgOutBlock);
            }

            return "UnknownBlock";
        }
    }
}

#endif //LODESTAR_BLOCKTYPE_HPP
