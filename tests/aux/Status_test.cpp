//
// Created by Hamza El-Kebir on 6/17/21.
//

#include "catchOnce.hpp"
#include "aux/Status.hpp"
#include "aux/StatusOr.hpp"

TEST_CASE("Status", "[static][aux]") {
//    ls::aux::Status status{};

    ls::aux::StatusOr<double> d(2);
    ls::aux::StatusOr<float> f(d);
    REQUIRE(f.ok());
    REQUIRE(f.value() == Approx(2));

    f = d;
    REQUIRE(f.ok());
    REQUIRE(f.value() == Approx(2));

//    ls::aux::StatusOr<char*> c(f);
//
//    ls::aux::StatusOr<char*> c{};
//    c = f;

//    ls::aux::util::OkStatus();
}