#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "main.h"
#include "integrator.h"
#include "initialconditions.h"
using namespace std;

extern double G;
extern double xscale;
extern double vscale;
extern double Mscale;

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
  double h;
  size_t steps;
  size_t printInterval;
  string filename;
  bool busy = true;

  while (busy) {
    //read in all variables
    cout << "Please provide a filename with initial conditions." << endl;
    cout << "If empty, you will have to specify an amount of randomly generated particles" << endl;
    cout << "If quit, the program will terminate." << endl;
    cout << endl;

    cout << "Filename with initial conditions:" << endl;
    cin >> filename;
    if (filename == "quit") {
      busy = false;
    } else if (filename == "") {
      cout << "How many particles?" << endl;
      filename = "data1";
      busy = false;
      //need to implement this WIP
    } else {
      cout << "reading initial values" << endl;
      // Initialise vector of particles
      vector<Body> bodies;
      // Create vector of particles that are described in the text file
      bodies = initialisation("init/" + filename + ".txt");
      Constellation a(bodies);
      a.scaleMass();
      a.center();
      a.rescale();
      cout << "Mscale = " << Mscale << endl;
      cout << "xscale = " << xscale << endl;
      cout << "tscale = " << tscale << endl;
      cout << "G = " << G << endl;
      cout << "a = " << a << endl;
      cout << "Ebegin = " << a.calcEpot() << '\t' << a.calcEkin() << '\t' << a.calcEtot() << endl;

      // ask for h, steps, printInterval
      cout << "h (in days):" << endl;
      cin >> h;

      //rescale timestep in days
      h *= 24*3600/tscale;

      cout << "steps:" << endl;
      cin >> steps;

      cout << "printInterval" << endl;
      cin >> printInterval;


      //set default values if none specified
      if (h == 0) {
        h = 1;
      }
      if (steps == 0) {
        steps = 365;
      }
      if (printInterval == 0) {
        printInterval = 1;
      }


      //RK4(h, steps, printInterval, filename, a);
      //Verlet(h, steps, printInterval, filename, a);
      //ERK(h, steps, printInterval, filename, a);
      FR(h, steps, printInterval, filename, a);

    }



  }

}
