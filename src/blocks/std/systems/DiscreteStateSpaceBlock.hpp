//
// Created by Hamza El-Kebir on 12/30/2021.
//

#ifndef LODESTAR_DISCRETESTATESPACEBLOCK_HPP
#define LODESTAR_DISCRETESTATESPACEBLOCK_HPP


#include "blocks/Block.hpp"
#include "systems/DiscreteStateSpace.hpp"
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

        template<typename TScalar, int NState, int NInput, int NOutput, std::DiscreteStateSpaceBlockFeedthrough TFeedthroughOps>
        class BlockTraits<std::DiscreteStateSpaceBlock<TScalar, TFeedthroughOps, NState, NInput, NOutput>> {
        public:
            static constexpr const BlockType blockType = BlockType::DiscreteStateSpaceBlock;
            static constexpr const bool directFeedthrough = (TFeedthroughOps == std::DiscreteStateSpaceBlockFeedthrough::HasFeedthrough);

            using type = std::DiscreteStateSpaceBlock<TScalar, TFeedthroughOps, NState, NInput, NOutput>;
            using Base = typename type::Base;

            static const constexpr int kIns = type::Base::kIns;
            static const constexpr int kOuts = type::Base::kOuts;
            static const constexpr int kPars = type::Base::kPars;

            static const constexpr int kNState = type::kNState;
            static const constexpr int kNInput = type::kNInput;
            static const constexpr int kNOutput = type::kNOutput;
        };
    }
}


#endif //LODESTAR_DISCRETESTATESPACEBLOCK_HPP
