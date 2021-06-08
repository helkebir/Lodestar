//
// Created by Hamza El-Kebir on 5/8/21.
//

#include "OrdinaryDifferentialEquation.hpp"

#ifdef LS_USE_GINAC

GiNaC::exmap
ls::symbolic::OrdinaryDifferentialEquation::generateExpressionMap() const
{
    GiNaC::exmap m;

    for (const auto &state : states_)
        m[GiNaC::ex_to<GiNaC::symbol>(state)] = 0;

    for (const auto &input : inputs_)
        m[GiNaC::ex_to<GiNaC::symbol>(input)] = 0;

    m[time_] = 0;

    return m;
}

inline void ls::symbolic::OrdinaryDifferentialEquation::makeSymbolMap()
{
    symbolMap_.clear();

    for (const auto &state : states_) {
        GiNaC::symbol x = GiNaC::ex_to<GiNaC::symbol>(state);
        symbolMap_[x.get_name()] = x;
    }

    for (const auto &input : inputs_) {
        GiNaC::symbol u = GiNaC::ex_to<GiNaC::symbol>(input);
        symbolMap_[u.get_name()] = u;
    }

    symbolMap_[time_.get_name()] = time_;
}

GiNaC::symbol
ls::symbolic::OrdinaryDifferentialEquation::getSymbol(
        const std::string &symbolName) const
{
    GiNaC::relational r;


    return symbolMap_.at(symbolName);
}

GiNaC::exmap
ls::symbolic::OrdinaryDifferentialEquation::generateExpressionMap(
        const std::vector<GiNaC::relational> &relationals) const
{
    GiNaC::exmap m = generateExpressionMap();

    for (const GiNaC::relational &relational : relationals)
        m[GiNaC::ex_to<GiNaC::symbol>(relational.lhs())] = relational.rhs();

    return m;
}

const GiNaC::lst &
ls::symbolic::OrdinaryDifferentialEquation::getFunctions() const
{
    return functions_;
}

void ls::symbolic::OrdinaryDifferentialEquation::setFunctions(
        const GiNaC::lst &functions)
{
    functions_ = functions;
}

const GiNaC::lst &
ls::symbolic::OrdinaryDifferentialEquation::getStates() const
{
    return states_;
}

void ls::symbolic::OrdinaryDifferentialEquation::setStates(
        const GiNaC::lst &states)
{
    states_ = states;

    makeSymbolMap();
}

const GiNaC::lst &
ls::symbolic::OrdinaryDifferentialEquation::getInputs() const
{
    return inputs_;
}

void ls::symbolic::OrdinaryDifferentialEquation::setInputs(
        const GiNaC::lst &inputs)
{
    inputs_ = inputs;

    makeSymbolMap();
}

Eigen::MatrixXd
ls::symbolic::OrdinaryDifferentialEquation::evalf(
        const GiNaC::exmap &m) const
{
    const int n = functions_.nops();

    Eigen::MatrixXd mat = Eigen::MatrixXd::Zero(n, 1);

    int i = 0;
    for (const auto &it : functions_) {
        mat(i, 1) = GiNaC::ex_to<GiNaC::numeric>(
                it.subs(m).evalf()).to_double();
        i++;
    }

    return mat;
}

GiNaC::exmap
ls::symbolic::OrdinaryDifferentialEquation::generateExpressionMap(
        const std::vector<double> &states,
        const std::vector<double> &inputs) const
{
    int n = states.size() > states_.nops() ? states_.nops() : states.size();
    int m = inputs.size() > inputs_.nops() ? inputs_.nops() : inputs.size();

    std::vector<GiNaC::relational> relationals(n + m);

    for (int i = 0; i < n; i++) {
        //        relationals.push_back(GiNaC::relational(exmap[getStateSymbol(i)], states.at(i)));
        relationals.emplace_back(getStateSymbol(i), states.at(i));
    }

    for (int i = 0; i < m; i++) {
        //        relationals.push_back(GiNaC::relational(exmap[getInputSymbol(i)], states.at(i)));
        relationals.emplace_back(getInputSymbol(i), inputs.at(i));
    }

    return generateExpressionMap(relationals);
}

