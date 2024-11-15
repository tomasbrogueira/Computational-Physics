#ifndef __INTERPOLATOR__
#define __INTERPOLATOR__ 
#include<vector>
#include<utility>
#include<functional>



std::vector<double> Interpolator(const std::vector<std::pair<double, double>>&);
std::vector<double> Interpolator(const std::vector<std::pair<double, double>>& p, const std::vector<std::pair<double, double>>& d);
std::function<double(double)> Coef2Func(const std::vector<double>&);
std::function<double(double)> SPline(const std::vector<std::pair<double, double>>& p);

#endif /* ifndef __INTERPOLATOR__ */
