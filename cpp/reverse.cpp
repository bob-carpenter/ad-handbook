#include <type_traits>
namespace autodiff {
template <typename T>
using enable_if_arithmetic_t
= std::enable_if_t<std::is_arithmetic_v<T>>;
}


#include <cstddef>
namespace autodiff {
std::size_t next_ = 0;

class adj {
  double val_;
  std::size_t idx_;
 public:
  template <typename T, typename = enable_if_arithmetic_t<T>>
  adj(T val = 0, int idx = next_++)
    : val_(val), idx_(idx) { }
  double val() const { return val_; }
  double idx() const { return idx_; }
};
}

#include <vector>
#include <functional>
namespace autodiff {
std::vector<std::function<void(std::vector<double>&)>> stack_;
}

namespace autodiff {
std::vector<double> chain(const adj& y) {
  std::vector<double> adjoints(y.idx() + 1, 0.0);
  adjoints[y.idx()] = 1;
  for (auto chain_f = stack_.crbegin(); chain_f != stack_.crend(); ++chain_f)
    (*chain_f)(adjoints);
  return adjoints;
}
}

namespace autodiff {
inline adj operator+(const adj& x1, const adj& x2) {
  adj y(x1.val() + x2.val());
  auto f = [=](std::vector<double>& adj) {
    adj[x1.idx()] += adj[y.idx()];
    adj[x2.idx()] += adj[y.idx()];
  };
  stack_.emplace_back(f);
  return y;
}
}

namespace autodiff {
template <typename T, typename = enable_if_arithmetic_t<T>>
inline adj operator+(const adj& x1, T x2) {
  adj y(x1.val() + x2);
  stack_.emplace_back([=](std::vector<double>& adj) {
      adj[x1.idx()] += adj[y.idx()];
    });
  return y;
}
template <typename T, typename = enable_if_arithmetic_t<T>>
inline adj operator+(T x1, const adj& x2) {
  adj y(x1 + x2.val());
  stack_.emplace_back([=](std::vector<double>& adj) {
      adj[x2.idx()] += adj[y.idx()];
    });
  return y;
}
}

namespace autodiff {
inline adj operator*(const adj& x1, const adj& x2) {
  adj y(x1.val() * x2.val());
  stack_.emplace_back([=](std::vector<double>& adj) {
      adj[x1.idx()] += x2.val() * adj[y.idx()];
      adj[x2.idx()] += x1.val() * adj[y.idx()];
    });
  return y;
}
template <typename T, typename = enable_if_arithmetic_t<T>>
inline adj operator*(const adj& x1, T x2) {
  adj y(x1.val() * x2);
  stack_.emplace_back([=](std::vector<double>& adj) {
      adj[x1.idx()] += x2 * adj[y.idx()];
    });
  return y;
}
template <typename T, typename = enable_if_arithmetic_t<T>>
inline adj operator*(T x1, const adj& x2) {
  adj y(x1 * x2.val());
  stack_.emplace_back([=](std::vector<double>& adj) {
      adj[x2.idx()] += x1 * adj[y.idx()];
    });
  return y;
}
}

#include <cmath>
namespace autodiff {
inline adj exp(const adj& x) {
  adj y(std::exp(x.val()));
  auto f = [=](std::vector<double>& adj) {
    adj[x.idx()] += y.val() * adj[y.idx()];
  };
  stack_.emplace_back(f);
  return y;
}
}

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
