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
#define WG_PP_SETVARDCLNNORMALIZE(typevardcln, valueexpr) \
  WG_PP_TYPEVARDCLN_NORMALIZE_IMPL(typevardcln, valueexpr) \
  WG_PP_TUPLIZE(valueexpr)

//###########
//Impl Macros
//###########

#define WG_PP_TYPEVARDCLN_NORMALIZE_EXPAND1(x) x

#define WG_PP_TYPEVARDCLN_NORMALIZE_IMPL(typevardcln, valueexpr) \
  WG_PP_TYPEVARDCLN_NORMALIZE_EXPAND1( \
    BOOST_PP_IIF( \
      WG_PP_VARDCLN_ISEXPLICIT(typevardcln), \
      WG_PP_VARDCLNEXPLICIT_TUPLIZE, \
      WG_PP_VARDCLNIMPLICIT_TUPLIZE_2ARG) \
    BOOST_PP_IIF( \
      WG_PP_VARDCLN_ISEXPLICIT(typevardcln), \
      (typevardcln), \
      (typevardcln, valueexpr) ))

/*
//Unit Tests.
#define S1 ( (T const * ) var1 , &this->m_Foo )
#define S2 ( local(U) var2 , catInTheHat )
#define S3 ( local(U *) ref var3 , mouse << in << the << hole )

#include <boost/preprocessor/expand.hpp>

BOOST_PP_EXPAND(WG_PP_SETVARDCLNNORMALIZE S1)
BOOST_PP_EXPAND(WG_PP_SETVARDCLNNORMALIZE S2)
BOOST_PP_EXPAND(WG_PP_SETVARDCLNNORMALIZE S3)

//EXPECTED:
//(T const *) (var1) (&this->m_Foo)
//(local(U)) ( var2 ) (catInTheHat)
//(local(U *) (ref)) ( var3 ) (mouse << in << the << hole)
*/

#endif //WG_PP_SETVARDCLNNORMALIZE_HH_
