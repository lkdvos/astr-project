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
vector<phaseVec> gravity(const Constellation& a);
vector<phaseVec> speed(const Constellation& a);
vector<phaseVec> driverFunc(const Constellation& a);

//RK4 integrator dependencies:
//==============================================================================

vector<phaseVec> k_1(const double h, Constellation a);
vector<phaseVec> k_2(const double h, Constellation a);
vector<phaseVec> k_3(const double h, Constellation a);
vector<phaseVec> k_4(const double h, Constellation a);

void RK41(const double h, Constellation& a);
void RK4(const double h, const size_t steps, const size_t printInterval, const string filename, Constellation a);

//Verlet integrator:
//==============================================================================

void Verlet1(const double h, Constellation& a, vector<phaseVec>& driver);
void Verlet(const double h, const size_t steps, const size_t printInterval, const string filename, Constellation a);

//imbedded RK:
//==============================================================================

void ERK1(const double h, Constellation& a);
void ERK(const double h, const size_t steps, const size_t printInterval, const string filename, Constellation a);


//Foresth Ruth
//==============================================================================
vector<phaseVec> FR1(double h, Constellation a);
void FR(const double h, const size_t steps, const size_t printInterval, const string filename, Constellation a);

#endif
