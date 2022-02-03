//
// Created by Hamza El-Kebir on 12/23/21.
//

#ifndef LODESTAR_CONSTANTBLOCK_HPP
#define LODESTAR_CONSTANTBLOCK_HPP

#include "Lodestar/blocks/Block.hpp"

namespace ls {
    namespace blocks {
        namespace std {
            template<typename TType>
            class ConstantBlock :
                    public Block<
                            BlockProto::empty,
                            ::std::tuple<TType>,
                            ::std::tuple<TType>
                    > {
            public:
                using Base =
                Block<
                        BlockProto::empty,
                        ::std::tuple<TType>,
                        ::std::tuple<TType>
                >;

                ConstantBlock()
                {
                    bindEquation();
                }

                ConstantBlock(const TType &constant)
                {
                    this->template p<0>() = constant;
                    bindEquation();
                }

                typename ::std::tuple_element<0, typename Base::Params>::type &
                constant()
                {
                    return this->template p<0>();
                }

                const typename ::std::tuple_element<0, typename Base::Params>::type &
                constant() const
                {
                    return this->template p<0>();
                }

#ifdef LS_USE_GINAC

                const ::std::array<GiNaC::ex, Base::kIns> &inputSymbols()
                {
                    static ::std::array<GiNaC::ex, Base::kIns> arr;
                    static bool isInit = false;

                    if (!isInit) {
                        for (int i = 0; i < Base::kIns; i++) {
                            if (ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TType>::value) {
                                GiNaC::lst input;
                                for (int ii = 0; ii <
                                                 ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TType>::rows; ii++) {
                                    GiNaC::lst row;
                                    for (int jj = 0; jj <
                                                     ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TType>::cols; jj++) {
                                        GiNaC::symbol entry{
                                                "blk" + ::std::to_string(this->id) + "_i_" + ::std::to_string(i) +
                                                "_r_" + ::std::to_string(ii) + "_c_" + ::std::to_string(jj),
                                                "\\text{BLK}^{i, " + ::std::to_string(i) + ", " + ::std::to_string(ii) +
                                                ", " + ::std::to_string(jj) + "}_{" + ::std::to_string(this->id) + "}"};

                                        row.append(entry);
                                    }
                                    input.append(row);
                                }

                                arr[i] = GiNaC::lst_to_matrix(input);
                            } else {
                                arr[i] = GiNaC::symbol{"blk" + ::std::to_string(this->id) + "_i_" + ::std::to_string(i),
                                                       "\\text{BLK}^{i, " + ::std::to_string(i) + "}_{" +
                                                       ::std::to_string(this->id) +
                                                       "}"};
                            }
                        }

                        isInit = true;
                    }

                    return arr;
                }

                const ::std::array<GiNaC::ex, Base::kOuts> &outputSymbols()
                {
                    static ::std::array<GiNaC::ex, Base::kOuts> arr;
                    static bool isInit = false;

                    if (!isInit) {
                        for (int i = 0; i < Base::kOuts; i++) {
                            if (ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TType>::value) {
                                GiNaC::lst output;
                                for (int ii = 0; ii <
                                                 ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TType>::rows; ii++) {
                                    GiNaC::lst row;
                                    for (int jj = 0; jj <
                                                     ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TType>::cols; jj++) {
                                        GiNaC::symbol entry{
                                                "blk" + ::std::to_string(this->id) + "_o_" + ::std::to_string(i) +
                                                "_r_" + ::std::to_string(ii) + "_c_" + ::std::to_string(jj),
                                                "\\text{BLK}^{i, " + ::std::to_string(i) + ", " + ::std::to_string(ii) +
                                                ", " + ::std::to_string(jj) + "}_{" + ::std::to_string(this->id) + "}"};

                                        row.append(entry);
                                    }
                                    output.append(row);
                                }

                                arr[i] = GiNaC::lst_to_matrix(output);
                            } else {
                                arr[i] = GiNaC::symbol{"blk" + ::std::to_string(this->id) + "_o_" + ::std::to_string(i),
                                                       "\\text{BLK}^{i, " + ::std::to_string(i) + "}_{" +
                                                       ::std::to_string(this->id) +
                                                       "}"};
                            }
                        }

                        isInit = true;
                    }

                    return arr;
                }

                const ::std::array<GiNaC::ex, 1> &parameterSymbols()
                {
                    static ::std::array<GiNaC::ex, 1> arr;
                    static bool isInit = false;

                    if (!isInit) {

                        int i = 0;

                        if (ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TType>::value) {
                            GiNaC::lst output;
                            for (int ii = 0;
                                 ii < ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TType>::rows; ii++) {
                                GiNaC::lst row;
                                for (int jj = 0; jj <
                                                 ls::aux::TemplateTraits::BinaryOperators::parseMatrixLike<TType>::cols; jj++) {
                                    GiNaC::symbol entry{
                                            "blk" + ::std::to_string(this->id) + "_p_" + ::std::to_string(i) + "_r_" +
                                            ::std::to_string(ii) + "_c_" + ::std::to_string(jj),
                                            "\\text{BLK}^{i, " + ::std::to_string(i) + ", " + ::std::to_string(ii) +
                                            ", " + ::std::to_string(jj) + "}_{" + ::std::to_string(this->id) + "}"};

                                    row.append(entry);
                                }
                                output.append(row);
                            }

                            arr[i] = GiNaC::lst_to_matrix(output);
                        } else {
                            arr[i] = GiNaC::symbol{"blk" + ::std::to_string(this->id) + "_p_" + ::std::to_string(i),
                                                   "\\text{BLK}^{i, " + ::std::to_string(i) + "}_{" +
                                                   ::std::to_string(this->id) +
                                                   "}"};
                        }

                        isInit = true;
                    }

                    return arr;
                }

#endif

            protected:
                void bindEquation()
                {
                    this->equation = ::std::bind(
                            &ConstantBlock<TType>::triggerFunction,
                            this,
                            ::std::placeholders::_1
                    );

#ifdef LS_USE_GINAC
                    GiNaC::function_options fops("blkf" + ::std::to_string(this->id) + "__", this->blkFunc_NPARAMS);
                    ls::blocks::symbolicEvalFunctionMap[this->id] = [&](const ::std::vector<GiNaC::ex> &exvec) -> GiNaC::ex {
                        return GiNaC::ex{this->parameterSymbols()[0]};
                    };

                    fops.eval_func(ls::blocks::symbolicEval);


                    this->serial = GiNaC::function::register_new(
                            fops
                    );
#endif
                }

                void triggerFunction(Base &b)
                {
                    b.template o<0>() = b.template p<0>();
                }
            };
        }

