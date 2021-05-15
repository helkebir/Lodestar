//
// Created by Hamza El-Kebir on 4/21/21.
//

#ifndef LODESTAR_FIXEDGAIN_HPP
#define LODESTAR_FIXEDGAIN_HPP

#include "Eigen/Dense"

namespace ls {
    namespace control {
        class FixedGain {
        public:
            FixedGain() : gain(new Eigen::MatrixXd)
            {}

            Eigen::MatrixXd *gain;
        };
    }
}

#endif //LODESTAR_FIXEDGAIN_HPP
