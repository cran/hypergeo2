#include "hypergeo_impl.h"
#include "../inst/include/hypergeo2/hypergeo.h"
#include "boost/multiprecision/gmp.hpp"
#include "boost/multiprecision/mpfr.hpp"
#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::depends(BH)]]

// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
double genhypergeo_cpp(const NumericVector& U,
                       const NumericVector& L,
                       const double& z,
                       const Nullable<IntegerVector>& prec,
                       const bool& check_mode,
                       const bool& log,
                       const String& backend) {
  double out;
  double nan_value = R_NaN;
  if (backend == "mpfr") {
    typedef typename boost::multiprecision::number<boost::multiprecision::backends::mpfr_float_backend<0>> prec_float;
    out = hypergeo2::genhypergeo_<REALSXP, double, prec_float>(U, L, z, nan_value, prec, check_mode);
  } else if (backend == "gmp") {
    typedef typename boost::multiprecision::number<boost::multiprecision::backends::gmp_float<0>> prec_float;
    out = hypergeo2::genhypergeo_<REALSXP, double, prec_float>(U, L, z, nan_value, prec, check_mode);
  } else {
    stop("Unrecognized backend: %s", backend.get_cstring());
  }
  if (log == true) {
    out = std::log(out);
  }
  return out;
}
