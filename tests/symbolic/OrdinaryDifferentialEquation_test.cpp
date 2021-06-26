//
// Created by Hamza El-Kebir on 6/26/21.
//

#ifdef LS_USE_GINAC

#include "catchOnce.hpp"
#include "symbolic/OrdinaryDifferentialEquation.hpp"

TEST_CASE("Ordinary differential equation", "[symbolic]")
{
    GiNaC::symbol x{"_s_x_"}, vx{"_s_vx_"},
            th{"_s_theta_"}, thdot{"_s_thdot_"},
            u("_s_u_");

    GiNaC::symbol mCart("_s_mCart_"), mPole("_s_mPole_"), g("_s_g_"), l("_s_l_");

    GiNaC::ex mCartEx = mCart;
    GiNaC::ex mPoleEx = mPole;
    GiNaC::ex lEx = l;
    GiNaC::ex gEx = g;

    mCartEx = 1.5;
    mPoleEx = 0.25;
    gEx = 9.80665;
    lEx = 0.4;
    
    using GiNaC::cos;
    using GiNaC::sin;
    
    GiNaC::lst odeFunc = {
            vx,
            0,
            thdot,
            (gEx * sin(th) + cos(th) * ((-u - mPoleEx * lEx * thdot * thdot * sin(th)) / (mCartEx + mPoleEx))) /
                (lEx * (4.0 / 3.0 - (mPoleEx * cos(th) * cos(th)) / (mCartEx + mPoleEx)))
    };
    
    odeFunc[1] = (u + mPoleEx * lEx * (thdot * thdot * sin(th - odeFunc[3] * cos(th)))) / (mCartEx + mPoleEx);
    GiNaC::lst stateArgs = {x, vx, th, thdot};
    GiNaC::lst inputArgs = {u};

    ls::symbolic::OrdinaryDifferentialEquation ode{};

    ode.setFunctions(odeFunc);
    ode.setStates(stateArgs);
    ode.setInputs(inputArgs);

//    std::cout << "Cart-pole demo:" << std::endl;
//    std::cout << ode.generateJacobianStatesArrayInputCppFunc("cartPoleStateJacobian") << std::endl;
//    std::cout << std::endl;
//    std::cout << ode.generateJacobianInputsArrayInputCppFunc("cartPoleInputJacobian") << std::endl;
}

#endif