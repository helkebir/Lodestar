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
            using Base::samplingPeriod_;
            using Base::time_;
            using Base::state_;
            using Base::integral_;

            IntegratorNewton();

            explicit IntegratorNewton(double dt);

            explicit IntegratorNewton(TState *state);

            explicit IntegratorNewton(double dt, TState *state);

            void updateState();

            void updateState(double dt);

            void updateState(TState *_state);

            void updateState(double dt, TState *state);

            const TState *getState() const;

            void setState(const TState &state);

            double updateTime();

            double updateTime(double dt);

            double getTime() const;

            const TState *getIntegral() const;
        };
    }
}

template<typename TState>
inline ls::primitives::IntegratorNewton<TState>::IntegratorNewton()
{
    samplingPeriod_ = 1e-3;
    time_ = 0;
    state_ = new TState{};
    integral_ = new TState{};
}

template<typename TState>
inline ls::primitives::IntegratorNewton<TState>::IntegratorNewton(double dt)
{
    samplingPeriod_ = dt;
    time_ = 0;
    state_ = new TState{};
    integral_ = new TState{};
}

template<typename TState>
inline ls::primitives::IntegratorNewton<TState>::IntegratorNewton(TState *state)
{
    samplingPeriod_ = 1e-3;
    time_ = 0;
    state_ = state;
    integral_ = new TState{};
}

template<typename TState>
inline
ls::primitives::IntegratorNewton<TState>::IntegratorNewton(double dt, TState *state)
{
    samplingPeriod_ = dt;
    time_ = 0;
    state_ = state;
    integral_ = new TState{};
}

template<typename TState>
inline void ls::primitives::IntegratorNewton<TState>::updateState()
{
    updateTime();
    (*integral_) += (*state_) * samplingPeriod_;
}

template<typename TState>
inline void ls::primitives::IntegratorNewton<TState>::updateState(double dt)
{
    updateTime(dt);
    (*integral_) += (*state_) * dt;
}

template<typename TState>
inline void ls::primitives::IntegratorNewton<TState>::updateState(TState *state)
{
    updateTime();
    (*state_) = (*state);
    (*integral_) += (*state_) * samplingPeriod_;
}

template<typename TState>
inline void
ls::primitives::IntegratorNewton<TState>::updateState(double dt, TState *state)
{
    updateTime(dt);
    (*state_) = (*state);
    (*integral_) += (*state_) * dt;
}

template<typename TState>
inline const TState *ls::primitives::IntegratorNewton<TState>::getIntegral() const
{
    return integral_;
}

template<typename TState>
inline double ls::primitives::IntegratorNewton<TState>::updateTime()
{
    time_ += samplingPeriod_;
    return time_;
}

template<typename TState>
inline double ls::primitives::IntegratorNewton<TState>::updateTime(double dt)
{
    time_ += dt;
    return time_;
}

template<typename TState>
const TState *ls::primitives::IntegratorNewton<TState>::getState() const
{
    return state_;
}

template<typename TState>
void ls::primitives::IntegratorNewton<TState>::setState(const TState &state)
{
    *state_ = state;
}

template<typename TState>
double ls::primitives::IntegratorNewton<TState>::getTime() const
{
    return time_;
}

#endif //LODESTAR_INTEGRATORNEWTON_HPP
