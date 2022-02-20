//
// Created by Hamza El-Kebir on 2/19/22.
//

#ifndef LODESTAR_DEADZONEBLOCK_HPP
#define LODESTAR_DEADZONEBLOCK_HPP


#include "Lodestar/blocks/Block.hpp"
#include "Lodestar/aux/CompileTimeQualifiers.hpp"
#include "Eigen/Dense"

namespace ls {
    namespace blocks {
        namespace std {
            enum class DeadzoneBlockOperator {
                Scalar,
                Elementwise
            };

            enum class DeadzoneBlockParameter {
                Parametric,
                AdditionalInput
            };

            template<typename TType,
                    DeadzoneBlockOperator TOps = DeadzoneBlockOperator::Scalar,
                    DeadzoneBlockParameter TPar = DeadzoneBlockParameter::Parametric>
            class DeadzoneBlock {
                static_assert(!::std::is_same<TType, TType>::value,
                              "DeadzoneBlock not defined for this type.");
            };

            template<typename TType, DeadzoneBlockOperator TOps>
            class DeadzoneBlock<
                    TType,
                    TOps,
                    DeadzoneBlockParameter::Parametric
            > :
                    public Block<
                            ::std::tuple<TType>,
                            ::std::tuple<TType>,
                            ::std::tuple<TType, TType>
                    > {
            public:
                using type =
                DeadzoneBlock<
                        TType,
                        TOps,
                        DeadzoneBlockParameter::Parametric
                >;

                using Base =
                Block<
                        ::std::tuple<TType>,
                        ::std::tuple<TType>,
                        ::std::tuple<TType, TType>
                >;

                DeadzoneBlock()
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

                TType deadzone(const TType x) const
                {
                    return (x < lower() || x > upper()) ? x : 0;
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>() = deadzone(b.template i<0>().object);
                }
            };

            template<typename TType, DeadzoneBlockOperator TOps>
            class DeadzoneBlock<
                    TType,
                    TOps,
                    DeadzoneBlockParameter::AdditionalInput
            > :
                    public Block<
                            ::std::tuple<TType, TType, TType>,
                            ::std::tuple<TType>,
                            ::std::tuple<TType>
                    > {
            public:
                using type =
                DeadzoneBlock<
                        TType,
                        TOps,
                        DeadzoneBlockParameter::AdditionalInput
                >;

                using Base =
                Block<
                        ::std::tuple<TType, TType, TType>,
                        ::std::tuple<TType>,
                        ::std::tuple<TType>
                >;

                DeadzoneBlock()
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

                TType deadzone(const TType x) const
                {
                    return (x < lower().object || x > upper().object) ? x : 0;
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>() = deadzone(b.template i<0>().object);
                }
            };

            template<typename TScalar, int TRows, int TCols>
            class DeadzoneBlock<
                    Eigen::Matrix<TScalar, TRows, TCols>,
                    DeadzoneBlockOperator::Scalar,
                    DeadzoneBlockParameter::Parametric
            > :
                    public Block<
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                            ::std::tuple<TScalar, TScalar>
                    > {
            public:
                using type =
                DeadzoneBlock<
                        Eigen::Matrix<TScalar, TRows, TCols>,
                        DeadzoneBlockOperator::Scalar,
                        DeadzoneBlockParameter::Parametric
                >;

                using Base =
                Block<
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                        ::std::tuple<TScalar, TScalar>
                >;

                DeadzoneBlock()
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

                TScalar deadzone(const TScalar x) const
                {
                    return ((x < lower() || x > upper()) ? x : 0);
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>() = b.template i<0>().object.unaryExpr(
                            ::std::bind(
                                    &type::deadzone,
                                    this,
                                    ::std::placeholders::_1
                            )
                    );
                }
            };

            template<typename TScalar, int TRows, int TCols>
            class DeadzoneBlock<
                    Eigen::Matrix<TScalar, TRows, TCols>,
                    DeadzoneBlockOperator::Scalar,
                    DeadzoneBlockParameter::AdditionalInput
            > :
                    public Block<
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>, TScalar, TScalar>,
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                            BlockProto::empty
                    > {
            public:
                using type =
                DeadzoneBlock<
                        Eigen::Matrix<TScalar, TRows, TCols>,
                        DeadzoneBlockOperator::Scalar,
                        DeadzoneBlockParameter::AdditionalInput
                >;

                using Base =
                Block<
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>, TScalar, TScalar>,
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                        BlockProto::empty
                >;

                DeadzoneBlock()
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

                TScalar deadzone(const TScalar x) const
                {
                    return ((x < lower().object || x > upper().object) ? x : 0);
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>() = b.template i<0>().object.unaryExpr(
                            ::std::bind(
                                    &type::deadzone,
                                    this,
                                    ::std::placeholders::_1
                            )
                    );
                }
            };

