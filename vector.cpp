//==============================================================================
//
//.cpp file for all necessary data types for project
//
//==============================================================================

#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "vector.h" // include header
using namespace std;

//==============================================================================
//
//define some constants
//
//==============================================================================

//define seperator for data files
const char sep = '\t';
//const double G = 6.67408 * pow(10, -11);
const double G = 1;


//==============================================================================
//
//implement class for 3D vectors with operators and assignment operators
//
//==============================================================================


//implement norm functions
double Vec::r() const { return sqrt(_x * _x + _y * _y + _z * _z); }
double Vec::r2() const { return _x * _x + _y * _y + _z * _z; }
double Vec::r3() const { return r()*r2(); }
//implement inproduct
double Vec::mult(Vec u) const { return _x*u._x + _y*u._y + _z*u._z; }

//implement assignment operators for Vec
//==============================================================================

Vec& Vec::operator+=(Vec v) {
	_x += v._x;
	_y += v._y;
	_z += v._z;
	return *this;
}

Vec& Vec::operator-=(Vec v) {
	_x -= v._x;
	_y -= v._y;
	_z -= v._z;
	return *this;
}

Vec& Vec::operator*=(double s) {
	_x *= s;
	_y *= s;
	_z *= s;
	return *this;
}

Vec& Vec::operator/=(double s) {
	_x /= s;
	_y /= s;
	_z /= s;
	return *this;
}

Vec& Vec::operator*=(Vec v) {
	double a = _x;
	double b = _y;
	double c = _z;
	_x = b* v._z - c * v._y;
	_y = c * v._x - a * v._z;
	_z = a * v._y - b * v._x;
	return *this;
}
//==============================================================================
//implement operator functions between Vec and double

Vec operator+(Vec a, Vec b) { return a += b; }
Vec operator-(Vec a, Vec b) { return a -= b; }
Vec operator*(Vec a, Vec b) { return a *= b; }

Vec operator*(Vec a, double s) { return a *= s; }
Vec operator*(double s, Vec a) { return a *= s; }

Vec operator/(double s, Vec a) { return a /= s; }
Vec operator/(Vec a, double s) { return a /= s; }

//==============================================================================
//implement printing operator for Vec

ostream& operator<<(ostream& os, const Vec& a) {
	os << a.x() << sep << a.y() << sep << a.z();
	return os;
}

//==============================================================================
//
//implement class for 2*3D vectors containing position and velocity
//
//==============================================================================

//getters
Vec phaseVec::pos() const { return _x; }
Vec phaseVec::vel() const { return _v; }
double phaseVec::x() const { return _x.x(); }
double phaseVec::y() const { return _x.y(); }
double phaseVec::z() const { return _x.z(); }
double phaseVec::v_x() const { return _v.x(); }
double phaseVec::v_y() const { return _v.y(); }
double phaseVec::v_z() const { return _v.z(); }

//assignment operators for phaseVec
//==============================================================================
phaseVec& phaseVec::operator+=(phaseVec v) {
	_x += v._x;
	_v += v._v;
	return *this;
}

phaseVec& phaseVec::operator-=(phaseVec v) {
	_x -= v._x;
	_v -= v._v;
	return *this;
}

phaseVec& phaseVec::operator*=(double s) {
	_x *= s;
	_v *= s;
	return *this;
}

phaseVec& phaseVec::operator/=(double s) {
	_x /= s;
	_v /= s;
	return *this;
}

//operators for phaseVec
//==============================================================================

phaseVec operator+(phaseVec a, phaseVec b) { return a += b; }
phaseVec operator-(phaseVec a, phaseVec b) { return a -= b; }
phaseVec operator*(phaseVec a, double s) { return a *= s; }
phaseVec operator/(phaseVec a, double s) { return a /= s; }

//==============================================================================
//
//implement class for a body in the system
//
//==============================================================================

//constructor
Body::Body(double x, double y, double z, double v_x, double v_y, double v_z, double m) {
	_x = Vec(x, y, z);
	_v = Vec(v_x, v_y, v_z);
	_m = m;
}

//getter
double Body::x() const { return _x.x(); }
double Body::y() const { return _x.y(); }
double Body::z() const { return _x.z(); }
double Body::v_x() const { return _v.x(); }
double Body::v_y() const { return _v.y(); }
double Body::v_z() const { return _v.z(); }

//body assignment operators
//==============================================================================
Body& Body::operator+=(phaseVec b) {
	_x += b.pos();
	_v += b.vel();
	return *this;
}

Body& Body::operator-=(phaseVec b) {
	_x -= b.pos();
	_v -= b.vel();
	return *this;
}

Body& Body::operator*=(double s) {
	_x *= s;
	_v *= s;
	return *this;
}

Body& Body::operator/=(double s) {
	_x /= s;
	_v /= s;
	return *this;
}

//operators for the class body
//==============================================================================
Body operator+(Body b, phaseVec v) { return b += v; }
Body operator-(Body b, phaseVec v) { return b -= v; }
Body operator*(Body b, double s) { return b *= s; }
Body operator/(Body b, double s) { return b /= s; }


//==============================================================================
//
//create operations for vector<Body> adding/multiplication/etc
//
//==============================================================================

vector<Body> operator+(vector<Body> a,vector<phaseVec> b) {
	//todo: add check for size of vectors...
	vector<Body> output(a.size());
	for (size_t i=0; i!=a.size(); ++i) {
		output[i] = a[i] + b[i];
	}
	return output;
}

