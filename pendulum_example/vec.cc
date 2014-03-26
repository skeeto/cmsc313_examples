#include <cmath>
#include <iostream>
#include "vec.hh"

template <typename T>
Vec<T> Vec<T>::operator-(const Vec<T> &v) const {
  Vec<T> result {x - v.x, y - v.y};
  return result;
}

template <typename T>
Vec<T> Vec<T>::operator+(const Vec<T> &v) const {
  Vec<T> result {x + v.x, y + v.y};
  return result;
}

template <typename T>
Vec<T> Vec<T>::scale(T s) const {
  Vec<T> result {x * s, y * s};
  return result;
}

template <typename T>
T Vec<T>::magnitude() const {
  return std::sqrt(x * x + y * y);
}

template <typename T>
Vec<T> Vec<T>::norm() const {
  return scale(1.0 / magnitude());
}

template <typename T>
T Vec<T>::dist(const Vec<T> &v) const {
  T dx = x - v.x, dy = y - v.y;
  return std::sqrt(dx * dx + dy * dy);
}

template <typename T>
T Vec<T>::angle() const {
  return std::atan2(x, y);
}

template class Vec<float>;
template class Vec<double>;

std::ostream &operator<<(std::ostream &out, const Vec<double>& v) {
  out << "(" << v.x << ", " << v.y << ")";
  return out;
}

std::ostream &operator<<(std::ostream &out, const Vec<float>& v) {
  out << "(" << v.x << ", " << v.y << ")";
  return out;
}
