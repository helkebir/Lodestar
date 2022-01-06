//
// Created by Hamza El-Kebir on 5/9/21.
//

#ifndef LODESTAR_GINACPROTOIFACE_HPP
#define LODESTAR_GINACPROTOIFACE_HPP

#ifdef LS_USE_PROTOBUF

#ifdef LS_USE_GINAC

#include "ProtoIfaceABC.hpp"
#include <ginac/ginac.h>

#undef Mutable

#include "proto/ls.proto.ginac.pb.h"

namespace ls {
    namespace io {
        class GiNaCProtoIface {
        public:
            class symbol : public ProtoIfaceABC {
            public:
                symbol() : _proto(new proto::ginac::symbol)
                {}

                symbol(GiNaC::symbol *symbol) : _proto(
                        new proto::ginac::symbol), _symbol(symbol)
                {}

                symbol(proto::ginac::symbol *proto, GiNaC::symbol *symbol)
                        : _proto(proto), _symbol(symbol)
                {}

                void generateProto();

                void clearProto();

            private:
                GiNaC::symbol *_symbol;
                proto::ginac::symbol *_proto;
            };
        };
    }
}

#endif // LS_USE_GINAC

#endif // LS_USE_PROTOBUF

#endif //LODESTAR_GINACPROTOIFACE_HPP
