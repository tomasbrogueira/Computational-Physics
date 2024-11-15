#ifndef Rwalk1D_hpp
#define Rwalk1D_hpp

#include <map>
#include <vector>
#include "TMultiGraph.h"
#include "TGraph.h"
#include "TRandom.h"
#include "TAxis.h"
#include "ctime"

class Rwalk1D{

    public:

    Rwalk1D(int N=1, double x=0., // N=nb of particles, x=x(0)
    double pL=0.5, double pR=0.5, // probabilities Left Right
    double dt=1, double dx=1 // time and space steps
    );

    ~Rwalk1D() = default;

    // particle simulation

    void Run(int nsteps); // number of steps

    // getters

    const std::vector<double>& GetTrajectory(int n=1); // particle number

    double GetTimeStep();
    double GetSpaceStep();


    // graph

    TMultiGraph* GetGraph(); 



    private:

    double x0; // initial coo
    int N; // number of particles
    
    double pL, pR; // probabilities (left,same,right)
    double dt, dx; // steps (time,space)

    std::map<int,std::vector<double> > mT; // trajectories
    TRandom gen; // random generator
};

#endif 