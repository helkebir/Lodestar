//
// Created by Hamza El-Kebir on 4/17/21.
//

#include "ZeroOrderHold.hpp"
#include "unsupported/Eigen/MatrixFunctions"

ls::systems::StateSpace
ls::analysis::ZeroOrderHold::c2d(const Eigen::MatrixXd &A,
                                 const Eigen::MatrixXd &B,
                                 const Eigen::MatrixXd &C,
                                 const Eigen::MatrixXd &D, double dt)
{
    dt = abs(dt);

    const long n = A.rows();
    const long m = B.cols();

    // Upper exponential matrix
    Eigen::MatrixXd upperEM(n, n + m);
    upperEM.block(0, 0, n, n) << A;
    upperEM.block(0, n, n, m) << B;

    // Lower exponential matrix
    auto lowerEM = Eigen::MatrixXd::Zero(m, n + m);

    // Stacked exponential matrix
    Eigen::MatrixXd EM(n + m, n + m);
    EM.block(0, 0, n, n + m) << upperEM;
    EM.block(n, 0, m, n + m) << lowerEM;

    // Matrix exponential
    Eigen::MatrixXd EXPM;
    EXPM = (EM * dt).exp().block(0, 0, n, n + m);

    Eigen::MatrixXd AD = EXPM.block(0, 0, n, n);
    Eigen::MatrixXd BD = EXPM.block(0, n, n, m);

    auto dss = systems::StateSpace(AD, BD, C, D);

    return dss;
}

ls::systems::StateSpace
ls::analysis::ZeroOrderHold::c2d(const systems::StateSpace &ss, double dt)
{
    return c2d(ss.getA(), ss.getB(), ss.getC(), ss.getD(), dt);
}

ls::systems::StateSpace
ls::analysis::ZeroOrderHold::d2c(const Eigen::MatrixXd &A,
                                 const Eigen::MatrixXd &B,
                                 const Eigen::MatrixXd &C,
                                 const Eigen::MatrixXd &D, double dt)
{
    dt = abs(dt);

    const long n = A.rows();
    const long m = B.cols();

    // Upper logarith matrix
    Eigen::MatrixXd upperLM(n, n + m);
    upperLM.block(0, 0, n, n) << A;
    upperLM.block(0, n, n, m) << B;

    // Lower logarithm matrix
    Eigen::MatrixXd lowerLM(m, n + m);
    lowerLM.block(0, 0, m, n) << Eigen::MatrixXd::Zero(m, n);
    lowerLM.block(0, n, m, m) << Eigen::MatrixXd::Identity(m, m);

    // Stacked logarithm matrix
    Eigen::MatrixXd LM(n + m,
                       n + m);
    LM.block(0, 0, n, n + m) << upperLM;
    LM.block(n, 0, m, n + m) << lowerLM;

    // Matrix logarithm
    Eigen::MatrixXd LOGM;
    LOGM = LM.log().block(0, 0, n, n + m) / dt;

    Eigen::MatrixXd AC = LOGM.block(0, 0, n, n);
    Eigen::MatrixXd BC = LOGM.block(0, n, n, m);

    auto css = systems::StateSpace(AC, BC, C, D);

    return css;
}

ls::systems::StateSpace
ls::analysis::ZeroOrderHold::d2c(const systems::StateSpace &ss, double dt)
{
    return d2c(ss.getA(), ss.getB(), ss.getC(), ss.getD(), dt);
}