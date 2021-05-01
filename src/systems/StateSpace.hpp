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
            StateSpace() : _A(Eigen::MatrixXd::Zero(1, 1)),
                           _B(Eigen::MatrixXd::Zero(1, 1)),
                           _C(Eigen::MatrixXd::Zero(1, 1)),
                           _D(Eigen::MatrixXd::Zero(1, 1)),
                           _dt(-1), _isDiscrete(false) {};

            StateSpace(const Eigen::MatrixXd &A, const Eigen::MatrixXd &B,
                       const Eigen::MatrixXd &C, const Eigen::MatrixXd &D);

            StateSpace(const StateSpace &lti);

            Eigen::MatrixXd getA() const;

            const Eigen::MatrixXd& getARef();

            void setA(const Eigen::MatrixXd &A);

            Eigen::MatrixXd getB() const;

            const Eigen::MatrixXd& getBRef();

            void setB(const Eigen::MatrixXd &B);

            Eigen::MatrixXd getC() const;

            const Eigen::MatrixXd& getCRef();

            void setC(const Eigen::MatrixXd &C);

            Eigen::MatrixXd getD() const;

            const Eigen::MatrixXd& getDRef();

            void setD(const Eigen::MatrixXd &D);

            void setDiscreteParams(double dt);

            void setDiscreteParams(double dt, bool discrete);

            bool isDiscrete() const;

            double getSamplingPeriod() const;

            void setSamplingPeriod(double dt);

            long stateDim() const;

            long inputDim() const;

            long outputDim() const;

            virtual void append(const StateSpace &ss);

            virtual bool isStable(double tolerance = 0) const;

        protected:
            Eigen::MatrixXd _A, _B, _C, _D;
            double _dt;
            bool _isDiscrete;
        };
    }
}


#endif //LODESTAR_STATESPACE_HPP
