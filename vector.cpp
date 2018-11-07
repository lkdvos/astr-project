#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

class Vec {
	double _x;
	double _y;
	double _z;

public:
	Vec() { _x = 0; _y = 0; _z = 0; }
	Vec(double x, double y, double z) { _x = x;  _y = y; _z = z; }

	double x() const { return _x; }
	double y() const { return _y; }
	double z() const { return _z; }

	double r() const { return sqrt(_x*_x + _y * _y + _z * _z); }
	double r2() const { return _x * _x + _y * _y + _z * _z; }
	double mult(Vec u) const { return _x*u._x + _y*u._y + _z*u._z; }

	Vec& operator+=(Vec v) {
		_x += v._x;
		_y += v._y;
		_z += v._z;
		return *this;
	}

	Vec& operator-=(Vec v) {
		_x -= v._x;
		_y -= v._y;
		_z -= v._z;
		return *this;
	}

	Vec& operator*=(double s) {
		_x *= s;
		_y *= s;
		_z *= s;
		return *this;
	}

	Vec& operator/=(double s) {
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
};

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