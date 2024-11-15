#include"Interpolator.hpp"
#include"EqSolver.h"
#include"Functor.hpp"
#include<cmath>
#include<iostream>
#include<string>




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

vector<double> Interpolator(const vector<pair<double, double>>& p, const vector<pair<double, double>>& d){
	MCoef M(p.size()+d.size(), p.size()+d.size());
	MConst b(p.size()+d.size());
	for (size_t i = 0; i < p.size(); ++i) {
		for (int j = 0; j < p.size()+d.size(); ++j) {
			M(i,j) = pow(p[i].first,j);
		}
		b(i) = p[i].second;
	}
	for (size_t i =0; i < d.size(); ++i) {
		M(i+p.size(),0)=0;
		for (int j = 1; j < p.size()+d.size() ; ++j) {
			M(i+p.size(),j) = j*pow(d[i].first,j-1);
		}
		b(i+p.size()) = d[i].second;
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
	return [coef](double x)->double{
	double sum =0;
	for (int i = 0; i < coef.size(); i++) {
		sum += coef[i] * pow(x,i);
	}
	return sum;
	};
}

function<double(double)> SPline(const vector<pair<double, double>>& p){

	if(p.size() < 5)	// if not ehough points to separate
		return Coef2Func(Interpolator(p));

	vector<function<double(double)>> F;
	vector<double> coef;
	size_t i;
	vector<double> points;

	F.push_back(Coef2Func(coef = Interpolator({p.begin(), p.begin()+4})));

	for (i = 0; i < (p.size()-4)/2; ++i) {
		double derivative = 0;
		pair<double, double> point = *(p.begin()+3+2*i);
		points.push_back(point.first);
		for (size_t j = 1; j < 4; ++j) {
			derivative +=  pow(point.first, j-1) * j * coef[j];
		}
		F.push_back(Coef2Func(coef = Interpolator({p.begin()+3+2*i, p.begin()+3+2*(i+1)+1}, {{point.first, derivative}})));
	}

	if(p.size()%2 == 0){
		double derivative = 0;
		pair<double, double> point = *(p.begin()+3+2*i);
		for (size_t j = 1; j < 4; ++j) {
			derivative +=  pow(point.first, j-1) * j * coef[j];
		}
		F.push_back(Coef2Func(coef = Interpolator({p.begin()+3+2*i, p.end()}, {{point.first, derivative}})));
	}

	return [F, points](double x)->double{
		for (size_t i = 0; i < points.size(); ++i) {
			if(x < points[i])
				return F[i](x);
		}	
		return F.back()(x);	
	};
	
}
