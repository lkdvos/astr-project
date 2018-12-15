//safeguard includes
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

//==============================================================================
//
//define some constants
//
//==============================================================================

extern double G;
extern size_t steps;
extern size_t funcEvals;
extern const char sep;

//driver functions:
//==============================================================================
vector<phaseVec> gravity(const Constellation& a);
vector<phaseVec> speed(const Constellation& a);
vector<phaseVec> driverFunc(const Constellation& a);

//RK4 integrator dependencies:
//==============================================================================
vector<phaseVec> RK4_1(const double h, Constellation a);
vector<phaseVec> RK4_2(const double h, Constellation a, const vector<phaseVec>& k1);
vector<phaseVec> RK4_3(const double h, Constellation a, const vector<phaseVec>& k2);
vector<phaseVec> RK4_4(const double h, Constellation a, const vector<phaseVec>& k3);

void RK4(const double h, Constellation& a);

//embedded RK:
//==============================================================================
void ERK5(const double h, Constellation& a, const vector<phaseVec>& K1, const vector<phaseVec>& K3, const vector<phaseVec>& K4, const vector<phaseVec>& K5, const std::vector<phaseVec>& K6);
void ERK4(const double h, Constellation& a, const vector<phaseVec>& K1, const vector<phaseVec>& K3, const vector<phaseVec>& K4, const vector<phaseVec>& K5);
void ERK_VAR(const double h_upper, const double h_lower, double& h, Constellation& a);
void ERK(const double h, const size_t steps, const size_t printInterval, const string filename, Constellation a);

//Verlet integrator:
//==============================================================================
void Verlet(const double h, Constellation& a, vector<phaseVec>& driver);

//Foresth Ruth:
//==============================================================================
void FR1(const double h, Constellation& a);
void FR(const double h, const size_t steps, const size_t printInterval, const string filename, Constellation a);

//Loop method
//==============================================================================
//method for fixed time step h
void run(const string method, const double h, const double endTime, const size_t printInterval, const string filename, Constellation a);
//method for variable time step h
void run(const string method, const double h_upper, const double h_lower, const double endTime, const size_t printInterval, const string filename, Constellation a);

#endif
