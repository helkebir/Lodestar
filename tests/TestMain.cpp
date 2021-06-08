//
// Created by Hamza El-Kebir on 5/19/21.
//

#define CATCH_CONFIG_MAIN
#include "catchOnce.hpp"

#ifdef LS_USE_GINAC

#include "ginac/ginac.h"
#include "symbolic/OrdinaryDifferentialEquation.hpp"

#endif

#include <iostream>
#include "TestAuxFunctions.hpp"
#include "control/DiscreteLQR.hpp"
#include "analysis/ZeroOrderHold.hpp"

TEST_CASE("Leapfrog", "") {
    Eigen::Matrix<double, 4, 3> P;
    P << -0.512312, 0, 0.280913,
            0, -0512312, 0.287097,
            0.512312, 0, 0.285137,
            0, 0.512312, 0.289119;

    Eigen::Vector3d Ivec;
    Ivec << 1.81006, 2.83132, 1.90705;

    double m = 21.544178;

    ls::symbolic::OrdinaryDifferentialEquation ode{};

    // 6 states
    auto x = GiNaC::symbol("x");
    auto y = GiNaC::symbol("y");
    auto z = GiNaC::symbol("z");
    auto roll = GiNaC::symbol("R");
    auto pitch = GiNaC::symbol("P");
    auto yaw = GiNaC::symbol("Y");

    // 13 inputs
    auto Fth = GiNaC::symbol("Fth");
    auto Fpox = GiNaC::symbol("Fpox");
    auto Fpoy = GiNaC::symbol("Fpoy");
    auto Fpoz = GiNaC::symbol("Fpoz");
    auto Fsbx = GiNaC::symbol("Fsbx");
    auto Fsby = GiNaC::symbol("Fsby");
    auto Fsbz = GiNaC::symbol("Fsbz");
    auto Fstx = GiNaC::symbol("Fstx");
    auto Fsty = GiNaC::symbol("Fsty");
    auto Fstz = GiNaC::symbol("Fstz");
    auto Fbox = GiNaC::symbol("Fbox");
    auto Fboy = GiNaC::symbol("Fboy");
    auto Fboz = GiNaC::symbol("Fboz");

    ode.setStates(GiNaC::lst{
        x, y, z,
        roll, pitch, yaw
    });
    ode.setInputs(GiNaC::lst{
        Fth,
        Fpox, Fpoy, Fpoz,
        Fsbx, Fsby, Fsbz,
        Fstx, Fsty, Fstz,
        Fbox, Fboy, Fboz
    });

    // z-y'-x" intrinsic Tait-Brian rotation matrix.
    using GiNaC::cos;
    using GiNaC::sin;
    auto Rmat = GiNaC::lst{
        GiNaC::lst{cos(pitch) * cos(yaw), - cos(roll) * sin(yaw) + sin(roll) * sin(pitch) * cos(yaw), sin(roll) * sin(yaw) + cos(roll) * sin(pitch) * cos(yaw)},
        GiNaC::lst{cos(pitch) * sin(yaw), cos(roll) * cos(yaw) + sin(roll) * sin(pitch) * sin(yaw), -sin(roll) * cos(yaw) + cos(roll) * sin(pitch) * sin(yaw)},
        GiNaC::lst{-sin(pitch), sin(roll) * cos(pitch), cos(roll) * cos(pitch)}
    };

    auto Rmat0 = Rmat[0];
    auto Rmat1 = Rmat[1];
    auto Rmat2 = Rmat[2];

    ode.setFunctions(GiNaC::lst{
        (Rmat0[0] * (Fpox + Fsbx + Fstx + Fbox) + Rmat0[1] * (Fpoy + Fsby + Fsty + Fboy) + Rmat0[2] * (Fpoz + Fsbz + Fstz + Fboz + Fth)) / m,
        (Rmat1[0] * (Fpox + Fsbx + Fstx + Fbox) + Rmat1[1] * (Fpoy + Fsby + Fsty + Fboy) + Rmat1[2] * (Fpoz + Fsbz + Fstz + Fboz + Fth)) / m,
        (Rmat2[0] * (Fpox + Fsbx + Fstx + Fbox) + Rmat2[1] * (Fpoy + Fsby + Fsty + Fboy) + Rmat2[2] * (Fpoz + Fsbz + Fstz + Fboz + Fth)) / m,
        Rmat0[0] * (Fsbz * P(1,1) + Fboz * P(3, 1)) / Ivec[0] +
            Rmat0[1] * (Fpoz * P(0,0) + Fstz * P(2, 0)) / Ivec[1] +
            Rmat0[2] * (Fpoy * abs(P(0, 0)) + Fsbx * P(1, 1) + Fsty * P(2, 0) + Fbox * P(3, 1)) / Ivec[2],
        Rmat1[0] * (Fsbz * P(1,1) + Fboz * P(3, 1)) / Ivec[0] +
            Rmat1[1] * (Fpoz * P(0,0) + Fstz * P(2, 0)) / Ivec[1] +
            Rmat1[2] * (Fpoy * abs(P(0, 0)) + Fsbx * P(1, 1) + Fsty * P(2, 0) + Fbox * P(3, 1)) / Ivec[2],
        Rmat2[0] * (Fsbz * P(1,1) + Fboz * P(3, 1)) / Ivec[0] +
            Rmat2[1] * (Fpoz * P(0,0) + Fstz * P(2, 0)) / Ivec[1] +
            Rmat2[2] * (Fpoy * abs(P(0, 0)) + Fsbx * P(1, 1) + Fsty * P(2, 0) + Fbox * P(3, 1)) / Ivec[2]
    });

    std::cout << "ODE" << std::endl;
    std::cout << GiNaC::latex << ode.getFunctions() << GiNaC::dflt << std::endl;
    std::cout << "Jacobian of states" << std::endl;
    std::cout << ode.generateJacobianStatesArrayInputCppFunc("jacStates") << std::endl;
    std::cout << "Jacobian of inputs" << std::endl;
    std::cout << ode.generateJacobianInputsArrayInputCppFunc("jacStates") << std::endl;

//    ls::systems::StateSpace<double, 6, 13> ss;
}

