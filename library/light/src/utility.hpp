#ifndef __UTILITY__
#define __UTILITY__ value
#include <array>
#include<iostream>


struct cell {
	std::array<float, 3> center_coo;		// cell center coordinates (cm)
	float area;								// cell area (cm^2)
	float power;							// cell incident power (W)
};

std::ostream& operator<<(std::ostream& os, cell& c);

struct lightsource {
	std::array<float, 3> coo; 				// source coordinates (cm)
	float power;							// source power (W)
};

#define PRINT(x)	std::cout << #x << " : " << x << std::endl

#endif /* ifndef __UTILITY__ */
