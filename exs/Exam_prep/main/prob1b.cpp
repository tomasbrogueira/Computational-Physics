#include "ODEsolver.hpp"
#include "ROOTplotter.hpp"


#include <cmath>

int main () {

    double const g = 9.8 , l = 5 , m = 1; // m/s^2 , m


    ODEpoint P0(0,{65*M_PI/180,0}); // t (s) , a (rad), w (rad/s)


    vector<std::function<double(ODEpoint)>> functions {
        [](ODEpoint P)->double {return P[1];},    // da/dt     
        [=](ODEpoint P)->double {return -g*sin(P[0])/l;},    // dw/dt
    };
    

    ODEsolver S(functions);
    double dt = 0.01 , Tmax = 60;


    vector<ODEpoint> R4 = S.RK4(P0,dt,Tmax);

    vector<double> T,A,W,Em;

    for (auto p : R4) {
        T.push_back(p.T());
        A.push_back(p[0]);
        W.push_back(p[1]);
        Em.push_back(1/2. *m* pow(p[1] * l, 2) + g * m *  l * (1 - cos(p[0])));
    }


/*
    for (auto a : A) {
        // graus
        A.push_back(a*180/M_PI);
    }

    for (auto w : W) {
        // graus 
        W.push_back(w*180/M_PI);
    }
*/

    ROOTplotter plotter;

    vector<vector<string>> labels_wa = {{"W by angle", "angle (degrees)","W(degrees)"}};
    TCanvas* C = plotter.PlotMultipleGraphs({A},{W},labels_wa);
    C->SaveAs("w_a.pdf");

    vector<vector<string>> labels_a = {{"Angle by time", "time","angle"}};
    C = plotter.PlotMultipleGraphs({T},{A},labels_a);
    C->SaveAs("a_t.pdf");

    vector<vector<string>> labels_et = {{"EM by time", "time","EM"}};
    C = plotter.PlotMultipleGraphs({T},{Em},labels_et);
    C->SaveAs("Em_t.pdf");
}