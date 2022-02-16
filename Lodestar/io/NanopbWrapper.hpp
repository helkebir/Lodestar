//
// Created by Hamza El-Kebir on 2/12/22.
//

#ifndef LODESTAR_NANOPBWRAPPER_HPP
#define LODESTAR_NANOPBWRAPPER_HPP

#include "Lodestar/io/proto/ls.proto.herald.pb.h"
#include "Lodestar/io/proto/ls.proto.types.pb.h"
#include "Lodestar/io/proto/ls.proto.matrix.pb.h"
#include "Lodestar/io/proto/ls.proto.vector.pb.h"
#include "Lodestar/io/proto/ls.proto.array.pb.h"

#include <pb_encode.h>
#include <pb_decode.h>

#include <Lodestar/aux/AlwaysFalse.hpp>
#include <Eigen/Dense>

namespace ls {
    namespace io {
        struct MsgInfo {
            int id = -1;
            int slot = 0;
            unsigned long publicKey = 0;
            bool encrypted = false;
            ls_proto_Type type = ls_proto_Type_unknown_t;
        };

        template<typename TType = void>
        struct NanopbWrapper {
            static_assert(always_false<TType>::value, "Wrapper not defined for this type.");

            enum {
                hasArrayType = false
            };

            using arrayType = void;

            enum {
                pbType = ls_proto_Type_unknown_t
            };
        };

        template<>
        struct NanopbWrapper<void> {
            enum {
                pbType = ls_proto_Type_unknown_t
            };

            enum {
                hasArrayType = false
            };

        };

        template<>
        struct NanopbWrapper<bool> {
            enum {
                pbType = ls_proto_Type_bool_t
            };

            enum {
                hasArrayType = true
            };
            using arrayType = ls_proto_ArrayBool;

            static ls_proto_Herald makeHerald()
            {
                ls_proto_Herald herald = ls_proto_Herald_init_default;
                herald.msgType = static_cast<ls_proto_Type>(pbType);

                return herald;
            }
        };

        template<>
        struct NanopbWrapper<char> {
            enum {
                pbType = ls_proto_Type_char_t
            };

            enum {
                hasArrayType = true
            };
            using arrayType = ls_proto_ArrayBytes;

            static ls_proto_Herald makeHerald()
            {
                ls_proto_Herald herald = ls_proto_Herald_init_default;
                herald.msgType = static_cast<ls_proto_Type>(pbType);

                return herald;
            }
        };

        template<>
        struct NanopbWrapper<double> {
            enum {
                pbType = ls_proto_Type_double_t
            };

            enum {
                hasArrayType = true
            };
            using arrayType = ls_proto_ArrayDouble;

            static ls_proto_Herald makeHerald()
            {
                ls_proto_Herald herald = ls_proto_Herald_init_default;
                herald.msgType = static_cast<ls_proto_Type>(pbType);

                return herald;
            }
        };

        template<>
        struct NanopbWrapper<float> {
            enum {
                pbType = ls_proto_Type_float_t
            };

            enum {
                hasArrayType = true
            };
            using arrayType = ls_proto_ArrayFloat;

            static ls_proto_Herald makeHerald()
            {
                ls_proto_Herald herald = ls_proto_Herald_init_default;
                herald.msgType = static_cast<ls_proto_Type>(pbType);

                return herald;
            }
        };

        template<>
        struct NanopbWrapper<::std::uint32_t> {
            enum {
                pbType = ls_proto_Type_uint32_t
            };

            enum {
                hasArrayType = true
            };
            using arrayType = ls_proto_ArrayInt32;

            static ls_proto_Herald makeHerald()
            {
                ls_proto_Herald herald = ls_proto_Herald_init_default;
                herald.msgType = static_cast<ls_proto_Type>(pbType);

                return herald;
            }
        };

        template<>
        struct NanopbWrapper<::std::int32_t> {
            enum {
                pbType = ls_proto_Type_int32_t
            };

            enum {
                hasArrayType = true
            };
            using arrayType = ls_proto_ArrayInt32;

