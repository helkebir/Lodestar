//
// Created by Hamza El-Kebir on 4/12/21.
//

#ifndef LODESTAR_INTEGRATORNEWTON_HPP
#define LODESTAR_INTEGRATORNEWTON_HPP

#include "../Integrator.hpp"

namespace ls {
    namespace primitives {
        template<typename TState>
        class IntegratorNewton : public Integrator<TState> {
        public:
            typedef Integrator<TState> Base;
            using Base::samplingPeriod;
            using Base::time;
            using Base::state;
            using Base::integral;

            IntegratorNewton();

            explicit IntegratorNewton(double _samplingPeriod);

            explicit IntegratorNewton(TState *_state);

            explicit IntegratorNewton(double _samplingPeriod, TState *_state);

            void updateState();

            void updateState(double _samplingPeriod);

            void updateState(TState *_state);

            void updateState(double _samplingPeriod, TState *_state);

            double updateTime();

            double updateTime(double _samplingPeriod);

            TState getIntegral();
        };
    }
}

template<typename State>
inline ls::primitives::IntegratorNewton<State>::IntegratorNewton()
{
    samplingPeriod = 1e-3;
    time = 0;
    state = new State();
    integral = State();
}

template<typename State>
inline ls::primitives::IntegratorNewton<State>::IntegratorNewton(double _samplingPeriod)
{
    samplingPeriod = _samplingPeriod;
    time = 0;
    state = new State();
    integral = State();
}

template<typename State>
inline ls::primitives::IntegratorNewton<State>::IntegratorNewton(State *_state)
{
    samplingPeriod = 1e-3;
    time = 0;
    state = _state;
    integral = State();
}

template<typename State>
inline
ls::primitives::IntegratorNewton<State>::IntegratorNewton(double _samplingPeriod, State *_state)
{
    samplingPeriod = _samplingPeriod;
    time = 0;
    state = _state;
    integral = State();
}

template<typename State>
inline void ls::primitives::IntegratorNewton<State>::updateState()
{
    updateTime();
    integral += (*state) * samplingPeriod;
}

template<typename State>
inline void ls::primitives::IntegratorNewton<State>::updateState(double _samplingPeriod)
{
    updateTime(_samplingPeriod);
    integral += (*state) * _samplingPeriod;
}

template<typename State>
inline void ls::primitives::IntegratorNewton<State>::updateState(State *_state)
{
    updateTime();
    state = _state;
    integral += (*state) * samplingPeriod;
}

template<typename State>
inline void
ls::primitives::IntegratorNewton<State>::updateState(double _samplingPeriod, State *_state)
{
    updateTime(_samplingPeriod);
    state = _state;
    integral += (*state) * _samplingPeriod;
}

template<typename State>
inline State ls::primitives::IntegratorNewton<State>::getIntegral()
{
    return integral;
}

template<typename State>
inline double ls::primitives::IntegratorNewton<State>::updateTime()
{
    time += samplingPeriod;
    return time;
}

template<typename State>
inline double ls::primitives::IntegratorNewton<State>::updateTime(double _samplingPeriod)
{
    time += _samplingPeriod;
    return time;
}

#endif //LODESTAR_INTEGRATORNEWTON_HPP
