#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "main.h"
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

*/

int main() {
/*example code*/

  double sunMass = 1000000;
  double earthMass = 1;
  double h = 0.1;
  size_t steps = 10000;

//create first body
  Body sun(0, 0, 0, 0, 0, 0, sunMass);
  cout << "sun " << sun << endl;
//create second body
  Body earth(-100, 0, 0, 0, 1, 0, earthMass);
  cout << "earth "<< earth << endl;
//create third body
  Body moon(0, 100, 0, 0, 0, -1, 1);
//combine bodies
  vector<Body> y = {sun, earth, moon};

//create constellation
  Constellation a(y);

//create datafile (also resets the file)
  string outfile = "data/data.txt";
  ofstream f(outfile);
  f.open("data/data.txt", ios::trunc);
  f << "#{tijd} #{positie1} #{snelheid1} #{...} \n";
  f.close();

//use the RK4 integrator to update and print to file
  for (size_t i=0; i!=steps; ++i) {
    if (i%100 == 0) {
      //print data only every 100 points.
      a.printFile(outfile);
    }
    a.RK4update(h);
  }
  a.printFile(outfile);
}
