#include "FuncInt.hpp"
#include <cmath>
#include "TAxis.h"
#include "TSystem.h"
#include "TGraph.h"

FuncInt::FuncInt(FuncIrr& f_) : Functor("funcInt") ,I(f_){;}

double FuncInt::operator() (double x){
	FuncIrr::y = x;
    double integral, error;
    I.TrapezoidalRule(-5,5, integral, error);
    cout << integral << endl;
    return integral;
}

void FuncInt::Draw(array<float, 2> range, int npoints, array<string, 2> titles){

}

