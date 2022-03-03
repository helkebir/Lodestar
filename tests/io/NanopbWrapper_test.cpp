//
// Created by Hamza El-Kebir on 2/12/22.
//

#include "catchOnce.hpp"
#include <Lodestar/io/NanopbWrapper.hpp>
#include <cstdint>

TEST_CASE("NanopbWrapper Matrix", "[io][proto]")
{
    ::std::uint8_t buffer[1024];

    pb_ostream_t stream;
    stream = pb_ostream_from_buffer(buffer, 1024);

    Eigen::Matrix<double, 3, 2> M, N;
    M << 1, 2,
         3, 4,
         5, 6;

    N.setZero();

    // Encode

    auto herald = ls::io::NanopbWrapper<decltype(M)>::makeHerald();
    auto subHerald = ls::io::NanopbWrapper<decltype(M)>::makeSubHerald();
    auto msgArg = ls::io::NanopbArg{};
    auto msg = ls::io::NanopbWrapper<decltype(M)>::makeEncodingMessage(M, msgArg, subHerald);

    REQUIRE(subHerald.type == ls_proto_Type_double_t);

    REQUIRE(pb_encode_delimited(&stream, ls_proto_Herald_fields, &herald));
    REQUIRE(pb_encode_delimited(&stream, ls_proto_MatrixHerald_fields, &subHerald));
    REQUIRE(pb_encode_delimited(&stream, ls_proto_ArrayDouble_fields, &msg));

    // Decode

    auto heraldRecv = ls::io::NanopbWrapper<decltype(N)>::makeHerald();
    auto subHeraldRecv = ls::io::NanopbWrapper<decltype(N)>::makeSubHerald();
    auto msgArgRecv = ls::io::NanopbArg{};
    ls::io::NanopbWrapper<decltype(N)>::MatrixCounter MC{};
    auto msgRecv = ls::io::NanopbWrapper<decltype(N)>::makeDecodingMessage(N, msgArgRecv, MC, subHeraldRecv);

    pb_istream_t istream = pb_istream_from_buffer(buffer, sizeof(buffer));

    REQUIRE(pb_decode_delimited(&istream, ls_proto_Herald_fields, &heraldRecv));
    REQUIRE(pb_decode_delimited(&istream, ls_proto_MatrixHerald_fields, &subHeraldRecv));
    REQUIRE(pb_decode_delimited(&istream, ls_proto_ArrayDouble_fields, &msgRecv));

    REQUIRE(heraldRecv.msgType == ls::io::NanopbWrapper<decltype(N)>::pbType);

    REQUIRE(subHeraldRecv.type == ls::io::NanopbWrapper<double>::pbType);
    REQUIRE(subHeraldRecv.rows == 3);
    REQUIRE(subHeraldRecv.cols == 2);
    REQUIRE(subHeraldRecv.has_ordering);
    REQUIRE(subHeraldRecv.ordering == ls_proto_MatrixOrdering_colMajor);

    REQUIRE(msgRecv.size == 3*2);
    REQUIRE((N - M).isZero(1e-5));
}

TEST_CASE("NanopbWrapper Matrix shorthand", "[io][proto]")
{

    Eigen::Matrix<double, 3, 2> M, N;
    M << 1, 2,
            3, 4,
            5, 6;

    ::std::uint8_t buffer[ls::io::NanopbWrapper<decltype(M)>::kMessageSize];

    pb_ostream_t stream;
    stream = pb_ostream_from_buffer(buffer, ls::io::NanopbWrapper<decltype(M)>::kMessageSize);

    N.setZero();

    ls::io::MsgInfo info;
    info.id = 5;
    info.slot = 1;

    // Encode

    ls::io::NanopbWrapper<decltype(M)>::encode(M, info, stream);

    // Decode

    pb_istream_t istream = pb_istream_from_buffer(buffer, sizeof(buffer));

    ls::io::NanopbWrapper<decltype(N)>::decode(N, info, istream);

    REQUIRE((N - M).isZero(1e-5));
    REQUIRE(info.id == 5);
    REQUIRE(info.slot == 1);
}

