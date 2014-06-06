#ifndef WG_LVALUEBINDER_AUTOANY_HH_
#define WG_LVALUEBINDER_AUTOANY_HH_

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

#include <boost/utility/addressof.hpp>
#include <WG/Local/Detail/LValueBinder/TypeWrapper.hh>

//###########
//Public APIs
//###########

namespace wg
{
namespace lvaluebinder
{

struct auto_any;

// General utility for putting an object of any type into automatic storage.
typedef auto_any const & auto_any_t;

}
}

// Binds the result of an lvalue expression "expr" to an opaque type of
// type auto_any_t;
// Usage:
//   auto_any_t <identifier> = WG_LVALUEBINDER_BIND(expr);
#define WG_LVALUEBINDER_BIND(expr) \
  WG_LVALUEBINDER_BIND_IMPL(expr)

// Expands to a reference to the expression that was bound by
// WG_LVALUEBINDER_BIND.
// opaque_obj:
//   An object of type auto_any_t that was bound to WG_LVALUEBINDER_BIND.
// expr:
//   The original parameter to WG_LVALUEBINDER_BIND.
#define WG_LVALUEBINDER_NONOPAQUEOBJ(opaque_obj, expr) \
  WG_LVALUEBINDER_NONOPAQUEOBJ_IMPL(opaque_obj, expr)

//####
//Impl
//####

namespace wg
{
namespace lvaluebinder
{
namespace detail
{

//--------
//auto_any
//--------

struct auto_any
{
};

//-------------
//auto_any_impl
//-------------

template <typename T>
struct auto_any_impl : auto_any
{
  explicit auto_any_impl(T & t)
  : m_pitem(::boost::addressof(t))
  {}

  T & item()
  {
    return *this->m_pitem;
  }

private:
  T * m_pitem;
};

//-------------
//auto_any_cast
//-------------

template <typename T>
inline T & auto_any_cast_impl(auto_any_t a, type_wrapper<T> *)
{
  return static_cast<auto_any_impl<T> const &>(a).item();
}

//-------
//capture
//-------

template <typename T>
inline auto_any_impl<T> capture(T & t)
{
  return auto_any_impl<T>(t);
}

}
}
}

#define WG_LVALUEBINDER_BIND_IMPL(expr) \
  capture(expr);

#define WG_LVALUEBINDER_NONOPAQUEOBJ_IMPL(opaque_obj, expr) \
  ::wg::lvaluebinder::detail::auto_any_cast_impl( \
    opaque_obj, \
    WG_RVALUESIMULATOR_DETAIL_ENCODEDTYPEOF(expr))

#endif /* WG_LVALUEBINDER_AUTOANY_HH_ */
