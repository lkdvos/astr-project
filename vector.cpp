#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "vector.h" // include header
using namespace std;


Vec::double r() const { return sqrt(_x*_x + _y * _y + _z * _z); }
Vec::double r2() const { return _x * _x + _y * _y + _z * _z; }
Vec::double mult(Vec u) const { return _x*u._x + _y*u._y + _z*u._z; }

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

Vec& operator*=(Vec v) {
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

void print(double s)
{
	cout << s << endl;
}

int main() {

	double s = 2;
	Vec a(1,2,3);
	Vec b(3,4,5);
	print(a*b);
	print(s*a);
	print(a / s);
	print(a.r());
	print(a.mult(b));
}
