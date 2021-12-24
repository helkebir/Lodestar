//
// Created by Hamza El-Kebir on 12/24/21.
//

#ifndef LODESTAR_QUATERNIONBLOCK_HPP
#define LODESTAR_QUATERNIONBLOCK_HPP

#include "blocks/Block.hpp"
#include "aux/CompileTimeQualifiers.hpp"
#include "Eigen/Dense"

namespace ls {
    namespace blocks {
        namespace std {
            enum class QuaternionBlockParameter {
                Parametric,
                AdditionalInput
            };

            template<typename TType,
                    QuaternionBlockParameter TPar = QuaternionBlockParameter::Parametric>
            class QuaternionBlock {
                static_assert(::std::is_same<TType, TType>::value,
                              "QuaternionBlock not defined for this type.");
            };

            template<typename TScalar>
            class QuaternionBlock<
                    Eigen::Matrix<TScalar, 3, 1>,
                    QuaternionBlockParameter::Parametric> :
                    public Block<
                            ::std::tuple<Eigen::Matrix<TScalar, 3, 1>>,
                            ::std::tuple<Eigen::Matrix<TScalar, 3, 1>>,
                            ::std::tuple<Eigen::Quaternion<TScalar>>
                    > {

                static_assert(::std::is_arithmetic<TScalar>::value,
                              "Scalar must be of arithmetic type.");

            public:
                using type =
                QuaternionBlock<Eigen::Matrix<TScalar, 3, 1>, QuaternionBlockParameter::Parametric>;

                using Base =
                Block<
                        ::std::tuple<Eigen::Matrix<TScalar, 3, 1>>,
                        ::std::tuple<Eigen::Matrix<TScalar, 3, 1>>,
                        ::std::tuple<Eigen::Quaternion<TScalar>>
                >;

                using Quaternion = Eigen::Quaternion<TScalar>;

                QuaternionBlock()
                {
                    quaternion(Quaternion::Identity());
                    bindEquation();
                }

                QuaternionBlock(const Quaternion &quat)
                {
                    quaternion(quat);
                    bindEquation();
                }

                Quaternion &quaternion()
                {
                    return this->template p<0>();
                }

                Quaternion &quaternion(const Quaternion &quat)
                {
                    this->template p<0>() = quat;
                    return this->template p<0>();
                }

                const Quaternion &quaternion() const
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
                    b.template o<0>() = quaternion() * b.template i<0>().object;
                }
            };

            template<typename TScalar>
            class QuaternionBlock<
                    Eigen::Matrix<TScalar, 3, 1>,
                    QuaternionBlockParameter::AdditionalInput> :
                    public Block<
                            ::std::tuple<Eigen::Matrix<TScalar, 3, 1>, Eigen::Quaternion<TScalar>>,
                            ::std::tuple<Eigen::Matrix<TScalar, 3, 1>>,
                            BlockProto::empty
                    > {

                static_assert(::std::is_arithmetic<TScalar>::value,
                              "Scalar must be of arithmetic type.");

            public:
                using type =
                QuaternionBlock<Eigen::Matrix<TScalar, 3, 1>, QuaternionBlockParameter::AdditionalInput>;

                using Base =
                Block<
                        ::std::tuple<Eigen::Matrix<TScalar, 3, 1>, Eigen::Quaternion<TScalar>>,
                        ::std::tuple<Eigen::Matrix<TScalar, 3, 1>>,
                        BlockProto::empty
                >;

                using Quaternion = Eigen::Quaternion<TScalar>;

                QuaternionBlock()
                {
                    quaternion(Quaternion::Identity());
                    bindEquation();
                }

                QuaternionBlock(const Quaternion &quat)
                {
                    quaternion(quat);
                    bindEquation();
                }

                Signal<Quaternion> &quaternion()
                {
                    return this->template i<1>();
                }

                Signal<Quaternion> &quaternion(const Quaternion &quat)
                {
                    this->template i<1>() = quat;
                    return this->template i<1>();
                }

                Signal<Quaternion> &quaternion(const Signal<Quaternion> &quat)
                {
                    this->template i<1>() = quat;
                    return this->template i<1>();
                }

                const Signal<Quaternion> &quaternion() const
                {
                    return this->template i<1>();
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
                    b.template o<0>() =
                            quaternion().object * b.template i<0>().object;
                }
            };

