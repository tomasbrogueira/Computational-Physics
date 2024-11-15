#ifndef __MYFUNCTION__
#define __MYFUNCTION__

#include "Functor.hpp"
#include <cmath>

class MyFunction : public Functor {

    public:
    MyFunction(std::string s ="MyFunction") : Functor(s) {;}
    ~MyFunction() = default;

    double operator()(double x) {
        //implement function f(x) =x^4log(x+sqrt(x^2+1))
        return pow(x,4)*log(x+sqrt(pow(x,2)+1));
    }

};

#endif