            static ls_proto_Herald makeHerald()
            {
                ls_proto_Herald herald = ls_proto_Herald_init_default;
                herald.msgType = static_cast<ls_proto_Type>(pbType);

                return herald;
            }
        };

        template<>
        struct NanopbWrapper<::std::uint64_t> {
            enum {
                pbType = ls_proto_Type_uint64_t
            };

            enum {
                hasArrayType = true
            };
            using arrayType = ls_proto_ArrayUInt64;

            static ls_proto_Herald makeHerald()
            {
                ls_proto_Herald herald = ls_proto_Herald_init_default;
                herald.msgType = static_cast<ls_proto_Type>(pbType);

                return herald;
            }
        };

        template<>
        struct NanopbWrapper<::std::int64_t> {
            enum {
                pbType = ls_proto_Type_int64_t
            };

            enum {
                hasArrayType = true
            };
            using arrayType = ls_proto_ArrayInt64;

            static ls_proto_Herald makeHerald()
            {
                ls_proto_Herald herald = ls_proto_Herald_init_default;
                herald.msgType = static_cast<ls_proto_Type>(pbType);

                return herald;
            }
        };

        struct NanopbArg {
            ::std::function<bool(pb_ostream_t *, const pb_field_t *, void *const *)> *fEncode;
            ::std::function<bool(pb_istream_t *, const pb_field_t *, void **)> *fDecode;
            void *data;
            void const *dataConst;
        };

        static bool encode_nanopb(pb_ostream_t *stream, const pb_field_t *field, void *const *arg)
        {
            auto mArg = (const NanopbArg *) *arg;

            return mArg->fEncode->operator()(stream, field, arg);
        }

        static bool decode_nanopb(pb_istream_t *stream, const pb_field_t *field, void **arg)
        {
            auto mArg = (NanopbArg *) *arg;

            return mArg->fDecode->operator()(stream, field, arg);
        }

        template<typename TScalar, int NRows, int NCols, int NOptions>
        struct NanopbWrapper<Eigen::Matrix<TScalar, NRows, NCols, NOptions>> {
            static_assert((NRows >= 0) && (NCols >= 0), "Matrix must be of fixed size.");
            static_assert(NanopbWrapper<TScalar>::hasArrayType, "An array message must be defined for this type.");

            enum {
                pbType = ls_proto_Type_matrix_t
            };

            using heraldType = ls_proto_Herald;
            using subHeraldType = ls_proto_MatrixHerald;
            using msgType = typename NanopbWrapper<TScalar>::arrayType;

            enum {
                hasArrayType = false
            };

            static ls_proto_Herald makeHerald()
            {
                ls_proto_Herald herald = ls_proto_Herald_init_default;
                herald.msgType = static_cast<ls_proto_Type>(pbType);

                return herald;
            }

            static ls_proto_MatrixHerald makeSubHerald()
            {
                ls_proto_MatrixHerald matrixHerald = ls_proto_MatrixHerald_init_default;

                matrixHerald.type = static_cast<ls_proto_Type>(NanopbWrapper<TScalar>::pbType);
                matrixHerald.rows = NRows;
                matrixHerald.cols = NCols;
                if ((NOptions & Eigen::StorageOptions::RowMajor) == Eigen::StorageOptions::RowMajor) {
                    matrixHerald.has_ordering = true;
                    matrixHerald.ordering = ls_proto_MatrixOrdering_rowMajor;
                } else if ((NOptions & Eigen::StorageOptions::ColMajor) == Eigen::StorageOptions::ColMajor) {
                    matrixHerald.has_ordering = true;
                    matrixHerald.ordering = ls_proto_MatrixOrdering_colMajor;
                }

                return matrixHerald;
            }

