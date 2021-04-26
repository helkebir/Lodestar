//
// Created by Hamza El-Kebir on 4/21/21.
//

#include "DiscreteSystem.hpp"

template<>
void ls::systems::DiscreteSystem<ls::systems::StateSpace>::advance()
{
    if (input != nullptr) {
        *state = system->A * (*state) + system->B * (*input);
    } else {
        *state = system->A * (*state);
    }

    time += system->getSamplingPeriod();
}

template<>
void ls::systems::DiscreteSystem<ls::systems::StateSpace>::advance(
        Eigen::VectorXd *control)
{
    *state = system->A * (*state) + system->B * (*control);

    time = system->getSamplingPeriod();
}

template<>
void ls::systems::DiscreteSystem<ls::systems::StateSpace>::advanceFree()
{
    *state = system->A * (*state);

    time += system->getSamplingPeriod();
}

template<>
void ls::systems::DiscreteSystem<ls::systems::StateSpace>::advanceForced()
{
    *state = system->A * (*state) + system->B * (*input);

    time += system->getSamplingPeriod();
}

template<>
void ls::systems::DiscreteSystem<ls::systems::StateSpace>::advanceForced(
        Eigen::VectorXd *control)
{
    *state = system->A * (*state) + system->B * (*control);

    time += system->getSamplingPeriod();
}

template<>
void ls::systems::DiscreteSystem<ls::systems::StateSpace>::initialize()
{
    state->conservativeResize(system->A.rows());

    if (input == nullptr)
        input = new Eigen::VectorXd;

    input->conservativeResize(system->B.cols());
}
