#include "functional.hpp"
#include <iostream>

int main() {
  auto f = [](const auto & x) { return x[0] * x[1] * x[2]; };
  Eigen::VectorXd x(3);
  x << 2, 3, 5;
  Eigen::MatrixXd H;
  autodiff::hessian(f, x, H);
  std::cout << "f(x) = x[0] * x[1] * x[2]" << std::endl;
  std::cout << "H_f([2, 3, 5]') = " << std::endl << H << std::endl;
}
