//
// Created by Hamza El-Kebir on 4/19/21.
//

#ifndef LODESTAR_UNITLITERALS_HPP
#define LODESTAR_UNITLITERALS_HPP

#include <math.h>

namespace ls {
    namespace aux {
        long double operator "" _Hz(long double freq)
        {
            return 1 / freq;
        }

        long double operator "" _Hz(unsigned long long freq)
        {
            return 1 / (long double) freq;
        }

        long double operator "" _ms(long double ms)
        {
            return ms * 1e-3;
        }

        long double operator "" _ms(unsigned long long ms)
        {
            return (long double) ms * 1e-3;
        }

        long double operator "" _us(long double us)
        {
            return us * 1e-6;
        }

        long double operator "" _us(unsigned long long us)
        {
            return (long double) us * 1e-6;
        }

        long double operator "" _ns(long double ns)
        {
            return ns * 1e-9;
        }

        long double operator "" _ns(unsigned long long ns)
        {
            return (long double) ns * 1e-9;
        }

        long double operator "" _deg(long double deg)
        {
            return deg * M_PI / 180;
        }

        long double operator "" _deg(unsigned long long deg)
        {
            return (long double) deg * M_PI / 180;
        }
    }
}

#endif //LODESTAR_UNITLITERALS_HPP
