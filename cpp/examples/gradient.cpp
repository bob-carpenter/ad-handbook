#include "functional.hpp"
#include <iostream>

int main() {
  auto f = [](const auto& v) { return v[0] * v[1] + 37.2 * v[2]; };
  Eigen::VectorXd x(3);
  x << 1, 2, 3;
  Eigen::RowVectorXd grad;
  double fx;
  autodiff::gradient(f, x, fx, grad);
  std::cout << "f(x) = x[0] * x[1] + 37.2 * x[3]" << std::endl;
  std::cout << "f([1 2 3]') = " << fx << std::endl;
  std::cout << "grad f([1 2 3]') = [" << grad << "]'" << std::endl;
}
