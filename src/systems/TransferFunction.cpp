//
// Created by Hamza El-Kebir on 4/18/21.
//

#include "TransferFunction.hpp"

ls::systems::TransferFunction::TransferFunction(
        const ls::systems::TransferFunction &tf)
{
    num = tf.num;
    den = tf.den;
}

void ls::systems::TransferFunction::normalize()
{
    /*if (den.isZero()) {
        // TODO: Throw error; denominator must at least have one nonzero element.
    }*/

    num = num / den(0, 0);
    den = den / den(0, 0);

    // Cont zero numerator columns.
    int leadingZeros = 0;
    for (int i = 0; i < num.cols(); i++) {
        if (num.col(i).isZero())
            leadingZeros++;
        else
            break;
    }

    // Trim leading zeros.
    if (leadingZeros > 0) {
        if (leadingZeros == num.cols())
            leadingZeros--;

        num = num.block(0, leadingZeros, num.rows(), num.cols() - leadingZeros);
    }

    // Squeeze first dimension if singular.
    if (num.rows() == 1)
        num = num.block(0, 0, 1, num.cols()).transpose();
}

ls::systems::TransferFunction ls::systems::TransferFunction::normalized() const
{
    auto tf = TransferFunction(*this);
    tf.normalize();

    return tf;
}

ls::systems::StateSpace
ls::systems::TransferFunction::toStateSpace() const
{
    auto tf = normalized();

    int M = tf.num.rows();
    int K = tf.den.rows();

    if (M > K) {
        throw LODESTAR_ERROR::ERROR_IMPROPER_TRANSFER_FUNC;

        return StateSpace();
        // TODO: Throw error; improper transfer function.
    }

    if (M == 0 || K == 0) {
        // Null system.
        return StateSpace();
    }

    if (K > M) {
        // Pad numerator to have same length as denominator.
        tf.num.conservativeResize(K, tf.num.cols());
        tf.num.block(M, 0, K - M, tf.num.cols()) << Eigen::MatrixXd::Zero(
                K - M, tf.num.cols());
    }

    Eigen::MatrixXd A(K - 1, K - 1), B, C, D;

    if (tf.num.cols() > 0)
        D = tf.num.col(0);
    else
        D = Eigen::MatrixXd::Zero(1, 1);

    if (K == 1) {
        D = Eigen::Map<Eigen::MatrixXd>(D.data(), tf.num.rows(), tf.num.cols());

        return StateSpace(Eigen::MatrixXd::Zero(1, 1),
                          Eigen::MatrixXd::Zero(1, D.cols()),
                          Eigen::MatrixXd::Zero(D.rows(), 1), D);
    }

    Eigen::MatrixXd frow = -tf.den.block(1, 0, tf.den.rows() - 1,
                                         tf.den.cols()).transpose();
    A.block(0, 0, 1, K - 1) = frow;
    A.block(1, 0, K - 2, K - 1) = Eigen::MatrixXd::Identity(K - 2, K - 1);

    B = Eigen::MatrixXd::Identity(K - 1, 1);

    Eigen::VectorXd v0, v1;
    v0 = tf.num.row(0).transpose();
    v1 = tf.den.block(1, 0, tf.den.rows() - 1, tf.den.cols());

    Eigen::MatrixXd C0 = tf.num.block(1, 0, tf.num.rows() - 1,
                                      tf.num.cols()).transpose();

    C = C0 - v0 * v1.transpose();

    D = Eigen::Map<Eigen::MatrixXd>(D.data(), C.rows(), B.cols());

    return StateSpace(A, B, C, D);
}

ls::systems::StateSpace
ls::systems::TransferFunction::toDiscreteStateSpace(double dt) const
{
    return ls::analysis::BilinearTransformation::c2dBwdDiff(toStateSpace(), dt);
}

ls::systems::StateSpace
ls::systems::TransferFunction::toDiscreteStateSpace(double dt,
                                                    double alpha) const
{
    auto ss = ls::analysis::BilinearTransformation::c2d(toStateSpace(), dt, alpha);
    ss.setDiscreteParams(dt);

    return ss;
}