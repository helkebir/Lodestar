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
    destObj->set_size(obj->size());
    destObj->clear_coeff();

    for (int i = 0; i < obj->size(); i++) {
        destObj->add_coeff(obj->coeff(i));
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
    destObj->resize(obj->coeff_size());
    destObj->setZero();

    for (int i = 0; i < obj->coeff_size(); i++) {
        destObj->coeffRef(i) = obj->coeff(i);
    }
}

#ifdef LS_USE_GINAC

PROTO_WRAP(ls::io::GiNaCExPair) {
    // Register objects by name
    for (const auto &symbol : obj->second) {
        auto symbolObj = destObj->add_symbols();
        symbolObj->set_name(GiNaC::ex_to<GiNaC::symbol>(symbol).get_name());
    }

    // Archive expression
    GiNaC::archive archive;
    archive.archive_ex(obj->first, "ex");

    // Serialize archive
    std::ostringstream stream;
    stream << archive;
    destObj->set_archive(stream.str());
}

PROTO_WRAP_STATIC(ls::io::GiNaCExPair) {
    // Register objects by name
    for (const auto &symbol : obj->second) {
        auto symbolObj = destObj->add_symbols();
        symbolObj->set_name(GiNaC::ex_to<GiNaC::symbol>(symbol).get_name());
    }

    // Archive expression
    GiNaC::archive archive;
    archive.archive_ex(obj->first, "ex");

    // Serialize archive
    std::ostringstream stream;
    stream << archive;
    destObj->set_archive(stream.str());
}

PROTO_WRAP(ls::io::ProtoExPair) {
    // Append symbols to symbol list.
    GiNaC::symtab symtab = obj->second;
    GiNaC::lst sym_lst;
    for (const auto &symbol: obj->first.symbols()) {
        std::string symbName = symbol.name();
        if (symtab.find(symbName) == symtab.end())
            symtab.emplace(symbName, GiNaC::symbol(symbName));

        sym_lst.append(symtab[symbName]);
    }

    // Update symbol table
    obj = new std::pair<proto::ginac::ex, GiNaC::symtab>(obj->first, symtab);

    // Load archive
    GiNaC::archive archive;
    std::istringstream stream(obj->first.archive());
    stream >> archive;

    // Unarchive expression
    *destObj = archive.unarchive_ex(sym_lst, 0u);
}

PROTO_WRAP_STATIC(ls::io::ProtoExPair) {
    // Append symbols to symbol list.
    GiNaC::symtab symtab = obj->second;
    GiNaC::lst sym_lst;
    for (const auto &symbol: obj->first.symbols()) {
        std::string symbName = symbol.name();
        if (symtab.find(symbName) == symtab.end())
            symtab.emplace(symbName, GiNaC::symbol(symbName));

        sym_lst.append(symtab[symbName]);
    }

    // Update symbol table
    obj = new std::pair<proto::ginac::ex, GiNaC::symtab>(obj->first, symtab);

    // Load archive
    GiNaC::archive archive;
    std::istringstream stream(obj->first.archive());
    stream >> archive;

    // Unarchive expression
    *destObj = archive.unarchive_ex(sym_lst, 0u);
}

PROTO_WRAP(ls::proto::ginac::ex) {
    // Retrieve symbols.
    GiNaC::lst sym_lst;
    for (const auto &symb : obj->symbols())
        sym_lst.append(GiNaC::symbol(symb.name()));

    GiNaC::archive archive;
    std::istringstream stream(obj->archive());
    stream >> archive;

    *destObj = archive.unarchive_ex(sym_lst, 0u);
}

PROTO_WRAP_STATIC(ls::proto::ginac::ex) {
    // Retrieve symbols.
    GiNaC::lst sym_lst;
    for (const auto &symb : obj->symbols())
        sym_lst.append(GiNaC::symbol(symb.name()));

    GiNaC::archive archive;
    std::istringstream stream(obj->archive());
    stream >> archive;

    *destObj = archive.unarchive_ex(sym_lst, 0u);
}

PROTO_WRAP(GiNaC::symbol)
{
    destObj->set_name(obj->get_name());
}

PROTO_WRAP_STATIC(GiNaC::symbol)
{
    destObj->set_name(obj->get_name());
}

PROTO_WRAP(ls::proto::ginac::symbol)
{
    destObj->set_name(obj->name());
}

PROTO_WRAP_STATIC(ls::proto::ginac::symbol)
{
    destObj->set_name(obj->name());
}

#endif // LS_USE_GINAC

#endif // LS_USE_PROTOBUF