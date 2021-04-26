//
// Created by Hamza El-Kebir on 4/21/21.
//

#ifndef LODESTAR_PROTOTYPETRAIT_HPP
#define LODESTAR_PROTOTYPETRAIT_HPP

#include "Eigen/Dense"
#include "systems/StateSpace.hpp"
#include "systems/TransferFunction.hpp"

#include "proto/ls.proto.eigen.pb.h"
#include "proto/ls.proto.systems.pb.h"

#define PROTO_TYPE_TRAIT(INP, RET) template<> struct ProtoTypeTrait<INP> { typedef RET type; }; template<> struct ProtoTypeTrait<RET> { typedef INP type; }

namespace ls { namespace io {
    template<typename T>
    struct ProtoTypeTrait {
        typedef T type;
    };

    PROTO_TYPE_TRAIT(Eigen::VectorXd, ls::proto::eigen::VectorXd);

    PROTO_TYPE_TRAIT(Eigen::MatrixXd, ls::proto::eigen::MatrixXd);

    PROTO_TYPE_TRAIT(ls::systems::StateSpace, ls::proto::systems::StateSpace);

    PROTO_TYPE_TRAIT(ls::systems::TransferFunction, ls::proto::systems::TransferFunction);
} }

#endif //LODESTAR_PROTOTYPETRAIT_HPP
