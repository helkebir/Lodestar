//
// Created by Hamza El-Kebir on 12/30/2021.
//

#ifndef LODESTAR_DISCRETESTATESPACEBLOCK_HPP
#define LODESTAR_DISCRETESTATESPACEBLOCK_HPP


#include "Lodestar/blocks/Block.hpp"
#include "Lodestar/systems/DiscreteStateSpace.hpp"
#include "Eigen/Dense"

namespace ls {
    namespace blocks {
        namespace std {
            enum class DiscreteStateSpaceBlockFeedthrough {
                HasFeedthrough,
                NoFeedthrough
            };

            template<typename TScalar, DiscreteStateSpaceBlockFeedthrough TFeedthroughOps = DiscreteStateSpaceBlockFeedthrough::NoFeedthrough, int NState = 0, int NInput = 0, int NOutput = 0>
            class DiscreteStateSpaceBlock : public Block<BlockProto::empty, BlockProto::empty, BlockProto::empty> {
                static_assert(!::std::is_same<TScalar, TScalar>::value,
                              "DiscreteStateSpaceBlock not defined for this type.");
            };

            // TODO: Add support for dynamic matrices.

            template<typename TScalar, int NState, int NInput, int NOutput>
            class DiscreteStateSpaceBlock<
                    TScalar,
                    DiscreteStateSpaceBlockFeedthrough::NoFeedthrough,
                    NState,
                    NInput,
                    NOutput
            > :
                    public Block<
                            ::std::tuple<Eigen::Vector<TScalar, NInput>>,
                            ::std::tuple<Eigen::Vector<TScalar, NOutput>>,
                            ::std::tuple<ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>>
                    > {
            public:
                static_assert(::std::is_arithmetic<TScalar>::value, "Scalar type must be arithmetic.");

                using type =
                DiscreteStateSpaceBlock<
                        TScalar,
                        DiscreteStateSpaceBlockFeedthrough::NoFeedthrough,
                        NState,
                        NInput,
                        NOutput
                >;

                using Base =
                Block<
                        ::std::tuple<Eigen::Vector<TScalar, NInput>>,
                        ::std::tuple<Eigen::Vector<TScalar, NOutput>>,
                        ::std::tuple<ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>>
                >;

                using DiscreteStateSpace = ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>;
                using StateVector = Eigen::Vector<TScalar, NState>;
                using InputVector = Eigen::Vector<TScalar, NInput>;
                using OutputVector = Eigen::Vector<TScalar, NOutput>;

                static constexpr const int kNState = NState;
                static constexpr const int kNInput = NInput;
                static constexpr const int kNOutput = NOutput;


                DiscreteStateSpaceBlock()
                {
                    bindFunction();
                }

                DiscreteStateSpaceBlock(const DiscreteStateSpace &dss)
                {
                    this->template p<0>() = dss;
                    bindFunction();
                }

                void setState(const StateVector &x)
                {
                    x_ = x;
                }

                const DiscreteStateSpace &getSystem() const
                {
                    return this->template p<0>();
                }

            protected:
                void bindFunction()
                {
                    this->equation = [&](Base &b)
                    {
                        this->triggerFunction(b);
                    };
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>() = b.template p<0>().getC() * this->x_;
                    this->setState(b.template p<0>().getA() * this->x_ + b.template p<0>().getB() * b.template i<0>().object);
                }

                StateVector x_;
            };