GiNaC::exmap
ls::symbolic::OrdinaryDifferentialEquation::generateExpressionMap(
        const double t, const std::vector<double> &states,
        const std::vector<double> &inputs) const
{
    GiNaC::exmap exmap = generateExpressionMap(states, inputs);
    exmap[getTimeSymbol()] = t;

    return exmap;
}

GiNaC::symbol ls::symbolic::OrdinaryDifferentialEquation::getStateSymbol(
        const unsigned int i) const
{
    return GiNaC::ex_to<GiNaC::symbol>(states_.op(i));
}

GiNaC::symbol ls::symbolic::OrdinaryDifferentialEquation::getInputSymbol(
        const unsigned int i) const
{
    return GiNaC::ex_to<GiNaC::symbol>(inputs_.op(i));
}

GiNaC::symbol
ls::symbolic::OrdinaryDifferentialEquation::getTimeSymbol() const
{
    return time_;
}

Eigen::MatrixXd ls::symbolic::OrdinaryDifferentialEquation::evalf(
        const std::vector<double> &states,
        const std::vector<double> &inputs) const
{
    GiNaC::exmap exmap = generateExpressionMap(states, inputs);

    return evalf(exmap);
}

Eigen::MatrixXd
ls::symbolic::OrdinaryDifferentialEquation::evalf(const double t,
                                                  const std::vector<double> &states,
                                                  const std::vector<double> &inputs) const
{
    GiNaC::exmap exmap = generateExpressionMap(t, states, inputs);

    return evalf(exmap);
}

GiNaC::matrix
ls::symbolic::OrdinaryDifferentialEquation::generateJacobian(
        const GiNaC::lst &variables) const
{
    GiNaC::lst cols{};
    for (const auto &variable : variables)
        cols.append(functions_.diff(GiNaC::ex_to<GiNaC::symbol>(variable)));

    GiNaC::matrix mat = GiNaC::ex_to<GiNaC::matrix>(GiNaC::lst_to_matrix(cols));

    return mat.transpose();
}

GiNaC::matrix
ls::symbolic::OrdinaryDifferentialEquation::generateJacobianStates() const
{
    return generateJacobian(states_);
}

GiNaC::matrix
ls::symbolic::OrdinaryDifferentialEquation::generateJacobianInputs() const
{
    return generateJacobian(inputs_);
}

Eigen::MatrixXd
ls::symbolic::OrdinaryDifferentialEquation::generateJacobianMatrix(
        const GiNaC::lst &variables, const GiNaC::exmap &exmap) const
{
    return matrixToMatrixXd(generateJacobian(variables).subs(exmap));
}

Eigen::MatrixXd
ls::symbolic::OrdinaryDifferentialEquation::matrixToMatrixXd(
        const GiNaC::matrix &mat)
{
    int n = mat.rows(), m = mat.cols();
    auto emat = Eigen::MatrixXd(n, m);
    emat.setZero();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            emat.coeffRef(i, j) = GiNaC::ex_to<GiNaC::numeric>(
                    mat(i, j).evalf()).to_double();
        }
    }

    return emat;
}

Eigen::MatrixXd
ls::symbolic::OrdinaryDifferentialEquation::matrixToMatrixXd(
        const GiNaC::ex &ex)
{
    GiNaC::matrix mat = GiNaC::ex_to<GiNaC::matrix>(ex);

    return matrixToMatrixXd(mat);
}

Eigen::MatrixXd
ls::symbolic::OrdinaryDifferentialEquation::generateJacobianMatrixStates(
        const GiNaC::exmap &exmap) const
{
    return matrixToMatrixXd(generateJacobianStates().subs(exmap));;
}

