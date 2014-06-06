#ifndef WG_RVALUESIMULATOR_CAPTURE_HH_
#define WG_RVALUESIMULATOR_CAPTURE_HH_

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
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_rvalue_reference.hpp>
#include <boost/type_traits/is_abstract.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/utility/enable_if.hpp>
#include <WG/Local/Detail/RValueSimulator/Config.hh>
#include <WG/Local/Detail/RValueSimulator/AutoAny.hh>

//###########
//Public APIs
//###########

// Usage:
//   auto_any_t captured_obj = WG_RVALUESIMULATOR_CAPTURE(...) ;
// is_rvalue_flag:
//   a boolean variable. This will be ignored if
//   WG_RVALUESIMULATOR_CONFIG_CONSTRVALUEDETECTION_COMPILETIME is defined.
#define WG_RVALUESIMULATOR_CAPTURE(expr, is_rvalue_flag) \
  WG_RVALUESIMULATOR_CAPTURE_IMPL(expr, is_rvalue_flag)

// WG_RVALUESIMULATOR_CONFIG_CONSTRVALUEDETECTION_COMPILETIME:
//   expands to:
//     1) ::boost::mpl::true_ *, if expr is a rvalue, else
//     2) ::boost::mpl::false_ * if expr is a lvalue.
// WG_RVALUESIMULATOR_CONFIG_CONSTRVALUEDETECTION_RUNTIME:
//   expands to:
//     1) ::boost::mpl::false_ *, if expr is an array or a non-const lvalue
//     2) bool *, if expr is const, non-array lvalue or it's an rvalue
#define WG_RVALUESIMULATOR_CAPTURE_CATEGORY(expr) \
  WG_RVALUESIMULATOR_CAPTURE_CATEGORY_IMPL(expr)

//###########
//Impl Macros
//###########

///////////////////////////////////////////////////////////////////////////////
// R-values and const R-values supported here with zero runtime overhead
///////////////////////////////////////////////////////////////////////////////
#ifdef WG_RVALUESIMULATOR_CONFIG_CONSTRVALUEDETECTION_COMPILETIME
  //////////////////////////////////////////////////////////////////////////////
  // Rvalue references makes it drop-dead simple to detect at compile time
  // whether an expression is an rvalue.
  //////////////////////////////////////////////////////////////////////////////
  #ifndef BOOST_NO_CXX11_RVALUE_REFERENCES

    namespace wg
    {
    namespace rvaluesimulator
    {
    namespace detail
    {

    template<typename T>
      inline ::boost::is_rvalue_reference<T &&> * is_rvalue_(T &&, int)
      {
        return 0;
      }

    #define WG_RVALUESIMULATOR_CAPTURE_ISRVALUE(expr) \
      ::wg::rvaluesimulator::detail::is_rvalue_((expr), 0)

    }
    }
    }

  //////////////////////////////////////////////////////////////////////////////
  // Detect at compile-time whether an expression yields an rvalue or
  // an lvalue. This is rather non-standard, but some popular compilers
  // accept it.
  //////////////////////////////////////////////////////////////////////////////
  #elif defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    namespace wg
    {
    namespace rvaluesimulator
    {
    namespace detail
    {

    template<typename T>
    inline ::boost::mpl::false_ * is_rvalue_(T &, int)
    {
      return 0;
    }

    template<typename T>
    inline ::boost::mpl::true_ * is_rvalue_(T const &, ...)
    {
      return 0;
    }

    }
    }
    }

    #define WG_RVALUESIMULATOR_CAPTURE_ISRVALUE(expr) \
      boost::foreach_detail_::and_( \
        boost::foreach_detail_::not_(boost::foreach_detail_::is_array_(expr)) , \
        (true ? 0 : ::wg::rvaluesimulator::detail::is_rvalue_( \
          (true ? ::wg::rvaluesimulator::detail::make_probe(expr) : (expr)), 0) ) )

    namespace wg
    {
    namespace rvaluesimulator
    {
    namespace detail
    {

    template<typename T>
    struct rvalue_probe;

    template<typename T>
    rvalue_probe<T> const make_probe(T const &)
    {
      return rvalue_probe<T>();
    }

    template<typename T>
    struct rvalue_probe
    {
      struct private_type_ {};
      // can't ever return an array by value
      typedef BOOST_DEDUCED_TYPENAME ::boost::mpl::if_
      <
        ::boost::mpl::or_<::boost::is_abstract<T>, ::boost::is_array<T> > ,
         private_type_ ,
         T
      >::type value_type;
      // never called
      operator value_type()
      { return *reinterpret_cast<value_type *>(this); }
      // never called
      operator T &() const
      { return *reinterpret_cast<T *>(const_cast<rvalue_probe *>(this)); }
    };

    }
    }
    }
  #endif

  #define WG_RVALUESIMULATOR_CAPTURE_EVALUATE(expr) (expr)

  #define WG_RVALUESIMULATOR_CAPTURE_SHOULDCOPY(expr) \
    (true ? 0 : WG_RVALUESIMULATOR_CAPTURE_ISRVALUE(expr) )

  #define WG_RVALUESIMULATOR_CAPTURE_IMPL(expr, ignored) \
    ::wg::rvaluesimulator::detail::capture( \
      WG_RVALUESIMULATOR_CAPTURE_EVALUATE(expr) , \
      WG_RVALUESIMULATOR_CAPTURE_SHOULDCOPY(expr))

  #define WG_RVALUESIMULATOR_CAPTURE_CATEGORY_IMPL(expr) \
    WG_RVALUESIMULATOR_CAPTURE_SHOULDCOPY(expr)

