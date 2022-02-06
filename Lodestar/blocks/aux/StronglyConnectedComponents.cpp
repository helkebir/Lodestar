//
// Created by Hamza El-Kebir on 12/25/21.
//

#include "StronglyConnectedComponents.hpp"

std::pair<
        ::std::vector<ls::blocks::aux::StronglyConnectedComponents::SCCResult::FullConnection>,
        ::std::vector<ls::blocks::aux::StronglyConnectedComponents::SCCResult::FullConnection>
>
ls::blocks::aux::StronglyConnectedComponents::SCCResult::getExternalIO(
        const ls::blocks::BlockPack &bp, int componentIdx) const
{
    static auto contains = [](const ::std::vector<int> &v, int val) -> bool {
        return (::std::find(v.begin(), v.end(), val) != v.end());
    };

    static auto containsBlock = [](
            const ::std::vector<::std::pair<const BlockProto *, int>> &v,
            ::std::pair<const BlockProto *, int> pair) -> bool {
        return (::std::find(v.begin(), v.end(), pair) != v.end());
    };

    ::std::vector<::std::pair<const BlockProto *, int>> externalInputs, externalOutputs;
    ::std::vector<FullConnection> externalInputConnections, externalOutputConnections;

    for (auto id: components[componentIdx]) {
        for (auto inputSlot: bp.getBlockById(id)->inputPointers)
            for (auto inputConnection: inputSlot->connectionPtrs)
                if (contains(components[0], inputConnection->blockId))
                    continue;
                else if (bp.getBlockById(inputConnection->blockId) != nullptr) {
                    ::std::pair<const BlockProto *, int> pair(
                            bp.getBlockById(inputConnection->blockId),
                            inputConnection->slotId);

                    if (!containsBlock(externalInputs, pair)) {
                        externalInputs.push_back(pair);
                        externalInputConnections.push_back(
                                {true,
                                 pair.first,
                                 pair.second,
                                 bp.getBlockById(inputSlot->blockId),
                                 inputSlot->slotId});
                    }
                } else
                    assert(bp.getBlockById(inputConnection->blockId) !=
                           nullptr &&
                           "Some blocks were not declared in the BlockPack");

        for (auto outputSlot: bp.getBlockById(id)->outputPointers)
            for (auto outputConnection: outputSlot->connectionPtrs)
                if (contains(components[componentIdx],
                             outputConnection->blockId))
                    continue;
                else if (bp.getBlockById(outputConnection->blockId) !=
                         nullptr) {
                    ::std::pair<const BlockProto *, int> pair(
                            bp.getBlockById(outputConnection->blockId),
                            outputConnection->slotId);

                    if (!containsBlock(externalOutputs, pair)) {
                        externalOutputs.push_back(pair);
                        externalOutputConnections.push_back(
                                {false,
                                 bp.getBlockById(outputSlot->blockId),
                                 outputSlot->slotId,
                                 pair.first,
                                 pair.second});
                    }
                } else
                    assert(bp.getBlockById(outputConnection->blockId) !=
                           nullptr &&
                           "Some blocks were not declared in the BlockPack");
    }

    return {externalInputConnections, externalOutputConnections};
}

::std::vector<ls::blocks::aux::StronglyConnectedComponents::SCCResult::FullConnection>
ls::blocks::aux::StronglyConnectedComponents::SCCResult::getInternalIO(
        const ls::blocks::BlockPack &bp, int componentIdx) const
{
    static auto contains = [](const ::std::vector<int> &v, int val) -> bool {
        return (::std::find(v.begin(), v.end(), val) != v.end());
    };

    static auto containsBlock = [](
            const ::std::vector<::std::pair<const BlockProto *, int>> &v,
            ::std::pair<const BlockProto *, int> pair) -> bool {
        return (::std::find(v.begin(), v.end(), pair) != v.end());
    };

    ::std::vector<::std::pair<const BlockProto *, int>> internalOutputs;
    ::std::vector<FullConnection> internalOutputConnections;

    for (auto id: components[componentIdx]) {
        for (auto outputSlot: bp.getBlockById(id)->outputPointers)
            for (auto outputConnection: outputSlot->connectionPtrs)
                if (contains(components[componentIdx],
                             outputConnection->blockId)) {
                    if (bp.getBlockById(outputConnection->blockId) !=
                        nullptr) {
                        ::std::pair<const BlockProto *, int> pair(
                                bp.getBlockById(outputConnection->blockId),
                                outputConnection->slotId);

                        if (!containsBlock(internalOutputs, pair)) {
                            internalOutputs.push_back(pair);
                            internalOutputConnections.push_back(
                                    {false,
                                     bp.getBlockById(outputSlot->blockId),
                                     outputSlot->slotId,
                                     pair.first,
                                     pair.second});
                        }
                    } else
                        assert(bp.getBlockById(outputConnection->blockId) !=
                               nullptr &&
                               "Some blocks were not declared in the BlockPack");
                }
    }

    return internalOutputConnections;
}

