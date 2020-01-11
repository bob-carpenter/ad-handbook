#include "forward.hpp"
#include <iostream>

int main() {
  using autodiff::dual;
  dual<double> a(2.2, -3.1);
  dual<double> b(5);
  dual<double> c = 5;
  dual<double> d = dual<double>(5);
  dual<double> e = exp(a);
  dual<double> f = log(c);
  dual<double> g = dual<double>(2) * dual<double>(3);
  dual<double> h = 2 * dual<double>(3);
  dual<double> i = dual<double>(2) * 3;
}
