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
                             const Eigen::VectorXd v, double& fx, double& x_gradv) {

}

}
