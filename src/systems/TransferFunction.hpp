//
// Created by Hamza El-Kebir on 4/18/21.
//

#ifndef LODESTAR_TRANSFERFUNCTION_HPP
#define LODESTAR_TRANSFERFUNCTION_HPP

#include "SystemStateless.hpp"
#include "StateSpace.hpp"
#include "DiscreteStateSpace.hpp"
#include "analysis/BilinearTransformation.hpp"
#include "LodestarErrors.hpp"

#include "Eigen/Dense"

#ifdef LS_USE_GINAC

#include <ginac/ginac.h>

#undef Mutable

#endif

namespace ls {
    namespace systems {
        class TransferFunction : SystemStateless {
        public:
            /**
             * @brief Default constructor.
             */
            TransferFunction() : _num(Eigen::MatrixXd::Ones(1, 1)),
                                 _den(Eigen::MatrixXd::Ones(1, 1))
            {}

            /**
             * @brief Copy constructor.
             *
             * @param other Transfer function to copy.
             */
            TransferFunction(const TransferFunction &other);

            /**
             * @brief Constructs a transfer function from a vector of numerator
             * and denominator coefficients.
             *
             * @note Coefficients are in descending order (starting with the
             * monomial with highest power).
             *
             * @param num Numerator coefficients.
             * @param den Denominator coefficients.
             */
            TransferFunction(const Eigen::MatrixXd &num,
                             const Eigen::MatrixXd &den) : _num(num), _den(den)
            {}

            /**
             * @brief Gets numerator coefficients.
             *
             * @return Numerator coefficients.
             */
            Eigen::MatrixXd getNum() const;

            /**
             * @brief Sets numerator coefficients.
             *
             * @param num Numerator coefficients.
             */
            void setNum(const Eigen::MatrixXd &num);

            /**
             * Returns polynomial degree of the numerator.
             *
             * @return Numerator degree.
             */
            long getNumDegree() const;

            /**
             * @brief Gets denominator coefficients.
             *
             * @return Denominator coefficients.
             */
            Eigen::MatrixXd getDen() const;

            /**
             * @brief Set denominator coefficients.
             *
             * @param den Denominator coefficients.
             */
            void setDen(const Eigen::MatrixXd &den);

            /**
             * Returns polynomial degree of the denominator.
             *
             * @return denominator degree.
             */
            long getDenDegree() const;

            /**
             * @brief Normalizes transfer function in place.
             */
            void normalizeInPlace();

            /**
             * @brief Creates normalized transfer function.
             *
             * @return Normalized transfer function.
             */
            TransferFunction normalized() const;

            /**
             * @brief Converts transfer function to state space object.
             *
             * @return State space object.
             */
            StateSpace toStateSpace() const;

            /**
             * @brief Converts transfer function to discrete-time state space
             * object.
             *
             * @note This method uses the backward difference method by default.
             *
             * @see ls::analysis::BilinearTransformation::c2dBwdDiff
             *
             * @param dt Sampling period.
             * @return Discrete-time state space system.
             */
            StateSpace toDiscreteStateSpace(double dt) const;

            /**
             * @brief Convert transfer function to discrete-time state space
             * object.
             *
             * This method adds the option to set \p alpha in the generalized
             * bilinear transform.
             *
             * @param dt Sampling period.
             * @param alpha Generalized bilinear transform parameter.
             * @return Discrete-time state space system.
             */
            StateSpace toDiscreteStateSpace(double dt, double alpha) const;

#ifdef LS_USE_GINAC

            /**
             * @brief Constructs a transfer function from the given symbolic
             * expression.
             *
             * @param tf Transfer function expression.
             * @param symbol Symbol used for the independent variable.
             */
            TransferFunction(const GiNaC::ex &tf, const GiNaC::ex &symbol);

            /**
             * @brief Generates a symbolic expression of the numerator
             * polynomial.
             *
             * @param symbol Symbol to use for the independent variable.
             *
             * @return GiNaC expression of the numerator polynomial.
             */
            GiNaC::ex getNumExpression(const GiNaC::ex &symbol) const;

            /**
             * @brief Generates a symbolic expression of the denominator
             * polynomial.
             *
             * @param symbol Symbol to use for the independent variable.
             *
             * @return GiNaC expression of the denominator polynomial.
             */
            GiNaC::ex getDenExpression(const GiNaC::ex &symbol) const;

            /**
             * @brief Generates a symbolic expression of the transfer function.
             *
             * @param symbol Symbol to use for the independent variable.
             * @return GiNaC expression of the transfer function.
             */
            GiNaC::ex getExpression(const GiNaC::ex &symbol) const;

            /**
             * @brief Copies transfer function coefficients from the given
             * symbolic expression.
             *
             * @param tf Transfer function expression.
             * @param symbol Symbol used for the independent variable.
             */
            void
            copyFromExpression(const GiNaC::ex &tf, const GiNaC::ex &symbol);

#endif

        private:
            Eigen::MatrixXd _num, /// Numerator coefficients.
            _den; /// Denominator coefficients.
        };
    }
}

#endif //LODESTAR_TRANSFERFUNCTION_HPP