vector<Body> operator-(vector<Body> a,vector<phaseVec> b) {
	//todo: add check for size of vectors...
	vector<Body> output(a.size());
	for (size_t i=0; i!=a.size(); ++i) {
		output[i] = a[i] - b[i];
	}
	return output;
}

vector<Body> operator+(vector<Body> a, phaseVec v) {
	vector<Body> output(a.size());
	for (size_t i=0; i!=a.size(); ++i) {
		output[i] = a[i] + v;
	}
	return output;
}

vector<phaseVec> operator+(vector<phaseVec> v, vector<phaseVec> w) {
	vector<phaseVec> output(v.size());
	for (size_t i=0; i!=v.size(); ++i) {
		output[i] = v[i] + w[i];
	}
	return output;
}
vector<phaseVec> operator-(vector<phaseVec> v, vector<phaseVec> w) {
	vector<phaseVec> output(v.size());
	for (size_t i=0; i!=v.size(); ++i) {
		output[i] = v[i] - w[i];
	}
	return output;
}

vector<phaseVec> operator/(vector<phaseVec> a, double s) {
	//todo: add check for size of vectors...
	vector<phaseVec> output(a.size());
	for (size_t i=0; i!=a.size(); ++i) {
		output[i] = a[i] / s;
	}
	return output;
}

vector<phaseVec> operator*(vector<phaseVec> a, double s) {
	//todo: add check for size of vectors...
	vector<phaseVec> output(a.size());
	for (size_t i=0; i!=a.size(); ++i) {
		output[i] = a[i] * s;
	}
	return output;
}

vector<phaseVec> operator*(double s, vector<phaseVec> a) {
	//todo: add check for size of vectors...
	vector<phaseVec> output(a.size());
	for (size_t i=0; i!=a.size(); ++i) {
		output[i] = a[i] * s;
	}
	return output;
}

//OPERATOR FOR PRINTING BODY
//==============================================================================
ostream& operator<<(ostream& os, const Body& b) {
	os << b.pos() << sep << b.vel();
	return os;
}

ostream& operator<<(ostream& os, const phaseVec& v) {
	os << v.pos() << sep << v.vel();
	return os;
}


//==============================================================================
//
//implement class for a constellation of (variable) N bodys
//
//==============================================================================

//constructor
Constellation::Constellation() {
	_t = 0;
	_E = calcEtot();
}

Constellation::Constellation(vector<Body> y) {
	_t = 0;
	_y = y;
	_E = calcEtot();
}

//getters
size_t Constellation::N() const {
	return _y.size();
}

Body Constellation::body(size_t n) const {
	return _y[n];
}

double Constellation::time() const {
	return _t;
}

double Constellation::energy() const {
	return _E;
}

//function for adding a body after creation
//==============================================================================
void Constellation::addBody(Body y_n) {
	_y.push_back(y_n);
	_E = calcEtot();
}

//functions for calculating energy of configuration
//==============================================================================
double Constellation::calcEpot() const {
	double output = 0;
	for (size_t i=0; i!=N(); ++i) {
		output += 0.5 * _y[i].m() * _y[i].vel().r2();
	}
	return output;
}

double Constellation::calcEkin() const {
	double output = 0;
	for (size_t i=0; i!=N(); ++i) {
		for (size_t j=0; j!=N(); ++j) {
			if (i != j) {
				output += G * _y[i].m() * _y[j].m() / (_y[i].pos() - _y[j].pos()).r();
			}
		}
	}
	return output / 2;
}

double Constellation::calcEtot() const {
	return calcEpot() + calcEkin();
}

//Update Constellation
//==============================================================================

void Constellation::addVec(const vector<phaseVec>& y) {
	_y = _y + y;
}

void Constellation::addT(double t) {
	_t += t;
}

void Constellation::transform(const phaseVec& y_n) {
	_y = _y + y_n;
}

//functions for printing the current Constellation
//==============================================================================

void Constellation::print() const {
	cout << "time " << _t << sep << "energy " << _E << sep;
	cout << "size " << _y.size() << endl;
	for (size_t i=0; i!=_y.size(); ++i) {
		cout << "body" << i << sep << _y[i] << endl;
	}
	cout << endl;
}

void Constellation::printFile(const string outfile) const {
	ofstream f;
	f.open(outfile, ios::app);
	f << setprecision(15);


	f << _t;
	for (size_t i=0; i!=_y.size(); ++i) {
		f << sep << _y[i];
	}
	f << '\n';

	f.close();
}

//==============================================================================
//
//printing/debugging neccesities
//
//==============================================================================

void printer(vector<phaseVec> k) {
	cout << "vector of phaseVecs containing: " << endl;
	for (size_t i=0; i!=k.size(); ++i) {
		cout << "elem" << i << sep << k[i] << endl;
	}
}

void printer(vector<Body> y) {
	cout << "vector of Bodies containing: " << endl;
	for (size_t i=0; i!=y.size(); ++i) {
		cout << "elem" << i << '\t' << y[i] << endl;
	}
}

void printer(double s)
{
	cout << s << endl;
}

void printer(Vec a)
{
	cout << '(' << a.x() << ',' << a.y() << ',' << a.z() << ')' << endl;
}
