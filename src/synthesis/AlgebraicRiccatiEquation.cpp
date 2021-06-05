//
// Created by Hamza El-Kebir on 5/9/21.
//

#include "AlgebraicRiccatiEquation.hpp"

Eigen::MatrixXd
ls::synthesis::AlgebraicRiccatiEquation::solveDARE(const Eigen::MatrixXd &A,
                                                   const Eigen::MatrixXd &B,
                                                   const Eigen::MatrixXd &Q,
                                                   const Eigen::MatrixXd &R)
{
    long m, n;
    m = B.rows();
    n = B.cols();

    Eigen::MatrixXd H = Eigen::MatrixXd::Zero(2 * m + n, 2 * m + n);
    H.block(0, 0, m, m) = A;
    H.block(0, 2 * m, m, n) = B;
    H.block(m, 0, m, m) = -Q;
    H.block(m, m, m, m) = Eigen::MatrixXd::Identity(m, m);
    H.block(m, 2 * m, m, n) = Eigen::MatrixXd::Zero(m, n);
    H.block(2 * m, 0, n, m) = Eigen::MatrixXd::Zero(n, m);
    H.block(2 * m, 2 * m, n, n) = R;

    Eigen::MatrixXd J = Eigen::MatrixXd::Zero(2 * m + n, 2 * m + n);
    J.block(0, 0, m, m) = Eigen::MatrixXd::Identity(m, m);
    J.block(m, m, m, m) = A.conjugate().transpose();
    J.block(2 * m, m, n, m) = -B.conjugate().transpose();


    { // Balancing
        Eigen::MatrixXd M = H.cwiseAbs() + J.cwiseAbs();
        M.diagonal() = Eigen::MatrixXd::Ones(2 * m + n, 1);
        // TODO: Implement matrix_balance
        // https://github.com/scipy/scipy/blob/v1.6.3/scipy/linalg/_solvers.py#L529-L734
    }

    Eigen::MatrixXd hhQ = H.block(0, 2 * m, 2 * m + n, n).fullPivHouseholderQr().matrixQ();

    Eigen::MatrixXd hhQtemp = hhQ.block(0, n, hhQ.rows(), hhQ.cols() - n).conjugate().transpose();
    H = hhQtemp * H.block(0, 0, 2 * m + n, 2 * m);
    J = hhQtemp * J.block(0, 0, 2 * m + n, 2 * m);

    Eigen::RealQZ<Eigen::MatrixXd> QZ(2 * m + n);
    QZ.compute(H, J);

    Eigen::MatrixXd Z = QZ.matrixZ();
    Eigen::MatrixXd Z00 = Z.block(0, 0, m, m);
    Eigen::MatrixXd Z10 = Z.block(m, 0, Z.rows() - m, m);

    // LU decomposition with partial pivoting to obtain Z00 = P L U
    auto ZLU = Z00.partialPivLu();
    auto ZL = ZLU.matrixLU().triangularView<Eigen::Lower>();
    auto ZU = ZLU.matrixLU().triangularView<Eigen::Upper>();
    Eigen::MatrixXd ZP = ZLU.permutationP();

    Eigen::MatrixXd X = ZL.conjugate().transpose().solve(
            ZU.conjugate().transpose().solve(
                    Z10.conjugate().transpose()
            )
    ).conjugate().transpose() * ZU.conjugate().transpose();

    // TODO: Add deviation from symmetry check.

    return (X + X.conjugate().transpose()) / 2;
}

Eigen::MatrixXd ls::synthesis::AlgebraicRiccatiEquation::solveDARE(
        const ls::systems::StateSpace<> &sys, const Eigen::MatrixXd &Q,
        const Eigen::MatrixXd &R)
{
    Eigen::MatrixXd A, B;
    A = *sys.getA();
    B = *sys.getB();

    return solveDARE(A, B, Q, R);
}
