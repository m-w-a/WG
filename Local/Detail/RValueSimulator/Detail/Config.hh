#ifndef WG_RVALUESIMULATOR_DETAIL_CONFIG_HH_
#define WG_RVALUESIMULATOR_DETAIL_CONFIG_HH_

///////////////////////////////////////////////////////////////////////////////
// foreach.hpp header file
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// See http://www.boost.org/libs/foreach for documentation
//
// Credits:
//  Anson Tsao        - for the initial inspiration and several good suggestions.
//  Thorsten Ottosen  - for Boost.Range, and for suggesting a way to detect
//                      const-qualified rvalues at compile time on VC7.1+
//  Russell Hind      - For help porting to Borland
//  Alisdair Meredith - For help porting to Borland
//  Stefan Slapeta    - For help porting to Intel
//  David Jenkins     - For help finding a Microsoft Code Analysis bug
//  mimomorin@...     - For a patch to use rvalue refs on supporting compilers

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

// Some compilers let us detect even const-qualified rvalues at compile-time
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)                                                   \
 || BOOST_WORKAROUND(BOOST_MSVC, >= 1310) && !defined(_PREFAST_)                                 \
 || (BOOST_WORKAROUND(__GNUC__, == 4) && (__GNUC_MINOR__ <= 5) && !defined(BOOST_INTEL) &&       \
                                                                  !defined(BOOST_CLANG))         \
 || (BOOST_WORKAROUND(__GNUC__, == 3) && (__GNUC_MINOR__ >= 4) && !defined(BOOST_INTEL) &&       \
                                                                  !defined(BOOST_CLANG))
# define BOOST_FOREACH_COMPILE_TIME_CONST_RVALUE_DETECTION
#else
// Some compilers allow temporaries to be bound to non-const references.
// These compilers make it impossible to for BOOST_FOREACH to detect
// temporaries and avoid reevaluation of the collection expression.
# if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)                                                      \
  || BOOST_WORKAROUND(__BORLANDC__, < 0x593)                                                    \
  || (BOOST_WORKAROUND(BOOST_INTEL_CXX_VERSION, <= 700) && defined(_MSC_VER))                   \
  || BOOST_WORKAROUND(__SUNPRO_CC, < 0x5100)                                                    \
  || BOOST_WORKAROUND(__DECCXX_VER, <= 60590042)
#  define BOOST_FOREACH_NO_RVALUE_DETECTION
# endif
// Some compilers do not correctly implement the lvalue/rvalue conversion
// rules of the ternary conditional operator.
# if defined(BOOST_FOREACH_NO_RVALUE_DETECTION)                                                 \
  || defined(BOOST_NO_SFINAE)                                                                   \
  || BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))                                        \
  || BOOST_WORKAROUND(BOOST_INTEL_WIN, BOOST_TESTED_AT(1400))                                   \
  || BOOST_WORKAROUND(__GNUC__, < 3)                                                            \
  || (BOOST_WORKAROUND(__GNUC__, == 3) && (__GNUC_MINOR__ <= 2))                                \
  || (BOOST_WORKAROUND(__GNUC__, == 3) && (__GNUC_MINOR__ <= 3) && defined(__APPLE_CC__))       \
  || BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(600))                                         \
  || BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3206))                                      \
  || BOOST_WORKAROUND(__SUNPRO_CC, >= 0x5100)                                                   \
  || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x590))
#  define BOOST_FOREACH_NO_CONST_RVALUE_DETECTION
# else
#  define BOOST_FOREACH_RUN_TIME_CONST_RVALUE_DETECTION
# endif
#endif

#ifdef BOOST_FOREACH_NO_RVALUE_DETECTION
  #define WG_RVALUESIMULATOR_DETAIL_CONFIG_NO_RVALUEDETECTION
#endif
#ifdef BOOST_FOREACH_NO_CONST_RVALUE_DETECTION
  #define WG_RVALUESIMULATOR_DETAIL_CONFIG_NO_CONSTRVALUEDETECTION
#endif
#ifdef BOOST_FOREACH_COMPILE_TIME_CONST_RVALUE_DETECTION
  #define WG_RVALUESIMULATOR_DETAIL_CONFIG_CONSTRVALUEDETECTION_COMPILETIME
#endif
#ifdef BOOST_FOREACH_RUN_TIME_CONST_RVALUE_DETECTION
  #define WG_RVALUESIMULATOR_DETAIL_CONFIG_CONSTRVALUEDETECTION_RUNTIME
#endif

#ifdef WG_RVALUESIMULATOR_DETAIL_CONFIG_NO_RVALUEDETECTION
  #error "Unsupported compiler. See BOOST_FOREACH_NO_RVALUE_DETECTION."
#endif

#ifdef WG_RVALUESIMULATOR_DETAIL_CONFIG_NO_CONSTRVALUEDETECTION
  #error "Unsupported compiler. See BOOST_FOREACH_NO_CONST_RVALUE_DETECTION."
#endif

#endif /* WG_RVALUESIMULATOR_DETAIL_CONFIG_HH_ */
