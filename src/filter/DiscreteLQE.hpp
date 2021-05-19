//
// Created by Hamza El-Kebir on 5/9/21.
//

#ifndef LODESTAR_DISCRETELQE_HPP
#define LODESTAR_DISCRETELQE_HPP

#include "synthesis/AlgebraicRiccatiEquation.hpp"
#include "Eigen/QR"
#include <vector>

namespace ls {
    namespace filter {
        class DiscreteLQE {
            static Eigen::MatrixXd
            infiniteHorizon(const Eigen::MatrixXd &A,
                            const Eigen::MatrixXd &B,
                            const Eigen::MatrixXd &Q,
                            const Eigen::MatrixXd &C,
                            const Eigen::MatrixXd &R);

            static Eigen::MatrixXd
            infiniteHorizon(const systems::StateSpace<> &sys,
                            const Eigen::MatrixXd &Q,
                            const Eigen::MatrixXd &R);

            static Eigen::MatrixXd
            finiteHorizon(const Eigen::MatrixXd &A,
                          const Eigen::MatrixXd &B,
                          const Eigen::MatrixXd &C,
                          const Eigen::MatrixXd &Q,
                          const Eigen::MatrixXd &R,
                          unsigned int N = 5);

            static Eigen::MatrixXd
            finiteHorizon(const systems::StateSpace<> &sys,
                          const Eigen::MatrixXd &Q,
                          const Eigen::MatrixXd &R,
                          unsigned int N = 5);
        };
    }
}

#endif //LODESTAR_DISCRETELQE_HPP
