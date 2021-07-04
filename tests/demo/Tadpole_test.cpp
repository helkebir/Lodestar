//
// Created by helkebir on 6/27/21.
//

#include "catchOnce.hpp"

#include "symbolic/OrdinaryDifferentialEquation.hpp"
#include "systems/StateSpace.hpp"
#include "control/DiscreteLQR.hpp"
#include "analysis/BilinearTransformation.hpp"
#include "analysis/ZeroOrderHold.hpp"

#include "TadpoleFunctions.hpp"

#include <fstream>

TEST_CASE("Tadpole ODE", "[demo]")
{
    using GiNaC::cos;
    using GiNaC::sin;

    GiNaC::symbol x{"_s_x_"}, y{"_s_y_"}, phi("_s_phi_");

    GiNaC::symbol r("_s_r_"), d("_s_d_");

    GiNaC::ex rEx = r;
    GiNaC::ex dEx = d;

//    rEx = 0.035;
//    dEx = 0.135;

    GiNaC::symbol uL("_s_ul_"), uR("_s_ur_");

    GiNaC::lst odeFunc = {
            (rEx/2) * cos(phi) * (uL + uR),
            (rEx/2) * sin(phi) * (uL + uR),
            ((rEx/2) * dEx) * (-uL + uR)
    };

    GiNaC::lst stateArgs = {x, y, phi};
    GiNaC::lst inputArgs = {uL, uR};

    ls::symbolic::OrdinaryDifferentialEquation ode;
    ode.setFunctions(odeFunc);
    ode.setStates(stateArgs);
    ode.setInputs(inputArgs);

    std::cout << "CAR DEMO" << std::endl;
    std::cout << ode.generateJacobianStatesArrayInputCppFunc("tadpoleJacStates") << std::endl;
    std::cout << std::endl;
    std::cout << ode.generateJacobianInputsArrayInputCppFunc("tadpoleJacInput") << std::endl;
}

TEST_CASE("Tadpole LQR", "[demo]")
{
    ls::systems::StateSpace<> ss, dss, dssi;
    ss.setC(Eigen::Matrix<double, 3, 3>::Identity());
    ss.setD(Eigen::Matrix<double, 3, 2>::Zero());

    typedef Eigen::Matrix<double, 3, 1> TDStateVector;
    typedef Eigen::Matrix<double, 6, 1> TDStateVectorIntegral;
    typedef Eigen::Matrix<double, 3, 3> TDStateMatrix;
    typedef Eigen::Matrix<double, 2, 1> TDInputVector;
    typedef Eigen::Matrix<double, 3, 2> TDInputMatrix;

    TDStateVector x, xdes;
    TDInputVector u;
    u.setZero();
    u.array() += 1e-3;


    x << 1e-3,1e-3,1e-3;
    xdes << 5.0, 0.25, atan(0.25/5.0);

    TDStateMatrix A;
    TDInputMatrix B;

    double dt = 0.1;

    A = tadpoleJacStates(x, u);
    B = tadpoleJacInput(x, u);

    ss.setA(A);
    ss.setB(B);

    Eigen::Matrix<double, 3, 3> Q;
    Eigen::Matrix<double, 6, 6> Qi;
    Eigen::Matrix<double, 2, 2> R;
    Eigen::Matrix<double, 2, 3> K;
    Eigen::Matrix<double, 2, 6> Ki;

    Eigen::Matrix<double, 3, 1> q;
    Eigen::Matrix<double, 6, 1> qi;
    Eigen::Matrix<double, 2, 1> r;

    q << 5, 5, 5;
    r << 1e-1, 1e-1;

    Q = q.asDiagonal();
    Qi = qi.asDiagonal();
    R = r.asDiagonal();

    dss = ls::analysis::BilinearTransformation::c2d(ss, dt);
    K = ls::control::DiscreteLQR::finiteHorizon(dss, Q, R, 75);

    std::ofstream xrec("xvalrec.txt");
    std::ofstream yrec("yvalrec.txt");
    std::ofstream phirec("phirec.txt");
    std::ofstream uLrec("uLrec.txt");
    std::ofstream uRrec("uRrec.txt");

    int N = 10;
    for (int i = 0; i < N; i++) {
        u = -K * (x - xdes);

        x = (*dss.getA()) * x + (*dss.getB()) * u;

        xrec << (i+1) * dt << " " << x(0) << "\n";
        yrec << (i+1) * dt << " " << x(1) << "\n";
        phirec << (i+1) * dt << " " << x(2) << "\n";
        uLrec << (i+1) * dt << " " << u(0) << "\n";
        uRrec << (i+1) * dt << " " << u(1) << "\n";

        // Linearize
        A = tadpoleJacStates(x, u);
        B = tadpoleJacInput(x, u);
        ss.setA(A);
        ss.setB(B);

        // Discretize
//        dss = ls::analysis::ZeroOrderHold::c2d(ss, dt);
        dss = ls::analysis::BilinearTransformation::c2d(ss, dt);

        // LQR
        K = ls::control::DiscreteLQR::finiteHorizon(dss, Q, R, 150);

        std::cout << "x at " << (i + 1) * dss.getSamplingPeriod() << " sec:" << std::endl;
        std::cout << x << std::endl;

        std::cout << "u at " << (i + 1) * dss.getSamplingPeriod() << " sec:" << std::endl;
        std::cout << u << std::endl;
    }
}