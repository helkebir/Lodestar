//
// Created by Hamza El-Kebir on 6/13/21.
//

#include "catchOnce.hpp"
#include "Lodestar/io/proto/nano/Herald.pb.h"
#include "Lodestar/io/proto/nano/Vector.pb.h"
#include "pb_encode.h"
#include "pb_decode.h"

#include "Lodestar/io/proto/nano/NanopbWrapper.hpp"

TEST_CASE("Nanopb encode/decode", "[static][nanopb]") {
    uint8_t buffer[256];
    bool status;

    {
        npb_Herald herald = npb_Herald_init_default;
        npb_Vector3d v3d = npb_Vector3d_init_default;

        REQUIRE(herald.type == npb_Unknown_t);
        REQUIRE(v3d.size == 3);

        herald.type = npb_Vector3d_t;

        Eigen::Vector3d vec3d;
        vec3d << 1, 2, 3;
        v3d = NanopbWrapper<Eigen::Vector3d>::wrap(vec3d);

        pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

        status = pb_encode_delimited(&stream, npb_Herald_fields, &herald);
        status = pb_encode_delimited(&stream, npb_Vector3d_fields, &v3d);
//        std::cout << "Bytes written: " << stream.bytes_written << std::endl;

        REQUIRE(status);
    }

    {
        npb_Herald herald = npb_Herald_init_zero;
        npb_Vector3d v3d = npb_Vector3d_init_zero;

        pb_istream_t stream = pb_istream_from_buffer(buffer, sizeof(buffer));

        status = pb_decode_delimited(&stream, npb_Herald_fields, &herald);

        switch (herald.type) {
            case npb_Vector3d_t:
                status = pb_decode_delimited(&stream, npb_Vector3d_fields, &v3d);
                break;
            default:
                status = false;
                break;
        }


//        std::cout << "Bytes read: " << sizeof(buffer) - stream.bytes_left << std::endl;

        REQUIRE(status);

        REQUIRE(herald.type == npb_Vector3d_t);
        REQUIRE(v3d.coeff[0] == 1);
        REQUIRE(v3d.coeff[1] == 2);
        REQUIRE(v3d.coeff[2] == 3);
        REQUIRE(v3d.size == 3);

        auto vec = NanopbWrapper<npb_Vector3d>::unwrap(v3d);

        REQUIRE(vec(0) == 1);
        REQUIRE(vec(1) == 2);
        REQUIRE(vec(2) == 3);

        vec = NanopbWrapper<Eigen::Vector3d>::unwrap(v3d);

        REQUIRE(vec(0) == 1);
        REQUIRE(vec(1) == 2);
        REQUIRE(vec(2) == 3);

        Eigen::Vector3d vec2;
        NanopbWrapper<npb_Vector3d>::unwrap(v3d, vec2);

        REQUIRE(vec2(0) == 1);
        REQUIRE(vec2(1) == 2);
        REQUIRE(vec2(2) == 3);

        Eigen::VectorXd vec3(1);
        NanopbWrapper<npb_Vector3d, false>::unwrap(v3d, vec3);

        REQUIRE(vec3(0) == 1);
        REQUIRE(vec3(1) == 2);
        REQUIRE(vec3(2) == 3);

//        std::cout << "vec3 rows: " << vec3.rows() << std::endl;
    }
}
