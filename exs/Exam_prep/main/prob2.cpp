#include "ROOTplotter.hpp"
#include "BVSolver.hpp"
#include "Interpolator.hpp"
#include "ODEsolver.hpp"

using namespace std;

int main () {

    const double R = 0.15; // m,kg
    double m= 0.5;

    vector<double> inter = Interpolator({{5.75e-2,1.2e-3},{12e-2,1.8e-3},{18e-2,2.6e-3},{30e-2,4e-3}});

    function<double(double)> func = Coef2Func(inter);

    const double c = func(15e-2);

    double const g = 9.8 , l = 5 ; // m/s^2 , m


    ODEpoint P0(0,{65*M_PI/180,0}); // t (s) , a (rad), w (rad/s)


    vector<std::function<double(ODEpoint)>> functions {
        [](ODEpoint P)->double {return P[1];},    // da/dt     
        [=](ODEpoint P)->double {return -g*sin(P[0])/l - c*P[1]*l/m;},    // dw/dt
    };
    

    ODEsolver S(functions);
    double dt = 0.01 , Tmax = 60;


    vector<ODEpoint> R4 = S.RK4(P0,dt,Tmax);

    vector<double> T,A,W,Em,V;

    for (auto p : R4) {
        T.push_back(p.T());
        A.push_back(p[0]);
        W.push_back(p[1]);
        Em.push_back(1/2 *m* pow(p[1] * l, 2) + g * m *  l * (1 - cos(p[0])));
        V.push_back(p[1]*l);
    }

    
    ROOTplotter plotter;

    vector<vector<string>> labels_wa = {{"W by angle", "angle (degrees)","W(degrees)"}};
    TCanvas* C = plotter.PlotMultipleGraphs({A},{V},labels_wa);
    C->SaveAs("w_vatrit.pdf");

    vector<vector<string>> labels_Va = {{"V by time", "time (s)","Vel (m/s)"}};
    C = plotter.PlotMultipleGraphs({T},{V},labels_Va);
    C->SaveAs("v_tatrit.pdf");

    double dEm = Em[550] - Em[720];
    
    cout << "Energia perdida = " << dEm << endl; 
}