        template<typename TType>
        class BlockTraits<std::ConstantBlock<TType>> {
        public:
            static constexpr const BlockType blockType = BlockType::ConstantBlock;
            enum {
                directFeedthrough = true
            };

            using type = std::ConstantBlock<TType>;
            using Base = typename type::Base;

            enum {
                kIns = Base::kIns,
                kOuts = Base::kOuts,
                kPars = Base::kPars
            };

            static const ::std::array<::std::string, kIns> inTypes;
            static const ::std::array<::std::string, kOuts> outTypes;
            static const ::std::array<::std::string, kPars> parTypes;

            static const ::std::array<::std::string, 1> templateTypes;
        };

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::ConstantBlock<TType>>::kIns> BlockTraits<std::ConstantBlock<TType>>::inTypes =
                {};

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::ConstantBlock<TType>>::kOuts> BlockTraits<std::ConstantBlock<TType>>::outTypes =
                {demangle(typeid(TType).name())};

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::ConstantBlock<TType>>::kPars> BlockTraits<std::ConstantBlock<TType>>::parTypes =
                {demangle(typeid(TType).name())};

        template<typename TType>
        const ::std::array<::std::string, 1> BlockTraits<std::ConstantBlock<TType>>::templateTypes =
                {demangle(typeid(TType).name())};
    }
}


#endif //LODESTAR_CONSTANTBLOCK_HPP
