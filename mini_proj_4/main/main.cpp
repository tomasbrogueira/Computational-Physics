#include "Functor.hpp"
#include "MyFunction.hpp"
#include "IntegDeriv.hpp"
#include "Rwalk1D.hpp"
#include <iostream>

using namespace std;

int main() {
    MyFunction f("testfunctor");

    f.Draw(-1,1,100,"x","y");
    cout << f(5) << endl;
    IntegDeriv I(f);

    double integral, error;
    // estao a entrar como referencia?
    I.TrapezoidalRule(0,10,100,integral,error);
    
    
    double integral2, error2;
    I.SimpsonRule(0,10,100, integral2, error2);

    cout << "Trapezoid\n" << "integral:" << integral<< "\n" <<"error:" <<error << endl;

    cout << "Simpson\n" << "integral:" << integral2 << "\n" <<"error:" <<error2 << endl;


    Rwalk1D R(10,0,0.5,0.5,1,1);
    R.Run(500);

    TMultiGraph *g = R.GetGraph();


    TCanvas* c = new TCanvas();
    c->cd();
    g->Draw("AL");
    c->SaveAs("test.png");

}