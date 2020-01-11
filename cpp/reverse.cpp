#include "reverse.hpp"
#include <iostream>

int main() {
  using autodiff::adj;
  autodiff::next_ = 0;
  autodiff::stack_.clear();
  adj x1 = 10.3;
  adj x2 = -1.1;
  adj y = x1 * exp(x2 * 2) + 7;
  std::vector<double> adjoints = chain(y);
  double dy_dx1 = adjoints[x1.idx()];
  double dy_dx2 = adjoints[x2.idx()];
  std::cout << "grad f = [" << dy_dx1 << ", " << dy_dx2 << "]" << std::endl;
  return 0;
}
