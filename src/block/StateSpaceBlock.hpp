//
// Created by Hamza El-Kebir on 5/12/21.
//

#ifndef LODESTAR_STATESPACEBLOCK_HPP
#define LODESTAR_STATESPACEBLOCK_HPP

#include "Block.hpp"
#include "systems/StateSpace.hpp"
#include "Eigen/Dense"

namespace ls {
    namespace block {
        template<typename InputType, typename OutputType>
        class StateSpaceBlock : Block<systems::StateSpace<>, InputType, OutputType> {
        public:
            StateSpaceBlock() : _input(new InputType), _output(new OutputType)
            {}

            OutputType processConst() const;

            OutputType processConst(const InputType &input) const;

            const OutputType &process(InputType &input);

            const OutputType &operator()();

            const OutputType &operator()(InputType &input);

            void setInput(InputType &input) = 0;

            void setOutput(OutputType &output) = 0;

        protected:

            InputType *_input;
            OutputType *_output;
        };
    }
}

#endif //LODESTAR_STATESPACEBLOCK_HPP
