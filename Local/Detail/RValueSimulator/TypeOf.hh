#ifndef WG_RVALUESIMULATOR_ENCODEDTYPEOF_HH_
#define WG_RVALUESIMULATOR_ENCODEDTYPEOF_HH_

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

#include <WG/Local/Detail/RValueSimulator/TypeTraits.hh>
#include <WG/Local/Detail/RValueSimulator/TypeWrapper.hh>

// A sneaky way to get the type of an expression without evaluating the
// expression.
#define WG_RVALUESIMULATOR_ENCODEDTYPEOF(expr)                                                               \
    (true \
      ? 0 \
      : ::wg::lclcontext::detail::encode_type( \
          expr, ::wg::lclcontext::detail::is_const_(expr)))

#endif /* WG_RVALUESIMULATOR_ENCODEDTYPEOF_HH_ */
