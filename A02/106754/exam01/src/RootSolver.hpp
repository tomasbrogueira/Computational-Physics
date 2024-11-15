#include<iostream>
#include<string>
#include<vector>
#include<functional>
#include<cmath>
#include"FCmatrixAlgo.hpp"
#include<utility>

using namespace std;
using namespace Eigen;

class RootSolver{
public:
RootSolver(vector<function<double(MatrixXd)>> F_): F(F_){;}
~RootSolver()=default;

vector<double> find_root(vector<double>&pi,double h,double tol=10e-5);
private:
vector<function<double(MatrixXd)>> F;

};