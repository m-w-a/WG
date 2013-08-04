#ifndef WG_PP_SETVARDCLNNORMALIZE_HH_
#define WG_PP_SETVARDCLNNORMALIZE_HH_

#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/FrontEnd/VarDcln.hh>
#include <WG/Local/Detail/FrontEnd/VarDclnExplicit.hh>
#include <WG/Local/Detail/FrontEnd/VarDclnImplicit.hh>

//###########
//Public APIs
//###########

// Expands to the following:
//   {(parsed-explicit-type) (var-name) (value-expr)}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_SETVARDCLN_NORMALIZE(typevardcln, valueexpr) \
  WG_PP_SETVARDCLN_NORMALIZE_IMPL(typevardcln, valueexpr, 0) \
  WG_PP_TUPLIZE(valueexpr)

// Expands to the following:
//   {(parsed-explicit-type) (var-name) (value-expr)}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_SETVARDCLN_NORMALIZE_TPL(typevardcln, valueexpr) \
  WG_PP_SETVARDCLN_NORMALIZE_IMPL(typevardcln, valueexpr, 1) \
  WG_PP_TUPLIZE(valueexpr)

// Expands to the following:
//   {(parsed-explicit-non-local-type) (var-name) (value-expr)}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_SETVARDCLN_NLT_NORMALIZE(typevardcln, valueexpr) \
  WG_PP_SETVARDCLN_NLT_NORMALIZE_IMPL(typevardcln, valueexpr, 0) \
  WG_PP_TUPLIZE(valueexpr)

// Expands to the following:
//   {(parsed-explicit-non-local-type) (var-name) (value-expr)}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_SETVARDCLN_NLT_NORMALIZE_TPL(typevardcln, valueexpr) \
  WG_PP_SETVARDCLN_NLT_NORMALIZE_IMPL(typevardcln, valueexpr, 1) \
  WG_PP_TUPLIZE(valueexpr)

//###########
//Impl Macros
//###########

#define WG_PP_SETVARDCLN_NORMALIZE_EXPAND1(x) x

#define WG_PP_SETVARDCLN_NORMALIZE_IMPL(typevardcln, valueexpr, istpl) \
  WG_PP_SETVARDCLN_NORMALIZE_EXPAND1( \
    BOOST_PP_IIF( \
      WG_PP_VARDCLN_ISEXPLICIT(typevardcln), \
      WG_PP_VARDCLN_EXPLICIT_TUPLIZE, \
      WG_PP_VARDCLN_IMPLICIT_TUPLIZE_2ARG) \
    BOOST_PP_IIF( \
      WG_PP_VARDCLN_ISEXPLICIT(typevardcln), \
      (typevardcln), \
      (typevardcln, valueexpr, istpl) ))

#define WG_PP_SETVARDCLN_NORMALIZE_EXPAND2(x) x

#define WG_PP_SETVARDCLN_NLT_NORMALIZE_IMPL(typevardcln, valueexpr, istpl) \
  WG_PP_SETVARDCLN_NORMALIZE_EXPAND2( \
    BOOST_PP_IIF( \
        WG_PP_VARDCLN_NLT_ISEXPLICIT(typevardcln), \
        WG_PP_VARDCLN_NLT_EXPLICIT_TUPLIZE, \
        WG_PP_VARDCLN_IMPLICIT_TUPLIZE_2ARG) \
      BOOST_PP_IIF( \
        WG_PP_VARDCLN_NLT_ISEXPLICIT(typevardcln), \
        (typevardcln), \
        (typevardcln, valueexpr, istpl) )  )

/*
//Unit Tests.
#define S1 ( (T const * ) var1 , &this->m_Foo )
#define S2 ( local(U) var2 , catInTheHat )
#define S3 ( local(U *) ref var3 , mouse << in << the << hole )

#include <boost/preprocessor/expand.hpp>

BOOST_PP_EXPAND(WG_PP_SETVARDCLN_NORMALIZE S1)
BOOST_PP_EXPAND(WG_PP_SETVARDCLN_NORMALIZE S2)
BOOST_PP_EXPAND(WG_PP_SETVARDCLN_NORMALIZE S3)

//EXPECTED:
//(T const *) (var1) (&this->m_Foo)
//(local(U)) ( var2 ) (catInTheHat)
//(local(U *) (ref)) ( var3 ) (mouse << in << the << hole)
*/

#endif //WG_PP_SETVARDCLNNORMALIZE_HH_
