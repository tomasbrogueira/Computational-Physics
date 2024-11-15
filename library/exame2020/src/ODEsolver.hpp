#ifndef __ODESOLVER__
#define __ODESOLVER__

#include <iostream>
#include <vector>
#include <functional>
#include "ODEpoint.hpp"
#include <map>
#include<string>
using namespace std;

class ODEsolver {
    public:
        ODEsolver(const vector<function<double(ODEpoint)>>&);
        ~ODEsolver() = default;

        // set functions
        void SetODEfunc(const vector<function<double(ODEpoint)>>&);
        //getters
        vector<ODEpoint>& getODEpoints(string s){return MS[s];}
        // solver methods
        const vector<ODEpoint>& Euler(ODEpoint i, double step, double T);
        const vector<ODEpoint>& PredictorCorrector(ODEpoint i, double step,
        double T);
        const vector<ODEpoint>& LeapFrog(ODEpoint i, double step, double T);
        const vector<ODEpoint>& RK2(ODEpoint i, double step, double T);
        const vector<ODEpoint>& RK4(ODEpoint i, double step, double T);

    private:
	ODEpoint Func(ODEpoint);
        vector<std::function<double(ODEpoint)>> F;
        map<string, vector<ODEpoint> > MS; // key: "euler", "trapezoidal", "leapfrog, "rk2", "rk4"
};

#endif

