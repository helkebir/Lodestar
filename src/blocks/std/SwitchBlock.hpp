//
// Created by Hamza El-Kebir on 12/23/21.
//

#ifndef LODESTAR_SWITCHBLOCK_HPP
#define LODESTAR_SWITCHBLOCK_HPP

#include "blocks/Block.hpp"

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
    }
}


#endif //LODESTAR_SWITCHBLOCK_HPP
