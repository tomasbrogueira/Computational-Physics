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
    double theta1;
    auto integrand = [&theta1](double x){
        return 1/sqrt(1-sin(theta1)*sin(theta1)*sin(x)*sin(x));
    };
    double integral,error,l1=5,g=9.8;
    Functor f("good",integrand);
    IntegDeriv algs(f);
    vector<double>x,y;
    //compute an integral approximation with Simpsons rule
    cout << "Simple pendulum period approximation using Simpsons rule with 10000 points, guaranteeing better than 10^-3 relative accuracy\n";
    for(int theta=1; theta<90; theta+=4){
        theta1 = theta*(M_PI/180.);
        algs.simpsonRule(0,M_PI_2,integral,error,10000);
        x.push_back(theta1*(180./M_PI));//Ângulos em graus
        y.push_back(4*sqrt(l1/g)*integral); //período em segundos
        cout << error << "\n\n";
    }
    TCanvas* c = new TCanvas("canvas","canvas", 1200,1000);
    TGraph* gr = new TGraph(x.size(),x.data(),y.data());
    string s = "Periodo(s) em funcao do angulo de abandono do pendulo";
    gr->SetTitle(s.c_str());
    gr->Draw("AL");
    c->Update();
    c->SaveAs("prob1a_periodo.pdf");
    return 0;
}