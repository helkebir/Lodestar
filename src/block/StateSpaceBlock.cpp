//
// Created by Hamza El-Kebir on 5/12/21.
//

#include "StateSpaceBlock.hpp"

template<>
const Eigen::MatrixXd &
ls::block::StateSpaceBlock<Eigen::MatrixXd, Eigen::MatrixXd>::process(
        Eigen::MatrixXd &input)
{
    if (_content->isDiscrete()) {
        auto A = _content->getA();
        *_output = A * input;

        return *_output;
    }

    // TODO: Implement logic for continuous time systems.

    return *_output;
}

template<>
Eigen::MatrixXd
ls::block::StateSpaceBlock<Eigen::MatrixXd, Eigen::MatrixXd>::processConst(
        const Eigen::MatrixXd &input) const
{
    if (_content->isDiscrete()) {
        auto A = _content->getA();
        Eigen::MatrixXd output = A * input;

        return output;
    }

    // TODO: Implement logic for continuous time systems.

    return *_output;
}

template<>
Eigen::MatrixXd
ls::block::StateSpaceBlock<Eigen::MatrixXd, Eigen::MatrixXd>::processConst() const
{
    if (_content->isDiscrete()) {
        auto A = _content->getA();
        Eigen::MatrixXd output = A * (*_input);

        return output;
    }

    // TODO: Implement logic for continuous time systems.

    return *_output;
}

template<>
const Eigen::MatrixXd &
ls::block::StateSpaceBlock<Eigen::MatrixXd, Eigen::MatrixXd>::operator()()
{
    return process(*_input);
}

template<>
const Eigen::MatrixXd &
ls::block::StateSpaceBlock<Eigen::MatrixXd, Eigen::MatrixXd>::operator()(
        Eigen::MatrixXd &input)
{
    return process(input);
}

template<>
void ls::block::StateSpaceBlock<Eigen::MatrixXd, Eigen::MatrixXd>::setInput(
        Eigen::MatrixXd &input)
{
    _input = &input;
}

template<>
void ls::block::StateSpaceBlock<Eigen::MatrixXd, Eigen::MatrixXd>::setOutput(
        Eigen::MatrixXd &output)
{
    _output = &output;
}