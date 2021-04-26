//
// Created by Hamza El-Kebir on 4/21/21.
//

#include "DiscreteStateSpace.hpp"

void ls::systems::DiscreteStateSpace::resample(const double dt)
{
    auto dss = ls::analysis::ZeroOrderHold::c2d(ls::analysis::ZeroOrderHold::d2c(*this, getSamplingPeriod()), dt);

    A = dss.A;
    B = dss.B;
    C = dss.C;
    D = dss.D;

    setSamplingPeriod(dt);
}

bool ls::systems::DiscreteStateSpace::isStable(const double tolerance) const
{
    auto eig = A.eigenvalues();
    double tol = (tolerance < 0 ? -tolerance*tolerance : tolerance*tolerance);

    for (int i = 0; i < eig.size(); i++) {
        if (eig(i).real()*eig(i).real() + eig(i).imag()*eig(i).imag() > 1 + tol)
            return false;
    }

    return true;
}
