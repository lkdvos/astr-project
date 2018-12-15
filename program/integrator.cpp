#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "integrator.h" // include header
using namespace std;

//implement driver function on a Constellation
//==============================================================================

vector<phaseVec> gravity(const Constellation& a) {
  /*function that returns phaseVectors of format (0, a) where a is the
  gravitational force determined by the constellation*/


  //create output vector of size N
  funcEvals += 1;
  size_t N = a.N();
  vector<phaseVec> output(N);

  //fill element by element
  for (size_t i=0; i!=N; ++i) {
    Vec x_punt;
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

vector<phaseVec> xpunt(const Constellation& a) {
  /*function that returns phaseVectors of format (a, 0) where a is the change
  in position = v*/


  //create output vector of size N
  size_t N = a.N();
  vector<phaseVec> output(N);

  //fill element by element
  for (size_t i=0; i!=N; ++i) {
    Vec x_punt = a.body(i).vel();
    Vec v_punt;
    output[i] = phaseVec(x_punt, v_punt);
  }
  return output;
}

vector<phaseVec> driverFunc(const Constellation& a) {
  //combine the two functions
  vector<phaseVec> output = gravity(a) + xpunt(a);
	return output;
}

//implement RK4 integrator:
//==============================================================================

vector<phaseVec> RK4_1(const double h, Constellation a) {
  return h * driverFunc(a);
}

vector<phaseVec> RK4_2(const double h, Constellation a, const vector<phaseVec>& k1) {
  //need to explicitely copy constellation to change time and position
  //without changing original constellation
  a.addT(h/2);
  a.addVec(k1/2);
  return h * driverFunc(a);
}
vector<phaseVec> RK4_3(const double h, Constellation a, const vector<phaseVec>& k2){
  //idem as before
  a.addT(h/2);
  a.addVec(k2/2);
  return h * driverFunc(a);
}
vector<phaseVec> RK4_4(const double h,  Constellation a, const vector<phaseVec>& k3){
  //idem as before
  a.addT(h);
  a.addVec(k3);
  return h * driverFunc(a);
}

void RK4(const double h, Constellation& a) {
  /*function to update constellation with 1 RK4 step of length h*/
  vector<phaseVec> k1 = RK4_1(h, a);
  vector<phaseVec> k2 = RK4_2(h, a, k1);
  vector<phaseVec> k3 = RK4_3(h, a, k2);
  vector<phaseVec> k4 = RK4_4(h, a, k3);
  a.addVec(k1 / 6 + k2 / 3 + k3 / 3 + k4 / 6);
  a.addT(h);
}

//Verlet integrator
//==============================================================================

void Verlet(const double h, Constellation& a, vector<phaseVec>& driver) {
  /*function to update constellation with 1 Verlet step of length h,
  requires initial driver function in order to avoid double calculation*/
  //update velocities to n+1/2
  a.addVec(h / 2 * driver);
  //update positions to n+1
  a.addVec(h * xpunt(a));
  //update velocities to n+1
  driver = gravity(a);
  a.addVec(h / 2 * driver);
  a.addT(h);
}

//implement embedded RK:
//==============================================================================

vector<phaseVec> RK45_1(const double h, const Constellation a) {
	return h * driverFunc(a);
}

vector<phaseVec> RK45_2(const double h, Constellation a, const vector<phaseVec>& K1) {
	a.addT(h / 4);
	a.addVec(K1 / 4);
	return h * driverFunc(a);
}

vector<phaseVec> RK45_3(const double h, Constellation a, const vector<phaseVec>& K1, const vector<phaseVec>& K2) {
	a.addT(h * 3 / 8);
	a.addVec(3.0 / 32 * K1 + 9.0 / 32 * K2);
	return h * driverFunc(a);
}

vector<phaseVec> RK45_4(const double h, Constellation a, const vector<phaseVec>& K1, const vector<phaseVec>& K2, const vector<phaseVec>& K3) {
	a.addT(12.0*h / 13);
	a.addVec(1932.0 / 2197 * K1 - 7200.0 / 2197 * K2 + 7296.0 / 2197 * K3);
	return h * driverFunc(a);
}

vector<phaseVec> RK45_5(const double h, Constellation a, const vector<phaseVec>& K1, const vector<phaseVec>& K2, const vector<phaseVec>& K3, const vector<phaseVec>& K4) {
	a.addT(h);
	a.addVec(439.0 / 216 * K1 - 8.0*K2 + 3680.0 / 513 * K3 - 845.0 / 4104 * K4);
	return h * driverFunc(a);
}

vector<phaseVec> RK45_6(const double h, Constellation a, const vector<phaseVec>& K1, const vector<phaseVec>& K2, const vector<phaseVec>& K3, const vector<phaseVec>& K4, const vector<phaseVec>& K5) {
	a.addT(h / 2);
	a.addVec(-8.0 / 27 * K1 + 2 * K2 - 3544.0 / 2565 * K3 + 1859.0 / 4104 * K4 - 11.0 / 40 * K5);
	return h * driverFunc(a);
}

void ERK5(const double h, Constellation& a, const vector<phaseVec>& K1, const vector<phaseVec>& K3, const vector<phaseVec>& K4, const vector<phaseVec>& K5, const std::vector<phaseVec>& K6) {
	a.addVec(16.0/135.0 * K1 + 6656.0/12825.0 * K3 + 28561.0 / 56430 * K4 - 9.0 / 50 * K5 + 2.0/55 * K6);
  a.addT(h);
}

void ERK4(const double h, Constellation& a, const vector<phaseVec>& K1, const vector<phaseVec>& K3, const vector<phaseVec>& K4, const vector<phaseVec>& K5) {
	a.addVec(25.0 / 216 * K1 + 1408.0 / 2565 * K3 + 2197.0 / 4104 * K4 - 1.0 / 5 * K5);
  a.addT(h);
}

double error(const Constellation& a, const Constellation& b) {
  /*function to evaluate difference between two constellations. Takes maximum
  absolute distance between the positions of the corresponding body's*/
  size_t N = a.N();
  double output = 0;
  for (size_t i=0; i!=N; ++i) {
    double err = (a.body(i).pos() - b.body(i).pos()).r();
    if (err > output) {
      output = err;
    }
  }
  return output;
}

void ERK(const double h, Constellation& a) {
  /*function to update constellation with one RK step (fifth order) with
  step h*/
  vector<phaseVec> K1 = RK45_1(h, a);
  vector<phaseVec> K2 = RK45_2(h, a, K1);
  vector<phaseVec> K3 = RK45_3(h, a, K1, K2);
  vector<phaseVec> K4 = RK45_4(h, a, K1, K2, K3);
  vector<phaseVec> K5 = RK45_5(h, a, K1, K2, K3, K4);
  vector<phaseVec> K6 = RK45_6(h, a, K1, K2, K3, K4, K5);

  ERK5(h, a, K1, K3, K4, K5, K6);
}

void ERK_VAR(const double h_upper, double h_lower, double& h, Constellation& a) {
  /*function to update constellation with one RK step (fifth order),
  with adaptive step so the maximum position distance between fourth and fifth
  order is between h_upper and h_lower. Changes h to this parameter*/
  Constellation b1;
  Constellation b2;
  double err;
  do { //do-while loop to ensure 1 step is taken
    //do a step of RK in fifth and fourth order
    vector<phaseVec> K1 = RK45_1(h, a);
    vector<phaseVec> K2 = RK45_2(h, a, K1);
    vector<phaseVec> K3 = RK45_3(h, a, K1, K2);
    vector<phaseVec> K4 = RK45_4(h, a, K1, K2, K3);
    vector<phaseVec> K5 = RK45_5(h, a, K1, K2, K3, K4);
    vector<phaseVec> K6 = RK45_6(h, a, K1, K2, K3, K4, K5);
    //make a copy of the original constellation
    b1 = a;
    b2 = a;
    ERK4(h, b1, K1, K3, K4, K5);
    ERK5(h, b2, K1, K3, K4, K5, K6);
    //calculate the difference
    err = error(b1, b2);
    //make h smaller. Repeat if difference is to big.
    h /= 2;
  } while (err > h_upper);
  if (err < h_lower) {
    h *= 2;
  }
  //if error is ok, update original constellation and undo last halving of h
  /*alternative implementation to avoid redoubling h would be breaking out
  of the loop if error is ok*/
  a = b2;
  h *= 2;
}

//Forest Ruth
//==============================================================================
const double theta = 1.35120719195966;

void FR(const double h, Constellation& a) {
	//step 1
  a.addVec(xpunt(a) * theta / 2 * h);
  a.addVec(gravity(a) * theta * h);
  //step 2
  a.addVec(xpunt(a) * (1 - theta) / 2 * h);
  a.addVec(gravity(a) * (1 - 2*theta) * h);
	//step 3
  a.addVec(xpunt(a) * (1 - theta) / 2 * h);
  a.addVec(gravity(a) * theta * h);
	//final evaluation of the position and time update
  a.addVec(xpunt(a) * theta / 2 * h);
  a.addT(h);
}

//Loop Methods
//==============================================================================
void run(const string method, const double h, const double endTime, const size_t printInterval, const string filename, Constellation a) {
  /*function to loop integrator with fixed time step, until time passes endTime
  outputs to datafiles every printInterval points*/

  //create and reset datafile f
  string outfile = "data/" + filename;
  ofstream f(outfile, ios::trunc);
  f << "#{tijd} #{positie1} #{...} \n";
  f << "#";
  for (size_t i=0; i!=a.N(); ++i) {
    f << sep << a.body(i).name();
  }
  f << "\n";
  f << setprecision(10);
  f.close();
  //create and reset datafile for energy g
  string outfile_Energy = "dataEnergy/" + filename;
  ofstream g(outfile_Energy, ios::trunc);
  g << "#{tijd} #Energiefout \n";
  g << setprecision(15);
  g.close();
  //pick integrator and loop
  if (method == "RK4") {
    for (size_t i=0; i*h<=endTime; ++i) {
      if (i%printInterval == 0) {
        //print data only every printInterval points.
        a.printFile(outfile);
        a.printEnergy(outfile_Energy);
      }
      //update constellation
      RK4(h, a);
      steps += 1;
    }
  } else if (method == "FR") {
    for (size_t i=0; i*h<=endTime; ++i) {
      if (i%printInterval == 0) {
        //print data only every printInterval points.
        a.printFile(outfile);
        a.printEnergy(outfile_Energy);
      }
      //update constellation
      FR(h, a);
      steps += 1;
    }
  } else if (method == "ERK") {
    for (size_t i=0; i*h<=endTime; ++i) {
      if (i%printInterval == 0) {
        //print data only every printInterval points.
        a.printFile(outfile);
        a.printEnergy(outfile_Energy);
      }
      //update constellation
      ERK(h, a);
      steps += 1;
    }
  } else if (method == "VER") {
    //initialize driver outside of update function to avoid calculating twice
    vector<phaseVec> driver = gravity(a);
    for (size_t i=0; i*h<=endTime; ++i) {
      if (i%printInterval == 0) {
        //print data only every printInterval points.
        a.printFile(outfile);
        a.printEnergy(outfile_Energy);
      }
      Verlet(h, a, driver);
      steps += 1;
    }
  } else {
    cout << "method not recognised" << endl;
  }
}

void run(const string method, double h_upper, double h_lower, const double endTime, const size_t printInterval, const string filename, Constellation a) {
  /*function to loop integrator with fixed time step, until time passes endTime
  outputs to datafiles every printInterval points*/

  //create and reset datafile f
  string outfile = "data/" + method + filename;
  ofstream f(outfile, ios::trunc);
  f << "#{tijd} #{positie1} #{...} \n";
  f << "#";
  for (size_t i=0; i!=a.N(); ++i) {
    f << sep << a.body(i).name();
  }
  f << "\n";
  f << setprecision(10);
  f.close();
  //create and reset datafile for energy g
  string outfile_Energy = "dataEnergy/" + method + filename;
  ofstream g(outfile_Energy, ios::trunc);
  g << "#{tijd} #Energiefout \n";
  g << setprecision(15);
  g.close();
  //pick integrator and loop
  if (method == "ERK_VAR") {
    size_t i = 0;
    double h = 1;
    while (a.time() < endTime) {
      if (i%printInterval == 0) {
        //print data only every printInterval points.
        a.printFile(outfile);
        a.printEnergy(outfile_Energy);
      }
      ERK_VAR(h_upper, h_lower, h, a);
      i += 1;
      steps += 1;
    }
  } else {
    cout << "method not recognised" << endl;
  }
}
