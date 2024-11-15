#include "Functor.hpp"

TCanvas* Functor::c = nullptr;

Functor::Functor(string name_) : name(name_){
    c = new TCanvas("c", "canvas Functor", 1000, 1000);
}

double Functor::operator() (double x){return 0.;};

void Functor::Draw(array<float, 2> range, int npoints, array<string, 2> titles) {};
