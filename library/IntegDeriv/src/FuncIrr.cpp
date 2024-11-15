#include "FuncIrr.hpp"
#include <cmath>
#include "TAxis.h"
#include "TSystem.h"
#include "TGraph.h"

FuncIrr::FuncIrr() : Functor("funcIrr"){cout << "create" <<endl;}

double FuncIrr::operator() (double x){
    return 100*25*sqrt(1/pow(x*x+y*y+25*25, 3))/(4*M_PI);
}
void FuncIrr::Draw(array<float, 2> range, int npoints, array<string, 2> titles){
    // Create a TCanvas if it doesn't exist
    if (!c) {
        c = new TCanvas("c", "canvas Functor", 1000, 1000);
        c->Draw(); // Ensure the canvas is drawn
    }

    // Create the histogram
    TF1 func("f", "100*25*sqrt(1/pow(x*x+[0]*[0]+25*25, 3))/(4*M_PI)", range[0], range[1]);
    func.SetParameter(0,y);
    func.SetNpx(npoints);

    // Set axis titles

    // Create a TGraph object to plot the function
    TGraph* graph = new TGraph(&func);


    // Set axis names
    graph->GetXaxis()->SetTitle(titles[0].c_str());
    graph->GetYaxis()->SetTitle(titles[1].c_str());

    graph->GetYaxis()->SetTitleOffset(1.2);


    // Draw the histogram on the canvas
    c->cd();
    graph->Draw();
    c->Update();

    c->SaveAs("f(x).png");
    
    // Clean up memory

    delete graph;

}

