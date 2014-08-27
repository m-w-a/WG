#ifndef WG_AUTOSIMULATOR_DETAIL_AUTOANY_HH_
#define WG_AUTOSIMULATOR_DETAIL_AUTOANY_HH_

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
#include <boost/move/core.hpp>
#include <boost/move/utility.hpp>
#include <boost/config.hpp>
#include <boost/aligned_storage.hpp>
#include <boost/mpl/bool_fwd.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_rvalue_reference.hpp>
#include <boost/type_traits/is_abstract.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/static_assert.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/enable_if.hpp>
#include <WG/Local/Detail/AutoSimulator/Detail/Config.hh>
#include <WG/Local/Detail/AutoSimulator/Detail/TypeTraits.hh>
#include <WG/Local/Detail/AutoSimulator/Detail/TypeWrapper.hh>

//###########
//Public APIs
//###########

// Usage:
//   auto_any_t captured_obj =
//     WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(...) ;
#define WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(expr, mutable_boolean_flag) \
  WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE_IMPL(expr, mutable_boolean_flag)

namespace wg
{
namespace autosimulator
{
namespace detail
{

struct expr_category_rvalue {};
struct expr_category_lvalue {};
struct expr_category_mutable_rvalue : public expr_category_rvalue {};

#ifdef WG_AUTOSIMULATOR_DETAIL_CONFIG_CONSTRVALUEDETECTION_COMPILETIME
  struct expr_category_const_rvalue : public expr_category_rvalue {};
#elif defined(WG_AUTOSIMULATOR_DETAIL_CONFIG_CONSTRVALUEDETECTION_RUNTIME)
  struct expr_category_array_or_mutable_lvalue : public expr_category_lvalue {};
  struct expr_category_const_nonarray_lvalue_or_const_rvalue {};
#endif

}
}
}

// WG_AUTOSIMULATOR_DETAIL_CONFIG_CONSTRVALUEDETECTION_COMPILETIME:
//   expands to:
//     1) expr_category_mutable_rvalue, or
//     2) expr_category_const_rvalue, or
//     2) expr_category_lvalue.
// WG_AUTOSIMULATOR_DETAIL_CONFIG_CONSTRVALUEDETECTION_RUNTIME:
//   expands to:
//     1) expr_category_mutable_rvalue, or
//     2) expr_category_array_or_mutable_lvalue, or
//     3) expr_category_const_nonarray_lvalue_or_const_rvalue.
#define WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(expr) \
  WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY_IMPL(expr)

#define WG_AUTOSIMULATOR_DETAIL_AUTOANY_VALUE(captured_obj, expr) \
  WG_AUTOSIMULATOR_DETAIL_AUTOANY_VALUE_IMPL(captured_obj, expr)

#define WG_AUTOSIMULATOR_DETAIL_AUTOANY_ISRVALUE(captured_obj, expr) \
  WG_AUTOSIMULATOR_DETAIL_AUTOANY_ISRVALUE_IMPL(captured_obj, expr)

// This is runtime deduction, not compile-time deduction.
#define WG_AUTOSIMULATOR_DETAIL_AUTOANY_AUTOANYIMPL_DEDUCEDPTRTYPE(expr) \
  WG_AUTOSIMULATOR_DETAIL_AUTOANY_AUTOANYIMPL_DEDUCEDPTRTYPE_IMPL(expr)

#define WG_AUTOSIMULATOR_DETAIL_AUTOANY_AUTOANYIMPL_VALUE(obj) \
  WG_AUTOSIMULATOR_DETAIL_AUTOANY_AUTOANYIMPL_VALUE_IMPL(obj)

#define WG_AUTOSIMULATOR_DETAIL_AUTOANY_AUTOANYIMPL_ISRVALUE(obj) \
  WG_AUTOSIMULATOR_DETAIL_AUTOANY_AUTOANYIMPL_ISRVALUE_IMPL(obj)

//####
//Impl
//####

