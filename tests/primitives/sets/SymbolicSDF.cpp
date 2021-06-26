//
// Created by Hamza El-Kebir on 6/25/21.
//

#include "catchOnce.hpp"

#ifdef LS_USE_GINAC

#include <ginac/ginac.h>
#include "symbolic/SymbolicFunctions.hpp"
#include <iostream>

//GiNaC::ex unionize(const GiNaC::ex &expr0, const GiNaC::ex &expr1)
//{
////    return GiNaC::cos
//}

TEST_CASE("Symbolic SDF", "[primitives][sets][sdf]")
{
    GiNaC::symbol p("p");
    GiNaC::ex f1 = 2 * p;
    GiNaC::ex f2 = 3 * p;

    std::cout << "f1 <= f2: " << (bool) (f1 <= f2) << std::endl;
    std::cout << "min(f2, 0) - min(f1, 0) <= 0: " << (bool) ((GiNaC::min(f2, 0) - GiNaC::min(f1, 0)) <= 0) << std::endl;

    GiNaC::expand(GiNaC::min(f1, 0));
    std::cout << "min(f1, 0): " << GiNaC::expand(GiNaC::min(f1, 0)) << std::endl;
    std::cout << "min(f2, 0): " << GiNaC::expand(GiNaC::min(f2, 0)) << std::endl;

    std::cout << "min(f1, 0) <= 0: " << (bool) (GiNaC::expand(GiNaC::min(f1, 0)) <= 0) << std::endl;
    std::cout << "p - abs(p) <= 0: " << (bool) ((p - GiNaC::abs(p)) <= 0) << std::endl;
    std::cout << "true: " << true << std::endl;
}

#endif // LS_USE_GINAC