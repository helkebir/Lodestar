//
// Created by Hamza El-Kebir on 4/17/21.
//

#include "LinearSystemInverse.hpp"

ls::systems::StateSpace ls::analysis::LinearSystemInverse::inverse(
        ls::systems::StateSpace &ss)
{
    Eigen::MatrixXd AINV =
            ss.getA() - ss.getB() * ss.getD().inverse() * ss.getC();
    Eigen::MatrixXd BINV = -ss.getB() * ss.getD().inverse();
    Eigen::MatrixXd CINV = ss.getD().inverse() * ss.getC();
    Eigen::MatrixXd DINV = ss.getD().inverse();

    auto invlti = systems::StateSpace(AINV, BINV, CINV, DINV);

    return invlti;
}
