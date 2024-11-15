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
    //finding c using lagrange polynomial interpolation
    //4 points -> cubic polynomial
    vector<pair<double,double>> pts = {{5.75,1.2*10e-3},{12.00,1.8*10e-3},{18.00,2.6*10e-3},{30.00,4.0*10e-3}};
    auto coef = Interpolator(pts);
    Functor F("interpol",Coef2Func(coef));
    double air_c = F(15), m=0.5,g=9.8,l=5+0.15; //using the interpolation polynomial to get the answer
    cout << air_c << "\n\n";

    double dt=0.01,T=55;
    function<double(ODEpoint)> dtheta_dt = [](ODEpoint p)-> double {return p[1];};
    function<double(ODEpoint)> domega_dt = [air_c,m,g,l](ODEpoint p)-> double {return -(g/l)*sin(p[0])-air_c*p[1]/m;};
    double theta=(65./180)*M_PI;
    ODEpoint p0(0, {theta,0});
    ODEsolver S1({dtheta_dt,domega_dt});
    S1.RK4(p0,dt,T);
    vector<double> rk4t,rk4x,rk4y,rk4z,rk4E;
    vector<ODEpoint> pts_=S1.getODEpoints("rk4");
    for(auto p: pts_){
    rk4t.push_back(p.T());
    rk4x.push_back(p[0]);
    rk4y.push_back(l*p[1]); //linear velocity
    rk4z.push_back(p[1]); //angular velocity
    rk4E.push_back(0.5*m*(l*p[1])*(l*p[1])+ m*g*l*(1-cos(p[0]))); //mechanical energy ;v = l*angular_velocity

    }
    TCanvas* c2 = new TCanvas("canvas","canvas", 1200,1000);
    TGraph g5(rk4x.size(),rk4x.data(),rk4z.data());
    TGraph g6(rk4t.size(),rk4t.data(),rk4y.data());
    string s;
    s = "angulo em funcao da velocidade angular";
    g5.SetTitle(s.c_str());
    s = "velocidade linear em funcao do tempo";
    g6.SetTitle(s.c_str());
    //TGraph g7(rk4t.size(),rk4t.data(),rk4E.data());
    //TGraph g8(rk4t.size(),rk4t.data(),rk4x.data());
    g5.Draw("APL");
    c2->SaveAs("prob2_diagramafase.pdf");
    g6.Draw("APL");
    c2->SaveAs(" prob2_velocidade.pdf");
    delete c2;
    //g7.Draw("APL");
    //c->SaveAs("g7.pdf");
    //g8.Draw("APL");
    //c->SaveAs("g8.pdf");
    /*

    exponential law theta_max = A*e^(B*t); A = theta_initial
    we can, for example, use the first maximum to determine B
    */
    ODEpoint first_max;
    for(int i=1; i < pts_.size()-1;i++){
        if(pts_[i-1][0]< pts_[i][0] && pts_[i+1][0] < pts_[i][0]) first_max = pts_[i];
    }
    // B = log(theta_max/A)/t
    double gamma = log(first_max[0]/theta)/first_max.T();
    auto exp_ = [gamma,theta](double t){return theta*exp(gamma*t);};
    vector<double> rk4z_;
    for(int i=0; i < rk4t.size();i++){
        rk4z_.push_back(exp_(rk4t[i]));
    }
    TCanvas* c3 = new TCanvas("canvas","canvas", 1200,1000);
    TGraph g7(rk4t.size(),rk4t.data(),rk4z_.data());
    TGraph g8(rk4t.size(),rk4t.data(),rk4x.data());
    g8.Draw("APL");
    g7.Draw("same");
    s = "plot do angulo em funcao do tempo juntamente e decaimento exponencial dos maximos";
    g8.SetTitle(s.c_str());
    c3->SaveAs("prob2_theta.pdf");
    cout << "energy lost by the system during [5.2,7.5]:  " <<rk4E[int(5.5/dt)]-rk4E[int(7.2/dt)] << "\n";
    return 0;
}