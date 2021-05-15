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

#ifdef LS_USE_GINAC

#include "ginac/ginac.h"
#include "symbolic/GiNaCNumTrait.hpp"

#include "symbolic/OrdinaryDifferentialEquation.hpp"

#endif

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

#ifdef LS_USE_GINAC
GiNaC::matrix
makeJacobian(const GiNaC::lst &states, const GiNaC::lst &functions)
{
    GiNaC::lst cols{};
    for (GiNaC::lst::const_iterator it = states.begin();
         it != states.end(); it++) {
        cols.append(functions.diff(GiNaC::ex_to<GiNaC::symbol>(*it)));
    }

    GiNaC::matrix mat = GiNaC::ex_to<GiNaC::matrix>(GiNaC::lst_to_matrix(cols));

    return mat.transpose();
}

Eigen::MatrixXd matrix_to_MatrixXd(const GiNaC::matrix &mat)
{
    int n = mat.rows(), m = mat.cols();
    auto emat = Eigen::MatrixXd(n, m);
    emat.setZero();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            emat.coeffRef(i, j) = GiNaC::ex_to<GiNaC::numeric>(
                    mat(i, j).evalf()).to_double();
        }
    }

    return emat;
}

Eigen::MatrixXd matrix_to_MatrixXd(const GiNaC::ex &ex)
{
    GiNaC::matrix mat = GiNaC::ex_to<GiNaC::matrix>(ex);
    int n = mat.rows(), m = mat.cols();
    auto emat = Eigen::MatrixXd(n, m);
    emat.setZero();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            emat.coeffRef(i, j) = GiNaC::ex_to<GiNaC::numeric>(
                    mat(i, j).evalf()).to_double();
        }
    }

    return emat;
}

GiNaC::matrix lst_to_vector(const GiNaC::lst &lst) {
    GiNaC::lst row{{lst}};
    return GiNaC::ex_to<GiNaC::matrix>(GiNaC::lst_to_matrix(row)).transpose();
}

