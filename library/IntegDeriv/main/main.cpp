#include "Functor.hpp"
#include "Func1.h"
#include "FuncInt.hpp"
#include "IntegDeriv.hpp"
#include <iostream>
#include<iomanip>


using namespace std;

int main(){
    // Functor F("Function")
    Func1 F1;
    cout << "f(1.2) = " << F1(1.2) << endl;
    F1.Draw({-1, 1}, 100, {"x", "f(x)"}); // Drawing the given funcion
    IntegDeriv F_ID(F1);
    cout << "f'(2) = " << F_ID.DF_fo(2, 1e-10) << endl;
    cout << "f''(2) = " << F_ID.D2F_5point(2, 1e-3) << endl;
    cout << "f''(2) = " << F_ID.D2F_3point(2, 1e-3) << endl;
    cout << "f⁴(2) = " << F_ID.D4F(2, 1e-2) << endl;
    double integ, err;
    F_ID.TrapezoidalRule(0, 2, integ, err);
    cout<< "Trapezoidal Rule:"<<endl;
    cout << setprecision(8) << "integral= " << integ << " ± " << err <<endl;
    cout<< "Simpson Rule:"<<endl;
    F_ID.simpsonRule(0., 2., integ, err);
    cout << setprecision(16) << "integral= " << integ << " ± " << err <<endl;
    F_ID.RombergRule(0., 2., integ, err,1);
    cout << setprecision(16) << "integral= " << integ << " ± " << err <<endl;
    F_ID.RombergRule(0., 2., integ, err,2);
    cout << setprecision(16) << "integral= " << integ << " ± " << err <<endl;
    F_ID.RombergRule(0., 2., integ, err,3);
    cout << setprecision(16) << "integral= " << integ << " ± " << err <<endl;

    FuncIrr f;
    FuncInt F(f);
    IntegDeriv Int(F);

    Int.TrapezoidalRule(-5, 5, integ, err);
    cout<< "Trapezoidal Rule:"<<endl;
    cout << setprecision(8) << "integral= " << integ << " ± " << err <<endl;
}
