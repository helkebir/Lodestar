//
// Created by Hamza El-Kebir on 5/19/21.
//

#ifndef LODESTAR_TRANSFERFUNCTION_TEST_HPP
#define LODESTAR_TRANSFERFUNCTION_TEST_HPP

#include "catchOnce.hpp"
#include "systems/TransferFunction.hpp"

TEST_CASE("TransferFunction dynamic construction", "[systems][TransferFunction][dynamic][construction]")
{
    Eigen::VectorXd num(3), den(3);
    //    num << 1,2,3;
    //    den << 2,3,4;
    num << 2.3,
            1.2,
            0;

    den << 0,
            2.1,
            5.3;

    auto tf = ls::systems::TransferFunction(num, den);

    REQUIRE(tf.getNum() == num);
    REQUIRE(tf.getDen() == den);
    REQUIRE(tf.getNumDegree() == 1);
    REQUIRE(tf.getDenDegree() == 2);
}

#endif //LODESTAR_TRANSFERFUNCTION_TEST_HPP
