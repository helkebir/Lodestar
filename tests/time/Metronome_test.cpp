//
// Created by Hamza El-Kebir on 6/13/21.
//

#include "catchOnce.hpp"
#include "Lodestar/time/Metronome.hpp"

TEST_CASE("Metronome test", "[time]") {
    auto metronome = ls::time::Metronome<TimeDuration::milliseconds>(2);
    auto t = std::chrono::high_resolution_clock::now();
    const int N = 3;
    double elapsed;

    for (int i = 0; i < N; i++) {
        while (!metronome.hasElapsed()) {
            elapsed = metronome.timeElapsed();
        }

//        REQUIRE(elapsed == Approx(2).epsilon(1e-1));
    }
}