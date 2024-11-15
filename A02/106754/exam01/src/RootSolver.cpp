#include"RootSolver.hpp"

double central_partial(int j,MatrixXd x, double h,function<double(MatrixXd)> F){
    MatrixXd x_plus,x_minus;
    x_plus = x_minus = x;
    //apply a variation of h to the j-th coordinate of F
    x_plus(j,0)+=h;x_minus(j,0)-=h;
    //compute the partial derivative of F wrt j using the central difference approximation
    return (F(x_plus)-F(x_minus))/(2*h);
}

double snorm(MatrixXd x,vector<function<double(MatrixXd)>> F){
    double s=0,eval;
    for(int i=0; i< x.rows();i++){
        eval = F[i](x);
        s += eval*eval;
    }
    return s;
}

vector<double> RootSolver::find_root(vector<double>& pi,double h,double tol){
    MatrixXd M(pi.size(),pi.size()),fx(pi.size(),1);
    MatrixXd p_next = MatrixXd(pi.size(),1),inv,p_curr;
    for(int i=0; i < pi.size();i++){
            p_next(i,0) = pi[i];
        }
    int i=1;
    while(snorm(p_next,F)>tol && i<=200){
        cout << "squared distance from 0:  "<<snorm(p_next,F) << "\n";
        p_curr = p_next;

        for(int i=0; i < pi.size();i++){
            for(int j=0; j < pi.size();j++){
                M(i,j) = central_partial(j,p_curr,h,F[i]);
            }
            fx(i,0)=F[i](p_curr);
        }
        inv = FCmatrixAlgo().Invert(M);
        p_next = p_curr - inv*fx;
        i++;
    }
    cout << "squared distance from 0:  "<<snorm(p_next,F) << "\n";
    vector<double> res;
    for(int i=0; i< pi.size();i++){
        res.push_back(p_next(i,0));
    }
    return res;


}