TEST_CASE("Temporary main", "")
{
    std::cout << "Test main" << std::endl;

#ifdef LS_USE_GINAC
    {
        GiNaC::symbol z("z");
        GiNaC::symbol w("w");
        GiNaC::symbol v("v");
        GiNaC::exmap xmap;
        xmap[z] = 2;
        std::cout << "5 <= 6 : " << (bool) GiNaC::relational(5, 6, GiNaC::relational::operators::less_or_equal)
                  << std::endl;
        std::cout << "z <= z+2 : " << (bool) GiNaC::relational(z, z + 2, GiNaC::relational::operators::less_or_equal)
                  << std::endl;
        std::cout << "z^2 <= z^3 : " << (bool) GiNaC::ex_to<GiNaC::relational>(
                GiNaC::relational(GiNaC::pow(z, 2), GiNaC::pow(z, 3), GiNaC::relational::operators::less_or_equal).subs(
                        xmap)) << std::endl;
        std::cout << GiNaC::series_to_poly(GiNaC::exp(z).series(z == 0, 3)) << std::endl;

        GiNaC::exset xset;
        GiNaC::ex xpression = (w - z + GiNaC::cos(z + 2) - z * z);
        std::cout << xpression << std::endl;
        std::cout << GiNaC::csrc << xpression << std::endl;
        std::cout << GiNaC::dflt;
        std::cout << xpression.find(GiNaC::cos(GiNaC::wild(0)), xset) << std::endl;
//    std::cout << xpression.find((z - w + GiNaC::wildcard(1)), xset) << std::endl;
//    std::cout << xpression.find((w - z + GiNaC::wildcard(2)), xset) << std::endl;
        std::cout << xset << std::endl;
        xmap.clear();
        for (const auto &ex : xset)
            xmap[ex] = 1;

        xpression = GiNaC::expand(xpression).subs(xmap);
        xpression = xpression.subs(GiNaC::lst{GiNaC::wildcard(0) + w - z == GiNaC::wildcard(0) + v});
        xpression = xpression.subs(GiNaC::lst{GiNaC::wildcard(0) + GiNaC::pow(w - z, GiNaC::wildcard(1)) ==
                                              GiNaC::wildcard(0) + GiNaC::pow(v, GiNaC::wildcard(1))});
        std::cout << xpression << std::endl;

        ls::symbolic::OrdinaryDifferentialEquation ode{};
        ode.setStates(GiNaC::lst{GiNaC::symbol("x0"), GiNaC::symbol("x1"), GiNaC::symbol("x2")});
        ode.setFunctions(GiNaC::lst{
                ode.getStateSymbol(0) * ode.getStateSymbol(1) + ode.getStateSymbol(0) * ode.getInputSymbol(0),
                ode.getStateSymbol(1) * ode.getStateSymbol(1) + ode.getStateSymbol(1) * ode.getInputSymbol(0),
                ode.getStateSymbol(0) * ode.getStateSymbol(1) * ode.getStateSymbol(2) +
                ode.getStateSymbol(2) * ode.getInputSymbol(0)});

//        std::cout << lst_to_vector(ode.getFunctions())(0,0) << std::endl;
//        std::cout << GiNaC::series_to_poly(ode.getFunctions().op(0).series(ode.getStateSymbol(0)==0, 2)) << std::endl;
//        std::cout << GiNaC::series_to_poly(lst_to_vector(ode.getFunctions()).series(ode.getStateSymbol(0)==0, 3).evalm()) << std::endl;


        auto exmap = ode.generateExpressionMap(std::vector<double>{2, 4, 6}, std::vector<double>{3});

        std::cout << exmap << std::endl;

        std::cout << "Functions" << std::endl;
        std::cout << ode.getFunctions() << std::endl;
        std::cout << "Jacobian of states" << std::endl;
        std::cout << ode.generateJacobianStates() << std::endl;
        std::cout << ode.generateJacobianStatesCppFunc("jacStates") << std::endl;
        std::cout << ode.generateJacobianStatesCppFunc("jacStates", true) << std::endl;
        std::cout << ode.generateJacobianStatesArrayInputCppFunc("jacStatesArray") << std::endl;
        std::cout << ode.generateJacobianStatesArrayInputCppFunc("jacStatesArray", true) << std::endl;
        std::cout << "Jacobian of inputs" << std::endl;
        std::cout << ode.generateJacobianInputs() << std::endl;
        std::cout << ode.generateJacobianInputsCppFunc("jacInputs") << std::endl;
        std::cout << ode.generateJacobianInputsCppFunc("jacInputs", true) << std::endl;
        std::cout << ode.generateJacobianInputsArrayInputCppFunc("jacInputsArray") << std::endl;
        std::cout << ode.generateJacobianInputsArrayInputCppFunc("jacInputsArray", true) << std::endl;
        std::cout << "Jacobian of states with substitution" << std::endl;
        std::cout << ode.generateJacobianMatrix(ode.generateJacobianStates(), exmap) << std::endl;

        auto jacStates = ode.generateJacobianStates();
        auto jacInputs = ode.generateJacobianInputs();

        auto ss = ode.linearize(jacStates, jacInputs, std::vector<double>{2, 4, 6}, std::vector<double>{3});
        std::cout << "Linearize ODE about x0=2, x1=4, x2=6, u=3:" << std::endl;
        std::cout << "A" << std::endl << *ss.getA() << std::endl;
        std::cout << "B" << std::endl << *ss.getB() << std::endl;
        std::cout << "C" << std::endl << *ss.getC() << std::endl;
        std::cout << "D" << std::endl << *ss.getD() << std::endl;

//    // FIXME: Fix casting problem here.
//    ss.copyMatrices(ode.linearize(jacStates, jacInputs, std::vector<double>{3}, std::vector<double>{5}));
//    std::cout << "Linearize ODE about x=3, u=5:" << std::endl;
//    std::cout << "A" << std::endl << *ss.getA() << std::endl;
//    std::cout << "B" << std::endl << *ss.getB() << std::endl;
//    std::cout << "C" << std::endl << *ss.getC() << std::endl;
//    std::cout << "D" << std::endl << *ss.getD() << std::endl;

        auto dss = ls::analysis::ZeroOrderHold::c2d(ss, 0.1);
        std::cout << "Discretized at 0.1 s ZOH" << std::endl;
        std::cout << "Ad" << std::endl << *dss.getA() << std::endl;
        std::cout << "Bd" << std::endl << *dss.getB() << std::endl;
        std::cout << "Cd" << std::endl << *dss.getC() << std::endl;
        std::cout << "Dd" << std::endl << *dss.getD() << std::endl;

        std::cout << std::endl;

        GiNaC::symbol x("x"), y("y"), u("u");

        GiNaC::lst states{x, y};
        GiNaC::lst inputs{u};
        GiNaC::lst functions{x * x, y * x + u / 2};
        GiNaC::lst mat_lst{{GiNaC::lst{x * x, y * x}}};
        GiNaC::ex poly;

        for (int i = 1; i < 4; i++) {
            poly += GiNaC::pow(x, i) + GiNaC::pow(y, i) +
                    GiNaC::pow(x, i) * GiNaC::pow(y, i);
        }



//    std::cout << GiNaC::latex;
        GiNaC::exmap m;
        m[x] = 2;
        m[y] = 2;
        m[u] = 0;

//    std::cout << lst_to_vector(functions).series(x==1,3).evalm();
        GiNaC::symtab table;
        table["x"] = x;
        table["y"] = y;
        table["u"] = u;
        GiNaC::parser reader(table);
        GiNaC::ex funcs = reader("{x * x, y * x + u/2}");
        std::cout << GiNaC::ex_to<GiNaC::lst>(funcs) << std::endl;
//        std::cout << makeJacobian(states, functions) << std::endl;
//        std::cout << makeJacobian(states, functions).subs(m) << std::endl;
//        std::cout << matrix_to_MatrixXd(makeJacobian(states, functions).subs(m)) << std::endl;
//        std::cout << makeJacobian(inputs, functions) << std::endl;
//        std::cout << matrix_to_MatrixXd(makeJacobian(inputs, functions).subs(m)) << std::endl;

        std::cout << std::endl;

        std::cout << mat_lst << std::endl;
        GiNaC::matrix mat = GiNaC::ex_to<GiNaC::matrix>(
                GiNaC::lst_to_matrix(mat_lst));
        mat = mat.transpose();
        std::cout << mat(0, 0) << std::endl;
        std::cout << mat << std::endl;
        std::cout << mat.diff(GiNaC::ex_to<GiNaC::symbol>(states[0])) << std::endl;
        std::cout << mat(0, 0) << "; " << mat(1, 0) << std::endl;

        //    std::cout << GiNaC::latex;
        std::cout << poly << std::endl;
        std::cout << "Deriv wrt x, x=2, y=2 : "
                  << poly.diff(x).subs(GiNaC::lst{x == 2, y == 2}) << std::endl;

        GiNaC::matrix M = {{poly, poly.diff(x)}};
        std::cout << M << std::endl;
        GiNaC::matrix Mx = GiNaC::ex_to<GiNaC::matrix>(M.diff(x));
        std::cout << M.add(Mx) << std::endl;
    }
#endif
}

