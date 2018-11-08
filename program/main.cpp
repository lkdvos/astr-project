#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "main.h"
using namespace std;


int main() {
//working in standard units: G = M = 1
  /*double sunMass = 332946 / (332946 + 1);
  double earthMass = 1 / (332946 + 1);*/

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


  Constellation a(y);
  string outfile = "data/data.txt";
  ofstream f(outfile);
  f.open("data/data.txt", ios::trunc);
  f << "#{tijd} #{positie1} #{snelheid1} #{...} \n";
  f.close();

  for (size_t i=0; i!=steps; ++i) {
    if (i%100 == 0) {
      a.printFile(outfile);
    }
    a.RK4update(h);
  }
  a.printFile(outfile);

}
