//
// Created by Hamza El-Kebir on 4/17/21.
//

#include "LinearSystemInverse.hpp"

ls::systems::StateSpace ls::analysis::LinearSystemInverse::inverse(
        ls::systems::StateSpace &lti)
{
    Eigen::MatrixXd AINV = lti.A - lti.B * lti.D.inverse() * lti.C;
    Eigen::MatrixXd BINV = -lti.B * lti.D.inverse();
    Eigen::MatrixXd CINV = lti.D.inverse() * lti.C;
    Eigen::MatrixXd DINV = lti.D.inverse();

    auto invlti = systems::StateSpace(AINV, BINV, CINV, DINV);

    return invlti;
}
