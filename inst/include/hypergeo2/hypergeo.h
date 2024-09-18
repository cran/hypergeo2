#ifndef HYPERGEO2_GENHYPERGEO_H_GEN_
#define HYPERGEO2_GENHYPERGEO_H_GEN_

#include "boost/math/special_functions/hypergeometric_pFq.hpp"
#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::depends(BH)]]

namespace hypergeo2
{
  // Convert R vector to std::vector<cpp_bin_float<prec>>
  template <typename T1, typename T2, typename T3>
  std::vector<T3> conv_vec_prec(const T1& x) {
    std::vector<T3> out(x.length());
    for (R_xlen_t i = 0; i < x.length(); i++) {
      T2 x_i = x(i);
      out[i] = x_i;
    }
    return out;
  }

  // Template: SXP - vector type, T1 - element type, T2 - GMP/MPFR type
  template <int SXP, typename T1, typename T2>
  T1 genhypergeo_(const Vector<SXP>& U,
                  const Vector<SXP>& L,
                  const T1& z,
                  const T1& nan_value,
                  const Nullable<IntegerVector>& prec = R_NilValue,
                  const bool& check_mode = true) {
    // Check inputs
    if (check_mode == true) {
      if (U.length() > L.length() + 1) {
        if (std::fabs(z) > 0.0) {
          warning("length(U) > length(L) + 1L: converge failure if abs(z) > 0; returning NaN");
          return nan_value;
        }
      } else if (U.length() > L.length()) {
        if (std::fabs(z) > 1.0) {
          warning("length(U) > length(L): converge failure if abs(z) > 1; returning NaN");
          return nan_value;
        }
      }
    }
    // Main code
    typedef typename boost::math::policies::policy<
      boost::math::policies::max_series_iterations<10000>
    > MyPol;
    T1 out;
    if (prec.isNull()) {
      T1 p_abs_error;
      out = boost::math::hypergeometric_pFq(U, L, z, &p_abs_error, MyPol());
    } else {
      IntegerVector prec_ = as<IntegerVector>(prec);
      unsigned int prec_use = (unsigned) prec_(0);
      boost::math::scoped_precision<T2> scoped(prec_use);
      T2 z_ = z;
      std::vector<T2> U_ = conv_vec_prec<Vector<SXP>, T1, T2>(U);
      std::vector<T2> L_ = conv_vec_prec<Vector<SXP>, T1, T2>(L);
      T2 p_abs_error;
      T2 out_ = boost::math::hypergeometric_pFq(U_, L_, z_, &p_abs_error, MyPol());
      out = static_cast<T1>(out_);
    }
    return out;
  }
} // namespace hypergeo2

#endif // HYPERGEO2_GENHYPERGEO_H_GEN_
