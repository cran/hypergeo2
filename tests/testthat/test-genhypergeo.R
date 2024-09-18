library(testthat)

# Parameters
test_x <- 5
test_size <- 10
test_alpha <- 2
test_beta <- 4
test_prec <- 20L

testthat::test_that(
  "gen_hypergeo",
  {
    U <- c(1 - test_x,
           test_size + 1 - test_x,
           test_size + 1 - test_x + test_beta)
    L <- c(test_size + test_alpha - test_x,
           test_size + 1 - test_x + test_alpha + test_beta)
    testthat::expect_equal(
      genhypergeo(U = U,
                  L = L,
                  z = 1,
                  prec = test_prec,
                  check_mode = TRUE,
                  log = FALSE),
      101/5460
    )
  }
)
