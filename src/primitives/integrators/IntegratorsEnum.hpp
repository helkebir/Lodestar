//
// Created by Hamza El-Kebir on 6/26/21.
//

#ifndef LODESTAR_INTEGRATORSENUM_HPP
#define LODESTAR_INTEGRATORSENUM_HPP

namespace ls {
    namespace primitives {
        enum class IntegratorsEnum {
            BogackiShampine,
            BogackiShampineEmbedded,
            RungeKuttaFehlberg45,
            RungeKuttaFehlberg45Embedded,
            RungeKuttaFehlberg78,
            RungeKuttaFehlberg78Embedded,
        };
    }
}

#endif //LODESTAR_INTEGRATORSENUM_HPP
