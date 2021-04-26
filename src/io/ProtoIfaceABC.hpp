//
// Created by Hamza El-Kebir on 4/19/21.
//

#ifndef LODESTAR_PROTOIFACEABC_HPP
#define LODESTAR_PROTOIFACEABC_HPP

namespace ls { namespace io {
    class ProtoIfaceABC {
    public:
        virtual void generateProto() = 0;
        virtual void clearProto() = 0;
    };
} }

#endif //LODESTAR_PROTOIFACEABC_HPP
