#include "Xvar.hpp"

Xvar::Xvar(int n) {
    x.resize(n);
}

Xvar::Xvar(std::vector<double> v) : x(v) {;}

Xvar::Xvar(const std::initializer_list<double>& v) : x(v) {;}

Xvar::Xvar(const Xvar& v) : x(v.x) {;}

Xvar& Xvar::operator=(const Xvar& v) {
    x = v.x;
    return *this;
}

Xvar Xvar::operator+(const Xvar& v) {
    Xvar sum(x.size());
    for (int i = 0; i < x.size(); i++) {
        sum[i] = x[i] + v.x[i];
        }
    return sum;
}

double& Xvar::operator[](int i) {
    return x[i];
}

Xvar operator*(double a, const Xvar& v) {
    Xvar scalar(x.size());
    for (int i=0; i<x.size() ; i++){
        scalar = a*v.x[i]
    }
    return scalar;
}

std::ostream& operator<<(std::ostream& os, const Xvar& v) {
    for (int i = 0; i < X.x.size(); i++) {
        os << v.x[i] << " ";
    }
    return os;
}


std::vector<double>& Xvar::X() {
    return x;
}

