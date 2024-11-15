#include "Functor.hpp"

TCanvas* Functor :: c = new TCanvas("c", "c", 800, 600);

double Functor :: operator() (double x){
    return 0;
}


void Functor :: Draw(double xi, double xf, int num, std::string xtitle, std::string ytitle){
    
    TGraph *g = new TGraph(num);
    g->SetTitle(name.c_str());
    g->GetXaxis()->SetTitle(xtitle.c_str());
    g->GetYaxis()->SetTitle(ytitle.c_str());

    double dx = (xf-xi)/num;

    for (int i=0; i<num; i++){
        double x = xi + i*dx;
        double y = (*this)(x);
        g->SetPoint(i,x,y);
    }

    g->Draw("APL");
    c->Draw();

    c->SaveAs((name+".png").c_str());
}


