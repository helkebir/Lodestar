//
// Created by Hamza El-Kebir on 6/17/21.
//

#include "catchOnce.hpp"
#include "Lodestar/core/Status.hpp"
#include "Lodestar/core/StatusOr.hpp"

TEST_CASE("Status", "[static][core]") {
//    ls::core::Status status{};

    ls::core::StatusOr<double> d(2);
    ls::core::StatusOr<float> f(d);
    REQUIRE(f.ok());
    REQUIRE(f.value() == Approx(2));

    f = d;
    REQUIRE(f.ok());
    REQUIRE(f.value() == Approx(2));

//    ls::core::StatusOr<char*> c(f);
//
//    ls::core::StatusOr<char*> c{};
//    c = f;

//    ls::core::util::OkStatus();
}