#include<cmath>
#include<iostream>
using namespace std;

int main(){
    const double G = 6.67e-11;
    const double m1 = 5.97e24;
    const double R = 6.371e6;
    double T, h;

    cout << "Enter the period of the satelite: ";
    cin >> T;

    T = pow((G*m1*pow(T,2))/(4*pow(M_PI,2)),1/3) - R;

    cout << "The height of the satelite is: " << h << endl;

    return 0;
}