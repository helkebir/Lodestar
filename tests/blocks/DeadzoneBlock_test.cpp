//
// Created by Hamza El-Kebir on 2/19/22.
//

#include "catchOnce.hpp"
#include "Lodestar/blocks/std/DeadzoneBlock.hpp"


TEST_CASE("DeadzoneBlock", "[blocks][std]")
{
    SECTION("Parametric input") {
        ls::blocks::std::DeadzoneBlock<double> dzb;

        dzb.lower() = -1;
        dzb.upper() = 1;

        dzb.i<0>() = 3;
        dzb.trigger();

        REQUIRE(dzb.o<0>().object == Approx(3));

        dzb.i<0>() = 0.5;
        dzb.trigger();

        REQUIRE(dzb.o<0>().object == 0);
    }

    SECTION("Additional input") {
        ls::blocks::std::DeadzoneBlock<double, ls::blocks::std::DeadzoneBlockOperator::Scalar, ls::blocks::std::DeadzoneBlockParameter::AdditionalInput> dzb;

        dzb.lower() = -1;
        dzb.upper() = 1;

        dzb.i<0>() = 3;
        dzb.trigger();

        REQUIRE(dzb.o<0>().object == Approx(3));

        dzb.i<0>() = 0.5;
        dzb.trigger();

        REQUIRE(dzb.o<0>().object == 0);
    }

    SECTION("Scalar and parametric input") {
        ls::blocks::std::DeadzoneBlock<Eigen::Vector2d> dzb;

        Eigen::Vector2d v;
        v << -3, 2;

        dzb.lower() = -1;
        dzb.upper() = 1;

        dzb.i<0>() = v;
        dzb.trigger();

        REQUIRE(dzb.o<0>().object(0) == Approx(-3));
        REQUIRE(dzb.o<0>().object(1) == Approx(2));

        v << 0.5, 2;
        dzb.i<0>() = v;
        dzb.trigger();

        REQUIRE(dzb.o<0>().object(0) == Approx(0));
        REQUIRE(dzb.o<0>().object(1) == Approx(2));
    }

    SECTION("Scalar and additional input") {
        ls::blocks::std::DeadzoneBlock<Eigen::Vector2d, ls::blocks::std::DeadzoneBlockOperator::Scalar, ls::blocks::std::DeadzoneBlockParameter::AdditionalInput> dzb;

        Eigen::Vector2d v;
        v << -3, 2;

        dzb.lower() = -1;
        dzb.upper() = 1;

        dzb.i<0>() = v;
        dzb.trigger();

        REQUIRE(dzb.o<0>().object(0) == Approx(-3));
        REQUIRE(dzb.o<0>().object(1) == Approx(2));

        v << 0.5, 2;
        dzb.i<0>() = v;
        dzb.trigger();

        REQUIRE(dzb.o<0>().object(0) == Approx(0));
        REQUIRE(dzb.o<0>().object(1) == Approx(2));
    }

    SECTION("Elementwise and parametric input") {
        ls::blocks::std::DeadzoneBlock<Eigen::Vector4d, ls::blocks::std::DeadzoneBlockOperator::Elementwise> dzb;

        Eigen::Vector4d v, vl, vu;
        v << -4, 2, -6, 6;
        vl << -1, 0, 0, 2;
        vu << 2, 3, 4, 5;

        dzb.lower() = vl;
        dzb.upper() = vu;

        dzb.i<0>() = v;
        dzb.trigger();

        REQUIRE(dzb.o<0>().object(0) == Approx(-4));
        REQUIRE(dzb.o<0>().object(1) == Approx(0));
        REQUIRE(dzb.o<0>().object(2) == Approx(-6));
        REQUIRE(dzb.o<0>().object(3) == Approx(6));

        v << 0, 1, -7, 6;
        dzb.i<0>() = v;
        dzb.trigger();

        REQUIRE(dzb.o<0>().object(0) == Approx(0));
        REQUIRE(dzb.o<0>().object(1) == Approx(0));
        REQUIRE(dzb.o<0>().object(2) == Approx(-7));
        REQUIRE(dzb.o<0>().object(3) == Approx(6));
    }

    SECTION("Elementwise and additional input") {
        ls::blocks::std::DeadzoneBlock<Eigen::Vector4d, ls::blocks::std::DeadzoneBlockOperator::Elementwise, ls::blocks::std::DeadzoneBlockParameter::AdditionalInput> dzb;

        Eigen::Vector4d v, vl, vu;
        v << -4, 2, -6, 6;
        vl << -1, 0, 0, 2;
        vu << 2, 3, 4, 5;

        dzb.lower() = vl;
        dzb.upper() = vu;

        dzb.i<0>() = v;
        dzb.trigger();

        REQUIRE(dzb.o<0>().object(0) == Approx(-4));
        REQUIRE(dzb.o<0>().object(1) == Approx(0));
        REQUIRE(dzb.o<0>().object(2) == Approx(-6));
        REQUIRE(dzb.o<0>().object(3) == Approx(6));

        v << 0, 1, -7, 6;
        dzb.i<0>() = v;
        dzb.trigger();

        REQUIRE(dzb.o<0>().object(0) == Approx(0));
        REQUIRE(dzb.o<0>().object(1) == Approx(0));
        REQUIRE(dzb.o<0>().object(2) == Approx(-7));
        REQUIRE(dzb.o<0>().object(3) == Approx(6));
    }

    SECTION("Type alias") {
        REQUIRE(::std::is_same<ls::blocks::std::DeadzoneBlockDynamic<Eigen::Vector4d, ls::blocks::std::DeadzoneBlockOperator::Elementwise>, ls::blocks::std::DeadzoneBlock<Eigen::Vector4d, ls::blocks::std::DeadzoneBlockOperator::Elementwise, ls::blocks::std::DeadzoneBlockParameter::AdditionalInput>>::value);
        REQUIRE(::std::is_same<ls::blocks::std::DeadzoneBlockDynamic<Eigen::Vector4d, ls::blocks::std::DeadzoneBlockOperator::Scalar>, ls::blocks::std::DeadzoneBlock<Eigen::Vector4d, ls::blocks::std::DeadzoneBlockOperator::Scalar, ls::blocks::std::DeadzoneBlockParameter::AdditionalInput>>::value);
    }
}