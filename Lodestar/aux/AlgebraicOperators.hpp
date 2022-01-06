//
// Created by Hamza El-Kebir on 6/12/21.
//

#ifndef LODESTAR_ALGEBRAICOPERATORS_HPP
#define LODESTAR_ALGEBRAICOPERATORS_HPP

enum class AlgebraicOperators {
    Addition,
    Subtraction,
    Multiplication,
    Division,
    Exponentiation
};

template <AlgebraicOperators... TOps>
struct AlgebraicOperatorsPack {

};

#endif //LODESTAR_ALGEBRAICOPERATORS_HPP
