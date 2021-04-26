//
// Created by Hamza El-Kebir on 4/17/21.
//

#ifndef LODESTAR_STATESPACE_HPP
#define LODESTAR_STATESPACE_HPP

#include "SystemStateless.hpp"
#include "Eigen/Dense"

namespace ls {
    namespace systems {
        class StateSpace : public SystemStateless {
        public:
            StateSpace() : A(Eigen::MatrixXd::Zero(1, 1)),
                           B(Eigen::MatrixXd::Zero(1, 1)),
                           C(Eigen::MatrixXd::Zero(1, 1)),
                           D(Eigen::MatrixXd::Zero(1, 1)),
                           _dt(-1), _isDiscrete(false)
            {};

            StateSpace(const Eigen::MatrixXd &A, const Eigen::MatrixXd &B,
                       const Eigen::MatrixXd &C, const Eigen::MatrixXd &D);

            StateSpace(const StateSpace &lti);

            void setDiscreteParams(double dt);

            void setDiscreteParams(double dt, bool discrete);

            bool isDiscrete() const;

            double getSamplingPeriod() const;

            void setSamplingPeriod(double dt);

            int stateDim() const;

            int inputDim() const;

            int outputDim() const;

            virtual void append(const StateSpace &ss);

            virtual bool isStable(double tolerance = 0) const;

            Eigen::MatrixXd A, B, C, D;
        protected:
            double _dt;
            bool _isDiscrete;
        };
    }
}


#endif //LODESTAR_STATESPACE_HPP
