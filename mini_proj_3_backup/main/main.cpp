#include "EqSolver.hpp"
#include "FCmatrixAlgo.hpp"
#include <iostream>


int main() {

    double R1 = 30;
    double R2 = 50;
    double R3 = 5;
    double R4 = 10;
    double R5 = 15;
    double R6 = 20;
    double R7 = 25;
    double R8 = 55;
    double V0 = 20;

    // define matrix equations: Ax = b
    Matrix<double, Dynamic, Dynamic> A; A.resize(4,4);
    A << R1+R4+R6, -R4, -R6, 0,
        -R4, R2+R4+R5, -R5, 0,
        -R6, -R5, R5+R6+R7+R8, -R8,
        0, 0, -R8, R3+R8;
    
    Matrix<double, Dynamic, 1> b; b.resize(3);
    b << V0, 0, 0, 0;

    Matrix<double, Dynamic, 1> P; P.resize(4);
    P << 0, 1, 2, 3;


    // define solver
    EqSolver eq(A,b);

    // solve using Gauss Elimination
    std::cout << "Gauss Elimination: \n";
    std::cout << eq.GaussSolver() << "\n";


    // solve using Jacobi Iterative method
    std::cout << "Jacobi Iterative method: \n";
    Matrix<double, Dynamic, 1> x(3);
    x << 0, 0, 0;
    int itmax = 100;
    double tol = 1.E-3;
    eq.IterativeJacobiSolver(x, itmax, tol);
    std::cout << x << "\n";

    // solve using Gauss-Seidel Iterative method
    std::cout << "Gauss-Seidel Iterative method: \n";
    x << 0, 0, 0;
    eq.IterativeGaussSeidelSolver(x, itmax, tol);
    std::cout << x << "\n";

    return 0;
}