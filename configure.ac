AC_INIT([hypergeo2],[0.2.0],[zxr6@163.com])

dnl Find pkg-config program
PKG_PROG_PKG_CONFIG

dnl Select optional include paths, from a configure option
dnl or from an environment variable.
gmp_include_path=""
AC_ARG_WITH([gmp-include],
            AS_HELP_STRING([--with-gmp-include=GMP_INCLUDE],[the 'gmp' include path]),
            [gmp_include_path=$withval])
HYPERGEO2_CPPFLAGS="-I."
if test [ -n "$gmp_include_path" ] ; then
   HYPERGEO2_CPPFLAGS="${HYPERGEO2_CPPFLAGS} -I${gmp_include_path}"
else
  if test [ -n "${GMP_INCLUDE}" ] ; then
     HYPERGEO2_CPPFLAGS="${HYPERGEO2_CPPFLAGS} -I${GMP_INCLUDE}"
  else
    if test [ -n "${PKG_CONFIG}" ]; then
      GMP_CFLAGS_PKG_CONFIG=`"${PKG_CONFIG}" --cflags gmp`
      HYPERGEO2_CPPFLAGS="${HYPERGEO2_CPPFLAGS} ${GMP_CFLAGS_PKG_CONFIG}"
    fi
  fi
fi

mpfr_include_path=""
AC_ARG_WITH([mpfr-include],
            AS_HELP_STRING([--with-mpfr-include=MPFR_INCLUDE],[the 'mpfr' include path]),
            [mpfr_include_path=$withval])
if test [ -n "$mpfr_include_path" ] ; then
   HYPERGEO2_CPPFLAGS="${HYPERGEO2_CPPFLAGS} -I${mpfr_include_path}"
else
  if test [ -n "${HYPERGEO2_MPFR_INCLUDE}" ] ; then
     HYPERGEO2_CPPFLAGS="${HYPERGEO2_CPPFLAGS} -I${MPFR_INCLUDE}"
  else
    if test [ -n "${PKG_CONFIG}" ]; then
      MPFR_CFLAGS_PKG_CONFIG=`"${PKG_CONFIG}" --cflags mpfr`
      HYPERGEO2_CPPFLAGS="${HYPERGEO2_CPPFLAGS} ${MPFR_CFLAGS_PKG_CONFIG}"
    fi
  fi
fi

dnl Select optional library paths
gmp_lib_path=""
AC_ARG_WITH([gmp-lib],
            AS_HELP_STRING([--with-gmp-lib=GMP_LIB],[the location of GMP library]),
            [gmp_lib_path=$withval])
if test [ -n "$gmp_lib_path" ] ; then
   LIBS="-L${gmp_lib_path} -lgmp ${LIBS}"
else
  if test [ -n "${GMP_LIB}" ] ; then
     LIBS="-L${GMP_LIB} -lgmp ${LIBS}"
  else
    if test [ -n "${PKG_CONFIG}" ]; then
      GMP_LIBS_PKG_CONFIG=`"${PKG_CONFIG}" --libs gmp`
      LIBS="${GMP_LIBS_PKG_CONFIG} ${LIBS}"
    fi
  fi
fi

mpfr_lib_path=""
AC_ARG_WITH([mpfr-lib],
            AS_HELP_STRING([--with-mpfr-lib=MPFR_LIB],[the location of 'mpfr' library]),
            [mpfr_lib_path=$withval])
if test [ -n "$mpfr_lib_path" ] ; then
   LIBS="-L${mpfr_lib_path} -lmpfr ${LIBS}"
else
  if test [ -n "${MPFR_LIB}" ] ; then
     LIBS="-L${MPFR_LIB} -lmpfr ${LIBS}"
  else
    if test [ -n "${PKG_CONFIG}" ]; then
      MPFR_LIBS_PKG_CONFIG=`"${PKG_CONFIG}" --libs mpfr`
      LIBS="${MPFR_LIBS_PKG_CONFIG} ${LIBS}"
    fi
  fi
fi

dnl Determine maximal series iteration
max_series_iter=10000
AC_ARG_WITH([max-iter],
            AS_HELP_STRING([--with-max-iter=MAX_SERIES_ITER],[the maximal iteration of series]),
            [max_series_iter=$withval])
if test [ -n "${MAX_ITER}" ] ; then
  max_series_iter=${MAX_ITER}
fi
sed "s/@MAX_SERIES_ITER@/${max_series_iter}/" 'inst/include/hypergeo2/hypergeo.h.in' \
  > 'inst/include/hypergeo2/hypergeo.h'

dnl Now find the compiler and compiler flags to use
: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
  echo "could not determine R_HOME"
  exit 1
fi
CC=`"${R_HOME}/bin/R" CMD config CC`
CFLAGS=`"${R_HOME}/bin/R" CMD config CFLAGS`
CPPFLAGS=`"${R_HOME}/bin/R" CMD config CPPFLAGS`

CPPFLAGS="${CPPFLAGS} ${HYPERGEO2_CPPFLAGS}"

dnl Check the headers can be found
AC_CHECK_HEADERS(mpfr.h gmp.h)
missing_header=""
if test "${ac_cv_header_gmp_h}" = no; then
  missing_header="${missing_header} 'gmp'"
fi
if test "${ac_cv_header_mpfr_h}" = no; then
  missing_header="${missing_header} 'mpfr'"
fi
if test [ ${missing_header} ]; then
  AC_MSG_FAILURE([
  ---------------------------------------------
  ${missing_header} and their (its) header files are required.

   Please install:

   * For Windows with rtools40 or newer: pacman -Syu make pkg-config libtool${missing_header}
   * For macOS: brew install${missing_header}
   * For Linux: (please find out platform-specific${missing_header} and build from source)

   and try again.

   If you believe the libraries are installed on your system but
   this script is simply unable to find it, you can specify the
   include and lib paths manually in one of the following ways:

   R CMD INSTALL ${PACKAGE_NAME} \\
     --configure-args='\\
       --with-gmp-include=GMP_INCLUDE_PATH \\
       --with-mpfr-include=MPFR_INCLUDE_PATH \\
       --with-gmp-lib=GMP_LIB_PATH \\
       --with-mpfr-lib=MPFR_LIB_PATH \\
       --with-max-iter=MAX_SERIES_TIER\\
     '

   R CMD INSTALL ${PACKAGE_NAME} \\
     --configure-vars='\\
       GMP_INCLUDE=GMP_INCLUDE_PATH \\
       MPFR_INCLUDE=MPFR_INCLUDE_PATH \\
       GMP_LIB=GMP_LIB_PATH \\
       MPFR_LIB=MPFR_LIB_PATH \\
       MAX_ITER=MAX_SERIES_ITER\\
     '
  ---------------------------------------------])
fi

dnl substitute HYPERGEO2_CPPFLAGS and LIBS
AC_SUBST(HYPERGEO2_CPPFLAGS)
AC_SUBST(LIBS)
AC_CONFIG_HEADERS([src/config.h])
dnl and do subsitution in the src/Makevars.in and src/config.h
AC_CONFIG_FILES([src/Makevars])
AC_OUTPUT

echo "
  --------------------------------------------------
  Configuration for ${PACKAGE_NAME} ${PACKAGE_VERSION}

    cppflags: ${CPPFLAGS} ${HYPERGEO2_CPPFLAGS}
    libs:     ${LIBS}
    max_iter: ${max_series_iter}

  --------------------------------------------------
"