            template<typename TScalar, int NState, int NInput, int NOutput>
            class DiscreteStateSpaceBlock<
                    ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>,
                    DiscreteStateSpaceBlockFeedthrough::NoFeedthrough,
                    0,
                    0,
                    0
            > :
                    public Block<
                            ::std::tuple<Eigen::Vector<TScalar, NInput>>,
                            ::std::tuple<Eigen::Vector<TScalar, NOutput>>,
                            ::std::tuple<ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>>
                    > {
            public:
                static_assert(::std::is_arithmetic<TScalar>::value, "Scalar type must be arithmetic.");

                using type =
                DiscreteStateSpaceBlock<
                        TScalar,
                        DiscreteStateSpaceBlockFeedthrough::NoFeedthrough,
                        NState,
                        NInput,
                        NOutput
                >;

                using Base =
                Block<
                        ::std::tuple<Eigen::Vector<TScalar, NInput>>,
                        ::std::tuple<Eigen::Vector<TScalar, NOutput>>,
                        ::std::tuple<ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>>
                >;

                using DiscreteStateSpace = ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>;
                using StateVector = Eigen::Vector<TScalar, NState>;
                using InputVector = Eigen::Vector<TScalar, NInput>;
                using OutputVector = Eigen::Vector<TScalar, NOutput>;

                static constexpr const int kNState = NState;
                static constexpr const int kNInput = NInput;
                static constexpr const int kNOutput = NOutput;


                DiscreteStateSpaceBlock()
                {
                    bindFunction();
                }

                DiscreteStateSpaceBlock(const DiscreteStateSpace &dss)
                {
                    this->template p<0>() = dss;
                    bindFunction();
                }

                void setState(const StateVector &x)
                {
                    x_ = x;
                }

                const DiscreteStateSpace &getSystem() const
                {
                    return this->template p<0>();
                }

            protected:
                void bindFunction()
                {
                    this->equation = [&](Base &b)
                    {
                        this->triggerFunction(b);
                    };
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>() = b.template p<0>().getC() * this->x_;
                    this->setState(b.template p<0>().getA() * this->x_ + b.template p<0>().getB() * b.template i<0>().object);
                }

                StateVector x_;
            };

            template<typename TScalar, int NState, int NInput, int NOutput>
            class DiscreteStateSpaceBlock<
                    TScalar,
                    DiscreteStateSpaceBlockFeedthrough::HasFeedthrough,
                    NState,
                    NInput,
                    NOutput
            > :
                    public Block<
                            ::std::tuple<Eigen::Vector<TScalar, NInput>>,
                            ::std::tuple<Eigen::Vector<TScalar, NOutput>>,
                            ::std::tuple<ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>>
                    > {
            public:
                static_assert(::std::is_arithmetic<TScalar>::value, "Scalar type must be arithmetic.");

                using type =
                DiscreteStateSpaceBlock<
                        TScalar,
                        DiscreteStateSpaceBlockFeedthrough::HasFeedthrough,
                        NState,
                        NInput,
                        NOutput
                >;

                using Base =
                Block<
                        ::std::tuple<Eigen::Vector<TScalar, NInput>>,
                        ::std::tuple<Eigen::Vector<TScalar, NOutput>>,
                        ::std::tuple<ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>>
                >;

                using DiscreteStateSpace = ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>;
                using StateVector = Eigen::Vector<TScalar, NState>;
                using InputVector = Eigen::Vector<TScalar, NInput>;
                using OutputVector = Eigen::Vector<TScalar, NOutput>;

                static constexpr const int kNState = NState;
                static constexpr const int kNInput = NInput;
                static constexpr const int kNOutput = NOutput;


                DiscreteStateSpaceBlock()
                {
                    bindFunction();
                }

                DiscreteStateSpaceBlock(const DiscreteStateSpace &dss)
                {
                    this->template p<0>() = dss;
                    bindFunction();
                }

                void setState(const StateVector &x)
                {
                    x_ = x;
                }

                const DiscreteStateSpace &getSystem() const
                {
                    return this->template p<0>();
                }

            protected:
                void bindFunction()
                {
                    this->equation = [&](Base &b)
                    {
                        this->triggerFunction(b);
                    };
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>() = b.template p<0>().getC() * x_ + b.template p<0>().getD() * b.template i<0>().object;
                    this->setState(b.template p<0>().getA() * x_ + b.template p<0>().getB() * b.template i<0>().object);
                }

                StateVector x_;
            };