///////////////////////////////////////////////////////////////////////////////
// Detect at run-time whether an expression yields an rvalue
// or an lvalue. This is 100% standard C++, but not all compilers
// accept it.
///////////////////////////////////////////////////////////////////////////////
#elif WG_RVALUESIMULATOR_CONFIG_CONSTRVALUEDETECTION_RUNTIME

  namespace wg
  {
  namespace rvaluesimulator
  {
  namespace detail
  {

  //-------------
  // rvalue_probe
  //-------------

  template<typename T>
  rvalue_probe<T> make_probe(T & value, bool & m_is_rvalue)
  {
    return rvalue_probe<T>(value, m_is_rvalue);
  }

  // This may seem redundant but it's not. It's needed for the case where the
  // first parameter is an rvalue.
  template<typename T>
  rvalue_probe<T const> make_probe(T const & value, bool & m_is_rvalue)
  {
    return rvalue_probe<T const>(value, m_is_rvalue);
  }

  template<typename T>
  struct rvalue_probe
  {
    rvalue_probe(T & value, bool & m_is_rvalue)
    : m_value(value),
      m_is_rvalue(m_is_rvalue)
    {}

    struct private_type_ {};
    // can't ever return an array or an abstract type by m_value
  #ifdef BOOST_NO_IS_ABSTRACT
    typedef BOOST_DEDUCED_TYPENAME ::boost::mpl::if_
    <
      ::boost::is_array<T>, private_type_, T
    >::type value_type;
  #else
    typedef BOOST_DEDUCED_TYPENAME ::boost::mpl::if_
    <
      ::boost::mpl::or_<::boost::is_abstract<T>, ::boost::is_array<T> > ,
      private_type_ ,
      T
    >::type value_type;
  #endif

    operator value_type()
    {
      this->m_is_rvalue = true;
      return this->m_value;
    }

    operator T &() const
    {
      return this->m_value;
    }

  private:
    T & m_value;
    bool & m_is_rvalue;
  };

  // If the collection is an array or is nonconst, it must be an lvalue.
  template<typename LValue>
  inline BOOST_DEDUCED_TYPENAME
    ::boost::enable_if<LValue, ::boost::mpl::false_>::type *
  should_copy_impl(LValue *, bool *)
  {
    return 0;
  }

  // Otherwise, we must determine at runtime whether it's an lvalue or rvalue
  inline bool *
  should_copy_impl(::boost::mpl::false_ *, bool * is_rvalue)
  {
    return is_rvalue;
  }

  }
  }
  }

  // Evaluate expr and detect if it's an lvalue or an rvalue.
  #define WG_RVALUESIMULATOR_CAPTURE_EVALUATE_AND_SETRVALUEFLAG( \
    expr, is_rvalue_flag) \
      (true ? \
        ::wg::rvaluesimulator::detail::make_probe((expr), is_rvalue_flag ) \
        : (expr))

  // The rvalue/lvalue-ness of the collection expression is determined
  // dynamically, unless the type is an array or is non-const,
  // in which case we know it's an lvalue.
  #define WG_RVALUESIMULATOR_CAPTURE_SHOULDCOPY(expr, ptr_is_rvalue_flag) \
    ( \
    ::wg::rvaluesimulator::should_copy_impl( \
      true ? 0 : ::wg::rvaluesimulator::detail::or_( \
        ::wg::rvaluesimulator::detail::is_array_(expr) , \
        ::wg::rvaluesimulator::detail::not_(::wg::rvaluesimulator::detail::is_const_(expr))) , \
      ptr_is_rvalue_flag) \
    )

  #define WG_RVALUESIMULATOR_CAPTURE_IMPL(expr, is_rvalue_flag) \
    ::wg::rvaluesimulator::detail::capture( \
      WG_RVALUESIMULATOR_CAPTURE_EVALUATE_AND_SETRVALUEFLAG(expr, is_rvalue_flag), \
      WG_RVALUESIMULATOR_CAPTURE_SHOULDCOPY(expr, &is_rvalue_flag) )

  #define WG_RVALUESIMULATOR_CAPTURE_CATEGORY_IMPL(expr) \
    WG_RVALUESIMULATOR_CAPTURE_SHOULDCOPY(expr, 0)

#endif

#endif /* WG_RVALUESIMULATOR_CAPTURE_HH_ */
