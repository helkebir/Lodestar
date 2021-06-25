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
#include <fstream>

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

    double dt = 1e-1;

    double xArray[6];
    double uArray[2];

    Eigen::Matrix<double, 6, 1> x;
    Eigen::Matrix<double, 2, 1> u;

    x << -1, 1e-2, -1, 1e-2, 1e-2, 1e-2;
    u << 1e-2, 1e-2;

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

    Eigen::Matrix<double, 6, 6> Q = Eigen::Matrix<double, 6, 6>::Identity();
    Q(0,0) = 1e2;
    Q(1,1) = 1e-1;
    Q(2,2) = 1e2;
    Q(3,3) = 1e-1;
    Q(4,4) = 1e-3;
    Q(5,5) = 1e-3;
    Eigen::Matrix<double, 2, 2> R = 0.1 * Eigen::Matrix<double, 2, 2>::Identity();

    auto K = ls::control::DiscreteLQR::finiteHorizon(dss, Q, R, 150);

    std::cout << "K:\n" << K << std::endl;

    int N = 500;

    Eigen::Matrix<double, 6, 1> X = x;
    Eigen::Matrix<double, 2, 1> U = u;

    std::ofstream xrec("Xrec.txt");
    std::ofstream yrec("Yrec.txt");
    std::ofstream vxrec("vxrec.txt");
    std::ofstream vyrec("vyrec.txt");
    std::ofstream psirec("psirec.txt");
    std::ofstream rrec("rrec.txt");

    std::ofstream f1rec("f1rec.txt");
    std::ofstream f2rec("f2rec.txt");
//    for (int u = 0; u < N; ++u) {
//        xrec << freq(u) << " " << std::abs(f_freq(u)) << "\n";
//        yrec << time(u) << " " << t_values(u) << "\n";
//    }

    double h = dss.getSamplingPeriod();

//    x.setZero();
//    x.array() += 1e-3;
//    u.setZero();
//    u.array() += 1e-3;

//    K.setZero();
    auto ssi = ss.addIntegralAction();
    auto dssi = ls::analysis::BilinearTransformation::c2d(ssi, dt);

    std::cout << "Ai matrix" << std::endl;
    std::cout << *ssi.getA() << std::endl;
    std::cout << "\n";
    std::cout << "Bi matrix" << std::endl;
    std::cout << *ssi.getB() << std::endl;
    std::cout << "Ci matrix" << std::endl;
    std::cout << *ssi.getC() << std::endl;
    std::cout << "\n";
    std::cout << "Di matrix" << std::endl;
    std::cout << *ssi.getD() << std::endl;
    std::cout << "\n";

    Eigen::Matrix<double, 12, 12> Qi = 1e-5 * Eigen::Matrix<double, 12, 12>::Identity();
    Qi(0,0) = 1e2;
    Qi(1,1) = 1e-1;
    Qi(2,2) = 1e2;
    Qi(3,3) = 1e-1;
    Qi(4,4) = 1e-3;
    Qi(5,5) = 1e-3;
    Eigen::Matrix<double, 2, 2> Ri = 1e5 * Eigen::Matrix<double, 2, 2>::Identity();

    auto Ki = ls::control::DiscreteLQR::finiteHorizon(dssi, Qi, Ri, 150);


    Eigen::Matrix<double, 6, 1> Xdes;
    Xdes.setZero();
    Xdes << 0.2, 0, 0.2, 0, 45.0 * M_PI / 180.0, 0;

    for (int i = 0; i < N; i++) {
        std::cout << "Time is " << i * h << std::endl;

//        std::cout << "K:\n" << K << std::endl;

        u = -K * (x - Xdes);

        x = *dss.getA() * x + *dss.getB() * u;

        std::cout << "x:\n" << x.transpose() << std::endl;
        std::cout << "u:\n" << u.transpose() << std::endl;
    }

    Eigen::Matrix<double, 12, 1> xi;
    xi.setZero();
    xi.topRows(6) = X;

    Eigen::Matrix<double, 6, 1> y = X;
    Eigen::Matrix<double, 6, 1> r = Xdes;

    std::cout << "Ki:\n" << Ki << std::endl;

    for (int i = 0; i < N; i++) {
        std::cout << "Time is " << i * h << std::endl;

//        std::cout << "K:\n" << K << std::endl;

        u = -Ki * xi;

        xi = *dssi.getA() * xi + *dssi.getB() * u;
        x = *dss.getA() * x + *dss.getB() * u;
        xi.topRows(6) = x;

        xrec << (i+1) * dt << " " << xi(0) << "\n";
        vxrec << (i+1) * dt << " " << xi(1) << "\n";
        yrec << (i+1) * dt << " " << xi(2) << "\n";
        vyrec << (i+1) * dt << " " << xi(3) << "\n";
        psirec << (i+1) * dt << " " << xi(4) << "\n";
        rrec << (i+1) * dt << " " << xi(5) << "\n";

        f1rec << (i+1) * dt << " " << u(0) << "\n";
        f2rec << (i+1) * dt << " " << u(1) << "\n";

        std::cout << "xi:\n" << xi.topRows(6).transpose() << std::endl;
        std::cout << "u:\n" << u.transpose() << std::endl;
    }

//    x.setZero();
//    u.setZero();
//
//    Eigen::Matrix<double, 6, 1> Xdes;
//    Xdes.setZero();
//    Xdes << 0.2, 0, 0.2, 0, 0, 0;
//
////    for (int j = 0; j < 6; j++)
////        xArray[j] = X(j);
//
//    for (int j = 0; j < 2; j++)
//        uArray[j] = U(j);
//
//    int bufferMax = 0;
//    int buffer = bufferMax;
//
//    for (int i = 0; i < N; i++) {
////        std::cout << "Time is " << i * h << std::endl;
//
//        for (int j = 0; j < 6; j++)
//            xArray[j] = X(j);
//
//        for (int j = 0; j < 2; j++)
//            uArray[j] = U(j);
//
//        A = jacStates(xArray, uArray);
//        B = jacInput(xArray, uArray);
//
//        ss.setA(A);
//        ss.setB(B);
//        dss = ls::analysis::BilinearTransformation::c2d(ss, dt);
//
//        if (buffer == bufferMax) {
//            K = ls::control::DiscreteLQR::finiteHorizon(dss, Q, R, 250);
//            buffer = 0;
//        } else {
//            buffer++;
//        }
//
////        std::cout << "K:\n" << K << std::endl;
//
//        u = -K * (X - Xdes);
//
//        x = *dss.getA() * X + *dss.getB() * u;
//
//        U = u;
//        X = x;
////        X += dt * dynamics(xArray, uArray) + dt * B * u;
//
////        std::cout << "x:\n" << x.transpose() << std::endl;
////        std::cout << "u:\n" << u.transpose() << std::endl;
//
//        xrec << (i+1) * dt << " " << X(0) << "\n";
//        vxrec << (i+1) * dt << " " << X(1) << "\n";
//        yrec << (i+1) * dt << " " << X(2) << "\n";
//        vyrec << (i+1) * dt << " " << X(3) << "\n";
//        psirec << (i+1) * dt << " " << X(4) << "\n";
//        rrec << (i+1) * dt << " " << X(5) << "\n";
//
//        f1rec << (i+1) * dt << " " << U(0) << "\n";
//        f2rec << (i+1) * dt << " " << U(1) << "\n";
//
//        x.setZero();
//        u.setZero();
////        std::cout << "X:\n" << X.transpose() << std::endl;
////        std::cout << "U:\n" << U.transpose() << std::endl;
//    }
}