//
// Created by Hamza El-Kebir on 5/9/21.
//

#ifndef LODESTAR_DISCRETELQR_HPP
#define LODESTAR_DISCRETELQR_HPP

#include "systems/StateSpace.hpp"
#include "synthesis/AlgebraicRiccatiEquation.hpp"
#include <vector>

namespace ls {
    namespace control {
        class DiscreteLQR {
        public:
            static Eigen::MatrixXd
            infiniteHorizon(const Eigen::MatrixXd &A,
                            const Eigen::MatrixXd &B,
                            const Eigen::MatrixXd &Q,
                            const Eigen::MatrixXd &R);

            static Eigen::MatrixXd
            infiniteHorizon(const systems::StateSpace<> &sys,
                            const Eigen::MatrixXd &Q,
                            const Eigen::MatrixXd &R);

            static Eigen::MatrixXd
            finiteHorizon(const Eigen::MatrixXd &A,
                          const Eigen::MatrixXd &B,
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

#endif //LODESTAR_DISCRETELQR_HPP
