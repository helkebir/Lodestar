//
// Created by Hamza El-Kebir on 12/25/21.
//

#include "Executor.hpp"

// TODO: Closely reconsider ordering rules, i.e., do not rely
//  on reversing the final order.
bool ls::blocks::aux::Executor::order(ls::blocks::BlockProto *blk1,
                                      ls::blocks::BlockProto *blk2) const
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

void
ls::blocks::aux::Executor::makeDotFile(std::stringstream &ss, bool lineLabels,
                                       bool slotLabels, float rankSep,
                                       float nodeSep)
{
    ss << "digraph R {\n";
    ss << "  rankdir=LR;\n";
    ss << "  overlap=false;\n";
    ss << fmt::format("  ranksep={:.2f};\n", rankSep);
    ss << fmt::format("  nodesep={:.2f};\n", nodeSep);
    ss << "  edge [colorscheme=spectral11];\n";
    ss << "\n";

    ::std::vector<int> algebraicLoops;
    algebraicLoops.reserve(components.components.size());
    for (int idx = 0; idx < components.components.size(); idx++)
        if (components.isAlgebraicLoop(blockPack, idx))
            algebraicLoops.push_back(idx);

    auto getAlgebraicLoopsColors = [&](int blockId) -> ::std::string {
        ::std::string res;
        int iComponents = 1;
        for (int i: algebraicLoops) {
            if (::std::any_of(components.components[i].begin(),
                              components.components[i].end(),
                              [blockId](int id) {
                                  return (id == blockId);
                              })) {
                if (iComponents > 1)
                    res += fmt::format(":{}", iComponents);
                else
                    res = ::std::to_string(iComponents);

                iComponents++;
            }
        }

        return res;
    };

    auto getSharedAlgebraicLoopsColors = [&](int blockId1,
                                             int blockId2) -> ::std::string {
        ::std::string res;
        int iComponents = 1;
        for (int i: algebraicLoops) {
            if (::std::any_of(components.components[i].begin(),
                              components.components[i].end(),
                              [blockId1](int id) {
                                  return (id == blockId1);
                              }) &&
                ::std::any_of(components.components[i].begin(),
                              components.components[i].end(),
                              [blockId2](int id) {
                                  return (id == blockId2);
                              })) {
                if (iComponents > 1)
                    res += fmt::format(":{}", iComponents);
                else
                    res = ::std::to_string(iComponents);

                iComponents++;
            }
        }

        return res;
    };

    for (const auto blk: executionOrder) {
        const auto traits = blockPack.getTraitsByPtr(blk);
        ss << "  ";
        ss << fmt::format("blk{} ", blk->id);
        ss << fmt::format(R"([shape=record, xlabel="{}", label=")",
                          blockTypeToString(traits->blockType));
        ::std::stringstream label;
        label << "{ ";

        int i = 0;
        if (!traits->inTypes.empty()) {
            label << "{ ";
            for (auto in: traits->inTypes) {
                if (i > 0)
                    label << " | ";

                replace(in, "<", "\\<");
                replace(in, ">", "\\>");

                if (slotLabels)
                    label << fmt::format("<i{0}> Inp{0} \\n {1}", i, in);
                else
                    label << fmt::format("<i{0}> Inp{0}", i);

                i++;
            }
            label << " } | ";
        }

        label << "{ ";

        i = 0;
        if (!traits->parTypes.empty()) {
            label << "{ ";
            for (auto par: traits->parTypes) {
                if (i > 0)
                    label << " | ";

                replace(par, "<", "\\<");
                replace(par, ">", "\\>");

                if (slotLabels)
                    label << fmt::format("<p{0}> Par{0} \\n {1}", i, par);
                else
                    label << fmt::format("<p{0}> Par{0}", i);

                i++;
            }
            label << " } | ";
        }

        label << fmt::format("#{}{}", blk->id,
                             traits->directFeedthrough ? "\\n dir. fd-thru"
                                                       : "");
        label << " } ";

        i = 0;
        if (!traits->outTypes.empty()) {
            label << "| { ";
            for (auto out: traits->outTypes) {
                if (i > 0)
                    label << " | ";

                replace(out, "<", "\\<");
                replace(out, ">", "\\>");

                if (slotLabels)
                    label << fmt::format("<o{0}> Out{0} \\n {1}", i, out);
                else
                    label << fmt::format("<o{0}> Out{0}", i);

                i++;
            }
            label << " }";
        }

        label << " }\"];";
        ss << label.str();
        ss << "\n";
    }

    ss << "\n";

    for (const auto blk: executionOrder) {
        const auto traits = blockPack.getTraitsByPtr(blk);

        int i = 0;
        for (const auto oSlot: blk->outputPointers) {
            for (const auto iSlotOther: oSlot->connectionPtrs) {
                ::std::string colors = getSharedAlgebraicLoopsColors(oSlot->blockId, iSlotOther->blockId);
                ss << fmt::format(
                        "  blk{}:o{}:e -> blk{}:i{}:w [label=\"<{}>\"{}];\n",
                        oSlot->blockId, oSlot->slotId,
                        iSlotOther->blockId,
                        iSlotOther->slotId,
                        lineLabels ? traits->outTypes[i] : "",
                        colors.empty() ? "" : ", color=\"" + colors + "\""
                        );
            }
            i++;
        }
    }

    ss << "}";
}

//void ls::blocks::aux::Executor::trigger()
//{
//    for (auto blk: executionOrder)
//        blk->trigger();
//}
