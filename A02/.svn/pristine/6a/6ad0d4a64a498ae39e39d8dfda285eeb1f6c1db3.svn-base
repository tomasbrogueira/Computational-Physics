#include "Func1.h"
#include <cmath>
#include "TAxis.h"
#include "TSystem.h"
#include "TGraph.h"

Func1::Func1() : Functor("func1"){;}

double Func1::operator() (double x){
    return x*x*x*x*log(x+sqrt(x*x+1));
}
void Func1::Draw(array<float, 2> range, int npoints, array<string, 2> titles){
    // Create a TCanvas if it doesn't exist
    if (!c) {
        c = new TCanvas("c", "canvas Functor", 1000, 1000);
        c->Draw(); // Ensure the canvas is drawn
    }

    // Create the histogram
    TF1 func("f", "x*x*x*x*log(x+sqrt(x*x+1))", range[0], range[1]);
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

