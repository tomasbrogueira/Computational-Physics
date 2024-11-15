#include"Rwalk1D.hpp"
using namespace std;

std::minstd_rand Rwalk1D::R(time(0));
std::uniform_real_distribution<double> Rwalk1D::D(0.,1.0);

Rwalk1D::Rwalk1D(int n, double x, double pl, double pr,double dt_, double dx_)
:x0{x}, N{n}, pL{pl}, pR{pr}, dt{dt_}, dx{dx_}
{
	for (int i = 0; i < N; ++i) {
		mT.insert({i, vector<double>{x0}});
	}
}

void Rwalk1D::Run(int nsteps){
	for (int n = 0; n < nsteps; ++n) {
		for (int i = 0; i < N; ++i) {
			double stoch = D(R);
			if (stoch < pL) {
				mT[i].push_back(mT[i].back()-dx);
			}
			else if (stoch >= 1-pR) {
				mT[i].push_back(mT[i].back()+dx);
			}
			else{
				mT[i].push_back(mT[i].back());
			}
		}
	}
}
