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

    auto ltiA = lti.getA();
    auto ltiB = lti.getB();
    auto ltiC = lti.getC();
    auto ltiD = lti.getD();

    auto I = Eigen::MatrixXd::Identity(ltiA.rows(), ltiA.rows());

    auto IMAC = I - alpha * dt * ltiA;
    auto IMAC2 = I - (1 - alpha) * dt * ltiA;

    Eigen::MatrixXd AD = IMAC.colPivHouseholderQr().solve(IMAC2);
    Eigen::MatrixXd BD = IMAC.colPivHouseholderQr().solve(dt * ltiB);
    Eigen::MatrixXd CD = IMAC.transpose().colPivHouseholderQr().solve(
            ltiC.transpose()).transpose();
    Eigen::MatrixXd DD = ltiD + alpha * (ltiC * BD);

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

    auto ltiA = lti.getA();
    auto ltiB = lti.getB();
    auto ltiC = lti.getC();
    auto ltiD = lti.getD();

    auto I = Eigen::MatrixXd::Identity(ltiA.rows(), ltiA.rows());

    auto ATMI = ltiA.transpose() - I;
    auto ATPI = alpha * dt * ltiA.transpose() + (1 - alpha) * dt * I;
    Eigen::MatrixXd AC = ATPI.colPivHouseholderQr().solve(ATMI).transpose();

    auto IMAC = I - alpha * dt * AC;
    Eigen::MatrixXd BC = IMAC * ltiB / dt;
    Eigen::MatrixXd CC = ltiC * IMAC;
    Eigen::MatrixXd DC = ltiD - alpha * (CC * ltiB);

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