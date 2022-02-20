//
// Created by Hamza El-Kebir on 12/23/21.
//

#ifndef LODESTAR_SWITCHBLOCK_HPP
#define LODESTAR_SWITCHBLOCK_HPP

#include "Lodestar/blocks/Block.hpp"

namespace ls {
    namespace blocks {
        namespace std {
            enum class SwitchBlockParameter {
                Parametric,
                AdditionalInput
            };

            template<typename TType,
                    SwitchBlockParameter TPar = SwitchBlockParameter::Parametric>
            class SwitchBlock {
                static_assert(::std::is_same<TType, TType>::value,
                              "SwitchBlock not defined for this type.");
            };

            template<typename TType>
            class SwitchBlock<TType, SwitchBlockParameter::Parametric> :
                    public Block<
                            ::std::tuple<TType, TType>,
                            ::std::tuple<TType>,
                            ::std::tuple<bool>
                    > {
            public:
                using Base =
                Block<
                        ::std::tuple<TType, TType>,
                        ::std::tuple<TType>,
                        ::std::tuple<bool>
                >;

                using type = SwitchBlock<TType, SwitchBlockParameter::Parametric>;

                SwitchBlock()
                {
                    state(false);
                    bindEquation();
                }

                SwitchBlock(const bool switchState)
                {
                    state(switchState);
                    bindEquation();
                }

                bool &state(bool setting)
                {
                    this->template p<0>() = setting;
                    return this->template p<0>();
                }

                bool state() const
                {
                    return this->template p<0>();
                }

                bool &state()
                {
                    return this->template p<0>();
                }

                void toggle()
                {
                    state(!state());
                }

            protected:
                void bindEquation()
                {
                    this->equation = ::std::bind(
                            &type::triggerFunction,
                            this,
                            ::std::placeholders::_1
                    );
                }

                void triggerFunction(Base &b)
                {
                    if (state())
                        this->template o<0>() = this->template i<1>();
                    else
                        this->template o<0>() = this->template i<0>();
                }
            };

            template<typename TType>
            class SwitchBlock<TType, SwitchBlockParameter::AdditionalInput> :
                    public Block<
                            ::std::tuple<TType, TType, bool>,
                            ::std::tuple<TType>,
                            BlockProto::empty
                    > {
            public:
                using Base =
                Block<
                        ::std::tuple<TType, TType, bool>,
                        ::std::tuple<TType>,
                        BlockProto::empty
                >;

                using type = SwitchBlock<TType, SwitchBlockParameter::AdditionalInput>;

                SwitchBlock()
                {
                    state(false);
                    bindEquation();
                }

                SwitchBlock(const bool switchState)
                {
                    state(switchState);
                    bindEquation();
                }

                Signal<bool> &state(bool setting)
                {
                    this->template i<2>() = setting;
                    return this->template i<2>();
                }

                Signal<bool> &state(const Signal<bool> &setting)
                {
                    this->template i<2>() = setting;
                    return this->template i<2>();
                }

                const Signal<bool> &state() const
                {
                    return this->template i<2>();
                }

                Signal<bool> &state()
                {
                    return this->template i<2>();
                }

                void toggle()
                {
                    state(!state().object);
                }

            protected:
                void bindEquation()
                {
                    this->equation = ::std::bind(
                            &type::triggerFunction,
                            this,
                            ::std::placeholders::_1
                    );
                }

                void triggerFunction(Base &b)
                {
                    if (state().object)
                        this->template o<0>() = this->template i<1>();
                    else
                        this->template o<0>() = this->template i<0>();
                }
            };

        }

        template<typename TType>
        class BlockTraits<std::SwitchBlock<TType, std::SwitchBlockParameter::AdditionalInput>> {
        public:
            static constexpr const BlockType blockType = BlockType::SwitchBlock;
            enum {
                directFeedthrough = true
            };

            using type = std::SwitchBlock<TType, std::SwitchBlockParameter::AdditionalInput>;
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

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::SwitchBlock<TType, std::SwitchBlockParameter::AdditionalInput>>::kIns> BlockTraits<std::SwitchBlock<TType, std::SwitchBlockParameter::AdditionalInput>>::inTypes =
                {demangle(typeid(TType).name())};

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::SwitchBlock<TType, std::SwitchBlockParameter::AdditionalInput>>::kOuts> BlockTraits<std::SwitchBlock<TType, std::SwitchBlockParameter::AdditionalInput>>::outTypes =
                {demangle(typeid(TType).name())};

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::SwitchBlock<TType, std::SwitchBlockParameter::AdditionalInput>>::kPars> BlockTraits<std::SwitchBlock<TType, std::SwitchBlockParameter::AdditionalInput>>::parTypes =
                {};

        template<typename TType>
        const ::std::array<::std::string, 2> BlockTraits<std::SwitchBlock<TType, std::SwitchBlockParameter::AdditionalInput>>::templateTypes =
                {demangle(typeid(TType).name()), demangle(typeid(std::SwitchBlockParameter::AdditionalInput).name())};

        template<typename TType>
        class BlockTraits<std::SwitchBlock<TType, std::SwitchBlockParameter::Parametric>> {
        public:
            static constexpr const BlockType blockType = BlockType::SwitchBlock;
            enum {
                directFeedthrough = true
            };

            using type = std::SwitchBlock<TType, std::SwitchBlockParameter::AdditionalInput>;
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

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::SwitchBlock<TType, std::SwitchBlockParameter::Parametric>>::kIns> BlockTraits<std::SwitchBlock<TType, std::SwitchBlockParameter::Parametric>>::inTypes =
                {demangle(typeid(TType).name())};

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::SwitchBlock<TType, std::SwitchBlockParameter::Parametric>>::kOuts> BlockTraits<std::SwitchBlock<TType, std::SwitchBlockParameter::Parametric>>::outTypes =
                {demangle(typeid(TType).name())};

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::SwitchBlock<TType, std::SwitchBlockParameter::Parametric>>::kPars> BlockTraits<std::SwitchBlock<TType, std::SwitchBlockParameter::Parametric>>::parTypes =
                {"bool"};

        template<typename TType>
        const ::std::array<::std::string, 2> BlockTraits<std::SwitchBlock<TType, std::SwitchBlockParameter::Parametric>>::templateTypes =
                {demangle(typeid(TType).name()), demangle(typeid(std::SwitchBlockParameter::Parametric).name())};


    }
}


#endif //LODESTAR_SWITCHBLOCK_HPP