            template<typename TScalar>
            class QuaternionBlock<
                    Eigen::Matrix<TScalar, 1, 3>,
                    QuaternionBlockParameter::Parametric> :
                    public Block<
                            ::std::tuple<Eigen::Matrix<TScalar, 1, 3>>,
                            ::std::tuple<Eigen::Matrix<TScalar, 1, 3>>,
                            ::std::tuple<Eigen::Quaternion<TScalar>>
                    > {

                static_assert(::std::is_arithmetic<TScalar>::value,
                              "Scalar must be of arithmetic type.");

            public:
                using type =
                QuaternionBlock<Eigen::Matrix<TScalar, 1, 3>, QuaternionBlockParameter::Parametric>;

                using Base =
                Block<
                        ::std::tuple<Eigen::Matrix<TScalar, 1, 3>>,
                        ::std::tuple<Eigen::Matrix<TScalar, 1, 3>>,
                        ::std::tuple<Eigen::Quaternion<TScalar>>
                >;

                using Quaternion = Eigen::Quaternion<TScalar>;

                QuaternionBlock()
                {
                    quaternion(Quaternion::Identity());
                    bindEquation();
                }

                QuaternionBlock(const Quaternion &quat)
                {
                    quaternion(quat);
                    bindEquation();
                }

                Quaternion &quaternion()
                {
                    return this->template p<0>();
                }

                Quaternion &quaternion(const Quaternion &quat)
                {
                    this->template p<0>() = quat;
                    return this->template p<0>();
                }

                const Quaternion &quaternion() const
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
                    b.template o<0>() = (quaternion() *
                                         b.template i<0>().object.transpose()).transpose();
                }
            };

            template<typename TScalar>
            class QuaternionBlock<
                    Eigen::Matrix<TScalar, 1, 3>,
                    QuaternionBlockParameter::AdditionalInput> :
                    public Block<
                            ::std::tuple<Eigen::Matrix<TScalar, 1, 3>, Eigen::Quaternion<TScalar>>,
                            ::std::tuple<Eigen::Matrix<TScalar, 1, 3>>,
                            BlockProto::empty
                    > {

                static_assert(::std::is_arithmetic<TScalar>::value,
                              "Scalar must be of arithmetic type.");

            public:
                using type =
                QuaternionBlock<Eigen::Matrix<TScalar, 1, 3>, QuaternionBlockParameter::AdditionalInput>;

                using Base =
                Block<
                        ::std::tuple<Eigen::Matrix<TScalar, 1, 3>, Eigen::Quaternion<TScalar>>,
                        ::std::tuple<Eigen::Matrix<TScalar, 1, 3>>,
                        BlockProto::empty
                >;

                using Quaternion = Eigen::Quaternion<TScalar>;

                QuaternionBlock()
                {
                    quaternion(Quaternion::Identity());
                    bindEquation();
                }

                QuaternionBlock(const Quaternion &quat)
                {
                    quaternion(quat);
                    bindEquation();
                }

                Signal<Quaternion> &quaternion()
                {
                    return this->template i<1>();
                }

                Signal<Quaternion> &quaternion(const Quaternion &quat)
                {
                    this->template i<1>() = quat;
                    return this->template i<1>();
                }

                Signal<Quaternion> &quaternion(const Signal<Quaternion> &quat)
                {
                    this->template i<1>() = quat;
                    return this->template i<1>();
                }

                const Signal<Quaternion> &quaternion() const
                {
                    return this->template i<1>();
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
                    b.template o<0>() = (quaternion().object *
                                         b.template i<0>().object.transpose()).transpose();
                }
            };