            static auto makeEncodingMessage(const Eigen::Matrix<TScalar, NRows, NCols, NOptions> &M, NanopbArg &nArg,
                                            const ls_proto_MatrixHerald &mHerald) -> typename NanopbWrapper<TScalar>::arrayType
            {
                typename NanopbWrapper<TScalar>::arrayType array;

                nArg.dataConst = &M;
                static ::std::function<bool(pb_ostream_t *, const pb_field_t *, void *const *)> fEncode;

                if (mHerald.type == ls_proto_Type_double_t) {
                    array = ls_proto_ArrayDouble_init_default;
                    if (mHerald.has_ordering) {
                        if (mHerald.ordering == ls_proto_MatrixOrdering_rowMajor) {
                            fEncode = decltype(fEncode){
                                    [](pb_ostream_t *stream, const pb_field_t *field, void *const *arg) -> bool {
                                        auto mArg = (NanopbArg *) *arg;
                                        auto M = (const Eigen::Matrix<TScalar, NRows, NCols, NOptions> *) mArg->dataConst;
                                        double value;
                                        for (int i = 0; i < NRows; i++) {
                                            for (int j = 0; j < NCols; j++) {
                                                if (!pb_encode_tag_for_field(stream, field))
                                                    return false;

                                                value = (*M)(i, j);

                                                if (!pb_encode_fixed64(stream, &value))
                                                    return false;
                                            }
                                        }

                                        return true;
                                    }};
                        } else {
                            fEncode = decltype(fEncode){
                                    [](pb_ostream_t *stream, const pb_field_t *field, void *const *arg) -> bool {
                                        auto mArg = (NanopbArg *) *arg;
                                        auto M = (const Eigen::Matrix<TScalar, NRows, NCols, NOptions> *) mArg->dataConst;
                                        double value;
                                        for (int j = 0; j < NCols; j++) {
                                            for (int i = 0; i < NRows; i++) {
                                                if (!pb_encode_tag_for_field(stream, field))
                                                    return false;

                                                value = (*M)(i, j);

                                                if (!pb_encode_fixed64(stream, &value))
                                                    return false;
                                            }
                                        }

                                        return true;
                                    }};
                        }
                    } else {
                        fEncode = decltype(fEncode){
                                [](pb_ostream_t *stream, const pb_field_t *field, void *const *arg) -> bool {
                                    auto mArg = (NanopbArg *) *arg;
                                    auto M = (const Eigen::Matrix<TScalar, NRows, NCols, NOptions> *) mArg->dataConst;
                                    double value;
                                    for (int j = 0; j < NCols; j++) {
                                        for (int i = 0; i < NRows; i++) {
                                            if (!pb_encode_tag_for_field(stream, field))
                                                return false;

                                            value = (*M)(i, j);

                                            if (!pb_encode_fixed64(stream, &value))
                                                return false;
                                        }
                                    }

                                    return true;
                                }};
                    }
                }

                if (mHerald.type == ls_proto_Type_float_t) {
                    array = ls_proto_ArrayFloat_init_default;
                    if (mHerald.has_ordering) {
                        if (mHerald.ordering == ls_proto_MatrixOrdering_rowMajor) {
                            fEncode = decltype(fEncode){
                                    [](pb_ostream_t *stream, const pb_field_t *field, void *const *arg) -> bool {
                                        auto mArg = (NanopbArg *) *arg;
                                        auto M = (const Eigen::Matrix<TScalar, NRows, NCols, NOptions> *) mArg->dataConst;
                                        float value;
                                        for (int i = 0; i < NRows; i++) {
                                            for (int j = 0; j < NCols; j++) {
                                                if (!pb_encode_tag_for_field(stream, field))
                                                    return false;

                                                value = (*M)(i, j);

                                                if (!pb_encode_fixed32(stream, &value))
                                                    return false;
                                            }
                                        }

                                        return true;
                                    }};
                        } else {
                            fEncode = decltype(fEncode){
                                    [](pb_ostream_t *stream, const pb_field_t *field, void *const *arg) -> bool {
                                        auto mArg = (NanopbArg *) *arg;
                                        auto M = (const Eigen::Matrix<TScalar, NRows, NCols, NOptions> *) mArg->dataConst;
                                        float value;
                                        for (int j = 0; j < NCols; j++) {
                                            for (int i = 0; i < NRows; i++) {
                                                if (!pb_encode_tag_for_field(stream, field))
                                                    return false;

                                                value = (*M)(i, j);

                                                if (!pb_encode_fixed32(stream, &value))
                                                    return false;
                                            }
                                        }

                                        return true;
                                    }};
                        }
                    } else {
                        fEncode = decltype(fEncode){
                                [](pb_ostream_t *stream, const pb_field_t *field, void *const *arg) -> bool {
                                    auto mArg = (NanopbArg *) *arg;
                                    auto M = (const Eigen::Matrix<TScalar, NRows, NCols, NOptions> *) mArg->dataConst;
                                    float value;
                                    for (int j = 0; j < NCols; j++) {
                                        for (int i = 0; i < NRows; i++) {
                                            if (!pb_encode_tag_for_field(stream, field))
                                                return false;

                                            value = (*M)(i, j);

                                            if (!pb_encode_fixed32(stream, &value))
                                                return false;
                                        }
                                    }

                                    return true;
                                }};
                    }
                }

                nArg.fEncode = &fEncode;

                array.values.funcs.encode = &encode_nanopb;
                array.values.arg = (void *) &nArg;
                array.size = NRows * NCols;

                return array;
            }

