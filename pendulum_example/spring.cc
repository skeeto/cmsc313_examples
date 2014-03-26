#include "vec.hh"
#include "spring.hh"

template <typename T>
Vec<T> Spring<T>::force() const {
  T actual = p1.dist(p2);
  T mf = (length - actual) * k;
  return (p2 - p1).norm().scale(mf);
}

template class Spring<float>;
template class Spring<double>;
