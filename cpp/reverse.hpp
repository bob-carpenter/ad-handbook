#include <cmath>
#include <cstddef>
#include <functional>
#include <iostream>
#include <type_traits>
#include <vector>

namespace autodiff {

template <typename T>
using enable_if_arithmetic_t
= std::enable_if_t<std::is_arithmetic_v<T>>;

std::size_t next_ = 0;

class adj {
  double val_;
  std::size_t idx_;
 public:
  adj() : adj(0) { }

  template <typename T, typename = enable_if_arithmetic_t<T>>
  adj(T val, int idx = next_++)
    : val_(val), idx_(idx) { }
  double val() const { return val_; }
  double idx() const { return idx_; }
};

std::vector<std::function<void(std::vector<double>&)>> stack_;


/**
 * Propagate chain rule from the specified dependent variable.
 * @param[in] y
 * @return stack of adjoint values matching variable indexes
 */
std::vector<double> chain(const adj& y) {
  std::vector<double> adjoints(y.idx() + 1, 0.0);
  adjoints[y.idx()] = 1;
  for (auto chain_f = stack_.crbegin(); chain_f != stack_.crend(); ++chain_f)
    (*chain_f)(adjoints);
  return adjoints;
}

inline adj operator+(const adj& x1, const adj& x2) {
  adj y(x1.val() + x2.val());
  auto f = [=](std::vector<double>& adj) {
    adj[x1.idx()] += adj[y.idx()];
    adj[x2.idx()] += adj[y.idx()];
  };
  stack_.emplace_back(f);
  return y;
}

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


inline adj exp(const adj& x) {
  adj y(std::exp(x.val()));
  auto f = [=](std::vector<double>& adj) {
    adj[x.idx()] += y.val() * adj[y.idx()];
  };
  stack_.emplace_back(f);
  return y;
}



std::ostream& operator<<(std::ostream& o, const adj& y) {
  o << "(" << y.val() << ", " << y.idx() << ")";
  return o;
}

}  // namespace autodiff
