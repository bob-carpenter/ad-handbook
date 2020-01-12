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

  dual<dual<double>> aa(dual<double>(2.1, 1), dual<double>(0, 0));
  dual<dual<double>> bb(dual<double>(1.5, 0), dual<double>(1, 0));
  dual<dual<double>> cc(dual<double>(-0.3, 0), dual<double>(0, 0));

  std::cout << "a = " << aa << std::endl;
  std::cout << "b = " << bb << std::endl;
  std::cout << "c = " << cc << std::endl;
  std::cout << "b * c = " << (bb * cc) << std::endl;
  std::cout << "exp(b * c) = " << exp(bb * cc) << std::endl;
  std::cout << "a * exp(b * c) = " << (aa * exp(bb * cc)) << std::endl;
}
