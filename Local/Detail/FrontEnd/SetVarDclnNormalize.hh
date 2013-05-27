#ifndef WG_PP_SETVARDCLNNORMALIZE_HH_
#define WG_PP_SETVARDCLNNORMALIZE_HH_

#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/FrontEnd/VarDclnExplicit.hh>

//###########
//Public APIs
//###########

// Expands to the following:
//   {(explicit-type) (var-name) (value-expr)}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_SETVARDCLNNORMALIZE(explicittypedvardcln, valueexpr) \
  WG_PP_VARDCLNEXPLICIT_TUPLIZE(explicittypedvardcln) \
  WG_PP_TUPLIZE(valueexpr)

/*
//Unit Tests.
#define S1 ( (T const * ) var1 , &this->m_Foo )
#define S2 ( local(U) var2 , catInTheHat )
#define S3 ( localref(Callback &) var3 , mouse << in << the << hole )

#include <boost/preprocessor/expand.hpp>

BOOST_PP_EXPAND(WG_PP_SETVARDCLNNORMALIZE S1)
BOOST_PP_EXPAND(WG_PP_SETVARDCLNNORMALIZE S2)
BOOST_PP_EXPAND(WG_PP_SETVARDCLNNORMALIZE S3)

//EXPECTED:
//(T const *) (var1) (&this->m_Foo)
//(local(U)) ( var2 ) (catInTheHat)
//(localref(Callback &)) ( var3 ) (mouse << in << the << hole)
*/

#endif //WG_PP_SETVARDCLNNORMALIZE_HH_
