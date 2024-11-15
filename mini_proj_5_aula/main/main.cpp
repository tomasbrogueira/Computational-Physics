#include "ODEpoint.hpp"
#include <functional>
#include <vector>
#include <iostream>
#include <TGraph.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TApplication.h>
#include <TColor.h>



using namespace std;
/*
    dy/dt = v     f0(t,y,v)
    dv/dt = -g    f1(t,y,v)

    ODEpoint:  [t; (y,v)]

    ODEsolver: 

        - ODEsolver( vector<std::function<double(ODEpoint)>>)

*/

int main() {

    //constants
    
    const double g = 9.80665; // m/s^2
  
    //init point

    ODEpoint p0(0, {200,150});


    // functions

    vector<function<double(ODEpoint)>> F{ 
        [](ODEpoint p) { return p.varGetter()[1];},
        [g](ODEpoint p) { return -g;}
    };

    
    // solving system
    double step = 0.2 ; // s
    double DT = 50; // s

    // euler
    vector<ODEpoint> v1;
    v1.push_back(p0);
    double t = 0;
    while (t < DT) {
        ODEpoint p = v1.back();
        v1.push_back(ODEpoint(t+step, {p.varGetter()[0] + step * F[0](p), p.varGetter()[1] + step * F[1](p)}));
        t += step;
        /*
        vector<double> var = v1.back().varGetter();
        vector<double> new_var;
        for (int i = 0; i < var.size(); i++) {
            new_var.push_back(var[i] + step * F[i](v1.back()));
        }
        t += step;
        v1.push_back(ODEpoint(t, new_var));
        */
    };

    // RK4
    vector<ODEpoint> v2;
    v2.push_back(p0);
    t = 0;
    while (v2.back().timeGetter() < DT) {
        ODEpoint p = v2.back();
        double k1 = step * F[0](p);
        double k2 = step * F[0](ODEpoint(p.timeGetter() + step/2, {p.varGetter()[0] + k1/2, p.varGetter()[1]}));
        double k3 = step * F[0](ODEpoint(p.timeGetter() + step/2, {p.varGetter()[0] + k2/2, p.varGetter()[1]}));
        double k4 = step * F[0](ODEpoint(p.timeGetter() + step, {p.varGetter()[0] + k3, p.varGetter()[1]}));
        double new_y = p.varGetter()[0] + (k1 + 2*k2 + 2*k3 + k4)/6;
        k1 = step * F[1](p);
        k2 = step * F[1](ODEpoint(p.timeGetter() + step/2, {p.varGetter()[0], p.varGetter()[1] + k1/2}));
        k3 = step * F[1](ODEpoint(p.timeGetter() + step/2, {p.varGetter()[0], p.varGetter()[1] + k2/2}));
        k4 = step * F[1](ODEpoint(p.timeGetter() + step, {p.varGetter()[0], p.varGetter()[1] + k3}));
        double new_v = p.varGetter()[1] + (k1 + 2*k2 + 2*k3 + k4)/6;
        t += step;
        v2.push_back(ODEpoint(t, {new_y, new_v}));
    };

    // print
    cout << "Euler:" << endl;
    for (auto i : v1) {
        cout << i;
    }
    cout << "RK4:" << endl;
    for (auto i : v2) {
        cout << i;
    }

    //TGraph
    vector<double> vt, vy, vv;
    for (auto i : v1) {
        vt.push_back(i.timeGetter());
        vy.push_back(i.varGetter()[0]);
        vv.push_back(i.varGetter()[1]);
    }

    TGraph gy(vt.size(), vt.data(), vy.data());
    TGraph gv(vt.size(), vt.data(), vv.data());

    gy.SetLinewidth(4);
    gy.SetLineColor(kRed);
    gy.GetXaxis()->SetTitle("t [s]");
    gy.GetYaxis()->SetTitle("y [m]");

    gv.SetLinewidth(4);
    gv.SetLineColor(kBlue);
    gv.GetXaxis()->SetTitle("t [s]");
    gv.GetYaxis()->SetTitle("v [m/s]");
    
    // display

    TApplication A("A", 0, 0);
    TCanvas c1("c1", "c1", 1400, 800);
    c1.Divide(2,1);
    c1.cd(1);
    gy.Draw("AL");
    c1.cd(2);
    gv.Draw("AL");
    c1.Update();
    A.Run();
    
}
