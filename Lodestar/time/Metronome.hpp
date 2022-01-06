//
// Created by Hamza El-Kebir on 6/13/21.
//

#ifndef LODESTAR_METRONOME_HPP
#define LODESTAR_METRONOME_HPP

#include <chrono>
#include "TimeResolution.hpp"
#include "TimeDuration.hpp"

namespace ls {
    namespace time {
        template <TimeDuration TDuration = TimeDuration::milliseconds, TimeResolution TTimeRes = TimeResolution::HighResolution>
        class Metronome {};

        template <TimeDuration TDuration>
        class Metronome<TDuration, TimeResolution::HighResolution> {
        public:
            using Clock = std::chrono::high_resolution_clock;
            Metronome() : period_(100 * (int) TDuration) {
                last_ = Clock::now();
            }

            Metronome(size_t period) : period_(period * (int) TDuration) {
                last_ = Clock::now();
            }

            bool hasElapsed() {
                auto current = Clock::now();

                if (std::chrono::duration_cast<std::chrono::nanoseconds>(current - last_).count() >= period_) {
                    last_ = current;

                    return true;
                } else {
                    return false;
                }
            }

            double timeElapsed() const {
                auto current = Clock::now();

                return (double) std::chrono::duration_cast<std::chrono::nanoseconds>(current - last_).count() / (int) TDuration;
            }
        protected:
            std::chrono::time_point<Clock, std::chrono::nanoseconds> last_;
            size_t period_;
        };
    }
}

#endif //LODESTAR_METRONOME_HPP
