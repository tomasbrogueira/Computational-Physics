#include<iostream>
#include<vector>
#include<string>
#include"../src/RootSolver.h"
#include<cmath>
# include "TGraph.h"
# include "TCanvas.h"
# include "TAxis.h"
using namespace std;


/*
Example
solve x^3 + y^4 = 5; x^2 +y^3=5
*/

auto F1 = [](MatrixXd x){
    return pow(x(0,0),3)+pow(x(1,0),4)-5;
};
auto F2 = [](MatrixXd x){
    return pow(x(0,0),2)+pow(x(1,0),3)-5;
};

int main(){
    vector<function<double(MatrixXd)>> vF = {F1,F2};
    vector<double> pi={-1,1.5};
    RootSolver rs = RootSolver(vF);
    vector<double> ans = rs.find_root(pi,10e-10);
    cout << ans[0] << "  " << ans[1] << "\n";

    return 0;
}