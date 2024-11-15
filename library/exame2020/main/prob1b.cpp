#include<iostream>
#include<vector>
#include<string>
#include"../src/ODEsolver.hpp"
#include"../src/IntegDeriv.hpp"
#include"../src/Interpolator.hpp"
#include<cmath>
# include "TGraph.h"
# include "TCanvas.h"
# include "TAxis.h"
using namespace std;

int main(){
    double g=9.8,l=5.,theta0=(65./180.)*M_PI,m=1;
    function<double(ODEpoint)> dtheta_dt = [](ODEpoint p)-> double {return p[1];};
    function<double(ODEpoint)> domega_dt = [g,l](ODEpoint p)-> double {return -(g/l)*sin(p[0]);};
    ODEpoint p0(0, {theta0,0});
    ODEsolver S({dtheta_dt,domega_dt});
    double dt=0.01,T=50;
    S.RK4(p0,dt,T);
    vector<double> rk4t,rk4x,rk4y,rk4E;
    for(auto p: S.getODEpoints("rk4")){
    rk4t.push_back(p.T());
    rk4x.push_back(p[0]);
    rk4y.push_back(p[1]);
    rk4E.push_back(0.5*m*(l*p[1])*(l*p[1])+ m*g*l*(1-cos(p[0]))); //mechanical energy ;v = l*angular_velocity

    }
    cout << rk4t.size() << "  " << rk4x.size() << "  " << rk4y.size() << "\n";
    TCanvas* c = new TCanvas("canvas","canvas", 1200,1000);
    //TGraph g1(rk4t.size(),rk4t.data(),rk4x.data());
    TGraph g2(rk4x.size(),rk4y.data(),rk4x.data());
    TGraph g3(rk4t.size(),rk4t.data(),rk4E.data());
    TGraph g4(rk4t.size(),rk4t.data(),rk4x.data());
    string s;
    s = "angulo em funcao da velocidade angular";
    g2.SetTitle(s.c_str());
    s = "energia total em funcao do tempo";
    g3.SetTitle(s.c_str());
    s = "angulo em funcao do tempo";
    g4.SetTitle(s.c_str());


    //g1.Draw("APL");
    //c->SaveAs("prob1b_diagramafase.pdf");
    g2.Draw("APL");
    c->SaveAs("prob1b_diagramafase.pdf");
    g3.Draw("APL");
    c->SaveAs("prob1b_diagramafase.pdf");
    g4.Draw("APL");
    c->SaveAs("prob1b_theta.pdf");
    return 0;
}