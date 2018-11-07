#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

#ifndef VECTOR_H
#define VECTOR_H
#endif

class Vec {
	double _x;
	double _y;
	double _z;

public:

//constructor
	Vec() { _x = 0; _y = 0; _z = 0; }
	Vec(double x, double y, double z) { _x = x;  _y = y; _z = z; }

//getter
	double x() const { return _x; }
	double y() const { return _y; }
	double z() const { return _z; }

//define norm
	double r() const;
	double r2() const;
  
 //define inproduct
	double mult(Vec u) const;

//define assignment operators
	Vec& operator+=(Vec v);
	Vec& operator-=(Vec v);
	Vec& operator*=(double s);
	Vec& operator/=(double s);
	Vec& operator*=(Vec v);
};


//define vector/vector operators
Vec operator+(Vec a, Vec b);
Vec operator-(Vec a, Vec b);
Vec operator*(Vec a, Vec b);

//define vector/scalar operators
Vec operator*(Vec a, double s);
Vec operator*(double s, Vec a);
Vec operator/(double s, Vec a);
Vec operator/(Vec a, double s);

//function for printing vectors
void print(Vec a);

//function for printing scalars
void print(double s);
