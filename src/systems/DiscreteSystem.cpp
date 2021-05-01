//
// Created by Hamza El-Kebir on 4/21/21.
//

#include "DiscreteSystem.hpp"

template<>
void ls::systems::DiscreteSystem<ls::systems::StateSpace>::advance()
{
    if (input != nullptr) {
        *state = system->getA() * (*state) + system->getB() * (*input);
    } else {
        *state = system->getA() * (*state);
    }

    time += system->getSamplingPeriod();
}

template<>
void ls::systems::DiscreteSystem<ls::systems::StateSpace>::advance(
        Eigen::VectorXd *control)
{
    *state = system->getA() * (*state) + system->getB() * (*control);

    time = system->getSamplingPeriod();
}

template<>
void ls::systems::DiscreteSystem<ls::systems::StateSpace>::advanceFree()
{
    *state = system->getA() * (*state);

    time += system->getSamplingPeriod();
}

template<>
void ls::systems::DiscreteSystem<ls::systems::StateSpace>::advanceForced()
{
    *state = system->getA() * (*state) + system->getB() * (*input);

    time += system->getSamplingPeriod();
}

template<>
void ls::systems::DiscreteSystem<ls::systems::StateSpace>::advanceForced(
        Eigen::VectorXd *control)
{
    *state = system->getA() * (*state) + system->getB() * (*control);

    time += system->getSamplingPeriod();
}

template<>
void ls::systems::DiscreteSystem<ls::systems::StateSpace>::initialize()
{
    state->conservativeResize(system->getA().rows());

    if (input == nullptr)
        input = new Eigen::VectorXd;

    input->conservativeResize(system->getB().cols());
}
