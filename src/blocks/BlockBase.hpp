//
// Created by Hamza El-Kebir on 12/22/21.
//

#ifndef LODESTAR_BLOCKBASE_HPP
#define LODESTAR_BLOCKBASE_HPP

#include "BlockProto.hpp"

namespace ls {
    namespace blocks {
        template <typename TChild>
        class BlockBase : public BlockProto {
        public:
            using BlockProto::empty;

            BlockBase() = default;

            void trigger() override
            {
                return static_cast<TChild*>(this)->trigger();
            }
        };
    }
}

#endif //LODESTAR_BLOCKBASE_HPP
