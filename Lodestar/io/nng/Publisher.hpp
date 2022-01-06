//
// Created by Hamza El-Kebir on 6/13/21.
//

#ifndef LODESTAR_PUBLISHER_HPP
#define LODESTAR_PUBLISHER_HPP

#ifdef LS_USE_NNG

extern "C" {
#include <nng/nng.h>
#include <nng/protocol/pubsub0/pub.h>
}

#include "nanopb/pb_encode.h"
#include "nanopb/pb_decode.h"

class Publisher {

};

#endif

#endif //LODESTAR_PUBLISHER_HPP
