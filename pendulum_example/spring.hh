#ifndef SPRING_HH
#define SPRING_HH

#include "spring.hh"

template <typename T>
class Spring {
 public:
  Spring(Vec<T> *p1, Vec<T> *p2, T k)
      : p1{p1}, p2{p2}, k{k}, length{p1->dist(*p2)} {};
  const Vec<T> *p1, *p2;
  T k, length;

  Vec<T> force() const;
};

#endif
