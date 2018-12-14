#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ctime>

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
  double h_upper;
  double h_lower;
  string filename;
  string method;
  bool busy = true;
  string manual;


  while (busy) {
    //read in all variables
    cout << "Please provide a filename with initial conditions." << endl;
    //cout << "If empty, you will have to specify an amount of randomly generated particles" << endl;
    cout << "If quit, the program will terminate." << endl;
    cin >> filename;
    if (filename == "quit") {
      busy = false;
    } else {

      cout << "reading initial values" << endl;
      // Initialise vector of particles
      vector<Body> bodies;
      bodies = initialisation("init/" + filename + ".txt", h, endTime, printInterval, h_upper, h_lower);
      Constellation a(bodies);

      //a.scaleMass();
      a.center();

      cout << "method" << endl;
      cin >> method;

      cout << "Manual mode? [y/n] " << endl;
      cin >> manual;

      if (manual == "y") {
        // ask for h, steps, printInterval
        cout << "h (in days):" << endl;
        cin >> h;

        cout << "endTime (in days):" << endl;
        cin >> endTime;

        cout << "printInterval (in steps):" << endl;
        cin >> printInterval;
      } else if (manual == "n") {
        cout << "using parameters from file" << endl;
      } else {
        cout << "wrong input, not [y/n]" << endl;
      }


      //rescale timestep in days
      h *= 24*3600/tscale;
      endTime *= 24*3600/tscale;

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

      ofstream d("duration/duration_" + filename + "_" + method + ".txt", ios::trunc);
      d << a.N() << " " << duration/steps << endl;
      d.close();
    }



  }

}
