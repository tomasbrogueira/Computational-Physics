#ifndef FCMATRIXALGO_HPP
#define FCMATRIXALGO_HPP


#include <Eigen/Core>



//using Eigen::MatrixXd
using Eigen::Matrix;
using Eigen::Dynamic;

class FCmatrixAlgo {

    public:
    FCmatrixAlgo() = default;
    ~FCmatrixAlgo() = default;

    // Gaussian Elimination

    static void GaussElimination(
        Matrix<double, Dynamic, Dynamic>& M, // Matrix Coefficients
        Matrix<double, Dynamic, 1> & C // Matrix Constants
    );
    
    static void GaussEliminationPivot(
        Matrix<double, Dynamic, Dynamic>& M, // Matrix Coefficients
        Matrix<double, Dynamic, 1> & C, // Matrix Constants
        Matrix<double, Dynamic, 1>& P // Row order indexing
    );
    
    // LU Decomposition

    static void LUdecomposition(
        Matrix<double, Dynamic, Dynamic>& M, // Matrix Coefficients
        Matrix<int, Dynamic, 1> & P, // Pivot indexing
        bool bpivot  // has pivoting?
    );

    static void IterativeJacobi(
        Matrix<double, Dynamic, Dynamic>& M, // Matrix Coefficients
        Matrix<double, Dynamic, 1> & C, // Matrix Constants
        Matrix<double, Dynamic, 1>& x, //initial guess
        int& itmax, //max number of iterations
        double& tol //tolerance
    );
    
    static void IterativeGaussSeidel(
        Matrix<double, Dynamic, Dynamic>& M, // Matrix Coefficients
        Matrix<double, Dynamic, 1> & C, // Matrix Constants
        Matrix<double, Dynamic, 1>& x, //initial guess
        int& itmax, //max number of iterations
        double& tol //tolerance
    );

};

#endif // FCMATRIXALGO_HPP