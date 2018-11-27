#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "integrator.h" // include header
using namespace std;

//==============================================================================
//
//define some constants
//
//==============================================================================

const double G = 1;

//implement driver function on a Constellation
//==============================================================================

vector<phaseVec> driverFunc(const Constellation& a) {
  //create output vector of size N
  size_t N = a.N();
  vector<phaseVec> output(N);

  //fill element by element
  for (size_t i=0; i!=N; ++i) {
    Vec x_punt = a.body(i).vel();
		Vec v_punt;
		for (size_t j=0; j!=N; ++j) {
			if (i != j) {
        Vec r_rel = a.body(i).pos() - a.body(j).pos();
				v_punt -= G * a.body(j).m() * r_rel / r_rel.r3();
			}
		}
		output[i] = phaseVec(x_punt, v_punt);
	}
	return output;
}

//implement RK4 integrator:
//==============================================================================

vector<phaseVec> k_1(const double h, const Constellation& a) {
  return h * driverFunc(a);
}

vector<phaseVec> k_2(const double h, Constellation a) {
  //need to explicitely copy constellation to change time and position
  //without changing original constellation
  a.addT(h/2);
  a.addVec(k_1(h, a)/2);
  return h * driverFunc(a);
}

vector<phaseVec> k_3(const double h, Constellation a){
  //idem as before
  a.addT(h/2);
  a.addVec(k_2(h, a)/2);
  return h * driverFunc(a);
}

vector<phaseVec> k_4(const double h,  Constellation a){
  //idem as before
  a.addT(h);
  a.addVec(k_3(h, a));
  return h * driverFunc(a);
}

vector<phaseVec> RK4(const double h, const Constellation& a) {
  return k_1(h, a) / 6 + k_2(h, a) / 3 + k_3(h, a) / 3 + k_4(h, a) / 6;
}

void RK4(const double h, const size_t steps, const size_t printInterval, const string filename, Constellation a) {
  //create datafile (also resets the file)
  string outfile = "data/" + filename + ".txt";
  ofstream f(outfile, ios::trunc);
  f << "#{tijd} #{positie1} #{snelheid1} #{...} \n";
  f << setprecision(5);
  f.close();


  string outfile_Energy = "data/" + filename + "_Energy.txt";
  ofstream g(outfile_Energy, ios::trunc);
  g << "#{tijd} #Energiefout \n";
  g << setprecision(5);
  g.close();

  for (size_t i=0; i!=steps; ++i) {
    if (i%printInterval == 0) {
      //print data only every printInterval points.
      a.printFile(outfile);
      a.printEnergy(outfile_Energy);
    }

    //create vectors with change
    vector<phaseVec> update = RK4(h, a);
    //update constellation
    a.addT(h);
    a.addVec(update);
  }

}
