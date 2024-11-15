#ifndef __FUNCIRR__
#define __FUNCIRR__
#include "TF1.h"
#include "Functor.hpp"

class FuncIrr: public Functor{
    public:
        FuncIrr();
        ~FuncIrr() = default;
        double operator() (double x);
        void Draw(array<float, 2> range, int npoints, array<string, 2> titles);
	static double y;
};

#endif
