#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

//include the data structures from "vector.h"
#include "vector.h"

//driver functions
//==============================================================================

vector<phaseVec> driverFunc(const Constellation& a);

//RK4 integrator dependencies:
//==============================================================================

vector<phaseVec> k_1(const double h, const Constellation& a);
vector<phaseVec> k_2(const double h, const Constellation& a);
vector<phaseVec> k_3(const double h, const Constellation& a);
vector<phaseVec> k_4(const double h, const Constellation& a);

vector<phaseVec> RK4(const double h, const Constellation& a);

#endif
