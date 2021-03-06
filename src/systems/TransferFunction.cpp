//
// Created by Hamza El-Kebir on 4/18/21.
//

#include "TransferFunction.hpp"

ls::systems::TransferFunction::TransferFunction(
        const ls::systems::TransferFunction &other)
{
    num_ = other.getNum();
    den_ = other.getDen();
}

void ls::systems::TransferFunction::normalizeInPlace()
{
    /*if (den.isZero()) {
        // TODO: Throw error; denominator must at least have one nonzero element.
    }*/

    num_ = num_ / den_(0, 0);
    den_ = den_ / den_(0, 0);

    // Cont zero numerator columns.
    int leadingZeros = 0;
    for (int i = 0; i < num_.cols(); i++) {
        if (num_.col(i).isZero())
            leadingZeros++;
        else
            break;
    }

    // Trim leading zeros.
    if (leadingZeros > 0) {
        if (leadingZeros == num_.cols())
            leadingZeros--;

        num_ = num_.block(0, leadingZeros, num_.rows(),
                          num_.cols() - leadingZeros);
    }

    // Squeeze first dimension if singular.
    if (num_.rows() == 1)
        num_ = num_.block(0, 0, 1, num_.cols()).transpose();
}

ls::systems::TransferFunction ls::systems::TransferFunction::normalized() const
{
    auto tf = TransferFunction(*this);
    tf.normalizeInPlace();

    return tf;
}

ls::systems::StateSpace<>
ls::systems::TransferFunction::toStateSpace() const
{
    auto tf = normalized();

    int M = tf.num_.rows();
    int K = tf.den_.rows();

    if (M > K) {
        throw LODESTAR_ERROR::ERROR_IMPROPER_TRANSFER_FUNC;

        return StateSpace<>();
        // TODO: Throw error; improper transfer function.
    }

    if (M == 0 || K == 0) {
        // Null system.
        return StateSpace<>();
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
        D = Eigen::Map<Eigen::MatrixXd>(D.data(), tf.getNum().rows(),
                                        tf.getNum().cols());

        return StateSpace<>(Eigen::MatrixXd::Zero(1, 1),
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

    return StateSpace<>(A, B, C, D);
}

ls::systems::StateSpace<>
ls::systems::TransferFunction::toDiscreteStateSpace(double dt) const
{
    return ls::analysis::BilinearTransformation::c2dBwdDiff(toStateSpace(), dt);
}

ls::systems::StateSpace<>
ls::systems::TransferFunction::toDiscreteStateSpace(double dt,
                                                    double alpha) const
{
    auto ss = ls::analysis::BilinearTransformation::c2d(toStateSpace(), dt,
                                                        alpha);
    ss.setDiscreteParams(dt);

    return ss;
}

Eigen::MatrixXd ls::systems::TransferFunction::getNum() const
{
    return num_;
}

void ls::systems::TransferFunction::setNum(const Eigen::MatrixXd &num)
{
    num_ = num;
}

long ls::systems::TransferFunction::getNumDegree() const
{
    long n = num_.rows() - 1;
    while ((num_(n, 0) == 0) && (n > 0)) {
        n--;
    }

    return n;
}

Eigen::MatrixXd ls::systems::TransferFunction::getDen() const
{
    return den_;
}

void ls::systems::TransferFunction::setDen(const Eigen::MatrixXd &den)
{
    den_ = den;
}

long ls::systems::TransferFunction::getDenDegree() const
{
    long d = den_.rows() - 1;
    while ((den_(d, 0) == 0) && (d > 0)) {
        d--;
    }

    return d;
}

#ifdef LS_USE_GINAC

ls::systems::TransferFunction::TransferFunction(const GiNaC::ex &tf,
                                                const GiNaC::ex &symbol)
{
    copyFromExpression(tf, symbol);
}

GiNaC::ex ls::systems::TransferFunction::getNumExpression(
        const GiNaC::ex &symbol) const
{
    GiNaC::ex num;

    const long n = getNumDegree();

    for (int i = 0; i < n + 1; i++) {
        num += num_(i, 0) * GiNaC::pow(symbol, n - i);
    }

    return num;
}

GiNaC::ex ls::systems::TransferFunction::getDenExpression(
        const GiNaC::ex &symbol) const
{
    GiNaC::ex den;

    const long d = getNumDegree();

    for (int i = 0; i < d + 1; i++) {
        den += den_(i, 0) * GiNaC::pow(symbol, d - i);
    }

    return den;
}

GiNaC::ex ls::systems::TransferFunction::getExpression(
        const GiNaC::ex &symbol) const
{
    return getNumExpression(symbol) / getDenExpression(symbol);
}

void ls::systems::TransferFunction::copyFromExpression(const GiNaC::ex &tf,
                                                       const GiNaC::ex &symbol)
{
    GiNaC::lst numer_denom = GiNaC::ex_to<GiNaC::lst>(
            tf.normal().numer_denom());
    GiNaC::ex num, den;
    num = numer_denom.op(0);
    den = numer_denom.op(1);

    const long n = num.degree(symbol)+1;
    const long d = den.degree(symbol)+1;

    num_ = Eigen::MatrixXd::Zero(n, 1);
    den_ = Eigen::MatrixXd::Zero(d, 1);

    for (int i = 0; i < n; i++) {
        num_(i, 0) = GiNaC::ex_to<GiNaC::numeric>(
                num.coeff(symbol, n - i - 1)).to_double();
    }

    for (int i = 0; i < d; i++) {
        den_(i, 0) = GiNaC::ex_to<GiNaC::numeric>(
                den.coeff(symbol, d - i - 1)).to_double();
    }
}

#endif