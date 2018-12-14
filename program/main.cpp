#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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

void GetFilesInDirectory(vector<string>& out, const string &directory)
  {
  DIR *dir;
  struct dirent *ent;
  dir = opendir(("init/" + directory).c_str());
  while ((ent = readdir(dir)) != NULL) {
      const string file_name = ent->d_name;
      //const string full_file_name = directory + "/" + file_name;
      if (file_name[0] == '.') { // Skipping hidden folders or files
        continue; }

      out.push_back(file_name);
  }
  closedir(dir);
} // GetFilesInDirectory

int main() {

  string inputName;
  string folder;
  vector<string> filenames;
  string initMethod;
  cout << "Initialisation by file or folder?" << endl;
  cin >> initMethod;
  if (initMethod == "file") {
    cout << "Please provide a filename with initial conditions." << endl;
    cin >> inputName;
    filenames.push_back(inputName + ".txt");
    folder = "";
  } else if (initMethod == "folder") {
    cout << "Please provide a folder with initial conditions." << endl;
    cin >> inputName;
    folder = inputName + "/";
    GetFilesInDirectory(filenames, folder);
  }

//==============================================================================
//Define method and method parameters
//==============================================================================

  string method;
  string manual;

  cout << "Manual mode? [y/n] " << endl;
  cin >> manual;

  cout << "method" << endl;
  cin >> method;

  double h;
  double h_upper;
  double h_lower;
  double endTime;
  size_t printInterval;

  if (manual == "y") {
    // ask for h, steps, printInterval
    if (method == "ERK_VAR") {
      cout << "precision upper bound:" << endl;
      cin >> h_upper;
      cout << "precision lower bound:" << endl;
      cin >> h_lower;
    } else {
      // ask for h, steps, printInterval
      cout << "h (in days):" << endl;
      cin >> h;

      cout << "endTime (in days):" << endl;
      cin >> endTime;

      cout << "printInterval (in steps):" << endl;
      cin >> printInterval;
    }
    //rescale timestep in days
    h *= 24*3600/tscale;
    endTime *= 24*3600/tscale;


  } else if (manual == "n") {
    cout << "using parameters from file" << endl;
  } else {
    cout << "wrong input, not [y/n]" << endl;
  }

  while (not filenames.empty()) {
    string filename = filenames.back();
    cout << "\n Now doing " << filename << '\n' << endl;
    filenames.pop_back();

    // Initialise vector of particles
    cout << "reading initial values of " << filename << endl;
    vector<Body> bodies;
    bodies = initialisation("init/" + folder + filename, h, endTime, printInterval, h_upper, h_lower);
    Constellation a(bodies);
    a.center();

    clock_t start;
    double duration;
    start = clock();
    steps = 0;
    funcEvals = 0;

    if (method == "ERK_VAR") {
      run(method, h_upper, h_lower, endTime, printInterval, folder + method + filename, a);
    } else {
      run(method, h, endTime, printInterval, folder + method + filename, a);
    }

    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    cout << "Ran " << steps << " steps, " << funcEvals << " evaluations and took " << duration << " seconds." << endl;
    cout << "Averaged " << steps / duration << " steps per second." << endl;
    cout << "Averaged " << funcEvals / steps << " evaluations per step." << endl;

    ofstream d("duration/" + folder + method, ios::trunc);
    d << a.N() << " " << duration/steps << endl;
    d.close();
  }

}
