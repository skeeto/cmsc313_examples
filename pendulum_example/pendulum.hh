#ifndef PENDULUM_HH
#define PENDULUM_HH

#include <iostream>
#include "vec.hh"
#include "spring.hh"
#include "particle.hh"

template <typename T>
class Pendulum {
public:
  Vec<T> anchor {0.0f, 1.0f};
  Particle<T> p1 {1.0f, 0.5f, 1.0f, 0.0f, 0.0f},
              p2 {1.0f, 1.0f, 1.0f, 0.0f, 0.0f};
  Spring<T> s1 {&anchor, &p1.position, 100.0},
            s2 {&p1.position, &p2.position, 100.0};

  void step(T dt);
};

std::ostream &operator<<(std::ostream &out, const Pendulum<double>& p);
std::ostream &operator<<(std::ostream &out, const Pendulum<float>& p);

#endif
