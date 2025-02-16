#include "FCmatrixAlgo.h"
#include "EqSolver.h"
#include <iostream>

int main(){

    // Creating matrices A and b
        
    Eigen::MatrixXd A(4, 4);

    A << 80., -30., -50., 0.,
         -30., 65., -10., -20.,
         -50., -10., 100., -25.,
          0., -20., -25., 100.;

    Eigen::MatrixXd b(4, 1);

    b <<   20.,
            0.,
            0.,
            0.;

    EqSolver S1(A, b);     // Creating EqSolver object for our system
    
    auto X = S1.GaussSolver();    // Gauss Solution (without pivoting)
    std::cout<<"Gauss Solution: \n"<<X.transpose()<<std::endl;

    EqSolver S5(A, b);     // Creating EqSolver object for our system
    auto X_p = S5.GaussSolver(true);    // Gauss Solution (pivoting)
    std::cout << "Gauss Solution (pivoting): \n" << X_p.transpose() << std::endl;

    EqSolver S2(A, b);    // Creating another EqSolver object
    
    auto Y = S2.LUSolver(); // Doolitle decomposition
    std::cout<<"LU Solution: \n"<<Y.transpose()<<std::endl;

    EqSolver S3(A, b);    // Creating another EqSolver object

    auto Y_p = S3.LUSolver(true);    // Doolitle decomposition (pivoting)
    std::cout << "LU Solution (pivoting): \n" << Y_p.transpose() << std::endl;
    
    EqSolver S4(A, b);    // Creating another EqSolver object

    // Creating a matrix with initial (random) solutions
    // Creating a matrix with initial (random) solutions
    Eigen::Matrix<double, Dynamic, 1> guess1(4,1);
    guess1 <<100,-900,50,-80;

    int max_iter = 900;
    S4.IterativeJacobiSolver(guess1, max_iter);  // Solution using Jacobi iterative method
    std::cout << "Jacobi iteration solution: \n" << guess1.transpose() << " Iterattions:"<< max_iter << std::endl;

    Eigen::Matrix<double, Dynamic, 1> guess2(4,1);
    guess2 <<100,-900,50,-80;
    max_iter = 900;
    S4.IterativeGaussSeidelSolver(guess2, max_iter);     // Solution using Gauss-Seidel iterative method
    std::cout << "Gauss-Seidel iterative solution: \n" << guess2.transpose() << " Iterattions:"<< max_iter << std::endl;
    
    Eigen::Matrix<double, Dynamic, 1> guess3(4,1);
    guess3 <<100,-900,50,-80;
    max_iter = 900;
    S4.IterativeRelaxation(guess3, max_iter);     // Solution using Gauss-Seidel iterative method
    std::cout << "Relaxation iterative solution: \n" << guess3.transpose() << " Iterattions:"<< max_iter << std::endl;

    MCoef R(4, 4);

    R << 80., -30., -50., 0.,
         -50., -10., 100., -25.,
         -30., 65., -10., -20.,
          0., -20., -25., 100.;
    MCoef R2(R);

    auto inverted = FCmatrixAlgo::Invert(R);
    cout << inverted <<endl;
    cout << R2*inverted << endl;

}
