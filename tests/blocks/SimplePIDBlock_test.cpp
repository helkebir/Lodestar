//
// Created by Hamza El-Kebir on 2/20/22.
//

#include "catchOnce.hpp"
#include "Lodestar/blocks/std/SimplePIDBlock.hpp"


TEST_CASE("SimplePIDBlock", "[blocks][std]")
{
    SECTION("Parametric input") {
        ls::blocks::std::SimplePIDBlock<double> pid;
        pid.samplingPeriod() = 1;
        pid.pGain() = 1;
        pid.iGain() = 2;
        pid.dGain() = 0.1;

        pid.i<0>() = 2;
        pid.trigger();

        REQUIRE(pid.o<0>().object == Approx(2 + 0.2));

        pid.trigger();
        REQUIRE(pid.o<0>().object == Approx(2 + 2*2));
    }

    SECTION("Additional input") {
        ls::blocks::std::SimplePIDBlock<double, ls::blocks::std::SimplePIDBlockOperator::Scalar, ls::blocks::std::SimplePIDBlockParameter::AdditionalInput> pid;
        pid.samplingPeriod() = 1;
        pid.pGain() = 1;
        pid.iGain() = 2;
        pid.dGain() = 0.1;

        pid.i<0>() = 2;
        pid.trigger();

        REQUIRE(pid.o<0>().object == Approx(2 + 0.2));

        pid.trigger();
        REQUIRE(pid.o<0>().object == Approx(2 + 2*2));
    }

    SECTION("Scalar and parametric input") {
        ls::blocks::std::SimplePIDBlock<Eigen::Vector2d> pid;
        pid.samplingPeriod() = 1;

        Eigen::Vector2d v;
        v << 2, -2;

        pid.pGain() = 1;
        pid.iGain() = 2;
        pid.dGain() = 0.1;

        pid.i<0>() = v;
        pid.trigger();

        REQUIRE(pid.o<0>().object(0) == Approx(2 + 0.2));
        REQUIRE(pid.o<0>().object(1) == Approx(-2 - 0.2));

        pid.trigger();

        REQUIRE(pid.o<0>().object(0) == Approx(2 + 2*2));
        REQUIRE(pid.o<0>().object(1) == Approx(-2 - 2*2));
    }

    SECTION("Scalar and additional input") {
        ls::blocks::std::SimplePIDBlock<Eigen::Vector2d, ls::blocks::std::SimplePIDBlockOperator::Scalar, ls::blocks::std::SimplePIDBlockParameter::AdditionalInput> pid;
        pid.samplingPeriod() = 1;

        Eigen::Vector2d v;
        v << 2, -2;

        pid.pGain() = 1;
        pid.iGain() = 2;
        pid.dGain() = 0.1;

        pid.i<0>() = v;
        pid.trigger();

        REQUIRE(pid.o<0>().object(0) == Approx(2 + 0.2));
        REQUIRE(pid.o<0>().object(1) == Approx(-2 - 0.2));

        pid.trigger();

        REQUIRE(pid.o<0>().object(0) == Approx(2 + 2*2));
        REQUIRE(pid.o<0>().object(1) == Approx(-2 - 2*2));
    }

    SECTION("Elementwise and parametric input") {
        ls::blocks::std::SimplePIDBlock<Eigen::Vector2d, ls::blocks::std::SimplePIDBlockOperator::Elementwise> pid;
        pid.samplingPeriod() = 1;

        Eigen::Vector2d v, Kp, Ki, Kd;
        v << 2, -4;
        Kp << 1, -1;
        Ki << 2, -2;
        Kd << 0.1, -0.1;

        pid.pGain() = Kp;
        pid.iGain() = Ki;
        pid.dGain() = Kd;

        pid.i<0>() = v;
        pid.trigger();

        REQUIRE(pid.o<0>().object(0) == Approx(2 + 0.2));
        REQUIRE(pid.o<0>().object(1) == Approx(4 + 0.4));

        pid.trigger();

        REQUIRE(pid.o<0>().object(0) == Approx(2 + 2*2));
        REQUIRE(pid.o<0>().object(1) == Approx(4 + 2*4));
    }

    SECTION("Elementwise and additional input") {
        ls::blocks::std::SimplePIDBlock<Eigen::Vector2d, ls::blocks::std::SimplePIDBlockOperator::Elementwise, ls::blocks::std::SimplePIDBlockParameter::AdditionalInput> pid;
        pid.samplingPeriod() = 1;

        Eigen::Vector2d v, Kp, Ki, Kd;
        v << 2, -4;
        Kp << 1, -1;
        Ki << 2, -2;
        Kd << 0.1, -0.1;

        pid.pGain() = Kp;
        pid.iGain() = Ki;
        pid.dGain() = Kd;

        pid.i<0>() = v;
        pid.trigger();

        REQUIRE(pid.o<0>().object(0) == Approx(2 + 0.2));
        REQUIRE(pid.o<0>().object(1) == Approx(4 + 0.4));

        pid.trigger();

        REQUIRE(pid.o<0>().object(0) == Approx(2 + 2*2));
        REQUIRE(pid.o<0>().object(1) == Approx(4 + 2*4));
    }

    SECTION("Type alias") {
        REQUIRE(::std::is_same<ls::blocks::std::SimplePIDBlockDynamic<Eigen::Vector4d, ls::blocks::std::SimplePIDBlockOperator::Elementwise>, ls::blocks::std::SimplePIDBlock<Eigen::Vector4d, ls::blocks::std::SimplePIDBlockOperator::Elementwise, ls::blocks::std::SimplePIDBlockParameter::AdditionalInput>>::value);
        REQUIRE(::std::is_same<ls::blocks::std::SimplePIDBlockDynamic<Eigen::Vector4d, ls::blocks::std::SimplePIDBlockOperator::Scalar>, ls::blocks::std::SimplePIDBlock<Eigen::Vector4d, ls::blocks::std::SimplePIDBlockOperator::Scalar, ls::blocks::std::SimplePIDBlockParameter::AdditionalInput>>::value);
    }
}
