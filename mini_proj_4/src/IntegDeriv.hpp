#ifndef __INTEGDERIV__
#define __INTEGDERIV__

#include "Functor.hpp"

class IntegDeriv {

    public:
    IntegDeriv(Functor& f) ;
    ~IntegDeriv() = default;

    // integration methods

    void TrapezoidalRule(double xi, double xf,int nintervals, double& Integral, double& Error);

    void SimpsonRule(double xi, double xf, int nintervals, double& Integral, double& Error);

    // derivative methods

    double second_derivative_3pt(double x, double h =0.01);

    double second_derivative_5pt(double x, double h =0.01);

    double fourth_derivative(double x, double h =0.01);

    private:
    Functor& F;
};

#endif