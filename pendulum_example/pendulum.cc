#include <iostream>
#include "particle.hh"
#include "spring.hh"
#include "pendulum.hh"

template <typename T>
void Pendulum<T>::step(T dt) {
  const Vec<T> gravity{0, -9.81};

  // the spring forces
  auto fs1a = s1.force();  // spring1 on p1
  auto fs1b = s2.force();  // spring2 on p1 (this is subtracted)
  auto fs2 = s2.force();   // spring2 on p2

  // drag forces
  auto fd1 = p1.drag_force(0.01f);
  auto fd2 = p2.drag_force(0.01f);

  // compute the final sums
  auto f1 = gravity + fs1a - fs1b + fd1;
  auto f2 = gravity + fs2 + fd2;

  // step the particles with the accumulated forces
  p1.step(f1, dt);
  p2.step(f2, dt);
}

template class Pendulum<float>;
template class Pendulum<double>;

std::ostream &operator<<(std::ostream &out, const Pendulum<double> &p) {
  out << "Pendulum{[" << p.p1.position << ", " << p.p1.velocity << "], ["
      << p.p2.position << ", " << p.p2.velocity << "]}";
  return out;
}

std::ostream &operator<<(std::ostream &out, const Pendulum<float> &p) {
  out << "Pendulum{[" << p.p1.position << ", " << p.p1.velocity << "], ["
      << p.p2.position << ", " << p.p2.velocity << "]}";
  return out;
}