            // Scalar inputs

            template<typename TScalar>
            class QuaternionBlock<
                    TScalar,
                    QuaternionBlockParameter::Parametric> :
                    public Block<
                            ::std::tuple<TScalar, TScalar, TScalar>,
                            ::std::tuple<TScalar, TScalar, TScalar>,
                            ::std::tuple<Eigen::Quaternion<TScalar>>
                    > {

                static_assert(::std::is_arithmetic<TScalar>::value,
                              "Scalar must be of arithmetic type.");

            public:
                using type =
                QuaternionBlock<TScalar, QuaternionBlockParameter::Parametric>;

                using Base =
                Block<
                        ::std::tuple<TScalar, TScalar, TScalar>,
                        ::std::tuple<TScalar, TScalar, TScalar>,
                        ::std::tuple<Eigen::Quaternion<TScalar>>
                >;

                using Quaternion = Eigen::Quaternion<TScalar>;

                QuaternionBlock()
                {
                    quaternion(Quaternion::Identity());
                    bindEquation();
                }

                QuaternionBlock(const Quaternion &quat)
                {
                    quaternion(quat);
                    bindEquation();
                }

                Quaternion &quaternion()
                {
                    return this->template p<0>();
                }

                Quaternion &quaternion(const Quaternion &quat)
                {
                    this->template p<0>() = quat;
                    return this->template p<0>();
                }

                const Quaternion &quaternion() const
                {
                    return this->template p<0>();
                }

            protected:
                Eigen::Vector<TScalar, 3> vec_;

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
                    vec_
                            << b.template i<0>().object, b.template i<1>().object, b.template i<2>().object;
                    vec_ = quaternion() * vec_;
                    b.template o<0>() = vec_.x();
                    b.template o<1>() = vec_.y();
                    b.template o<2>() = vec_.z();
                }
            };

            template<typename TScalar>
            class QuaternionBlock<
                    TScalar,
                    QuaternionBlockParameter::AdditionalInput> :
                    public Block<
                            ::std::tuple<TScalar, TScalar, TScalar, Eigen::Quaternion<TScalar>>,
                            ::std::tuple<TScalar, TScalar, TScalar>,
                            BlockProto::empty
                    > {

                static_assert(::std::is_arithmetic<TScalar>::value,
                              "Scalar must be of arithmetic type.");

            public:
                using type =
                QuaternionBlock<TScalar, QuaternionBlockParameter::AdditionalInput>;

                using Base =
                Block<
                        ::std::tuple<TScalar, TScalar, TScalar, Eigen::Quaternion<TScalar>>,
                        ::std::tuple<TScalar, TScalar, TScalar>,
                        BlockProto::empty
                >;

                using Quaternion = Eigen::Quaternion<TScalar>;

                QuaternionBlock()
                {
                    quaternion(Quaternion::Identity());
                    bindEquation();
                }

                QuaternionBlock(const Quaternion &quat)
                {
                    quaternion(quat);
                    bindEquation();
                }

                Signal<Quaternion> &quaternion()
                {
                    return this->template i<3>();
                }

                Signal<Quaternion> &quaternion(const Quaternion &quat)
                {
                    this->template i<3>() = quat;
                    return this->template i<3>();
                }

                Signal<Quaternion> &quaternion(const Signal<Quaternion> &quat)
                {
                    this->template i<3>() = quat;
                    return this->template i<3>();
                }

                const Signal<Quaternion> &quaternion() const
                {
                    return this->template i<3>();
                }

            protected:
                Eigen::Vector<TScalar, 3> vec_;

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
                    vec_
                            << b.template i<0>().object, b.template i<1>().object, b.template i<2>().object;
                    vec_ = quaternion().object * vec_;
                    b.template o<0>() = vec_.x();
                    b.template o<1>() = vec_.y();
                    b.template o<2>() = vec_.z();
                }
            };
        }
    }
}


#endif //LODESTAR_QUATERNIONBLOCK_HPP
