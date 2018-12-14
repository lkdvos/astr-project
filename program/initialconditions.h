//==============================================================================
//
//header file for initialconditions.cpp
//
//==============================================================================

#ifndef INITIALCONDITIONS_H
#define INITIALCONDITIONS_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include "vector.h"
using namespace std;


vector<Body> initialisation(string filename, double& h, double& endTime, size_t& printInterval, double& h_upper, double& h_lower);

#endif
