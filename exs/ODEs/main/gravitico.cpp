#include "BVSolver.hpp"
#include "EqSolver.hpp"
#include "FCmatrixAlgo.hpp"
#include "ODEsolver.hpp"

#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TColor.h"

using namespace std;

int main () {

    const double m = 80; // massa (kg)
    const double k = 0.3; // constante resistencia do ar
    const double g = 9.81; // acelaracao gravitica
    

    // dv/dt = (k*v)/m -g
    // dy/dt = v


    ODEpoint P0(0,{2000,0});

    // functions
    vector<std::function<double(ODEpoint)>> functions {
        [](ODEpoint P)->double {return P[1];},
        [=](ODEpoint P)->double {return -(k*P[1])/m-g;},
    };

    double step = 0.1, Tmax = 30 ;

    ODEsolver S(functions);
    vector<ODEpoint> R4 = S.RK4(P0,step,Tmax);

    vector<double> T1,Z1,V1;

    for (auto p : R4) {
        T1.push_back(p.T());
        Z1.push_back(p[0]);
        V1.push_back(p[1]);
    }


    TCanvas C = ("canvas","canvas",1000,1000);
    TGraph gr4zt(R4.size(),T1.data(),Z1.data());
    TGraph gr4vt(R4.size(),T1.data(),V1.data());

    gr4zt.SetLineColor(kRed);
    gr4vt.SetLineColor(kBlue);


    C.Divide(2,1);
    C.cd(1);
    gr4vt.Draw("AL");

    C.cd(2);
    gr4zt.Draw("AL");


    C.SaveAs("gravitico.png");
}