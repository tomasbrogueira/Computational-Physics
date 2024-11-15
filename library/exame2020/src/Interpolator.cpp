#include"Interpolator.hpp"
#include"EqSolver.hpp"
#include<cmath>


using namespace std;

vector<double> Interpolator(const vector<pair<double, double>>& p){
	MCoef M(p.size(), p.size());
	MConst b(p.size());
	for (int i = 0; i < p.size(); ++i) {
		for (int j = 0; j < p.size(); ++j) {
			M(i,j) = pow(p[i].first,j);
		}
		b(i) = p[i].second;
	}
	EqSolver S(M, b);
	MConst sol = S.GaussSolver(true);
	vector<double> ret;
	for(auto coef : sol){
		ret.push_back(coef);
	}
	return ret;
}

function<double(double)> Coef2Func(const vector<double>& coef){
	return [coef](double x){
	double sum =0;
	for (int i = 0; i < coef.size(); i++) {
		sum += coef[i] * pow(x,i);
	}
	return sum;
	};
}
