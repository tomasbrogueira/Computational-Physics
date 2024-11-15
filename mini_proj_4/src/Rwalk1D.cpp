#include "Rwalk1D.hpp"


Rwalk1D::Rwalk1D(int N, double x, 
    double pL, double pR, 
    double dt, double dx 
    ) : x0(x), N(N), pL(pL), pR(pR), dt(dt), dx(dx) , gen(time(NULL)) {
    // initialize trajectories
    for (int i=0; i<N; i++) {
        mT[i].push_back(x0);
    }
}

void Rwalk1D::Run(int nsteps){
    
    for (int i = 0; i<nsteps; i++) {
        for (auto p :mT){
            double r = gen.Rndm(); //random beetween 0-1
            double x = p.second.back();

            if (r < pL) {
                x -= dx;
            } else if (r > pL){
                x += dx;
            }

            mT[p.first].push_back(x);
        }
    }
} 

const std::vector<double>& Rwalk1D::GetTrajectory(int n) {
    return mT[n];
}

double Rwalk1D::GetTimeStep() {
    return dt;
}
double Rwalk1D:: GetSpaceStep() {
    return dx;
}

TMultiGraph* Rwalk1D::GetGraph() {
    TMultiGraph* ans = new TMultiGraph;

    for (int i=1; i<= N ; i++) {
        TGraph* g = new TGraph;
        int j = 0;
        for (auto u : mT[i]){
            g->AddPoint(j*dt,u);
            j++;
        }
        g->SetLineColor(i+1);
        ans->Add(g);
    }

    ans->GetXaxis()->SetTitle("Time");
    ans->GetYaxis()->SetTitle("X");

    return ans;
}


