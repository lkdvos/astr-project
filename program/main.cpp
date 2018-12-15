#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <string>

#include "integrator.h"
#include "initialconditions.h"
using namespace std;

double G = 1;;
double xscale = 1;
double tscale = 1;
double Mscale = 1;
size_t steps = 0;
size_t funcEvals = 0;

int main() {
//============================================================================
//Choose what files to initialise
//============================================================================
  //declare variables for choosing initialisation
  string inputName;
  string folder;
  vector<string> filenames;
  string initMethod;
  //read initialisation method
  //todo safeguard input
  cout << "Initialisation by file or folder?\nReading a folder might only work on a Linux system" << endl;
  cin >> initMethod;

  //add all initialisation files to vector
  if (initMethod == "file") {
    cout << "Please provide a filename with initial conditions." << endl;
    cin >> inputName;
    filenames.push_back(inputName + ".txt");
    folder = "";
  } else if (initMethod == "folder") {
    cout << "Please provide a folder with initial conditions." << endl;
    cout << "Make sure a folder with the same name exists in the data folders." << endl;
    cin >> inputName;
    folder = inputName + "/";
    GetFilesInDirectory(filenames, folder);
  }

//==============================================================================
//Define method and method parameters
//==============================================================================
  //declare variables for choosing method
  string method;
  string manual;

  cout << "Manual mode? [y/n] " << endl;
  cin >> manual;

  cout << "Integration method? [RK4/ERK/FR/VER/ERK_VAR] " << endl;
  cin >> method;

  double h;
  double h_upper;
  double h_lower;
  double endTime;
  size_t printInterval;
  //manual input of parameters
  if (manual == "y") {
    // ask for h, steps, printInterval
    if (method == "ERK_VAR") {
      //variable timestep bounds
      cout << "precision for upper bound?:" << endl;
      cin >> h_upper;
      cout << "precision for lower bound?:" << endl;
      cin >> h_lower;
    } else {
      //non variable: ask for h
      cout << "h (in days):" << endl;
      cin >> h;
    }
    //ask for endTime and printInterval
    cout << "endTime (in days):" << endl;
    cin >> endTime;

    cout << "printInterval (in steps):" << endl;
    cin >> printInterval;

    //rescale timestep in days
    h *= 24*3600/tscale;
    endTime *= 24*3600/tscale;

  } else if (manual == "n") {
    //parameters from files
    cout << "Using parameters from files." << endl;

  } else {
    //give message for wrong input, will fail rest of program
    //todo restart asking for manual
    cout << "wrong input, not [y/n]" << endl;
  }

//==============================================================================
//integrate all chosen files with chosen parameters and method
//==============================================================================
//loop over files
  while (not filenames.empty()) {
    //pick one file and delete from stack
    string filename = filenames.back();
    cout << "\n Now doing " << filename << '\n' << endl;
    filenames.pop_back();

    // Initialise vector of particles
    cout << "reading initial values of " << filename << endl;
    vector<Body> bodies;
    bodies = initialisation("init/" + folder + filename, h, endTime, printInterval, h_upper, h_lower);
    Constellation a(bodies);

    // change constellation to COM frame
    a.center();

    //declare variables for performance test
    clock_t start;
    double duration;
    start = clock();
    steps = 0;
    funcEvals = 0;

    if (method == "ERK_VAR") {
      //loop variable timestep
      run(method, h_upper, h_lower, endTime, printInterval, folder + method + filename, a);
    } else {
      //loop fixed timestep
      run(method, h, endTime, printInterval, folder + method + filename, a);
    }
    //calculate time taken to run loop
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    cout << "Ran " << steps << " steps, " << funcEvals << " evaluations and took " << duration << " seconds." << endl;
    cout << "Averaged " << steps / duration << " steps per second." << endl;
    cout << "Averaged " << funcEvals / steps << " evaluations per step." << endl;

    //add performance data to file
    ofstream d("duration/" + folder + method + filename, ios::trunc);
    d << method << endl;
    d << a.N() << " " << duration/steps << endl;
    if (method == "ERK_VAR") {
      //print h bounds for variable timestep
      d << h_upper << " " << h_lower << " " << endTime << " " << printInterval << endl;
    } else {
      //print h for fixed timestep
      d << h << " " << endTime << " " << printInterval << endl;
    }
    d.close();
  } //end loop over files


  //explicitly return int for main
  return 1;
} //end main
