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

//declare norm
	double r() const;
	double r2() const;

//declare inproduct
	double mult(Vec u) const;

//declare assignment operators
	Vec& operator+=(Vec v);
	Vec& operator-=(Vec v);
	Vec& operator*=(double s);
	Vec& operator/=(double s);
	Vec& operator*=(Vec v);
};


//declare vector/vector operators
Vec operator+(Vec a, Vec b);
Vec operator-(Vec a, Vec b);
Vec operator*(Vec a, Vec b);

//declare vector/scalar operators
Vec operator*(Vec a, double s);
Vec operator*(double s, Vec a);
Vec operator/(double s, Vec a);
Vec operator/(Vec a, double s);

//declare function for printing vectors
void print(Vec a);

//==============================================================================

//declare function for printing scalars
void print(double s);

//==============================================================================
//
//create class for 6D vectors containing position and velocity
//
//==============================================================================

class phaseVec {
//class that represents a 2*3D vector (position/velocity)
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
};

//declare phasevector/phasevector operators
phaseVec operator+(phaseVec a, phaseVec b);
phaseVec operator-(phaseVec a, phaseVec b);

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

//declare body/phaseVec operators
	Body& operator+=(phaseVec b);
	Body& operator-=(phaseVec b);
	Body& operator/=(double s);
	Body& operator*=(double s);

};

//==============================================================================
//
//create operations for vector<phaseVec> adding/multiplication/etc
//create operations for vector<Body> adding
//
//==============================================================================

vector<Body> operator+(vector<Body> a, vector<phaseVec> b);
vector<Body> operator-(vector<Body> a, vector<phaseVec> b);
vector<phaseVec> operator*(vector<phaseVec> a, double s);
vector<phaseVec> operator*(double s, vector<phaseVec> a);
vector<phaseVec> operator/(vector<phaseVec> a, double s);

//==============================================================================
//
//create class for a constellation of (variable) N bodys
//
//==============================================================================

class Constellation {
	double _t;
	double _E;
	vector<Body> _y;

public:

//constructor
	Constellation();
	Constellation(vector<Body> y);

//getter
	Body particle(size_t n);
	double time();
	double energy();

//evolve system
	void RK4update(double h);


//calculate energy
	double calcE();

//print state
	void print();
};

#endif
