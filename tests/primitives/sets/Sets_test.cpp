//
// Created by Hamza El-Kebir on 6/21/21.
//

#include "catchOnce.hpp"
#include "primitives/sets/SetExpression.hpp"
#include "primitives/sets/SetUnion.hpp"
#include "primitives/sets/Singleton.hpp"
#include "primitives/sets/EmptySet.hpp"

#include <iostream>

TEST_CASE("Sets", "[primitives][sets]")
{
    Eigen::Vector2d sval, sval2, sval3;
    sval << 1, 2;
    sval2 << 2, 2;
    sval3 << 3, 1;
    ls::primitives::sets::Singleton<2> s(sval), s2(sval2), s3(sval3);

    REQUIRE(s.contains(s));
    REQUIRE(!s.contains(s2));
    REQUIRE(s2.contains(s2));

    REQUIRE(s == s);
    REQUIRE(s2 == s2);
    REQUIRE(s != s2);

    auto sUnion2 = s.unionize(s2);

    REQUIRE(sUnion2.getEnum() == ls::primitives::sets::SetEnum::Union);
    REQUIRE((sUnion2.contains(s) && sUnion2.contains(s2)));

    auto sUnion3 = sUnion2.unionize(s3);
    REQUIRE(sUnion3.getEnum() == ls::primitives::sets::SetEnum::Union);
    REQUIRE((sUnion3.contains(s) && sUnion3.contains(s2) && sUnion3.contains(s3)));

    auto emptySet = ls::primitives::sets::EmptySet{};
    auto emptySet2 = ls::primitives::sets::EmptySet{};

    REQUIRE(emptySet == emptySet2);
    REQUIRE(!(emptySet != emptySet2));
    REQUIRE(emptySet.unionize(emptySet2).isEmpty());
    REQUIRE(emptySet.relComplement(emptySet2).isEmpty());

    auto relComplement = s.relComplement(s);
    REQUIRE(!relComplement.contains(s));
    REQUIRE(relComplement.isEmpty());
    REQUIRE(emptySet.relComplement(emptySet2).getLeft() == emptySet);
    REQUIRE(emptySet.relComplement(emptySet2).getLeft() == relComplement);
//    REQUIRE(relComplement == relComplement);

    REQUIRE(!sUnion3.contains(emptySet));

    auto sUnion4 = sUnion3.unionize(ls::primitives::sets::EmptySet{});
    REQUIRE(sUnion4.contains(emptySet));

    REQUIRE(emptySet.isSubset(sUnion4));

    REQUIRE(emptySet.isSubset(emptySet));
    REQUIRE(emptySet.isSuperset(emptySet));

//    std::cout << "s.sdf(sval2) " << s.sdf(sval2) << std::endl;
//    std::cout << "s.sdf(sval3) " << s.sdf(sval3) << std::endl;
//    std::cout << "emptySet.sdf(sval3) " << emptySet.sdf(sval3) << std::endl;
//    std::cout << "sUnion2.sdf(sval3) " << sUnion2.sdf(sval3) << std::endl;
//    std::cout << "sUnion3.sdf(sval3) " << sUnion3.sdf(sval3) << std::endl;
//    std::cout << "relComplement.sdf(sval3) " << relComplement.sdf(sval3) << std::endl;

//    std::cout << "sUnion3 contains sUnion2? " << (sUnion3.contains(sUnion2))
}