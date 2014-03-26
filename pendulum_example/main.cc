#include <iostream>
#include "pendulum.hh"

const double kPi = 3.14159265358979323846;

int main() {
  Vec<float> a {1.1, 2.0}, b {1.0, 1.0};
  std::cout << (a - b) << std::endl;
  Pendulum<double> p;
  std::cout << p << std::endl;
  return 0;
}
