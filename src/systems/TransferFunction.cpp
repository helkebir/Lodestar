//
// Created by Hamza El-Kebir on 4/18/21.
//

#include "TransferFunction.hpp"

ls::systems::TransferFunction::TransferFunction(
        const ls::systems::TransferFunction &tf) {
    _num = tf.getNum();
    _den = tf.getDen();
}

void ls::systems::TransferFunction::normalize() {
    /*if (den.isZero()) {
        // TODO: Throw error; denominator must at least have one nonzero element.
    }*/

    _num = _num / _den(0, 0);
    _den = _den / _den(0, 0);

    // Cont zero numerator columns.
    int leadingZeros = 0;
    for (int i = 0; i < _num.cols(); i++) {
        if (_num.col(i).isZero())
            leadingZeros++;
        else
            break;
    }

    // Trim leading zeros.
    if (leadingZeros > 0) {
        if (leadingZeros == _num.cols())
            leadingZeros--;

        _num = _num.block(0, leadingZeros, _num.rows(), _num.cols() - leadingZeros);
    }

    // Squeeze first dimension if singular.
    if (_num.rows() == 1)
        _num = _num.block(0, 0, 1, _num.cols()).transpose();
}

ls::systems::TransferFunction ls::systems::TransferFunction::normalized() const {
    auto tf = TransferFunction(*this);
    tf.normalize();

    return tf;
}

ls::systems::StateSpace
ls::systems::TransferFunction::toStateSpace() const {
    auto tf = normalized();

    int M = tf._num.rows();
    int K = tf._den.rows();

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
        auto numtmp = tf.getNum();
        numtmp.conservativeResize(K, tf.getNum().cols());
        numtmp.block(M, 0, K - M, tf.getNum().cols()) << Eigen::MatrixXd::Zero(
                K - M, tf.getNum().cols());
        tf.setNum(numtmp);
    }

    Eigen::MatrixXd A(K - 1, K - 1), B, C, D;

    if (tf.getNum().cols() > 0)
        D = tf.getNum().col(0);
    else
        D = Eigen::MatrixXd::Zero(1, 1);

    if (K == 1) {
        D = Eigen::Map<Eigen::MatrixXd>(D.data(), tf.getNum().rows(), tf.getNum().cols());

        return StateSpace(Eigen::MatrixXd::Zero(1, 1),
                          Eigen::MatrixXd::Zero(1, D.cols()),
                          Eigen::MatrixXd::Zero(D.rows(), 1), D);
    }

    Eigen::MatrixXd frow = -tf.getDen().block(1, 0, tf.getDen().rows() - 1,
                                              tf.getDen().cols()).transpose();
    A.block(0, 0, 1, K - 1) = frow;
    A.block(1, 0, K - 2, K - 1) = Eigen::MatrixXd::Identity(K - 2, K - 1);

    B = Eigen::MatrixXd::Identity(K - 1, 1);

    Eigen::VectorXd v0, v1;
    v0 = tf.getNum().row(0).transpose();
    v1 = tf.getDen().block(1, 0, tf.getDen().rows() - 1, tf.getDen().cols());

    Eigen::MatrixXd C0 = tf.getNum().block(1, 0, tf.getNum().rows() - 1,
                                           tf.getNum().cols()).transpose();

    C = C0 - v0 * v1.transpose();

    D = Eigen::Map<Eigen::MatrixXd>(D.data(), C.rows(), B.cols());

    return StateSpace(A, B, C, D);
}

ls::systems::StateSpace
ls::systems::TransferFunction::toDiscreteStateSpace(double dt) const {
    return ls::analysis::BilinearTransformation::c2dBwdDiff(toStateSpace(), dt);
}

ls::systems::StateSpace
ls::systems::TransferFunction::toDiscreteStateSpace(double dt,
                                                    double alpha) const {
    auto ss = ls::analysis::BilinearTransformation::c2d(toStateSpace(), dt, alpha);
    ss.setDiscreteParams(dt);

    return ss;
}

Eigen::MatrixXd ls::systems::TransferFunction::getNum() const {
    return _num;
}

const Eigen::MatrixXd &ls::systems::TransferFunction::getNumRef() {
    return _num;
}

void ls::systems::TransferFunction::setNum(const Eigen::MatrixXd &num) {
    _num = num;
}

Eigen::MatrixXd ls::systems::TransferFunction::getDen() const {
    return _den;
}

const Eigen::MatrixXd &ls::systems::TransferFunction::getDenRef() {
    return _den;
}

void ls::systems::TransferFunction::setDen(const Eigen::MatrixXd &den) {
    _den = den;
}