            template<typename TScalar, int NState, int NInput, int NOutput>
            class DiscreteStateSpaceBlock<
                    ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>,
                    DiscreteStateSpaceBlockFeedthrough::HasFeedthrough,
                    0,
                    0,
                    0
            > :
                    public Block<
                            ::std::tuple<Eigen::Vector<TScalar, NInput>>,
                            ::std::tuple<Eigen::Vector<TScalar, NOutput>>,
                            ::std::tuple<ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>>
                    > {
            public:
                static_assert(::std::is_arithmetic<TScalar>::value, "Scalar type must be arithmetic.");

                using type =
                DiscreteStateSpaceBlock<
                        TScalar,
                        DiscreteStateSpaceBlockFeedthrough::NoFeedthrough,
                        NState,
                        NInput,
                        NOutput
                >;

                using Base =
                Block<
                        ::std::tuple<Eigen::Vector<TScalar, NInput>>,
                        ::std::tuple<Eigen::Vector<TScalar, NOutput>>,
                        ::std::tuple<ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>>
                >;

                using DiscreteStateSpace = ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>;
                using StateVector = Eigen::Vector<TScalar, NState>;
                using InputVector = Eigen::Vector<TScalar, NInput>;
                using OutputVector = Eigen::Vector<TScalar, NOutput>;

                static constexpr const int kNState = NState;
                static constexpr const int kNInput = NInput;
                static constexpr const int kNOutput = NOutput;


                DiscreteStateSpaceBlock()
                {
                    bindFunction();
                }

                DiscreteStateSpaceBlock(const DiscreteStateSpace &dss)
                {
                    this->template p<0>() = dss;
                    bindFunction();
                }

                void setState(const StateVector &x)
                {
                    x_ = x;
                }

                const DiscreteStateSpace &getSystem() const
                {
                    return this->template p<0>();
                }

            protected:
                void bindFunction()
                {
                    this->equation = [&](Base &b)
                    {
                        this->triggerFunction(b);
                    };
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>() = b.template p<0>().getC() * x_ + b.template p<0>().getD() * b.template i<0>().object;
                    this->setState(b.template p<0>().getA() * x_ + b.template p<0>().getB() * b.template i<0>().object);
                }

                StateVector x_;
            };
        }

        // TODO: Check if partial specialization are needed for both feedthrough cases.
        template<typename TScalar, int NState, int NInput, int NOutput, std::DiscreteStateSpaceBlockFeedthrough TFeedthroughOps>
        class BlockTraits<std::DiscreteStateSpaceBlock<TScalar, TFeedthroughOps, NState, NInput, NOutput>> {
        public:
            static constexpr const BlockType blockType = BlockType::DiscreteStateSpaceBlock;
            enum {
                directFeedthrough = (TFeedthroughOps == std::DiscreteStateSpaceBlockFeedthrough::HasFeedthrough)
            };

            using type = std::DiscreteStateSpaceBlock<TScalar, TFeedthroughOps, NState, NInput, NOutput>;
            using Base = typename type::Base;

            enum {
                kIns = Base::kIns,
                kOuts = Base::kOuts,
                kPars = Base::kPars
            };

            enum {
                kNState = type::kNState,
                kNInput = type::kNInput,
                kNOutput = type::kNOutput
            };

            static const ::std::array<::std::string, kIns> inTypes;
            static const ::std::array<::std::string, kOuts> outTypes;
            static const ::std::array<::std::string, kPars> parTypes;

            static const ::std::array<::std::string, 5> templateTypes;
        };

        template<typename TScalar, int NState, int NInput, int NOutput, std::DiscreteStateSpaceBlockFeedthrough TFeedthroughOps>
        const ::std::array<::std::string, BlockTraits<std::DiscreteStateSpaceBlock<TScalar, TFeedthroughOps, NState, NInput, NOutput>>::kIns> BlockTraits<std::DiscreteStateSpaceBlock<TScalar, TFeedthroughOps, NState, NInput, NOutput>>::inTypes =
                { demangle(typeid(Eigen::Vector<TScalar, NInput>).name()) };

        template<typename TScalar, int NState, int NInput, int NOutput, std::DiscreteStateSpaceBlockFeedthrough TFeedthroughOps>
        const ::std::array<::std::string, BlockTraits<std::DiscreteStateSpaceBlock<TScalar, TFeedthroughOps, NState, NInput, NOutput>>::kOuts> BlockTraits<std::DiscreteStateSpaceBlock<TScalar, TFeedthroughOps, NState, NInput, NOutput>>::outTypes =
                { demangle(typeid(Eigen::Vector<TScalar, NOutput>).name()) };

