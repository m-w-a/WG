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
#include <WG/Local/Detail/AutoSimulator/Detail/TypeTraits.hh>

//###########
//Public APIs
//###########

namespace wg
{
namespace autosimulator
{
namespace detail
{

template<typename T, typename IsExprConst>
struct encoded_type;

}
}
}

// Expands to "encoded_type<NonConstNonRefExprType, IsExprConst> *" without
// evaluating expr, where
// 1) NonConstNonRefExprType is the equivalent of BOOST_TYPEOF(expr), and
// 2) IsExprConst is either ::boost::mpl::false_ or ::boost::mpl::true_
// Note: if expr is an rvalue then IsExprConst will always be ::boost::mpl::true_.
#define WG_AUTOSIMULATOR_DETAIL_ENCODEDTYPEOF(expr) \
  (true \
    ? 0 \
    : ::wg::autosimulator::detail::encode_typeof( \
        expr, ::wg::autosimulator::detail::is_const_(expr)))

//####
//Impl
//####

namespace wg
{
namespace autosimulator
{
namespace detail
{

template<typename T, typename IsExprConst>
struct encoded_type : ::boost::mpl::if_<IsExprConst, T const, T>
{
};

template<typename T>
inline encoded_type<T, ::boost::mpl::false_> *
  encode_typeof(T &, ::boost::mpl::false_ *)
{ return 0; }

template<typename T>
inline encoded_type<T, ::boost::mpl::true_> *
  encode_typeof(T const &, ::boost::mpl::true_ *)
{ return 0; }

}
}
}

#endif /* WG_AUTOSIMULATOR_TYPEWRAPPER_HH_ */
