#include <iostream>
#include <cmath>


double func1(double){
    return sqrt(sin(2*x));
}

void func2(double x, double& f){
    f = sqrt(sin(2*x));
}

void func3(double x, double* f){
    *f = sqrt(sin(2*x));
}

int main(){
    double x;
    cin << x;

    double f1 = func1(x);
    double f2;
    double f3;
    
    func2(x, f2);
    func3(x, &f3);
    
    std::cout << "f1 = " << f1 << std::endl;
    std::cout << "f2 = " << f2 << std::endl;
    std::cout << "f3 = " << f3 << std::endl;
    
    return 0;
}
