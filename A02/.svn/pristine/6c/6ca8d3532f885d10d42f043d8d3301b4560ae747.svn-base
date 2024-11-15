#include "Functor.hpp"
#include "ROOTplotter.hpp"
#include "IntegDeriv.hpp"
#include "ODEsolver.hpp"

#include <cmath>

using namespace std;

int main () {

    const double V = 10, R = 25 , Cap = 4; // diferenca de potencial , resistencia, capacidade condensador

    //funcao    
    
    Functor f("Corrente",[=](double t){return V/(exp(t/(R*Cap))*R);});
    
    // alinea a.
    
    vector<double> I, T; // corrente, tempo
    
    /*escolhi um dt arbitrario de 1 seg uma vez que sao 400s no total parece razoavel,
      o gráfico confirama que foi uma escolha decente uma vez que é "suave"  */ 
    for (int i = 0 ; i<=400 ; i++) {
        T.push_back(i);
        I.push_back(f(i));
    }

    
    // plot com a classe ROOTplotter

    ROOTplotter plotter;

    vector<vector<string>> labels_current = {{"Current by time","Time (s)","Current (A)"}};

    TCanvas* C = plotter.PlotMultipleGraphs({T},{I},labels_current);
    C->SaveAs("Exam01_a.pdf");


    // alinea b.


    IntegDeriv F_ID(f);



    // aplicar a mid-rule a 100 intervalos de 2 segundos (mudei no integderiv.cpp as fatias)

    double Integral,Error;

    double ti = 0 , tf = 200;
    
    F_ID.MidRule(ti,tf,Integral,Error);

    

    // resposta à pergunta b.

    cout << "Q(200) 100 fatias = " << Integral << endl;
    
   
   
    // resposta à pergunta c.


    cout << "Mid-rule Error  100 fatias = " << Error << endl;





    // alinea d.

    
    // ponto inicial

    ODEpoint P0(0,{0}); // time (s) , Q (C)

    
    // funcoes definidas para o ODEsolver receber

    vector<std::function<double(ODEpoint)>> functions {
        [=](ODEpoint P)->double {return V/(exp(P.T()/(R*Cap))*R);}, // dQ/dt
    };


    
    ODEsolver S(functions);
    
    double dt = 0.01, Tmax = 500; // step e tempo max (s)
    vector<ODEpoint> Trapezoid = S.PredictorCorrector(P0,dt,Tmax); // resolver usando o metodo trapezoidal


    // criar vetores para dar plot aos resultados

    vector<double> T1,Q1;

    for (auto p : Trapezoid) {
        T1.push_back(p.T());
        Q1.push_back(p[0]);
    }

    // resposta a alinea d.
    cout << "Q(500) = " << Q1.back() << endl;


    // criar o plot da alinea d.
    
    vector<vector<string>> labels_charge = {{"Charge over time","Time (s)","Charge (C)"}};
    C = plotter.PlotMultipleGraphs({T1},{Q1},labels_charge);
    
    C->SaveAs("Exam01_d.pdf");
}