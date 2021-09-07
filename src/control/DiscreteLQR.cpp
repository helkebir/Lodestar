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
    return infiniteHorizon(sys.getA(), sys.getB(), Q, R);
}

Eigen::MatrixXd
ls::control::DiscreteLQR::finiteHorizon(const Eigen::MatrixXd &A,
                                        const Eigen::MatrixXd &B,
                                        const Eigen::MatrixXd &Q,
                                        const Eigen::MatrixXd &R,
                                        const unsigned int N)
{
    Eigen::MatrixXd SLatest = Q;
    Eigen::MatrixXd KLatest = (R + B.transpose() * Q * B).inverse() * (B.transpose() * Q * A);

    Eigen::MatrixXd Mi, Ri, S, Si, Ki;

    for (int i = 0; i < N; i++) {
        S = SLatest;
        Ri = R + B.transpose() * S * B;
        Mi = S - S * B * Ri.inverse() * B.transpose() * S;
        Si = A.transpose() * Mi * A + Q;
        Ki = Ri.inverse() * (B.transpose() * (S * A));

        SLatest = Si;
        KLatest = Ki;
    }


    return KLatest;
}

Eigen::MatrixXd
ls::control::DiscreteLQR::finiteHorizon(const ls::systems::StateSpace<> &sys,
                                        const Eigen::MatrixXd &Q,
                                        const Eigen::MatrixXd &R,
                                        const unsigned int N)
{
    return finiteHorizon(sys.getA(), sys.getB(), Q, R, N);
}
