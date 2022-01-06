//
// Created by Hamza El-Kebir on 12/23/21.
//

#include "catchOnce.hpp"
#include "Lodestar/blocks/std/SaturationBlock.hpp"


TEST_CASE("SaturationBlock", "[blocks][std]")
{
    SECTION("Parametric input") {
        ls::blocks::std::SaturationBlock<double> sb;

        sb.lower() = -1;
        sb.upper() = 1;

        sb.i<0>() = 3;
        sb.trigger();

        REQUIRE(sb.o<0>().object == Approx(1));
    }

    SECTION("Additional input") {
        ls::blocks::std::SaturationBlock<double, ls::blocks::std::SaturationBlockOperator::Scalar, ls::blocks::std::SaturationBlockParameter::AdditionalInput> sb;

        sb.lower() = -1;
        sb.upper() = 1;

        sb.i<0>() = 3;
        sb.trigger();

        REQUIRE(sb.o<0>().object == Approx(1));
    }

    SECTION("Scalar and parametric input") {
        ls::blocks::std::SaturationBlock<Eigen::Vector2d> sb;

        Eigen::Vector2d v;
        v << -3, 2;

        sb.lower() = -1;
        sb.upper() = 1;

        sb.i<0>() = v;
        sb.trigger();

        REQUIRE(sb.o<0>().object(0) == Approx(-1));
        REQUIRE(sb.o<0>().object(1) == Approx(1));
    }

    SECTION("Scalar and additional input") {
        ls::blocks::std::SaturationBlock<Eigen::Vector2d, ls::blocks::std::SaturationBlockOperator::Scalar, ls::blocks::std::SaturationBlockParameter::AdditionalInput> sb;

        Eigen::Vector2d v;
        v << -3, 2;

        sb.lower() = -1;
        sb.upper() = 1;

        sb.i<0>() = v;
        sb.trigger();

        REQUIRE(sb.o<0>().object(0) == Approx(-1));
        REQUIRE(sb.o<0>().object(1) == Approx(1));
    }

    SECTION("Elementwise and parametric input") {
        ls::blocks::std::SaturationBlock<Eigen::Vector4d, ls::blocks::std::SaturationBlockOperator::Elementwise> sb;

        Eigen::Vector4d v, vl, vu;
        v << -4, 2, -6, 6;
        vl << -1, 0, 0, 2;
        vu << 2, 3, 4, 5;

        sb.lower() = vl;
        sb.upper() = vu;

        sb.i<0>() = v;
        sb.trigger();

        REQUIRE(sb.o<0>().object(0) == Approx(-1));
        REQUIRE(sb.o<0>().object(1) == Approx(2));
        REQUIRE(sb.o<0>().object(2) == Approx(0));
        REQUIRE(sb.o<0>().object(3) == Approx(5));
    }

    SECTION("Elementwise and additional input") {
        ls::blocks::std::SaturationBlock<Eigen::Vector4d, ls::blocks::std::SaturationBlockOperator::Elementwise, ls::blocks::std::SaturationBlockParameter::AdditionalInput> sb;

        Eigen::Vector4d v, vl, vu;
        v << -4, 2, -6, 6;
        vl << -1, 0, 0, 2;
        vu << 2, 3, 4, 5;

        sb.lower() = vl;
        sb.upper() = vu;

        sb.i<0>() = v;
        sb.trigger();

        REQUIRE(sb.o<0>().object(0) == Approx(-1));
        REQUIRE(sb.o<0>().object(1) == Approx(2));
        REQUIRE(sb.o<0>().object(2) == Approx(0));
        REQUIRE(sb.o<0>().object(3) == Approx(5));
    }

    SECTION("Type alias") {
        REQUIRE(::std::is_same<ls::blocks::std::SaturationBlockDynamic<Eigen::Vector4d, ls::blocks::std::SaturationBlockOperator::Elementwise>, ls::blocks::std::SaturationBlock<Eigen::Vector4d, ls::blocks::std::SaturationBlockOperator::Elementwise, ls::blocks::std::SaturationBlockParameter::AdditionalInput>>::value);
        REQUIRE(::std::is_same<ls::blocks::std::SaturationBlockDynamic<Eigen::Vector4d, ls::blocks::std::SaturationBlockOperator::Scalar>, ls::blocks::std::SaturationBlock<Eigen::Vector4d, ls::blocks::std::SaturationBlockOperator::Scalar, ls::blocks::std::SaturationBlockParameter::AdditionalInput>>::value);
    }
}