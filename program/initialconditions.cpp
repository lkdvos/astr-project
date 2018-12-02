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
vector<Body> initialisation(string filename)
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

	// The number of particles in the simulation is defined as numpart
	int numpart = 0;
	file_input >> numpart;
	// define a G for the relevant data (this specifies the units)
	file_input >> G;
	file_input >> tscale;
	for (int i=0; i<numpart; i++)	// For-loop that reads out lines of file line by line
		{
		file_input >> x >> y >> z >> vx >> vy >> vz >> m;
		Body body = Body(x, y, z, vx, vy, vz, m);
		// Add each particle to the vector of particles
		bodies.push_back(body);
		}
	return bodies;
	}
