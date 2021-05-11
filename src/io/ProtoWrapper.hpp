//
// Created by Hamza El-Kebir on 4/21/21.
//

#ifndef LODESTAR_PROTOWRAPPER_HPP
#define LODESTAR_PROTOWRAPPER_HPP

#ifdef LS_USE_PROTOBUF

#include "ProtoTypeTrait.hpp"

#define PROTO_WRAP(TYPE) template<> void ls::io::ProtoWrapper<TYPE>::wrap(typename ProtoTypeTrait<TYPE>::type *destObj)

#define PROTO_WRAP_STATIC(TYPE) template<> void ls::io::ProtoWrapper<TYPE>::wrap(typename ProtoTypeTrait<TYPE>::type *destObj, const TYPE *srcObj)

namespace ls { namespace io {
    template<typename T>
    class ProtoWrapper {
    public:
        ProtoWrapper() : obj(nullptr)
        {}

        explicit ProtoWrapper(T *_obj) : obj(_obj)
        {}

        void wrap(typename ProtoTypeTrait<T>::type *protoObj);

        static void wrap(typename ProtoTypeTrait<T>::type *protoObj, const T *obj);

        T *obj;
    };
} }

#endif // LS_USE_PROTOBUF

#endif //LODESTAR_PROTOWRAPPER_HPP
