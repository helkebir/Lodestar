//
// Created by Hamza El-Kebir on 12/25/21.
//

#ifndef LODESTAR_BLOCKTYPE_HPP
#define LODESTAR_BLOCKTYPE_HPP

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
            /// Function block.
            FunctionBlock,
            /// Gain block.
            GainBlock,
            /// Multiplexer block.
            MuxBlock,
            /// Real and imaginary to complex block.
            ReImToComplexBlock,
            /// Saturation block.
            SaturationBlock,
            /// Signum block.
            SignumBlock,
            /// Summation block.
            SumBlock,
            /// Switch (manual) block.
            SwitchBlock
        };
    }
}

#endif //LODESTAR_BLOCKTYPE_HPP
