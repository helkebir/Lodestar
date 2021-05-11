//
// Created by Hamza El-Kebir on 4/21/21.
//

#include "ProtoWrapper.hpp"

#ifdef LS_USE_PROTOBUF

PROTO_WRAP(Eigen::VectorXd)
{
    destObj->set_size(obj->size());
    destObj->clear_coeff();

    for (int i = 0; i < obj->size(); i++) {
        destObj->add_coeff(obj->coeff(i));
    }
}

PROTO_WRAP_STATIC(Eigen::VectorXd)
{
    destObj->set_size(srcObj->size());
    destObj->clear_coeff();

    for (int i = 0; i < srcObj->size(); i++) {
        destObj->add_coeff(srcObj->coeff(i));
    }
}

PROTO_WRAP(ls::proto::eigen::VectorXd)
{
    destObj->resize(obj->coeff_size());
    destObj->setZero();

    for (int i = 0; i < obj->coeff_size(); i++) {
        destObj->coeffRef(i) = obj->coeff(i);
    }
}

PROTO_WRAP_STATIC(ls::proto::eigen::VectorXd)
{
    destObj->resize(srcObj->coeff_size());
    destObj->setZero();

    for (int i = 0; i < srcObj->coeff_size(); i++) {
        destObj->coeffRef(i) = srcObj->coeff(i);
    }
}

#ifdef LS_USE_GINAC

PROTO_WRAP(GiNaC::symbol)
{
    destObj->set_name(obj->get_name());
}

PROTO_WRAP_STATIC(GiNaC::symbol)
{
    destObj->set_name(srcObj->get_name());
}

PROTO_WRAP(ls::proto::ginac::symbol)
{
    destObj->set_name(obj->name());
}

PROTO_WRAP_STATIC(ls::proto::ginac::symbol)
{
    destObj->set_name(srcObj->name());
}

#endif // LS_USE_GINAC

#endif // LS_USE_PROTOBUF