TEST_CASE("Linearize and discretize", "[example]") {
    std::cout << "=================================================" << std::endl << std::endl;
    ls::symbolic::OrdinaryDifferentialEquation ode{};

    // 2 states
    auto x = GiNaC::symbol("x");
    auto y = GiNaC::symbol("y");

    // 1 input
    auto u = GiNaC::symbol("u");

    ode.setStates(GiNaC::lst{
        x, y
    });

    ode.setInputs(GiNaC::lst{
        u
    });

    ode.setFunctions(GiNaC::lst{
        x*x + x*y + x*u + 0.2*u,
        y*y + 2*u
    });

    std::cout << "Functions: " << ode.getFunctions() << std::endl;
    std::cout << "// A(x, u)" << std::endl;
    std::cout << ode.generateJacobianStatesCppFunc("jacStates") << std::endl << std::endl;
    std::cout << "// B(x, u)" << std::endl;
    std::cout << ode.generateJacobianInputsCppFunc("jacInputs") << std::endl;

    auto A = jacStates(0, 0, 0, 0);
    auto B = jacInputs(0, 0, 0, 0);

    std::cout << "A((0, 0), 0)\n" << A << std::endl;
    std::cout << "B((0, 0), 0)\n" << B << std::endl;

    A = jacStates(1, 2, 3, 0);
    B = jacInputs(1, 2, 3, 0);

    std::cout << "A((1, 2), 3)\n" << A << std::endl;
    std::cout << "B((1, 2), 3)\n" << B << std::endl;

    ls::systems::StateSpace<> ss(A, B, Eigen::Matrix<double, 2, 2>::Identity(), Eigen::Matrix<double, 2, 1>::Zero());
    auto dss = ls::analysis::ZeroOrderHold::c2d(ss, 0.1);

    std::cout << "Continuous time system\nA:\n" << (*ss.getA()) << "\nB:\n" << (*ss.getB()) << "\nC:\n" << (*ss.getC()) << "\nD:\n" << (*ss.getD()) << std::endl;
    std::cout << "\nDiscrete time system\nA:\n" << (*dss.getA()) << "\nB:\n" << (*dss.getB()) << "\nC:\n" << (*dss.getC()) << "\nD:\n" << (*dss.getD()) << std::endl;

    Eigen::Matrix<double, 2, 2> Q;
    Eigen::Matrix<double, 1, 1> R;

    Q << 2, 0,
         0, 2;

    R << 1;

    auto K = ls::control::DiscreteLQR::finiteHorizon(dss, Q, R, 100);
    auto Kinf = ls::control::DiscreteLQR::infiniteHorizon(dss, Q, R);

    std::cout << "\nLQR Feedback Fixed Gain:\n" << K << std::endl;
    std::cout << "\nLQR Feedback Fixed Gain (inf):\n" << Kinf << std::endl;

    {
        Eigen::Matrix<double, 2, 1> x;
        x << 2, 4;

        std::cout << "x at 0 sec:\n" << std::endl;
        std::cout << x << std::endl;

        uint8_t N = 10;
        for (int i = 0; i < N; i++) {
            std::cout << "x at " << (i+1)*dss.getSamplingPeriod() << "sec:\n" << std::endl;
            x = (*dss.getA()) * x + (*dss.getB()) * (-K * x);
            std::cout << x << std::endl;
        }
    }
}