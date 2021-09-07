//
// Created by Hamza El-Kebir on 4/17/21.
//

#include "BilinearTransformation.hpp"

ls::systems::StateSpace<>
ls::analysis::BilinearTransformation::c2d(const Eigen::MatrixXd &A,
                                          const Eigen::MatrixXd &B,
                                          const Eigen::MatrixXd &C,
                                          const Eigen::MatrixXd &D, double dt,
                                          double alpha)
{
    systems::StateSpace<> ss(A, B, C, D), out;
    auto *memStruct = new mallocStructC2D<>;
    c2d(&ss, dt, alpha, &out, memStruct);
    delete memStruct;

    return out;
}

ls::systems::StateSpace<>
ls::analysis::BilinearTransformation::c2d(const Eigen::MatrixXd *A,
                                          const Eigen::MatrixXd *B,
                                          const Eigen::MatrixXd *C,
                                          const Eigen::MatrixXd *D, double dt,
                                          double alpha)
{
    return c2d(*A, *B, *C, *D, dt, alpha);
}

ls::systems::StateSpace<>
ls::analysis::BilinearTransformation::c2d(const systems::StateSpace<> &ss,
                                          double dt,
                                          double alpha)
{
    return c2d(ss.getA(), ss.getB(), ss.getC(), ss.getD(), dt, alpha);
}

ls::systems::StateSpace<>
ls::analysis::BilinearTransformation::d2c(const Eigen::MatrixXd *A,
                                          const Eigen::MatrixXd *B,
                                          const Eigen::MatrixXd *C,
                                          const Eigen::MatrixXd *D, double dt,
                                          double alpha)
{
    systems::StateSpace<> ss(*A, *B, *C, *D), out;
    auto *memStruct = new mallocStructD2C<>;
    d2c(&ss, dt, alpha, &out, memStruct);
    delete memStruct;

    return out;
}

ls::systems::StateSpace<>
ls::analysis::BilinearTransformation::d2c(const Eigen::MatrixXd &A,
                                          const Eigen::MatrixXd &B,
                                          const Eigen::MatrixXd &C,
                                          const Eigen::MatrixXd &D, double dt,
                                          double alpha)
{
    systems::StateSpace<> ss(A, B, C, D), out;
    auto *memStruct = new mallocStructD2C<>;
    d2c(&ss, dt, alpha, &out, memStruct);
    delete memStruct;

    return out;
}

ls::systems::StateSpace<>
ls::analysis::BilinearTransformation::d2c(const systems::StateSpace<> &ss,
                                          double dt,
                                          double alpha)
{
    return d2c(ss.getA(), ss.getB(), ss.getC(), ss.getD(), dt, alpha);
}

ls::systems::StateSpace<>
ls::analysis::BilinearTransformation::d2c(const ls::systems::StateSpace<> &ss,
                                          double alpha)
{
    return d2c(ss.getA(), ss.getB(), ss.getC(), ss.getD(), ss.getSamplingPeriod(), alpha);
}

ls::systems::StateSpace<>
ls::analysis::BilinearTransformation::c2dTustin(const systems::StateSpace<> &ss,
                                                double dt)
{
    return c2d(ss, dt, 0.5);
}

ls::systems::StateSpace<>
ls::analysis::BilinearTransformation::d2cTustin(const systems::StateSpace<> &ss,
                                                double dt)
{
    return d2c(ss, dt, 0.5);
}

ls::systems::StateSpace<>
ls::analysis::BilinearTransformation::c2dEuler(const systems::StateSpace<> &ss,
                                               double dt)
{
    return c2d(ss, dt, 0.0);
}

ls::systems::StateSpace<>
ls::analysis::BilinearTransformation::d2cEuler(const systems::StateSpace<> &ss,
                                               double dt)
{
    return d2c(ss, dt, 0.0);
}

ls::systems::StateSpace<>
ls::analysis::BilinearTransformation::c2dBwdDiff(const systems::StateSpace<> &ss,
                                                 double dt)
{
    return c2d(ss, dt, 1.0);
}

ls::systems::StateSpace<>
ls::analysis::BilinearTransformation::d2cBwdDiff(const systems::StateSpace<> &ss,
                                                 double dt)
{
    return d2c(ss, dt, 1.0);
}