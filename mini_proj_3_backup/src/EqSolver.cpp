#include "EqSolver.hpp"
#include "FCmatrixAlgo.hpp"

using Eigen::Matrix;
using Eigen::Dynamic;

EqSolver::EqSolver() {
    M = Matrix<double, Dynamic, Dynamic>(0,0);
    C = Matrix<double, Dynamic, 1>(0);
} 

EqSolver::EqSolver(
        const Matrix<double, Dynamic, Dynamic>& M_, // Matrix Coefficients
        const Matrix<double, Dynamic, 1> & C_ // Matrix Constants
    ) : M(M_), C(C_) {;}

EqSolver::EqSolver(
        const Matrix<double, Dynamic, Dynamic>& M_, // Matrix Coefficients
        const Matrix<double, Dynamic, 1> & C_, // Matrix Constants
        const Matrix<double, Dynamic, 1>& P_ // Row order indexing
    ) : M(M_), C(C_), P(P_) {;}




//output


std::ostream& operator<<(std::ostream& os, const EqSolver& eq) {
    os << "M = \n" << eq.M << "\n";
    os << "C = \n" << eq.C << "\n";
    return os;
}




//solvers



const Matrix<double, Dynamic, 1>& EqSolver::GaussSolver(bool pivot) {
    FCmatrixAlgo solver;
    if (pivot) {
        solver.GaussEliminationPivot(M,C,P);
    } else {
        solver.GaussElimination(M,C);
    }
    return C;
}



void EqSolver::IterativeJacobiSolver(
        Matrix<double, Dynamic, 1>& x, //initial guess
        int& itmax, //max number of iterations
        double tol=1.E-3 //tolerance
    ) {
        FCmatrixAlgo solver;
        solver.IterativeJacobi(M,C,x,itmax,tol);
    }


void EqSolver::IterativeGaussSeidelSolver(
        Matrix<double, Dynamic, 1>& x, //initial guess
        int& itmax, //max number of iterations
        double tol=1.E-3 //tolerance
    ) {
        FCmatrixAlgo solver;
        solver.IterativeGaussSeidel(M,C,x,itmax,tol);
    }
