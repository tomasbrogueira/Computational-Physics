# ifndef ODEPOINT__HPP
# define ODEPOINT__HPP

#include <vector>
#include <iostream>

using namespace std;


class ODEpoint {

    public:
    ODEpoint(double time_, vector<double> var_) : time(time_) , var(var_) {;}

    const double& timeGetter();

    const vector<double>& varGetter();

    friend ostream& operator<<(ostream& os, const ODEpoint& p);

    protected:
    
    double time;
    vector<double> var;

};

# endif