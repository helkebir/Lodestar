//
// Created by Hamza El-Kebir on 4/21/21.
//

#ifndef LODESTAR_PROTOTYPETRAIT_HPP
#define LODESTAR_PROTOTYPETRAIT_HPP

#ifdef LS_USE_PROTOBUF

#ifdef LS_USE_GINAC

#include "ginac/ginac.h"
#undef Mutable

#include "proto/ls.proto.ginac.pb.h"
#include "proto/ls.proto.symbolic.pb.h"

#endif

#include "Eigen/Dense"
#include "systems/StateSpace.hpp"
#include "systems/TransferFunction.hpp"

#include "proto/ls.proto.eigen.pb.h"
#include "proto/ls.proto.systems.pb.h"

#define PROTO_TYPE_TRAIT(INP, RET) template<> struct ProtoTypeTrait<INP> { typedef RET type; }; template<> struct ProtoTypeTrait<RET> { typedef INP type; }

namespace ls {
    namespace io {
        template<typename T>
        struct ProtoTypeTrait {
            typedef T type;
        };

        PROTO_TYPE_TRAIT(Eigen::VectorXd, ls::proto::eigen::VectorXd);

        PROTO_TYPE_TRAIT(Eigen::MatrixXd, ls::proto::eigen::MatrixXd);

        PROTO_TYPE_TRAIT(ls::systems::StateSpace,
                         ls::proto::systems::StateSpace);

        PROTO_TYPE_TRAIT(ls::systems::TransferFunction,
                         ls::proto::systems::TransferFunction);

#ifdef LS_USE_GINAC
        PROTO_TYPE_TRAIT(GiNaC::ex, ls::proto::ginac::ex);

        PROTO_TYPE_TRAIT(GiNaC::symbol, ls::proto::ginac::symbol);

        PROTO_TYPE_TRAIT(GiNaC::lst, ls::proto::ginac::lst);
#endif
    }
}

#endif // LS_USE_PROTOBUF

#endif //LODESTAR_PROTOTYPETRAIT_HPP
