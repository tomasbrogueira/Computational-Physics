#ifndef XVAR_HPP
#define XVAR_HPP

#include <vector>
#include <iostream>
#include <initializer_list>


class Xvar {
    public:
    Xvar() = default;
    Xvar(int n); // number of dependent variables
    Xvar(std::vector<double> v); // passing vector
    // using initializer list to build object: X({1,2})
    Xvar(const std::initializer_list<double>& v); // passing initializer list

    ~Xvar() = default;


    Xvar(const Xvar& v); // copy constructor
    Xvar& operator=(const Xvar& v); // assignment operator
    Xvar operator+(const Xvar& v); // sum operator
    double& operator[](int i); // access operator X[i]

    friend Xvar operator*(double a, const Xvar& v); // scalar multiplication
    friend std::ostream& operator<<(std::ostream& os, const Xvar& v);

    std::vector<double>& X(); // returns X


    protected:
    std::vector<double> x;
};

#endif