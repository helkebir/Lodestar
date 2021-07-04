//
// Created by Hamza El-Kebir on 6/6/21.
//

#ifndef LODESTAR_TESTAUXFUNCTIONS_HPP
#define LODESTAR_TESTAUXFUNCTIONS_HPP

#include <Eigen/Dense>

// A(x, u)
Eigen::Matrix<double, 2, 2> jacStates(const double x, const double y, const double u, const double t) {
    Eigen::Matrix<double, 2, 2> mat;
    mat <<  y+u+2.0*x, x,
            0.0, 2.0*y;

    return mat;
}
// B(x, u)
Eigen::Matrix<double, 2, 1> jacInputs(const double x, const double y, const double u, const double t) {
    Eigen::Matrix<double, 2, 1> mat;
    mat <<  x+2e-01,
            2.0;

    return mat;
}

#endif //LODESTAR_TESTAUXFUNCTIONS_HPP
