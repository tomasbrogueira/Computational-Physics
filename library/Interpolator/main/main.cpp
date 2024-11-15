#include"../src/Interpolator.hpp"
#include"../src/Functor.hpp"
#include<iostream>


using namespace std;
int main(int argc, char *argv[])
{
	vector<pair<double, double>> points {
		{3.,-1.},{4.,-1.},{5.,0.2}
	};
	vector<pair<double, double>> points2 {
		{0.,0.},{1.,1.},{2.,0.},{3.,-1.},{4.,-1.},{5.,0.2},{6.,0.3},{7.,0.3},{8.,-4.},{9.,-5.},{10.,-6.},{11.,+8.},{13.,+9.},{14.,00.},{15.,-1.}
	};
	auto coef = Interpolator(points);
	for(auto c : coef){
		cout << c << ", ";
	}
	cout << endl;
	Functor F("Interpolation", Coef2Func(coef));
	F.Draw({3,5},100, {"x", "y"});
	Functor F3("Interpolation3", Coef2Func(Interpolator(points, {{3,-1}})));
	F3.Draw({3,5},100, {"x", "y"});
	Functor F2("InterpolationSPline", SPline(points2));
	F2.Draw({0,15},1000, {"x", "y"});
	cout << "F2(9)=" << F2(9)  << endl;
	Functor F4("Interpolationpure", Coef2Func(Interpolator(points2)));
	F4.Draw({0,15},1000, {"x", "y"});
}
