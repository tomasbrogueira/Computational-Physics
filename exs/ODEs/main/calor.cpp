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

    ODEpoint P0(0,{350,0,0}); // x (m) , T (K) , dT/dt (ºC/s) , d^2T/dt^2  (ºC/s^2)
    ODEpoint PF(20,{300,0,0});


    const double k = 0.3 /*(W.m^-1.K^-1)*/  ,c = 600 /*(J.Kg^-1)*/  ,p = 200 /*(Kg.m^-3)*/ ; 

    const double nintervals = 100;


    // functions 
    std::array<std::function<double(double)>,4> functions {
        [=](double P)->double {return k/(c*p);},    // da/dt     
        [](double P)->double {return 0;},    // dw/dt
        [](double P)->double {return 0;},    // da/dt     
        [](double P)->double {return 0;},    // dw/dt
    };

    BVSolver S(functions);

    vector<ODEpoint> sol = S.Solve(P0,PF,nintervals);

    vector<double>  X1,T1;

    for (auto p : sol) {
        X1.push_back(p.T());
        T1.push_back(p[0]);
    }

    TCanvas C = ("canvas","canvas",1000,1000);
    TGraph BVTx(sol.size(),X1.data(),T1.data());

    BVTx.SetLineColor(kRed);
    
    BVTx.Draw("APL");


    C.SaveAs("calor.png");
}
