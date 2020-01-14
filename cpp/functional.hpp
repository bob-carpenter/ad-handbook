#include "reverse.hpp"
#include "forward.hpp"
#include <Eigen/Dense>
#include <vector>
#include <iostream>

namespace autodiff {

/**
 * Set the value and derivative of the specified function at the
 * specified input.  The functor must define the method
 * `dual<double> operator()(const dual<double>& x) const;`
 *
 * @tparam F type of function
 * @param[in] f function
 * @param[in] x input
 * @param[out] y function applied to input
 * @param[out] dy_dx derivative of y w.r.t. x
 */
template <typename F>
void derivative(const F& f, double x, double& y, double& dy_dx) {
  dual<double> xd{ x, 1 };
  auto yd = f(xd);
  y = yd.val();
  dy_dx = yd.tan();
}


/**
 * Set the value and gradient of the specified function at the
 * specified input.  The functor must define the method
 * `adj operator()(const Eigen::Matrix<adj, -1, 1>& x) const;`.
 *
 * @tparam F type of function
 * @param[in] f function
 * @param[in] x input
 * @param[out] fx function applied to input
 * @param[out] grad gradient of function applied to input
 */
template <typename F>
void gradient(const F& f, const Eigen::VectorXd& x,
              double& fx, Eigen::RowVectorXd& grad) {
  Eigen::Matrix<adj, -1, 1> xa(x.size());
  for (int i = 0; i < xa.size(); ++i)
    xa(i) = x(i);
  adj y = f(xa);
  std::vector<double> adjoints = chain(y);
  fx = y.val();
  grad.resize(x.size());
  for (int i = 0; i < x.size(); ++i)
    grad(i) = adjoints[xa(i).idx()];
}

/**
 * Set the value of the specified function at the specified value and
 * the product of the gradient of the function at the specified value
 * and the specified vector.
 *
 * @tparam F type of function
 * @param[in] f function
 * @param[in] x input
 * @param[in] v vector to multiply
 * @param[out] fx value of f(x)
 * @param[out] gradv product of gradient of f(x) and v
 */
template <typename F>
void vector_gradient_product(const F& f, const Eigen::VectorXd& x,
                             const Eigen::VectorXd v, double& fx,
                             double& gradv) {
  Eigen::Matrix<dual<double>, -1, 1> xd(x.size());
  for (int i = 0; i < xd.size(); ++i)
    xd(i) = { x(i), v(i) };
  dual<double> fxd = f(xd);
  fx = fxd.val();
  gradv = fxd.tan();
}

/**
 * Set the specified Hessian matrix to the Hessian of the specified
 * function at the specified value.
 *
 * @tparam F type of function
 * @param[in] f function
 * @param[in] x input
 * @param[out] H set to Hessian of function at input
 */
template <typename F>
void hessian(const F& f, const Eigen::VectorXd& x, Eigen::MatrixXd& H) {
  int N = x.size();
  H.resize(N, N);
  for (int m = 0; m < N; ++m) {  // m-th row of H
    Eigen::Matrix<dual<adj>, -1, 1> xd(N);
    for (int n = 0; n < N; ++n)
      xd(n) = { x(n), m == n };  // d.x(n)/d.x(m) = 1 iff m == n
    auto y = f(xd);
    std::vector<double> adjoints = chain(y.tan());
    for (int n = 0; n < N; ++n)
      H(m, n) = adjoints[xd(n).val().idx()];  // = bar(dot(x[m, n]))
  }
}

}
