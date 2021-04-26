//
// Created by Hamza El-Kebir on 4/21/21.
//

#ifndef LODESTAR_DISCRETESYSTEM_HPP
#define LODESTAR_DISCRETESYSTEM_HPP

#include "Eigen/Dense"
#include "StateSpace.hpp"
#include "SystemStateful.hpp"

namespace ls { namespace systems {
    template<class SYS>
    class DiscreteSystem : public SystemStateful {
    public:
        DiscreteSystem() : system(new SYS), state(new Eigen::VectorXd), input(
                nullptr), time(0)
        {}

        DiscreteSystem(SYS *sys) : system(sys), state(new Eigen::VectorXd),
                                   input(nullptr), time(0)
        {}

        void initialize();

        void advance();

        void advance(Eigen::VectorXd *control);

        void advanceFree();

        void advanceForced();

        void advanceForced(Eigen::VectorXd *control);

        SYS *system;
        Eigen::VectorXd *state;
        Eigen::VectorXd *input;

        double time;
    };
} }

#endif //LODESTAR_DISCRETESYSTEM_HPP
