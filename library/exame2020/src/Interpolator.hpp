#ifndef __INTERPOLATOR__
#define __INTERPOLATOR__ 
#include<vector>
#include<utility>
#include<functional>



std::vector<double> Interpolator(const std::vector<std::pair<double, double>>&);
std::function<double(double)> Coef2Func(const std::vector<double>&);

#endif /* ifndef __INTERPOLATOR__ */
