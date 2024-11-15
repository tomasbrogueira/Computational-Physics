#include "ODEpoint.hpp"

const double& ODEpoint::timeGetter() {
    return time;
}

const vector<double>& ODEpoint::varGetter() {
    return var;
}

ostream& ODEpoint::operator<<(ostream& os, const ODEpoint& p) {
    os << "[";
    for (auto i : p.var) {
        os << i << " ";
    }
    os << "]" << endl;
    
    return os;
}