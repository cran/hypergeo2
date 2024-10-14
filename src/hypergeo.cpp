#include "hypergeo_impl.h"
#include <Rcpp.h>
using namespace Rcpp;

#ifndef HYPERGEO2_MACROS
#define HYPERGEO2_MACROS
#define GETV(x, i)      x(i % x.length())    // wrapped indexing of vector
#endif // HYPERGEO2_MACROS

template <typename T1, typename T2>
Nullable<T2> nullable_getv(const Nullable<T1>& x, const int& idx) {
  if (x.isNull()) {
    return R_NilValue;
  }
  T1 x_vec = as<T1>(x);
  T2 out(1, GETV(x_vec, idx));
  return out;
}

// [[Rcpp::interfaces(r, cpp)]]
// [[Rcpp::export]]
NumericVector genhypergeo_vec(const List& U,
                              const List& L,
                              const NumericVector& z,
                              const Nullable<List>& prec = R_NilValue,
                              const LogicalVector& check_mode = true,
                              const LogicalVector& log = false,
                              const String& backend = "mpfr") {
  if (std::min({U.length(), L.length(), z.length()}) < 1) {
    return NumericVector(0);
  }

  int n_max = std::max({
    U.length(),
    L.length(),
    z.length()
  });

  NumericVector out(n_max);
  for (R_xlen_t idx = 0; idx < n_max; idx++) {
    out(idx) = genhypergeo_cpp(
      GETV(U, idx),
      GETV(L, idx),
      GETV(z, idx),
      nullable_getv<List, IntegerVector>(prec, idx),
      GETV(check_mode, idx),
      false, // log
      backend
    );
  }

  if (log(0) == true) {
    out = Rcpp::log(out);
  }
  return out;
}

/*** R
genhypergeo_vec(U = list(c(1.1, 0.2, 0.3)), L = list(c(10.1, 4 * pi)), z = 1,
                prec = NULL, check_mode = TRUE, log = FALSE)
*/
