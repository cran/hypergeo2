#' Generalized hypergeometric function
#'
#' \code{genhypergeo} computes generalized hypergeometric function with vectorized input.
#' This function is available in \code{\link[Rcpp:Rcpp-package]{Rcpp}}
#' as \code{hypergeo2::genhypergeo_vec()}. Its non-vectorized version is available in
#' \code{\link[Rcpp:Rcpp-package]{Rcpp}} as \code{hypergeo2::genhypergeo_vec()}.
#' To use them, please use \code{[[Rcpp::depends(hypergeo2)]]} and \code{#include "hypergeo2.h"}.
#'
#' @param U,L List of numeric vectors for upper and lower values.
#' @param z Numeric vector as common ratios.
#' @param prec List of \code{NULL} or (unsigned) integers as precision level during computation,
#' a.k.a the number of precise digits of floating-point datatypes.
#' This argument is vectorized: you may use different precision settings for different input elements.
#' If \code{NULL}, double precision (default) is used.
#' @param check_mode Logical vector indicating whether the mode of \code{x}
#' should be checked for obvious convergence failures.
#' This argument is vectorized: you may use different check modes for different input elements.
#' @param log Logical (1L) indicating whether result is given as log(result).
#' This argument is **NOT** vectorized: only its first element is used.
#' @param backend One of the following: 'mpfr' (default) or 'gmp', for the realization of
#' floating-point datatype of tunable precision. This argument is **NOT** vectorized:
#' you may only input character (1L).
#'
#' @details
#' Sometimes, computing generalized hypergeometric function in double precision is not sufficient,
#' even though we only need 6-8 accurate digits in the results (see example). Here, two floating-point
#' datatypes are provided: \code{mpfr_float} ('mpfr') and \code{gmp_float} ('gmp'). By comparison,
#' the 'mpfr' backend is safer, since it defines \code{Inf} while the 'gmp' backend throws overflow
#' exception (see references). But the 'gmp' backend results in more accurate results at the same precision,
#' since it usually uses higher precision than set (see reference and validate it on yourself with the examples).
#'
#'
#' @return Numeric vector as the results of computation (at \code{double} precision).
#' Warnings are issued if failing to converge.
#'
#' @note Change log:
#' \itemize{
#'   \item{0.1.0 Xiurui Zhu - Initiate the function.}
#' }
#' @author Xiurui Zhu
#'
#' @references For the floating-point datatypes of tunable precision:
#' * Documentation about [\code{mpfr_float}](https://www.boost.org/doc/libs/master/libs/multiprecision/doc/html/boost_multiprecision/tut/floats/mpfr_float.html)
#' * Documentation about [\code{gmp_float}](https://www.boost.org/doc/libs/master/libs/multiprecision/doc/html/boost_multiprecision/tut/floats/gmp_float.html)
#' * Documentation about [higher precision of \code{gmp_float} datatype](https://www.mpfr.org/faq.html#:~:text=What%20are%20the%20differences%20between%20MPF%20from%20GMP,minimum%20value%20%28MPF%20generally%20uses%20a%20higher%20precision%29)
#'
#' @export
#'
#' @examples
#' U <- c(-28.2, 11.8, 15.8)
#' L <- c(12.8, 17.8)
#' z <- 1
#' # hypergeo results
#' if (length(find.package("hypergeo", quiet = TRUE)) > 0L) {
#'   hypergeo::genhypergeo(U = U, L = L, z = z)
#' }
#' # Default (double) precision: this may result in cancellation error on some platforms
#' tryCatch(
#'   genhypergeo(U = U, L = L, z = z),
#'   error = function(err) {
#'     if (grepl("Cancellation is so severe that no bits in the result are correct",
#'               conditionMessage(err)) == TRUE) {
#'       message("! Cancellation error on your platform: ",
#'               "you may need a higher [prec] than double ([prec = NULL]): ",
#'               conditionMessage(err))
#'     } else {
#'       stop(err)
#'     }
#'   }
#' )
#' # Precision of 20 digits, default ('mpfr') backend
#' genhypergeo(U = U, L = L, z = z, prec = 20L)
#' # Precision of 20 digits, 'gmp' backend
#' genhypergeo(U = U, L = L, z = z, prec = 20L, backend = "gmp")
#' # Precision of 25 digits, default ('mpfr') backend
#' genhypergeo(U = U, L = L, z = z, prec = 25L)
#' # Precision of 25 digits, 'gmp' backend
#' genhypergeo(U = U, L = L, z = z, prec = 25L, backend = "gmp")
genhypergeo <- function(U, L, z, prec = NULL, check_mode = TRUE, log = FALSE,
                        backend = c("mpfr", "gmp")) {
  backend <- match.arg(backend)
  if (is.list(U) == FALSE) {
    U <- list(U)
  }
  U <- lapply(U, as.numeric)
  if (is.list(L) == FALSE) {
    L <- list(L)
  }
  L <- lapply(L, as.numeric)
  if (is.null(prec) == FALSE) {
    if (is.list(prec) == FALSE) {
      prec <- list(prec)
    }
    prec <- lapply(prec, as.integer)
  }
  if (length(log) == 0L) {
    stop("[log] shoule be logical of length 1, not 0")
  } else if (length(log) > 1L) {
    warning("[log] is of length ", length(log), ": only its first element is used",
            immediate. = TRUE)
  }
  genhypergeo_vec(U = U,
                  L = L,
                  z = as.numeric(z),
                  prec = prec,
                  check_mode = as.logical(check_mode),
                  log = as.logical(log),
                  backend = backend)
}
