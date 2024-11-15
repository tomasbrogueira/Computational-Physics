#include "ODEpoint.hpp"

void ODEpoint::SetODEpoint(double t, Xvar& p) {
    Time() = t;
    for (int i = 0; i < p.size(); i++) {
        (*this)[i] = p[i];
    }
}

void ODEpoint::SetODEpoint(double t, const std::initializer_list<double>& v) {
    Time() = t;
    int i = 0;
    for (auto it = v.begin(); it != v.end(); it++) {
        (*this)[i] = *it;
        i++;
    }
}

void ODEpoint::SetODEpoint(double t, std::vector<double> v) {
    Time() = t;
    for (int i = 0; i < v.size(); i++) {
        (*this)[i] = v[i];
    }
}

double& ODEpoint::Time() {
    return T;
}