            struct MatrixCounter {
                void *M;
                int i;
                int j;
            };

            static auto makeDecodingMessage(Eigen::Matrix<TScalar, NRows, NCols, NOptions> &M, NanopbArg &nArg, MatrixCounter &MC,
                                            const ls_proto_MatrixHerald &mHerald) -> typename NanopbWrapper<TScalar>::arrayType
            {
                typename NanopbWrapper<TScalar>::arrayType array;
                array.size = NRows * NCols;

//                auto MC = new MatrixCounter{};
//                MC->M = &M;
//                MC->i = 0;
//                MC->j = 0;

                MC.M = &M;
                MC.i = 0;
                MC.j = 0;

                nArg.data = &MC;
                static ::std::function<bool(pb_istream_t *, const pb_field_t *, void **)> fDecode;

                if (mHerald.type == ls_proto_Type_double_t) {
                    array = ls_proto_ArrayDouble_init_default;
                    if (mHerald.has_ordering) {
                        if (mHerald.ordering == ls_proto_MatrixOrdering_rowMajor) {
                            fDecode = decltype(fDecode){
                                    [](pb_istream_t *stream, const pb_field_t *field, void **arg) -> bool {
                                        auto MC = (MatrixCounter *) ((NanopbArg *) *arg)->data;
                                        auto M = (Eigen::Matrix<TScalar, NRows, NCols, NOptions> *) MC->M;
                                        double value;

                                        if (!pb_decode_fixed64(stream, &value))
                                            return false;

                                        (*M)(MC->i, MC->j) = value;

                                        MC->j++;
                                        MC->j = MC->j % NCols;

                                        if (MC->j == 0) {
                                            MC->i++;
                                            MC->i = MC->i % NRows;
                                        }

                                        return true;
                                    }};
                        } else {
                            fDecode = decltype(fDecode){
                                    [](pb_istream_t *stream, const pb_field_t *field, void **arg) -> bool {
                                        auto MC = (MatrixCounter *) ((NanopbArg *) *arg)->data;
                                        auto M = (Eigen::Matrix<TScalar, NRows, NCols, NOptions> *) MC->M;
                                        double value = 0;

                                        if (!pb_decode_fixed64(stream, &value))
                                            return false;

                                        (*M)(MC->i, MC->j) = value;

                                        MC->i++;
                                        MC->i = MC->i % NRows;

                                        if (MC->i == 0) {
                                            MC->j++;
                                            MC->j = MC->j % NCols;
                                        }

                                        return true;
                                    }};
                        }
                    } else {
                        fDecode = decltype(fDecode){
                                [](pb_istream_t *stream, const pb_field_t *field, void **arg) -> bool {
                                    auto MC = (MatrixCounter *) ((NanopbArg *) *arg)->data;
                                    auto M = (Eigen::Matrix<TScalar, NRows, NCols, NOptions> *) MC->M;
                                    double value;

                                    if (!pb_decode_fixed64(stream, &value))
                                        return false;

                                    (*M)(MC->i, MC->j) = value;

                                    MC->i++;
                                    MC->i = MC->i % NRows;

                                    if (MC->i == 0) {
                                        MC->j++;
                                        MC->j = MC->j % NCols;
                                    }

                                    return true;
                                }};
                    }
                }

                if (mHerald.type == ls_proto_Type_float_t) {
                    array = ls_proto_ArrayFloat_init_default;
                    if (mHerald.has_ordering) {
                        if (mHerald.ordering == ls_proto_MatrixOrdering_rowMajor) {
                            fDecode = decltype(fDecode){
                                    [](pb_istream_t *stream, const pb_field_t *field, void **arg) -> bool {
                                        auto MC = (MatrixCounter *) ((NanopbArg *) *arg)->data;
                                        auto M = (Eigen::Matrix<TScalar, NRows, NCols, NOptions> *) MC->M;
                                        float value;

                                        if (!pb_decode_fixed32(stream, &value))
                                            return false;

                                        (*M)(MC->i, MC->j) = value;

                                        MC->j++;
                                        MC->j = MC->j % NCols;

                                        if (MC->j == 0) {
                                            MC->i++;
                                            MC->i = MC->i % NRows;
                                        }

                                        return true;
                                    }};
                        } else {
                            fDecode = decltype(fDecode){
                                    [](pb_istream_t *stream, const pb_field_t *field, void **arg) -> bool {
                                        auto MC = (MatrixCounter *) ((NanopbArg *) *arg)->data;
                                        auto M = (Eigen::Matrix<TScalar, NRows, NCols, NOptions> *) MC->M;
                                        float value;

                                        if (!pb_decode_fixed32(stream, &value))
                                            return false;

                                        (*M)(MC->i, MC->j) = value;

                                        MC->i++;
                                        MC->i = MC->i % NRows;

                                        if (MC->i == 0) {
                                            MC->j++;
                                            MC->j = MC->j % NCols;
                                        }

                                        return true;
                                    }};
                        }
                    } else {
                        fDecode = decltype(fDecode){
                                [](pb_istream_t *stream, const pb_field_t *field, void **arg) -> bool {
                                    auto MC = (MatrixCounter *) ((NanopbArg *) *arg)->data;
                                    auto M = (Eigen::Matrix<TScalar, NRows, NCols, NOptions> *) MC->M;
                                    float value;

                                    if (!pb_decode_fixed32(stream, &value))
                                        return false;

                                    (*M)(MC->i, MC->j) = value;

                                    MC->i++;
                                    MC->i = MC->i % NRows;

                                    if (MC->i == 0) {
                                        MC->j++;
                                        MC->j = MC->j % NCols;
                                    }

                                    return true;
                                }};
                    }
                }

                nArg.fDecode = &fDecode;

                array.values.funcs.decode = &decode_nanopb;
                array.values.arg = (void *) &nArg;

                return array;
            }

