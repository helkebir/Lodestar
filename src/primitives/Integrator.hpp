//
// Created by Hamza El-Kebir on 4/12/21.
//

#ifndef LODESTAR_INTEGRATOR_HPP
#define LODESTAR_INTEGRATOR_HPP

namespace ls {
    namespace primitives {
        template<typename TState>
        class Integrator {
        public:
            template<typename> friend
            class Integrator;

            virtual void updateState() = 0;

            virtual void updateState(double samplingPeriod) = 0;

            virtual void updateState(TState *curState) = 0;

            virtual void updateState(double samplingPeriod, TState *curState) = 0;

            virtual const TState *getState() const = 0;

            virtual void setState(const TState &state) = 0;

            virtual double updateTime() = 0;

            virtual double updateTime(double samplingPeriod) = 0;

            virtual double getTime() const = 0;

            virtual const TState *getIntegral() const = 0;

        protected:
            TState *state_;
            TState *integral_;

            double samplingPeriod_;
            double time_;
        };
    }
}

#endif //LODESTAR_INTEGRATOR_HPP
