#include "IntegDeriv.hpp"

IntegDeriv :: IntegDeriv(Functor& f) : F(f) {;}   // pq fazer num cpp e n logo no hpp?

void IntegDeriv::TrapezoidalRule(double xi, double xf, int nintervals, double& Integral, double& Error){

    double dx = (xf-xi)/nintervals;
    double x = xi;
    double sum = 0;
    double error = 0;

    for (int i = 0; i < nintervals-1; i++) {
        sum += F(x) + F(x+dx);
        
        error -= (dx*dx*dx/12)*second_derivative_5pt(x + dx/2); 
        
        x += dx;
    }

    Integral = sum*dx/2;
    Error = error;
}



void IntegDeriv::SimpsonRule(double xi, double xf, int nintervals, double& Integral, double& Error){
    
        double dx = (xf-xi)/nintervals;
        double x = xi;
        double sum = 0;
        double error = 0;
    
        if (nintervals%2 == 0) {
            for (int i = 0; i<nintervals; i += 2){
                sum += F(x) + 4*F(x+dx) + F(x+2*dx);
                // o erro devia ser negativo?
                error += (dx*nintervals*dx*dx*dx*dx/180)*fourth_derivative(x);
                x += 2*dx;
            }
            sum *= dx/3;
        }
        else {
            for (int i = 0; i<nintervals-1; i += 2){
                sum += F(x) + 4*F(x+dx) + F(x+2*dx);
                // o erro devia ser negativo?
                error += (dx*nintervals*dx*dx*dx*dx/180)*fourth_derivative(x);
                x += 2*dx;
            }
            sum *= dx/3;
            sum += dx/12*(-F(x-2*dx) + 8*F(x-dx) + 5*F(x));
            error += (dx*nintervals*dx*dx*dx*dx/180)*fourth_derivative(x);
        }
        Integral = sum;
        Error = error;
}

double IntegDeriv::second_derivative_3pt(double x, double h){
    return (F(x+h) - 2*F(x) + F(x-h))/(h*h);
}

double IntegDeriv::second_derivative_5pt(double x, double h){
    return (16*F(x+h) + 16*F(x-h) - 30*F(x) - F(x-2*h) - F(x-2*h))/(12*h*h);
}

double IntegDeriv::fourth_derivative(double x, double h) {
    return (second_derivative_5pt(x + h, h) - 2 * second_derivative_5pt(x, h) + second_derivative_5pt(x - h, h)) / (h * h);
}