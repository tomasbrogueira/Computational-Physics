#include "ODEsolver.hpp"


ODEsolver::~ODEsolver() {
    F.clear();
    MS.clear();
}

ODEsolver::SetODEfunc(const std::vector<std::function<double(ODEpoint)>>& f) {
    F = f;
}

const std::vector<ODEpoint>& ODEsolver::Euler(ODEpoint i, double step, double t) {
    std::vector<ODEpoint> v;
    v.push_back(i);

    for (int j = 0; j < F.size(); j++) {
        v.push_back(ODEpoint(t, v[j] + step * F[j](v[j])));
    }

    MS["euler"] = v;
    return v;
}

const std::vector<ODEpoint>& ODEsolver::PredictorCorrector(ODEpoint i, double step, double t) {
    std::vector<ODEpoint> v;
    v.push_back(i);

    for (int j = 0; j < F.size(); j++) {
        // not sure about this
        v.push_back(ODEpoint(t, v[j] + step * (F[j](v[j])+F[j](v[j]+step/**F[j](v[j])*/))/2.0));
    }

    MS["predictor"] = v;
    return v;
}

// defenitivamente errado
const std::vector<ODEpoint>& ODEsolver::LeapFrog(ODEpoint i, double step, double t) {
    std::vector<ODEpoint> v;
    v.push_back(i);

    for (int j = 0; j < F.size(); j++) {
        v.push_back(ODEpoint(t, v[j] + 2.0*step * F[j](v[j])));
    }

    MS["leapfrog"] = v;
    return v;
}

const std::vector<ODEpoint>& ODEsolver::RK2(ODEpoint i, double step, double t) {
    std::vector<ODEpoint> v;
    v.push_back(i);

    for (int j = 0; j < F.size(); j++) {
        v.push_back(ODEpoint(t, v[j] + step * F[j](v[j] + step/2.0 * F[j](v[j]))));
    }

    MS["rk2"] = v;
    return v;
}

const std::vector<ODEpoint>& ODEsolver::RK4(ODEpoint i, double step, double t) {
    std::vector<ODEpoint> v;
    v.push_back(i);

    for (int j = 0; j < F.size(); j++) {
        v.push_back(ODEpoint(t, v[j] + step * (F[j](v[j]) + 2.0*F[j](v[j] + step/2.0 * F[j](v[j])) + 2.0*F[j](v[j] + step/2.0 * F[j](v[j] + step/2.0 * F[j](v[j]))) + F[j](v[j] + step * F[j](v[j] + step/2.0 * F[j](v[j] + step/2.0 * F[j](v[j])))))/6.0));
    }

    MS["rk4"] = v;
    return v;
}
