//
// Created by Hamza El-Kebir on 12/25/21.
//

#include "catchOnce.hpp"
#include "Lodestar/blocks/std/ConstantBlock.hpp"
#include "Lodestar/blocks/std/SumBlock.hpp"

TEST_CASE("BlockTraits", "[blocks]")
{
    typedef ls::blocks::BlockTraits<ls::blocks::std::ConstantBlock<double>> TDTraitsConstant;
    typedef ls::blocks::BlockTraits<ls::blocks::std::SumBlock<double, 7>> TDTraitsSum7;

    /* This is a weird Catch2 quirk; linking error when the r-value is put in
     * the REQUIRE statement.
     */
    bool a = (TDTraitsConstant::blockType == ls::blocks::BlockType::ConstantBlock);
    bool b = (TDTraitsConstant::kIns == 0);
    bool c = (TDTraitsConstant::kOuts == 1);
    bool d = (TDTraitsConstant::kPars == 1);
    bool e = TDTraitsConstant::directFeedthrough;

    bool f = (TDTraitsSum7::inTypes[0] == "double");
    bool g = (TDTraitsSum7::inTypes[TDTraitsSum7::kIns-1] == "double");
    bool h = (TDTraitsSum7::templateTypes[0] == "double");
    bool i = (TDTraitsSum7::templateTypes[1] == "unsigned int");
    bool j = (TDTraitsSum7::outTypes[0] == "double");

    REQUIRE(a);
    REQUIRE(b);
    REQUIRE(c);
    REQUIRE(d);
    REQUIRE(e);

    REQUIRE(f);
    REQUIRE(g);
    REQUIRE(h);
    REQUIRE(i);
    REQUIRE(j);
}