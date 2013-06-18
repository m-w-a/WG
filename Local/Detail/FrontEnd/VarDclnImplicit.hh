#ifndef WG_PP_VARDCLNIMPLICIT_HH_
#define WG_PP_VARDCLNIMPLICIT_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/Keywords.hh>
#include <WG/Local/Detail/PP.hh>
#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_pointer.hpp>

//###########
//Public APIs
//###########

// Expands to the following:
//   (parsed-deduced-type) (var-name)
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_1ARG(implicitvardcln) \
  WG_PP_VARDCLNIMPLICIT_TUPLIZE(implicitvardcln, 0, BOOST_PP_NIL)

// Expands to the following:
//   (parsed-deduced-type) (var-name)
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_2ARG(implicitvardcln, valueexpr) \
  WG_PP_VARDCLNIMPLICIT_TUPLIZE(implicitvardcln, 1, valueexpr)
  
//###########
//Impl Macros
//###########

// Need to use these instead of BOOST_PP_EXPAND because for some reason the 
//  latter prevents the macro expansion of BOOST_PP_EXPANDs in these macros.
#define WG_PP_VARDCLNIMPLICIT_EXPAND1(x) x
#define WG_PP_VARDCLNIMPLICIT_EXPAND2(x) x

#define WG_PP_VARDCLNIMPLICIT_TUPLIZE( \
  implicitvardcln, hasvalueexpr, valueexpr) \
    WG_PP_VARDCLNIMPLICIT_EXPAND1( \
      WG_PP_VARDCLNIMPLICIT_TUPLIZE2 \
      BOOST_PP_IIF( \
        WG_PP_TOKENS_STARTWITH_CONST(implicitvardcln), \
        ( 1, WG_PP_TOKENS_EAT_HEADKEYWORD(implicitvardcln), hasvalueexpr, valueexpr ), \
        ( 0, implicitvardcln, hasvalueexpr, valueexpr ) ))

#define WG_PP_VARDCLNIMPLICIT_TUPLIZE2( \
  addconst, implicitvardcln, hasvalueexpr, valueexpr) \
    WG_PP_VARDCLNIMPLICIT_EXPAND2( \
      BOOST_PP_IIF( \
        BOOST_PP_NOT(hasvalueexpr), \
        WG_PP_VARDCLNIMPLICIT_TUPLIZE_BOUND, \
        WG_PP_VARDCLNIMPLICIT_TUPLIZE_SET) \
      BOOST_PP_LPAREN() \
        addconst BOOST_PP_COMMA() \
        BOOST_PP_SEQ_ENUM( \
          BOOST_PP_IIF( \
            WG_PP_TOKENS_STARTWITH_REF(implicitvardcln), \
            (1)  ( WG_PP_TOKENS_EAT_HEADKEYWORD(implicitvardcln) ), \
            (0) ( implicitvardcln ) ) \
          BOOST_PP_EXPR_IIF( \
            hasvalueexpr, \
            ( valueexpr ) )) \
      BOOST_PP_RPAREN() )

#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_SET(addconst, addref, var, valueexpr) \
  ( \
    BOOST_PP_CAT( \
      WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_, \
      BOOST_PP_CAT(addconst, addref) ) (valueexpr) \
  ) \
  (var)

#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_BOUND( \
  addconst, addref, var) \
    ( \
      BOOST_PP_CAT( \
        BOOST_PP_IIF( \
          WG_PP_TOKENS_STARTWITH_THISU(var), \
          WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_THISU_, \
          WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_), \
        BOOST_PP_CAT(addconst, addref) ) (var) \
    ) \
    (var)

#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_00(expr) \
  WG_PP_DEDUCEDTYPE BOOST_TYPEOF(expr)
#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_01(expr) \
  WG_PP_DEDUCEDTYPE boost::add_reference< BOOST_TYPEOF(expr) >::type
#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_10(expr) \
  WG_PP_DEDUCEDTYPE boost::add_const< BOOST_TYPEOF(expr) >::type
#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_11(expr) \
  WG_PP_DEDUCEDTYPE \
    boost::add_reference<boost::add_const< BOOST_TYPEOF(expr) >::type>::type

#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_THISU_00(bvar) \
  WG_PP_DEDUCEDTYPE BOOST_TYPEOF(this)
#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_THISU_01(bvar) \
  WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_THISU_ERRMSG()
#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_THISU_10(bvar) \
  WG_PP_DEDUCEDTYPE \
    boost::add_const< \
      boost::add_pointer< \
        boost::add_const< \
          BOOST_TYPEOF(*this) >::type >::type >::type
#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_THISU_11(bvar) \
  WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_THISU_ERRMSG()

#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_THISU_ERRMSG() \
  BOOST_PP_ASSERT_MSG( \
    0, \
    "ERROR: ref keyword cannot be used in conjunction with this_ keyword.")

#endif //WG_PP_VARDCLNIMPLICIT_HH_
