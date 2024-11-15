#ifndef __FUNCINT__
#define __FUNCINT__
#include "TF1.h"
#include "Functor.hpp"
#include "FuncIrr.hpp"
#include"IntegDeriv.hpp"


class FuncInt: public Functor{
    public:
        FuncInt(FuncIrr&);
        ~FuncInt() = default;
        double operator() (double x);
        void Draw(array<float, 2> range, int npoints, array<string, 2> titles);
	IntegDeriv I;
};

#endif
