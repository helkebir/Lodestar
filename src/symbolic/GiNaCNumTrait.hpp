//
// Created by Hamza El-Kebir on 5/7/21.
//

#ifndef LODESTAR_GINACNUMTRAIT_HPP
#define LODESTAR_GINACNUMTRAIT_HPP

#ifdef LS_USE_GINAC

#include "Eigen/Core"
#include "ginac/ginac.h"

namespace Eigen {

    template<>
    struct NumTraits<GiNaC::ex> : NumTraits<double> {
        typedef GiNaC::ex Real;
        typedef GiNaC::ex NonInteger;
        typedef GiNaC::ex Nested;

        enum {
            IsComplex = 1,
            IsInteger = 0,
            IsSigned = 1,
            RequireInitialization = 1,
            ReadCost = 1,
            AddCost = 3,
            MulCost = 3
        };
    };

}

namespace GiNaC {

    // TODO: Fix conservativeResize.

    inline const ex &conj(const ex &x)
    { return conjugate(x); }

    inline const ex &real(const ex &x)
    { return real_part(x); }

    inline ex imag(const ex &x)
    { return imag_part(x); }

    //inline ex abs(const ex&  x)  { return abs(x); }
    inline ex abs2(const ex &x)
    { return x * x; }

}

#endif

#endif //LODESTAR_GINACNUMTRAIT_HPP
