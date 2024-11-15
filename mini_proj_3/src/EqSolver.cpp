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
        const Matrix<int, Dynamic, 1>& P_ // Row order indexing
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
        double tol //tolerance
    ) {
        FCmatrixAlgo solver;
        solver.IterativeJacobi(M,C,x,itmax,tol);
    }


void EqSolver::IterativeGaussSeidelSolver(
        Matrix<double, Dynamic, 1>& x, //initial guess
        int& itmax, //max number of iterations
        double tol //tolerance
    ) {
        FCmatrixAlgo solver;
        solver.IterativeGaussSeidel(M,C,x,itmax,tol);
    }

const Eigen::Matrix<double, Dynamic, 1>& EqSolver::LUSolver(bool pivot) {

    Eigen::Matrix<int, Dynamic, 1> rowOrder (M.rows()); //Creating rowOrder as a column matrix

    //Filling rowOrder
    for(int i = 0; i < M.rows(); i++){
            rowOrder(i,0) = i;
    }

    FCmatrixAlgo::LUdecomposition(M, rowOrder, pivot);  // Performing LUdecomposition

    int numRows = M.rows();
    Matrix<double, Dynamic, 1> b2(M.rows());
    for (int i = 0; i < M.rows(); ++i) {
    	b2(rowOrder(i,0)) = C(i,0);
    }

    //Applying Gauss Elimination

    //Forward substitution
    for (int k = 0; k < numRows; k++){ 
        for (int i = 0; i < k; i++){
            b2(k) -= M(k, i)*b2(i);   // lower triangular part of the matrix
        }
    }

    // Backward substitution
    for (int k = numRows - 1; k >= 0; --k) {
        for (int j = k + 1; j < numRows; ++j) {
            b2(k) -= M(k, j) * b2(j); // upper triangular part of the matrix
        }
        b2(k) /= M(k, k);          
    }
    C = b2;
    return C;
}