            template<typename TScalar, int TRows, int TCols>
            class DeadzoneBlock<
                    Eigen::Matrix<TScalar, TRows, TCols>,
                    DeadzoneBlockOperator::Elementwise,
                    DeadzoneBlockParameter::Parametric
            > :
                    public Block<
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>>
                    > {
            public:
                using type =
                DeadzoneBlock<
                        Eigen::Matrix<TScalar, TRows, TCols>,
                        DeadzoneBlockOperator::Elementwise,
                        DeadzoneBlockParameter::Parametric
                >;

                using Base =
                Block<
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>>
                >;

                using BoundMatrix = Eigen::Matrix<TScalar, TRows, TCols>;

                DeadzoneBlock()
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

                TScalar deadzone(const TScalar x, int i = 0, int j = 0) const
                {
                    return (x < lower()(i, j) || x > upper()(i, j)) ? x : 0;
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

                        b.template o<0>().object(i, j) = deadzone(x, i, j);
                        idx++;
                    }

                    b.template o<0>().propagate();
                }
            };

            template<typename TScalar, int TRows, int TCols>
            class DeadzoneBlock<
                    Eigen::Matrix<TScalar, TRows, TCols>,
                    DeadzoneBlockOperator::Elementwise,
                    DeadzoneBlockParameter::AdditionalInput
            > :
                    public Block<
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>>,
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                            BlockProto::empty
                    > {
            public:
                using type =
                DeadzoneBlock<
                        Eigen::Matrix<TScalar, TRows, TCols>,
                        DeadzoneBlockOperator::Elementwise,
                        DeadzoneBlockParameter::AdditionalInput
                >;

                using Base =
                Block<
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>>,
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                        BlockProto::empty
                >;

                using BoundMatrix = Eigen::Matrix<TScalar, TRows, TCols>;

                DeadzoneBlock()
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

                TScalar deadzone(const TScalar x, int i = 0, int j = 0) const
                {
                    return (x < lower().object(i, j) || x > upper().object(i, j)) ? x : 0;
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

                        b.template o<0>().object(i, j) = deadzone(x, i, j);
                        idx++;
                    }

                    b.template o<0>().propagate();
                }
            };

            template<typename TType, DeadzoneBlockOperator TOps>
            using DeadzoneBlockDynamic = DeadzoneBlock<TType, TOps, DeadzoneBlockParameter::AdditionalInput>;
        }

        template<typename TType, std::DeadzoneBlockOperator TOps>
        class BlockTraits<std::DeadzoneBlock<TType, TOps, std::DeadzoneBlockParameter::Parametric>> {
        public:
            static constexpr const BlockType blockType = BlockType::DeadzoneBlock;
            enum {
                directFeedthrough = true
            };

            using type = std::DeadzoneBlock<TType, TOps, std::DeadzoneBlockParameter::Parametric>;
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

        template<typename TType, std::DeadzoneBlockOperator TOps>
        const ::std::array<::std::string, BlockTraits<std::DeadzoneBlock<TType, TOps, std::DeadzoneBlockParameter::Parametric>>::kIns>
                BlockTraits<std::DeadzoneBlock<TType, TOps, std::DeadzoneBlockParameter::Parametric>>::inTypes =
                {demangle(typeid(TType).name())};

        template<typename TType, std::DeadzoneBlockOperator TOps>
        const ::std::array<::std::string, BlockTraits<std::DeadzoneBlock<TType, TOps, std::DeadzoneBlockParameter::Parametric>>::kOuts>
                BlockTraits<std::DeadzoneBlock<TType, TOps, std::DeadzoneBlockParameter::Parametric>>::outTypes =
                {demangle(typeid(TType).name())};

        template<typename TType, std::DeadzoneBlockOperator TOps>
        const ::std::array<::std::string, BlockTraits<std::DeadzoneBlock<TType, TOps, std::DeadzoneBlockParameter::Parametric>>::kPars>
                BlockTraits<std::DeadzoneBlock<TType, TOps, std::DeadzoneBlockParameter::Parametric>>::parTypes =
                {demangle(typeid(TType).name()), demangle(typeid(TType).name())};

        template<typename TType, std::DeadzoneBlockOperator TOps>
        const ::std::array<::std::string, 3>
                BlockTraits<std::DeadzoneBlock<TType, TOps, std::DeadzoneBlockParameter::Parametric>>::templateTypes =
                {demangle(typeid(TType).name()), demangle(typeid(std::DeadzoneBlockOperator).name()), demangle(typeid(std::DeadzoneBlockParameter).name())};
    }
}


#endif //LODESTAR_DEADZONEBLOCK_HPP
