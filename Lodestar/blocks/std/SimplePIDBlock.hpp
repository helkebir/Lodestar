//
// Created by Hamza El-Kebir on 2/20/22.
//

#ifndef LODESTAR_SIMPLEPIDBLOCK_HPP
#define LODESTAR_SIMPLEPIDBLOCK_HPP


#include "Lodestar/blocks/Block.hpp"
#include "Lodestar/aux/CompileTimeQualifiers.hpp"
#include "Eigen/Dense"

namespace ls {
    namespace blocks {
        namespace std {
            enum class SimplePIDBlockOperator {
                Scalar,
                Elementwise
            };

            enum class SimplePIDBlockParameter {
                Parametric,
                AdditionalInput
            };

            template<typename TType,
                    SimplePIDBlockOperator TOps = SimplePIDBlockOperator::Scalar,
                    SimplePIDBlockParameter TPar = SimplePIDBlockParameter::Parametric>
            class SimplePIDBlock {
                static_assert(!::std::is_same<TType, TType>::value,
                              "SimplePIDBlock not defined for this type.");
            };

            template<typename TType, SimplePIDBlockOperator TOps>
            class SimplePIDBlock<
                    TType,
                    TOps,
                    SimplePIDBlockParameter::Parametric
            > :
                    public Block<
                            ::std::tuple<TType>,
                            ::std::tuple<TType>,
                            ::std::tuple<TType, TType, TType, TType>
                    > {
            public:
                using type =
                SimplePIDBlock<
                        TType,
                        TOps,
                        SimplePIDBlockParameter::Parametric
                >;

                using Base =
                Block<
                        ::std::tuple<TType>,
                        ::std::tuple<TType>,
                        ::std::tuple<TType, TType, TType, TType>
                >;

                SimplePIDBlock()
                {
                    bindEquation();
                }

                TType &pGain()
                {
                    return this->template p<0>();
                }

                TType &pGain(const TType Kp)
                {
                    this->template p<0>() = Kp;
                    return this->template p<0>();
                }

                TType pGain() const
                {
                    return this->template p<0>();
                }

                TType &iGain()
                {
                    return this->template p<1>();
                }

                TType &iGain(const TType Ki)
                {
                    this->template p<1>() = Ki;
                    return this->template p<1>();
                }

                TType iGain() const
                {
                    return this->template p<1>();
                }

                TType &dGain()
                {
                    return this->template p<2>();
                }

                TType &dGain(const TType Kd)
                {
                    this->template p<2>() = Kd;
                    return this->template p<2>();
                }

                TType dGain() const
                {
                    return this->template p<2>();
                }

                TType &samplingPeriod()
                {
                    return this->template p<3>();
                }

                TType &samplingPeriod(const TType t)
                {
                    this->template p<3>() = t;
                    return this->template p<3>();
                }

                TType samplingPeriod() const
                {
                    return this->template p<3>();
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

                TType pid(const TType x) const
                {
                    static TType lastX = 0;
                    static TType intX = 0;

                    TType res = pGain() * x + iGain() * intX + dGain() * (x - lastX)/samplingPeriod();

                    intX += x * samplingPeriod();
                    lastX = x;

                    return res;
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>() = pid(b.template i<0>().object);
                }
            };

            template<typename TType, SimplePIDBlockOperator TOps>
            class SimplePIDBlock<
                    TType,
                    TOps,
                    SimplePIDBlockParameter::AdditionalInput
            > :
                    public Block<
                            ::std::tuple<TType, TType, TType, TType>,
                            ::std::tuple<TType>,
                            ::std::tuple<TType>
                    > {
            public:
                using type =
                SimplePIDBlock<
                        TType,
                        TOps,
                        SimplePIDBlockParameter::AdditionalInput
                >;

                using Base =
                Block<
                        ::std::tuple<TType, TType, TType, TType>,
                        ::std::tuple<TType>,
                        ::std::tuple<TType>
                >;

                SimplePIDBlock()
                {
                    bindEquation();
                }

                Signal<TType> &pGain()
                {
                    return this->template i<1>();
                }

                Signal<TType> &pGain(const TType &Kp)
                {
                    this->template i<1>() = Kp;
                    return this->template i<1>();
                }

                Signal<TType> &pGain(const Signal<TType> &Kp)
                {
                    this->template i<1>() = Kp;
                    return this->template i<1>();
                }

                const Signal<TType> &pGain() const
                {
                    return this->template i<1>();
                }

                Signal<TType> &iGain()
                {
                    return this->template i<2>();
                }

                Signal<TType> &iGain(const TType &Ki)
                {
                    this->template i<2>() = Ki;
                    return this->template i<2>();
                }

                Signal<TType> &iGain(const Signal<TType> Ki)
                {
                    this->template i<2>() = Ki;
                    return this->template i<2>();
                }

                const Signal<TType> &iGain() const
                {
                    return this->template i<2>();
                }

                Signal<TType> &dGain()
                {
                    return this->template i<3>();
                }

                Signal<TType> &dGain(const TType &Kd)
                {
                    this->template i<3>() = Kd;
                    return this->template i<3>();
                }

                Signal<TType> &dGain(const Signal<TType> Kd)
                {
                    this->template i<3>() = Kd;
                    return this->template i<3>();
                }

                const Signal<TType> &dGain() const
                {
                    return this->template i<3>();
                }

                TType &samplingPeriod()
                {
                    return this->template p<0>();
                }

                TType &samplingPeriod(const TType t)
                {
                    this->template p<0>() = t;
                    return this->template p<0>();
                }

                TType samplingPeriod() const
                {
                    return this->template p<0>();
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

                TType pid(const TType x) const
                {
                    static TType lastX = 0;
                    static TType intX = 0;

                    TType res = pGain() * x + iGain() * intX + dGain() * (x - lastX)/samplingPeriod();

                    intX += x * samplingPeriod();
                    lastX = x;

                    return res;
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>() = pid(b.template i<0>().object);
                }
            };

            template<typename TScalar, int TRows, int TCols>
            class SimplePIDBlock<
                    Eigen::Matrix<TScalar, TRows, TCols>,
                    SimplePIDBlockOperator::Scalar,
                    SimplePIDBlockParameter::Parametric
            > :
                    public Block<
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                            ::std::tuple<TScalar, TScalar, TScalar, TScalar>
                    > {
            public:
                using type =
                SimplePIDBlock<
                        Eigen::Matrix<TScalar, TRows, TCols>,
                        SimplePIDBlockOperator::Scalar,
                        SimplePIDBlockParameter::Parametric
                >;

                using Base =
                Block<
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                        ::std::tuple<TScalar, TScalar, TScalar, TScalar>
                >;

                SimplePIDBlock()
                {
                    bindEquation();
                }

                TScalar &pGain()
                {
                    return this->template p<0>();
                }

                TScalar &pGain(const TScalar Kp)
                {
                    this->template p<0>() = Kp;
                    return this->template p<0>();
                }

                TScalar pGain() const
                {
                    return this->template p<0>();
                }

                TScalar &iGain()
                {
                    return this->template p<1>();
                }

                TScalar &iGain(const TScalar Ki)
                {
                    this->template p<1>() = Ki;
                    return this->template p<1>();
                }

                TScalar iGain() const
                {
                    return this->template p<1>();
                }

                TScalar &dGain()
                {
                    return this->template p<2>();
                }

                TScalar &dGain(const TScalar Kd)
                {
                    this->template p<2>() = Kd;
                    return this->template p<2>();
                }

                TScalar dGain() const
                {
                    return this->template p<2>();
                }

                TScalar &samplingPeriod()
                {
                    return this->template p<3>();
                }

                TScalar &samplingPeriod(const TScalar t)
                {
                    this->template p<3>() = t;
                    return this->template p<3>();
                }

                TScalar samplingPeriod() const
                {
                    return this->template p<3>();
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

                Eigen::Matrix<TScalar, TRows, TCols> pid(Eigen::Matrix<TScalar, TRows, TCols> &x) const
                {
                    static Eigen::Matrix<TScalar, TRows, TCols> lastX = Eigen::Matrix<TScalar, TRows, TCols>::Zero();
                    static Eigen::Matrix<TScalar, TRows, TCols> intX = Eigen::Matrix<TScalar, TRows, TCols>::Zero();

                    Eigen::Matrix<TScalar, TRows, TCols> res = pGain() * x + iGain() * intX + dGain() * (x - lastX)/samplingPeriod();

                    intX += samplingPeriod() * x;
                    lastX = x;

                    return res;
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>() = pid(b.template i<0>().object);
                }
            };

            template<typename TScalar, int TRows, int TCols>
            class SimplePIDBlock<
                    Eigen::Matrix<TScalar, TRows, TCols>,
                    SimplePIDBlockOperator::Scalar,
                    SimplePIDBlockParameter::AdditionalInput
            > :
                    public Block<
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>, TScalar, TScalar, TScalar>,
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                            ::std::tuple<TScalar>
                    > {
            public:
                using type =
                SimplePIDBlock<
                        Eigen::Matrix<TScalar, TRows, TCols>,
                        SimplePIDBlockOperator::Scalar,
                        SimplePIDBlockParameter::AdditionalInput
                >;

                using Base =
                Block<
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>, TScalar, TScalar, TScalar>,
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                        ::std::tuple<TScalar>
                >;

                SimplePIDBlock()
                {
                    bindEquation();
                }

                Signal<TScalar> &pGain()
                {
                    return this->template i<1>();
                }

                Signal<TScalar> &pGain(const TScalar &Kp)
                {
                    this->template i<1>() = Kp;
                    return this->template i<1>();
                }

                Signal<TScalar> &pGain(const Signal<TScalar> &Kp)
                {
                    this->template i<1>() = Kp;
                    return this->template i<1>();
                }

                const Signal<TScalar> &pGain() const
                {
                    return this->template i<1>();
                }

                Signal<TScalar> &iGain()
                {
                    return this->template i<2>();
                }

                Signal<TScalar> &iGain(const TScalar &Ki)
                {
                    this->template i<2>() = Ki;
                    return this->template i<2>();
                }

                Signal<TScalar> &iGain(const Signal<TScalar> Ki)
                {
                    this->template i<2>() = Ki;
                    return this->template i<2>();
                }

                const Signal<TScalar> &iGain() const
                {
                    return this->template i<2>();
                }

                Signal<TScalar> &dGain()
                {
                    return this->template i<3>();
                }

                Signal<TScalar> &dGain(const TScalar &Kd)
                {
                    this->template i<3>() = Kd;
                    return this->template i<3>();
                }

                Signal<TScalar> &dGain(const Signal<TScalar> Kd)
                {
                    this->template i<3>() = Kd;
                    return this->template i<3>();
                }

                const Signal<TScalar> &dGain() const
                {
                    return this->template i<3>();
                }

                TScalar &samplingPeriod()
                {
                    return this->template p<0>();
                }

                TScalar &samplingPeriod(const TScalar t)
                {
                    this->template p<0>() = t;
                    return this->template p<0>();
                }

                TScalar samplingPeriod() const
                {
                    return this->template p<0>();
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
                    b.template o<0>() = pid(b.template i<0>().object);
                }

                Eigen::Matrix<TScalar, TRows, TCols> pid(Eigen::Matrix<TScalar, TRows, TCols> &x) const
                {
                    static Eigen::Matrix<TScalar, TRows, TCols> lastX = Eigen::Matrix<TScalar, TRows, TCols>::Zero();
                    static Eigen::Matrix<TScalar, TRows, TCols> intX = Eigen::Matrix<TScalar, TRows, TCols>::Zero();

                    Eigen::Matrix<TScalar, TRows, TCols> res = pGain() * x + iGain() * intX + dGain() * (x - lastX)/samplingPeriod();

                    intX += samplingPeriod() * x;
                    lastX = x;

                    return res;
                }
            };

            template<typename TScalar, int TRows, int TCols>
            class SimplePIDBlock<
                    Eigen::Matrix<TScalar, TRows, TCols>,
                    SimplePIDBlockOperator::Elementwise,
                    SimplePIDBlockParameter::Parametric
            > :
                    public Block<
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>, TScalar>
                    > {
            public:
                using type =
                SimplePIDBlock<
                        Eigen::Matrix<TScalar, TRows, TCols>,
                        SimplePIDBlockOperator::Elementwise,
                        SimplePIDBlockParameter::Parametric
                >;

                using Base =
                Block<
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>, TScalar>
                >;

                using GainMatrix = Eigen::Matrix<TScalar, TRows, TCols>;

                SimplePIDBlock()
                {
                    bindEquation();
                }

                GainMatrix &pGain()
                {
                    return this->template p<0>();
                }

                GainMatrix &pGain(const GainMatrix &Kp)
                {
                    this->template p<0>() = Kp;
                    return this->template p<0>();
                }

                GainMatrix pGain() const
                {
                    return this->template p<0>();
                }

                GainMatrix &iGain()
                {
                    return this->template p<1>();
                }

                GainMatrix &iGain(const GainMatrix &Ki)
                {
                    this->template p<1>() = Ki;
                    return this->template p<1>();
                }

                GainMatrix iGain() const
                {
                    return this->template p<1>();
                }

                GainMatrix &dGain()
                {
                    return this->template p<2>();
                }

                GainMatrix &dGain(const GainMatrix &Kd)
                {
                    this->template p<2>() = Kd;
                    return this->template p<2>();
                }

                GainMatrix dGain() const
                {
                    return this->template p<2>();
                }

                TScalar &samplingPeriod()
                {
                    return this->template p<3>();
                }

                TScalar &samplingPeriod(const TScalar t)
                {
                    this->template p<3>() = t;
                    return this->template p<3>();
                }

                TScalar samplingPeriod() const
                {
                    return this->template p<3>();
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

                Eigen::Matrix<TScalar, TRows, TCols> pid(Eigen::Matrix<TScalar, TRows, TCols> &x) const
                {
                    static Eigen::Matrix<TScalar, TRows, TCols> lastX = Eigen::Matrix<TScalar, TRows, TCols>::Zero();
                    static Eigen::Matrix<TScalar, TRows, TCols> intX = Eigen::Matrix<TScalar, TRows, TCols>::Zero();

                    Eigen::Matrix<TScalar, TRows, TCols> res = pGain().array() * x.array() + iGain().array() * intX.array() + dGain().array() * ((x - lastX)/samplingPeriod()).array();

                    intX += samplingPeriod() * x;
                    lastX = x;

                    return res;
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>() = pid(b.template i<0>().object);
                }
            };

            template<typename TScalar, int TRows, int TCols>
            class SimplePIDBlock<
                    Eigen::Matrix<TScalar, TRows, TCols>,
                    SimplePIDBlockOperator::Elementwise,
                    SimplePIDBlockParameter::AdditionalInput
            > :
                    public Block<
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>>,
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                            ::std::tuple<TScalar>
                    > {
            public:
                using type =
                SimplePIDBlock<
                        Eigen::Matrix<TScalar, TRows, TCols>,
                        SimplePIDBlockOperator::Elementwise,
                        SimplePIDBlockParameter::AdditionalInput
                >;

                using Base =
                Block<
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>>,
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>>,
                        ::std::tuple<TScalar>
                >;

                using GainMatrix = Eigen::Matrix<TScalar, TRows, TCols>;

                SimplePIDBlock()
                {
                    bindEquation();
                }

                Signal<GainMatrix> &pGain()
                {
                    return this->template i<1>();
                }

                Signal<GainMatrix> &pGain(const GainMatrix &Kp)
                {
                    this->template i<1>() = Kp;
                    return this->template i<1>();
                }

                Signal<GainMatrix> &pGain(const Signal<GainMatrix> &Kp)
                {
                    this->template i<1>() = Kp;
                    return this->template i<1>();
                }

                const Signal<GainMatrix> &pGain() const
                {
                    return this->template i<1>();
                }

                Signal<GainMatrix> &iGain()
                {
                    return this->template i<2>();
                }

                Signal<GainMatrix> &iGain(const GainMatrix &Ki)
                {
                    this->template i<2>() = Ki;
                    return this->template i<2>();
                }

                Signal<GainMatrix> &iGain(const Signal<GainMatrix> &Ki)
                {
                    this->template i<2>() = Ki;
                    return this->template i<2>();
                }

                const Signal<GainMatrix> &iGain() const
                {
                    return this->template i<2>();
                }

                Signal<GainMatrix> &dGain()
                {
                    return this->template i<3>();
                }

                Signal<GainMatrix> &dGain(const GainMatrix &Kd)
                {
                    this->template i<3>() = Kd;
                    return this->template i<3>();
                }

                Signal<GainMatrix> &dGain(const Signal<GainMatrix> &Kd)
                {
                    this->template i<3>() = Kd;
                    return this->template i<3>();
                }

                const Signal<GainMatrix> &dGain() const
                {
                    return this->template i<3>();
                }

                TScalar &samplingPeriod()
                {
                    return this->template p<0>();
                }

                TScalar &samplingPeriod(const TScalar t)
                {
                    this->template p<0>() = t;
                    return this->template p<0>();
                }

                TScalar samplingPeriod() const
                {
                    return this->template p<0>();
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

                Eigen::Matrix<TScalar, TRows, TCols> pid(Eigen::Matrix<TScalar, TRows, TCols> &x) const
                {
                    static Eigen::Matrix<TScalar, TRows, TCols> lastX{};
                    static Eigen::Matrix<TScalar, TRows, TCols> intX{};

                    Eigen::Matrix<TScalar, TRows, TCols> res = pGain().object.array() * x.array() + iGain().object.array() * intX.array() + dGain().object.array() * ((x - lastX)/samplingPeriod()).array();

                    intX += samplingPeriod() * x;
                    lastX = x;

                    return res;
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>() = pid(b.template i<0>().object);
                }
            };

            template<typename TType, SimplePIDBlockOperator TOps>
            using SimplePIDBlockDynamic = SimplePIDBlock<TType, TOps, SimplePIDBlockParameter::AdditionalInput>;
        }

        // FIXME: Add additional specializations.
        template<typename TType>
        class BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Scalar, std::SimplePIDBlockParameter::Parametric>> {
        public:
            static constexpr const BlockType blockType = BlockType::SimplePIDBlock;
            enum {
                directFeedthrough = true
            };

            using type = std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Scalar, std::SimplePIDBlockParameter::Parametric>;
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

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Scalar, std::SimplePIDBlockParameter::Parametric>>::kIns>
                BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Scalar, std::SimplePIDBlockParameter::Parametric>>::inTypes =
                {demangle(typeid(TType).name())};

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Scalar, std::SimplePIDBlockParameter::Parametric>>::kOuts>
                BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Scalar, std::SimplePIDBlockParameter::Parametric>>::outTypes =
                {demangle(typeid(TType).name())};

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Scalar, std::SimplePIDBlockParameter::Parametric>>::kPars>
                BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Scalar, std::SimplePIDBlockParameter::Parametric>>::parTypes =
                {demangle(typeid(TType).name()), demangle(typeid(TType).name()), demangle(typeid(TType).name()), demangle(typeid(TType).name())};

        template<typename TType>
        const ::std::array<::std::string, 3>
                BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Scalar, std::SimplePIDBlockParameter::Parametric>>::templateTypes =
                {demangle(typeid(TType).name()), demangle(typeid(std::SimplePIDBlockOperator).name()), demangle(typeid(std::SimplePIDBlockParameter).name())};

        template<typename TType>
        class BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Elementwise, std::SimplePIDBlockParameter::Parametric>> {
        public:
            static constexpr const BlockType blockType = BlockType::SimplePIDBlock;
            enum {
                directFeedthrough = true
            };

            using type = std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Elementwise, std::SimplePIDBlockParameter::Parametric>;
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

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Elementwise, std::SimplePIDBlockParameter::Parametric>>::kIns>
                BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Elementwise, std::SimplePIDBlockParameter::Parametric>>::inTypes =
                {demangle(typeid(TType).name())};

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Elementwise, std::SimplePIDBlockParameter::Parametric>>::kOuts>
                BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Elementwise, std::SimplePIDBlockParameter::Parametric>>::outTypes =
                {demangle(typeid(TType).name())};

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Elementwise, std::SimplePIDBlockParameter::Parametric>>::kPars>
                BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Elementwise, std::SimplePIDBlockParameter::Parametric>>::parTypes =
                {demangle(typeid(TType).name()), demangle(typeid(TType).name()), demangle(typeid(TType).name()), demangle(typeid(TType).name())};

        template<typename TType>
        const ::std::array<::std::string, 3>
                BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Elementwise, std::SimplePIDBlockParameter::Parametric>>::templateTypes =
                {demangle(typeid(TType).name()), demangle(typeid(std::SimplePIDBlockOperator).name()), demangle(typeid(std::SimplePIDBlockParameter).name())};

        template<typename TType>
        class BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Scalar, std::SimplePIDBlockParameter::AdditionalInput>> {
        public:
            static constexpr const BlockType blockType = BlockType::SimplePIDBlock;
            enum {
                directFeedthrough = true
            };

            using type = std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Scalar, std::SimplePIDBlockParameter::AdditionalInput>;
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

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Scalar, std::SimplePIDBlockParameter::AdditionalInput>>::kIns>
                BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Scalar, std::SimplePIDBlockParameter::AdditionalInput>>::inTypes =
                {demangle(typeid(TType).name()), demangle(typeid(TType).name()), demangle(typeid(TType).name()), demangle(typeid(TType).name())};

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Scalar, std::SimplePIDBlockParameter::AdditionalInput>>::kOuts>
                BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Scalar, std::SimplePIDBlockParameter::AdditionalInput>>::outTypes =
                {demangle(typeid(TType).name())};

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Scalar, std::SimplePIDBlockParameter::AdditionalInput>>::kPars>
                BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Scalar, std::SimplePIDBlockParameter::AdditionalInput>>::parTypes =
                {demangle(typeid(TType).name())};

        template<typename TType>
        const ::std::array<::std::string, 3>
                BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Scalar, std::SimplePIDBlockParameter::AdditionalInput>>::templateTypes =
                {demangle(typeid(TType).name()), demangle(typeid(std::SimplePIDBlockOperator).name()), demangle(typeid(std::SimplePIDBlockParameter).name())};

        template<typename TType>
        class BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Elementwise, std::SimplePIDBlockParameter::AdditionalInput>> {
        public:
            static constexpr const BlockType blockType = BlockType::SimplePIDBlock;
            enum {
                directFeedthrough = true
            };

            using type = std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Elementwise, std::SimplePIDBlockParameter::AdditionalInput>;
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

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Elementwise, std::SimplePIDBlockParameter::AdditionalInput>>::kIns>
                BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Elementwise, std::SimplePIDBlockParameter::AdditionalInput>>::inTypes =
                {demangle(typeid(TType).name()), demangle(typeid(TType).name()), demangle(typeid(TType).name()), demangle(typeid(TType).name())};

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Elementwise, std::SimplePIDBlockParameter::AdditionalInput>>::kOuts>
                BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Elementwise, std::SimplePIDBlockParameter::AdditionalInput>>::outTypes =
                {demangle(typeid(TType).name())};

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Elementwise, std::SimplePIDBlockParameter::AdditionalInput>>::kPars>
                BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Elementwise, std::SimplePIDBlockParameter::AdditionalInput>>::parTypes =
                {demangle(typeid(TType).name())};

        template<typename TType>
        const ::std::array<::std::string, 3>
                BlockTraits<std::SimplePIDBlock<TType, std::SimplePIDBlockOperator::Elementwise, std::SimplePIDBlockParameter::AdditionalInput>>::templateTypes =
                {demangle(typeid(TType).name()), demangle(typeid(std::SimplePIDBlockOperator).name()), demangle(typeid(std::SimplePIDBlockParameter).name())};
    }
}

#endif //LODESTAR_SIMPLEPIDBLOCK_HPP
