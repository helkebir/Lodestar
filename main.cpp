#include <iostream>

#include "primitives/integrators/IntegratorNewton.hpp"
#include "tests/analysis/LinearSystemInverse_test.hpp"
#include "analysis/ZeroOrderHold.hpp"
#include "analysis/BilinearTransformation.hpp"
#include "systems/TransferFunction.hpp"
#include "systems/DiscreteSystem.hpp"

#include "LodestarErrors.hpp"
#include "LodestarErrorNames.hpp"
#include "aux/UnitLiterals.hpp"

using namespace ls::aux;

template<typename S>
void linear(ls::primitives::Integrator<S> *integrator)
{
    *integrator->state = integrator->time;
}

template<typename S>
void quadratic(ls::primitives::Integrator<S> *integrator)
{
    *integrator->state = integrator->time * integrator->time;
}

int main()
{
    double state = 0;
    double period = 1e-2;
    auto *integrator = new ls::primitives::IntegratorNewton<double>(period,
                                                                    &state);

    double finalTime = 0.5;

    while (integrator->time <= finalTime) {
        //        quadratic(integrator);
        linear(integrator);
        integrator->updateState();
    }

    std::cout << "integral " << (*integrator).integral << std::endl;

    auto ilti = linearSystemInverseExample();
    std::cout << "Ai " << std::endl << ilti.A << std::endl;
    std::cout << "Bi " << std::endl << ilti.B << std::endl;
    std::cout << "Ci " << std::endl << ilti.C << std::endl;
    std::cout << "Di " << std::endl << ilti.D << std::endl << std::endl;

    Eigen::MatrixXd A(3, 3), B(3, 2), C(2, 3), D(2, 2);
    A << 1, 2, 0,
            4, -1, 0,
            0, 0, 1;

    B << 1, 0,
            0, 1,
            1, 0;

    C << 0, 1, -1,
            0, 0, 1;

    D << 4, 0,
            0, 1;

    auto lti = ls::systems::StateSpace(A, B, C, D);

    std::cout << "isStable: " << (lti.isStable() ? "true" : "false") << std::endl;

    auto dlti = ls::analysis::ZeroOrderHold::c2d(lti, 0.1);
    std::cout << "ZOH (0.1)" << std::endl;
    std::cout << "Ad " << std::endl << dlti.A << std::endl;
    std::cout << "Bd " << std::endl << dlti.B << std::endl;
    std::cout << "Cd " << std::endl << dlti.C << std::endl;
    std::cout << "Dd " << std::endl << dlti.D << std::endl << std::endl;

    dlti = ls::analysis::ZeroOrderHold::d2c(dlti, 0.1);
    std::cout << "ZOH inv. (0.1)" << std::endl;
    std::cout << "Ac " << std::endl << dlti.A << std::endl;
    std::cout << "Bc " << std::endl << dlti.B << std::endl;
    std::cout << "Cc " << std::endl << dlti.C << std::endl;
    std::cout << "Dc " << std::endl << dlti.D << std::endl << std::endl;

    dlti = ls::analysis::BilinearTransformation::c2dTustin(lti, 0.1);
    std::cout << "Tustin (0.1)" << std::endl;
    std::cout << "Ad " << std::endl << dlti.A << std::endl;
    std::cout << "Bd " << std::endl << dlti.B << std::endl;
    std::cout << "Cd " << std::endl << dlti.C << std::endl;
    std::cout << "Dd " << std::endl << dlti.D << std::endl << std::endl;

    dlti = ls::analysis::BilinearTransformation::d2cTustin(dlti, 0.1);
    std::cout << "Tustin inv. (0.1)" << std::endl;
    std::cout << "Ac " << std::endl << dlti.A << std::endl;
    std::cout << "Bc " << std::endl << dlti.B << std::endl;
    std::cout << "Cc " << std::endl << dlti.C << std::endl;
    std::cout << "Dc " << std::endl << dlti.D << std::endl << std::endl;

    dlti = ls::analysis::BilinearTransformation::c2dEuler(lti, 0.1);
    std::cout << "Euler (0.1)" << std::endl;
    std::cout << "Ad " << std::endl << dlti.A << std::endl;
    std::cout << "Bd " << std::endl << dlti.B << std::endl;
    std::cout << "Cd " << std::endl << dlti.C << std::endl;
    std::cout << "Dd " << std::endl << dlti.D << std::endl << std::endl;

    dlti = ls::analysis::BilinearTransformation::d2cEuler(dlti, 0.1);
    std::cout << "Euler inv. (0.1)" << std::endl;
    std::cout << "Ac " << std::endl << dlti.A << std::endl;
    std::cout << "Bc " << std::endl << dlti.B << std::endl;
    std::cout << "Cc " << std::endl << dlti.C << std::endl;
    std::cout << "Dc " << std::endl << dlti.D << std::endl << std::endl;

    dlti = ls::analysis::BilinearTransformation::c2dBwdDiff(lti, 0.1);
    std::cout << "Bwd Diff (0.1)" << std::endl;
    std::cout << "Ad " << std::endl << dlti.A << std::endl;
    std::cout << "Bd " << std::endl << dlti.B << std::endl;
    std::cout << "Cd " << std::endl << dlti.C << std::endl;
    std::cout << "Dd " << std::endl << dlti.D << std::endl << std::endl;

    dlti = ls::analysis::BilinearTransformation::d2cBwdDiff(dlti, 0.1);
    std::cout << "Bwd Diff inv. (0.1)" << std::endl;
    std::cout << "Ac " << std::endl << dlti.A << std::endl;
    std::cout << "Bc " << std::endl << dlti.B << std::endl;
    std::cout << "Cc " << std::endl << dlti.C << std::endl;
    std::cout << "Dc " << std::endl << dlti.D << std::endl << std::endl;

    std::cout << "isStable: " << (dlti.isStable() ? "true" : "false") << std::endl;

    Eigen::VectorXd num(3), den(3);
    //    num << 1,2,3;
    //    den << 2,3,4;
    num << 2.3, 1.2, 0;
    den << 4.5, 2.1, 5.3;

    std::cout << "outer " << num * den.transpose() << std::endl;

    auto tf = ls::systems::TransferFunction(num, den);

    ls::systems::StateSpace ss;

    try {
        ss = tf.toStateSpace();
    } catch (LODESTAR_ERROR lsErr) {
        std::cout << "Lodestar error " << LODESTAR_ERROR_NAME(lsErr)
                  << std::endl;
    }

    std::cout << "tf to ss" << std::endl;
    std::cout << "A " << std::endl << ss.A << std::endl;
    std::cout << "B " << std::endl << ss.B << std::endl;
    std::cout << "C " << std::endl << ss.C << std::endl;
    std::cout << "D " << std::endl << ss.D << std::endl << std::endl;

    auto dss = tf.toDiscreteStateSpace(0.1);

    std::cout << "tf to discr. ss (0.1)" << std::endl;
    std::cout << "Ad " << std::endl << dss.A << std::endl;
    std::cout << "Bd " << std::endl << dss.B << std::endl;
    std::cout << "Cd " << std::endl << dss.C << std::endl;
    std::cout << "Dd " << std::endl << dss.D << std::endl << std::endl;

    std::cout << "25 Hz " << 25_Hz << std::endl;
    std::cout << "25 us " << 25_us << std::endl;

    std::cout << "45 deg " << 45_deg << std::endl;

    auto dsys = ls::systems::StateSpace();
    dsys.A.resize(4,4);
    dsys.A << 0.9599,  0.0401, -0.4861,  0.0139,
              0.0401,  0.9599, -0.0139,  0.4861,
              0.1566, -0.1565,  0.9321, -0.0678,
              0.1566, -0.1565, -0.0679,  0.9322;

    dsys.B.resize(4,2);
    dsys.B << -0.1049,  0.0017,
              -0.0017,  0.1049,
               0.4148, -0.0118,
              -0.0118,  0.4148;

//    dsys.C.setOnes(4,4);
//
//    dsys.D.setZero(4,2);

    dsys.C.resize(2, 4);
    dsys.C <<  0.5,   0.5,   0,     0,
              -2.113, 2.113, 0.375, 0.375;

    dsys.D.resize(2,2);
    dsys.D.setIdentity();

    ls::systems::DiscreteSystem<ls::systems::StateSpace> dfullsys(&dsys);
    dfullsys.state->setZero(4);
    (*dfullsys.state) << 100, 100, 0, 100;

//    std::cout << "test " << dsys.A * (*dfullsys.state) << std::endl;
//    auto csys = ls::analysis::ZeroOrderHold::d2c(dsys, 0.05);
//    auto csysinv = ls::analysis::LinearSystemInverse::inverse(csys);
//    auto dsysinv = ls::analysis::ZeroOrderHold::c2d(csysinv, 0.05);
//    dsysinv.setDiscreteParams(-dsys.getSamplingPeriod());

//    std::cout << "dsysinv" << std::endl;
//    std::cout << "Dinv" << dsys.D.inverse() << std::endl;
//    std::cout << "Ad " << std::endl << dsysinv.A << std::endl;
//    std::cout << "Bd " << std::endl << dsysinv.B << std::endl;
//    std::cout << "Cd " << std::endl << dsysinv.C << std::endl;
//    std::cout << "Dd " << std::endl << dsysinv.D << std::endl << std::endl;

    for (int i = 0; i < 10; i++) {
        std::cout << "Time " << i << ": " << std::endl << *dfullsys.state << std::endl;
        dfullsys.advanceFree();
    }

    return 0;
}