void ginacTest()
{
    GiNaC::symbol z("z");
    GiNaC::symbol w("w");
    GiNaC::symbol v("v");
    GiNaC::exmap xmap;
    xmap[z] = 2;
    std::cout << "5 <= 6 : " << (bool) GiNaC::relational(5, 6, GiNaC::relational::operators::less_or_equal) << std::endl;
    std::cout << "z <= z+2 : " << (bool) GiNaC::relational(z, z+2, GiNaC::relational::operators::less_or_equal) << std::endl;
    std::cout << "z^2 <= z^3 : " << (bool) GiNaC::ex_to<GiNaC::relational>(GiNaC::relational(GiNaC::pow(z, 2), GiNaC::pow(z, 3), GiNaC::relational::operators::less_or_equal).subs(xmap)) << std::endl;
    std::cout << GiNaC::exp(z).series(z==0, 3) << std::endl;

    GiNaC::exset xset;
    GiNaC::ex xpression = (w - z + GiNaC::cos(z+2) - z*z);
    std::cout << xpression << std::endl;
    std::cout << xpression.find(GiNaC::cos(GiNaC::wild(0)), xset) << std::endl;
//    std::cout << xpression.find((z - w + GiNaC::wildcard(1)), xset) << std::endl;
//    std::cout << xpression.find((w - z + GiNaC::wildcard(2)), xset) << std::endl;
    std::cout << xset << std::endl;
    xmap.clear();
    for (const auto &ex : xset)
        xmap[ex] = 1;

    xpression = GiNaC::expand(xpression).subs(xmap);
    xpression = xpression.subs(GiNaC::lst{GiNaC::wildcard(0) + w - z == GiNaC::wildcard(0) + v});
    xpression = xpression.subs(GiNaC::lst{GiNaC::wildcard(0) + GiNaC::pow(w - z, GiNaC::wildcard(1)) == GiNaC::wildcard(0) + GiNaC::pow(v, GiNaC::wildcard(1))});
    std::cout << xpression << std::endl;

    ls::symbolic::OrdinaryDifferentialEquation ode{};
    ode.setFunctions(GiNaC::lst{ode.getStateSymbol(0)*ode.getStateSymbol(0) + ode.getStateSymbol(0)*ode.getInputSymbol(0)});

    std::cout << lst_to_vector(ode.getFunctions())(0,0) << std::endl;
    std::cout << GiNaC::series_to_poly(ode.getFunctions().op(0).series(ode.getStateSymbol(0)==0, 2)) << std::endl;
    std::cout << GiNaC::series_to_poly(lst_to_vector(ode.getFunctions()).series(ode.getStateSymbol(0)==0, 3).evalm()) << std::endl;


    auto exmap = ode.generateExpressionMap(std::vector<double>{2}, std::vector<double>{3});

    std::cout << exmap << std::endl;

    std::cout << ode.getFunctions() << std::endl;
    std::cout << ode.generateJacobianStates() << std::endl;
    std::cout << ode.generateJacobianMatrix(ode.generateJacobianStates(), exmap) << std::endl;

    auto jacStates = ode.generateJacobianStates();
    auto jacInputs = ode.generateJacobianInputs();

    auto ss = ode.linearize(jacStates, jacInputs, std::vector<double>{2}, std::vector<double>{3});
    std::cout << "Linearize ODE about x=2, u=3:" << std::endl;
    std::cout << "A" << std::endl << ss.getA() << std::endl;
    std::cout << "B" << std::endl << ss.getB() << std::endl;
    std::cout << "C" << std::endl << ss.getC() << std::endl;
    std::cout << "D" << std::endl << ss.getD() << std::endl;

    ss.copyMatrices(ode.linearize(jacStates, jacInputs, std::vector<double>{3}, std::vector<double>{5}));
    std::cout << "Linearize ODE about x=3, u=5:" << std::endl;
    std::cout << "A" << std::endl << ss.getA() << std::endl;
    std::cout << "B" << std::endl << ss.getB() << std::endl;
    std::cout << "C" << std::endl << ss.getC() << std::endl;
    std::cout << "D" << std::endl << ss.getD() << std::endl;

    auto dss = ls::analysis::ZeroOrderHold::c2d(ss, 0.1);
    std::cout << "Discretized at 0.1 s ZOH" << std::endl;
    std::cout << "Ad" << std::endl << dss.getA() << std::endl;
    std::cout << "Bd" << std::endl << dss.getB() << std::endl;
    std::cout << "Cd" << std::endl << dss.getC() << std::endl;
    std::cout << "Dd" << std::endl << dss.getD() << std::endl;

    std::cout << std::endl;

    GiNaC::symbol x("x"), y("y"), u("u");

    GiNaC::lst states{x, y};
    GiNaC::lst inputs{u};
    GiNaC::lst functions{x * x, y * x + u/2};
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
    std::cout << makeJacobian(states, functions) << std::endl;
    std::cout << makeJacobian(states, functions).subs(m) << std::endl;
    std::cout << matrix_to_MatrixXd(makeJacobian(states, functions).subs(m)) << std::endl;
    std::cout << makeJacobian(inputs, functions) << std::endl;
    std::cout << matrix_to_MatrixXd(makeJacobian(inputs, functions).subs(m)) << std::endl;

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

    Eigen::Matrix<GiNaC::ex, Eigen::Dynamic, Eigen::Dynamic> A{};
    A.resize(2, 1);
    //    A.conservativeResize(2,1);
    A(0, 0) = poly;
    A(1, 0) = poly.diff(x).subs(GiNaC::lst{x == 2, y == 2});

    std::cout << A << std::endl;
}
#endif

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
    std::cout << "Ai " << std::endl << ilti.getA() << std::endl;
    std::cout << "Bi " << std::endl << ilti.getB() << std::endl;
    std::cout << "Ci " << std::endl << ilti.getC() << std::endl;
    std::cout << "Di " << std::endl << ilti.getD() << std::endl << std::endl;

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

    std::cout << "isStable: " << (lti.isStable() ? "true" : "false")
              << std::endl;

    auto dlti = ls::analysis::ZeroOrderHold::c2d(lti, 0.1);
    std::cout << "ZOH (0.1)" << std::endl;
    std::cout << "Ad " << std::endl << dlti.getA() << std::endl;
    std::cout << "Bd " << std::endl << dlti.getB() << std::endl;
    std::cout << "Cd " << std::endl << dlti.getC() << std::endl;
    std::cout << "Dd " << std::endl << dlti.getD() << std::endl << std::endl;

    dlti = ls::analysis::ZeroOrderHold::d2c(dlti, 0.1);
    std::cout << "ZOH inv. (0.1)" << std::endl;
    std::cout << "Ac " << std::endl << dlti.getA() << std::endl;
    std::cout << "Bc " << std::endl << dlti.getB() << std::endl;
    std::cout << "Cc " << std::endl << dlti.getC() << std::endl;
    std::cout << "Dc " << std::endl << dlti.getD() << std::endl << std::endl;

    dlti = ls::analysis::BilinearTransformation::c2dTustin(lti, 0.1);
    std::cout << "Tustin (0.1)" << std::endl;
    std::cout << "Ad " << std::endl << dlti.getA() << std::endl;
    std::cout << "Bd " << std::endl << dlti.getB() << std::endl;
    std::cout << "Cd " << std::endl << dlti.getC() << std::endl;
    std::cout << "Dd " << std::endl << dlti.getD() << std::endl << std::endl;

    dlti = ls::analysis::BilinearTransformation::d2cTustin(dlti, 0.1);
    std::cout << "Tustin inv. (0.1)" << std::endl;
    std::cout << "Ac " << std::endl << dlti.getA() << std::endl;
    std::cout << "Bc " << std::endl << dlti.getB() << std::endl;
    std::cout << "Cc " << std::endl << dlti.getC() << std::endl;
    std::cout << "Dc " << std::endl << dlti.getD() << std::endl << std::endl;

    dlti = ls::analysis::BilinearTransformation::c2dEuler(lti, 0.1);
    std::cout << "Euler (0.1)" << std::endl;
    std::cout << "Ad " << std::endl << dlti.getA() << std::endl;
    std::cout << "Bd " << std::endl << dlti.getB() << std::endl;
    std::cout << "Cd " << std::endl << dlti.getC() << std::endl;
    std::cout << "Dd " << std::endl << dlti.getD() << std::endl << std::endl;

    dlti = ls::analysis::BilinearTransformation::d2cEuler(dlti, 0.1);
    std::cout << "Euler inv. (0.1)" << std::endl;
    std::cout << "Ac " << std::endl << dlti.getA() << std::endl;
    std::cout << "Bc " << std::endl << dlti.getB() << std::endl;
    std::cout << "Cc " << std::endl << dlti.getC() << std::endl;
    std::cout << "Dc " << std::endl << dlti.getD() << std::endl << std::endl;

    dlti = ls::analysis::BilinearTransformation::c2dBwdDiff(lti, 0.1);
    std::cout << "Bwd Diff (0.1)" << std::endl;
    std::cout << "Ad " << std::endl << dlti.getA() << std::endl;
    std::cout << "Bd " << std::endl << dlti.getB() << std::endl;
    std::cout << "Cd " << std::endl << dlti.getC() << std::endl;
    std::cout << "Dd " << std::endl << dlti.getD() << std::endl << std::endl;

    dlti = ls::analysis::BilinearTransformation::d2cBwdDiff(dlti, 0.1);
    std::cout << "Bwd Diff inv. (0.1)" << std::endl;
    std::cout << "Ac " << std::endl << dlti.getA() << std::endl;
    std::cout << "Bc " << std::endl << dlti.getB() << std::endl;
    std::cout << "Cc " << std::endl << dlti.getC() << std::endl;
    std::cout << "Dc " << std::endl << dlti.getD() << std::endl << std::endl;

    std::cout << "isStable: " << (dlti.isStable() ? "true" : "false")
              << std::endl;

    Eigen::VectorXd num(3), den(3);
    //    num << 1,2,3;
    //    den << 2,3,4;
    num << 2.3, 1.2, 0;
    den << 4.5, 2.1, 5.3;

    std::cout << "outer " << num * den.transpose() << std::endl;

    auto tf = ls::systems::TransferFunction(num, den);

