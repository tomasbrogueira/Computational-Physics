#ifndef DOUBLEE_H
#define DOUBLEE_H
#include<limits>
#include<iostream>

#define ABS(x)	(x>=0 ? x : -x)
#define MAX(x,y) (x>y ? x : y)

class DoubleE
{
public:
	DoubleE(double f, double e):num{f}, err{e}{check();}
	DoubleE(double f): num{f}, err{MAX(f * std::numeric_limits<double>::epsilon()/2, std::numeric_limits<double>::min())}{}
	DoubleE& operator=(double f){num = f; err = f * std::numeric_limits<double>::epsilon(); return *this;}
	DoubleE operator+(DoubleE d); 
	DoubleE operator-(DoubleE d); 
	DoubleE operator*(DoubleE d); 
	DoubleE operator/(DoubleE d); 
	DoubleE& operator+=(DoubleE d); 
	DoubleE& operator-=(DoubleE d); 
	DoubleE& operator*=(DoubleE d); 
	DoubleE& operator/=(DoubleE d); 
	friend std::ostream& operator<<(std::ostream& os, const DoubleE& n);
	void check(){if (ABS(num)<ABS(err)) std::cout << "num < err" << std::endl;}

private:
	double num;
	double err;
};


#endif /* DOUBLEE_H */
