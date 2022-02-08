//
// Created by Hamza El-Kebir on 2/6/22.
//

#include "SymbolicCodegen.hpp"

ers::Codegen &SymbolicCodegen::declareEigenMatrix(ers::Codegen &cg, unsigned int rows, unsigned int cols, const ::std::string& name, const ::std::string& type, bool isStatic)
{
    ::std::stringstream ss;
    if (isStatic)
        ss << "static ";

    ss << fmt::format("Eigen::Matrix<{}, {}, {}> ", type, rows, cols);
    ss << name << ";";

    return cg.appendLine(ss.str());
}