bool ls::blocks::aux::StronglyConnectedComponents::SCCResult::isSubset(int sup,
                                                                       int sub) const
{
    for (auto id: components[sub]) {
        if (::std::find(components[sup].begin(), components[sup].end(), id) ==
            components[sup].end())
            return false;
    }
    return true;

    //    return ::std::all_of(components[sub].begin(), components[sub].end(),
    //                         [&](int a) -> bool {
    //                             return ::std::any_of(components[sup].begin(),
    //                                                  components[sup].end(),
    //                                                  [=](int b) {
    //                                                      return a == b;
    //                                                  });
    //                         });
}

bool
ls::blocks::aux::StronglyConnectedComponents::SCCResult::intersects(int idx1,
                                                                    int idx2) const
{
    for (auto id: components[idx2]) {
        if (::std::find(components[idx1].begin(), components[idx1].end(), id) !=
            components[idx1].end())
            return true;
    }
    return false;

    //    return ::std::any_of(components[idx1].begin(), components[idx1].end(),
    //                         [&](int a) -> bool {
    //                             return ::std::any_of(components[idx2].begin(),
    //                                                  components[idx2].end(),
    //                                                  [&](int b) {
    //                                                      return a == b;
    //                                                  });
    //                         });
}

::std::vector<const ls::blocks::BlockProto *>
ls::blocks::aux::StronglyConnectedComponents::SCCResult::extractBlocks(
        const ::std::vector<FullConnection> &connections) const
{
    ::std::set<const BlockProto *> blks;
    for (auto &connection: connections) {
        blks.insert(connection.src);
        blks.insert(connection.dst);
    }

    std::vector<const BlockProto *> res;
    res.reserve(blks.size());

    for (auto blk: blks)
        res.push_back(blk);

    return res;
}

bool ls::blocks::aux::StronglyConnectedComponents::SCCResult::isAlgebraicLoop(const ls::blocks::BlockPack &bp,
                                                                              int componentIdx) const
{
//    for (auto id : components[componentIdx])
//        if (!bp.getTraitsById(id)->directFeedthrough)
//            return false;
//
//    return true;

    return ::std::all_of(components[componentIdx].begin(), components[componentIdx].end(),
                         [&](int id) -> bool { return bp.getTraitsById(id)->directFeedthrough; });
}

bool
ls::blocks::aux::StronglyConnectedComponents::SCCResult::containsAlgebraicLoops(const ls::blocks::BlockPack &bp) const
{
    for (int i = 0; i < components.size(); i++)
        if (isAlgebraicLoop(bp, i))
            return true;

    return false;
}

::std::size_t ls::blocks::aux::StronglyConnectedComponents::SCCResult::getComponentLength(int componentIdx) const
{
    return components[0].size();
}

#ifdef LS_USE_GINAC

GiNaC::lst
ls::blocks::aux::StronglyConnectedComponents::SCCResult::getSymbolicEquationList(const ls::blocks::BlockPack &bp,
                                                                                 int componentIdx) const
{
    GiNaC::lst l;

    auto internalIO = getInternalIO(bp, componentIdx);
    auto externalIO = getExternalIO(bp, componentIdx);

    auto interconnections = getInterconnectionEquationList(bp, componentIdx);
    auto blockEqs = getBlockEquationList(bp, componentIdx);

    for (auto &iconn: interconnections)
        l.append(iconn);

    for (auto &eq: blockEqs)
        l.append(eq);

    return l;
}