            static bool encode(const Eigen::Matrix<TScalar, NRows, NCols, NOptions> &M, const MsgInfo &info, pb_ostream_t &stream)
            {
                static auto herald = makeHerald();
                static auto subHerald = makeSubHerald();
                static auto msgArg = new ls::io::NanopbArg{};
                static auto msg = makeEncodingMessage(M, *msgArg, subHerald);

                herald.blockId = info.id;
                herald.slotId = info.slot;
                herald.msgType = info.type;
                if (info.encrypted) {
                    herald.has_sign = true;
                }

                msgArg->dataConst = &M;

                return pb_encode_delimited(&stream, ls_proto_Herald_fields, &herald) &&
                       pb_encode_delimited(&stream, ls_proto_MatrixHerald_fields, &subHerald) &&
                       pb_encode_delimited(&stream, ls_proto_ArrayDouble_fields, &msg);
            }

            static bool decode(Eigen::Matrix<TScalar, NRows, NCols, NOptions> &M, MsgInfo &info, pb_istream_t &stream)
            {
                static auto heraldRecv = makeHerald();
                static auto subHeraldRecv = makeSubHerald();
                static auto msgArgRecv = new ls::io::NanopbArg{};
                MatrixCounter MC;
                static auto msgRecv = makeDecodingMessage(M, *msgArgRecv, MC, subHeraldRecv);

                auto heraldRes = pb_decode_delimited(&stream, ls_proto_Herald_fields, &heraldRecv);

                info.id = heraldRecv.blockId;
                info.slot = heraldRecv.slotId;
                info.type = heraldRecv.msgType;
                if (heraldRecv.has_sign) {
                    info.encrypted = true;
                }

                return heraldRes &&
                       pb_decode_delimited(&stream, ls_proto_MatrixHerald_fields, &subHeraldRecv) &&
                       pb_decode_delimited(&stream, ls_proto_ArrayDouble_fields, &msgRecv);
            }

