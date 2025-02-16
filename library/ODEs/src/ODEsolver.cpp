#include "ODEsolver.h"

ODEsolver::ODEsolver(const vector<function<double(ODEpoint)>>& F_) : F(F_){;}

void ODEsolver::SetODEfunc(const vector<function<double(ODEpoint)>>& F_) {
    F = F_;
}

const vector<ODEpoint>& ODEsolver::Euler(ODEpoint i, double step, double T){
    vector <ODEpoint> V;
    V.push_back(i); // create initial ODEpoint from whom we calculate the next
    while (V.back().T() < T){
        ODEpoint Pcur = V.back();
        V.push_back(Pcur+Func(Pcur)*step);
    }

    MS["euler"] = V;

    return MS["euler"];
}

const vector<ODEpoint>& ODEsolver::PredictorCorrector(ODEpoint i, double step, double T){
    vector <ODEpoint> V;
    V.push_back(i); // create initial ODEpoint from whom we calculate the next
    while (V.back().T() < T){
        ODEpoint Pcur = V.back();
        ODEpoint Ppred = Pcur+Func(Pcur)*step;
        V.push_back(Pcur+(Func(Pcur)+Func(Ppred))*0.5*step);
    }

    MS["trapezoidal"] = V;

    return MS["trapezoidal"];
}

const vector<ODEpoint>& ODEsolver::LeapFrog(ODEpoint i, double step, double T){
    vector <ODEpoint> V;
    V.push_back(i);
    int n = 0;
    ODEpoint P0 = V.back();
    ODEpoint P1 = P0+Func(P0)*step;
    V.push_back(P1);

    while (V.back().T() < T){
        ODEpoint Pprev = V[V.size()-2];
        ODEpoint Pcur = V.back();
        ODEpoint Pnext = Pprev+Func(Pcur)*2*step;
        V.push_back(Pnext);        
    }

    MS["leapfrog"] = V;

    return MS["leapfrog"];
}

const vector<ODEpoint>& ODEsolver::RK2(ODEpoint i, double step, double T){
    vector<ODEpoint> V;
    V.push_back(i);
    while(V.back().T() < T){
        ODEpoint Pcur = V.back();
	ODEpoint K1 = Func(Pcur)*step;
	ODEpoint K2 = Func(Pcur+K1*0.5)*step;
        V.push_back(Pcur+K2);
    }
    MS["rk2"] = V;
    return MS["rk2"];
}

const vector<ODEpoint>& ODEsolver::RK4(ODEpoint i, double step, double T){
    vector<ODEpoint> V;
    V.push_back(i);
    while(V.back().T() < T){
        ODEpoint Pcur = V.back();
	ODEpoint K1 = Func(Pcur)*step;
	ODEpoint K2 = Func(Pcur+K1*0.5)*step;
	ODEpoint K3 = Func(Pcur+K2*0.5)*step;
	ODEpoint K4 = Func(Pcur+K3)*step;
        V.push_back(Pcur+(K1+K2*2+K3*2+K4)*(1./6));
    }
    MS["rk4"] = V;
    return MS["rk4"];
}

ODEpoint ODEpoint::operator+(ODEpoint P){
	vector<double> var(x);
	for (int i = 0; i < var.size(); ++i) {
		var[i] += P[i];
	}
	return {time+P.time, var};
}

ODEpoint ODEpoint::operator*(double d){
	vector<double> var(x);
	for (int i = 0; i < var.size(); ++i) {
		var[i] *= d;
	}
	return {time*d, var};
}

ODEpoint ODEsolver::Func(ODEpoint P){
	ODEpoint P0(1, P.X());
	for (int i = 0; i < F.size(); ++i) {
		P0[i] = F[i](P);
	}
	return P0;
}

vector<ODEpoint> StormerVerlet(function<double(double, double)> f, ODEpoint pi, double step, double T){
	vector<ODEpoint> ret;
	double time = pi.T();
	ret.push_back(pi);
	double ym1 = pi[0] - step*pi[1] - step*step/2* f(time, pi[0]);
	double y1  = 2*pi[0] - ym1 + step*step* f(time, pi[0]) ;
	time+=step;
	ret.push_back({time, {y1, 0}});

	while(ret.back().T() < T){
		ym1 = 2*ret.back()[0] - ret[ret.size()-2][0] +step*step*f(time,ret.back()[0]);
		ret.back()[1] = (ym1-ret[ret.size()-2][0])/2/step;
		time+=step;
		ret.push_back({time, {ym1, 0}});
	}
	return ret;
}
