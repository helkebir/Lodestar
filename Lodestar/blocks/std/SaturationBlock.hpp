//
// Created by Hamza El-Kebir on 12/23/21.
//

#ifndef LODESTAR_SATURATIONBLOCK_HPP
#define LODESTAR_SATURATIONBLOCK_HPP

#include "Lodestar/blocks/Block.hpp"
#include "Lodestar/aux/CompileTimeQualifiers.hpp"
#include "Eigen/Dense"

namespace ls {
    namespace blocks {
        namespace std {
            enum class SaturationBlockOperator {
                Scalar,
                Elementwise
            };

            enum class SaturationBlockParameter {
                Parametric,
                AdditionalInput
            };

            template<typename TType,
                    SaturationBlockOperator TOps = SaturationBlockOperator::Scalar,
                    SaturationBlockParameter TPar = SaturationBlockParameter::Parametric>
            class SaturationBlock {
                static_assert(!::std::is_same<TType, TType>::value,
                              "SaturationBlock not defined for this type.");
            };

            template<typename TType, SaturationBlockOperator TOps>
            class SaturationBlock<
                    TType,
                    TOps,
                    SaturationBlockParameter::Parametric
            > :
                    public Block<
                            ::std::tuple<TType>,
                            ::std::tuple<TType>,
                            ::std::tuple<TType, TType>
                    > {
            public:
                using type =
                SaturationBlock<
                        TType,
                        TOps,
                        SaturationBlockParameter::Parametric
                >;

                using Base =
                Block<
                        ::std::tuple<TType>,
                        ::std::tuple<TType>,
                        ::std::tuple<TType, TType>
                >;

                SaturationBlock()
                {
                    bindEquation();
                }

                TType &lower()
                {
                    return this->template p<0>();
                }

                TType &lower(const TType lo)
                {
                    this->template p<0>() = lo;
                    return this->template p<0>();
                }

                TType lower() const
                {
                    return this->template p<0>();
                }

                TType &upper()
                {
                    return this->template p<1>();
                }

                TType &upper(const TType up)
                {
                    this->template p<1>() = up;
                    return this->template p<1>();
                }

                TType upper() const
                {
                    return this->template p<1>();
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

                TType saturate(const TType x) const
                {
                    return (x < lower() ? lower() :
                            (x > upper() ? upper() : x));
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>() = saturate(b.template i<0>().object);
                }
            };

            template<typename TType, SaturationBlockOperator TOps>
            class SaturationBlock<
                    TType,
                    TOps,
                    SaturationBlockParameter::AdditionalInput
            > :
                    public Block<
                            ::std::tuple<TType, TType, TType>,
                            ::std::tuple<TType>,
                            ::std::tuple<TType>
                    > {
            public:
                using type =
                SaturationBlock<
                        TType,
                        TOps,
                        SaturationBlockParameter::AdditionalInput
                >;

                using Base =
                Block<
                        ::std::tuple<TType, TType, TType>,
                        ::std::tuple<TType>,
                        ::std::tuple<TType>
                >;

                SaturationBlock()
                {
                    bindEquation();
                }

                Signal<TType> &lower()
                {
                    return this->template i<1>();
                }

                Signal<TType> &lower(const TType &lo)
                {
                    this->template i<1>() = lo;
                    return this->template i<1>();
                }

                Signal<TType> &lower(const Signal<TType> &lo)
                {
                    this->template i<1>() = lo;
                    return this->template i<1>();
                }

                const Signal<TType> &lower() const
                {
                    return this->template i<1>();
                }

                Signal<TType> &upper()
                {
                    return this->template i<2>();
                }

                Signal<TType> &upper(const TType &up)
                {
                    this->template i<2>() = up;
                    return this->template i<2>();
                }

                Signal<TType> &upper(const Signal<TType> up)
                {
                    this->template i<2>() = up;
                    return this->template i<2>();
                }

                const Signal<TType> &upper() const
                {
                    return this->template i<2>();
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

                TType saturate(const TType x) const
                {
                    return (x < lower().object ? lower().object :
                            (x > upper().object ? upper().object : x));
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>() = saturate(b.template i<0>().object);
                }
            };

            template<typename TScalar, int TRows, int TCols>
            class SaturationBlock<
                    Eigen::Matrix<TScalar, TRows, TCols>,
                    SaturationBlockOperator::Scalar,
                    SaturationBlockParameter::Parametric
            > :
                    public Block<
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                            ::std::tuple<TScalar, TScalar>
                    > {
            public:
                using type =
                SaturationBlock<
                        Eigen::Matrix<TScalar, TRows, TCols>,
                        SaturationBlockOperator::Scalar,
                        SaturationBlockParameter::Parametric
                >;

                using Base =
                Block<
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                        ::std::tuple<TScalar, TScalar>
                >;

                SaturationBlock()
                {
                    bindEquation();
                }

                TScalar &lower()
                {
                    return this->template p<0>();
                }

                TScalar &lower(const TScalar lo)
                {
                    this->template p<0>() = lo;
                    return this->template p<0>();
                }

                TScalar lower() const
                {
                    return this->template p<0>();
                }

                TScalar &upper()
                {
                    return this->template p<1>();
                }

                TScalar &upper(const TScalar up)
                {
                    this->template p<1>() = up;
                    return this->template p<1>();
                }

                TScalar upper() const
                {
                    return this->template p<1>();
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

                TScalar saturate(const TScalar x) const
                {
                    return (x < lower() ? lower() :
                            (x > upper() ? upper() : x));
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>() = b.template i<0>().object.unaryExpr(
                            ::std::bind(
                                    &type::saturate,
                                    this,
                                    ::std::placeholders::_1
                            )
                    );
                }
            };

            template<typename TScalar, int TRows, int TCols>
            class SaturationBlock<
                    Eigen::Matrix<TScalar, TRows, TCols>,
                    SaturationBlockOperator::Scalar,
                    SaturationBlockParameter::AdditionalInput
            > :
                    public Block<
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>, TScalar, TScalar>,
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                            BlockProto::empty
                    > {
            public:
                using type =
                SaturationBlock<
                        Eigen::Matrix<TScalar, TRows, TCols>,
                        SaturationBlockOperator::Scalar,
                        SaturationBlockParameter::AdditionalInput
                >;

                using Base =
                Block<
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>, TScalar, TScalar>,
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                        BlockProto::empty
                >;

                SaturationBlock()
                {
                    bindEquation();
                }

                Signal<TScalar> &lower()
                {
                    return this->template i<1>();
                }

                Signal<TScalar> &lower(const TScalar lo)
                {
                    this->template i<1>() = lo;
                    return this->template i<1>();
                }

                Signal<TScalar> &lower(const Signal<TScalar> lo)
                {
                    this->template i<1>() = lo;
                    return this->template i<1>();
                }

                const Signal<TScalar> &lower() const
                {
                    return this->template i<1>();
                }

                Signal<TScalar> &upper()
                {
                    return this->template i<2>();
                }

                Signal<TScalar> &upper(const TScalar up)
                {
                    this->template i<2>() = up;
                    return this->template i<2>();
                }

                Signal<TScalar> &upper(const Signal<TScalar> up)
                {
                    this->template i<2>() = up;
                    return this->template i<2>();
                }

                const Signal<TScalar> &upper() const
                {
                    return this->template i<2>();
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

                TScalar saturate(const TScalar x) const
                {
                    return (x < lower().object ? lower().object :
                            (x > upper().object ? upper().object : x));
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>() = b.template i<0>().object.unaryExpr(
                            ::std::bind(
                                    &type::saturate,
                                    this,
                                    ::std::placeholders::_1
                            )
                    );
                }
            };

            template<typename TScalar, int TRows, int TCols>
            class SaturationBlock<
                    Eigen::Matrix<TScalar, TRows, TCols>,
                    SaturationBlockOperator::Elementwise,
                    SaturationBlockParameter::Parametric
            > :
                    public Block<
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>>
                    > {
            public:
                using type =
                SaturationBlock<
                        Eigen::Matrix<TScalar, TRows, TCols>,
                        SaturationBlockOperator::Elementwise,
                        SaturationBlockParameter::Parametric
                >;

                using Base =
                Block<
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>>
                >;

                using BoundMatrix = Eigen::Matrix<TScalar, TRows, TCols>;

                SaturationBlock()
                {
                    bindEquation();
                }

                BoundMatrix &lower()
                {
                    return this->template p<0>();
                }

                BoundMatrix &lower(const BoundMatrix &lo)
                {
                    this->template p<0>() = lo;
                    return this->template p<0>();
                }

                BoundMatrix lower() const
                {
                    return this->template p<0>();
                }

                BoundMatrix &upper()
                {
                    return this->template p<1>();
                }

                BoundMatrix &upper(const BoundMatrix &up)
                {
                    this->template p<1>() = up;
                    return this->template p<1>();
                }

                BoundMatrix upper() const
                {
                    return this->template p<1>();
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

                TScalar saturate(const TScalar x, int i = 0, int j = 0) const
                {
                    return (x < lower()(i, j) ? lower()(i, j) :
                            (x > upper()(i, j) ? upper()(i, j) : x));
                }

                int row(int idx) const
                {
                    return floor<int, double>(idx / TCols);
                }

                int col(int idx) const
                {
                    return idx - floor<int, double>(idx / TCols) * TCols;
                }

                void triggerFunction(Base &b)
                {
                    int idx = 0;
                    int i = 0;
                    int j = 0;

                    for (auto x: b.template i<0>().object.reshaped()) {
                        i = row(idx);
                        j = col(idx);

                        b.template o<0>().object(i, j) = saturate(x, i, j);
                        idx++;
                    }

                    b.template o<0>().propagate();
                }
            };

            template<typename TScalar, int TRows, int TCols>
            class SaturationBlock<
                    Eigen::Matrix<TScalar, TRows, TCols>,
                    SaturationBlockOperator::Elementwise,
                    SaturationBlockParameter::AdditionalInput
            > :
                    public Block<
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>>,
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                            BlockProto::empty
                    > {
            public:
                using type =
                SaturationBlock<
                        Eigen::Matrix<TScalar, TRows, TCols>,
                        SaturationBlockOperator::Elementwise,
                        SaturationBlockParameter::AdditionalInput
                >;

                using Base =
                Block<
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>>,
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                        BlockProto::empty
                >;

                using BoundMatrix = Eigen::Matrix<TScalar, TRows, TCols>;

                SaturationBlock()
                {
                    bindEquation();
                }

                Signal<BoundMatrix> &lower()
                {
                    return this->template i<1>();
                }

                Signal<BoundMatrix> &lower(const BoundMatrix &lo)
                {
                    this->template i<1>() = lo;
                    return this->template i<1>();
                }

                Signal<BoundMatrix> &lower(const Signal<BoundMatrix> &lo)
                {
                    this->template i<1>() = lo;
                    return this->template i<1>();
                }

                const Signal<BoundMatrix> &lower() const
                {
                    return this->template i<1>();
                }

                Signal<BoundMatrix> &upper()
                {
                    return this->template i<2>();
                }

                Signal<BoundMatrix> &upper(const BoundMatrix &up)
                {
                    this->template i<2>() = up;
                    return this->template i<2>();
                }

                Signal<BoundMatrix> &upper(const Signal<BoundMatrix> up)
                {
                    this->template i<2>() = up;
                    return this->template i<2>();
                }

                const Signal<BoundMatrix> &upper() const
                {
                    return this->template i<2>();
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

                TScalar saturate(const TScalar x, int i = 0, int j = 0) const
                {
                    return (x < lower().object(i, j) ? lower().object(i, j) :
                            (x > upper().object(i, j) ? upper().object(i, j)
                                                      : x));
                }

                int row(int idx) const
                {
                    return floor<int, double>(idx / TCols);
                }

                int col(int idx) const
                {
                    return idx - floor<int, double>(idx / TCols) * TCols;
                }

                void triggerFunction(Base &b)
                {
                    int idx = 0;
                    int i = 0;
                    int j = 0;

                    for (auto x: b.template i<0>().object.reshaped()) {
                        i = row(idx);
                        j = col(idx);

                        b.template o<0>().object(i, j) = saturate(x, i, j);
                        idx++;
                    }

                    b.template o<0>().propagate();
                }
            };

            template<typename TType, SaturationBlockOperator TOps>
            using SaturationBlockDynamic = SaturationBlock<TType, TOps, SaturationBlockParameter::AdditionalInput>;
        }

        template<typename TType, std::SaturationBlockOperator TOps>
        class BlockTraits<std::SaturationBlock<TType, TOps, std::SaturationBlockParameter::Parametric>> {
        public:
            static constexpr const BlockType blockType = BlockType::SaturationBlock;
            enum {
                directFeedthrough = true
            };

            using type = std::SaturationBlock<TType, TOps, std::SaturationBlockParameter::Parametric>;
            using Base = typename type::Base;

            enum {
                kIns = Base::kIns,
                kOuts = Base::kOuts,
                kPars = Base::kPars
            };

            static const ::std::array<::std::string, kIns> inTypes;
            static const ::std::array<::std::string, kOuts> outTypes;
            static const ::std::array<::std::string, kPars> parTypes;

            static const ::std::array<::std::string, 3> templateTypes;
        };

        template<typename TType, std::SaturationBlockOperator TOps>
        const ::std::array<::std::string, BlockTraits<std::SaturationBlock<TType, TOps, std::SaturationBlockParameter::Parametric>>::kIns>
                BlockTraits<std::SaturationBlock<TType, TOps, std::SaturationBlockParameter::Parametric>>::inTypes =
                {demangle(typeid(TType).name())};

        template<typename TType, std::SaturationBlockOperator TOps>
        const ::std::array<::std::string, BlockTraits<std::SaturationBlock<TType, TOps, std::SaturationBlockParameter::Parametric>>::kOuts>
                BlockTraits<std::SaturationBlock<TType, TOps, std::SaturationBlockParameter::Parametric>>::outTypes =
                {demangle(typeid(TType).name())};

        template<typename TType, std::SaturationBlockOperator TOps>
        const ::std::array<::std::string, BlockTraits<std::SaturationBlock<TType, TOps, std::SaturationBlockParameter::Parametric>>::kPars>
                BlockTraits<std::SaturationBlock<TType, TOps, std::SaturationBlockParameter::Parametric>>::parTypes =
                {demangle(typeid(TType).name()), demangle(typeid(TType).name())};

        template<typename TType, std::SaturationBlockOperator TOps>
        const ::std::array<::std::string, 3>
                BlockTraits<std::SaturationBlock<TType, TOps, std::SaturationBlockParameter::Parametric>>::templateTypes =
                {demangle(typeid(TType).name()), demangle(typeid(std::SaturationBlockOperator).name()), demangle(typeid(std::SaturationBlockParameter).name())};
    }
}


#endif //LODESTAR_SATURATIONBLOCK_HPP
