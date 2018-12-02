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

extern double G;

//implement driver function on a Constellation
//==============================================================================

vector<phaseVec> gravity(const Constellation& a) {
  //create output vector of size N
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

vector<phaseVec> speed(const Constellation& a) {
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
  //create output vector of size N
  size_t N = a.N();
  //fill in v_punt
  vector<phaseVec> output = gravity(a);

  //fill in x_punt
  for (size_t i=0; i!=N; ++i) {
    Vec x_punt = a.body(i).vel();
    Vec v_punt;
    output[i] += phaseVec(x_punt, v_punt);
  }
	return output;
}

//implement RK4 integrator:
//==============================================================================

vector<phaseVec> k_1(const double h, Constellation a) {
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

void RK41(const double h, Constellation& a) {
  a.addVec(k_1(h, a) / 6 + k_2(h, a) / 3 + k_3(h, a) / 3 + k_4(h, a) / 6);
  a.addT(h);
}

void RK4(const double h, const size_t steps, const size_t printInterval, const string filename, Constellation a) {
  //create datafile (also resets the file)
  string outfile = "data/" + filename + "RK4.txt";
  ofstream f(outfile, ios::trunc);
  f << "#{tijd} #{positie1} #{snelheid1} #{...} \n";
  f << setprecision(5);
  f.close();


  string outfile_Energy = "data/" + filename + "RK4_Energy.txt";
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

    //update constellation
    RK41(h, a);
  }

}

//Verlet integrator
//==============================================================================

void Verlet1(const double h, Constellation& a, vector<phaseVec>& driver) {
  //update velocities to n+1/2
  a.addVec(h / 2 * driver);

  //update positions to n+1
  a.addVec(h * speed(a));

  //update velocities to n+1
  driver = gravity(a);
  a.addVec(h / 2 * driver);
  a.addT(h);

}



void Verlet(const double h, const size_t steps, const size_t printInterval, const string filename, Constellation a) {
  //create datafile (also resets the file)
  string outfile = "data/" + filename + "Verlet.txt";
  ofstream f(outfile, ios::trunc);
  f << "#{tijd} #{positie1} #{snelheid1} #{...} \n";
  f << setprecision(5);
  f.close();


  string outfile_Energy = "data/" + filename + "Verlet_Energy.txt";
  ofstream g(outfile_Energy, ios::trunc);
  g << "#{tijd} #Energiefout \n";
  g << setprecision(5);
  g.close();

  //initialize driver outside of update function to avoid calculating twice
  vector<phaseVec> driver = gravity(a);
  for (size_t i=0; i!=steps; ++i) {
    if (i%printInterval == 0) {
      //print data only every printInterval points.
      a.printFile(outfile);
      a.printEnergy(outfile_Energy);
    }
    Verlet1(h, a, driver);
  }
}

//implement embedded RK:
//==============================================================================

vector<phaseVec> K_1(const double h, const Constellation a) {
	return h * driverFunc(a);
}

vector<phaseVec> K_2(const double h, Constellation a) {
	a.addT(h / 4);
	a.addVec(K_1(h, a) / 4);
	return h * driverFunc(a);
}

vector<phaseVec> K_3(const double h, Constellation a) {
	a.addT(3.0*h / 8);
	a.addVec(3.0 / 32 * K_1(h, a) + 9.0 / 32 * K_2(h, a));
	return h * driverFunc(a);
}

vector<phaseVec> K_4(const double h, Constellation a) {
	a.addT(12.0*h / 13);
	a.addVec(1932.0 / 2197 * K_1(h, a) - 7200.0 / 2197 * K_2(h, a) + 7296.0 / 2197 * K_3(h, a));
	return h * driverFunc(a);
}

vector<phaseVec> K_5(const double h, Constellation a) {
	a.addT(h);
	a.addVec(439.0 / 216 * K_1(h, a) - 8.0*K_2(h, a) + 3680.0 / 513 * K_3(h, a) - 845.0 / 4104 * K_4(h, a));
	return h * driverFunc(a);
}

vector<phaseVec> K_6(const double h, Constellation a) {
	a.addT(h / 2);
	a.addVec(-8.0 / 27 * K_1(h, a) + 2 * K_2(h, a) - 3544.0 / 2565 * K_3(h, a) + 1859.0 / 4104 * K_4(h, a) - 11.0 / 40 * K_5(h, a));
	return h * driverFunc(a);
}

void ERK1(const double h, Constellation& a) {
	a.addVec(25.0 / 216 * K_1(h, a) + 1408.0 / 2565 * K_3(h, a) + 2197.0 / 4104 * K_4(h, a) - 1.0 / 5 * K_5(h, a));
  a.addT(h);
}

void ERK(const double h, const size_t steps, const size_t printInterval, const string filename, Constellation a) {
  //create datafile (also resets the file)
  string outfile = "data/" + filename + "ERK.txt";
  ofstream f(outfile, ios::trunc);
  f << "#{tijd} #{positie1} #{snelheid1} #{...} \n";
  f << setprecision(5);
  f.close();

  string outfile_Energy = "data/" + filename + "ERK_Energy.txt";
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

    //update constellation
    ERK1(h, a);
  }
}


