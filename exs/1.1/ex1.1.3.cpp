#include<iostream>
using namespace std;

//write a program to get the bytes of the following types: short int, int, long int, unsigned int, float, double, long double

int main(){
    short int a;
    int b;
    long int c;
    unsigned int d;
    float e;
    double f;
    long double g;
    cout << "The size of short int is " << sizeof(a) << " bytes." << endl;
    cout << "The size of int is " << sizeof(b) << " bytes." << endl;
    cout << "The size of long int is " << sizeof(c) << " bytes." << endl;
    cout << "The size of unsigned int is " << sizeof(d) << " bytes." << endl;
    cout << "The size of float is " << sizeof(e) << " bytes." << endl;
    cout << "The size of double is " << sizeof(f) << " bytes." << endl;
    cout << "The size of long double is " << sizeof(g) << " bytes." << endl;
    return 0;
}