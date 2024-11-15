#include<iostream>
#include<cmath>
using namespace std;

int main(){
    float f_pi = atan(1)*4;
    double d_pi = atan(1)*4;
    long double f_precision = f_pi/M_PI;
    long double d_precision = d_pi/M_PI;
    cout << "The value of pi in float is " << f_pi << endl;
    cout << "The precision of pi in float is " << f_precision << endl;
    cout << "The value of pi in double is " << d_pi << endl;
    cout << "The precision of pi in double is " << d_precision << endl;
    return 0;
}