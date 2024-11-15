#ifndef __FUNCTOR__
#define __FUNCTOR__


#include <string>

#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"

class Functor {

    public:

    Functor(std::string s="Functor") : name(s) {;}
    ~Functor() = default;

    virtual double operator()(double x);

    //args:
    // xi, xf : xmin and xmax of the plot
    // num : number of points to plot
    // xtitle, ytitle : title of the axis

    virtual void Draw(double xi, double xf, int num, std::string xtitle="x", std::string ytitle="y");

    protected:
    static TCanvas *c;
    std::string name;

};


#endif