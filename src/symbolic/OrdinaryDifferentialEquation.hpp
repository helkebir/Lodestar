//
// Created by Hamza El-Kebir on 5/8/21.
//

#ifndef LODESTAR_ORDINARYDIFFERENTIALEQUATION_HPP
#define LODESTAR_ORDINARYDIFFERENTIALEQUATION_HPP

#ifdef LS_USE_GINAC

#include "Eigen/Dense"
#include "systems/StateSpace.hpp"
#include "ginac/ginac.h"

namespace ls {
    namespace symbolic {
        class OrdinaryDifferentialEquation {
        public:
            OrdinaryDifferentialEquation() :
                    _functions(GiNaC::lst{GiNaC::ex(0)}),
                    _states(GiNaC::lst{GiNaC::symbol("x")}),
                    _inputs(GiNaC::lst{GiNaC::symbol("u")}),
                    _time(GiNaC::symbol("t"))
            {
                makeSymbolMap();
            }

            OrdinaryDifferentialEquation(const GiNaC::lst &functions,
                                         const GiNaC::lst &states,
                                         const GiNaC::lst &inputs) :
                    _functions(functions),
                    _states(states),
                    _inputs(inputs),
                    _time(GiNaC::symbol("t"))
            {
                makeSymbolMap();
            }

            OrdinaryDifferentialEquation(const GiNaC::lst &functions,
                                         const GiNaC::lst &states,
                                         const GiNaC::lst &inputs,
                                         const GiNaC::symbol &time) :
                    _functions(functions),
                    _states(states),
                    _inputs(inputs),
                    _time(time)
            {
                makeSymbolMap();
            }

            GiNaC::exmap generateExpressionMap() const;

            GiNaC::exmap generateExpressionMap(
                    const std::vector<GiNaC::relational> &relationals) const;

            GiNaC::exmap
            generateExpressionMap(const std::vector<double> &states,
                                  const std::vector<double> &inputs) const;

            GiNaC::exmap generateExpressionMap(double t,
                                               const std::vector<double> &states,
                                               const std::vector<double> &inputs) const;

            GiNaC::symbol getSymbol(const std::string &symbolName) const;

            GiNaC::symbol getStateSymbol(unsigned int i) const;

            GiNaC::symbol getInputSymbol(unsigned int i) const;

            GiNaC::symbol getTimeSymbol() const;

            const GiNaC::lst &getFunctions() const;

            void setFunctions(const GiNaC::lst &functions);

            const GiNaC::lst &getStates() const;

            void setStates(const GiNaC::lst &states);

            const GiNaC::lst &getInputs() const;

            void setInputs(const GiNaC::lst &inputs);

            Eigen::MatrixXd evalf(const GiNaC::exmap &m) const;

            Eigen::MatrixXd evalf(const std::vector<double> &states,
                                  const std::vector<double> &inputs) const;

            Eigen::MatrixXd
            evalf(double t, const std::vector<double> &states,
                  const std::vector<double> &inputs) const;

            GiNaC::matrix generateJacobian(const GiNaC::lst &variables) const;

            GiNaC::matrix generateJacobianStates() const;

            GiNaC::matrix generateJacobianInputs() const;

            Eigen::MatrixXd generateJacobianMatrix(const GiNaC::lst &variables,
                                                   const GiNaC::exmap &exmap) const;

            Eigen::MatrixXd
            generateJacobianMatrix(const GiNaC::matrix &jacobian,
                                   const GiNaC::exmap &exmap) const;

            Eigen::MatrixXd
            generateJacobianMatrixStates(const GiNaC::exmap &exmap) const;

            Eigen::MatrixXd
            generateJacobianMatrixInputs(const GiNaC::exmap &exmap) const;

            systems::StateSpace<> linearize(const GiNaC::exmap &exmap) const;

            systems::StateSpace<> linearize(const std::vector<double> &states,
                                          const std::vector<double> &inputs) const;

            systems::StateSpace<> linearize(double t,
                                          const std::vector<double> &states,
                                          const std::vector<double> &inputs) const;

            systems::StateSpace<> linearize(const GiNaC::matrix &jacobianStates,
                                          const GiNaC::matrix &jacobianInputs,
                                          const GiNaC::exmap &exmap) const;

            systems::StateSpace<> linearize(const GiNaC::matrix &jacobianStates,
                                          const GiNaC::matrix &jacobianInputs,
                                          const std::vector<double> &states,
                                          const std::vector<double> &inputs) const;

            systems::StateSpace<> linearize(const GiNaC::matrix &jacobianStates,
                                          const GiNaC::matrix &jacobianInputs,
                                          double t,
                                          const std::vector<double> &states,
                                          const std::vector<double> &inputs) const;

            static Eigen::MatrixXd matrixToMatrixXd(const GiNaC::matrix &mat);

            static Eigen::MatrixXd matrixToMatrixXd(const GiNaC::ex &ex);

        private:
            GiNaC::lst _functions;
            GiNaC::symbol _time;
            GiNaC::lst _states;
            GiNaC::lst _inputs;

            std::map<std::string, GiNaC::symbol> _symbolMap;

            void makeSymbolMap();
        };
    }
}

#endif

#endif //LODESTAR_ORDINARYDIFFERENTIALEQUATION_HPP
