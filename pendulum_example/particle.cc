#include "vec.hh"
#include "particle.hh"

template <typename T>
Vec<T> Particle<T>::drag_force(T c) const {
  return velocity.scale(-c);
}

template <typename T>
void Particle<T>::step(const Vec<T> &force, T dt) {
  auto acceleration = force.scale(1.0 / mass);   // f = ma
  velocity = velocity + acceleration.scale(dt);  // a = dv / dt
  position = position + velocity.scale(dt);      // v = dx / dt
}

template class Particle<float>;
template class Particle<double>;

std::ostream &operator<<(std::ostream &out, const Particle<double>& p) {
  out << "Particle["
      << p.mass << ", " << p.position << ", " << p.velocity << "]";
  return out;
}

std::ostream &operator<<(std::ostream &out, const Particle<float>& p) {
  out << "Particle["
      << p.mass << ", " << p.position << ", " << p.velocity << "]";
  return out;
}
