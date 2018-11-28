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
vector<phaseVec> k_2(const double h, Constellation a);
vector<phaseVec> k_3(const double h, Constellation a);
vector<phaseVec> k_4(const double h, Constellation a);

vector<phaseVec> RK4(const double h, const Constellation& a);

//Embedded RK
//==============================================================================

vector<phaseVec> K_1(const double h, const Constellation a);
vector<phaseVec> K_2(const double h, const Constellation a);
vector<phaseVec> K_3(const double h, const Constellation a);
vector<phaseVec> K_4(const double h, const Constellation a);
vector<phaseVec> K_5(const double h, const Constellation a);
vector<phaseVec> K_6(const double h, const Constellation a);

vector<phaseVec> ERK(const double h, const Constellation a);

// Verlet
//==============================================================================

vector<Vec> v_up(const double h, const Constellation a);
vector<phaseVec> VER(const double h, const Constellation a);

//Forest-Ruth
//==============================================================================

vector<Vec> accel(Constellation a, vector<Vec> x_change);
vector<phaseVec> FR(const double h, Constellation a);

#endif
