#include "FCmatrixAlgo.hpp"
using namespace Eigen;
#include <array>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


void FCmatrixAlgo::GaussElimination(
	MCoef& M, 	// Coefficients matrix
	MConst& b) 		// Constants vector   
{
    
    if (M.rows() != M.cols()){  // Checking if the matrix is a square matrix
        std::cerr<<"The matrix is not a square matrix";
	return ;
    }
    int Rows = M.rows();
    int Cols = M.cols();

    // Forward elimination 
    for (int k = 0; k < Cols - 1; k++){ 
	    for (int i = k + 1; i < Rows; i ++){
		    double factor = M(i, k)/M(k, k);    // Calculating the factor by dividing the current element by the pivot element
		    M.row(i) -= factor*M.row(k);    	// Subtract from the current row the pivot row times the factor
		    b(i) -= factor*b(k);    		// Updating the constants vector
	    }
    }

    // Backward substitution
    for (int k = Rows - 1; k >= 0; k--){
	    b(k) /= M(k, k);    		// normalize pivot
	    for (int i = k - 1; i >= 0; i--) {
		    b(i) -= M(i, k) * b(k);	// eliminate k column
	    }
    }

}

void FCmatrixAlgo::GaussEliminationPivot(
	MCoef& M, // Coefficients matrix
        MConst& b, // Constants vector
        MOrder& index_order){ // Row order indexing

    std::vector<double> s;  // Absolute maximum value of each row
    
    if (M.rows() != M.cols()){
        std::cerr<<"The matrix is not a square matrix";
	return;
    }

    for(int i=0; i<M.rows(); ++i){
	    s.push_back(M.row(i).cwiseAbs().maxCoeff());
    }


    // Begin pivoting Gauss
    for(int i=0; i<M.rows()-1; ++i){    	// Iterate from the first row to the penultimate row
	    // Pivoting
	    double s_r=abs(M(i,i)/s[i]);    	// Relative maximum value of pivot
	    int pivot=i;
	    for(int k=i+1; k<M.rows(); ++k){    // Find relative maximum of possible pivots
		    if(s_r < abs(M(i,k)/s[k])){
			s_r = abs(M(i,k)/s[k]);
		    	pivot = k;
		    }
	    }
	    if (pivot > i){			// swap rows if needed
		    M.row(i).swap(M.row(pivot));
		    index_order.row(i).swap(index_order.row(pivot));
		    std::swap(b(i), b(pivot));	// Swap rows of the constants vector
		    std::swap(s[i], s[pivot]);	// Swap elements of s 
	    }

	    for(int j=i+1; j<M.cols(); j++){  // Forward elimination
		    double factor = M(j, i)/M(i, i);
		    M.row(j) -= factor*M.row(i);
		    b(j) -= factor* b(i);
	    }
    }
    // Backward substitution
    for (int k = M.rows() - 1; k >= 0; k--){
	    b(k) /= M(k, k);    // normalize pivot
	    for (int i = k - 1; i >= 0; i--) {
		    b(i) -= M(i, k) * b(k);   // eliminate k column
	    }
    }
}

void FCmatrixAlgo::LUdecomposition(
	MCoef& A,
        MOrder& rowOrder,
        bool bpivot) {
    if (A.rows() != A.cols()) { // Checking if the matrix is a square matrix
        std::cerr << "The matrix is not a square matrix";
	return;
    }
    int n = A.rows();

    if (bpivot) {
    std::vector<double> s;  // Absolute maximum value of each row
    for(int i=0; i<A.rows(); ++i){
	    s.push_back(A.row(i).cwiseAbs().maxCoeff());
    }
	    // Partial pivoting: Rearrange rows to ensure the largest element in each column is on the diagonal
    for (int k = 0; k < n - 1; k++) {
	    int pivot_index = k;
	    double pivot_value = std::abs(A(k, k));
	    for (int i = k + 1; i < n; i++) {
		    double current_value = std::abs(A(i, k));
		    if (current_value/s[i] > pivot_value/s[pivot_index]) {
			    pivot_index = i;
			    pivot_value = current_value;
		    }
	    }

	    if(pivot_index != k){
		    // Swap rows of the coefficients matrix
		    A.row(k).swap(A.row(pivot_index));

		    // Swap rows of the row order vector
		    std::swap(rowOrder(k), rowOrder(pivot_index));
	    }
	    // Perform elimination and store the factor in the lower triangular part of the matrix A
	    for (int i = k + 1; i < n; i++) {
		    double factor = A(i, k) / A(k, k);
		    A.block(i, k, 1, n - k) -= factor * A.block(k, k, 1, n - k);
		    A(i, k) = factor; 
	    }
    }

    std::cout<<"RowOrder: "<<rowOrder.transpose()<<std::endl;

    }

    else {
	    // Without pivoting 
	    for (int k = 0; k < n - 1; k++) {
		    for (int i = k + 1; i < n; i++) {
			    double factor = A(i, k) / A(k, k);
			    A.block(i, k, 1, n - k) -= factor * A.block(k, k, 1, n - k);
			    A(i, k) = factor; // Store the factor in the lower triangular part of the matrix
		    }
	    }
    }
}

pair<MCoef, MCoef> FCmatrixAlgo::LUmatrices(MCoef& LU){
	pair<MCoef, MCoef> p(MCoef(LU.rows(), LU.cols()), MCoef(LU.rows(), LU.cols()));
	for (int i = 0; i < LU.rows(); ++i) {
		for (int j = 0; j < LU.cols(); ++j) {
			if(j>i){
				p.second(i,j) = LU(i,j);
				p.first(i,j) = 0;
			}
			else if(j == i){
				p.second(i,j) = LU(i,j);
				p.first(i,j) = 1;
			}
			else{
				p.second(i,j) = 0;
				p.first(i,j) = LU(i,j);
			}
		}
	}
	return p;
}
