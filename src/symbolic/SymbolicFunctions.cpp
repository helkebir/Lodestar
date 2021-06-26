//
// Created by Hamza El-Kebir on 6/25/21.
//

#ifdef LS_USE_GINAC

#include "SymbolicFunctions.hpp"

namespace GiNaC {
    static ex max_eval(const ex &a, const ex &b)
    {
        return (a + b) / 2 + abs(a - b) / 2;
    }

    const numeric max(const numeric &a, const numeric &b)
    {
        return numeric((a.to_cl_N() + b.to_cl_N()) / 2 + cln::abs(a.to_cl_N() - b.to_cl_N()) / 2);
    }

    static ex max_evalf(const ex &a, const ex &b)
    {
        if (is_exactly_a<numeric>(a) && is_exactly_a<numeric>(b))
            return max(ex_to<numeric>(a), ex_to<numeric>(b));

        return max(a, b).hold();
    }

    // TODO: Deal with nonexistance for a = b
    //  check if the relation a < b can be evaluated in general.
    static ex max_deriv(const ex &a, const ex &b, unsigned deriv_param)
    {
        GINAC_ASSERT(deriv_param < 2);

        if (deriv_param == 0) {
            // d/da max(a, b)
            if (a < b)
                return 0;
            else
                return 1;
        }

        // d/db max(a, b)
        if (a < b)
            return 1;
        else
            return 0;
    }

    REGISTER_FUNCTION(max, eval_func(max_eval).
            evalf_func(max_evalf).
            derivative_func(max_deriv));

    static ex min_eval(const ex &a, const ex &b)
    {
        return (a + b) / 2 - abs(a - b) / 2;
    }

    const numeric min(const numeric &a, const numeric &b)
    {
        return numeric((a.to_cl_N() + b.to_cl_N()) / 2 - cln::abs(a.to_cl_N() - b.to_cl_N()) / 2);
    }

    static ex min_evalf(const ex &a, const ex &b)
    {
        if (is_exactly_a<numeric>(a) && is_exactly_a<numeric>(b))
            return min(ex_to<numeric>(a), ex_to<numeric>(b));

        return min(a, b).hold();
    }

    static ex min_deriv(const ex &a, const ex &b, unsigned deriv_param)
    {
        GINAC_ASSERT(deriv_param < 2);

        if (deriv_param == 0) {
            // d/da min(a, b)
            if (a < b)
                return 1;
            else
                return 0;
        }

        // d/db min(a, b)
        if (a < b)
            return 0;
        else
            return 1;
    }

    REGISTER_FUNCTION(min, eval_func(min_eval).
            evalf_func(min_evalf).
            derivative_func(min_deriv));
}

#endif