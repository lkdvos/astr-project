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
//implement class for 3D vectors with operators and assignment operators
//
//==============================================================================

double Vec::r() const { return sqrt(_x*_x + _y * _y + _z * _z); }
double Vec::r2() const { return _x * _x + _y * _y + _z * _z; }
double Vec::mult(Vec u) const { return _x*u._x + _y*u._y + _z*u._z; }

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

Vec operator+(Vec a, Vec b) { return a += b; }
Vec operator-(Vec a, Vec b) { return a -= b; }
Vec operator*(Vec a, Vec b) { return a *= b; }

Vec operator*(Vec a, double s) { return a *= s; }
Vec operator*(double s, Vec a) { return a *= s; }

Vec operator/(double s, Vec a) { return a /= s; }
Vec operator/(Vec a, double s) { return a /= s; }

void print(Vec a)
{
	cout << '(' << a.x() << ',' << a.y() << ',' << a.z() << ')' << endl;
}

//==============================================================================

void print(double s)
{
	cout << s << endl;
}

//==============================================================================
//
//implement class for 6D vectors containing position and velocity
//
//==============================================================================

//getters
Vec phaseVec::pos() const { return _x; }
Vec phaseVec::vel() const { return _v; }


//assignment operators
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

//operators
phaseVec operator+(phaseVec a, phaseVec b) { return a += b; }
phaseVec operator-(phaseVec a, phaseVec b) { return a -= b; }

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

//body/phaseVec operators
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

//==============================================================================
//
//create operations for vector<Body> adding/multiplication/etc
//
//==============================================================================

vector<Body> operator+(vector<Body> a,vector<phaseVec> b) {
	//todo: add check for size of vectors...
	vector<Body> output(a.size());
	for (size_t i=0; i!=a.size(); ++i) {
		output.push_back(a[i] += b[i]);
	}
	return output;
}

vector<Body> operator-(vector<Body> a,vector<phaseVec> b) {
	//todo: add check for size of vectors...
	vector<Body> output(a.size());
	for (size_t i=0; i!=a.size(); ++i) {
		output.push_back(a[i] -= b[i]);
	}
	return output;
}

vector<phaseVec> operator/(vector<phaseVec> a, double s) {
	//todo: add check for size of vectors...
	vector<phaseVec> output(a.size());
	for (size_t i=0; i!=a.size(); ++i) {
		output.push_back(a[i] /= s);
	}
	return output;
}

vector<phaseVec> operator*(vector<phaseVec> a, double s) {
	//todo: add check for size of vectors...
	vector<phaseVec> output(a.size());
	for (size_t i=0; i!=a.size(); ++i) {
		output.push_back(a[i] *= s);
	}
	return output;
}

vector<phaseVec> operator*(double s, vector<phaseVec> a) {
	//todo: add check for size of vectors...
	vector<phaseVec> output(a.size());
	for (size_t i=0; i!=a.size(); ++i) {
		output.push_back(a[i] *= s);
	}
	return output;
}

//==============================================================================
//
//implement class for a constellation of (variable) N bodys
//
//==============================================================================

//constructor
Constellation::Constellation() {
	double _t = 0;
	vector<Body> _y;
	double _E = calcE();
}

Constellation::Constellation(vector<Body> y) {
	double _t = 0;
	vector<Body> _y = y;
	double _E = calcE();
}

//getters
Body Constellation::particle(size_t n) {
	return _y[n];
}

double Constellation::time() {
	return _t;
}

double Constellation::energy() {
	return _E;
}

double Constellation::calcE(){
	return 0;
}

vector<phaseVec> driverFunc(double t, vector<Body> y) {
	vector<phaseVec> output(y.size());
	for (size_t i=0; i!=y.size(); ++i) {
		Vec v_punt(0, 0); //todo add driver function
		output.push_back(phaseVec());


	}
	return output;
}

void Constellation::RK4update(const double h) {
	vector<phaseVec> k_1 = h * driverFunc(_t, _y);
	vector<phaseVec> k_2 = h * driverFunc(_t + (h/2), _y + (k_1/2) );
	vector<phaseVec> k_3 = h * driverFunc(_t + (h/2), _y + (k_2/2) );
	vector<phaseVec> k_4 = h * driverFunc(_t + h, _y + k_3);
	_y = _y + k_1/6 + k_2/3 + k_3/3 + k_4/6;
	_t += h;
}

void Constellation::print() {
	cout << _t << ' ' << _E << ' ' << endl;
}
