#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "main.h"
using namespace std;


int main() {


//create first body
  Body sun(1, 0, 0, 0, 0.5, 0, 1);
  Body earth(-1, 0, 0, 0, -0.5, 0, 1);
  vector<Body> y = {sun, earth};
  Constellation a(y);
  for (size_t i=0; i != 100; ++i) {
      a.print();
      a.RK4update(0.1);
  }


}