namespace wg
{
namespace autosimulator
{
namespace detail
{

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

protected:
  auto_any() {}
  auto_any(BOOST_RV_REF(auto_any) rhs) {}

private:
  //Declared and purposefully not defined.
  auto_any & operator=(auto_any);
private:
  BOOST_COPYABLE_AND_MOVABLE(auto_any)
};

//-------------
//auto_any_impl
//-------------

template
<
  typename ExprCategory,
  typename CapturedType,
  typename EnableIfDummyArg = void
>
struct auto_any_impl;

//expr_category_rvalue

template
<
  typename ExprCategory,
  typename CapturedType
>
struct auto_any_impl
<
  ExprCategory,
  CapturedType,
  BOOST_DEDUCED_TYPENAME ::boost::enable_if
  <
    ::boost::is_base_of<expr_category_rvalue, ExprCategory>
  >::type
>
: public auto_any
{
  auto_any_impl(bool, CapturedType const & obj)
  : item(obj)
  {}

  auto_any_impl(bool, BOOST_RV_REF(CapturedType) obj)
  : item(::boost::move(obj))
  {}

//TODO:
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
  auto_any_impl(auto_any_impl const & rhs)
  : item(rhs.item)
  {}
#endif

  auto_any_impl(BOOST_RV_REF(auto_any_impl) rhs)
  : auto_any(::boost::move(static_cast<auto_any &>(rhs))),
    item(::boost::move(rhs.item))
  {}

  bool is_rvalue() const
  { return true; }

  CapturedType & value() const
  { return this->item; }

private:
  //Purposefully declared and not defined.
  auto_any_impl & operator=(auto_any_impl);
private:
  BOOST_COPYABLE_AND_MOVABLE(auto_any_impl)
private:
  // Temporaries of type auto_any_impl will be bound to const auto_any
  // references, but we may still want to be able to mutate the stored
  // data, so declare it as mutable.
  mutable CapturedType item;
};

//expr_category_lvalue

template
<
  typename ExprCategory,
  typename CapturedType
>
struct auto_any_impl
<
  ExprCategory,
  CapturedType,
  BOOST_DEDUCED_TYPENAME ::boost::enable_if
  <
    ::boost::is_base_of<expr_category_lvalue, ExprCategory>
  >::type
>
: public auto_any
{
  auto_any_impl(bool, CapturedType & obj)
  :
#if BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x570))
    item(&obj)
#else
    item(::boost::addressof(obj))
#endif
  {}

//TODO:
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
  auto_any_impl(auto_any_impl const & rhs)
  : item(rhs.item)
  {}
#endif

  auto_any_impl(BOOST_RV_REF(auto_any_impl) rhs)
  : auto_any(::boost::move(static_cast<auto_any &>(rhs))),
    item(rhs.item)
  {
    rhs.item = 0;
  }

  bool is_rvalue() const
  { return false; }

  CapturedType & value() const
  { return *this->item; }

private:
  //Purposefully declared and not defined.
  auto_any_impl & operator=(auto_any_impl);
private:
  BOOST_COPYABLE_AND_MOVABLE(auto_any_impl)
private:
  CapturedType * item;
};

//expr_category_const_nonarray_lvalue_or_const_rvalue

#ifdef WG_AUTOSIMULATOR_DETAIL_CONFIG_CONSTRVALUEDETECTION_RUNTIME
  template<typename T>
  struct simple_variant;

