# include "ROOTplotter.hpp"
# include <iostream>

using namespace std;

int main() {
    ROOTplotter RP;
    
    vector<vector<double>> X = {
        {1, 2, 3, 4},
        {1, 2, 3, 4}
    };

    vector<vector<double>> Y = {
        {1, 2, 3, 4},
        {1, 4, 9, 16}
    };

    vector<vector<string>> labels = {
        {"Title 1", "Xlabel 1", "Ylabel 1"},
        {"Title 2", "Xlabel 2", "Ylabel 2"}
    };

    TCanvas* C = RP.PlotMultipleGraphs(X, Y, labels, true); // Plot 2 graphs side by side
    C->SaveAs("test1.png");

    C = RP.PlotFunction([](double x){return x*x;}, 0, 10, {"Title", "Xlabel", "Ylabel"}); // Plot the function x^2
    C->SaveAs("test2.png");

    vector<vector<double>> Z = {
        {1, 2, 3, 4},
        {1, 2, 3, 4},
        {1, 2, 3, 4},
        {1, 4, 9, 16}
    };

    vector<string> labels2 = {
        "Title", "Xlabel", "Ylabel", "POWERRR"
    };

    C = RP.Plot2DHistogram(Z, labels2, 0, 20, 0, 20); // Plot a 2D histogram
    C->SaveAs("test3.png");

    /*
    PLOT A ODE FUNCTION GRAPH
    */

    // Define ODEs
    vector<function<double(ODEpoint)>> F = {
        [](ODEpoint p){return cos(p.T()) - p[1];},
        [](ODEpoint p){return sin(p.T()) + p[0];}
    };

    ODEpoint p0(0, {0, 0}); // Initial conditions
    ODEsolver S(F); // Create ODEsolver object

    double dt = 0.1, T = 2.0;
    S.RK4(p0, dt, T);

    vector<double> rk4x, rk4y, rk4z;

    for (auto p : S.GetODEpoints("rk4")) {
        rk4x.push_back(p.T());
        rk4y.push_back(p[0]);
        rk4z.push_back(p[1]);
    }

    X = {rk4x, rk4x};
    Y = {rk4y, rk4z};
    labels = {
        {"RK4 y", "x", "y"},
        {"RK4 z", "x", "z"}
    };

    C = RP.PlotMultipleGraphs(X, Y, labels, true); // Plot 2 graphs side by side
    C->SaveAs("test4.png");

    C = RP.PlotMultipleGraphsSamePad(X, Y, labels); // Plot 2 graphs in the same pad
    C->SaveAs("test5.png");
    return 0;
}