GiNaC::lst
ls::blocks::aux::StronglyConnectedComponents::SCCResult::getInterconnectionEquationList(const ls::blocks::BlockPack &bp,
                                                                                        int componentIdx) const
{
    auto internalIO = getInternalIO(bp, componentIdx);

    GiNaC::lst l;

    for (auto &iconn: internalIO)
        l.append((*bp.getInputSymbolsByPtr(iconn.dst))[iconn.dstSlot]
                 ==
                 (*bp.getOutputSymbolsByPtr(iconn.src))[iconn.srcSlot]);

    return l;
}

GiNaC::lst
ls::blocks::aux::StronglyConnectedComponents::SCCResult::getBlockEquationList(const ls::blocks::BlockPack &bp,
                                                                              int componentIdx) const
{
    GiNaC::lst l;

    for (auto id: components[componentIdx]) {
        int i = 0;
        auto f = (*bp.getSymbolicFunctionById(id))(*bp.getInputSymbolsById(id)).eval().evalm();

        for (auto &output: *bp.getOutputSymbolsById(id)) {
            if (GiNaC::is_a<GiNaC::lst>(f))
                l.append(output == f[i]);
            else
                l.append(output == f);

            i++;
        }
    }

    return l;
}

GiNaC::lst ls::blocks::aux::StronglyConnectedComponents::SCCResult::getKnownSymbolList(const ls::blocks::BlockPack &bp,
                                                                                       int componentIdx) const
{
    GiNaC::lst l;

    // All external inputs are known. We do not care about external outputs, since they can be computed from the loop's
    // internal unknowns.

    auto externalIO = getExternalIO(bp, componentIdx);

    for (auto &iconn: externalIO.first) {
        auto inputs = bp.getInputSymbolsByPtr(iconn.dst);
        auto iSymb = (*inputs)[iconn.dstSlot];
        if (GiNaC::is_a<GiNaC::symbol>(iSymb))
            l.append(iSymb);
        else if (GiNaC::is_a<GiNaC::lst>(iSymb))
            expandListToSymbols(GiNaC::ex_to<GiNaC::lst>(iSymb), l);
        else if (GiNaC::is_a<GiNaC::matrix>(iSymb))
            expandListToSymbols(GiNaC::ex_to<GiNaC::matrix>(iSymb), l);
    }

    // All internal parameters are known.

    auto internalIO = getInternalIO(bp, componentIdx);

    for (auto &iconn: internalIO) {
        for (const auto &pSymb: *bp.getParameterSymbolsByPtr(iconn.src)) {
            if (GiNaC::is_a<GiNaC::symbol>(pSymb))
                l.append(pSymb);
            else if (GiNaC::is_a<GiNaC::lst>(pSymb))
                expandListToSymbols(GiNaC::ex_to<GiNaC::lst>(pSymb), l);
            else if (GiNaC::is_a<GiNaC::matrix>(pSymb))
                expandListToSymbols(GiNaC::ex_to<GiNaC::matrix>(pSymb), l);
        }
    }

    return l;
}

GiNaC::lst
ls::blocks::aux::StronglyConnectedComponents::SCCResult::getUnknownSymbolList(const ls::blocks::BlockPack &bp,
                                                                              int componentIdx) const
{
    GiNaC::lst l;

    // All the loop's internal inputs and outputs are unknown.

    auto internalIO = getInternalIO(bp, componentIdx);

    for (auto &iconn: internalIO) {
        auto outputs = bp.getOutputSymbolsByPtr(iconn.src);
        auto oSymb = (*outputs)[iconn.srcSlot];
        if (GiNaC::is_a<GiNaC::symbol>(oSymb))
            l.append(oSymb);
        else if (GiNaC::is_a<GiNaC::lst>(oSymb))
            expandListToSymbols(GiNaC::ex_to<GiNaC::lst>(oSymb), l);
        else if (GiNaC::is_a<GiNaC::matrix>(oSymb))
            expandListToSymbols(GiNaC::ex_to<GiNaC::matrix>(oSymb), l);

        auto inputs = bp.getInputSymbolsByPtr(iconn.dst);
        auto iSymb = (*inputs)[iconn.dstSlot];
        if (GiNaC::is_a<GiNaC::symbol>(iSymb))
            l.append(iSymb);
        else if (GiNaC::is_a<GiNaC::lst>(iSymb))
            expandListToSymbols(GiNaC::ex_to<GiNaC::lst>(iSymb), l);
        else if (GiNaC::is_a<GiNaC::matrix>(iSymb))
            expandListToSymbols(GiNaC::ex_to<GiNaC::matrix>(iSymb), l);
    }

    return l;
}

