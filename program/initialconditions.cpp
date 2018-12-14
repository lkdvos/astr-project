//==============================================================================
//
//.cpp file that can be used to read out initial conditions for
//a certain N-body simulation.
//
//==============================================================================

#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "vector.h"
#include "initialconditions.h"
using namespace std;

extern double G;
extern double tscale;

// Function that reads out initial conditions for a certain N-body simulation
// (contained in a file) and returns a vector containing the particles of the simulation
vector<Body> initialisation(string filename, double& h, double& endTime, size_t& printInterval, double& h_upper, double& h_lower)
	{
	ifstream file_input(filename);
	// Initialise vector of particles
	vector<Body> bodies;

	//==============================================================================
	//
	// Initialise mass, velocity components and position components for particles
	//
	//==============================================================================

	double x = 0;
	double y = 0;
	double z = 0;
	double vx = 0;
	double vy = 0;
	double vz = 0;
	double m = 0;
	string name = "";

	// The number of particles in the simulation is defined as numpart
	int numpart = 0;
	file_input >> numpart;
	// define a G for the relevant data (this specifies the units)
	file_input >> G;
	file_input >> tscale;

	for (int i=0; i<numpart; i++)	// For-loop that reads out lines of file line by line
		{
		file_input >> x >> y >> z >> vx >> vy >> vz >> m >> name;
		Body body = Body(x, y, z, vx, vy, vz, m, name);
		// Add each particle to the vector of particles
		bodies.push_back(body);
		}
	//check if end of file, else read h, endTime, printInterval
	if (file_input.peek()!=EOF) {
		file_input >> h;
		file_input >> endTime;
		file_input >> printInterval;
		if (file_input.peek()!=EOF) {
			file_input >> h_upper;
			file_input >> h_lower;
		} else {
			h_upper = 0;
			h_lower = 0;
		}
	}
	return bodies;
	}
