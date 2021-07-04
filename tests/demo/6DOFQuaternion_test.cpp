//
// Created by helkebir on 6/29/21.
//

#include "catchOnce.hpp"

#include "symbolic/OrdinaryDifferentialEquation.hpp"
#include "Eigen/Dense"

TEST_CASE("6-DOF with Quaternions", "[demo]")
{
    // 13 states
    GiNaC::symbol x{"_s_x_"}, y{"_s_y_"}, z{"_s_z_"},
            vx("_s_vx_"), vy("_s_vy_"), vz("_s_vz_"),
            qx("_s_qx_"), qy("_s_qy_"), qz("_s_qz_"), qw("_s_qw_"),
            p("_s_p_"), q("_s_q_"), r("_s_r_");

    // 13 inputs
    GiNaC::symbol Fth("_s_Fth_"),
        Fpox("_s_Fpox_"), Fpoy("_s_Fpoy_"), Fpoz("_s_Fpoz_"),
        Fsbx("_s_Fsbx_"), Fsby("_s_Fsby_"), Fsbz("_s_Fsbz_"),
        Fstx("_s_Fstx_"), Fsty("_s_Fsty_"), Fstz("_s_Fstz_"),
        Fbox("_s_Fbox_"), Fboy("_s_Fboy_"), Fboz("_s_Fboz_");

    GiNaC::ex m, g{9.80665};
    GiNaC::ex Ixx, Iyy, Izz;
    GiNaC::ex Fx, Fy, Fz, Mx, My, Mz;

    Eigen::Matrix<double, 5, 3> P;
    P << -0.512312, 0, 0.280913-0.3,
            0, -0.512312, 0.287097-0.3,
            0.512312, 0, 0.285137-0.3,
            0, 0.512312, 0.289119-0.3,
            0, 0, 0.3 - 0.22074;

    // Inertial parameters
    Ixx = 1.81006;
    Iyy = 2.83132;
    Izz = 1.90705;
    m = 21.544178;

    // Forces in body frame
    Fx = Fpox + Fsbx + Fstx + Fbox;
    Fy = Fpoy + Fsby + Fsty + Fboy;
    Fz = Fpoz + Fsbz + Fstz + Fboz + Fth;

    // Moments in body frame
//    Mx = Fsbz * P(1, 1) + Fboz * P(3, 1);
//    My = Fpoz * P(0, 0) + Fstz * P(2, 0);
//    Mz = Fpoy * abs(P(0, 0)) + Fsbx * P(1, 1) + Fsty * P(2, 0) + Fbox * P(3, 1);
    Mx = Fsbz * P(1, 1) + Fboz * P(3, 1) - Fpoy * P(0, 2) - Fsby * P(1,2) - Fsty * P(2,2) - Fboy * P(3,2);
    My = Fpoz * P(0, 0) + Fstz * P(2, 0) + Fpox * P(0, 2) + Fsbx * P(1,2) + Fstx * P(2,2) + Fbox * P(3,2);
    Mz = Fpoy * abs(P(0, 0)) + Fsbx * P(1, 1) + Fsty * P(2, 0) + Fbox * P(3, 1);


//    GiNaC::lst rQuat = {
//            (qw * Fx + Fy * qz - Fz * qy)/m,
//            (qw * Fy + Fz * qx - Fx * qz)/m,
//            (qw * Fz + Fx * qy - Fy * qx)/m,
//            (Fx * qx + Fy * qy + Fz * qz)/m
//    };
//
//    GiNaC::ex rx(rQuat[0]), ry(rQuat[1]), rz(rQuat[2]), rw(rQuat[3]);

    GiNaC::ex ax{Fx/m}, ay{Fy/m}, az{Fz/m};

//    GiNaC::ex axi = 2 * (qx * ax + qy * ay + qz * az) * qx + (qw * qw - (qx*qx + qy*qy + qz*qz)) * ax + 2 * qw * (qy * az - qz * ay);
    GiNaC::ex axi = 2 * (az * qw * qy + ay * qx * qy - ay * qw * qz + az * qx * qz) + ax * (qw*qw + qx*qx - qy*qy - qz*qz);
//    GiNaC::ex ayi = 2 * (qx * ax + qy * ay + qz * az) * qy + (qw * qw - (qx*qx + qy*qy + qz*qz)) * ay + 2 * qw * (qz * ax - qx * az);
    GiNaC::ex ayi = 2 * (-(az * qw * qx) + ax * qx * qy + ax * qw * qz + az * qy * qz) + ay * (qw*qw - qx*qx + qy*qy - qz*qz);
//    GiNaC::ex azi = 2 * (qx * ax + qy * ay + qz * az) * qz + (qw * qw - (qx*qx + qy*qy + qz*qz)) * az + 2 * qw * (qx * ay - qy * ax) - g;
    GiNaC::ex azi = 2 * (ay * qw * qx - ax * qw * qy + ax * qx * qz + ay * qy * qz) + az * (qw*qw - qx*qx - qy*qy + qz*qz) - g;


//    GiNaC::lst Finertial = {
//            qw * rx + rw * qx + qy * rz - qz * ry,
//            qw * ry + rw * qy + qz * rz - qx * rz,
//            qw * rz + rw * qz + qx * ry - qy * rz
//    };
//
//    GiNaC::ex Fxi{Finertial[0]}, Fyi{Finertial[1]}, Fzi{Finertial[2]};

    GiNaC::lst qdot = {
            (qw * p + 0 * qx + qy * r - qz * q) / 2,
            (qw * q + 0 * qy + qz * p - qx * r) / 2,
            (qw * r + 0 * qz + qx * q - qy * p) / 2,
            (qw * 0 - qx * p - qy * q - qz * r) / 2,
    };

    GiNaC::ex qxdot{qdot[0]}, qydot{qdot[1]}, qzdot{qdot[2]}, qwdot{qdot[3]};

    GiNaC::lst omdot = {
            (Mx - (q * Izz * r - r * Iyy * q)) / Ixx,
            (My - (r * Ixx * p - p * Izz * r)) / Iyy,
            (Mz - (p * Iyy * q - q * Ixx * p)) / Izz,
    };

    GiNaC::ex omxdot{omdot[0]}, omydot{omdot[1]}, omzdot{omdot[2]};

    ls::symbolic::OrdinaryDifferentialEquation ode{};
    ode.setFunctions(GiNaC::lst{
        vx,
        vy,
        vz,
        axi.expand(),
        ayi.expand(),
        azi.expand(),
        qxdot.expand(),
        qydot.expand(),
        qzdot.expand(),
        qwdot.expand(),
        omxdot.expand(),
        omydot.expand(),
        omzdot.expand()
    });

    ode.setStates(GiNaC::lst{
        x, y, z,
        vx, vy, vz,
        qx, qy, qz, qw,
        p, q, r
    });

    ode.setInputs(GiNaC::lst{
        Fth,
        Fpox, Fpoy, Fpoz,
        Fsbx, Fsby, Fsbz,
        Fstx, Fsty, Fstz,
        Fbox, Fboy, Fboz
    });

    std::cout << "6DOF Quaternion ODE" << std::endl;
    std::cout << GiNaC::latex << ode.getFunctions() << GiNaC::dflt << std::endl;
    std::cout << ode.generateJacobianStatesArrayInputCppFunc("jac6DOFStates") << std::endl << std::endl;
    std::cout << ode.generateJacobianInputsArrayInputCppFunc("jac6DOFInputs") << std::endl;
}