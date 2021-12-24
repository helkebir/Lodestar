//
// Created by Hamza El-Kebir on 12/23/21.
//

#ifndef LODESTAR_DEMUXBLOCK_HPP
#define LODESTAR_DEMUXBLOCK_HPP

#include "blocks/Block.hpp"
#include "aux/TemplateTools.hpp"
#include "aux/CompileTimeQualifiers.hpp"
#include "Eigen/Dense"

namespace ls {
    namespace blocks {
        namespace std {
            enum class DemuxBlockOperator {
                RowMajor,
                ColMajor
            };

            template<typename TWrapper, DemuxBlockOperator TOps = DemuxBlockOperator::RowMajor>
            class DemuxBlock :
                    public Block<
                            ::std::tuple<TWrapper>,
                            ::std::tuple<TWrapper>,
                            ::std::tuple<DemuxBlockOperator>
                    > {
                static_assert(true,
                              "MuxBlock not defined for this wrapper.");
            };

            // TODO: Look into support for dynamically size matrices.
            template<typename TScalar, int TRows, int TCols, DemuxBlockOperator TOps>
            class DemuxBlock<Eigen::Matrix<TScalar, TRows, TCols>, TOps> :
                    public Block<
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                            typename aux::TemplateTools::repeat<TScalar,
                                    TRows * TCols, ::std::tuple>::type,
                            ::std::tuple<DemuxBlockOperator>
                    > {
            public:
                using Base =
                Block<
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                        typename aux::TemplateTools::repeat<TScalar,
                                TRows * TCols, ::std::tuple>::type,
                        ::std::tuple<DemuxBlockOperator>
                >;

                DemuxBlock()
                {
                    setOperator(TOps);
                    bindEquation();
                }

                explicit DemuxBlock(const DemuxBlockOperator ops)
                {
                    setOperator(ops);
                    bindEquation();
                }

                void setOperator(const DemuxBlockOperator ops)
                {
                    this->template p<0>() = ops;
                }

                DemuxBlockOperator getOperator() const
                {
                    return this->template p<0>();
                }

            protected:
                void bindEquation()
                {
                    this->equation = ::std::bind(
                            &DemuxBlock<Eigen::Matrix<TScalar, TRows, TCols>, TOps>::triggerFunction,
                            this,
                            ::std::placeholders::_1
                    );
                }

                void triggerFunction(Base &b)
                {
                    get();
                }

                template<unsigned int TIdx = Base::kOuts - 1>
                typename ::std::enable_if<(TIdx > 0), void>::type
                get()
                {
                    switch (getOperator()) {
                        case DemuxBlockOperator::RowMajor:
                            this->template o<TIdx>() = this->template i<0>().object(
                                    floor<int, double>(TIdx / TCols),
                                    TIdx -
                                    floor<int, double>(TIdx / TCols) * TCols
                            );
                            break;
                        case DemuxBlockOperator::ColMajor:
                            this->template o<TIdx>() = this->template i<0>().object(
                                    TIdx -
                                    floor<int, double>(TIdx / TRows) * TRows,
                                    floor<int, double>(TIdx / TRows));
                            break;
                    }
                    return get<TIdx - 1>();
                }

                template<unsigned int TIdx = Base::kOuts - 1>
                typename ::std::enable_if<(TIdx == 0), void>::type
                get()
                {
                    this->template o<TIdx>() = this->template i<0>().object(0,
                                                                            0);
                }

                template<unsigned int TIdx = Base::kOuts - 1>
                typename ::std::enable_if<(TIdx < 0), void>::type
                get()
                {
                    return;
                }
            };

            template<typename... TTypes, DemuxBlockOperator TOps>
            class DemuxBlock<::std::tuple<TTypes...>, TOps> :
                    public Block<
                            ::std::tuple<::std::tuple<TTypes...>>,
                            ::std::tuple<TTypes...>,
                            ::std::tuple<DemuxBlockOperator>
                    > {
            public:
                using Base =
                Block<
                        ::std::tuple<::std::tuple<TTypes...>>,
                        ::std::tuple<TTypes...>,
                        ::std::tuple<DemuxBlockOperator>
                >;

                DemuxBlock()
                {
                    setOperator(TOps);
                    bindEquation();
                }

                explicit DemuxBlock(const DemuxBlockOperator ops)
                {
                    setOperator(ops);
                    bindEquation();
                }

                void setOperator(const DemuxBlockOperator ops)
                {
                    this->template p<0>() = ops;
                }

                DemuxBlockOperator getOperator() const
                {
                    return this->template p<0>();
                }

            protected:
                void bindEquation()
                {
                    this->equation = ::std::bind(
                            &DemuxBlock<::std::tuple<TTypes...>, TOps>::triggerFunction,
                            this,
                            ::std::placeholders::_1
                    );
                }

                void triggerFunction(Base &b)
                {
                    get();
                }

                template<unsigned int TIdx = Base::kOuts - 1>
                typename ::std::enable_if<(TIdx > 0), void>::type
                get()
                {
                    this->template o<TIdx>() = ::std::get<TIdx>(
                            this->template i<0>().object);
                    return get<TIdx - 1>();
                }

                template<unsigned int TIdx = Base::kOuts - 1>
                typename ::std::enable_if<(TIdx == 0), void>::type
                get()
                {
                    this->template o<TIdx>() = ::std::get<TIdx>(
                            this->template i<0>().object);
                }

                template<unsigned int TIdx = Base::kOuts - 1>
                typename ::std::enable_if<(TIdx < 0), void>::type
                get()
                {
                    return;
                }
            };
        }
    }
}


#endif //LODESTAR_DEMUXBLOCK_HPP