TEST_CASE("NanopbWrapper Vector", "[io][proto]")
{
    Eigen::Vector<double, 12> M, N;
    M << 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2;

    ::std::uint8_t buffer[ls::io::NanopbWrapper<decltype(M)>::kMessageSize];

    pb_ostream_t stream;
    stream = pb_ostream_from_buffer(buffer, ls::io::NanopbWrapper<decltype(M)>::kMessageSize);

    N.setZero();

    // Encode

    auto herald = ls::io::NanopbWrapper<decltype(M)>::makeHerald();
    auto subHerald = ls::io::NanopbWrapper<decltype(M)>::makeSubHerald();
    auto msgArg = ls::io::NanopbArg{};
    auto msg = ls::io::NanopbWrapper<decltype(M)>::makeEncodingMessage(M, msgArg, subHerald);

    REQUIRE(subHerald.type == ls_proto_Type_double_t);

    REQUIRE(pb_encode_delimited(&stream, ls_proto_Herald_fields, &herald));
    REQUIRE(pb_encode_delimited(&stream, ls_proto_VectorHerald_fields, &subHerald));
    REQUIRE(pb_encode_delimited(&stream, ls_proto_ArrayDouble_fields, &msg));

    // Decode

    auto heraldRecv = ls::io::NanopbWrapper<decltype(N)>::makeHerald();
    auto subHeraldRecv = ls::io::NanopbWrapper<decltype(N)>::makeSubHerald();
    auto msgArgRecv = ls::io::NanopbArg{};
    ls::io::NanopbWrapper<decltype(N)>::VectorCounter vC{};
    auto msgRecv = ls::io::NanopbWrapper<decltype(N)>::makeDecodingMessage(N, msgArgRecv, vC, subHeraldRecv);

    pb_istream_t istream = pb_istream_from_buffer(buffer, sizeof(buffer));

    REQUIRE(pb_decode_delimited(&istream, ls_proto_Herald_fields, &heraldRecv));
    REQUIRE(pb_decode_delimited(&istream, ls_proto_VectorHerald_fields, &subHeraldRecv));
    REQUIRE(pb_decode_delimited(&istream, ls_proto_ArrayDouble_fields, &msgRecv));

    REQUIRE(heraldRecv.msgType == ls::io::NanopbWrapper<decltype(N)>::pbType);

    REQUIRE(subHeraldRecv.type == ls::io::NanopbWrapper<double>::pbType);
    REQUIRE(subHeraldRecv.size == 12);

    REQUIRE(msgRecv.size == 12);
    REQUIRE((N - M).isZero(1e-5));
}

TEST_CASE("NanopbWrapper Vector shorthand", "[io][proto]")
{
    ::std::uint8_t buffer[1024];

    pb_ostream_t stream;
    stream = pb_ostream_from_buffer(buffer, 1024);

    Eigen::Vector<double, 12> M, N;
    M << 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2;

    N.setZero();

    ls::io::MsgInfo info;
    info.id = 5;
    info.slot = 1;

    // Encode

    ls::io::NanopbWrapper<decltype(M)>::encode(M, info, stream);

    // Decode

    pb_istream_t istream = pb_istream_from_buffer(buffer, sizeof(buffer));

    ls::io::NanopbWrapper<decltype(N)>::decode(N, info, istream);

    REQUIRE((N - M).isZero(1e-5));
    REQUIRE(info.id == 5);
    REQUIRE(info.slot == 1);
    REQUIRE((!info.encrypted));
}

TEST_CASE("NanopbWrapper Vector encryption", "[io][proto]")
{
    hydro_init();

    ::std::uint8_t BUFFER[1024] = {0};

    pb_ostream_t stream;
    stream = pb_ostream_from_buffer(BUFFER, sizeof(BUFFER));

    Eigen::Vector<double, 12> M, N;
    M << 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2;

    N.setZero();

    ls::io::MsgInfo info;
    info.id = 5;
    info.slot = 1;
    info.encrypted = true;
    hydro_secretbox_keygen(info.sign);

    // Encode

    auto resEncode = ls::io::NanopbWrapper<decltype(M)>::encode(M, info, stream);

    // Decode

    pb_istream_t istream = pb_istream_from_buffer(BUFFER, sizeof(BUFFER));

    auto resDecode = ls::io::NanopbWrapper<decltype(N)>::decode(N, info, istream);

    // FIXME: Fix decoding pass.
//
//    REQUIRE(resEncode);
//    REQUIRE(resDecode);
//    REQUIRE((N - M).isZero(1e-5));
    REQUIRE(info.id == 5);
    REQUIRE(info.slot == 1);
    REQUIRE((info.encrypted));
}