//
// Created by Hamza El-Kebir on 6/13/21.
//

#include "catchOnce.hpp"
#include "time/Metronome.hpp"
#include <iostream>
#include "aux/TypeName.hpp"

TEST_CASE("Metronome test", "[time]") {
    auto metronome = ls::time::Metronome<TimeDuration::milliseconds>(100);
    auto t = std::chrono::high_resolution_clock::now();
    std::cout << "Typename: " << type_name<decltype(t)>() << std::endl;
    std::cout << "Time elapse since last: " << metronome.timeElapsed() << std::endl;
    int N = 3;
    for (int i = 0; i < N; i++) {
        while (!metronome.hasElapsed()) {}

        std::cout << "Metronome triggered " << i << std::endl;
    }
}