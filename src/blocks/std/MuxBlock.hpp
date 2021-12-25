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

            template<typename TType, MuxBlockOperator TOps = MuxBlockOperator::RowMajor>
            class MuxBlock :
                    public Block<
                            ::std::tuple<TType>,
                            ::std::tuple<TType>,
                            BlockProto::empty
                    > {
                static_assert(true,
                              "MuxBlock not defined for this type.");
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

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                ((TTRows * TTCols > 0) &&
                                 ((TTRows == 1) ||
                                  (TTCols == 1))), void *>::type * = nullptr>
                Signal<TScalar> &x()
                {
                    return this->template i<0>();
                }

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                !((TTRows * TTCols > 0) &&
                                  ((TTRows == 1) ||
                                   (TTCols == 1))), void *>::type * = nullptr>
                Signal<TScalar> &x()
                {
                    static_assert(
                            (TTRows * TTCols > 0) &&
                            (TTRows == 1 || TTCols == 1),
                            "Mux contains less than 1 input and/or does not map to a 1D object.");
                    return this->template i<0>();
                }

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                ((TTRows * TTCols > 0) &&
                                 (TTRows == 1 ||
                                  TTCols == 1)), void *>::type * = nullptr>
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
                            "Mux contains less than 1 input and/or does not map to a 1D object.");
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
                            "Mux contains less than 2 inputs and/or does not map to a 1D object.");
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
                            "Mux contains less than 2 inputs and/or does not map to a 1D object.");
                    return this->template i<1>();
                }

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                (TTRows * TTCols > 2) &&
                                (TTRows == 1 ||
                                 TTCols == 1), void *>::type * = nullptr>
                Signal<TScalar> &z()
                {
                    return this->template i<2>();
                }

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                !((TTRows * TTCols > 2) &&
                                  (TTRows == 1 ||
                                   TTCols == 1)), void *>::type * = nullptr>
                Signal<TScalar> &z()
                {
                    static_assert(
                            (TTRows * TCols > 2) &&
                            (TTRows == 1 || TTCols == 1),
                            "Mux contains less than 3 inputs and/or does not map to a 1D object.");
                    return this->template i<2>();
                }

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                (TTRows * TTCols > 2) &&
                                (TTRows == 1 ||
                                 TTCols == 1), void *>::type * = nullptr>
                const Signal<TScalar> &z() const
                {
                    return this->template i<2>();
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
                            "Mux contains less than 3 inputs and/or does not map to a 1D object.");
                    return this->template i<2>();
                }

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                (TTRows * TTCols > 3) &&
                                (TTRows == 1 ||
                                 TTCols == 1), void *>::type * = nullptr>
                Signal<TScalar> &w()
                {
                    return this->template i<3>();
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
                            "Mux contains less than 4 inputs and/or does not map to a 1D object.");
                    return this->template i<3>();
                }

                template<int TTRows = TRows, int TTCols = TCols,
                        typename ::std::enable_if<
                                (TTRows * TTCols > 3) &&
                                (TTRows == 1 ||
                                 TTCols == 1), void *>::type * = nullptr>
                const Signal<TScalar> &w() const
                {
                    return this->template i<3>();
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
                            "Mux contains less than 4 inputs and/or does not map to a 1D object.");
                    return this->template i<3>();
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

                template<unsigned int TIdx = TRows * TCols - 1>
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

                template<unsigned int TIdx = TRows * TCols - 1>
                typename ::std::enable_if<(TIdx == 0), void>::type
                set()
                {
                    this->template o<0>().object(0,
                                                 0) = this->template i<TIdx>();
                }

                template<unsigned int TIdx = TRows * TCols - 1>
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

        template<typename TType, std::MuxBlockOperator TOps>
        class BlockTraits<std::MuxBlock<TType, TOps>> {
        public:
            static constexpr const BlockType blockType = BlockType::MuxBlock;
            static constexpr const bool directFeedthrough = true;

            using type = std::MuxBlock<TType, TOps>;
            using Base = typename type::Base;

            static const constexpr int kIns = type::Base::kIns;
            static const constexpr int kOuts = type::Base::kOuts;
            static const constexpr int kPars = type::Base::kPars;
        };
    }
}


#endif //LODESTAR_MUXBLOCK_HPP
