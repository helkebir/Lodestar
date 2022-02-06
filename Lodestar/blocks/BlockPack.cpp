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

bool ls::blocks::BlockPack::hasDirectFeedthrough(ls::blocks::BlockProto &blk) const
{
    return hasDirectFeedthrough(&blk);
}

bool ls::blocks::BlockPack::isDriving(ls::blocks::BlockProto *blk1, ls::blocks::BlockProto *blk2) const
{
    if (contains(blk1) && contains(blk2))
        return graph.hasConnection(blk1->id, blk2->id);
    else
        return false;
}

bool ls::blocks::BlockPack::isDriving(ls::blocks::BlockProto &blk1, ls::blocks::BlockProto &blk2) const
{
    return isDriving(&blk1, &blk2);
}

std::shared_ptr <ls::blocks::BlockPack::BlockTraits>
ls::blocks::BlockPack::getTraitsByPtr(const ls::blocks::BlockProto *ptr) const
{
    if (traitsByPtr.find(ptr) != traitsByPtr.end())
        return traitsByPtr.at(ptr);

    return nullptr;
}

std::shared_ptr <ls::blocks::BlockPack::BlockTraits> ls::blocks::BlockPack::getTraitsById(unsigned int id) const
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

#ifdef LS_USE_GINAC

::std::shared_ptr<::std::vector < GiNaC::ex>>

ls::blocks::BlockPack::getInputSymbolsByPtr(const ls::blocks::BlockProto *ptr) const
{
    if (inputSymbolsByPtr.find(ptr) != inputSymbolsByPtr.end())
        return inputSymbolsByPtr.at(ptr);

    return nullptr;
}

::std::shared_ptr<::std::vector < GiNaC::ex>>

ls::blocks::BlockPack::getOutputSymbolsByPtr(const ls::blocks::BlockProto *ptr) const
{
    if (outputSymbolsByPtr.find(ptr) != outputSymbolsByPtr.end())
        return outputSymbolsByPtr.at(ptr);

    return nullptr;
}

::std::shared_ptr<::std::vector < GiNaC::ex>>

ls::blocks::BlockPack::getParameterSymbolsByPtr(const ls::blocks::BlockProto *ptr) const
{
    if (parameterSymbolsByPtr.find(ptr) != parameterSymbolsByPtr.end())
        return parameterSymbolsByPtr.at(ptr);

    return nullptr;
}

::std::shared_ptr<::std::vector < GiNaC::ex>>

ls::blocks::BlockPack::getInputSymbolsById(unsigned int id) const
{
    auto blk = getBlockById(id);

    if (blk == nullptr)
        return nullptr;

    return getInputSymbolsByPtr(blk);
}

::std::shared_ptr<::std::vector < GiNaC::ex>>

ls::blocks::BlockPack::getOutputSymbolsById(unsigned int id) const
{
    auto blk = getBlockById(id);

    if (blk == nullptr)
        return nullptr;

    return getOutputSymbolsByPtr(blk);
}

::std::shared_ptr<::std::vector < GiNaC::ex>>

ls::blocks::BlockPack::getParameterSymbolsById(unsigned int id) const
{
    auto blk = getBlockById(id);

    if (blk == nullptr)
        return nullptr;

    return getParameterSymbolsByPtr(blk);
}

::std::shared_ptr<::std::function<const GiNaC::function(const ::std::vector<GiNaC::ex> &exvec)>>
ls::blocks::BlockPack::getSymbolicFunctionByPtr(const ls::blocks::BlockProto *ptr) const
{
    if (symbolicFunctionByPtr.find(ptr) != symbolicFunctionByPtr.end())
        return symbolicFunctionByPtr.at(ptr);

    return nullptr;
}

::std::shared_ptr<::std::function<const GiNaC::function(const ::std::vector<GiNaC::ex> &exvec)>>
ls::blocks::BlockPack::getSymbolicFunctionById(unsigned int id) const
{
    auto blk = getBlockById(id);

    if (blk == nullptr)
        return nullptr;

    return getSymbolicFunctionByPtr(blk);
}

#endif