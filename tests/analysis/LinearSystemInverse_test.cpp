//
// Created by Hamza El-Kebir on 4/17/21.
//

#include "analysis/LinearSystemInverse.hpp"
#include "systems/StateSpace.hpp"
#include "Eigen/Dense"

ls::systems::StateSpace<> linearSystemInverseExample()
{
    Eigen::MatrixXd A(3, 3), B(3, 2), C(2, 3), D(2, 2);
    A.block(0, 0, 3, 3) << 1, 2, 0, 4, -1, 0, 0, 0, 1;
    B.block(0, 0, 3, 2) << 1, 0, 0, 1, 1, 0;
    C.block(0, 0, 2, 3) << 0, 1, -1, 0, 0, 1;
    D.block(0, 0, 2, 2) << 4, 0, 0, 1;

    ls::systems::StateSpace<> lti = ls::systems::StateSpace<>(A, B, C, D);
    return lti;
//    ls::systems::StateSpace<> ilti = ls::analysis::LinearSystemInverse::inverse(lti);
//
//    return ilti;
}
