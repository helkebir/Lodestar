//
// Created by Hamza El-Kebir on 4/17/21.
//

#include "BilinearTransformation.hpp"

ls::systems::StateSpace
ls::analysis::BilinearTransformation::c2d(const systems::StateSpace &lti,
                                          double dt,
                                          double alpha)
{
    if (alpha < 0 || alpha > 1) alpha = 0;
    dt = abs(dt);

    auto I = Eigen::MatrixXd::Identity(lti.A.rows(), lti.A.rows());

    auto IMAC = I - alpha * dt * lti.A;
    auto IMAC2 = I - (1 - alpha) * dt * lti.A;

    Eigen::MatrixXd AD = IMAC.colPivHouseholderQr().solve(IMAC2);
    Eigen::MatrixXd BD = IMAC.colPivHouseholderQr().solve(dt * lti.B);
    Eigen::MatrixXd CD = IMAC.transpose().colPivHouseholderQr().solve(
            lti.C.transpose()).transpose();
    Eigen::MatrixXd DD = lti.D + alpha * (lti.C * BD);

    auto dlti = systems::StateSpace(AD, BD, CD, DD);
    dlti.setSamplingPeriod(dt);

    return dlti;
}

ls::systems::StateSpace
ls::analysis::BilinearTransformation::d2c(const systems::StateSpace &lti,
                                          double dt,
                                          double alpha)
{
    if (alpha < 0 || alpha > 1) alpha = 0;
    dt = abs(dt);

    auto I = Eigen::MatrixXd::Identity(lti.A.rows(), lti.A.rows());

    auto ATMI = lti.A.transpose() - I;
    auto ATPI = alpha * dt * lti.A.transpose() + (1 - alpha) * dt * I;
    Eigen::MatrixXd AC = ATPI.colPivHouseholderQr().solve(ATMI).transpose();

    auto IMAC = I - alpha * dt * AC;
    Eigen::MatrixXd BC = IMAC * lti.B / dt;
    Eigen::MatrixXd CC = lti.C * IMAC;
    Eigen::MatrixXd DC = lti.D - alpha * (CC * lti.B);

    auto clti = systems::StateSpace(AC, BC, CC, DC);

    return clti;
}

ls::systems::StateSpace
ls::analysis::BilinearTransformation::c2dTustin(const systems::StateSpace &lti,
                                                double dt)
{
    return c2d(lti, dt, 0.5);
}

ls::systems::StateSpace
ls::analysis::BilinearTransformation::d2cTustin(const systems::StateSpace &lti,
                                                double dt)
{
    return d2c(lti, dt, 0.5);
}

ls::systems::StateSpace
ls::analysis::BilinearTransformation::c2dEuler(const systems::StateSpace &lti,
                                               double dt)
{
    return c2d(lti, dt, 0.0);
}

ls::systems::StateSpace
ls::analysis::BilinearTransformation::d2cEuler(const systems::StateSpace &lti,
                                               double dt)
{
    return d2c(lti, dt, 0.0);
}

ls::systems::StateSpace
ls::analysis::BilinearTransformation::c2dBwdDiff(const systems::StateSpace &lti,
                                                 double dt)
{
    return c2d(lti, dt, 1.0);
}

ls::systems::StateSpace
ls::analysis::BilinearTransformation::d2cBwdDiff(const systems::StateSpace &lti,
                                                 double dt)
{
    return d2c(lti, dt, 1.0);
}