#ifdef LS_USE_GINAC
    auto s = GiNaC::symbol("s");
    GiNaC::archive arxiv;
    arxiv.archive_ex(tf.getExpression(s), "tf");
    std::cout << "Archived tf:" << std::endl;
    std::cout << sizeof arxiv << std::endl;

    std::cout << "tf to ex" << std::endl;
//    std::cout << GiNaC::latex;
//    GiNaC::Digits = 6;
    std::cout << tf.getExpression(s) << std::endl;
    auto tf2 = ls::systems::TransferFunction(tf.getExpression(s), s);
    std::cout << tf2.getExpression(s) << std::endl;
    if ((bool) (tf.getExpression(s) == tf2.getExpression(s))) {
        std::cout << "Expressions are equal." << std::endl;
    } else
        std::cout << (bool) (tf.getExpression(s) == tf2.getExpression(s)) << std::endl;

    std::cout << GiNaC::dflt;
#endif

    ls::systems::StateSpace ss;

    try {
        ss = tf.toStateSpace();
    } catch (LODESTAR_ERROR lsErr) {
        std::cout << "Lodestar error " << LODESTAR_ERROR_NAME(lsErr)
                  << std::endl;
    }

    std::cout << "tf to ss" << std::endl;
    std::cout << "A " << std::endl << ss.getA() << std::endl;
    std::cout << "B " << std::endl << ss.getB() << std::endl;
    std::cout << "C " << std::endl << ss.getC() << std::endl;
    std::cout << "D " << std::endl << ss.getD() << std::endl << std::endl;

    auto dss = tf.toDiscreteStateSpace(0.1);

    std::cout << "tf to discr. ss (0.1)" << std::endl;
    std::cout << "Ad " << std::endl << dss.getA() << std::endl;
    std::cout << "Bd " << std::endl << dss.getB() << std::endl;
    std::cout << "Cd " << std::endl << dss.getC() << std::endl;
    std::cout << "Dd " << std::endl << dss.getD() << std::endl << std::endl;

    std::cout << "25 Hz " << 25_Hz << std::endl;
    std::cout << "25 us " << 25_us << std::endl;

    std::cout << "45 deg " << 45_deg << std::endl;

    auto dsys = ls::systems::StateSpace();
    auto Atmp = dsys.getA();
    Atmp.resize(4, 4);
    Atmp << 0.9599, 0.0401, -0.4861, 0.0139,
            0.0401, 0.9599, -0.0139, 0.4861,
            0.1566, -0.1565, 0.9321, -0.0678,
            0.1566, -0.1565, -0.0679, 0.9322;
    dsys.setA(Atmp);

    auto Btmp = dsys.getB();
    Btmp.resize(4, 2);
    Btmp << -0.1049, 0.0017,
            -0.0017, 0.1049,
            0.4148, -0.0118,
            -0.0118, 0.4148;
    dsys.setB(Btmp);

    //    dsys.C.setOnes(4,4);
    //
    //    dsys.D.setZero(4,2);

    auto Ctmp = dsys.getC();
    Ctmp.resize(2, 4);
    Ctmp << 0.5, 0.5, 0, 0,
            -2.113, 2.113, 0.375, 0.375;
    dsys.setC(Ctmp);

    auto Dtmp = dsys.getD();
    Dtmp.resize(2, 2);
    Dtmp.setIdentity();
    dsys.setD(Dtmp);

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
        std::cout << "Time " << i << ": " << std::endl << *dfullsys.state
                  << std::endl;
        dfullsys.advanceFree();
    }

    #ifdef LS_USE_GINAC
    ginacTest();
    #endif

    return 0;
}
