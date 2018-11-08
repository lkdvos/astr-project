#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "integrator.h" // include header
using namespace std;

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
  return h * driverFunc(a.addT(h/2).addY(k_1/2));
}

vector<phaseVec> k_3(const double h, Constellation a){
  //idem as before
  return h * driverFunc(a.addT(h/2).addY(k_2/2));
}

vector<phaseVec> k_4(const double h,  Constellation a){
  //idem as before
  return h * driverFunc(a.addT(h).addY(k_3));
}

vector<phaseVec> RK4(const double h, const Constellation& a) {
  return k_1 / 6 + k_2 / 3 + k_3 / 3 + k_4 / 6;
}
