#ifndef WG_RVALUESIMULATOR_AUTOANY_HH_
#define WG_RVALUESIMULATOR_AUTOANY_HH_

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

#include <new>
#include <boost/config.hpp>
#include <boost/aligned_storage.hpp>
#include <boost/mpl/bool_fwd.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/mpl/if.hpp>
#include <WG/Local/Detail/RValueSimulator/Config.hh>

//###########
//Public APIs
//###########

namespace wg
{
namespace rvaluesimulator
{

//----------
//Fwd Dclns.
//----------

struct auto_any;

template<typename T>
struct auto_any_impl;

//------------------------------------------------------------------------------
//auto_any_t
//  General utility for putting an object of any type into automatic storage.
//------------------------------------------------------------------------------
typedef auto_any const & auto_any_t;

//-------------
//auto_any_cast
//-------------
struct util
{
  template<typename T, typename IsConst>
  inline BOOST_DEDUCED_TYPENAME ::boost::mpl::if_<IsConst, T const, T>::type &
    auto_any_cast(auto_any_t a)
  {
    return static_cast<auto_any_impl<T> const &>(a).item;
  }
};

//--------
//auto_any
//--------
struct auto_any
{
  // auto_any must evaluate to false in boolean contexts so that
  // they can be declared in if() statements.
  operator bool() const
  {
    return false;
  }
};

//-------------
//auto_any_impl
//-------------
template<typename T>
struct auto_any_impl : auto_any
{
  explicit auto_any_impl(T const & t)
  : item(t)
  {}

private:
  friend struct util;
private:
  // Temporaries of type auto_any_impl will be bound to const auto_any
  // references, but we still want to be able to mutate the stored
  // data, so declare it as mutable.
  mutable T item;
};

}
}

//####
//Impl
//####

namespace wg
{
namespace rvaluesimulator
{
namespace detail
{

//------------------------------------------------------------------------------
//capture
//  Captures the result of an expression.
//  If it's an lvalue a copy of it is made, else a reference to it is held.
//------------------------------------------------------------------------------

// WG_RVALUESIMULATOR_CONFIG_CONSTRVALUEDETECTION_COMPILETIME:
//   t is a rvalue
template<typename T>
inline auto_any_impl<T> capture(T const & t, ::boost::mpl::true_ *)
{
  return auto_any_impl<T>(t);
}

// WG_RVALUESIMULATOR_CONFIG_CONSTRVALUEDETECTION_COMPILETIME:
//   t is a lvalue
// WG_RVALUESIMULATOR_CONFIG_CONSTRVALUEDETECTION_RUNTIME:
//   t is an array or a non-const lvalue
template<typename T>
inline auto_any_impl<T *> capture(T & t, ::boost::mpl::false_ *)
{
  // Cannot seem to get sunpro to handle addressof() with array types.
#if BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x570))
  return auto_any_impl<T *>(&t);
#else
  return auto_any_impl<T *>(::boost::addressof(t));
#endif
}

#ifdef WG_RVALUESIMULATOR_CONFIG_CONSTRVALUEDETECTION_RUNTIME
  template<typename T>
  struct simple_variant;

  // t is const, non-array lvalue or it's an rvalue
  // The constness of T is erased here, but we will be able to retrieve it with
  // auto_any_cast and the help of type_wrapper.
  template<typename T>
  inline auto_any_impl<simple_variant<T> > capture(T const & t, bool * rvalue)
  {
    // Have to use a variant because we don't know whether to capture by value
    // or by reference until runtime.
    return auto_any_impl<simple_variant<T> >(
      *rvalue ? simple_variant<T>(t) : simple_variant<T>(&t));
  }

  //-------------------------------------
  //simple_variant
  //  Holds either a T or a "T const *".
  //-------------------------------------

  template<typename T>
  struct simple_variant
  {
    simple_variant(T const * t)
    : m_is_rvalue(false)
    {
      *static_cast<T const **>(this->m_data.address()) = t;
    }

    simple_variant(T const & t)
    : m_is_rvalue(true)
    {
      ::new(this->m_data.address()) T(t);
    }

    simple_variant(simple_variant const & that)
    : m_is_rvalue(that.m_is_rvalue)
    {
      if(this->m_is_rvalue)
      {
        ::new(this->m_data.address()) T(*that.get());
      }
      else
      {
        *static_cast<T const **>(this->m_data.address()) = that.get();
      }
    }

    ~simple_variant()
    {
      if(this->m_is_rvalue)
      {
        this->get()->~T();
      }
    }

    T const * get() const
    {
      if(this->m_is_rvalue)
      {
        return static_cast<T const *>(this->m_data.address());
      }
      else
      {
        return *static_cast<T const * const *>(this->m_data.address());
      }
    }

  private:
    // Purposefully declared and not defined.
    simple_variant & operator=(simple_variant const &);
  private:
    // TODO: don't understand this logic.
    enum { m_size = sizeof(T) > sizeof(T*) ? sizeof(T) : sizeof(T*) };
    bool const m_is_rvalue;
    ::boost::aligned_storage<m_size> m_data;
  };
#endif

}
}
}

#endif /* WG_RVALUESIMULATOR_AUTOANY_HH_ */
