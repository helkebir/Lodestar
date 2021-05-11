//
// Created by Hamza El-Kebir on 4/17/21.
//

#include "BilinearTransformation.hpp"

ls::systems::StateSpace
ls::analysis::BilinearTransformation::c2d(const Eigen::MatrixXd &A,
                                          const Eigen::MatrixXd &B,
                                          const Eigen::MatrixXd &C,
                                          const Eigen::MatrixXd &D, double dt,
                                          double alpha)
{
    if (alpha < 0 || alpha > 1) alpha = 0;
    dt = abs(dt);

    auto I = Eigen::MatrixXd::Identity(A.rows(), A.rows());

    auto IMAC = I - alpha * dt * A;
    auto IMAC2 = I - (1 - alpha) * dt * A;

    Eigen::MatrixXd AD = IMAC.colPivHouseholderQr().solve(IMAC2);
    Eigen::MatrixXd BD = IMAC.colPivHouseholderQr().solve(dt * B);
    Eigen::MatrixXd CD = IMAC.transpose().colPivHouseholderQr().solve(
            C.transpose()).transpose();
    Eigen::MatrixXd DD = D + alpha * (C * BD);

    auto dss = systems::StateSpace(AD, BD, CD, DD);
    dss.setSamplingPeriod(dt);

    return dss;
}

ls::systems::StateSpace
ls::analysis::BilinearTransformation::c2d(const systems::StateSpace &ss,
                                          double dt,
                                          double alpha)
{
    return c2d(ss.getA(), ss.getB(), ss.getC(), ss.getD(), dt, alpha);
}

ls::systems::StateSpace
ls::analysis::BilinearTransformation::d2c(const Eigen::MatrixXd &A,
                                          const Eigen::MatrixXd &B,
                                          const Eigen::MatrixXd &C,
                                          const Eigen::MatrixXd &D, double dt,
                                          double alpha)
{
    if (alpha < 0 || alpha > 1) alpha = 0;
    dt = abs(dt);

    auto I = Eigen::MatrixXd::Identity(A.rows(), A.rows());

    auto ATMI = A.transpose() - I;
    auto ATPI = alpha * dt * A.transpose() + (1 - alpha) * dt * I;
    Eigen::MatrixXd AC = ATPI.colPivHouseholderQr().solve(ATMI).transpose();

    auto IMAC = I - alpha * dt * AC;
    Eigen::MatrixXd BC = IMAC * B / dt;
    Eigen::MatrixXd CC = C * IMAC;
    Eigen::MatrixXd DC = D - alpha * (CC * B);

    auto css = systems::StateSpace(AC, BC, CC, DC);

    return css;
}

ls::systems::StateSpace
ls::analysis::BilinearTransformation::d2c(const systems::StateSpace &ss,
                                          double dt,
                                          double alpha)
{
    return d2c(ss.getA(), ss.getB(), ss.getC(), ss.getD(), dt, alpha);
}

ls::systems::StateSpace
ls::analysis::BilinearTransformation::d2c(const ls::systems::StateSpace &ss,
                                          double alpha)
{
    return d2c(ss.getA(), ss.getB(), ss.getC(), ss.getD(), ss.getSamplingPeriod(), alpha);
}

ls::systems::StateSpace
ls::analysis::BilinearTransformation::c2dTustin(const systems::StateSpace &ss,
                                                double dt)
{
    return c2d(ss, dt, 0.5);
}

ls::systems::StateSpace
ls::analysis::BilinearTransformation::d2cTustin(const systems::StateSpace &ss,
                                                double dt)
{
    return d2c(ss, dt, 0.5);
}

ls::systems::StateSpace
ls::analysis::BilinearTransformation::c2dEuler(const systems::StateSpace &ss,
                                               double dt)
{
    return c2d(ss, dt, 0.0);
}

ls::systems::StateSpace
ls::analysis::BilinearTransformation::d2cEuler(const systems::StateSpace &ss,
                                               double dt)
{
    return d2c(ss, dt, 0.0);
}

ls::systems::StateSpace
ls::analysis::BilinearTransformation::c2dBwdDiff(const systems::StateSpace &ss,
                                                 double dt)
{
    return c2d(ss, dt, 1.0);
}

ls::systems::StateSpace
ls::analysis::BilinearTransformation::d2cBwdDiff(const systems::StateSpace &ss,
                                                 double dt)
{
    return d2c(ss, dt, 1.0);
}