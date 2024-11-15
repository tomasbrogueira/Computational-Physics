#ifndef __INTEGDERIV__
#define __INTEGDERIV__
#include "Functor.hpp"

class IntegDeriv {
    public:
        IntegDeriv(Functor&);
        ~IntegDeriv() = default;
        // integration methods
        void TrapezoidalRule(double xi, double xf, double& Integral, double&
        Error);
        void simpsonRule(double xi, double xf, double& Integral, double&
        Error);
        // derivative methods
        double DF_fo(double x0, double dx); // point where we are differentiating, step
        double DF_central(double x0, double dx);
        double DF_bck(double x0, double dx);
        double D2F_3point(double x0, double dx); // for the second derivatives, dx must be ~3e-4
        double D2F_5point(double x0, double dx);
        double D4F(double x0, double dx); // dx ~ 8e-3
    private:
        Functor& F;
};

#endif