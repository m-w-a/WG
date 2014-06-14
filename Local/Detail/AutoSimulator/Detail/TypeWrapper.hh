#ifndef WG_AUTOSIMULATOR_TYPEWRAPPER_HH_
#define WG_AUTOSIMULATOR_TYPEWRAPPER_HH_

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

#include <boost/mpl/bool_fwd.hpp>
#include <boost/mpl/if.hpp>

//###########
//Public APIs
//###########

namespace wg
{
namespace autosimulator
{

template<typename T, typename IsExprConst>
struct type_wrapper;

}
}

// Expands to "type_wrapper<T, IsExprConst> *" without evaluating expr, where
// T is the equivalent of BOOST_TYPEOF(expr), and
// IsExprConst is either ::boost::mpl::false_ or ::boost::mpl::true_
// Note: if expr is an rvalue then IsExprConst will always be ::boost::mpl::true_.
#define WG_AUTOSIMULATOR_DETAIL_ENCODEDTYPEOF(expr) \
  (true \
    ? 0 \
    : ::wg::lclcontext::detail::encode_type( \
        expr, ::wg::lclcontext::detail::is_const_(expr)))

//####
//Impl
//####

namespace wg
{
namespace autosimulator
{

template<typename T, typename IsExprConst>
struct type_wrapper : ::boost::mpl::if_<IsExprConst, T const, T>
{
};

template<typename T>
inline type_wrapper<T, ::boost::mpl::false_> *
  encode_type(T &, ::boost::mpl::false_ *)
{ return 0; }

template<typename T>
inline type_wrapper<T, ::boost::mpl::true_> *
  encode_type(T const &, ::boost::mpl::true_ *)
{ return 0; }

}
}

#endif /* WG_AUTOSIMULATOR_TYPEWRAPPER_HH_ */
