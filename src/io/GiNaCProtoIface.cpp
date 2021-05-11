//
// Created by Hamza El-Kebir on 5/9/21.
//

#ifdef LS_USE_PROTOBUF

#ifdef LS_USE_GINAC

#include "GiNaCProtoIface.hpp"

void ls::io::GiNaCProtoIface::symbol::generateProto()
{
    clearProto();

    _proto->set_name(_symbol->get_name());
}

void ls::io::GiNaCProtoIface::symbol::clearProto()
{
    _proto->clear_name();
}

#endif // LS_USE_GINAC

#endif // LS_USE_PROTOBUF