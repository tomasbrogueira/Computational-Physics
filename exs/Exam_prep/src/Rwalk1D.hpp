#ifndef __RWALK1D
#define __RWALK1D value

#include<vector>
#include<map>
#include<random>
#include<ctime>



class Rwalk1D {
	public:
		Rwalk1D(int n=1, double x=0., // N=nb of particles, x=x(0)
				double pl=0.5, double pr=0.5, // probabilities Left Right
				double dt_=1, double dx_=1 // time and space steps
		       );
		~Rwalk1D() = default;
		// particle simulation
		void Run(int nsteps); // number of steps
	        // getters
		const std::vector<double>& GetTrajectory(int n=1){return mT[n];} // particle number
		double GetTimeStep(){return dt;}
		double GetSpaceStep(){return dx;}

	private:
		double x0; // init coo
		int N; // number of particles
		double pL, pR; // probabilities (left, same, righ)
		double dt, dx; // steps (time, space)
		std::map<int, std::vector<double> > mT; // trajectories
		static std::minstd_rand R;
		static std::uniform_real_distribution<double> D;
};

#endif /* ifndef __RWALK1D */
