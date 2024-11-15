#include "ODEpoint.hpp"
#include <functional>

class ODEsolver {
    public:

    ODEsolver(const std::vector<std::function<double(ODEpoint)>>& f) : F(f) {;}
    ~ODEsolver();

    // set functions

    SetODEfunc(const std::vector<std::function<double(ODEpoint)>>&);

    // solver methods
    const std::vector<ODEpoint>& Euler(ODEpoint i, double step, double t);
    const std::vector<ODEpoint>& PredictorCorrector(ODEpoint i, double step, double t);
    const std::vector<ODEpoint>& LeapFrog(ODEpoint i, double step, double t);
    const std::vector<ODEpoint>& RK2(ODEpoint i, double step, double t);
    const std::vector<ODEpoint>& RK4(ODEpoint i, double step, double t);


    private:
    std::vector<std::function<double(ODEpoint)>> F;
    std::map<std::string, std::function<double(ODEpoint)>> MS; // key: "euler", "trapezoidal",...
};