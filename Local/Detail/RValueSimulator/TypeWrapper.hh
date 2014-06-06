#ifndef WG_LCLCONTEXT_DETAIL_TYPEWRAPPER_HH_
#define WG_LCLCONTEXT_DETAIL_TYPEWRAPPER_HH_

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

namespace wg
{
namespace rvaluesimulator
{

template<typename T, typename IsConst = ::boost::mpl::false_>
struct type_wrapper : ::boost::mpl::if_<IsConst, T const, T>
{
};

template<typename T>
inline type_wrapper<T> *
  encode_type(T &, ::boost::mpl::false_ *)
{ return 0; }

template<typename T>
inline type_wrapper<T, ::boost::mpl::true_> *
  encode_type(T const &, ::boost::mpl::true_ *)
{ return 0; }

}
}

#endif /* WG_LCLCONTEXT_DETAIL_TYPEWRAPPER_HH_ */
