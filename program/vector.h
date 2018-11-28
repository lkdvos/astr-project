//==============================================================================
//
//header file for all necessary data types for project
//
//==============================================================================

//safeguard includes
#ifndef VECTOR_H
#define VECTOR_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

//==============================================================================
//
//create class for 3D vectors with operators and assignment operators
//
//==============================================================================
//define seperator for data files
const char sep = '\t';
//const double G = 6.67408 * pow(10, -11);
extern double G;
extern double xscale;
extern double tscale;
extern double Mscale;

class Vec {
	double _x;
	double _y;
	double _z;

public:

//constructor
	Vec() { _x = 0; _y = 0; _z = 0; }
	Vec(double x, double y) { _x = x; _y = y; _z = 0; }
	Vec(double x, double y, double z) { _x = x;  _y = y; _z = z; }


//getter
	double x() const { return _x; }
	double y() const { return _y; }
	double z() const { return _z; }

//declare norm functions
	double r() const;
	double r2() const;
	double r3() const;

//declare inproduct
	double mult(Vec u) const;

//declare assignment operators
	Vec& operator+=(Vec v);
	Vec& operator-=(Vec v);
	Vec& operator*=(double s);
	Vec& operator/=(double s);
	Vec& operator*=(Vec v);

//friend function for acces to private class data
	friend ostream& operator<<(ostream& os, const Vec& a);
};

//declare operator for printing
ostream& operator<<(ostream& os, const Vec& a);

//declare vector/vector operators
Vec operator+(Vec a, Vec b);
Vec operator-(Vec a, Vec b);
Vec operator*(Vec a, Vec b);

//declare vector/scalar operators
Vec operator*(Vec a, double s);
Vec operator*(double s, Vec a);
Vec operator/(double s, Vec a);
Vec operator/(Vec a, double s);

//==============================================================================
//
//create class for 2*3D vectors containing position and velocity
//
//==============================================================================

class phaseVec {
	Vec _x;
	Vec _v;

public:

//constructor
	phaseVec() { _x = Vec(); _v = Vec(); }
	phaseVec(Vec pos, Vec vel) { _x = pos; _v = vel; }

//getter
	Vec pos() const;
	Vec vel() const;
	double x() const;
	double y() const;
	double z() const;
	double v_x() const;
	double v_y() const;
	double v_z() const;

//declare assignment operators
	phaseVec& operator+=(phaseVec v);
	phaseVec& operator-=(phaseVec v);
	phaseVec& operator*=(double s);
	phaseVec& operator/=(double s);

//print operators
	friend ostream& operator<<(ostream& os, const phaseVec& v);
};

ostream& operator<<(ostream& os, const phaseVec& v);

//declare phasevector/phasevector operators
phaseVec operator+(phaseVec a, phaseVec b);
phaseVec operator-(phaseVec a, phaseVec b);
phaseVec operator*(phaseVec a, double s);
phaseVec operator/(phaseVec a, double s);

//==============================================================================
//
//create class for a body in the system
//
//==============================================================================

class Body {
//class that represents a body with a position _x, velocity _v and mass _m
	Vec _x;
	Vec _v;
	double _m;

public:

//constructor
	Body() { _x = Vec(); _v = Vec(); _m = 1; }
	Body(double mass) { _x = Vec(); _v = Vec(); _m = mass; }
	Body(Vec pos, Vec vel, double mass) { _x = pos; _v = vel; _m = mass; }
	Body(double x, double y, double z, double v_x, double v_y, double v_z, double m);


//getter
	Vec pos() const { return _x; }
	Vec vel() const { return _v; }
	double m() const { return _m; }
	double x() const;
	double y() const;
	double z() const;
	double v_x() const;
	double v_y() const;
	double v_z() const;

//declare body/phaseVec assignment operators
	Body& operator+=(phaseVec b);
	Body& operator-=(phaseVec b);
	Body& operator/=(double s);
	Body& operator*=(double s);

//change body functions
	void changeMass(double factor);
	void changePos(double factor);
	void changeVel(double factor);

//operator for easy printing
//need friend function to acces private class data
	friend ostream& operator<<(ostream& os, const Body& b);
};

//declare body/phaseVec operators
Body operator+(Body b, phaseVec v);
Body operator-(Body b, phaseVec v);
Body operator/(Body b, double s);
Body operator*(Body b, double s);

ostream& operator<<(ostream& os, const Body& b);

//==============================================================================
//
//create operations for vector<phaseVec> adding/multiplication/etc
//create operations for vector<Body> adding
//
//==============================================================================

vector<Body> operator+(vector<Body> a, vector<phaseVec> b);
vector<Body> operator-(vector<Body> a, vector<phaseVec> b);
vector<Body> operator+(vector<Body> a, phaseVec b);
vector<phaseVec> operator+(vector<phaseVec> v, vector<phaseVec> w);
vector<phaseVec> operator-(vector<phaseVec> v, vector<phaseVec> w);
vector<phaseVec> operator*(vector<phaseVec> a, double s);
vector<phaseVec> operator*(double s, vector<phaseVec> a);
vector<phaseVec> operator/(vector<phaseVec> a, double s);

//==============================================================================
//
//create class for a constellation of (variable) N bodys
//
//==============================================================================

vector<phaseVec> driverFuncHelp(double t, vector<Body>& y);

class Constellation {
	double _t;
	double _E;
	vector<Body> _y;

public:

//constructor
	Constellation();
	Constellation(vector<Body> y);

//getter
	size_t N() const;
	Body body(size_t n) const;
	double time() const;
	double energy() const;

//add body after creation
	void addBody(Body y_n);

//rescale system
	void center();
	void rescale();
	void scaleMass(double Mtot=1);

//update system
	void addVec(const vector<phaseVec>& y);
	void addT(double t);
	void transform(const phaseVec& y_n);

//calculate properties
	double calcEpot() const;
	double calcEkin() const;
	double calcEtot() const;
	double totalMass() const;

//print state
	friend ostream& operator<<(ostream& os, const Constellation& y);
	void print() const;
	void printFile(const string outfile) const;
	void printEnergy(const string outfile) const;
};

ostream& operator<<(ostream& os, const Constellation& y);

//==============================================================================
//
//printing neccesities
//
//==============================================================================

void printer(double s);
void printer(Vec a);
void printer(vector<phaseVec> k);
void printer(vector<Body> y);

#endif
