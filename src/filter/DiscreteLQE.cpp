//
// Created by Hamza El-Kebir on 5/9/21.
//

#include "DiscreteLQE.hpp"

Eigen::MatrixXd
ls::filter::DiscreteLQE::infiniteHorizon(const Eigen::MatrixXd &A,
                                         const Eigen::MatrixXd &B,
                                         const Eigen::MatrixXd &C,
                                         const Eigen::MatrixXd &Q,
                                         const Eigen::MatrixXd &R)
{
    Eigen::MatrixXd Minf, Linf;

    Minf = synthesis::AlgebraicRiccatiEquation::solveDARE(A.transpose(),
                                                          C.transpose(),
                                                          B * Q * B.transpose(),
                                                          R);
    Linf = Minf * C.transpose() * (C * Minf * C.transpose() + R).inverse();

    return Linf;
}

Eigen::MatrixXd
ls::filter::DiscreteLQE::infiniteHorizon(const ls::systems::StateSpace<> &sys,
                                         const Eigen::MatrixXd &Q,
                                         const Eigen::MatrixXd &R)
{
    return infiniteHorizon(sys.getA(), sys.getB(), sys.getC(), Q, R);
}

Eigen::MatrixXd ls::filter::DiscreteLQE::finiteHorizon(const Eigen::MatrixXd &A,
                                                       const Eigen::MatrixXd &B,
                                                       const Eigen::MatrixXd &C,
                                                       const Eigen::MatrixXd &Q,
                                                       const Eigen::MatrixXd &R,
                                                       const unsigned int N)
{
    Eigen::MatrixXd M0, Rinv;

    M0 = R.maxCoeff() * Eigen::MatrixXd::Identity(A.rows(), A.rows());
    Rinv = R.inverse();

    std::vector<Eigen::MatrixXd> M_l = {M0};
    std::vector<Eigen::MatrixXd> P_l = {
            M0 - M0 * C.transpose() * ((C * M0 *
                                        C.transpose()).completeOrthogonalDecomposition().pseudoInverse() +
                                       R) * C * M0
    };
    std::vector<Eigen::MatrixXd> L_l = {
            P_l.back() * C.transpose() * Rinv
    };

    for (int i = 0; i < N; i++) {
        Eigen::MatrixXd Mi, Pi, Li, S, Si, Ki;

        Mi = A * P_l.back() * A.transpose() + B * Q * B.transpose();
        Pi = Mi - Mi * C.transpose() * ((C * Mi *
                                         C.transpose()).completeOrthogonalDecomposition().pseudoInverse() +
                                        R) * C * Mi;
        Li = P_l.back() * C.transpose() * Rinv;

        M_l.pop_back();
        M_l.push_back(Mi);
        P_l.pop_back();
        P_l.push_back(Pi);
        L_l.pop_back();
        L_l.push_back(Li);
    }

    return L_l.back();
}

Eigen::MatrixXd
ls::filter::DiscreteLQE::finiteHorizon(const ls::systems::StateSpace<> &sys,
                                       const Eigen::MatrixXd &Q,
                                       const Eigen::MatrixXd &R,
                                       const unsigned int N)
{
    return finiteHorizon(sys.getA(), sys.getB(), sys.getC(), Q, R, N);
}
