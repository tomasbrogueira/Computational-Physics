#include "EqSolver.hpp"
#include <iostream>

EqSolver::EqSolver(){} // Default constructor

EqSolver::EqSolver(const Matrix<double,Dynamic,Dynamic>& matrixA, 
const Matrix<double,Dynamic,1>& matrixb) : M(matrixA), b(matrixb) {} // Create coefficients matrix and constants vector

ostream& operator<<(ostream& os, const EqSolver& solver){
    os << "Matrix A: \n" << solver.M << endl;
    os << "Matrix b: \n" << solver.b << endl;
    return os;
}

const Eigen::Matrix<double,Eigen::Dynamic,1>& EqSolver::GaussSolver(bool pivot){
    
    if (pivot){
        // Perform Gaussian elimination with pivoting
        Matrix<int, Dynamic, 1> rowOrder(M.rows());
        for(int i = 0; i < M.rows(); i++){
            rowOrder(i,0) = i;
        }
        FCmatrixAlgo::GaussEliminationPivot(M, b, rowOrder);
	std::cout << "Row Order: " << rowOrder.transpose() << std::endl;
    }

    else{
        // Perform Gaussian elimination without pivoting
        FCmatrixAlgo::GaussElimination(M, b);
    }
    return b;
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
    	b2(rowOrder(i,0)) = b(i,0);
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
    b = b2;
    return b;
}
 

void EqSolver::IterativeJacobiSolver(Eigen::Matrix<double, Eigen::Dynamic, 1>& initialSolution,
                                     int& maxIterations,
                                     double tolerance){
                                        
    int numRows = M.rows();
    int iteration = 0;
    double maxDiff = tolerance;   
    Eigen::Matrix<double, Eigen::Dynamic, 1> currentSolution = initialSolution;   
    Eigen::Matrix<double, Eigen::Dynamic, 1> previousSolution = initialSolution; 
    
    if(!DiagonallyDominant())
	cerr << "JacobiSolver: Matrix not Diagonally Dominant, may not converge" <<endl;

    for (iteration = 0; iteration < maxIterations; ++iteration){
        for (int i = 0; i < numRows; i++) {	// Jacobi iteration
            double sum = 0.0;
            for (int j = 0; j < numRows; j++) 
                if (j != i)  sum += M(i,j) * previousSolution(j);    

            if (M(i, i) != 0)
                currentSolution(i) = (b(i) - sum) / M(i, i);     // Update the current solution 
            else 
                currentSolution(i) = 0.0;   // prevent divide by 0
        }

        maxDiff = (currentSolution - previousSolution).cwiseAbs().maxCoeff();    // maximum deviation
        
        if (maxDiff < tolerance) break;  // Convergence reached
        
        previousSolution = currentSolution; // Update the previousSolution vector between each iteration
    }

    if(maxDiff > tolerance)
	    cerr << "JacobiSolver didn't converge" <<endl;
    maxIterations = iteration;          
    initialSolution = currentSolution;  
}

void EqSolver::IterativeGaussSeidelSolver(Eigen::Matrix<double, Eigen::Dynamic, 1>& initialSolution,
                                         int& maxIterations,
                                         double tolerance) {
    int numRows = M.rows();
    int iteration = 0;
    double maxDiff = tolerance;   
    Eigen::Matrix<double, Eigen::Dynamic, 1> currentSolution = initialSolution;   
    
    if(!DiagonallyDominant())
	cerr << "GaussSeidelSolver: Matrix not Diagonally Dominant, may not converge" <<endl;

    for (iteration = 0; iteration < maxIterations; ++iteration){
        for (int i = 0; i < numRows; i++) {	// Jacobi iteration
            double sum = 0.0;
            for (int j = 0; j < numRows; j++) 
                if (j != i)  sum += M(i,j) * currentSolution(j);    

            if (M(i, i) != 0)
                currentSolution(i) = (b(i) - sum) / M(i, i);     // Update the current solution 
            else 
                currentSolution(i) = 0.0;   // prevent divide by 0
        }

        maxDiff = (currentSolution - initialSolution).cwiseAbs().maxCoeff();    // maximum deviation
        
        if (maxDiff < tolerance) break;  // Convergence reached
        
        initialSolution = currentSolution; // Update the previousSolution vector between each iteration
    }

    if(maxDiff > tolerance)
	    cerr << "GaussSeidelSolver didn't converge" <<endl;
    maxIterations = iteration;          
}

void EqSolver::IterativeRelaxation(Eigen::Matrix<double, Eigen::Dynamic, 1>& initialSolution,
                                     int& maxIterations,
                                     double tolerance){
                                        
    int numRows = M.rows();
    int iteration = 0;
    double maxDiff = tolerance;   
    double weight = 1;
    Eigen::Matrix<double, Eigen::Dynamic, 1> currentSolution = initialSolution;   
    Eigen::Matrix<double, Eigen::Dynamic, 1> previousSolution = initialSolution; 
    if(!DiagonallyDominant())
	cerr << "JacobiSolver: Matrix not Diagonally Dominant, may not converge" <<endl;
    vector<int> iterations{10, 5, maxIterations};
    vector<double> dx(3);

    for(int n=0 ; n<3 ; n++){
    for (iteration = 0; iteration < iterations[n] ; ++iteration){
        for (int i = 0; i < numRows; i++) {	// Jacobi iteration
            double sum = 0.0;
	    previousSolution = currentSolution; // Update the previousSolution vector between each iteration
            for (int j = 0; j < numRows; j++) 
                if (j != i)  sum += M(i,j) * previousSolution(j);    

            if (M(i, i) != 0)
                currentSolution(i) = weight*(b(i) - sum) / M(i, i) + (1-weight)*previousSolution(i);     // Update the current solution 
            else 
                currentSolution(i) = 0.0;   // prevent divide by 0
        }

        maxDiff = (currentSolution - previousSolution).cwiseAbs().maxCoeff();    // maximum deviation
        
        if (maxDiff < tolerance) break;  // Convergence reached
        
    }
    dx[n] = (currentSolution-previousSolution).norm();
    if(n==1)
	    weight = 2/(1+sqrt(1-pow(dx[1]/dx[0], 1/5.)));
    }


    if(maxDiff > tolerance)
	    cerr << "JacobiSolver didn't converge" <<endl;
    maxIterations = iteration+15;          
    initialSolution = currentSolution;  
}

bool EqSolver::DiagonallyDominant(){
	for (int i = 0; i < M.rows(); ++i) {
		double sum=0;
		for (int j = 0; j < M.cols(); ++j) {
			if(j!=i) sum += M(i,j);
		}
		if (sum > M(i,i)) return false;
	}
	return true;
}
