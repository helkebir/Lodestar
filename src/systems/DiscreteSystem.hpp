//
// Created by Hamza El-Kebir on 4/21/21.
//

#ifndef LODESTAR_DISCRETESYSTEM_HPP
#define LODESTAR_DISCRETESYSTEM_HPP

#include "Eigen/Dense"
#include "StateSpace.hpp"
#include "SystemStateful.hpp"
#include "aux/CompileTimeQualifiers.hpp"

namespace ls {
    namespace systems {
        template<class SYS>
        class DiscreteSystem : public SystemStateful {
        public:
            typedef SYS TDSystem;
            DiscreteSystem() : system(new SYS), state(new Eigen::VectorXd),
                               input(
                                       nullptr), time(0)
            {}

            DiscreteSystem(SYS *sys) : system(sys), state(new Eigen::VectorXd),
                                       input(nullptr), time(0)
            {}

            void advance();

//            void advance(void *control);

            void advanceFree();

            void advanceForced();

//            void advanceForced(void *control);

            SYS *system;
            void *state;
            void *input;

            double time;
        };

        template <template <typename, const int, const int, const int> class TSystem, typename TScalar, const int TStateDim, const int TInputDim, const int TOutputDim>
        class DiscreteSystem<TSystem<TScalar, TStateDim, TInputDim, TOutputDim>>;

        template <typename TScalar, const int TStateDim, const int TInputDim, const int TOutputDim>
        class DiscreteSystem<StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>> {
            typedef StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> TDSystem;
            typedef Eigen::Matrix<TScalar, TStateDim, LS_STATIC_UNLESS_DYNAMIC_VAL(TStateDim, 1)> TDStateVector;
            typedef Eigen::Matrix<TScalar, TInputDim, LS_STATIC_UNLESS_DYNAMIC_VAL(TInputDim, 1)> TDInputVector;

            DiscreteSystem() : system(new TDSystem), state(new TDStateVector),
                               input(nullptr), time(0)
            {}

            DiscreteSystem(TDSystem *sys) : system(sys), state(new TDStateVector),
                                       input(nullptr), time(0)
            {}

            void initialize(LS_IS_DYNAMIC_DEFAULT(TStateDim, TInputDim, TOutputDim));

            void initialize(LS_IS_STATIC_DEFAULT(TStateDim, TInputDim, TOutputDim));

            void advance();

            void advance(TDInputVector *control);

            void advanceFree();

            void advanceForced();

            void advanceForced(TDInputVector *control);

            TDSystem *system;
            TDStateVector *state;
            TDInputVector *input;

            double time;
        };
    }
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::DiscreteSystem<ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>>::advance()
{
    if (input != nullptr) {
        *state = system->getA() * (*state) + system->getB() * (*input);
    } else {
        *state = system->getA() * (*state);
    }

    time += system->getSamplingPeriod();
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::DiscreteSystem<ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>>::advance(
        Eigen::Matrix<TScalar, TInputDim, constexprMax2(-1, TInputDim, 1)> *control)
{
    *state = system->getA() * (*state) + system->getB() * (*control);

    time = system->getSamplingPeriod();
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::DiscreteSystem<ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>>::advanceFree()
{
    *state = system->getA() * (*state);

    time += system->getSamplingPeriod();
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::DiscreteSystem<ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>>::advanceForced()
{
    *state = system->getA() * (*state) + system->getB() * (*input);

    time += system->getSamplingPeriod();
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::DiscreteSystem<ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>>::advanceForced(
        Eigen::Matrix<TScalar, TInputDim, constexprMax2(-1, TInputDim, 1)> *control)
{
    *state = system->getA() * (*state) + system->getB() * (*control);

    time += system->getSamplingPeriod();
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::DiscreteSystem<ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>>::initialize(
        LS_IS_DYNAMIC(TStateDim, TInputDim, TOutputDim))
{
    state->conservativeResize(system->getA().rows());

    if (input == nullptr)
        input = new Eigen::VectorXd;

    input->conservativeResize(system->getB().cols());
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void ls::systems::DiscreteSystem<ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>>::initialize(
        LS_IS_STATIC(TStateDim, TInputDim, TOutputDim))
{
    // NOTE: No action since no memory may be allocated.
    return;
}



#endif //LODESTAR_DISCRETESYSTEM_HPP