            enum {
                kMessageSize = ls_proto_Herald_size + ls_proto_MatrixHerald_size + NRows * NCols * sizeof(TScalar) + 50
            };
        };

        template<typename TScalar, int NRows>
        struct NanopbWrapper<Eigen::Vector<TScalar, NRows>> {
            static_assert((NRows >= 0), "Vector must be of fixed size.");
            static_assert(NanopbWrapper<TScalar>::hasArrayType, "An array message must be defined for this type.");

            enum {
                pbType = ls_proto_Type_vector_t
            };

            enum {
                hasArrayType = false
            };

            using heraldType = ls_proto_Herald;
            using subHeraldType = ls_proto_VectorHerald;
            using msgType = typename NanopbWrapper<TScalar>::arrayType;

            static ls_proto_Herald makeHerald()
            {
                ls_proto_Herald herald = ls_proto_Herald_init_default;
                herald.msgType = static_cast<ls_proto_Type>(pbType);

                return herald;
            }

            static ls_proto_VectorHerald makeSubHerald()
            {
                ls_proto_VectorHerald vectorHerald = ls_proto_VectorHerald_init_default;

                vectorHerald.type = static_cast<ls_proto_Type>(NanopbWrapper<TScalar>::pbType);
                vectorHerald.size = NRows;
                vectorHerald.has_vectorType = false;

                return vectorHerald;
            }

            static auto makeEncodingMessage(const Eigen::Vector<TScalar, NRows> &v, NanopbArg &nArg,
                                            const ls_proto_VectorHerald &mHerald) -> typename NanopbWrapper<TScalar>::arrayType
            {
                typename NanopbWrapper<TScalar>::arrayType array;

                nArg.dataConst = &v;
                static ::std::function<bool(pb_ostream_t *, const pb_field_t *, void *const *)> fEncode;

                if (mHerald.type == ls_proto_Type_double_t) {
                    array = ls_proto_ArrayDouble_init_default;
                    fEncode = decltype(fEncode){
                            [](pb_ostream_t *stream, const pb_field_t *field, void *const *arg) -> bool {
                                auto mArg = (NanopbArg *) *arg;
                                auto v = (const Eigen::Vector<TScalar, NRows> *) mArg->dataConst;
                                double value;
                                for (int i = 0; i < NRows; i++) {
                                    if (!pb_encode_tag_for_field(stream, field))
                                        return false;

                                    value = (*v)[i];

                                    if (!pb_encode_fixed64(stream, &value))
                                        return false;
                                }

                                return true;
                            }};
                }

                if (mHerald.type == ls_proto_Type_float_t) {
                    array = ls_proto_ArrayFloat_init_default;
                    fEncode = decltype(fEncode){
                            [](pb_ostream_t *stream, const pb_field_t *field, void *const *arg) -> bool {
                                auto mArg = (NanopbArg *) *arg;
                                auto v = (const Eigen::Vector<TScalar, NRows> *) mArg->dataConst;
                                float value;
                                for (int i = 0; i < NRows; i++) {
                                    if (!pb_encode_tag_for_field(stream, field))
                                        return false;

                                    value = (*v)[i];

                                    if (!pb_encode_fixed32(stream, &value))
                                        return false;
                                }

                                return true;
                            }};
                }

                nArg.fEncode = &fEncode;

                array.values.funcs.encode = &encode_nanopb;
                array.values.arg = (void *) &nArg;
                array.size = NRows;

                return array;
            }

            struct VectorCounter {
                void *v;
                int i;
            };

