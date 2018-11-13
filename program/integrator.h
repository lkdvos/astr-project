#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

class phaseVec;




//declare driver function
phaseVec driver(const double t, const phaseVec y);


//declare RK4 functions
phaseVec k_1(double h, double t, phaseVec y);
phaseVec k_2(double h, double t, phaseVec y);
phaseVec k_3(double h, double t, phaseVec y);
phaseVec k_4(double h, double t, phaseVec y);


#endif
