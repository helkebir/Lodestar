//
// Created by Hamza El-Kebir on 12/23/21.
//

#include "catchOnce.hpp"
#include "Lodestar/blocks/std/GainBlock.hpp"
#include "Lodestar/blocks/std/ConstantBlock.hpp"
#include "Lodestar/blocks/std/SumBlock.hpp"
#include "Lodestar/blocks/BlockUtilities.hpp"
#include "Eigen/Dense"


TEST_CASE("GainBlock", "[blocks][std]")
{
    SECTION("Arithmetic types") {
        ls::blocks::std::GainBlock<double> gb{};

        gb.i<0>() = 2;
        gb.setGain(3);
        gb.trigger();

        REQUIRE(gb.o<0>() == Approx(6));
    }

    SECTION("Eigen types") {
        ls::blocks::std::GainBlock<Eigen::Vector3d, Eigen::Matrix3d> gb{};

        Eigen::Vector3d v;
        v << 1, 2, 3;

        Eigen::Matrix3d m = -Eigen::Matrix3d::Identity();

        gb.i<0>() = v;
        gb.setGain(m);
        gb.trigger();

        REQUIRE(gb.o<0>().object(0) == Approx(-1));
        REQUIRE(gb.o<0>().object(1) == Approx(-2));
        REQUIRE(gb.o<0>().object(2) == Approx(-3));
    }
}