//Forest Ruth
//==============================================================================

const double theta = 1.35120719195966;

vector<Vec> accel(Constellation a, vector<Vec> x_change) {
	const size_t N = a.N();
	vector<Vec> out(N);
	for (size_t i = 0; i != N; ++i) {
		Vec v_punt;
		for (size_t j = 0; j != N; ++j) {
			if (j != i) {
				Vec r_rel= a.body(i).pos() + x_change[i] - a.body(j).pos() - x_change[j];
				v_punt -= G * a.body(j).m()* r_rel / r_rel.r3();
			}
		}
		out[i] = v_punt;
	}
	return out;
}

vector<phaseVec> FR1(double h, Constellation a) {
	const size_t N = a.N();
	vector<Vec> v(N);
	vector<Vec> x(N);
	vector<phaseVec> out(N);
	for (size_t i=0; i != N; ++i) {
		v[i] = a.body(i).vel();
		x[i] = a.body(i).pos();
	}

	//step 1

	vector<Vec> x1(N);
	vector<Vec> v1(N);
	vector<Vec> ac1(N);
	for (size_t i=0; i != N; ++i) {
		x1[i] = theta / 2 * h*v[i];
	}
	ac1 = accel(a, x1);
	for (size_t i=0; i != N; ++i) {
		v1[i] = theta * h*ac1[i];
	}

	//step 2

	vector<Vec> x2(N);
	vector<Vec> v2(N);
	vector<Vec> ac2(N);

	for (size_t i=0; i != N; ++i) {
		x2[i] = x1[i] + 1 / 2 * (1 - theta)*h*(v[i] + v1[i]);
	}
	ac2 = accel(a, x2);
	for (size_t i=0; i != N; ++i) {
		v2[i] = v1[i] + (1 - 2 * theta)*h*ac2[i];
	}

	//step 3

	vector<Vec> x3(N);
	vector<Vec> v3(N);
	vector<Vec> ac3(N);

	for (size_t i=0; i != N; ++i) {
		x3[i] = x2[i] + 1 / 2 * (1 - theta)*h*(v[i] + v2[i]);
	}
	ac3 = accel(a, x3);
	for (size_t i=0; i != N; ++i) {
		v3[i] = v2[i] + theta * h*ac3[i];
	}

	//final evaluation of the position and the return

	vector<Vec> x4(N);
	for (size_t i=0; i != N; ++i) {
		x4[i] = x3[i] + theta / 2 * h*(v[i] + v3[i]);
	}

	for (size_t i=0; i != N; ++i) {
		out[i] = phaseVec(x4[i], v3[i]);
	}
	return out;
}

void FR(const double h, const size_t steps, const size_t printInterval, const string filename, Constellation a) {
  //create datafile (also resets the file)
  string outfile = "data/" + filename + "FR.txt";
  ofstream f(outfile, ios::trunc);
  f << "#{tijd} #{positie1} #{snelheid1} #{...} \n";
  f << setprecision(5);
  f.close();

  string outfile_Energy = "data/" + filename + "FR_Energy.txt";
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

    //update constellation
    a.addVec(FR1(h, a));
    a.addT(h);
  }
}
