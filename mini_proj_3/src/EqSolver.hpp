#ifndef __EqSolver_HPP__
#define __EqSolver_HPP__

#include <eigen3/Eigen/Dense>
#include <iostream>
#include <ostream>


using Eigen::Matrix;
using Eigen::Dynamic;

class EqSolver {
    public:
    EqSolver();
    EqSolver(
        const Matrix<double, Dynamic, Dynamic>& M_, // Matrix Coefficients
        const Matrix<double, Dynamic, 1> & C_ // Matrix Constants
    );

    EqSolver(
        const Matrix<double, Dynamic, Dynamic>& M_, // Matrix Coefficients
        const Matrix<double, Dynamic, 1> & C_, // Matrix Constants
        const Matrix<int, Dynamic, 1>& P_ // Row order indexing
    );


    ~EqSolver() = default;

    //output
    friend std::ostream& operator<<(std::ostream& os, const EqSolver& eq);

    //solvers

    const Matrix<double, Dynamic, 1>& GaussSolver(bool pivot=false);


    void IterativeJacobiSolver(
        Matrix<double, Dynamic, 1>& x, //initial guess
        int& itmax, //max number of iterations
        double tol=1.E-3 //tolerance
    );

    void IterativeGaussSeidelSolver(
        Matrix<double, Dynamic, 1>& x, //initial guess
        int& itmax, //max number of iterations
        double tol=1.E-3 //tolerance
    );
        const Matrix<double,Dynamic,1>& LUSolver(bool pivot=false);


    private:
    Matrix<double, Dynamic, Dynamic> M; // Matrix Coefficients
    Matrix<double, Dynamic, 1> C; // Matrix Constants
    Matrix<int, Dynamic, 1> P; // Row order indexing
};

#endif // __EqSolver_HPP__
