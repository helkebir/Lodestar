//
// Created by helkebir on 6/17/21.
//

#include "catchOnce.hpp"
#include "systems/StateSpace.hpp"
#include "analysis/BilinearTransformation.hpp"
#include "analysis/ZeroOrderHold.hpp"
#include "symbolic/OrdinaryDifferentialEquation.hpp"
#include "control/DiscreteLQR.hpp"

#include "CarDemoFunctions.hpp"

#include <iostream>

TEST_CASE("Car demo", "[demo]")
{
    GiNaC::symbol x{"_s_x_"}, y{"_s_y_"},
            vx{"_s_vx_"}, vy{"_s_vy_"},
            psi("_s_psi_"), r("_s_r_");

    GiNaC::symbol m("_s_m_"), Iz("_s_Iz_"), b1("_s_b1_"), b2("_s_b2_"), w("_s_w_");

    GiNaC::ex mEx = m;
    GiNaC::ex IzEx = Iz;
    GiNaC::ex wEx = w;

    mEx = 1;
    IzEx = 1;
    wEx = 1;

    GiNaC::symbol f1("_s_f1_"), f2("_s_f2_");

    GiNaC::lst odeFunc = {
            vx,
            ((f1 + f2) * GiNaC::cos(psi) + (f2 + f1) * GiNaC::cos(psi)) / mEx,
            vy,
            (-(f1 + f2) * GiNaC::sin(psi) - (f2 + f1) * GiNaC::sin(psi)) / mEx,
            r,
            ((f1 - f2) * wEx / 2 + (-f2 + f1) * wEx / 2) / IzEx
    };

    GiNaC::lst stateArgs = {x, y, vx, vy, psi, r};
    GiNaC::lst inputArgs = {f1, f2};

    ls::symbolic::OrdinaryDifferentialEquation ode;
    ode.setFunctions(odeFunc);
    ode.setStates(stateArgs);
    ode.setInputs(inputArgs);

    std::cout << "CAR DEMO" << std::endl;
    std::cout << ode.generateJacobianStatesArrayInputCppFunc("jacStates") << std::endl;
    std::cout << std::endl;
    std::cout << ode.generateJacobianInputsArrayInputCppFunc("jacInput") << std::endl;
}

TEST_CASE("Car control demo", "[demo]") {
    auto ss = ls::systems::StateSpace<>{};

    double dt = 0.1;

    double xArray[6];
    double uArray[2];

    Eigen::Matrix<double, 6, 1> x;
    Eigen::Matrix<double, 2, 1> u;

    x << -5, 1e-3, -2, 1e-3, 1e-3, 1e-3;
    u << 1e-3, 1e-3;

    for (int j = 0; j < 6; j++)
        xArray[j] = x(j);

    for (int j = 0; j < 2; j++)
        uArray[j] = u(j);

    auto A = jacStates(xArray, uArray);
    auto B = jacInput(xArray, uArray);

    ss.setA(A);
    ss.setB(B);
    ss.setC(Eigen::Matrix<double, 6, 6>::Identity());
    ss.setD(Eigen::Matrix<double, 6, 2>::Zero());

    auto dss = ls::analysis::BilinearTransformation::c2d(ss, dt);

    std::cout << "A matrix" << std::endl;
    std::cout << *ss.getA() << std::endl;
    std::cout << "\n";
    std::cout << "B matrix" << std::endl;
    std::cout << *ss.getB() << std::endl;

    std::cout << "\n";

    std::cout << "Ad matrix" << std::endl;
    std::cout << *dss.getA() << std::endl;
    std::cout << "\n";
    std::cout << "Bd matrix" << std::endl;
    std::cout << *dss.getB() << std::endl;

    auto Q = Eigen::Matrix<double, 6, 6>::Identity();
    auto R = Eigen::Matrix<double, 2, 2>::Identity();

    auto K = ls::control::DiscreteLQR::finiteHorizon(dss, Q, R, 500);

    std::cout << "K:\n" << K << std::endl;

    int N = 1000;

    Eigen::Matrix<double, 6, 1> X = x;
    Eigen::Matrix<double, 2, 1> U = u;

    for (int i = 0; i < N; i++) {
        u = -K * x;
        X += x;

        for (int j = 0; j < 6; j++)
            xArray[j] = X(j);

        for (int j = 0; j < 2; j++)
            uArray[j] = U(j) + u(j);

        A = jacStates(xArray, uArray);
        B = jacInput(xArray, uArray);

        ss.setA(A);
        ss.setB(B);
        dss = ls::analysis::BilinearTransformation::c2d(ss, dt);

        K = ls::control::DiscreteLQR::finiteHorizon(dss, Q, R, 75);

        x = *dss.getA() * x + *dss.getB() * u;

        std::cout << "Time is " << i * dss.getSamplingPeriod() << std::endl;
        std::cout << "X:\n" << x << std::endl;
    }
}