Eigen::MatrixXd
ls::symbolic::OrdinaryDifferentialEquation::generateJacobianMatrixInputs(
        const GiNaC::exmap &exmap) const
{
    return matrixToMatrixXd(generateJacobianInputs().subs(exmap));;
}

Eigen::MatrixXd
ls::symbolic::OrdinaryDifferentialEquation::generateJacobianMatrix(
        const GiNaC::matrix &jacobian, const GiNaC::exmap &exmap) const
{
    return matrixToMatrixXd(jacobian.subs(exmap));
}

ls::systems::StateSpace<> ls::symbolic::OrdinaryDifferentialEquation::linearize(
        const GiNaC::exmap &exmap) const
{
    auto A = generateJacobianMatrixStates(exmap);
    auto B = generateJacobianMatrixInputs(exmap);
    Eigen::MatrixXd C = Eigen::MatrixXd::Identity(A.rows(), A.rows());
    Eigen::MatrixXd D = Eigen::MatrixXd::Zero(A.rows(), B.rows());

    return ls::systems::StateSpace<>(A, B, C, D);
}

ls::systems::StateSpace<>
ls::symbolic::OrdinaryDifferentialEquation::linearize(
        const std::vector<double> &states,
        const std::vector<double> &inputs) const
{
    GiNaC::exmap exmap = generateExpressionMap(states, inputs);
    return linearize(exmap);
}

ls::systems::StateSpace<>
ls::symbolic::OrdinaryDifferentialEquation::linearize(
        const double t,
        const std::vector<double> &states,
        const std::vector<double> &inputs) const
{
    GiNaC::exmap exmap = generateExpressionMap(t, states, inputs);
    return linearize(exmap);
}

ls::systems::StateSpace<> ls::symbolic::OrdinaryDifferentialEquation::linearize(
        const GiNaC::matrix &jacobianStates,
        const GiNaC::matrix &jacobianInputs, const GiNaC::exmap &exmap) const
{
    Eigen::MatrixXd A = generateJacobianMatrix(jacobianStates, exmap);
    Eigen::MatrixXd B = generateJacobianMatrix(jacobianInputs, exmap);
    Eigen::MatrixXd C = Eigen::MatrixXd::Identity(A.rows(), A.rows());
    Eigen::MatrixXd D = Eigen::MatrixXd::Zero(A.rows(), B.rows());

    return ls::systems::StateSpace<>(A, B, C, D);
}

ls::systems::StateSpace<> ls::symbolic::OrdinaryDifferentialEquation::linearize(
        const GiNaC::matrix &jacobianStates,
        const GiNaC::matrix &jacobianInputs, const std::vector<double> &states,
        const std::vector<double> &inputs) const
{
    GiNaC::exmap exmap = generateExpressionMap(states, inputs);
    return linearize(jacobianStates, jacobianInputs, exmap);
}

ls::systems::StateSpace<> ls::symbolic::OrdinaryDifferentialEquation::linearize(
        const GiNaC::matrix &jacobianStates,
        const GiNaC::matrix &jacobianInputs, const double t,
        const std::vector<double> &states,
        const std::vector<double> &inputs) const
{
    GiNaC::exmap exmap = generateExpressionMap(t, states, inputs);
    return linearize(jacobianStates, jacobianInputs, exmap);
}

std::string ls::symbolic::OrdinaryDifferentialEquation::generateJacobianStatesCppFunc(const std::string &functionName, const bool dynamicType) const
{
    return generateMatrixCppFunc(generateJacobianStates(), functionName, dynamicType);
}

std::string ls::symbolic::OrdinaryDifferentialEquation::generateJacobianInputsCppFunc(const std::string &functionName,
                                                                                      const bool dynamicType) const
{
    return generateMatrixCppFunc(generateJacobianInputs(), functionName, dynamicType);
}

