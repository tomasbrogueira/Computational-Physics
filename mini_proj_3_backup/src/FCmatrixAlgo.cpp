#include "FCmatrixAlgo.hpp"

using Eigen::Matrix;
using Eigen::Dynamic;

static void FCmatrixAlgo::GaussElimination(
        Matrix<double, Dynamic, Dynamic>& M, // Matrix Coefficients
        Matrix<double, Dynamic, 1> & C // Matrix Constants
    ) {
    // Gaussian Elimination
    // M is the matrix of coefficients
    // C is the matrix of constants
    // M and C are modified in place
    // M is upper triangular
    // C is modified accordingly
    // M and C are modified in place
    // M is upper triangular
    // C is modified accordingly
    int n = M.rows();
    for (int k=0; k<n-1; k++) {
        for (int i=k+1; i<n; i++) {
            double factor = M(i,k)/M(k,k);
            for (int j=k+1; j<n; j++) {
                M(i,j) -= factor*M(k,j);
            }
            C(i) -= factor*C(k);
        }
    }

    // Backward substitution
    for (int i=n-1; i>=0; i--) {
        for (int j=i+1; j<n; j++) {
            C(i) -= M(i,j)*C(j);
        }
        C(i) /= M(i,i);
    }
}

static void FCmatrixAlgo::GaussEliminationPivot(
        Matrix<double, Dynamic, Dynamic>& M, // Matrix Coefficients
        Matrix<double, Dynamic, 1> & C, // Matrix Constants
        Matrix<double, Dynamic, 1>& P // Row order indexing
    ) {
    // Gaussian Elimination with pivoting
    // M is the matrix of coefficients
    // C is the matrix of constants
    // P is the row order indexing
    // M and C are modified in place
    // M is upper triangular
    // C is modified accordingly
    // P is modified accordingly
    int n = M.rows();
    for (int k=0; k<n-1; k++) {
        // pivot
        int p = k;
        double max = std::abs(M(P(k),k));
        for (int i=k+1; i<n; i++) {
            double tmp = std::abs(M(P(i),k));
            if (tmp > max) {
                max = tmp;
                p = i;
            }
        }
        // swap
        int tmp = P(k);
        P(k) = P(p);
        P(p) = tmp;
        // elimination
        for (int i=k+1; i<n; i++) {
            double factor = M(P(i),k)/M(P(k),k);
            for (int j=k+1; j<n; j++) {
                M(P(i),j) -= factor*M(P(k),j);
            }
            C(P(i)) -= factor*C(P(k));
        }
    }

    // Backward substitution
    for (int i=n-1; i>=0; i--) {
        for (int j=i+1; j<n; j++) {
            C(P(i)) -= M(P(i),j)*C(P(j));
        }
        C(P(i)) /= M(P(i),i);
    }
}


void FCmatrixAlgo::LUdecomposition(
        Matrix<double, Dynamic, Dynamic>& M, // Matrix Coefficients
        Matrix<int, Dynamic, 1> & P, // Pivot indexing
        bool bpivot = true  // has pivoting?
    ) {
    // LU decomposition
    // M is the matrix of coefficients
    // P is the pivot indexing
    // M and P are modified in place
    // M is the LU decomposition
    // P is the row order indexing
    int n = M.rows();
    for (int k=0; k<n-1; k++) {
        if (bpivot) {
            // pivot
            int p = k;
            double max = std::abs(M(P(k),k));
            for (int i=k+1; i<n; i++) {
                double tmp = std::abs(M(P(i),k));
                if (tmp > max) {
                    max = tmp;
                    p = i;
                }
            }
            // swap
            int tmp = P(k);
            P(k) = P(p);
            P(p) = tmp;
        }
        // elimination
        for (int i=k+1; i<n; i++) {
            double factor = M(P(i),k)/M(P(k),k);
            M(P(i),k) = factor;
            for (int j=k+1; j<n; j++) {
                M(P(i),j) -= factor*M(P(k),j);
            }
        }
    }
}

static void FCmatrixAlgo::IterativeJacobi(
        Matrix<double, Dynamic, Dynamic>& M, // Matrix Coefficients
        Matrix<double, Dynamic, 1> & C, // Matrix Constants
        Matrix<double, Dynamic, 1>& x, //initial guess
        int& itmax, //max number of iterations
        double& tol //tolerance
    ) {
    // Jacobi iterative method
    // M is the matrix of coefficients
    // C is the matrix of constants
    // x is the initial guess
    // itmax is the max number of iterations
    // tol is the tolerance
    // M, C, x are modified in place
    // x is the solution
    int n = M.rows();
    Matrix<double, Dynamic, 1> xold(n);
    for (int it=0; it<itmax; it++) {
        xold = x;
        for (int i=0; i<n; i++) {
            double sum = 0.0;
            for (int j=0; j<n; j++) {
                if (j != i) {
                    sum += M(i,j)*xold(j);
                }
            }
            x(i) = (C(i) - sum)/M(i,i);
        }

        // posso usar o norm?
        if ((x-xold).norm() < tol) {
            break;
        }
    }
}

static void FCmatrixAlgo::IterativeGaussSeidel(
        Matrix<double, Dynamic, Dynamic>& M, // Matrix Coefficients
        Matrix<double, Dynamic, 1> & C, // Matrix Constants
        Matrix<double, Dynamic, 1>& x, //initial guess
        int& itmax, //max number of iterations
        double& tol //tolerance
    ) {
    // Gauss-Seidel iterative method
    // M is the matrix of coefficients
    // C is the matrix of constants
    // x is the initial guess
    // itmax is the max number of iterations
    // tol is the tolerance
    // M, C, x are modified in place
    // x is the solution
    int n = M.rows();
    Matrix<double, Dynamic, 1> xold(n);
    for (int it=0; it<itmax; it++) {
        xold = x;
        for (int i=0; i<n; i++) {
            double sum = 0.0;
            for (int j=0; j<n; j++) {
                if (j != i) {
                    sum += M(i,j)*x(j);
                }
            }
            x(i) = (C(i) - sum)/M(i,i);
        }
        // posso usar o norm?
        if ((x-xold).norm() < tol) {
            break;
        }
    }
}

