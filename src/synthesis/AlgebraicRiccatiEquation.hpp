//
// Created by Hamza El-Kebir on 5/9/21.
//

#ifndef LODESTAR_ALGEBRAICRICCATIEQUATION_HPP
#define LODESTAR_ALGEBRAICRICCATIEQUATION_HPP

#include "systems/StateSpace.hpp"
#include "Eigen/Eigenvalues"

namespace ls {
    namespace synthesis {
        class AlgebraicRiccatiEquation {
        public:
            static Eigen::MatrixXd solveDARE(const Eigen::MatrixXd &A, const Eigen::MatrixXd &B, const Eigen::MatrixXd &Q, const Eigen::MatrixXd &R);
            static Eigen::MatrixXd solveDARE(const systems::StateSpace<> &sys, const Eigen::MatrixXd &Q, const Eigen::MatrixXd &R);
        };
    }
}

#endif //LODESTAR_ALGEBRAICRICCATIEQUATION_HPP
