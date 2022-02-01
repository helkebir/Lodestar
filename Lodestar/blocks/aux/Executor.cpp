//
// Created by Hamza El-Kebir on 12/25/21.
//

#include "Executor.hpp"

void ls::blocks::aux::Executor::computeExecutionOrder()
{
    executionOrder = blockPack.blocks;

    ::std::sort(executionOrder.begin(),
                executionOrder.end(),
                [&](
                        BlockProto *a,
                        BlockProto *b) {
                    return order(a, b);
                });

    ::std::reverse(executionOrder.begin(),
                   executionOrder.end());
}

void ls::blocks::aux::Executor::applyExecutionOrder()
{
    int i = 0;
    for (auto &blk: executionOrder) {
        blk->setPriority(i);
        i++;
    }
}

// TODO: Closely reconsider ordering rules, i.e., do not rely
//  on reversing the final order.
bool ls::blocks::aux::Executor::order(ls::blocks::BlockProto *blk1, ls::blocks::BlockProto *blk2) const
{
    bool res = false;
    if (blockPack.isDriving(blk1, blk2)) {
        if (blockPack.hasDirectFeedthrough(blk2))
            res = true;
    }

    //                    if (blockPack.hasDirectFeedthrough(blk2)) {
    //                        if (blockPack.isDriving(blk1, blk2))
    //                            res = true;
    //                        else
    //                            res = false;
    //                    }

    //                    else if (blockPack.hasDirectFeedthrough(blk1)) {
    //                        if (blockPack.isDriving(blk2, blk1))
    //                            res = false;
    //                        else
    //                            res = true;
    //                    }

    return !res;
}

void ls::blocks::aux::Executor::trigger()
{
    for (auto blk: executionOrder)
        blk->trigger();
}
