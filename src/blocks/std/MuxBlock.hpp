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
            enum class MuxBlockOperator {
                RowMajor,
                ColMajor
            };

            template<typename TWrapper, MuxBlockOperator TOps = MuxBlockOperator::RowMajor>
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
            template<typename TScalar, int TRows, int TCols, MuxBlockOperator TOps>
            class MuxBlock<Eigen::Matrix<TScalar, TRows, TCols>, TOps> :
                    public Block<
                            typename aux::TemplateTools::repeat<TScalar,
                                    TRows * TCols, ::std::tuple>::type,
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                            ::std::tuple<MuxBlockOperator>
                    > {
            public:
                using Base =
                Block<
                        typename aux::TemplateTools::repeat<TScalar,
                                TRows * TCols, ::std::tuple>::type,
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                        ::std::tuple<MuxBlockOperator>
                >;

                MuxBlock()
                {
                    setOperator(TOps);
                    bindEquation();
                }

                explicit MuxBlock(const MuxBlockOperator ops)
                {
                    setOperator(ops);
                    bindEquation();
                }

                void setOperator(const MuxBlockOperator ops)
                {
                    this->template p<0>() = ops;
                }

                MuxBlockOperator getOperator() const
                {
                    return this->template p<0>();
                }

            protected:
                void bindEquation()
                {
                    this->equation = ::std::bind(
                            &MuxBlock<Eigen::Matrix<TScalar, TRows, TCols>, TOps>::triggerFunction,
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
                    switch (getOperator()) {
                        case MuxBlockOperator::RowMajor:
                            this->template o<0>().object(
                                    floor<int, double>(TIdx / TCols),
                                    TIdx -
                                    floor<int, double>(TIdx / TCols) * TCols)
                                    = this->template i<TIdx>();
                            break;
                        case MuxBlockOperator::ColMajor:
                            this->template o<0>().object(
                                    TIdx -
                                    floor<int, double>(TIdx / TRows) * TRows,
                                    floor<int, double>(TIdx / TRows))
                                    = this->template i<TIdx>();
                            break;
                    }
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

            template<typename... TTypes, MuxBlockOperator TOps>
            class MuxBlock<::std::tuple<TTypes...>, TOps> :
                    public Block<
                            ::std::tuple<TTypes...>,
                            ::std::tuple<::std::tuple<TTypes...>>,
                            ::std::tuple<MuxBlockOperator>
                    > {
            public:
                using Base =
                Block<
                        ::std::tuple<TTypes...>,
                        ::std::tuple<::std::tuple<TTypes...>>,
                        ::std::tuple<MuxBlockOperator>
                >;

                MuxBlock()
                {
                    setOperator(TOps);
                    bindEquation();
                }

                explicit MuxBlock(const MuxBlockOperator ops)
                {
                    setOperator(ops);
                    bindEquation();
                }

                void setOperator(const MuxBlockOperator ops)
                {
                    this->template p<0>() = ops;
                }

                MuxBlockOperator getOperator() const
                {
                    return this->template p<0>();
                }

            protected:
                void bindEquation()
                {
                    this->equation = ::std::bind(
                            &MuxBlock<::std::tuple<TTypes...>, TOps>::triggerFunction,
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
