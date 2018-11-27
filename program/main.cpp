#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "main.h"
#include "integrator.h"
#include "initialconditions.h"
using namespace std;

/*
To compile the multiple files:
LINUX:
open terminal
go to directory with program files
run "g++ -std=c++11 -Wall -O3 -o program *cpp"
run ./program


WINDOWS:
no idea
*/

/*
How to use:
================================================================================
start by creating a particle (or multiple particles)
using any of the following methods:

Body name(x, y, z, v_x, v_y, v_z, m);

Vec pos(x, y, z);
Vec vel(v_x, v_y, v_z);
Body(pos, vel, m);

Body name(); //defaults to pos and vel 0, m = 1
Body name(m); //defaults to pos and vel 0
================================================================================
create a constellation using any of the following methods:

Constellation name(); //defaults to empty

vector<Body> name1 = {body1, body2, ...};
Constellation name(name1);

you can add particles afterwards by using:
name.addBody(Body)
================================================================================
you can print the current state of the constellation to cmdline with
name.print();

or by using
cout << name << endl;
(note that all data types should have this functionality)

you can print the current state of the constellation to a datafile with
string path = "path";
name.printFile(path);
where path specifies the path to the data file
================================================================================
you can get information about the current state by:
Constellation.N(); //returns amount of particles
Constellation.time();
Constellation.energy(); //returns initial energy (from when last particle is added)
Constellation.particle(n); //returns the nth body
Constellation.calcEpot();
Constellation.calcEtot();
Constellation.calcEkin();
*/

int main() {

  // Define timestep h and number of timesteps
  double h = 0.000001;
  size_t steps = 1000000;
  size_t printInterval = 1000;
  string filename;
  string initConditions;
  cout << "Filename with initial conditions:" << endl;
  // Read in filename that is given as input in the terminal by the user
  cin >> filename;
  // Initialise vector of particles
  vector<Body> bodies;
  // Change location of initial conditions
  initConditions = "init/" + filename + ".txt";
  // Create vector of particles that are described in the text file
  bodies = initialisation(initConditions);
  Constellation a(bodies);

  RK4(h, steps, printInterval, filename, a);

}