  template <typename CapturedType>
  struct auto_any_impl
  <
    expr_category_const_nonarray_lvalue_or_const_rvalue,
    CapturedType,
    void
  >
  : public auto_any
  {
    auto_any_impl(bool const is_rvalue, CapturedType & obj)
    : item(is_rvalue
        ? simple_variant<CapturedType>(expr_category_rvalue(), obj)
        : simple_variant<CapturedType>(expr_category_lvalue(), obj) )
    {}

  //TODO:
  #ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    auto_any_impl(auto_any_impl const & rhs)
    : item(rhs.item)
    {}
  #endif

    auto_any_impl(BOOST_RV_REF(auto_any_impl) rhs)
    : auto_any(::boost::move(static_cast<auto_any &>(rhs))),
      item(::boost::move(rhs.item))
    {}

    bool is_rvalue() const
    { return this->item.is_rvalue(); }

    CapturedType & value() const
    { return this->item.get_value(); }

  private:
    //Purposefully declared and not defined.
    auto_any_impl & operator=(auto_any_impl);
  private:
    BOOST_COPYABLE_AND_MOVABLE(auto_any_impl)
  private:
    // Have to use a variant because we don't know whether to capture by value
    // or by reference until runtime.
    simple_variant<CapturedType> item;
  };
#endif

//------------------------------------------------------------------------------
//capture
//  Captures the result of an expression.
//  If it's an lvalue a copy of it is made, else a reference to it is held.
//------------------------------------------------------------------------------

// is_rvalue_flag:
//   must be const reference type. This is because this value may have to
//   be determined during the evaluation of obj parameter; and in C++ the order
//   of function argument evaluation is implementation defined.
template <typename S, typename T, typename IsExprConst>
inline auto_any_impl
<
  expr_category_mutable_rvalue,
  BOOST_DEDUCED_TYPENAME encoded_type<T, IsExprConst>::non_ref_type
>
  capture(
    expr_category_mutable_rvalue,
    S const & obj,
    bool const & is_rvalue_flag,
    encoded_type<T, IsExprConst> *)
{
  typedef
    BOOST_DEDUCED_TYPENAME encoded_type<T, IsExprConst>::non_ref_type
      expr_type;
  // This const_cast is safe because it has been determined that obj is
  // bound to a mutable rvalue.
  return
    auto_any_impl<expr_category_mutable_rvalue, expr_type>(
      is_rvalue_flag, ::boost::move(const_cast<expr_type &>(obj)) );
}

// is_rvalue_flag:
//   must be const reference type. This is because this value may have to
//   be determined during the evaluation of obj parameter; and in C++ the order
//   of function argument evaluation is implementation defined.
template <typename ExprCategory, typename S, typename T, typename IsExprConst>
inline auto_any_impl
<ExprCategory, BOOST_DEDUCED_TYPENAME encoded_type<T, IsExprConst>::non_ref_type>
  capture(
    ExprCategory,
    S & obj,
    bool const & is_rvalue_flag,
    encoded_type<T, IsExprConst> *)
{
  return
    auto_any_impl
    <
      ExprCategory,
      BOOST_DEDUCED_TYPENAME encoded_type<T, IsExprConst>::non_ref_type
    >(is_rvalue_flag, obj);
}

#ifdef WG_AUTOSIMULATOR_DETAIL_CONFIG_CONSTRVALUEDETECTION_RUNTIME

  //-------------------------------------
  //simple_variant<T>
  //  Holds either a "T const" or a "T const *".
  //  "T const" means the expression was an rvalue.
  //  "T const *" means the expression was an lvalue.
  //-------------------------------------

  template<typename T>
  struct simple_variant
  {
    simple_variant(expr_category_lvalue, T const & t)
    : m_is_rvalue(false)
    {
      this->init_lvalue(t);
    }

    simple_variant(expr_category_rvalue, T const & t)
    : m_is_rvalue(true)
    {
      this->init_rvalue(t);
    }

    simple_variant(simple_variant const & that)
    : m_is_rvalue(that.m_is_rvalue)
    {
      if(this->m_is_rvalue)
      {
        this->init_rvalue(that.get_rvalue());
      }
      else
      {
        this->init_lvalue(that.get_lvalue());
      }
    }

    simple_variant(BOOST_RV_REF(simple_variant) rhs)
    : m_is_rvalue(rhs.m_is_rvalue)
    {
      if(this->m_is_rvalue)
      {
        ::new(this->m_data.address()) T(::boost::move(rhs.get_rvalue()));
      }
      else
      {
        this->init_lvalue(rhs.get_lvalue());
      }
    }

    ~simple_variant()
    {
      if(this->m_is_rvalue)
      {
        this->get_rvalue().~T();
      }
    }

