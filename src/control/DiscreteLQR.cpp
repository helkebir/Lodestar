//
// Created by Hamza El-Kebir on 5/9/21.
//

#include "DiscreteLQR.hpp"

Eigen::MatrixXd
ls::control::DiscreteLQR::infiniteHorizon(const Eigen::MatrixXd &A,
                                          const Eigen::MatrixXd &B,
                                          const Eigen::MatrixXd &Q,
                                          const Eigen::MatrixXd &R)
{
    Eigen::MatrixXd Sinf, Kinf;

    Sinf = synthesis::AlgebraicRiccatiEquation::solveDARE(A, B, Q, R);
    Kinf = (R + B.transpose() * Sinf * B).inverse() *
           (B.transpose() * Sinf * A);

    return Kinf;
}

Eigen::MatrixXd
ls::control::DiscreteLQR::infiniteHorizon(const ls::systems::StateSpace<> &sys,
                                          const Eigen::MatrixXd &Q,
                                          const Eigen::MatrixXd &R)
{
    return infiniteHorizon(*sys.getA(), *sys.getB(), Q, R);
}

Eigen::MatrixXd
ls::control::DiscreteLQR::finiteHorizon(const Eigen::MatrixXd &A,
                                        const Eigen::MatrixXd &B,
                                        const Eigen::MatrixXd &Q,
                                        const Eigen::MatrixXd &R,
                                        const unsigned int N)
{
    std::vector<Eigen::MatrixXd> S_l = {Q};
    std::vector<Eigen::MatrixXd> K_l = {
            (R + B.transpose() * Q * B).inverse() * (B.transpose() * Q * A)
    };

    for (int i = 0; i < N; i++) {
        Eigen::MatrixXd Mi, Ri, S, Si, Ki;

        S = S_l.back();
        S_l.pop_back();
        Ri = R + B.transpose() * S * B;
        Mi = S - S * B * Ri.inverse() * B.transpose() * S;
        Si = A.transpose() * Mi * A + Q;
        Ki = R.inverse() * B.transpose() * Si * A;

        S_l.push_back(Si);
        K_l.pop_back();
        K_l.push_back(Ki);
    }


    return K_l.back();
}

Eigen::MatrixXd
ls::control::DiscreteLQR::finiteHorizon(const ls::systems::StateSpace<> &sys,
                                        const Eigen::MatrixXd &Q,
                                        const Eigen::MatrixXd &R,
                                        const unsigned int N)
{
    return finiteHorizon(*sys.getA(), *sys.getB(), Q, R, N);
}
