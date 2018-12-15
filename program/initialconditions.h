//==============================================================================
//
//header file for initialconditions.cpp
//functions for reading initialisation files
//
//==============================================================================
//safeguard header includes
#ifndef INITIALCONDITIONS_H
#define INITIALCONDITIONS_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <dirent.h>
#include <string>
#include "vector.h"
using namespace std;

//function to initialise parameters from file
vector<Body> initialisation(string filename, double& h, double& endTime, size_t& printInterval, double& h_upper, double& h_lower);

//function to get all files in a directory
void GetFilesInDirectory(vector<string>& out, const string &directory);
#endif