            static auto makeDecodingMessage(Eigen::Vector<TScalar, NRows> &v, NanopbArg &nArg, VectorCounter &vC,
                                            const ls_proto_VectorHerald &vHerald) -> typename NanopbWrapper<TScalar>::arrayType
            {
                typename NanopbWrapper<TScalar>::arrayType array;
                array.size = NRows;

//                auto vC = new VectorCounter{};
//                vC->v = &v;
//                vC->i = 0;

                vC.v = &v;
                vC.i = 0;

                nArg.data = &vC;
                static ::std::function<bool(pb_istream_t *, const pb_field_t *, void **)> fDecode;

                if (vHerald.type == ls_proto_Type_double_t) {
                    array = ls_proto_ArrayDouble_init_default;

                    fDecode = decltype(fDecode){[](pb_istream_t *stream, const pb_field_t *field, void **arg) -> bool {
                        auto vC = (VectorCounter *) ((NanopbArg *) *arg)->data;
                        auto v = (Eigen::Vector<TScalar, NRows> *) vC->v;
                        double value = 0;

                        if (!pb_decode_fixed64(stream, &value))
                            return false;

                        (*v)[vC->i] = value;

                        vC->i++;
                        vC->i = vC->i % NRows;

                        return true;
                    }};
                }

                if (vHerald.type == ls_proto_Type_float_t) {
                    array = ls_proto_ArrayFloat_init_default;
                    fDecode = decltype(fDecode){[](pb_istream_t *stream, const pb_field_t *field, void **arg) -> bool {
                        auto vC = (VectorCounter *) ((NanopbArg *) *arg)->data;
                        auto v = (Eigen::Vector<TScalar, NRows> *) vC->v;
                        float value;

                        if (!pb_decode_fixed32(stream, &value))
                            return false;

                        (*v)[vC->i] = value;

                        vC->i++;
                        vC->i = vC->i % NRows;

                        return true;
                    }};
                }

                nArg.fDecode = &fDecode;

                array.values.funcs.decode = &decode_nanopb;
                array.values.arg = (void *) &nArg;

                return array;
            }

            static bool encode(const Eigen::Vector<TScalar, NRows> &v, const MsgInfo &info, pb_ostream_t &stream)
            {
                static auto herald = makeHerald();
                static auto subHerald = makeSubHerald();
                static auto msgArg = new ls::io::NanopbArg{};
                static auto msg = makeEncodingMessage(v, *msgArg, subHerald);

                herald.blockId = info.id;
                herald.slotId = info.slot;
                herald.msgType = info.type;
                if (info.encrypted) {
                    herald.has_sign = true;
                }

                msgArg->dataConst = &v;

                return pb_encode_delimited(&stream, ls_proto_Herald_fields, &herald) &&
                       pb_encode_delimited(&stream, ls_proto_VectorHerald_fields, &subHerald) &&
                       pb_encode_delimited(&stream, ls_proto_ArrayDouble_fields, &msg);
            }

            static bool decode(Eigen::Vector<TScalar, NRows> &v, MsgInfo &info, pb_istream_t &stream)
            {
                static auto heraldRecv = makeHerald();
                static auto subHeraldRecv = makeSubHerald();
                static auto msgArgRecv = new ls::io::NanopbArg{};
                VectorCounter vc;
                static auto msgRecv = makeDecodingMessage(v, *msgArgRecv, vc, subHeraldRecv);

                auto heraldRes = pb_decode_delimited(&stream, ls_proto_Herald_fields, &heraldRecv);

                info.id = heraldRecv.blockId;
                info.slot = heraldRecv.slotId;
                info.type = heraldRecv.msgType;
                if (heraldRecv.has_sign) {
                    info.encrypted = true;
                }

                return heraldRes &&
                       pb_decode_delimited(&stream, ls_proto_VectorHerald_fields, &subHeraldRecv) &&
                       pb_decode_delimited(&stream, ls_proto_ArrayDouble_fields, &msgRecv);
            }

            enum {
                kMessageSize = ls_proto_Herald_size + ls_proto_VectorHerald_size + NRows * sizeof(TScalar) + 50
            };
        };
    }
}


#endif //LODESTAR_NANOPBWRAPPER_HPP
