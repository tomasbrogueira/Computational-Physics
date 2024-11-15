#include "BVSolver.hpp"
#include "EqSolver.hpp"
#include "FCmatrixAlgo.hpp"
#include "ODEsolver.hpp"

#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TColor.h"


#include <cmath>

using namespace std;

int main() {

    ODEpoint P0(0,{0,0}); // x,y,z

    // functions
    vector<std::function<double(ODEpoint)>> functions {
        [](ODEpoint P)->double {return cos(P.T())-P[1];},    // dy/dx     de acordo com a ordem das variaveis no P0
        [](ODEpoint P)->double {return sin(P.T())+P[0];},    // dz/dx
        
    };

    double step = 0.1, Xmax = 2 ;

    ODEsolver S(functions);
    vector<ODEpoint> R4 = S.RK4(P0,step,Xmax);

    vector<double> X1,Y1,Z1 ;
    
    for (auto p : R4) {
        X1.push_back(p.T());
        Y1.push_back(p[0]);
        Z1.push_back(p[1]);
    }
    

    
    TCanvas C = ("canvas","canvas",100,100);
    TGraph gr4yx(R4.size(),X1.data(),Y1.data());
    TGraph gr4zx(R4.size(),X1.data(),Z1.data());

    gr4yx.SetLineColor(kRed);
    gr4zx.SetLineColor(kBlue);

    gr4zx.Draw("APL");
    gr4yx.Draw("PL");

    C.SaveAs("twoeq.png");
} 