//
// Created by Hamza El-Kebir on 12/26/21.
//

#include "catchOnce.hpp"

#include "Lodestar/aux/TemplateTraits.hpp"
#include "Eigen/Dense"

TEST_CASE("TemplateTraits binary operators", "[aux]")
{
    REQUIRE(ls::aux::TemplateTraits::BinaryOperators::isAddable<double, double>::value);
    REQUIRE(::std::is_same<ls::aux::TemplateTraits::BinaryOperators::isAddable<double, double>::returnType, double>::value);
    REQUIRE(!::std::is_same<ls::aux::TemplateTraits::BinaryOperators::isAddable<double, double>::returnType, int>::value);
    REQUIRE(::std::is_same<ls::aux::TemplateTraits::BinaryOperators::isAddable<double, int>::returnType, double>::value);

    REQUIRE(ls::aux::TemplateTraits::BinaryOperators::isSubtractable<double, double>::value);
    REQUIRE(::std::is_same<ls::aux::TemplateTraits::BinaryOperators::isSubtractable<double, double>::returnType, double>::value);
    REQUIRE(!::std::is_same<ls::aux::TemplateTraits::BinaryOperators::isSubtractable<double, double>::returnType, int>::value);
    REQUIRE(::std::is_same<ls::aux::TemplateTraits::BinaryOperators::isSubtractable<double, int>::returnType, double>::value);

    REQUIRE(ls::aux::TemplateTraits::BinaryOperators::isMultiplicable<double, double>::value);
    REQUIRE(::std::is_same<ls::aux::TemplateTraits::BinaryOperators::isMultiplicable<double, double>::returnType, double>::value);
    REQUIRE(!::std::is_same<ls::aux::TemplateTraits::BinaryOperators::isMultiplicable<double, double>::returnType, int>::value);
    REQUIRE(::std::is_same<ls::aux::TemplateTraits::BinaryOperators::isMultiplicable<double, int>::returnType, double>::value);

    REQUIRE(ls::aux::TemplateTraits::BinaryOperators::isDivisble<double, double>::value);
    REQUIRE(::std::is_same<ls::aux::TemplateTraits::BinaryOperators::isDivisble<double, double>::returnType, double>::value);
    REQUIRE(!::std::is_same<ls::aux::TemplateTraits::BinaryOperators::isDivisble<double, double>::returnType, int>::value);
    REQUIRE(::std::is_same<ls::aux::TemplateTraits::BinaryOperators::isDivisble<double, int>::returnType, double>::value);
}

TEST_CASE("TemplateTraits binary operators sanitization", "[aux]")
{
    using sanitizeMultiplicable = ls::aux::TemplateTraits::BinaryOperators::sanitizeTypeMultiplicable<Eigen::Product<Eigen::Matrix3d, Eigen::Vector3d, 0>>;

    REQUIRE(sanitizeMultiplicable::value);
    REQUIRE(::std::is_same<sanitizeMultiplicable::condition1, ::std::true_type>::value);
    REQUIRE(!::std::is_same<sanitizeMultiplicable::condition1, ::std::false_type>::value);
    REQUIRE(::std::is_same<sanitizeMultiplicable::condition2, ::std::true_type>::value);
    REQUIRE(!::std::is_same<sanitizeMultiplicable::condition2, ::std::false_type>::value);
    REQUIRE(::std::is_same<sanitizeMultiplicable::returnType, Eigen::Vector3d>::value);
}