TEST_CASE("GainBlock and ConstantBlock", "[blocks][std]")
{
    const int N = 3;
    ls::blocks::std::ConstantBlock<Eigen::Matrix<double, N, 1>> cb;
    ls::blocks::std::GainBlock<Eigen::Matrix<double, N, 1>, Eigen::Matrix<double, N, N>> gb;
    ls::blocks::std::SumBlock<Eigen::Matrix<double, N, 1>, 2> sb;
    sb.setOperators(decltype(sb)::Plus, decltype(sb)::Minus);

    connect(cb.o<0>(), sb.i<0>());
    connect(sb.o<0>(), gb.i<0>());
    connect(gb.o<0>(), sb.i<1>());

#ifdef LS_USE_GINAC

    ::std::vector<GiNaC::ex>
            sb_i{sb.inputSymbols().begin(), sb.inputSymbols().end()},
            sb_o{sb.outputSymbols().begin(), sb.outputSymbols().end()},
            cb_p{cb.parameterSymbols().begin(), cb.parameterSymbols().end()},
            cb_o{cb.outputSymbols().begin(), cb.outputSymbols().end()},
            gb_p{gb.parameterSymbols().begin(), gb.parameterSymbols().end()},
            gb_i{gb.inputSymbols().begin(), gb.inputSymbols().end()},
            gb_o{gb.outputSymbols().begin(), gb.outputSymbols().end()};

    GiNaC::lst a{};

    // Constant block
    a.append((cb_o[0] == cb_p[0]));

    // Gain block
    a.append((gb_o[0] == gb_p[0] * gb_i[0]));

    ::std::vector<ls::blocks::std::SumBlockOperator> sb_ops;
    sb.getOperators(sb_ops);

    GiNaC::ex sb_rhs = 0;
    for (int i = 0; i < sb_ops.size(); i++)
        sb_rhs += ls::blocks::std::SumBlockOperatorHelper::interpret(sb_ops[i]) * sb_i[i];

    // Sum block
    a.append((sb_o[0] == sb_rhs));

    // Interconnections
    a.append((sb_i[0] == cb_o[0]));
    a.append((gb_i[0] == sb_o[0]));
    a.append((sb_i[1] == gb_o[0]));


    // Strongly connected component:
    GiNaC::lst b{};

    GiNaC::lst b_known{sb_i[0]};
    for (auto p : gb_p)
        b_known.append(p);

    GiNaC::lst b_unknown{sb_i[1], sb_o[0], gb_i[0], gb_o[0]};

    // Gain block
//    b.append((gb_o[0] == gb_p[0] * gb_i[0]));
    b.append((gb_o[0] == gb.blkf(gb_i[0]).eval().evalm()));

    // Sum block
//    b.append((sb_o[0] == sb_rhs));
    b.append((sb_o[0] == sb.blkf(sb_i[0], sb_i[1]).eval().evalm()));

    // Interconnections
    b.append((gb_i[0] == sb_o[0]));
    b.append((sb_i[1] == gb_o[0]));

    GiNaC::ex eq = sb_o[0];
    eq = eq.subs(b).evalm();

    ::std::cout << "gb_o[0]: " << gb_o[0] << ::std::endl;
    ::std::cout << "sb_o[0]: " << sb_o[0] << ::std::endl;
    ::std::cout << "sb_i[0]: " << sb_i[0] << ::std::endl;
    ::std::cout << "sb_i[1]: " << sb_i[1] << ::std::endl;
    ::std::cout << sb_o[0] << ::std::endl;
    ::std::cout << sb_o[0][0] << ::std::endl;

    ::std::cout << b << ::std::endl;

    int i = 0;
//    while (!eq.has(sb_o[0][0])) {
//        eq = eq.subs(b).evalm();
//        ::std::cout << i << ": " << eq << ::std::endl;
//        i++;
//    }

    ::std::cout << i << ": " << eq << ::std::endl;
    i++;

    for (auto &bex : b) {
        auto rel = bex;

        if (rel.lhs().nops() > 0) {
            ::std::cout << "LHS: " << rel.lhs() << ::std::endl;
            ::std::cout << "RHS: " << rel.rhs() << ::std::endl;
            for (int ii = 0; ii < rel.lhs().nops(); ii++)
                if (rel.lhs()[ii].nops() > 0) {
                    for (int jj = 0; jj < rel.lhs()[ii].nops(); jj++) {
                        eq = eq.subs(rel.lhs()[ii][jj] == rel.rhs()[ii][jj]);
                        ::std::cout << "REL " << GiNaC::ex{(rel.lhs()[ii][jj] == rel.rhs()[ii][jj])} << ::std::endl;
                    }
                } else {
                    eq = eq.subs(rel.lhs()[ii] == rel.rhs()[ii]);
                    ::std::cout << "REL " << GiNaC::ex{(rel.lhs()[ii] == rel.rhs()[ii])} << ::std::endl;
                }
        } else {
            eq = eq.subs(rel);
        }
    }

    ::std::cout << i << ": " << eq << ::std::endl;
    i++;

    for (auto &bex : b) {
        auto rel = bex;

        if (rel.lhs().nops() > 0) {
            for (int ii = 0; ii < rel.lhs().nops(); ii++)
                if (rel.lhs()[ii].nops() > 0) {
                    for (int jj = 0; jj < rel.lhs()[ii].nops(); jj++) {
                        eq = eq.subs(rel.lhs()[ii][jj] == rel.rhs()[ii][jj]);
                    }
                } else {
                    eq = eq.subs(rel.lhs()[ii] == rel.rhs()[ii]);
                }
        } else {
            eq = eq.subs(rel);
        }
    }

    ::std::cout << i << ": " << eq << ::std::endl;
    i++;

//    eq = eq.subs(b).evalm();
//    ::std::cout << i << ": " << eq << ::std::endl;
//    i++;
//
//    eq = eq.subs(b).evalm();
//    ::std::cout << i << ": " << eq << ::std::endl;
//    i++;
//
//    eq = eq.subs(b).evalm();
//    ::std::cout << i << ": " << eq << ::std::endl;
//    i++;
//
//    eq = eq.subs(b).evalm();
//    ::std::cout << i << ": " << eq << ::std::endl;
//    i++;

    ::std::cout << sb_o[0] << " == " << eq << ::std::endl;

    ::std::cout << "Partial deriv wrt. sb_o_0_0 [0]: " << eq[0].diff(GiNaC::ex_to<GiNaC::symbol>(sb_o[0][0])) << ::std::endl;
    ::std::cout << "Partial deriv wrt. sb_o_0_0: " << eq.diff(GiNaC::ex_to<GiNaC::symbol>(sb_o[0][0])) << ::std::endl;

    GiNaC::matrix jac(sb_o[0].nops(), sb_o[0].nops());
    for (int k = 0; k < sb_o[0].nops(); k++) {
        for (int kk = 0; kk < sb_o[0].nops(); kk++)
            jac(k, kk) = eq[k].diff(GiNaC::ex_to<GiNaC::symbol>(sb_o[0][kk]));
    }

    ::std::cout << "Jac: " << jac << ::std::endl;

    GiNaC::matrix vars(sb_o[0].nops(), 1);

    for (int k = 0; k < sb_o[0].nops(); k++) {
        vars(k, 0) = GiNaC::symbol{"dsb_o_0_" + ::std::to_string(k)};
    }

    jac.solve(vars, GiNaC::ex_to<GiNaC::matrix>((-eq).evalm())).eval();

    ::std::cout << "Soln: " << ::std::endl;
//    ::std::cout << "Soln: " << GiNaC::latex <<  jac.solve(vars, GiNaC::ex_to<GiNaC::matrix>((-eq).evalm())).eval();

    bool res = ::std::all_of(b_unknown.begin(), b_unknown.end(), [&] (GiNaC::ex ex) -> bool {
        if (ex != sb_o[0])
            return !eq.has(ex);
        else
            return true;
    });

//    ::std::cout << (eq - sb_o[0]).diff(GiNaC::ex_to<GiNaC::symbol>(sb_o[0])) << ::std::endl;
//
//    GiNaC::symbol delta("dsb_0");
//    GiNaC::ex func = (eq - sb_o[0]);
//    GiNaC::ex grad = (eq - sb_o[0]).diff(GiNaC::ex_to<GiNaC::symbol>(sb_o[0]));
//    GiNaC::lst eqs{grad*delta == -func};
//    GiNaC::lst vars{delta};
//
//    auto sols = GiNaC::lsolve(eqs, vars);
//
//    ::std::cout << "Sol: " << GiNaC::csrc << sols << ::std::endl;

//    ::std::cout << "Function: " << sb.blkFunc(cb_o[0], sb_o[0]) << ::std::endl;

//    ::std::cout << sb_o[0][0] << ::std::endl;

    REQUIRE(res);

    // 0. Construct an equation with an output, and substitute once.
    // 1. Substitute until symbol from 0. reappears.
    // 2. Detect any other unknown outputs, and repeat step zero for these symbols, skipping previously seen unknowns.
    // 3. Once there are no more unvisited unknown symbols, we have a system of N equations.
    // 4. Compute the Jacobian of the system of equations, and construct a Newton-Raphson iteration.

#endif
}

TEST_CASE("GainBlock convolution", "[blocks][std]")
{
    ls::blocks::std::GainBlock<
            Eigen::Matrix<double, 5, 5>,
            Eigen::Matrix<double, 3, 3>,
            ls::blocks::std::GainBlockOperator::Convolution,
            ls::blocks::std::GainBlockConvolutionMode::Reflect
    > gb;

    Eigen::Matrix<double, 5, 5> I;
    I << 1 , 2 , 3 , 4 , 5 ,
         6 , 7 , 8 , 9 , 10,
         11, 12, 13, 14, 15,
         16, 17, 18, 19, 20,
         21, 22, 23, 24, 25;

    Eigen::Matrix<double, 3, 3> K;
    K << -1, 0, 1,
         -2, 0, 2,
         -1, 0, 1;

    gb.i<0>() = I;
    gb.gain() = K;
    gb.trigger();



    ::std::cout << "Convolution:\n" << gb.o<0>().object << ::std::endl;
}