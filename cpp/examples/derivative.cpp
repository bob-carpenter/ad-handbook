#include <functional.hpp>
#include <iostream>

int main() {
  auto f = [](const auto& x) { return 2 * exp(x); };
  double x = 1.3;
  double y;
  double dy_dx;
  autodiff::derivative(f, x, y, dy_dx);
  std::cout << "x = " << x
            << "; y = 2 * exp(x) = " << y
            << "; d.y/d.x = " << dy_dx
            << std::endl;
}
