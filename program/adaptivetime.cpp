#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <algorithm>

#include "adaptivetime.h"
#include "vector.h"
using namespace std;

double hstep(double hmax, Constellation a){	

	size_t N = a.N();
	// timestep has a minimum of 1/1024 of the 'standard' timestep (2^-10)
	double maxexp = 10;
	double h;
	double rmin = 0.0;
	double r = 0.0;


	for (size_t i = 0; i != N; i++) {
		for (size_t j = 0; j != N; j++) {
			r = (a.body(i).pos() - a.body(j).pos()).r();
			if (rmin && r) {
				rmin = min(rmin, r);
			}
			else {
				rmin = max(rmin, r);
			}
		}
	}
	double exp = min(maxexp,floor(log2(10*h/rmin)));
	h = hmax / pow(2, exp);
	return h;
}