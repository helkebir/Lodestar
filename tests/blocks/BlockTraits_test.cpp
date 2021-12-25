//
// Created by Hamza El-Kebir on 12/25/21.
//

#include "catchOnce.hpp"
#include "blocks/std/ConstantBlock.hpp"

TEST_CASE("BlockTraits", "[blocks]")
{
    typedef ls::blocks::BlockTraits<ls::blocks::std::ConstantBlock<double>> TDTraitsConstant;

    /* This is a weird Catch2 quirk; linking error when the r-value is put in
     * the REQUIRE statement.
     */
    bool a = (TDTraitsConstant::blockType == ls::blocks::BlockType::ConstantBlock);
    bool b = (TDTraitsConstant::kIns == 0);
    bool c = (TDTraitsConstant::kOuts == 1);
    bool d = (TDTraitsConstant::kPars == 1);
    bool e = TDTraitsConstant::directFeedthrough;

    REQUIRE(a);
    REQUIRE(b);
    REQUIRE(c);
    REQUIRE(d);
    REQUIRE(e);
}