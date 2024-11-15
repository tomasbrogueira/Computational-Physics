#include "BVSolver.hpp"
#include "EqSolver.hpp"
#include "FCmatrixAlgo.hpp"
#include "ODEsolver.hpp"

#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TColor.h"

#include "cmath"

using namespace std;

int main () {

    // da/dt = w
    // dw/dt = gsin(a) - klw/m



    ODEpoint P0(0,{180/(70*M_PI),0}); // t (s) , a (radianos) , w (radianos/s)

    const double k = 0.3; // escalar de atrito
    const double m = 1; // massa (kg)
    const double L = 1; // comprimento fio (m)
    const double g = 9.81; // m/s^2

    // functions 
    vector<std::function<double(ODEpoint)>> functions {
        [](ODEpoint P)->double {return P[1];},    // da/dt     
        [=](ODEpoint P)->double {return -g*sin(P[0])-(k*L*P[1])/m;},    // dw/dt
    };
    
    double dt = 0.1 , Tmax = 60;

    ODEsolver S(functions);

    vector<ODEpoint> R4 = S.RK4(P0,dt,Tmax);

    vector<double> T1,A1,W1;

    for (auto p : R4) {
        T1.push_back(p.T());
        A1.push_back(p[0]);
        W1.push_back(p[1]);
    }


    TCanvas C = ("canvas","canvas",1000,1000);
    TGraph gr4at(R4.size(),T1.data(),A1.data());
    TGraph gr4wt(R4.size(),T1.data(),W1.data());

    gr4at.SetLineColor(kRed);
    gr4wt.SetLineColor(kBlue);


    gr4wt.Draw("APL");
    gr4at.Draw("PL");


    C.SaveAs("pendulo.png");
}