    T const & get_value() const
    {
      if(this->m_is_rvalue)
      {
        return this->get_rvalue();
      }
      else
      {
        return this->get_lvalue();
      }
    }

    bool is_rvalue() const
    {
      return this->m_is_rvalue;
    }

  private:
    BOOST_COPYABLE_AND_MOVABLE(simple_variant)
  private:
    // Purposefully declared and not defined.
    simple_variant & operator=(simple_variant);
  private:
    T const & get_rvalue() const
    {
      return *static_cast<T const *>(this->m_data.address());
    }

    T const & get_lvalue() const
    {
      return **static_cast<T const * const *>(this->m_data.address());
    }

    void init_rvalue(T const & t)
    {
      ::new(this->m_data.address()) T(t);
    }

    void init_lvalue(T const & t)
    {
      *static_cast<T const **>(this->m_data.address()) = ::boost::addressof(t);
    }
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

///////////////////////////////////////////////////////////////////////////////
// R-values and const R-values supported here with zero runtime overhead
///////////////////////////////////////////////////////////////////////////////
#ifdef WG_AUTOSIMULATOR_DETAIL_CONFIG_CONSTRVALUEDETECTION_COMPILETIME
  //////////////////////////////////////////////////////////////////////////////
  // Rvalue references makes it drop-dead simple to detect at compile time
  // whether an expression is an rvalue.
  //////////////////////////////////////////////////////////////////////////////
  #ifndef BOOST_NO_CXX11_RVALUE_REFERENCES

    namespace wg
    {
    namespace autosimulator
    {
    namespace detail
    {

    template<typename T>
    inline ::boost::is_rvalue_reference<T &&> * is_rvalue_(T &&)
    {
      return 0;
    }

    #define WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_ISRVALUE(expr) \
      (true ? 0 : ::wg::autosimulator::detail::is_rvalue_(expr) )

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
    namespace autosimulator
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

    #define WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_ISRVALUE(expr) \
      (true ? 0 : \
        ::wg::autosimulator::detail::and_( \
          ::wg::autosimulator::detail::not_( \
            boost::foreach_detail_::is_array_(expr)) , \
          (true ? 0 : ::wg::autosimulator::detail::is_rvalue_( \
            (true ? ::wg::autosimulator::detail::make_probe(expr) : (expr)), 0) ) ) )

  #endif

  namespace wg
  {
  namespace autosimulator
  {
  namespace detail
  {

  inline expr_category_mutable_rvalue
    expr_category(::boost::mpl::true_ *, ::boost::mpl::true_ *)
  {
    return expr_category_mutable_rvalue();
  }

  inline expr_category_const_rvalue
    expr_category(::boost::mpl::false_ *, ::boost::mpl::true_ *)
  {
    return expr_category_const_rvalue();
  }

  inline expr_category_lvalue
    expr_category(::boost::mpl::false_ *, ::boost::mpl::false_ *)
  {
    return expr_category_lvalue();
  }

  }
  }
  }

  #define WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_EVALUATE(expr) (expr)

  #define WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY_IMPL(expr) \
    ::wg::autosimulator::detail::expr_category( \
      WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLERVALUE(expr), \
      WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_ISRVALUE(expr) )

  #define WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE_IMPL(expr, is_rvalue_flag) \
    ::wg::autosimulator::detail::capture( \
      WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(expr), \
      WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_EVALUATE(expr) , \
      is_rvalue_flag, \
      WG_AUTOSIMULATOR_DETAIL_ENCODEDTYPEOF(expr) )

///////////////////////////////////////////////////////////////////////////////
// Detect at run-time whether an expression yields an rvalue
// or an lvalue. This is 100% standard C++, but not all compilers
// accept it.
///////////////////////////////////////////////////////////////////////////////
#elif defined(WG_AUTOSIMULATOR_DETAIL_CONFIG_CONSTRVALUEDETECTION_RUNTIME)

  namespace wg
  {
  namespace autosimulator
  {
  namespace detail
  {

  template<typename T>
  struct rvalue_probe;

