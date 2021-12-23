//
// Created by Hamza El-Kebir on 10/7/21.
//

#ifndef LODESTAR_MODELPREDICTIVECONTROL_HPP
#define LODESTAR_MODELPREDICTIVECONTROL_HPP

#include <type_traits>
#include "systems/StateSpace.hpp"
#include "aux/CompileTimeQualifiers.hpp"

namespace ls {
    namespace control {
        template<const int THorizonLength = Eigen::Dynamic,
                typename TScalar = double,
                const int TStateDim = Eigen::Dynamic,
                const int TInputDim = Eigen::Dynamic,
                const int TOutputDim = Eigen::Dynamic>
        class ModelPredictiveControl {
        public:
            using StateSpace = systems::StateSpace<TScalar, TStateDim, TInputDim, TOutputDim>;
            const int kHMatrixDim = LS_STATIC_UNLESS_DYNAMIC_VAL(THorizonLength, THorizonLength*(TStateDim + TInputDim));
            const int kCMatrixRows = LS_STATIC_UNLESS_DYNAMIC_VAL(THorizonLength, TStateDim * THorizonLength);
            const int kCMatrixCols = LS_STATIC_UNLESS_DYNAMIC_VAL(THorizonLength, THorizonLength*(TStateDim + TInputDim));

            typedef Eigen::Matrix<TScalar,
                    LS_STATIC_UNLESS_DYNAMIC_VAL(THorizonLength, THorizonLength*(TStateDim + TInputDim)),
                    LS_STATIC_UNLESS_DYNAMIC_VAL(THorizonLength, THorizonLength*(TStateDim + TInputDim))>
                    TDHMatrix;

            typedef Eigen::Matrix<TScalar,
                    LS_STATIC_UNLESS_DYNAMIC_VAL(THorizonLength, TStateDim * THorizonLength),
                    LS_STATIC_UNLESS_DYNAMIC_VAL(THorizonLength, THorizonLength*(TStateDim + TInputDim))>
                    TDCMatrix;

            ModelPredictiveControl() : ss_{}
            {};

            ModelPredictiveControl(const StateSpace &ss) : ss_{ss}
            {}

            // TODO: Implement
            IF_DYNAMIC_RETURN(TStateDim, TInputDim, TOutputDim, Eigen::MatrixXd)
            computeH() const
            {
                return Eigen::MatrixXd{};
            }

            // TODO: Implement
            IF_STATIC_RETURN(TStateDim, TInputDim, TOutputDim, TDHMatrix)
            computH() const
            {
                return TDHMatrix{};
            }

        protected:
            StateSpace ss_;
        };
    }
}

#endif //LODESTAR_MODELPREDICTIVECONTROL_HPP