std::string ls::symbolic::OrdinaryDifferentialEquation::generateMatrixCppFunc(const GiNaC::matrix &ginacMatrix, const std::string &functionName, const bool dynamicType) const
{
    std::string cppFunc;

    std::deque<std::string> argSymbols;
    for (const auto &x: states_)
        argSymbols.push_back(GiNaC::ex_to<GiNaC::symbol>(x).get_name());

    for (const auto &u: inputs_)
        argSymbols.push_back(GiNaC::ex_to<GiNaC::symbol>(u).get_name());

    argSymbols.push_back(GiNaC::ex_to<GiNaC::symbol>(time_).get_name());

    // Generate function argument list with const-qualified doubles.
    std::string argList, rawArgList;
    argList += "const double " + argSymbols.front();
    argSymbols.pop_front();

    while (!argSymbols.empty()) {
        argList += " = 0, const double " + argSymbols.front();
        argSymbols.pop_front();
    }

    argList += " = 0";

    std::string matrixType;
    std::string matrixArgs;
    std::stringstream matrixStream;
    matrixStream << GiNaC::csrc;

    const unsigned int n = ginacMatrix.rows();
    const unsigned int m = ginacMatrix.cols();

    // Populate matrix arguments in human-readable format (i.e., with line breaks).
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < m; j++) {
            if ((i == n-1) && (j == m-1))
                matrixStream << ginacMatrix(i, j) << ";";
            else
                matrixStream << ginacMatrix(i, j) << ", ";
        }

        if (i == n - 1)
            matrixStream << "\n";
        else
            matrixStream << "\n           ";
    }

    matrixArgs = matrixStream.str();

    if (dynamicType)
        matrixType = "Eigen::MatrixXd";
    else
        matrixType = "Eigen::Matrix<double, " + std::to_string(n) + ", " + std::to_string(m) + ">";

    cppFunc += "// Function automatically generated by Lodestar\n";
    cppFunc += matrixType + " " + functionName + "(" + argList + ") {\n";
    cppFunc += "    " + matrixType + " mat" + (dynamicType ? "(" + std::to_string(n) + ", " + std::to_string(m) + ")" : "") + ";\n";
    cppFunc += "    mat << " + matrixArgs + "\n";
    cppFunc += "    return mat;\n";
    cppFunc += "}\n";

    return cppFunc;
}

