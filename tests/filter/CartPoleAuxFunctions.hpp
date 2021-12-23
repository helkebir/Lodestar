//
// Created by Hamza El-Kebir on 6/26/21.
//

#ifndef LODESTAR_CARTPOLEAUXFUNCTIONS_HPP
#define LODESTAR_CARTPOLEAUXFUNCTIONS_HPP

#include <Eigen/Dense>

/**
 * @param x State array:
 *     _s_x_, _s_vx_, _s_theta_, _s_thdot_
 * @param u Input array:
 *     _s_u_
 * @param t Time.
 *
 * @return Jacobian matrix.
 */
// Function automatically generated by Lodestar
Eigen::Matrix<double, 4, 4> cartPoleStateJacobian(const Eigen::Matrix<double, 4, 1> &x, const Eigen::Matrix<double, 1, 1> &u, const double t = 0) {
    Eigen::Matrix<double, 4, 4> mat;
    mat << 0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 5.7142857142857148e-02*(x[3]*x[3])*cos(-cos(x[2])/( -5.7142857142857148e-02*pow(cos(x[2]),2.0)+5.3333333333333333e-01)*( ( -5.7142857142857148e-02*(x[3]*x[3])*sin(x[2])+-5.7142857142857140e-01*u[0])*cos(x[2])+9.8066499999999994e+00*sin(x[2]))+x[2])*( 1.1428571428571430e-01*pow(cos(x[2]),2.0)/pow( -5.7142857142857148e-02*pow(cos(x[2]),2.0)+5.3333333333333333e-01,2.0)*sin(x[2])*( ( -5.7142857142857148e-02*(x[3]*x[3])*sin(x[2])+-5.7142857142857140e-01*u[0])*cos(x[2])+9.8066499999999994e+00*sin(x[2]))+( ( -5.7142857142857148e-02*(x[3]*x[3])*sin(x[2])+-5.7142857142857140e-01*u[0])*sin(x[2])+-9.8066499999999994e+00*cos(x[2])+5.7142857142857148e-02*(x[3]*x[3])*pow(cos(x[2]),2.0))*cos(x[2])/( -5.7142857142857148e-02*pow(cos(x[2]),2.0)+5.3333333333333333e-01)+1.0/( -5.7142857142857148e-02*pow(cos(x[2]),2.0)+5.3333333333333333e-01)*sin(x[2])*( ( -5.7142857142857148e-02*(x[3]*x[3])*sin(x[2])+-5.7142857142857140e-01*u[0])*cos(x[2])+9.8066499999999994e+00*sin(x[2]))+1.0),  6.5306122448979603e-03*(x[3]*x[3]*x[3])*cos(-cos(x[2])/( -5.7142857142857148e-02*pow(cos(x[2]),2.0)+5.3333333333333333e-01)*( ( -5.7142857142857148e-02*(x[3]*x[3])*sin(x[2])+-5.7142857142857140e-01*u[0])*cos(x[2])+9.8066499999999994e+00*sin(x[2]))+x[2])*pow(cos(x[2]),2.0)/( -5.7142857142857148e-02*pow(cos(x[2]),2.0)+5.3333333333333333e-01)*sin(x[2])+1.1428571428571430e-01*sin(-cos(x[2])/( -5.7142857142857148e-02*pow(cos(x[2]),2.0)+5.3333333333333333e-01)*( ( -5.7142857142857148e-02*(x[3]*x[3])*sin(x[2])+-5.7142857142857140e-01*u[0])*cos(x[2])+9.8066499999999994e+00*sin(x[2]))+x[2])*x[3],
            0.0, 0.0, 0.0, 1.0,
            0.0, 0.0,  -1.1428571428571430e-01*cos(x[2])/pow( -5.7142857142857148e-02*pow(cos(x[2]),2.0)+5.3333333333333333e-01,2.0)*sin(x[2])*( ( -5.7142857142857148e-02*(x[3]*x[3])*sin(x[2])+-5.7142857142857140e-01*u[0])*cos(x[2])+9.8066499999999994e+00*sin(x[2]))-( ( -5.7142857142857148e-02*(x[3]*x[3])*sin(x[2])+-5.7142857142857140e-01*u[0])*sin(x[2])+-9.8066499999999994e+00*cos(x[2])+5.7142857142857148e-02*(x[3]*x[3])*pow(cos(x[2]),2.0))/( -5.7142857142857148e-02*pow(cos(x[2]),2.0)+5.3333333333333333e-01), -1.1428571428571430e-01*x[3]*cos(x[2])/( -5.7142857142857148e-02*pow(cos(x[2]),2.0)+5.3333333333333333e-01)*sin(x[2]);

    return mat;
}


/**
 * @param x State array:
 *     _s_x_, _s_vx_, _s_theta_, _s_thdot_
 * @param u Input array:
 *     _s_u_
 * @param t Time.
 *
 * @return Jacobian matrix.
 */
// Function automatically generated by Lodestar
Eigen::Matrix<double, 4, 1> cartPoleInputJacobian(const Eigen::Matrix<double, 4, 1> &x, const Eigen::Matrix<double, 1, 1> &u, const double t = 0) {
    Eigen::Matrix<double, 4, 1> mat;
    mat << 0.0,
            3.2653061224489799e-02*(x[3]*x[3])*cos(-cos(x[2])/( -5.7142857142857148e-02*pow(cos(x[2]),2.0)+5.3333333333333333e-01)*( ( -5.7142857142857148e-02*(x[3]*x[3])*sin(x[2])+-5.7142857142857140e-01*u[0])*cos(x[2])+9.8066499999999994e+00*sin(x[2]))+x[2])*pow(cos(x[2]),2.0)/( -5.7142857142857148e-02*pow(cos(x[2]),2.0)+5.3333333333333333e-01)+5.7142857142857140e-01,
            0.0,
            -5.7142857142857140e-01*cos(x[2])/( -5.7142857142857148e-02*pow(cos(x[2]),2.0)+5.3333333333333333e-01);

    return mat;
}

#endif //LODESTAR_CARTPOLEAUXFUNCTIONS_HPP