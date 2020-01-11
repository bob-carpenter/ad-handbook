#include "functional.hpp"
#include <iostream>



int main() {
  auto f = [](const auto& v) { return v[0] * v[1] + 37.2 * v[2]; };
  Eigen::VectorXd x(3);
  x << 1, 2, 3;
  Eigen::VectorXd grad;
  double fx;
  autodiff::gradient(f, x, fx, grad);
  std::cout << "fx = " << fx << "; grad = " << grad << std::endl;
}
