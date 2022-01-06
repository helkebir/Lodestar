//
// Created by Hamza El-Kebir on 5/8/21.
//

#ifndef LODESTAR_ORDINARYDIFFERENTIALEQUATION_HPP
#define LODESTAR_ORDINARYDIFFERENTIALEQUATION_HPP

#ifdef LS_USE_GINAC

#include <Eigen/Dense>
#include "ginac/ginac.h"

#include "Lodestar/systems/StateSpace.hpp"

#include <string>
#include <deque>

namespace ls {
    namespace symbolic {
        class OrdinaryDifferentialEquation {
        public:
            OrdinaryDifferentialEquation() :
                    functions_(GiNaC::lst{GiNaC::ex(0)}),
                    states_(GiNaC::lst{GiNaC::symbol("x")}),
                    inputs_(GiNaC::lst{GiNaC::symbol("u")}),
                    time_(GiNaC::symbol("t"))
            {
                makeSymbolMap();
            }

            OrdinaryDifferentialEquation(const GiNaC::lst &functions,
                                         const GiNaC::lst &states,
                                         const GiNaC::lst &inputs) :
                    functions_(functions),
                    states_(states),
                    inputs_(inputs),
                    time_(GiNaC::symbol("t"))
            {
                makeSymbolMap();
            }

            OrdinaryDifferentialEquation(const GiNaC::lst &functions,
                                         const GiNaC::lst &states,
                                         const GiNaC::lst &inputs,
                                         const GiNaC::symbol &time) :
                    functions_(functions),
                    states_(states),
                    inputs_(inputs),
                    time_(time)
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

            std::string generateJacobianStatesCppFunc(const std::string &functionName, const bool dynamicType = false) const;

            std::string generateJacobianStatesArrayInputCppFunc(const std::string &functionName, const bool dynamicType = false) const;

            GiNaC::matrix generateJacobianInputs() const;

            std::string generateJacobianInputsCppFunc(const std::string &functionName, const bool dynamicType = false) const;

            std::string generateJacobianInputsArrayInputCppFunc(const std::string &functionName, const bool dynamicType = false) const;

            Eigen::MatrixXd generateJacobianMatrix(const GiNaC::lst &variables,
                                                   const GiNaC::exmap &exmap) const;

            Eigen::MatrixXd
            generateJacobianMatrix(const GiNaC::matrix &jacobian,
                                   const GiNaC::exmap &exmap) const;

            Eigen::MatrixXd
            generateJacobianMatrixStates(const GiNaC::exmap &exmap) const;

            Eigen::MatrixXd
            generateJacobianMatrixInputs(const GiNaC::exmap &exmap) const;

            std::string generateMatrixCppFunc(const GiNaC::matrix &ginacMatrix, const std::string &functionName, const bool dynamicType = false) const;

            std::string generateMatrixArrayInputCppFunc(const GiNaC::matrix &ginacMatrix, const std::string &functionName, const bool dynamicType = false) const;

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

        protected:
            GiNaC::lst functions_;
            GiNaC::symbol time_;
            GiNaC::lst states_;
            GiNaC::lst inputs_;

            std::map<std::string, GiNaC::symbol> symbolMap_;

            void makeSymbolMap();

            static void replaceString(std::string &str, const std::string &source, const std::string &dest);
            static void replaceStringAll(std::string &str, const std::string &source, const std::string &dest);
            static std::string stripWhiteSpace(std::string &str);
        };
    }
}

#endif

#endif //LODESTAR_ORDINARYDIFFERENTIALEQUATION_HPP
