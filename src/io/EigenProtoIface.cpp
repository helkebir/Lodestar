//
// Created by Hamza El-Kebir on 4/19/21.
//

#include "EigenProtoIface.hpp"

void ls::io::EigenProtoIface::MatrixXd::generateProto()
{
    clearProto();

    proto->set_rows(matrix->rows());
    proto->set_cols(matrix->cols());

    for (int i = 0; i < matrix->rows(); i++) {
        auto row = matrix->row(i);

        auto protoRow = proto->add_row();
        protoRow->set_size(row.size());

        for (int j = 0; j < row.size(); j++) {
            protoRow->set_coeff(j, row[j]);
        }
    }
}

void ls::io::EigenProtoIface::MatrixXd::clearProto()
{
    proto->clear_rows();
    proto->clear_cols();
    proto->clear_row();
}

void ls::io::EigenProtoIface::VectorXd::generateProto()
{
    clearProto();

    proto->set_size(vector->size());

    for (int j = 0; j < vector->size(); j++) {
        proto->set_coeff(j, vector->operator[](j));
    }
}

void ls::io::EigenProtoIface::VectorXd::clearProto()
{
    proto->clear_size();
    proto->clear_coeff();
}
