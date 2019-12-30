namespace autodiff {
template <typename T>
class dual {
  T val_;
  T tan_;
 public:
  dual(const T& val, const T& tan = 0)
      : val_(val), tan_(tan) { }
  const T& val() const { return val_; }
  const T& tan() const { return tan_; }
};
}

#include <cmath>
namespace autodiff {
template <typename T>
inline dual<T> exp(const dual<T>& x) {
  using std::exp;
  T y = exp(x.val());
  return dual(y, x.tan() * y);
}
template <typename T>
inline dual<T> log(const dual<T>& x) {
  using std::log;
  T y = log(x.val());
  return dual(y, x.tan() / y );
}
}

namespace autodiff {
template <typename T>
inline dual<T> operator*(const dual<T>& x1, const dual<T>& x2) {
  return dual(x1.val() * x2.val(),
              x1.tan() * x2.val() + x1.val() * x2.tan());
}
}

#include <type_traits>
namespace autodiff {
template <typename T, typename U,
          typename = std::enable_if_t<std::is_arithmetic_v<U>>>
inline dual<T> operator*(const dual<T>& x1, const U& c2) {
  return dual(x1.val() * c2, x1.tan() * c2);
}
template <typename T, typename U,
          typename = std::enable_if_t<std::is_arithmetic_v<U>>>
inline dual<T> operator*(const U& c1, const dual<T>& x2) {
  return dual(c1 * x2.val(), c1 * x2.tan());
}
}


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
