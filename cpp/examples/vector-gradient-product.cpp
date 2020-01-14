#include "functional.hpp"
#include <iostream>

int main() {
  auto f = [](const auto& x) { return x[0] * x[1] + exp(x[2]); };
  Eigen::VectorXd x(3);
  x << 0.5, -0.5, 1.3;
  Eigen::VectorXd v(3);
  v << 1, 2, 3;
  double fx;
  double gradv;
  autodiff::vector_gradient_product(f, x, v, fx, gradv);
  std::cout << "f = x[0] * x[1] + exp(x[2])" << std::endl;
  std::cout << "f([0.5 -0.5, 1.3]') = " << fx << std::endl;
  std::cout << "grad f([0.5 -0.5 1.3]') * [1 2 3] = " << gradv << std::endl;
  return 0;
}
