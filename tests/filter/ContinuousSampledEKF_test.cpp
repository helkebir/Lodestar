//
// Created by Hamza El-Kebir on 6/25/21.
//

#include "catchOnce.hpp"
#include "Lodestar/filter/ContinuousSampledEKF.hpp"
#include <cmath>
#include "CartPoleAuxFunctions.hpp"

#include <iostream>

TEST_CASE("Continuous sampled extended Kalman filter", "[filter][ekf]")
{
    typedef ls::filter::ContinuousSampledEKF::EKFParameters<ls::filter::ContinuousSampledEKF::integrators::RungeKuttaFehlberg78, double, 4, 1, 2> TDEkf;
    TDEkf param;

    // Cart-pole system without friction:
    // R. V. Florian (2007), Correct equations for the dynamics of the cart-pole system.
    // Eqs. 23, 24.
    double mCart = 1.5;
    double mPole = 0.25;
    double g = 9.80665;
    double l = 0.4;

    // Output returns linear and angular velocity
    TDEkf::TDOutputMatrix C;
    C.setZero();
    C(0, 1) = 1;
    C(1, 3) = 1;

    TDEkf::TDOde ode = [g, l, mCart, mPole](double t, const TDEkf::TDStateVector &x, const TDEkf::TDInputVector &u) {
        TDEkf::TDStateVector xdot;
        xdot(0) = x(1);
        xdot(2) = x(3);
        xdot(3) = (g * sin(x(2)) + cos(x(2)) * ((-u(0) - mPole * l * x(3) * x(3) * sin(x(2))) / (mCart + mPole))) /
                  (l * (4.0 / 3.0 - (mPole * cos(x(2)) * cos(x(2))) / (mCart + mPole)));

        xdot(1) = (u(0) + mPole * l * (x(3) * x(3) * sin(x(2) - xdot(3) * cos(x(2))))) / (mCart + mPole);

        return xdot;
    };

    TDEkf::TDOutputJacobian outputJacobian = [&] (const TDEkf::TDStateVector &x)
    {
        return C;
    };

    TDEkf::TDOutputMap outputMap = [&] (const TDEkf::TDStateVector &x)
    {
        return C * x;
    };

    TDEkf::TDProcessCovarianceMatrix Q;
    Q.setIdentity();
    Q *= 0.05;
    TDEkf::TDObservationCovarianceMatrix R;
    R.setIdentity();
    R *= 0.2;

    TDEkf::TDStateVector x0;
    x0.setZero();
    x0.array() += 1e-3;

    TDEkf::TDStateMatrix P0;
    P0.setIdentity();
    P0 *= 0.1;
    P0.array() += 0.01;

    param.initParams(x0, P0);
    param.initEquations(ode, std::bind(cartPoleStateJacobian, std::placeholders::_1, std::placeholders::_2, 0), outputJacobian, outputMap);

    TDEkf::TDInputVector u0;
    u0.setZero();
    u0.array() += 0.1;

    TDEkf::TDStateVector xout;
    xout = x0;

    TDEkf::TDOdeFunc func = [&](TDEkf::scalar_type t, const TDEkf::TDStateVector &x)
    {
        return ode(t, x, u0);
    };
    double t = 0;
    double h = 0.1;

//    for (int i = 0; i < 10; i++) {
//        ls::primitives::RungeKuttaFehlberg78<TDEkf::TDStateVector, TDEkf::scalar_type>::integrateSimple(func, t, xout,
//                                                                                                        h, 1);
//
//        std::cout << "State after t = " << t << ": " << xout << std::endl;
//    }
//
//    TDEkf::TDOutputVector z0;
//    z0.setZero();
//    z0.array() += 0.05;
//
//    param.step(u0, z0, 0.5);
//
//    std::cout << "State estimate at t = " << param.getCurrentTime() << ": " << param.getStateEstimate() << std::endl;
}