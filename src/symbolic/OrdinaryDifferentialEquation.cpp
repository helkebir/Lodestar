//
// Created by Hamza El-Kebir on 5/8/21.
//

#include "OrdinaryDifferentialEquation.hpp"

#ifdef LS_USE_GINAC

GiNaC::exmap
ls::symbolic::OrdinaryDifferentialEquation::generateExpressionMap() const
{
    GiNaC::exmap m;

    for (const auto &state : _states)
        m[GiNaC::ex_to<GiNaC::symbol>(state)] = 0;

    for (const auto &input : _inputs)
        m[GiNaC::ex_to<GiNaC::symbol>(input)] = 0;

    m[_time] = 0;

    return m;
}

inline void ls::symbolic::OrdinaryDifferentialEquation::makeSymbolMap()
{
    _symbolMap.clear();

    for (const auto &state : _states) {
        GiNaC::symbol x = GiNaC::ex_to<GiNaC::symbol>(state);
        _symbolMap[x.get_name()] = x;
    }

    for (const auto &input : _inputs) {
        GiNaC::symbol u = GiNaC::ex_to<GiNaC::symbol>(input);
        _symbolMap[u.get_name()] = u;
    }

    _symbolMap[_time.get_name()] = _time;
}

GiNaC::symbol
ls::symbolic::OrdinaryDifferentialEquation::getSymbol(
        const std::string &symbolName) const
{
    GiNaC::relational r;


    return _symbolMap.at(symbolName);
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
    return _functions;
}

void ls::symbolic::OrdinaryDifferentialEquation::setFunctions(
        const GiNaC::lst &functions)
{
    _functions = functions;
}

const GiNaC::lst &
ls::symbolic::OrdinaryDifferentialEquation::getStates() const
{
    return _states;
}

void ls::symbolic::OrdinaryDifferentialEquation::setStates(
        const GiNaC::lst &states)
{
    _states = states;

    makeSymbolMap();
}

const GiNaC::lst &
ls::symbolic::OrdinaryDifferentialEquation::getInputs() const
{
    return _inputs;
}

void ls::symbolic::OrdinaryDifferentialEquation::setInputs(
        const GiNaC::lst &inputs)
{
    _inputs = inputs;

    makeSymbolMap();
}

Eigen::MatrixXd
ls::symbolic::OrdinaryDifferentialEquation::evalf(
        const GiNaC::exmap &m) const
{
    const int n = _functions.nops();

    Eigen::MatrixXd mat = Eigen::MatrixXd::Zero(n, 1);

    int i = 0;
    for (const auto &it : _functions) {
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
    int n = states.size() > _states.nops() ? _states.nops() : states.size();
    int m = inputs.size() > _inputs.nops() ? _inputs.nops() : inputs.size();

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
    return GiNaC::ex_to<GiNaC::symbol>(_states.op(i));
}

GiNaC::symbol ls::symbolic::OrdinaryDifferentialEquation::getInputSymbol(
        const unsigned int i) const
{
    return GiNaC::ex_to<GiNaC::symbol>(_inputs.op(i));
}

GiNaC::symbol
ls::symbolic::OrdinaryDifferentialEquation::getTimeSymbol() const
{
    return _time;
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
        cols.append(_functions.diff(GiNaC::ex_to<GiNaC::symbol>(variable)));

    GiNaC::matrix mat = GiNaC::ex_to<GiNaC::matrix>(GiNaC::lst_to_matrix(cols));

    return mat.transpose();
}

GiNaC::matrix
ls::symbolic::OrdinaryDifferentialEquation::generateJacobianStates() const
{
    return generateJacobian(_states);
}

GiNaC::matrix
ls::symbolic::OrdinaryDifferentialEquation::generateJacobianInputs() const
{
    return generateJacobian(_inputs);
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

ls::systems::StateSpace ls::symbolic::OrdinaryDifferentialEquation::linearize(
        const GiNaC::exmap &exmap) const
{
    auto A = generateJacobianMatrixStates(exmap);
    auto B = generateJacobianMatrixInputs(exmap);

    return ls::systems::StateSpace(A, B, Eigen::MatrixXd::Identity(A.rows(),
                                                                   A.rows()),
                                   Eigen::MatrixXd::Zero(A.rows(), B.rows()));
}

ls::systems::StateSpace
ls::symbolic::OrdinaryDifferentialEquation::linearize(
        const std::vector<double> &states,
        const std::vector<double> &inputs) const
{
    GiNaC::exmap exmap = generateExpressionMap(states, inputs);
    return linearize(exmap);
}

ls::systems::StateSpace
ls::symbolic::OrdinaryDifferentialEquation::linearize(
        const double t,
        const std::vector<double> &states,
        const std::vector<double> &inputs) const
{
    GiNaC::exmap exmap = generateExpressionMap(t, states, inputs);
    return linearize(exmap);
}

ls::systems::StateSpace ls::symbolic::OrdinaryDifferentialEquation::linearize(
        const GiNaC::matrix &jacobianStates,
        const GiNaC::matrix &jacobianInputs, const GiNaC::exmap &exmap) const
{
    auto A = generateJacobianMatrix(jacobianStates, exmap);
    auto B = generateJacobianMatrix(jacobianInputs, exmap);

    return ls::systems::StateSpace(A, B, Eigen::MatrixXd::Identity(A.rows(),
                                                                   A.rows()),
                                   Eigen::MatrixXd::Zero(A.rows(), B.rows()));
}

ls::systems::StateSpace ls::symbolic::OrdinaryDifferentialEquation::linearize(
        const GiNaC::matrix &jacobianStates,
        const GiNaC::matrix &jacobianInputs, const std::vector<double> &states,
        const std::vector<double> &inputs) const
{
    GiNaC::exmap exmap = generateExpressionMap(states, inputs);
    return linearize(jacobianStates, jacobianInputs, exmap);
}

ls::systems::StateSpace ls::symbolic::OrdinaryDifferentialEquation::linearize(
        const GiNaC::matrix &jacobianStates,
        const GiNaC::matrix &jacobianInputs, const double t,
        const std::vector<double> &states,
        const std::vector<double> &inputs) const
{
    GiNaC::exmap exmap = generateExpressionMap(t, states, inputs);
    return linearize(jacobianStates, jacobianInputs, exmap);
}

#endif