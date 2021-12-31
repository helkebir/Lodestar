//
// Created by Hamza El-Kebir on 12/30/2021.
//

#include "LunarLanderDemo.hpp"

#include "control/DiscreteLQR.hpp"
#include "analysis/ZeroOrderHold.hpp"
#include "analysis/BilinearTransformation.hpp"

#include <iostream>

/**
 * @brief A lunar lander control demo.
 * @ingroup examples_module
 *
 * @details Illustrates use of ls::systems::StateSpace<>, ls::analysis::ZeroOrderHold,
 * ls::analysis::BilinearTransformation, and ls::control::DiscreteLQR.
*/
void lunarLanderDemo()
{
    double xArray[13];
    double uArray[13] = {1e-3, 1e-3, 1e-3, 1e-3, 1e-3, 1e-3, 1e-3, 1e-3, 1e-3, 1e-3, 1e-3, 1e-3, 1e-3};

    Eigen::Matrix<double, 13, 1> x, x0, X;
    x.setZero();
    x << 1e-3,1e-3,1e-3,0,0,0,0,0,1,0,0,0,0;
    X = x;
    x0 = x;

    Eigen::Matrix<double, 13, 1> Xdes;
    Xdes.setZero();
    Xdes << 0.1,0.1,0.1,0,0,0,0,0,1,0,0,0,0;

    Eigen::Matrix<double, 13, 1> u, u0, U;
    u.setZero();

    for (int j = 0; j < 13; j++) {
        xArray[j] = X(j);
    }

//    Eigen::Map<Eigen::Matrix<double, 13, 1>>(xArray, 13, 1) = X;

    auto A = jac6DOFStates(xArray, uArray);
    auto B = jac6DOFInputs(xArray, uArray);

    double dt = 0.1;

    ls::systems::StateSpace<> ss(A, B, Eigen::Matrix<double, 13, 13>::Identity(), Eigen::Matrix<double, 13, 13>::Zero());
    auto dss = ls::analysis::ZeroOrderHold::c2d(ss, dt);

    std::cout << "Continuous time system\nA:\n" << (ss.getA()) << "\nB:\n" << (ss.getB()) << "\nC:\n" << (ss.getC())
              << "\nD:\n" << (ss.getD()) << std::endl;
    std::cout << "\nDiscrete time system\nA:\n" << (dss.getA()) << "\nB:\n" << (dss.getB()) << "\nC:\n"
              << (dss.getC()) << "\nD:\n" << (dss.getD()) << std::endl;

    Eigen::Matrix<double, 13, 13> Q;
    Eigen::Matrix<double, 13, 13> R;

    Eigen::Matrix<double, 13, 1> q;
    q << 80, 80, 85,
            1, 1, 1,
            1, 1, 1, 1,
            1, 1, 1;

    /*
     * REGULATION
     *     X
     *               O
     *
     * TRACKING
     *     X
     *               O
     *
     *            XDes
     */

    Q = q.asDiagonal();

    Eigen::Matrix<double, 13, 1> r;
    r << 0.01,
            30, 30, 30,
            30, 30, 30,
            30, 30, 30,
            30, 30, 30;
    R = 0.1 * (r).asDiagonal();

    auto K = ls::control::DiscreteLQR::finiteHorizon(dss, Q, R, 75);
    std::cout << "\nLQR Feedback Fixed Gain:\n" << K << std::endl;

    std::cout << "x at 0 sec:\n" << x << std::endl;

    int N = 100;
    for (int i = 0; i < N; i++) {
//        std::cout << "((x - x0) - (xdes - x0)):\n" << ((x - x0) - (xdes - x0)) << std::endl;
//        u = -K * (X - x0);
        U = -K * (X - Xdes);
//        U = u0 + u;

        X = (dss.getA()) * X + (dss.getB()) * U;
//        X = x0 + x;

//        Eigen::Map<Eigen::Matrix<double, 13, 1>>(xArray, 13, 1) = X;
//        Eigen::Map<Eigen::Matrix<double, 13, 1>>(uArray, 13, 1) = U;

        for (int j = 0; j < 13; j++) {
            xArray[j] = X(j);
            uArray[j] = U(j);
        }

        // Linearize
        A = jac6DOFStates(xArray, uArray);
        B = jac6DOFInputs(xArray, uArray);
        ss.setA(A);
        ss.setB(B);
        x0 = X;
        u0 = U;

        // Discretize
        // dss = ls::analysis::ZeroOrderHold::c2d(ss, dt);
        dss = ls::analysis::BilinearTransformation::c2d(ss, dt);

        // LQR
        K = ls::control::DiscreteLQR::finiteHorizon(dss, Q, R, 75);

        std::cout << "X at " << (i + 1) * dss.getSamplingPeriod() << " sec:" << std::endl;
        std::cout << X << std::endl;

        std::cout << "U at " << (i + 1) * dss.getSamplingPeriod() << " sec:" << std::endl;
        std::cout << U << std::endl;
    }
}