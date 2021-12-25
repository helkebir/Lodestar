//
// Created by Hamza El-Kebir on 12/25/21.
//

#ifndef LODESTAR_BLOCKTYPE_HPP
#define LODESTAR_BLOCKTYPE_HPP

namespace ls {
    namespace blocks {
        enum class BlockType {
            UnknownBlock,
            GenericBlock,
            ConstantBlock,
            ConverterBlock,
            DemuxBlock,
            FunctionBlock,
            GainBlock,
            MuxBlock,
            ReImToComplexBlock,
            SaturationBlock,
            SignumBlock,
            SumBlock,
            SwitchBlock
        };
    }
}

#endif //LODESTAR_BLOCKTYPE_HPP
