#ifndef WG_LCLCONTEXT_DETAIL_TYPETRAITS_HH_
#define WG_LCLCONTEXT_DETAIL_TYPETRAITS_HH_

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
#include <boost/mpl/bool_fwd.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_const.hpp>

namespace wg
{
namespace rvaluesimulator
{
namespace detail
{

template<typename Bool1, typename Bool2>
inline ::boost::mpl::and_<Bool1, Bool2> * and_(Bool1 *, Bool2 *)
{
  return 0;
}

template<typename Bool1, typename Bool2, typename Bool3>
inline ::boost::mpl::and_<Bool1, Bool2, Bool3> * and_(Bool1 *, Bool2 *, Bool3 *)
{
  return 0;
}

template<typename Bool1, typename Bool2>
inline ::boost::mpl::or_<Bool1, Bool2> * or_(Bool1 *, Bool2 *)
{
  return 0;
}

template<typename Bool1, typename Bool2, typename Bool3>
inline ::boost::mpl::or_<Bool1, Bool2, Bool3> * or_(Bool1 *, Bool2 *, Bool3 *)
{
  return 0;
}

template<typename Bool1>
inline ::boost::mpl::not_<Bool1> * not_(Bool1 *)
{
  return 0;
}

template<typename T>
inline ::boost::is_array<T> * is_array_(T const &)
{
  return 0;
}

template<typename T>
inline ::boost::is_const<T> * is_const_(T &)
{
  return 0;
}

template<typename T>
inline ::boost::mpl::true_ * is_const_(T const &)
{
  return 0;
}

}
}
}

#endif /* WG_LCLCONTEXT_DETAIL_TYPETRAITS_HH_ */
