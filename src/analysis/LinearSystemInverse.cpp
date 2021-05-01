//
// Created by Hamza El-Kebir on 4/17/21.
//

#include "LinearSystemInverse.hpp"

ls::systems::StateSpace ls::analysis::LinearSystemInverse::inverse(
        ls::systems::StateSpace &lti)
{
    Eigen::MatrixXd AINV = lti.getA() - lti.getB() * lti.getD().inverse() * lti.getC();
    Eigen::MatrixXd BINV = -lti.getB() * lti.getD().inverse();
    Eigen::MatrixXd CINV = lti.getD().inverse() * lti.getC();
    Eigen::MatrixXd DINV = lti.getD().inverse();

    auto invlti = systems::StateSpace(AINV, BINV, CINV, DINV);

    return invlti;
}
