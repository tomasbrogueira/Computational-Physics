#include"utility.hpp"

std::ostream& operator<<(std::ostream& os, cell& c){
	os << "(" << c.center_coo[0] <<", " << c.center_coo[1] <<
		"): " << c.power << " W";
	return os;
}
