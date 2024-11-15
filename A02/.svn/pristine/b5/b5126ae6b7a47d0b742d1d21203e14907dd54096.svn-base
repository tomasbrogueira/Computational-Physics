#ifndef __EQSOLVER_H__
#define  __EQSOLVER_H__
#include <fstream>
using namespace std;

#include "eigen3/Eigen/Dense"
#include "FCmatrixAlgo.h"
using namespace Eigen;


class EqSolver {
    public:
        // Constructors and destructor
        EqSolver();
        EqSolver(const Matrix<double,Dynamic,Dynamic>&, // Coefficients matrix
                const Matrix<double,Dynamic,1>&); // Constants vector
        ~EqSolver() = default;

        // output 
        friend ostream& operator<<(ostream&, const EqSolver&);

        // solvers
        const Matrix<double,Dynamic,1>& GaussSolver(bool pivot=false);

        const Matrix<double,Dynamic,1>& LUSolver(bool pivot=false);
        
        void IterativeJacobiSolver(Matrix<double,Dynamic,1>&, // Initial/starting solution
                                int& itmax, //Number of max iterations
                                double tol = 1.E-3); // Tolerance on convergence

        void IterativeGaussSeidelSolver(Matrix<double,Dynamic,1>&, int& itmax, double tol = 1.E-3);
        void IterativeRelaxation(Matrix<double,Dynamic,1>&, int& itmax, double tol = 1.E-3);
    
    private:

    Matrix<double,Dynamic,Dynamic> M; // Coefficients matrix
    Matrix<double,Dynamic,1> b; // Constants vector
    
    bool DiagonallyDominant();		// test if system is Diagonally Dominant
};
#endif // ifndef __EQSOLVER_H__
