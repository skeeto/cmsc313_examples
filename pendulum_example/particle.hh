#ifndef PARTICLE_HH
#define PARTICLE_HH

#include <iostream>
#include "vec.hh"
#include "particle.hh"

template <typename T>
class Particle {
 public:
  Particle(T mass, T x, T y, T dx, T dy)
      : mass{mass}, position{x, y}, velocity{dx, dy} {};
  const T mass;
  Vec<T> position, velocity;

  Vec<T> drag_force(T c) const;
  void step(const Vec<T> &force, T dt);
};

std::ostream &operator<<(std::ostream &out, const Particle<double> &p);
std::ostream &operator<<(std::ostream &out, const Particle<float> &p);

#endif
