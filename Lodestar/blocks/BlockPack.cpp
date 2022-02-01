//
// Created by Hamza El-Kebir on 12/25/21.
//

#include "BlockPack.hpp"

void ls::blocks::BlockPack::makeGraph()
{
    graph = ls::blocks::aux::DirectedGraph::fromBlocks(blocks);
}

bool ls::blocks::BlockPack::contains(ls::blocks::BlockProto *blk) const
{
    return (traitsByPtr.find(blk) != traitsByPtr.end());
}

bool ls::blocks::BlockPack::contains(unsigned int idx) const
{
    return (blockById.find(idx) != blockById.end());
}

bool ls::blocks::BlockPack::hasDirectFeedthrough(ls::blocks::BlockProto *blk) const
{
    if (contains(blk))
        return traitsByPtr.at(blk)->directFeedthrough;
    else
        return false;
}

bool ls::blocks::BlockPack::isDriving(ls::blocks::BlockProto *blk1, ls::blocks::BlockProto *blk2) const
{
    if (contains(blk1) && contains(blk2))
        return graph.hasConnection(blk1->id, blk2->id);
    else
        return false;
}

std::shared_ptr<ls::blocks::BlockPack::BlockTraits> ls::blocks::BlockPack::getTraitsByPtr(ls::blocks::BlockProto *ptr)
{
    if (traitsByPtr.find(ptr) != traitsByPtr.end())
        return traitsByPtr[ptr];

    return nullptr;
}

std::shared_ptr<ls::blocks::BlockPack::BlockTraits> ls::blocks::BlockPack::getTraitsById(unsigned int id)
{
    auto blk = getBlockById(id);

    if (blk == nullptr)
        return nullptr;

    return getTraitsByPtr(blk);
}

ls::blocks::BlockProto *ls::blocks::BlockPack::getBlockById(unsigned int id)
{
    if (blockById.find(id) != blockById.end())
        return blockById[id];

    return nullptr;
}

const ls::blocks::BlockProto *ls::blocks::BlockPack::getBlockById(unsigned int id) const
{
    if (blockById.find(id) != blockById.end())
        return blockById.at(id);

    return nullptr;
}