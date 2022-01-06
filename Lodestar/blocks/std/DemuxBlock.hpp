//
// Created by Hamza El-Kebir on 12/23/21.
//

#ifndef LODESTAR_DEMUXBLOCK_HPP
#define LODESTAR_DEMUXBLOCK_HPP

#include "Lodestar/blocks/Block.hpp"
#include "Lodestar/aux/TemplateTools.hpp"
#include "Lodestar/aux/CompileTimeQualifiers.hpp"
#include "Eigen/Dense"

namespace ls {
    namespace blocks {
        namespace std {
            enum class DemuxBlockOperator {
                RowMajor,
                ColMajor
            };

            template<typename TType, DemuxBlockOperator TOps = DemuxBlockOperator::RowMajor>
            class DemuxBlock :
                    public Block<
                            ::std::tuple<TType>,
                            ::std::tuple<TType>,
                            ::std::tuple<DemuxBlockOperator>
                    > {
                static_assert(true,
                              "DemuxBlock not defined for this type.");
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

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                ((TTRows * TTCols > 0) &&
                                 (TTRows == 1 ||
                                  TTCols == 1)), void *>::type * = nullptr>
                Signal<TScalar> &x()
                {
                    return this->template i<0>();
                }

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                !((TTRows * TTCols > 0) &&
                                  (TTRows == 1 ||
                                   TTCols == 1)), void *>::type * = nullptr>
                Signal<TScalar> &x()
                {
                    static_assert(
                            (TTRows * TTCols > 0) &&
                            (TTRows == 1 || TTCols == 1),
                            "Demux contains less than 1 output and/or does not map to a 1D object.");
                    return this->template i<0>();
                }

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                (TTRows * TTCols > 0) &&
                                (TTRows == 1 ||
                                 TTCols == 1), void *>::type * = nullptr>
                const Signal<TScalar> &x() const
                {
                    return this->template i<0>();
                }

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                !((TTRows * TTCols > 0) &&
                                  (TTRows == 1 ||
                                   TTCols == 1)), void *>::type * = nullptr>
                const Signal<TScalar> &x() const
                {
                    static_assert(
                            (TTRows * TTCols > 0) &&
                            (TTRows == 1 || TTCols == 1),
                            "Demux contains less than 1 output and/or does not map to a 1D object.");
                    return this->template i<0>();
                }

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                (TTRows * TTCols > 1) &&
                                (TTRows == 1 ||
                                 TTCols == 1), void *>::type * = nullptr>
                Signal<TScalar> &y()
                {
                    return this->template i<1>();
                }

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                !((TTRows * TTCols > 1) &&
                                  (TTRows == 1 ||
                                   TTCols == 1)), void *>::type * = nullptr>
                Signal<TScalar> &y()
                {
                    static_assert(
                            (TTRows * TTCols > 1) &&
                            (TTRows == 1 || TTCols == 1),
                            "Demux contains less than 2 outputs and/or does not map to a 1D object.");
                    return this->template i<1>();
                }

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                (TTRows * TTCols > 1) &&
                                (TTRows == 1 ||
                                 TTCols == 1), void *>::type * = nullptr>
                const Signal<TScalar> &y() const
                {
                    return this->template i<1>();
                }

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                !((TTRows * TTCols > 1) &&
                                  (TTRows == 1 ||
                                   TTCols == 1)), void *>::type * = nullptr>
                const Signal<TScalar> &y() const
                {
                    static_assert(
                            (TTRows * TTCols > 1) &&
                            (TTRows == 1 || TTCols == 1),
                            "Demux contains less than 2 outputs and/or does not map to a 1D object.");
                    return this->template i<1>();
                }

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                (TTRows * TTCols > 2) &&
                                (TTRows == 1 ||
                                 TTCols == 1), void *>::type * = nullptr>
                Signal<TScalar> &z()
                {
                    return this->template o<2>();
                }

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                !((TTRows * TTCols > 2) &&
                                  (TTRows == 1 ||
                                   TTCols == 1)), void *>::type * = nullptr>
                Signal<TScalar> &z()
                {
                    static_assert(
                            (TTRows * TTCols > 2) &&
                            (TTRows == 1 || TTCols == 1),
                            "Demux contains less than 3 outputs and/or does not map to a 1D object.");
                    return this->template o<2>();
                }

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                (TTRows * TTCols > 2) &&
                                (TTRows == 1 ||
                                 TTCols == 1), void *>::type * = nullptr>
                const Signal<TScalar> &z() const
                {
                    return this->template o<2>();
                }

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                !((TTRows * TTCols > 2) &&
                                  (TTRows == 1 ||
                                   TTCols == 1)), void *>::type * = nullptr>
                const Signal<TScalar> &z() const
                {
                    static_assert(
                            (TTRows * TTCols > 2) &&
                            (TTRows == 1 || TTCols == 1),
                            "Demux contains less than 3 outputs and/or does not map to a 1D object.");
                    return this->template o<2>();
                }

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                (TTRows * TTCols > 3) &&
                                (TTRows == 1 ||
                                 TTCols == 1), void *>::type * = nullptr>
                Signal<TScalar> &w()
                {
                    return this->template o<3>();
                }

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                !((TTRows * TTCols > 3) &&
                                  (TTRows == 1 ||
                                   TTCols == 1)), void *>::type * = nullptr>
                Signal<TScalar> &w()
                {
                    static_assert(
                            (TTRows * TTCols > 3) &&
                            (TTRows == 1 || TTCols == 1),
                            "Demux contains less than 4 outputs and/or does not map to a 1D object.");
                    return this->template o<3>();
                }

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                (TTRows * TTCols > 3) &&
                                (TTRows == 1 ||
                                 TTCols == 1), void *>::type * = nullptr>
                const Signal<TScalar> &w() const
                {
                    return this->template o<3>();
                }

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                !((TTRows * TTCols > 3) &&
                                  (TTRows == 1 ||
                                   TTCols == 1)), void *>::type * = nullptr>
                const Signal<TScalar> &w() const
                {
                    static_assert(
                            (TTRows * TTCols > 3) &&
                            (TTRows == 1 || TTCols == 1),
                            "Demux contains less than 4 outputs and/or does not map to a 1D object.");
                    return this->template o<3>();
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

                template<unsigned int TIdx = TRows * TCols - 1>
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

                template<unsigned int TIdx = TRows * TCols - 1>
                typename ::std::enable_if<(TIdx == 0), void>::type
                get()
                {
                    this->template o<TIdx>() = this->template i<0>().object(0,
                                                                            0);
                }

                template<unsigned int TIdx = TRows * TCols - 1>
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

        template<typename TType, std::DemuxBlockOperator TOps>
        class BlockTraits<std::DemuxBlock<TType, TOps>> {
        public:
            static constexpr const BlockType blockType = BlockType::DemuxBlock;
            static constexpr const bool directFeedthrough = true;

            using type = std::DemuxBlock<TType, TOps>;
            using Base = typename type::Base;

            static const constexpr int kIns = type::Base::kIns;
            static const constexpr int kOuts = type::Base::kOuts;
            static const constexpr int kPars = type::Base::kPars;
        };
    }
}


#endif //LODESTAR_DEMUXBLOCK_HPP