std::string
ls::symbolic::OrdinaryDifferentialEquation::generateMatrixArrayInputCppFunc(const GiNaC::matrix &ginacMatrix,
                                                                            const std::string &functionName,
                                                                            const bool dynamicType) const
{
    std::string cppFunc;

    const unsigned int n = ginacMatrix.rows();
    const unsigned int m = ginacMatrix.cols();

    // Generate function argument list with const-qualified double arrays.
    std::string argList = "const double (&x)[" + std::to_string(states_.nops()) + "], const double (&u)[" + std::to_string(inputs_.nops()) + "], const double t = 0";

    std::string matrixType;
    std::string matrixArgs;
    std::stringstream matrixStream;
    matrixStream << GiNaC::csrc;

    // Populate matrix arguments in human-readable format (i.e., with line breaks).
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < m; j++) {
            if ((i == n-1) && (j == m-1))
                matrixStream << ginacMatrix(i, j) << ";";
            else
                matrixStream << ginacMatrix(i, j) << ", ";
        }

        if (i == n - 1)
            matrixStream << "\n";
        else
            matrixStream << "\n           ";
    }

    std::string symbName;
    std::string docString = "/**\n";
    docString += " * @param x State array:\n";
    if (states_.nops() > 0)
        docString += " *     " + GiNaC::ex_to<GiNaC::symbol>(states_[0]).get_name();

    // Replace symbols by array elements.
    matrixArgs = matrixStream.str();
    std::string src, dest;
    unsigned int i = 0;
    for (const auto &x: states_) {
        src = GiNaC::ex_to<GiNaC::symbol>(x).get_name();
        if (i > 0)
            docString += ", " + src;

        dest = "__STATES__[" + std::to_string(i) + "]";
        replaceStringAll(matrixArgs, src, dest);

        i++;
    }

    docString += '\n';
    docString += " * @param u Input array:\n";
    if (inputs_.nops() > 0)
        docString += " *     " + GiNaC::ex_to<GiNaC::symbol>(inputs_[0]).get_name();

    i = 0;
    for (const auto &u: inputs_) {
        src = GiNaC::ex_to<GiNaC::symbol>(u).get_name();
        if (i > 0)
            docString += ", " + src;

        dest = "__INPUTS__[" + std::to_string(i) + "]";
        replaceStringAll(matrixArgs, src, dest);

        i++;
    }

    docString += '\n';
    docString += " * @param t Time.\n\n";
    docString += " * @return Jacobian matrix.\n";
    docString += " */\n";
    {
        src = GiNaC::ex_to<GiNaC::symbol>(time_).get_name();
        dest = "__TIME__";
        replaceStringAll(matrixArgs, src, dest);
    }

    // Replace all-caps with more compact symbols.
    {
        src = "__STATES__";
        dest = "x";
        replaceStringAll(matrixArgs, src, dest);
    }

    {
        src = "__INPUTS__";
        dest = "u";
        replaceStringAll(matrixArgs, src, dest);
    }

    {
        src = "__TIME__";
        dest = "t";
        replaceStringAll(matrixArgs, src, dest);
    }


    if (dynamicType)
        matrixType = "Eigen::MatrixXd";
    else
        matrixType = "Eigen::Matrix<double, " + std::to_string(n) + ", " + std::to_string(m) + ">";

    cppFunc += docString;
    cppFunc += "// Function automatically generated by Lodestar\n";
    cppFunc += matrixType + " " + functionName + "(" + argList + ") {\n";
    cppFunc += "    " + matrixType + " mat" + (dynamicType ? "(" + std::to_string(n) + ", " + std::to_string(m) + ")" : "") + ";\n";
    cppFunc += "    mat << " + matrixArgs + "\n";
    cppFunc += "    return mat;\n";
    cppFunc += "}\n";

    return cppFunc;
}

std::string
ls::symbolic::OrdinaryDifferentialEquation::generateJacobianStatesArrayInputCppFunc(const std::string &functionName,
                                                                                    const bool dynamicType) const
{
    return generateMatrixArrayInputCppFunc(generateJacobianStates(), functionName, dynamicType);
}

std::string
ls::symbolic::OrdinaryDifferentialEquation::generateJacobianInputsArrayInputCppFunc(const std::string &functionName,
                                                                                    const bool dynamicType) const
{
    return generateMatrixArrayInputCppFunc(generateJacobianInputs(), functionName, dynamicType);
}

inline void ls::symbolic::OrdinaryDifferentialEquation::replaceString(std::string &str, const std::string &source, const std::string &dest)
{
    size_t start = str.find(source);
    if(start == std::string::npos)
        return;

    str.replace(start, source.length(), dest);
}

inline void ls::symbolic::OrdinaryDifferentialEquation::replaceStringAll(std::string &str, const std::string &source, const std::string &dest)
{
    if (source.empty())
        return;

    std::size_t start = 0;
    while((start = str.find(source, start)) != std::string::npos) {
        str.replace(start, source.length(), dest);
        start += dest.length();
    }
}

std::string ls::symbolic::OrdinaryDifferentialEquation::stripWhiteSpace(std::string &str)
{
    std::string res = str;

    // Forward pass
    for (std::size_t i = 0; i < res.size(); i++) {
        if (res[i] == ' ')
            replaceString(res, " ", "");
        else
            break;
    }

    // Backward pass
    std::size_t start = res.size();
    while (res[start] == ' ')
        start--;


    for (std::size_t i = start; i < res.size(); i++) {
        if (res[i] == ' ')
            replaceString(res, " ", "");
        else
            break;
    }

    return res;
}

#endif