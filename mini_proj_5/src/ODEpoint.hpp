#ifndef ODEPOINT_HPP
#define ODEPOINT_HPP

#include "Xvar.hpp"

class ODEpoint : public Xvar {
    public:
    ODEpoint() : t(-1) {}
    ODEpoint(double t, Xvar a_) : t(t), Xvar(a_) {;}
    ODEpoint(double t, const std::vector<double>& v) : T(t), Xvar(v) {;}
    ODEpoint(double t, const std::initializer_list<double>& v) : T(t), Xvar(v) {;}

    void SetODEpoint(double t, Xvar& p);
    void SetODEpoint(double t, const std::initializer_list<double>& v);
    void SetODEpoint(double t, std::vector<double> v);
    
    double& Time() {return T;}
    
    private:
    double T; // time
};

#endif