::std::pair<GiNaC::lst, GiNaC::lst>
ls::blocks::aux::StronglyConnectedComponents::SCCResult::getAlgebraicEquations(const ls::blocks::BlockPack &bp,
                                                                               int componentIdx) const
{
    GiNaC::lst l, unknowns;

    auto eqs = getSymbolicEquationList(bp, componentIdx);
    auto allUnknowns = getUnknownSymbolList(bp, componentIdx);
    const auto N = getComponentLength(componentIdx);

    ::std::vector<GiNaC::ex> knowns;

    ::std::function<void(GiNaC::ex)> expandUnknown;
    expandUnknown = [&](GiNaC::ex unknown) {
        GiNaC::ex eq = unknown;

        for (int i = 0; i < N; i++)
            substituteExpressions(eq, eqs);

        knowns.push_back(unknown);
        if (!(eq - unknown).is_zero()) {
            l.append(eq - unknown);
            unknowns.append(unknown);
        }

        for (auto unknown2: allUnknowns) {
            if ((::std::find(knowns.begin(), knowns.end(), unknown2) == knowns.end()) &&
                eq.has(unknown2))
                expandUnknown(unknown2);
        }
    };

    expandUnknown(allUnknowns[0]);

    return {l, unknowns};
}

GiNaC::matrix
ls::blocks::aux::StronglyConnectedComponents::SCCResult::getAlgebraicEquationsJacobian(const GiNaC::lst &eqs,
                                                                                       const GiNaC::lst &vars)
{
    GiNaC::matrix jac(eqs.nops(), vars.nops());

    int i = 0;
    int j = 0;
    for (auto &eq: eqs) {
        j = 0;

        for (auto &var: vars) {
            jac(i, j) = eq.diff(GiNaC::ex_to<GiNaC::symbol>(var));

            j++;
        }

        i++;
    }

    return jac;
}

::std::pair<GiNaC::matrix, GiNaC::matrix>
ls::blocks::aux::StronglyConnectedComponents::SCCResult::solveAlgebraicEquationsNewtonRaphson(const GiNaC::lst &eqs,
                                                                                              const GiNaC::matrix &jac,
                                                                                              const GiNaC::lst &vars)
{
    GiNaC::matrix rhs(jac.rows(), 1), delta(jac.rows(), 1);

    int i = 0;

    for (auto &eq: eqs) {
        rhs(i, 0) = -eq;
        delta(i, 0) = GiNaC::symbol("d" + GiNaC::ex_to<GiNaC::symbol>(vars[i]).get_name(),
                                    "d" + GiNaC::ex_to<GiNaC::symbol>(vars[i]).get_TeX_name());

        i++;
    }

    return {jac.solve(delta, rhs), delta};
}

void ls::blocks::aux::StronglyConnectedComponents::SCCResult::expandListToSymbols(const GiNaC::lst &l, GiNaC::lst &g)
{
    for (auto &ex: l) {
        if (GiNaC::is_a<GiNaC::symbol>(ex)) {
            g.append(ex);
        } else if (GiNaC::is_a<GiNaC::lst>(ex)) {
            expandListToSymbols(GiNaC::ex_to<GiNaC::lst>(ex), g);
        } else if (GiNaC::is_a<GiNaC::matrix>(ex)) {
            expandListToSymbols(GiNaC::ex_to<GiNaC::matrix>(ex), g);
        }
    }
}

