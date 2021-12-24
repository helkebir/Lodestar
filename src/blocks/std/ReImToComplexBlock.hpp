//
// Created by Hamza El-Kebir on 12/23/21.
//

#ifndef LODESTAR_REIMTOCOMPLEXBLOCK_HPP
#define LODESTAR_REIMTOCOMPLEXBLOCK_HPP

#include <iomanip>
#include <complex>
#include <cmath>
#include "blocks/Block.hpp"
#include "Eigen/Dense"

namespace ls {
    namespace blocks {
        namespace std {
            template<typename TType, typename SFINAE = void>
            class ReImToComplexBlock :
                    public Block<
                            ::std::tuple<TType>,
                            ::std::tuple<TType>,
                            BlockProto::empty
                    > {
                static_assert(true,
                              "ReImToComplexBlock not defined for this type.");
            };

            template<typename TType>
            class ReImToComplexBlock<TType, typename ::std::enable_if<(
                    ::std::is_same<TType, float>::value ||
                    ::std::is_same<TType, double>::value ||
                    ::std::is_same<TType, long double>::value)>::type>
                    :
                            public Block<
                                    ::std::tuple<TType, TType>,
                                    ::std::tuple<::std::complex<TType>>,
                                    BlockProto::empty
                            > {
            public:
                using type = ReImToComplexBlock<
                        TType,
                        typename ::std::enable_if<(
                                ::std::is_same<TType, float>::value ||
                                ::std::is_same<TType, double>::value ||
                                ::std::is_same<TType, long double>::value)>::type
                >;

                using Base =
                Block<
                        ::std::tuple<TType, TType>,
                        ::std::tuple<::std::complex<TType>>,
                        BlockProto::empty
                >;

                ReImToComplexBlock()
                {
                    bindEquation();
                }

                Signal<TType> &real()
                {
                    return this->template i<0>();
                }

                Signal<TType> &real(TType re)
                {
                    this->template i<0>() = re;
                    return this->template i<0>();
                }

                const Signal<TType> &real() const
                {
                    return this->template i<0>();
                }

                Signal<TType> &imag()
                {
                    return this->template i<1>();
                }

                Signal<TType> &imag(TType im)
                {
                    this->template i<1>() = im;
                    return this->template i<1>();
                }

                const Signal<TType> &imag() const
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
                    b.template o<0>().object.real(b.template i<0>());
                    b.template o<0>().object.imag(b.template i<1>());
                }
            };

            template<typename TScalar, int TRows, int TCols>
            class ReImToComplexBlock<Eigen::Matrix<TScalar, TRows, TCols>, typename ::std::enable_if<(
                    ::std::is_same<TScalar, float>::value ||
                    ::std::is_same<TScalar, double>::value ||
                    ::std::is_same<TScalar, long double>::value)>::type> :
                    public Block<
                            ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>>,
                            ::std::tuple<Eigen::Matrix<::std::complex<TScalar>, TRows, TCols>>,
                            BlockProto::empty
                    > {
            public:
                using type = ReImToComplexBlock<
                        Eigen::Matrix<TScalar, TRows, TCols>,
                        typename ::std::enable_if<(
                                ::std::is_same<TScalar, float>::value ||
                                ::std::is_same<TScalar, double>::value ||
                                ::std::is_same<TScalar, long double>::value)
                        >::type>;

                using Base =
                Block<
                        ::std::tuple<Eigen::Matrix<TScalar, TRows, TCols>, Eigen::Matrix<TScalar, TRows, TCols>>,
                        ::std::tuple<Eigen::Matrix<::std::complex<TScalar>, TRows, TCols>>,
                        BlockProto::empty
                >;

                using RealMatrix = Eigen::Matrix<TScalar, TRows, TCols>;

                ReImToComplexBlock()
                {
                    bindEquation();
                }

                Signal<RealMatrix> &real()
                {
                    return this->template i<0>();
                }

                Signal<RealMatrix> &real(const RealMatrix &re)
                {
                    this->template i<0>() = re;
                    return this->template i<0>();
                }

                const Signal<RealMatrix> &real() const
                {
                    return this->template i<0>();
                }

                Signal<RealMatrix> &imag()
                {
                    return this->template i<1>();
                }

                Signal<RealMatrix> &imag(const RealMatrix &im)
                {
                    this->template i<1>() = im;
                    return this->template i<1>();
                }

                const Signal<RealMatrix> &imag() const
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
                    b.template o<0>().object = real().object + ::std::complex<TScalar>(0, 1) * imag().object;
                }
            };
        }
    }
}


#endif //LODESTAR_REIMTOCOMPLEXBLOCK_HPP