        template<typename TScalar, int NState, int NInput, int NOutput, std::DiscreteStateSpaceBlockFeedthrough TFeedthroughOps>
        const ::std::array<::std::string, BlockTraits<std::DiscreteStateSpaceBlock<TScalar, TFeedthroughOps, NState, NInput, NOutput>>::kPars> BlockTraits<std::DiscreteStateSpaceBlock<TScalar, TFeedthroughOps, NState, NInput, NOutput>>::parTypes =
                { demangle(typeid(ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>).name()) };

        template<typename TScalar, int NState, int NInput, int NOutput, std::DiscreteStateSpaceBlockFeedthrough TFeedthroughOps>
        const ::std::array<::std::string, 5> BlockTraits<std::DiscreteStateSpaceBlock<TScalar, TFeedthroughOps, NState, NInput, NOutput>>::templateTypes =
                { demangle(typeid(TScalar).name()), demangle(typeid(NState).name()), demangle(typeid(NInput).name()), demangle(typeid(NOutput).name()), demangle(typeid(TFeedthroughOps).name()) };

        template<typename TScalar, int NState, int NInput, int NOutput>
        class BlockTraits<std::DiscreteStateSpaceBlock<
                          ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>,
                std::DiscreteStateSpaceBlockFeedthrough::NoFeedthrough,
                0,
                0,
                0
        >> {
        public:
            static constexpr const BlockType blockType = BlockType::DiscreteStateSpaceBlock;
            enum {
                directFeedthrough = false
            };

            using type = std::DiscreteStateSpaceBlock<
                    ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>,
                    std::DiscreteStateSpaceBlockFeedthrough::NoFeedthrough,
                    0,
                    0,
                    0
            >;
            using Base = typename type::Base;

            enum {
                kIns = Base::kIns,
                kOuts = Base::kOuts,
                kPars = Base::kPars
            };

            enum {
                kNState = type::kNState,
                kNInput = type::kNInput,
                kNOutput = type::kNOutput
            };

            static const ::std::array<::std::string, kIns> inTypes;
            static const ::std::array<::std::string, kOuts> outTypes;
            static const ::std::array<::std::string, kPars> parTypes;

            static const ::std::array<::std::string, 2> templateTypes;
        };

        template<typename TScalar, int NState, int NInput, int NOutput>
        const ::std::array<::std::string, BlockTraits<std::DiscreteStateSpaceBlock<
                ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>,
                std::DiscreteStateSpaceBlockFeedthrough::NoFeedthrough,
                0,
                0,
                0
        >>::kIns> BlockTraits<std::DiscreteStateSpaceBlock<
                ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>,
                std::DiscreteStateSpaceBlockFeedthrough::NoFeedthrough,
                0,
                0,
                0
        >>::inTypes =
                { demangle(typeid(Eigen::Vector<TScalar, NInput>).name()) };

        template<typename TScalar, int NState, int NInput, int NOutput>
        const ::std::array<::std::string, BlockTraits<std::DiscreteStateSpaceBlock<
                ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>,
                std::DiscreteStateSpaceBlockFeedthrough::NoFeedthrough,
                0,
                0,
                0
        >>::kOuts> BlockTraits<std::DiscreteStateSpaceBlock<
                ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>,
                std::DiscreteStateSpaceBlockFeedthrough::NoFeedthrough,
                0,
                0,
                0
        >>::outTypes =
                { demangle(typeid(Eigen::Vector<TScalar, NOutput>).name()) };

        template<typename TScalar, int NState, int NInput, int NOutput>
        const ::std::array<::std::string, BlockTraits<std::DiscreteStateSpaceBlock<
                ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>,
                std::DiscreteStateSpaceBlockFeedthrough::NoFeedthrough,
                0,
                0,
                0
        >>::kPars> BlockTraits<std::DiscreteStateSpaceBlock<
                ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>,
                std::DiscreteStateSpaceBlockFeedthrough::NoFeedthrough,
                0,
                0,
                0
        >>::parTypes =
                { demangle(typeid(ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>).name()) };

