//
// Created by Hamza El-Kebir on 5/19/21.
//

#ifndef LODESTAR_STATESPACE_TEST_HPP
#define LODESTAR_STATESPACE_TEST_HPP

#include "catchOnce.hpp"
#include "Eigen/Dense"
#include "systems/StateSpace.hpp"

TEST_CASE("StateSpace dynamic construction", "[systems][StateSpace][dynamic][construction]") {
    Eigen::MatrixXd A(3, 3), B(3, 2), C(2, 3), D(2, 2);
    A << 1,  2, 0,
         4, -1, 0,
         0,  0, 1;

    B << 1, 0,
         0, 1,
         1, 0;

    C << 0, 1, -1,
         0, 0,  1;

    D << 4, 0,
         0, 1;

    auto ss = ls::systems::StateSpace<>(A, B, C, D);

    SECTION("Default discrete parameters") {
        REQUIRE(ss.getSamplingPeriod() == -1);
        REQUIRE(ss.isDiscrete() == false);
    }

    SECTION("Dimensions") {
        REQUIRE(ss.stateDim() == 3);
        REQUIRE(ss.inputDim() == 2);
        REQUIRE(ss.outputDim() == 2);
    }

    SECTION("Matrices") {
        REQUIRE(*ss.getA() == A);
        REQUIRE(*ss.getB() == B);
        REQUIRE(*ss.getC() == C);
        REQUIRE(*ss.getD() == D);
    }

    SECTION("Set discrete parameters") {
        ss.setDiscreteParams(0.1);
        REQUIRE(ss.isDiscrete() == true);
        REQUIRE(ss.getSamplingPeriod() == Approx(0.1));
    }
}

TEST_CASE("StateSpace static construction", "[StateSpace][static][construction]") {
    Eigen::MatrixXd A(3, 3), B(3, 2), C(2, 3), D(2, 2);
    A << 1,  2, 0,
         4, -1, 0,
         0,  0, 1;

    B << 1, 0,
         0, 1,
         1, 0;

    C << 0, 1, -1,
         0, 0,  1;

    D << 4, 0,
         0, 1;

    auto ss = ls::systems::StateSpace<double, 3, 2, 2>(A, B, C, D);

    SECTION("Default discrete parameters") {
        REQUIRE(ss.getSamplingPeriod() == -1);
        REQUIRE(ss.isDiscrete() == false);
    }

    SECTION("Dimensions") {
        REQUIRE(ss.stateDim() == 3);
        REQUIRE(ss.inputDim() == 2);
        REQUIRE(ss.outputDim() == 2);
    }

    SECTION("Matrices") {
        REQUIRE(*ss.getA() == A);
        REQUIRE(*ss.getB() == B);
        REQUIRE(*ss.getC() == C);
        REQUIRE(*ss.getD() == D);
    }

    SECTION("Set discrete parameters") {
        ss.setDiscreteParams(0.1);
        REQUIRE(ss.isDiscrete() == true);
        REQUIRE(ss.getSamplingPeriod() == Approx(0.1));
    }
}

#endif //LODESTAR_STATESPACE_TEST_HPP
