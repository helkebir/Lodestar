//
// Created by helkebir on 6/29/21.
//

#include "catchOnce.hpp"

#include "symbolic/OrdinaryDifferentialEquation.hpp"

TEST_CASE("6-DOF with Euler angles", "[demo]")
{
    using GiNaC::cos;
    using GiNaC::sin;
    using GiNaC::tan;

    GiNaC::symbol x{"_s_x_"}, y{"_s_y_"}, z{"_s_z_"},
            vx("_s_vx_"), vy("_s_vy_"), vz("_s_vz_"),
            phi("_s_phi_"), theta("_s_theta_"), psi("_s_psi_"),
            p("_s_p_"), q("_s_q_"), r("_s_r_");


    GiNaC::symbol Fth("_s_Fth_"),
        Fpox("_s_Fpox_"), Fpoy("_s_Fpoy_"), Fpoz("_s_Fpoz_"),
        Fsbx("_s_Fsbx_"), Fsby("_s_Fsby_"), Fsbz("_s_Fsbz_"),
        Fstx("_s_Fstx_"), Fsty("_s_Fsty_"), Fstz("_s_Fstz_"),
        Fbox("_s_Fbox_"), Fboy("_s_Fboy_"), Fboz("_s_Fboz_");

    GiNaC::matrix CBL = GiNaC::ex_to<GiNaC::matrix>(GiNaC::lst_to_matrix(GiNaC::lst{
        GiNaC::lst{cos(theta) * cos(psi), sin(phi) * sin(theta) * cos(psi) - cos(phi) * sin(psi), cos(phi) * sin(theta) * cos(psi) + sin(phi) * sin(psi)},
        GiNaC::lst{cos(theta) * sin(psi), sin(phi) * sin(theta) * sin(psi) - cos(phi) * cos(psi), cos(phi) * sin(theta) * sin(psi) + sin(phi) * cos(psi)},
        GiNaC::lst{-sin(theta), sin(theta) * cos(theta), cos(phi) * cos(theta)}
    }));

    GiNaC::matrix CLB = CBL.transpose();

    // phi, theta, psi
    GiNaC::lst bodyRatesToEulerRates = {
            p + sin(phi) * tan(theta) * q + cos(phi) * tan(theta) * r,
            cos(phi) * q - sin(phi) * r,
            (sin(phi) * q + cos(phi) * r) / cos(theta)
    };
}