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

    ODEpoint P0(0,{1,0}); // t (s), x (cm),v (cm/s)

    const double w = 0.3;

    // functions 
    vector<std::function<double(ODEpoint)>> functions {
        [](ODEpoint P)->double {return P[1];},    // dx/dt     
        [=](ODEpoint P)->double {return -w*w*P[0];},    // dv/dt
    };
    
    double dt = 0.1 , Tmax = 20;

    ODEsolver S(functions);
    vector<ODEpoint> R4 = S.RK4(P0,dt,Tmax);
    vector<ODEpoint> Strvrlt = S.LeapFrog(P0,dt,Tmax);

    vector<double> T1,X1,V1,T2,X2,V2;

    for (auto p : R4) {
        T1.push_back(p.T());
        X1.push_back(p[0]);
        V1.push_back(p[1]);
    }

    for (auto p : Strvrlt) {
        T2.push_back(p.T());
        X2.push_back(p[0]);
        V2.push_back(p[1]);
    }

    TCanvas C = ("canvas","canvas",1000,1000);
    TGraph gr4xt(R4.size(),T1.data(),X1.data());
    TGraph gr4vt(R4.size(),T1.data(),V1.data());

    TGraph strxt(Strvrlt.size(),T2.data(),X2.data());
    TGraph strvt(Strvrlt.size(),T2.data(),V2.data());

    gr4xt.SetLineColor(kRed);
    gr4vt.SetLineColor(kBlue);
    strxt.SetLineColor(kGreen);
    strvt.SetLineColor(kYellow);

    
    gr4xt.Draw("APL");
    gr4vt.Draw("PL");
    strxt.Draw("PL");
    strvt.Draw("PL");


    C.SaveAs("mola.png");
}