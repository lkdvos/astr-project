#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <string>

#include "main.h"
#include "integrator.h"
#include "initialconditions.h"
using namespace std;

double G = 1;;
double xscale = 1;
double tscale = 1;
double Mscale = 1;
size_t steps = 0;
size_t funcEvals = 0;

/*
To compile the multiple files:
LINUX:
open terminal
go to directory with program files
run "g++ -std=c++11 -Wall -O3 -o program *cpp"
run ./program
*/

int main() {

  // Define timestep h and number of timesteps
  double h;
  double endTime;
  size_t printInterval;
  string filename;
  string method ;
  bool busy = true;


  while (busy) {
    //read in all variables
    cout << "Please provide a filename with initial conditions." << endl;
    //cout << "If empty, you will have to specify an amount of randomly generated particles" << endl;
    cout << "If quit, the program will terminate." << endl;
    cout << endl;

    //cout << "Filename with initial conditions:" << endl;
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
      //a.scaleMass();
      a.center();
      //a.rescale();
      /*cout << "Mscale = " << Mscale << endl;
      cout << "xscale = " << xscale << endl;
      cout << "tscale = " << tscale << endl;
      cout << "G = " << G << endl;
      cout << "a = " << a << endl;
      cout << "Ebegin = " << a.calcEpot() << '\t' << a.calcEkin() << '\t' << a.calcEtot() << endl;
      */
      // ask for method of integration

      cout << "method" << endl;
      cin >> method;

      // ask for h, steps, printInterval
      cout << "h (in days):" << endl;
      cin >> h;

      cout << "endTime (in days):" << endl;
      cin >> endTime;

      cout << "printInterval (in steps):" << endl;
      cin >> printInterval;

      //rescale timestep in days
      h *= 24*3600/tscale;
      endTime *= 24*3600/tscale;
      /*
      RK4(h, steps, printInterval, filename, a);
      Verlet(h, steps, printInterval, filename, a);
      ERK(h, steps, printInterval, filename, a);
      FR(h, steps, printInterval, filename, a);
      */
      clock_t start;
      double duration;
      start = clock();
      steps = 0;
      funcEvals = 0;

      run(method, h, endTime, printInterval, filename, a);


      duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
      cout << "Ran " << steps << " steps, " << funcEvals << " evaluations and took " << duration << " seconds." << endl;
      cout << "Averaged " << steps / duration << " steps per second." << endl;
      cout << "Averaged " << funcEvals / steps << " evaluations per step." << endl;

    }



  }

}
