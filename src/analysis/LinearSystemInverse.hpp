//
// Created by Hamza El-Kebir on 4/17/21.
//

#ifndef LODESTAR_LINEARSYSTEMINVERSE_HPP
#define LODESTAR_LINEARSYSTEMINVERSE_HPP

#include "systems/StateSpace.hpp"

namespace ls {
    namespace analysis {
        /**
         * @brief Routines for computing the  inverse of a continuous-time state
         * space systems.
         *
         * Corresponds to SLICOT Routine <a href="http://slicot.org/objects/software/shared/doc/AB07ND.html">AB07ND</a>
         * (<em>Inverse of a given state-space representation</em>).
         */
        class LinearSystemInverse {
        public:
            /**
             * @brief Generates the inverse of a state space system.
             *
             * @param ss Pointer to state space system.
             * @param out Output of inverted state space system.
             */
            template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
            static void inverse(const systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *ss,
                                systems::StateSpace<TScalar, TStateDim, TOutputDim, TInputDim> *out);

            /**
             * @brief Generates the inverse of a state space system.
             *
             * @param ss State space system.
             * @param out Output of inverted state space system.
             */
            template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
            static void inverse(const systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> &ss,
                                systems::StateSpace<TScalar, TStateDim, TOutputDim, TInputDim> *out);

            /**
             * @brief Generates the inverse of a state space system.
             *
             * @param ss Pointer to state space system.
             *
             * @return Inverted state space system.
             */
            static systems::StateSpace<>
            inverse(const systems::StateSpace<> *ss);

            /**
             * @brief Generates the inverse of a state space system.
             *
             * @param ss State space system.
             *
             * @return Inverted state space system.
             */
            static systems::StateSpace<>
            inverse(const systems::StateSpace<> &ss);
        };
    }
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void
ls::analysis::LinearSystemInverse::inverse(const systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> *ss,
                                           systems::StateSpace<TScalar, TStateDim, TOutputDim, TInputDim> *out)
{
    out->setA((*ss->getA()) - (*ss->getB()) * (*ss->getD()).inverse() * (*ss->getC()));
    out->setB(-(*ss->getB()) * (*ss->getD()).inverse());
    out->setC((*ss->getD()).inverse() * (*ss->getC()));
    out->setD((*ss->getD()).inverse());
}

template<typename TScalar, int TStateDim, int TInputDim, int TOutputDim>
void
ls::analysis::LinearSystemInverse::inverse(const ls::systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim> &ss,
                                           ls::systems::StateSpace<TScalar, TStateDim, TOutputDim, TInputDim> *out)
{
    inverse(&ss, out);
}

#endif //LODESTAR_LINEARSYSTEMINVERSE_HPP
