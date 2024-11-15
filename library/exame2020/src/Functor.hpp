#ifndef __FUNCTOR__
#define __FUNCTOR__

#include <string>
#include <array>
#include<functional>

using namespace std;
#include "TCanvas.h"
class Functor {
    public:
        Functor(string s, function<double(double)> f_);
        ~Functor() = default;
        double operator()(double x);
        
        void Draw(array<float, 2> range, int npoints, array<string, 2> titles);

    protected:
        static TCanvas *c;
        string name;
	function<double(double)> f;
};

#endif
