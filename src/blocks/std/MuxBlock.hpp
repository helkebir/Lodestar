//
// Created by Hamza El-Kebir on 12/23/21.
//

#ifndef LODESTAR_MUXBLOCK_HPP
#define LODESTAR_MUXBLOCK_HPP

#include "blocks/Block.hpp"
#include "aux/TemplateTools.hpp"
#include "aux/CompileTimeQualifiers.hpp"
#include "Eigen/Dense"

namespace ls {
    namespace blocks {
        namespace std {
            template<typename TWrapper>
            class MuxBlock :
                    public Block<
                            ::std::tuple<TWrapper>,
                            ::std::tuple<TWrapper>,
                            BlockProto::empty
                    > {
                static_assert(true,
                              "MuxBlock not defined for this wrapper.");
            };

            // TODO: Look into support for dynamically size matrices.
            template<typename TScalar, int TRows, int TCols>
            class MuxBlock<Eigen::Matrix<TScalar, TRows, TCols>> :
                    public Block<
                            typename aux::TemplateTools::repeat<TScalar,
                                    TRows * TCols, ::std::tuple>::type,
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                            BlockProto::empty
                    > {
            public:
                using Base =
                Block<
                        typename aux::TemplateTools::repeat<TScalar,
                                TRows * TCols, ::std::tuple>::type,
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                        BlockProto::empty
                >;

                MuxBlock()
                {
                    bindEquation();
                }

            protected:
                void bindEquation()
                {
                    this->equation = ::std::bind(
                            &MuxBlock<Eigen::Matrix<TScalar, TRows, TCols>>::triggerFunction,
                            this,
                            ::std::placeholders::_1
                    );
                }

                void triggerFunction(Base &b)
                {
                    set();
                }

                template<unsigned int TIdx = Base::kIns - 1>
                typename ::std::enable_if<(TIdx > 0), void>::type
                set()
                {
                    this->template o<0>().object(
                            TIdx - floor<int, double>(TIdx / TRows) * TRows,
                            floor<int, double>(
                                    TIdx / TRows)) = this->template i<TIdx>();
                    return set<TIdx - 1>();
                }

                template<unsigned int TIdx = Base::kIns - 1>
                typename ::std::enable_if<(TIdx == 0), void>::type
                set()
                {
                    this->template o<0>().object(0,
                                                 0) = this->template i<TIdx>();
                }

                template<unsigned int TIdx = Base::kIns - 1>
                typename ::std::enable_if<(TIdx < 0), void>::type
                set()
                {
                    return;
                }
            };

            template<typename... TTypes>
            class MuxBlock<::std::tuple<TTypes...>> :
                    public Block<
                            ::std::tuple<TTypes...>,
                            ::std::tuple<::std::tuple<TTypes...>>,
                            BlockProto::empty
                    > {
            public:
                using Base =
                Block<
                        ::std::tuple<TTypes...>,
                        ::std::tuple<::std::tuple<TTypes...>>,
                        BlockProto::empty
                >;

                MuxBlock()
                {
                    bindEquation();
                }

            protected:
                void bindEquation()
                {
                    this->equation = ::std::bind(
                            &MuxBlock<::std::tuple<TTypes...>>::triggerFunction,
                            this,
                            ::std::placeholders::_1
                    );
                }

                void triggerFunction(Base &b)
                {
                    set();
                }

                template<unsigned int TIdx = Base::kIns - 1>
                typename ::std::enable_if<(TIdx > 0), void>::type
                set()
                {
                    ::std::get<TIdx>(
                            this->template o<0>().object) = this->template i<TIdx>().object;
                    return set<TIdx - 1>();
                }

                template<unsigned int TIdx = Base::kIns - 1>
                typename ::std::enable_if<(TIdx == 0), void>::type
                set()
                {
                    ::std::get<TIdx>(
                            this->template o<0>().object) = this->template i<TIdx>().object;
                    this->template o<0>().propagate();
                }

                template<unsigned int TIdx = Base::kIns - 1>
                typename ::std::enable_if<(TIdx < 0), void>::type
                set()
                {
                    return;
                }
            };
        }
    }
}


#endif //LODESTAR_MUXBLOCK_HPP
