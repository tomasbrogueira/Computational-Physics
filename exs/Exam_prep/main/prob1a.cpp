#include "IntegDeriv.hpp"
#include "ROOTplotter.hpp"

#include <cmath>

using namespace std;

int main () {

    const double l = 5, g = 9.8; // fio (m) , acelaracao gravit (m/s^2), angulo inicial (rad)
    
    ROOTplotter plotter;

    vector<double> A, T; 

    int numPoints = 1000;

    for (double a = M_PI/180 ; a < M_PI/2 ; a +=  (4*M_PI)/180 ) {
        Functor f("Periodo",[=](double x){return 4*sqrt(l/g)/sqrt(1-sin(a/2)*sin(a/2)*sin(x)*sin(x)) ;});
        double integ, err;
        IntegDeriv F_ID(f);

        F_ID.TrapezoidalRule(0,M_PI/2 ,integ, err , numPoints);
        
        A.push_back(a*180/M_PI);
        T.push_back(integ);
    }

    cout << "using Trapezoidal" << endl;

    cout << "periodos de acordo com angulo inicial:" << endl;

    for (auto t : T) {
        cout << t << endl;
    }  

    vector<vector<string>> labels = {{"Period by angle","Init angle (degrees)","Period (s)"}};

    TCanvas* C = plotter.PlotMultipleGraphs({A}, {T}, labels);

    C->SaveAs("Periodo.pdf");
}