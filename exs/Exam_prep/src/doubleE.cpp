#include"doubleE.hpp"

using namespace std;

DoubleE DoubleE::operator+(DoubleE d){
	double res = num+d.num;
	return {res, MAX(numeric_limits<double>::epsilon() * ABS(res)/2, err) + MAX(numeric_limits<double>::epsilon() * ABS(res)/2, d.err)};
}

DoubleE DoubleE::operator-(DoubleE d){
	double res = num-d.num;
	return {res, MAX(numeric_limits<double>::epsilon() * ABS(res)/2, err) + MAX(numeric_limits<double>::epsilon() * ABS(res)/2, d.err)};
}

DoubleE DoubleE::operator*(DoubleE d){
	return {num*d.num, ABS(num*d.err)+ABS(d.num*err)};
}

DoubleE DoubleE::operator/(DoubleE d){
	return {num/d.num, ABS(err/d.num)+ABS(d.err*num/(d.num*d.num))};
}

ostream& operator<<(ostream& os, const DoubleE& n){
	os << n.num << "±" << n.err ;
	return os;
}


DoubleE& DoubleE::operator+=(DoubleE d){
	num += d.num;
	err = MAX(numeric_limits<double>::epsilon() * ABS(num)/2, err) + MAX(numeric_limits<double>::epsilon() * ABS(num)/2, d.err);
	check();
	return *this;
}

DoubleE& DoubleE::operator-=(DoubleE d){
	num -= d.num;
	err = MAX(numeric_limits<double>::epsilon() * ABS(num)/2, err) + MAX(numeric_limits<double>::epsilon() * ABS(num)/2, d.err);
	check();
	return *this;
}

DoubleE& DoubleE::operator*=(DoubleE d){
	err = ABS(num*d.err)+ABS(d.num*err);
	num *= d.num;
	check();
	return *this;
}

DoubleE& DoubleE::operator/=(DoubleE d){
	err = ABS(err/d.num)+ABS(d.err*num/(d.num*d.num));
	num /= d.num;
	check();
	return *this;
}
