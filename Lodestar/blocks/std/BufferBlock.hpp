//
// Created by Hamza El-Kebir on 2/19/22.
//

#ifndef LODESTAR_BUFFERBLOCK_HPP
#define LODESTAR_BUFFERBLOCK_HPP

#include <Lodestar/blocks/Block.hpp>

namespace ls {
    namespace blocks {
        namespace std {
            template<typename TInput, unsigned int NSize=2>
            class BufferBlock
                    : public Block<
                            ::std::tuple<TInput>,
                            typename ls::aux::TemplateTools::repeat<TInput, NSize, ::std::tuple>::type,
                            BlockProto::empty
                    > {
            public:
                using Base =
                Block<
                        ::std::tuple<TInput>,
                        typename ls::aux::TemplateTools::repeat<TInput, NSize, ::std::tuple>::type,
                        BlockProto::empty
                >;

                BufferBlock()
                {
                    bindFunction();
                }

                void clear(TInput value)
                {
                    return clear_(value);
                }

                void clear(TInput &value)
                {
                    return clearRef_(value);
                }


            protected:
                void bindFunction()
                {
                    this->equation = ::std::bind(
                            &BufferBlock<TInput, NSize>::triggerFunction,
                            this,
                            ::std::placeholders::_1
                    );
                }

                void triggerFunction(Base &b)
                {
                    update();
                }

                template<unsigned int NIdx = NSize - 1>
                typename ::std::enable_if<(NIdx > 0), void>::type
                update()
                {
                    this->template o<NIdx>().object = this->template o<NIdx-1>().object;
                    this->template o<NIdx>().propagate();

                    return update<NIdx - 1>();
                }

                template<unsigned int NIdx = NSize - 1>
                typename ::std::enable_if<(NIdx == 0), void>::type
                update()
                {
                    this->template o<NIdx>() = this->template i<NIdx>(); 
                }

                template<unsigned int NIdx = NSize - 1>
                typename ::std::enable_if<(NIdx < 0), void>::type
                update()
                {
                    return;
                }

                template<unsigned int NIdx = NSize - 1>
                typename ::std::enable_if<(NIdx > 0), void>::type
                clearRef_(const TInput &value)
                {
                    this->template o<NIdx>() = value;

                    return clearRef_<NIdx - 1>(value);
                }

                template<unsigned int NIdx = NSize - 1>
                typename ::std::enable_if<(NIdx == 0), void>::type
                clearRef_(const TInput &value)
                {
                    this->template o<NIdx>() = value;
                }

                template<unsigned int NIdx = NSize - 1>
                typename ::std::enable_if<(NIdx < 0), void>::type
                clearRef_(const TInput &value)
                {
                    return;
                }

                template<unsigned int NIdx = NSize - 1>
                typename ::std::enable_if<(NIdx > 0), void>::type
                clear_(const TInput value)
                {
                    this->template o<NIdx>() = value;

                    return clear_<NIdx - 1>(value);
                }

                template<unsigned int NIdx = NSize - 1>
                typename ::std::enable_if<(NIdx == 0), void>::type
                clear_(const TInput value)
                {
                    this->template o<NIdx>() = value;
                }

                template<unsigned int NIdx = NSize - 1>
                typename ::std::enable_if<(NIdx < 0), void>::type
                clear_(const TInput value)
                {
                    return;
                }
            };
        }

        template<typename TInput, unsigned int NSize>
        class BlockTraits<std::BufferBlock<TInput, NSize>> {
        public:
            static constexpr const BlockType blockType = BlockType::BufferBlock;
            enum {
                directFeedthrough = true
            };

            using type = std::BufferBlock<TInput, NSize>;
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

        template<typename TInput, unsigned int NSize>
        const ::std::array<::std::string, BlockTraits<std::BufferBlock<TInput, NSize>>::kIns> BlockTraits<std::BufferBlock<TInput, NSize>>::inTypes =
                {demangle(typeid(TInput).name())};

        template<typename TInput, unsigned int NSize>
        const ::std::array<::std::string, BlockTraits<std::BufferBlock<TInput, NSize>>::kOuts> BlockTraits<std::BufferBlock<TInput, NSize>>::outTypes =
                {demangle(typeid(TInput).name())};

        template<typename TInput, unsigned int NSize>
        const ::std::array<::std::string, BlockTraits<std::BufferBlock<TInput, NSize>>::kPars> BlockTraits<std::BufferBlock<TInput, NSize>>::parTypes =
                {};

        template<typename TInput, unsigned int NSize>
        const ::std::array<::std::string, 2> BlockTraits<std::BufferBlock<TInput, NSize>>::templateTypes =
                {demangle(typeid(TInput).name()), "unsigned int"};
    }
}

#endif //LODESTAR_BUFFERBLOCK_HPP
