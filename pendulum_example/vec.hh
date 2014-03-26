#ifndef VEC_HH
#define VEC_HH

#include <cmath>
#include <iostream>

template <typename T>
class Vec {
public:
  Vec(T x, T y) : x {x}, y {y} {};
  Vec(T angle) : x {std::sin(x)}, y {std::cos(y)} {};
  T x, y;

  Vec<T> operator-(const Vec<T> &v) const;
  Vec<T> operator+(const Vec<T> &v) const;
  Vec<T> &operator=(const Vec<T> &rhs);
  Vec<T> scale(T s) const;
  T magnitude() const;
  Vec<T> norm() const;
  T dist(const Vec<T> &v) const;
  T angle() const;
};

std::ostream &operator<<(std::ostream &out, const Vec<double>& v);
std::ostream &operator<<(std::ostream &out, const Vec<float>& v);

#endif
