//
// Created by Hamza El-Kebir on 12/24/21.
//

#include "catchOnce.hpp"
#include "blocks/std/geometry/QuaternionBlock.hpp"

TEST_CASE("QuaternionBlock", "[blocks][std][geometry]")
{
    SECTION("Scalar parametric input") {
        ls::blocks::std::QuaternionBlock<double> qb;

        Eigen::Vector3d a, b, c;
        a << 1, 0, 0;
        b << 0, 1, 0;

        decltype(qb)::Quaternion quat;
        quat.setFromTwoVectors(a, b);

        qb.quaternion() = quat;
        qb.i<0>() = 1;
        qb.i<1>() = 0;
        qb.i<2>() = 0;
        qb.trigger();

        c << qb.o<0>().object, qb.o<1>().object, qb.o<2>().object;

        REQUIRE((c - b).isZero());
    }

    SECTION("Scalar additional input") {
        ls::blocks::std::QuaternionBlock<double, ls::blocks::std::QuaternionBlockParameter::AdditionalInput> qb;

        Eigen::Vector3d a, b, c;
        a << 1, 0, 0;
        b << 0, 1, 0;

        decltype(qb)::Quaternion quat;
        quat.setFromTwoVectors(a, b);

        qb.quaternion() = quat;
        qb.i<0>() = 1;
        qb.i<1>() = 0;
        qb.i<2>() = 0;
        qb.trigger();

        c << qb.o<0>().object, qb.o<1>().object, qb.o<2>().object;

        REQUIRE((c - b).isZero());
    }

    SECTION("Column vector parametric input") {
        ls::blocks::std::QuaternionBlock<Eigen::Vector3d> qb;

        Eigen::Vector3d a, b;
        a << 1, 0, 0;
        b << 0, 1, 0;

        decltype(qb)::Quaternion quat;
        quat.setFromTwoVectors(a, b);

        qb.quaternion() = quat;
        qb.i<0>() = a;
        qb.trigger();

        REQUIRE((qb.o<0>().object - b).isZero());
    }

    SECTION("Column vector additional input") {
        ls::blocks::std::QuaternionBlock<Eigen::Vector3d, ls::blocks::std::QuaternionBlockParameter::AdditionalInput> qb;

        Eigen::Vector3d a, b;
        a << 1, 0, 0;
        b << 0, 1, 0;

        decltype(qb)::Quaternion quat;
        quat.setFromTwoVectors(a, b);

        qb.quaternion() = quat;
        qb.i<0>() = a;
        qb.trigger();

        REQUIRE((qb.o<0>().object - b).isZero());
    }

    SECTION("Row vector parametric input") {
        ls::blocks::std::QuaternionBlock<Eigen::RowVector3d> qb;

        Eigen::RowVector3d a, b;
        a << 1, 0, 0;
        b << 0, 1, 0;

        decltype(qb)::Quaternion quat;
        quat.setFromTwoVectors(a, b);

        qb.quaternion() = quat;
        qb.i<0>() = a;
        qb.trigger();

        REQUIRE((qb.o<0>().object - b).isZero());
    }

    SECTION("Row vector additional input") {
        ls::blocks::std::QuaternionBlock<Eigen::RowVector3d, ls::blocks::std::QuaternionBlockParameter::AdditionalInput> qb;

        Eigen::RowVector3d a, b;
        a << 1, 0, 0;
        b << 0, 1, 0;

        decltype(qb)::Quaternion quat;
        quat.setFromTwoVectors(a, b);

        qb.quaternion() = quat;
        qb.i<0>() = a;
        qb.trigger();

        REQUIRE((qb.o<0>().object - b).isZero());
    }
}