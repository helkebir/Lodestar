//
// Created by Hamza El-Kebir on 4/12/21.
//

#ifndef LODESTAR_INTEGRATOR_HPP
#define LODESTAR_INTEGRATOR_HPP

namespace ls { namespace primitives {
    template<typename State>
    class Integrator {
    public:
        State *state;
        State integral;

        double samplingPeriod;
        double time;

        virtual void updateState() = 0;

        virtual void updateState(double samplingPeriod) = 0;

        virtual void updateState(State *curState) = 0;

        virtual void updateState(double samplingPeriod, State *curState) = 0;

        virtual double updateTime() = 0;

        virtual double updateTime(double samplingPeriod) = 0;

        virtual State getIntegral() = 0;
    };
} }

#endif //LODESTAR_INTEGRATOR_HPP
