#ifndef HYPERGEO2_HYPERGEO_IMPL_H_GEN_
#define HYPERGEO2_HYPERGEO_IMPL_H_GEN_

#include <Rcpp.h>
using namespace Rcpp;

double genhypergeo_cpp(const NumericVector& U,
                       const NumericVector& L,
                       const double& z,
                       const Nullable<IntegerVector>& prec = R_NilValue,
                       const bool& check_mode = true,
                       const bool& log = false,
                       const String& backend = "mpfr");

#endif // HYPERGEO2_HYPERGEO_IMPL_H_GEN_
