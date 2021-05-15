//
// Created by Hamza El-Kebir on 5/12/21.
//

#ifndef LODESTAR_BLOCK_HPP
#define LODESTAR_BLOCK_HPP

namespace ls {
    namespace block {
        template<typename ContentType, typename InputType, typename OutputType>
        class Block {
        public:
            typedef ContentType contentType;

            virtual OutputType processConst() const = 0;

            virtual OutputType processConst(const InputType &input) const = 0;

            virtual const OutputType &process(InputType &input) = 0;

            virtual const OutputType &operator()() = 0;

            virtual const OutputType &operator()(InputType &input) = 0;

            virtual void setInput(InputType &input) = 0;

            virtual void setOutput(OutputType &output) = 0;

        protected:
            ContentType *_content;
            InputType *_input;
            OutputType *_output;
        };
    }
}

#endif //LODESTAR_BLOCK_HPP