  //-------------
  // rvalue_probe
  //-------------

  // Expr is a mutable rvalue, therefore:
  //   1) catch by const reference
  //   2) return by value.
  template <typename S, typename T, typename IsExprConst>
  BOOST_DEDUCED_TYPENAME encoded_type<T, IsExprConst>::non_ref_type
    probe(
      expr_category_mutable_rvalue,
      S const & value,
      bool & is_rvalue,
      encoded_type<T, IsExprConst> *)
  {
    is_rvalue = true;
    typedef
      BOOST_DEDUCED_TYPENAME encoded_type<T, IsExprConst>::non_ref_type
        return_type;
    // This const_cast is safe because it has been determined that value is
    // bound to a mutable rvalue.
    // DO NOT use BOOST_MOVE_RET since we want an explicit move in C++11.
    // value is not a local object so RVO won't kick, that's why we need move.
    return ::boost::move( const_cast<return_type &>(value) );
  }

  template<typename T>
  struct rvalue_probe;

  template <typename ExprCategory, typename S, typename T, typename IsExprConst>
  rvalue_probe<S>
    probe(
      ExprCategory,
      S & value,
      bool & is_rvalue,
      encoded_type<T, IsExprConst> *)
  {
    return rvalue_probe<S>(value, is_rvalue);
  }

  template<typename T>
  struct rvalue_probe
  {
    rvalue_probe(T & value, bool & m_is_rvalue)
    : m_value(value),
      m_is_rvalue(m_is_rvalue)
    {}

    struct private_type_ {};
    // can't ever return an array or an abstract type by value
  #ifdef BOOST_NO_IS_ABSTRACT
    typedef BOOST_DEDUCED_TYPENAME ::boost::mpl::if_
    <
      ::boost::is_array<T>, private_type_, T
    >::type value_type;
  #else
    typedef BOOST_DEDUCED_TYPENAME ::boost::mpl::if_
    <
      ::boost::mpl::or_< ::boost::is_abstract<T>, ::boost::is_array<T> > ,
      private_type_ ,
      T
    >::type value_type;
  #endif

    operator value_type ()
    {
      this->m_is_rvalue = true;
      // rvalue_probe should only be used for const rvalues.
      // Because const rvalues can't be moved a non-moved return is performed
      // here.
      BOOST_STATIC_ASSERT(( ::boost::is_const<T>::value ));
      return this->m_value;
    }

    operator T & () const
    {
      this->m_is_rvalue = false;
      return this->m_value;
    }

  private:
    T & m_value;
    bool & m_is_rvalue;
  };

  //-------------
  //expr_category
  //-------------

  inline expr_category_mutable_rvalue expr_category(
    ::boost::mpl::true_ *, ::boost::mpl::false_ *)
  {
    return expr_category_mutable_rvalue();
  }

  inline expr_category_array_or_mutable_lvalue expr_category(
    ::boost::mpl::false_ *, ::boost::mpl::true_ *)
  {
    return expr_category_array_or_mutable_lvalue();
  }

  inline expr_category_const_nonarray_lvalue_or_const_rvalue expr_category(
    ::boost::mpl::false_ *, ::boost::mpl::false_ *)
  {
    return expr_category_const_nonarray_lvalue_or_const_rvalue();
  }

  }
  }
  }

  // Evaluate expr and detect if it's an lvalue or an rvalue.
  #define WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_EVALUATE_AND_SETRVALUEFLAG( \
    expr, is_rvalue_flag) \
      (true ? \
        ::wg::autosimulator::detail::probe \
        ( \
          WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(expr), \
          (expr), \
          is_rvalue_flag, \
          WG_AUTOSIMULATOR_DETAIL_ENCODEDTYPEOF(expr) \
        ) \
        : (expr))

  // The rvalue/lvalue-ness of the collection expression is determined
  // dynamically, unless the type is an array or mutable lvalue, or is a
  // mutable rvalue.
  #define WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY_IMPL(expr) \
    ::wg::autosimulator::detail::expr_category \
    ( \
      WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLERVALUE(expr), \
      ::wg::autosimulator::detail::or_( \
        WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISARRAY(expr), \
        WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLELVALUE(expr) ) \
    )

