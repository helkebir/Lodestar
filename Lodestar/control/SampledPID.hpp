//
// Created by Hamza El-Kebir on 6/20/21.
//

#ifndef LODESTAR_SAMPLEDPID_HPP
#define LODESTAR_SAMPLEDPID_HPP

#include "Lodestar/primitives/differentiators/BackwardDifference.hpp"


namespace ls {
    namespace control {
        template<typename TScalarType = double>
        class SampledPID {
        public:
            SampledPID() : proportionalGain_(1), integralGain_(1), derivativeGain_(1)
            {};



        protected:
            TScalarType proportionalGain_, integralGain_, derivativeGain_;
        };
    }
}


#endif //LODESTAR_SAMPLEDPID_HPP
