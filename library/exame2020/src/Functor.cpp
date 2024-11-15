#include "Functor.hpp"
#include<TF1.h>
#include<TGraph.h>
#include<TAxis.h>


TCanvas* Functor::c = nullptr;

Functor::Functor(string name_, function<double(double)> f_) : name(name_), f(f_){
    c = new TCanvas("c", "canvas Functor", 1000, 1000);
}

double Functor::operator() (double x){return f(x);};

void Functor::Draw(array<float, 2> range, int npoints, array<string, 2> titles) {
    std::function<double(const double*, const double*)> F = [this](const double*x, const double*p){return f(x[0]);};
    TF1 func(name.c_str(), F, range[0], range[1]);
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

    c->SaveAs((name+".png").c_str());
    
    // Clean up memory

    delete graph;
};