  #define WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE_IMPL(expr, is_rvalue_flag) \
    ::wg::autosimulator::detail::capture( \
      WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(expr), \
      WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_EVALUATE_AND_SETRVALUEFLAG( \
        expr, is_rvalue_flag), \
      is_rvalue_flag, \
      WG_AUTOSIMULATOR_DETAIL_ENCODEDTYPEOF(expr) )

#endif

#define WG_AUTOSIMULATOR_DETAIL_AUTOANY_AUTOANYIMPL_DEDUCEDPTRTYPE_IMPL(expr) \
  ::wg::autosimulator::detail::dfta_auto_any_impl_type( \
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(expr), \
    WG_AUTOSIMULATOR_DETAIL_ENCODEDTYPEOF(expr) )

#define WG_AUTOSIMULATOR_DETAIL_AUTOANY_VALUE_IMPL(captured_obj, expr) \
  ::wg::autosimulator::detail::auto_any_impl_cast( \
    captured_obj, \
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(expr), \
    WG_AUTOSIMULATOR_DETAIL_ENCODEDTYPEOF(expr)).value()

#define WG_AUTOSIMULATOR_DETAIL_AUTOANY_ISRVALUE_IMPL(captured_obj, expr) \
  ::wg::autosimulator::detail::auto_any_impl_cast( \
    captured_obj, \
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(expr), \
    WG_AUTOSIMULATOR_DETAIL_ENCODEDTYPEOF(expr)).is_rvalue()

#define WG_AUTOSIMULATOR_DETAIL_AUTOANY_AUTOANYIMPL_VALUE_IMPL(obj) \
  obj.value()

#define WG_AUTOSIMULATOR_DETAIL_AUTOANY_AUTOANYIMPL_ISRVALUE_IMPL(obj) \
  obj.is_rvalue()

namespace wg
{
namespace autosimulator
{
namespace detail
{

//------------------------------------
//dfta_traits
//  Deduced Template Function Argument
//------------------------------------

template
<
  typename ExprCategory,
  typename NonRefExprType,
  typename IsExprConst
>
struct dfta_traits
{
  typedef BOOST_DEDUCED_TYPENAME
    encoded_type<NonRefExprType, IsExprConst>::non_ref_type
      captured_expr_type;
  typedef auto_any_impl<ExprCategory, captured_expr_type> auto_any_impl_type;
};

//-----------------------
//dfta_auto_any_impl_type
//-----------------------

template
<
  typename ExprCategory,
  typename NonConstNonRefExprType,
  typename IsExprConst
>
inline BOOST_DEDUCED_TYPENAME
dfta_traits
<
  ExprCategory,
  NonConstNonRefExprType,
  IsExprConst
>::auto_any_impl_type *
  dfta_auto_any_impl_type(
    ExprCategory,
    encoded_type<NonConstNonRefExprType, IsExprConst> *)
{
  return 0;
}

//------------------
//auto_any_impl_cast
//------------------

template
<
  typename ExprCategory,
  typename NonConstNonRefExprType,
  typename IsExprConst
>
inline BOOST_DEDUCED_TYPENAME
  dfta_traits
  <
    ExprCategory,
    NonConstNonRefExprType,
    IsExprConst
  >::auto_any_impl_type const &
    auto_any_impl_cast(
      auto_any const & opaqued_obj,
      ExprCategory,
      encoded_type<NonConstNonRefExprType, IsExprConst> *)
{
  typedef BOOST_DEDUCED_TYPENAME
    dfta_traits
    <
      ExprCategory,
      NonConstNonRefExprType,
      IsExprConst
    >::auto_any_impl_type
      auto_any_impl_type;

  return static_cast<auto_any_impl_type const &>(opaqued_obj);
}

}
}
}

#endif /* WG_AUTOSIMULATOR_DETAIL_AUTOANY_HH_ */
