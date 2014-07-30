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

//###########
//Public APIs
//###########

// Expands to either "::boost::mpl::true_ *" or "::boost::mpl::false_ *"
// without evaluating expr.
#define WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLERVALUE(expr) \
  WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLERVALUE_IMPL(expr)

// Expands to either "::boost::mpl::true_ *" or "::boost::mpl::false_ *"
// without evaluating expr.
#define WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLELVALUE(expr) \
  WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLELVALUE_IMPL(expr)

// Expands to either "::boost::mpl::true_ *" or "::boost::mpl::false_ *"
// without evaluating expr.
// NOTE: any top level reference is ignored when evaluating this query.
#define WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISARRAY(expr) \
  WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISARRAY_IMPL(expr)

// Expands to either "::boost::mpl::true_ *" or "::boost::mpl::false_ *"
// without evaluating expr.
// NOTE: any top level reference is ignored when evaluating this query.
#define WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISEXPRCONST(expr) \
  WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISEXPRCONST_IMPL(expr)

namespace wg
{
namespace autosimulator
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

}
}
}

//####
//Impl
//####

#define WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLERVALUE_IMPL(expr) \
  (true ? 0 : ::wg::autosimulator::detail::is_mutable_rvalue(expr, 0) )

#define WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLELVALUE_IMPL(expr) \
  (true ? 0 : ::wg::autosimulator::detail::is_mutable_lvalue(expr) )

#define WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISARRAY_IMPL(expr) \
  (true ? 0 : ::wg::autosimulator::detail::is_array_(expr) )

#define WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISEXPRCONST_IMPL(expr) \
  (true \
    ? 0 \
    : ::wg::autosimulator::detail::is_expr_const( \
        WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLERVALUE(expr), \
        WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLELVALUE(expr) ) )

namespace wg
{
namespace autosimulator
{
namespace detail
{

//------------------------------------------------------------------------------
//is_mutable_rvalue
//
// 13.3.3.2/2
// When comparing the basic forms of implicit conversion sequences (as
// defined in 13.3.3.1)
// — a standard conversion sequence (13.3.3.1.1) is a better conversion
//   sequence than a user-defined conversion sequence or an
//   ellipsis conversion sequence

// 13.3.3.1.3
// An ellipsis conversion sequence occurs when an argument in a function
// call is matched with the ellipsis parameter specification of the
// function called.

// mutable-lvalues, const-lvalues, const-rvalues expressions will match
// both overloads, but the first one will be preferred because of the
// above.
// mutable-rvalues can only be matched by the second overload.
//------------------------------------------------------------------------------

template <typename T>
inline ::boost::mpl::false_ * is_mutable_rvalue(T &, int)
{
  return 0;
}

template <typename T>
inline ::boost::mpl::true_ * is_mutable_rvalue(T const &, ...)
{
  return 0;
}

template <typename T>
inline ::boost::mpl::false_ * is_mutable_lvalue(T const &)
{
  return 0;
}

template <typename T>
inline ::boost::mpl::true_ * is_mutable_lvalue(T &)
{
  return 0;
}

inline ::boost::mpl::true_ *
  is_expr_const(::boost::mpl::false_ *, ::boost::mpl::false_ *)
{
  return 0;
}

inline ::boost::mpl::false_ * is_expr_const(void *, void *)
{
  return 0;
}

template<typename T>
inline ::boost::is_array<T> * is_array_(T const &)
{
  return 0;
}

}
}
}

#endif /* WG_LCLCONTEXT_DETAIL_TYPETRAITS_HH_ */
