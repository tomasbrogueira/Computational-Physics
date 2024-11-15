#include "BVSolver.hpp"
#include "EqSolver.hpp"
#include "FCmatrixAlgo.hpp"
#include "ODEsolver.hpp"

#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TColor.h"

using namespace std;



int main() {
    ODEpoint p0 = ODEpoint(0,{3});

    
    // functions
    vector<std::function<double(ODEpoint)>> functions {
        [](ODEpoint P)->double {return 3*P[0]-P[1]+8;},
    };

    
    ODEsolver S(functions);

    double step = 0.1 ,  Xtotal = 2.0;
    
    vector<ODEpoint> Eu = S.Euler(p0,step,Xtotal);
    vector<ODEpoint> Trap = S.PredictorCorrector(p0,step,Xtotal);
    vector<ODEpoint> R2 = S.RK2(p0,step,Xtotal);
    vector<ODEpoint> R4 = S.RK4(p0,step,Xtotal);


    vector<double> X1, Y1 , X2 , Y2 ,X3 ,Y3, X4, Y4;

    for (auto p: Eu ) {
        X1.push_back(p.T());
        Y1.push_back(p[0]);
    }

    for (auto p: Trap ) {
        X2.push_back(p.T());
        Y2.push_back(p[0]);
    }

    for (auto p: R2 ) {
        X3.push_back(p.T());
        Y3.push_back(p[0]);
    }

    for (auto p: R2 ) {
        X4.push_back(p.T());
        Y4.push_back(p[0]);
    }



    TCanvas C = ("canvas","canvas",800,800);
    TGraph geuler(Eu.size(),X1.data(),Y1.data());
    TGraph gtrap(Trap.size(),X2.data(),Y2.data());
    TGraph gr2(R2.size(),X3.data(),Y3.data());
    TGraph gr4(R4.size(),X4.data(),Y4.data());

    geuler.SetLineColor(kRed);
    gtrap.SetLineColor(kBlue);
    gr2.SetLineColor(kGreen);
    gr4.SetLineColor(kYellow);

    geuler.Draw("APL");
    gtrap.Draw("PL");
    gr2.Draw("PL");
    gr4.Draw("PL");

    C.SaveAs("unidirect.png");

}


