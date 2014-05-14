#ifndef WG_PP_SETVARDCLNNORMALIZE_HH_
#define WG_PP_SETVARDCLNNORMALIZE_HH_

#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/VarDclns/VarDcln.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/VarDclns/VarDclnExplicit.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/VarDclns/VarDclnImplicit.hh>

//###########
//Public APIs
//###########

// typevardcln:
//   set-var-dcln
// Expands to the following:
//   {(explicit-type) (var-name) (value-expr)}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_SETVARDCLN_NORMALIZE(typevardcln, valueexpr) \
  WG_PP_SETVARDCLN_NORMALIZE_IMPL(typevardcln, valueexpr, 0) \
  WG_PP_TUPLIZE_ARG1(valueexpr)

// typevardcln:
//   set-var-dcln
// Expands to the following:
//   {(explicit-type) (var-name) (value-expr)}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_SETVARDCLN_NORMALIZE_TPL(typevardcln, valueexpr) \
  WG_PP_SETVARDCLN_NORMALIZE_IMPL(typevardcln, valueexpr, 1) \
  WG_PP_TUPLIZE_ARG1(valueexpr)

// typevardcln:
//   nlt-set-var-dcln
// Expands to the following:
//   {(explicit-non-local-type) (var-name) (value-expr)}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_SETVARDCLN_NLT_NORMALIZE(typevardcln, valueexpr) \
  WG_PP_SETVARDCLN_NLT_NORMALIZE_IMPL(typevardcln, valueexpr, 0) \
  WG_PP_TUPLIZE_ARG1(valueexpr)

// typevardcln:
//   nlt-set-var-dcln
// Expands to the following:
//   {(explicit-non-local-type) (var-name) (value-expr)}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_SETVARDCLN_NLT_NORMALIZE_TPL(typevardcln, valueexpr) \
  WG_PP_SETVARDCLN_NLT_NORMALIZE_IMPL(typevardcln, valueexpr, 1) \
  WG_PP_TUPLIZE_ARG1(valueexpr)

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
      (typevardcln, istpl), \
      (typevardcln, valueexpr, istpl) ))

#define WG_PP_SETVARDCLN_NORMALIZE_EXPAND2(x) x

#define WG_PP_SETVARDCLN_NLT_NORMALIZE_IMPL(typevardcln, valueexpr, istpl) \
  WG_PP_SETVARDCLN_NORMALIZE_EXPAND2( \
    BOOST_PP_IIF( \
        WG_PP_VARDCLN_ISEXPLICIT_NLT(typevardcln), \
        WG_PP_VARDCLN_EXPLICIT_NLT_TUPLIZE, \
        WG_PP_VARDCLN_IMPLICIT_TUPLIZE_2ARG) \
      BOOST_PP_IIF( \
        WG_PP_VARDCLN_ISEXPLICIT_NLT(typevardcln), \
        (typevardcln, istpl), \
        (typevardcln, valueexpr, istpl) )  )

/*
//Unit Tests.
#define S1 ( type(T const * ) var1 , &this->m_Foo )
#define S2 ( lcltype(U) var2 , catInTheHat )
#define S3 ( lcltype(U *) ref var3 , mouse << in << the << hole )

#include <boost/preprocessor/expand.hpp>

BOOST_PP_EXPAND(WG_PP_SETVARDCLN_NORMALIZE S1)
BOOST_PP_EXPAND(WG_PP_SETVARDCLN_NORMALIZE S2)
BOOST_PP_EXPAND(WG_PP_SETVARDCLN_NORMALIZE S3)

//EXPECTED:
//( type(T const *) ) (var1) (&this->m_Foo)
//( lcltype(U) ) ( var2 ) (catInTheHat)
//( lcltype(U *) (ref) ) ( var3 ) (mouse << in << the << hole)
*/

#endif //WG_PP_SETVARDCLNNORMALIZE_HH_