void ls::blocks::aux::StronglyConnectedComponents::SCCResult::expandListToSymbols(const GiNaC::matrix &l, GiNaC::lst &g)
{
    for (int i = 0; i < l.rows(); i++) {
        for (int j = 0; j < l.cols(); i++) {
            if (GiNaC::is_a<GiNaC::symbol>(l(i, j)))
                g.append(l(i, j));
            else if (GiNaC::is_a<GiNaC::lst>(l(i, j)))
                expandListToSymbols(GiNaC::ex_to<GiNaC::lst>(l(i, j)), g);
            else if (GiNaC::is_a<GiNaC::matrix>(l(i, j)))
                expandListToSymbols(GiNaC::ex_to<GiNaC::matrix>(l(i, j)), g);
        }
    }
}

void ls::blocks::aux::StronglyConnectedComponents::SCCResult::substituteExpressions(GiNaC::ex &ex, GiNaC::lst &subs)
{
    for (auto &rel: subs) {
        if (GiNaC::is_a<GiNaC::matrix>(rel.lhs())) {
            auto m = GiNaC::ex_to<GiNaC::matrix>(rel.lhs());

            for (int ii = 0; ii < m.rows(); ii++) {
                for (int jj = 0; jj < m.cols(); jj++) {
                    ex = ex.subs(m(ii, jj) == GiNaC::ex_to<GiNaC::matrix>(rel.rhs())(ii, jj));
                }
            }
        } else {
            ex = ex.subs(rel);
        }
    }
}


#endif

ls::blocks::aux::StronglyConnectedComponents::SCCResult
ls::blocks::aux::StronglyConnectedComponents::findComponents(
        const ls::blocks::aux::DirectedGraph &graph, bool allowSingletons)
{
    ::std::vector<int> disc, low;
    disc.reserve(graph.getSize());
    low.reserve(graph.getSize());

    ::std::stack<int> stack;
    ::std::vector<bool> stackItem;
    stackItem.reserve(graph.getSize());

    ::std::vector<::std::vector<int>> components;

    for (int i = 0; i < graph.getSize(); i++) {    //initialize all elements
        disc[i] = -1;
        low[i] = -1;
        stackItem[i] = false;
    }

    int time = 0;

    for (int i = 0; i < graph.getSize(); i++)    //initialize all elements
        if (disc[i] == -1)
            findComponentsImpl(graph, i, disc, low, stack,
                               stackItem, components, time,
                               allowSingletons);

    return {components};
}

void ls::blocks::aux::StronglyConnectedComponents::findComponentsImpl(
        const ls::blocks::aux::DirectedGraph &graph, int u,
        std::vector<int> &disc, std::vector<int> &low, std::stack<int> &stack,
        std::vector<bool> &stackItem,
        std::vector<::std::vector<int>> &components, int &time, bool allowSingletons)
{
    disc[u] = low[u] = ++time;    //initially discovery time and low value is 1
    stack.push(u);
    stackItem[u] = true;    //flag as u in the stack

    for (int v = 0; v < graph.getSize(); v++) {
        if (graph.hasConnection(u, v)) {
            if (disc[v] == -1) {   //when v is not visited
                findComponentsImpl(graph, v, disc, low, stack,
                                   stackItem, components, time,
                                   allowSingletons);
                low[u] = (low[u] < low[v] ? low[u] : low[v]);
            } else if (stackItem[v])    //when v is in the stack, update low for u
                low[u] = (low[u] < low[v] ? low[u] : disc[v]);
        }
    }

    int poppedItem = 0;
    if (low[u] == disc[u]) {
        ::std::vector<int> chain;

        while (stack.top() != u) {
            poppedItem = stack.top();
            chain.push_back(poppedItem);
            stackItem[poppedItem] = false;    //mark as item is popped
            stack.pop();
        }

        poppedItem = stack.top();
        chain.push_back(poppedItem);
        stackItem[poppedItem] = false;
        stack.pop();

        if (allowSingletons || (chain.size() > 1))
            components.push_back(chain);
    }
}
