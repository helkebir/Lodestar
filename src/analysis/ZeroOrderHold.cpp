//
// Created by Hamza El-Kebir on 4/17/21.
//

#include "ZeroOrderHold.hpp"
#include "unsupported/Eigen/MatrixFunctions"

ls::systems::StateSpace
ls::analysis::ZeroOrderHold::c2d(const systems::StateSpace &lti, double dt)
{
    dt = abs(dt);

    // Upper exponential matrix
    Eigen::MatrixXd upperEM(lti.stateDim(), lti.stateDim() + lti.inputDim());
    upperEM.block(0, 0, lti.stateDim(), lti.stateDim()) << lti.getA();
    upperEM.block(0, lti.stateDim(), lti.stateDim(), lti.inputDim()) << lti.getB();

    // Lower exponential matrix
    auto lowerEM = Eigen::MatrixXd::Zero(lti.inputDim(),
                                         lti.stateDim() + lti.inputDim());

    // Stacked exponential matrix
    Eigen::MatrixXd EM(lti.stateDim() + lti.inputDim(), lti.stateDim() + lti.inputDim());
    EM.block(0, 0, lti.stateDim(), lti.stateDim() + lti.inputDim())
            << upperEM;
    EM.block(lti.stateDim(), 0, lti.inputDim(),
             lti.stateDim() + lti.inputDim()) << lowerEM;

    // Matrix exponential
    Eigen::MatrixXd EXPM;
    EXPM = (EM * dt).exp().block(0, 0, lti.stateDim(),
                                 lti.stateDim() + lti.inputDim());

    Eigen::MatrixXd AD = EXPM.block(0, 0, lti.stateDim(), lti.stateDim());
    Eigen::MatrixXd BD = EXPM.block(0, lti.stateDim(), lti.stateDim(),
                                    lti.inputDim());

    auto dlti = systems::StateSpace(AD, BD, lti.getC(), lti.getD());

    return dlti;
}

ls::systems::StateSpace
ls::analysis::ZeroOrderHold::d2c(const systems::StateSpace &lti, double dt)
{
    dt = abs(dt);

    // Upper logarith matrix
    Eigen::MatrixXd upperLM(lti.stateDim(), lti.stateDim() + lti.inputDim());
    upperLM.block(0, 0, lti.stateDim(), lti.stateDim()) << lti.getA();
    upperLM.block(0, lti.stateDim(), lti.stateDim(), lti.inputDim()) << lti.getB();

    // Lower logarithm matrix
    Eigen::MatrixXd lowerLM(lti.inputDim(), lti.stateDim() + lti.inputDim());
    lowerLM.block(0, 0, lti.inputDim(), lti.stateDim())
            << Eigen::MatrixXd::Zero(lti.inputDim(), lti.stateDim());
    lowerLM.block(0, lti.stateDim(), lti.inputDim(), lti.inputDim())
            << Eigen::MatrixXd::Identity(lti.inputDim(), lti.inputDim());

    // Stacked logarithm matrix
    Eigen::MatrixXd LM(lti.stateDim() + lti.inputDim(), lti.stateDim() + lti.inputDim());
    LM.block(0, 0, lti.stateDim(), lti.stateDim() + lti.inputDim())
            << upperLM;
    LM.block(lti.stateDim(), 0, lti.inputDim(),
             lti.stateDim() + lti.inputDim()) << lowerLM;

    // Matrix logarithm
    Eigen::MatrixXd LOGM;
    LOGM = LM.log().block(0, 0, lti.stateDim(),
                          lti.stateDim() + lti.inputDim()) / dt;

    Eigen::MatrixXd AC = LOGM.block(0, 0, lti.stateDim(), lti.stateDim());
    Eigen::MatrixXd BC = LOGM.block(0, lti.stateDim(), lti.stateDim(),
                                    lti.inputDim());

    auto clti = systems::StateSpace(AC, BC, lti.getC(), lti.getD());

    return clti;
}