        template<typename TScalar, int NState, int NInput, int NOutput>
        const ::std::array<::std::string, 2> BlockTraits<std::DiscreteStateSpaceBlock<
                ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>,
                std::DiscreteStateSpaceBlockFeedthrough::NoFeedthrough,
                0,
                0,
                0
        >>::templateTypes =
                { demangle(typeid(ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>).name()), demangle(typeid(std::DiscreteStateSpaceBlockFeedthrough::NoFeedthrough).name()) };

        // Has feedthrough

        template<typename TScalar, int NState, int NInput, int NOutput>
        class BlockTraits<std::DiscreteStateSpaceBlock<
                ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>,
                std::DiscreteStateSpaceBlockFeedthrough::HasFeedthrough,
                0,
                0,
                0
        >> {
        public:
            static constexpr const BlockType blockType = BlockType::DiscreteStateSpaceBlock;
            enum {
                directFeedthrough = true
            };

            using type = std::DiscreteStateSpaceBlock<
                    ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>,
                    std::DiscreteStateSpaceBlockFeedthrough::HasFeedthrough,
                    0,
                    0,
                    0
            >;
            using Base = typename type::Base;

            enum {
                kIns = Base::kIns,
                kOuts = Base::kOuts,
                kPars = Base::kPars
            };

            enum {
                kNState = type::kNState,
                kNInput = type::kNInput,
                kNOutput = type::kNOutput
            };

            static const ::std::array<::std::string, kIns> inTypes;
            static const ::std::array<::std::string, kOuts> outTypes;
            static const ::std::array<::std::string, kPars> parTypes;

            static const ::std::array<::std::string, 2> templateTypes;
        };

        template<typename TScalar, int NState, int NInput, int NOutput>
        const ::std::array<::std::string, BlockTraits<std::DiscreteStateSpaceBlock<
                ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>,
                std::DiscreteStateSpaceBlockFeedthrough::HasFeedthrough,
                0,
                0,
                0
        >>::kIns> BlockTraits<std::DiscreteStateSpaceBlock<
                ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>,
                std::DiscreteStateSpaceBlockFeedthrough::HasFeedthrough,
                0,
                0,
                0
        >>::inTypes =
                { demangle(typeid(Eigen::Vector<TScalar, NInput>).name()) };

        template<typename TScalar, int NState, int NInput, int NOutput>
        const ::std::array<::std::string, BlockTraits<std::DiscreteStateSpaceBlock<
                ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>,
                std::DiscreteStateSpaceBlockFeedthrough::HasFeedthrough,
                0,
                0,
                0
        >>::kOuts> BlockTraits<std::DiscreteStateSpaceBlock<
                ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>,
                std::DiscreteStateSpaceBlockFeedthrough::HasFeedthrough,
                0,
                0,
                0
        >>::outTypes =
                { demangle(typeid(Eigen::Vector<TScalar, NOutput>).name()) };

        template<typename TScalar, int NState, int NInput, int NOutput>
        const ::std::array<::std::string, BlockTraits<std::DiscreteStateSpaceBlock<
                ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>,
                std::DiscreteStateSpaceBlockFeedthrough::HasFeedthrough,
                0,
                0,
                0
        >>::kPars> BlockTraits<std::DiscreteStateSpaceBlock<
                ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>,
                std::DiscreteStateSpaceBlockFeedthrough::HasFeedthrough,
                0,
                0,
                0
        >>::parTypes =
                { demangle(typeid(ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>).name()) };

        template<typename TScalar, int NState, int NInput, int NOutput>
        const ::std::array<::std::string, 2> BlockTraits<std::DiscreteStateSpaceBlock<
                ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>,
                std::DiscreteStateSpaceBlockFeedthrough::HasFeedthrough,
                0,
                0,
                0
        >>::templateTypes =
                { demangle(typeid(ls::systems::DiscreteStateSpace<TScalar, NState, NInput, NOutput>).name()), demangle(typeid(std::DiscreteStateSpaceBlockFeedthrough::NoFeedthrough).name()) };
    }
}


#endif //LODESTAR_DISCRETESTATESPACEBLOCK_HPP
