#include "reverse.hpp"
#include "forward.hpp"
#include <Eigen/Dense>
#include <vector>
#include <iostream>

namespace autodiff {

template <typename F>
void gradient(const F& f, const Eigen::VectorXd& x,
              double& fx, Eigen::VectorXd& grad) {
  Eigen::Matrix<adj, -1, 1> xa(x.size());
  for (int i = 0; i < xa.size(); ++i)
    xa(i) = x(i);
  auto y = f(xa);
  std::vector<double> adjoints = chain(y);
  grad.resize(x.size());
  for (int i = 0; i < x.size(); ++i)
    grad(i) = adjoints[xa(i).idx()];
}

template <typename F>
void vector_gradient_product(const F& f, const Eigen::VectorXd& x,
                             const Eigen::VectorXd v, double& fx,
                             double& x_gradv) {
}

Eigen::MatrixXd hessian(const F& f, const Eigen::VectorXd& x) {
  int N = x.size();
  Eigen::MatrixXd H(N, N);
  for (int m = 0; m < N; ++m) {
    // calculate m-th row of Hessian
    Eigen::Matrix<dual<adj>, -1, 1> xa(N);
    for (int n = 0; n < N; ++n)
      xa(n) = { x(n), m == n };  // d.x(n)/d.x(m) = 1 iff m == n
    auto y = f(xa);
    std::vector<double> adjoints = chain(y);
    for (int n = 0; n < N; ++n)
      H(m, n) = adjoints[xa(n).tan().idx()];  // = bar(dot(x[n]))
  }
  return H;
}
