//
// Created by Hamza El-Kebir on 2/10/22.
//

#ifndef LODESTAR_PROTOMSGOUTBLOCK_HPP
#define LODESTAR_PROTOMSGOUTBLOCK_HPP

#include "Lodestar/blocks/Block.hpp"
#include <Lodestar/io/NanopbWrapper.hpp>

namespace ls {
    namespace blocks {
        namespace std {
            template<typename TType, bool BEncrypt = false>
            class ProtoMsgOutBlock :
                    public Block<
                            ::std::tuple<TType>,
                            ::std::tuple<pb_ostream_t *>,
                            ::std::tuple<pb_ostream_t *>
                    > {
            public:
                using Base =
                Block<
                        ::std::tuple<TType>,
                        ::std::tuple<pb_ostream_t *>,
                        ::std::tuple<pb_ostream_t *>
                >;

                ProtoMsgOutBlock()
                {
                    bindEquation();
                }

                typename ::std::tuple_element<0, typename Base::Params>::type &
                stream()
                {
                    return this->template p<0>();
                }

                const typename ::std::tuple_element<0, typename Base::Params>::type &
                stream() const
                {
                    return this->template p<0>();
                }

                const ls::io::MsgInfo &info() const
                {
                    static ls::io::MsgInfo info;
                    info.encrypted = BEncrypt;
                    info.slot = this->template i<0>().connectionPtrs.begin()->slotId;
                    info.id = this->template i<0>().connectionPtrs.begin()->blockId;

                    return  info;
                }

            protected:
                void bindEquation()
                {
                    this->equation = ::std::bind(
                            &ProtoMsgOutBlock<TType, BEncrypt>::triggerFunction,
                            this,
                            ::std::placeholders::_1
                    );
                }

                void triggerFunction(Base &b)
                {
                    ls::io::NanopbWrapper<TType>::encode(b->template i<0>().object, info(), stream());
                    b.template o<0>() = b.template p<0>();
                }
            };
        }

        template<typename TType>
        class BlockTraits<std::ProtoMsgOutBlock<TType>> {
        public:
            static constexpr const BlockType blockType = BlockType::ProtoMsgOutBlock;
            enum {
                directFeedthrough = false
            };

            using type = std::ProtoMsgOutBlock<TType>;
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
        const ::std::array<::std::string, BlockTraits<std::ProtoMsgOutBlock<TType>>::kIns> BlockTraits<std::ProtoMsgOutBlock<TType>>::inTypes =
                {demangle(typeid(TType).name())};

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::ProtoMsgOutBlock<TType>>::kOuts> BlockTraits<std::ProtoMsgOutBlock<TType>>::outTypes =
                {demangle(typeid(pb_ostream_t *).name())};

        template<typename TType>
        const ::std::array<::std::string, BlockTraits<std::ProtoMsgOutBlock<TType>>::kPars> BlockTraits<std::ProtoMsgOutBlock<TType>>::parTypes =
                {demangle(typeid(pb_ostream_t *).name())};

        template<typename TType>
        const ::std::array<::std::string, 1> BlockTraits<std::ProtoMsgOutBlock<TType>>::templateTypes =
                {demangle(typeid(pb_ostream_t *).name())};
    }
}

#endif //LODESTAR_PROTOMSGOUTBLOCK_HPP
