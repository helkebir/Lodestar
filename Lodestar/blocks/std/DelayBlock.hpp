//
// Created by Hamza El-Kebir on 2/24/22.
//

#ifndef LODESTAR_DELAYBLOCK_HPP
#define LODESTAR_DELAYBLOCK_HPP

#include <Lodestar/blocks/Block.hpp>
#include <Lodestar/aux/ArrayStack.hpp>

namespace ls {
    namespace blocks {
        namespace std {
            template<typename TInput, unsigned int NDelay=1>
            class DelayBlock
                    : public Block<
                            ::std::tuple<TInput>,
                            ::std::tuple<TInput>,
                            BlockProto::empty
                    > {
            public:
                using Base =
                Block<
                        ::std::tuple<TInput>,
                        ::std::tuple<TInput>,
                        BlockProto::empty
                >;

                DelayBlock()
                {
                    bindFunction();
                }

                void clear(TInput value)
                {
                    fifoStack_.fill(value);
                    this->template o<0>() = value;
                }

                void clear(TInput &value)
                {
                    fifoStack_.fill(value);
                    this->template o<0>() = value;
                }
            protected:
                ls::aux::ArrayStack<TInput, NDelay+1> fifoStack_;
                
                void bindFunction()
                {
                    this->equation = ::std::bind(
                            &DelayBlock<TInput, NDelay>::triggerFunction,
                            this,
                            ::std::placeholders::_1
                    );
                }

                void triggerFunction(Base &b)
                {
                    fifoStack_.push(b.template i<0>().object);
                    b.template o<0>() = fifoStack_.back();
                }
            };
        }

        template<typename TInput, unsigned int NDelay>
        class BlockTraits<std::DelayBlock<TInput, NDelay>> {
        public:
            static constexpr const BlockType blockType = BlockType::DelayBlock;
            enum {
                directFeedthrough = (NDelay < 1)
            };

            using type = std::DelayBlock<TInput, NDelay>;
            using Base = typename type::Base;

            enum {
                kIns = Base::kIns,
                kOuts = Base::kOuts,
                kPars = Base::kPars
            };

            static const ::std::array<::std::string, kIns> inTypes;
            static const ::std::array<::std::string, kOuts> outTypes;
            static const ::std::array<::std::string, kPars> parTypes;

            static const ::std::array<::std::string, 2> templateTypes;
        };

        template<typename TInput, unsigned int NDelay>
        const ::std::array<::std::string, BlockTraits<std::DelayBlock<TInput, NDelay>>::kIns> BlockTraits<std::DelayBlock<TInput, NDelay>>::inTypes =
                {demangle(typeid(TInput).name())};

        template<typename TInput, unsigned int NDelay>
        const ::std::array<::std::string, BlockTraits<std::DelayBlock<TInput, NDelay>>::kOuts> BlockTraits<std::DelayBlock<TInput, NDelay>>::outTypes =
                {demangle(typeid(TInput).name())};

        template<typename TInput, unsigned int NDelay>
        const ::std::array<::std::string, BlockTraits<std::DelayBlock<TInput, NDelay>>::kPars> BlockTraits<std::DelayBlock<TInput, NDelay>>::parTypes =
                {};

        template<typename TInput, unsigned int NDelay>
        const ::std::array<::std::string, 2> BlockTraits<std::DelayBlock<TInput, NDelay>>::templateTypes =
                {demangle(typeid(TInput).name()), "unsigned int"};
    }
}


#endif //LODESTAR_DELAYBLOCK_HPP
