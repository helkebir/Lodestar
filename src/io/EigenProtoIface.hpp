//
// Created by Hamza El-Kebir on 4/19/21.
//

#ifndef LODESTAR_EIGENPROTOIFACE_HPP
#define LODESTAR_EIGENPROTOIFACE_HPP

#include "Eigen/Dense"

#include "ProtoIfaceABC.hpp"
#include "proto/ls.proto.eigen.pb.h"

namespace ls { namespace io {
    class EigenProtoIface {
    public:
        class MatrixXd : public ProtoIfaceABC {
        public:
            MatrixXd() : proto(new proto::eigen::MatrixXd)
            {}

            MatrixXd(Eigen::MatrixXd *mat) : proto(new proto::eigen::MatrixXd),
                                             matrix(mat)
            {}

            MatrixXd(proto::eigen::MatrixXd *prot) : proto(prot)
            {}

            MatrixXd(proto::eigen::MatrixXd *prot, Eigen::MatrixXd *mat)
                    : proto(prot),
                      matrix(mat)
            {}

            void generateProto();

            void clearProto();

            Eigen::MatrixXd *matrix;
            proto::eigen::MatrixXd *proto;
        };

        class VectorXd {
        public:
            VectorXd() : proto(new proto::eigen::VectorXd)
            {}

            VectorXd(Eigen::VectorXd *vec) : proto(new proto::eigen::VectorXd),
                                             vector(vec)
            {}

            VectorXd(proto::eigen::VectorXd *prot) : proto(prot)
            {}

            VectorXd(proto::eigen::VectorXd *prot, Eigen::VectorXd *vec)
                    : proto(prot),
                      vector(vec)
            {}

            void generateProto();

            void clearProto();

            Eigen::VectorXd *vector;
            proto::eigen::VectorXd *proto;
        };
    };
} }


#endif //LODESTAR_EIGENPROTOIFACE_HPP
