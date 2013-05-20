#ifndef WG_PP_SPLITHEADFROMTOKENS_HH_
#define WG_PP_SPLITHEADFROMTOKENS_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>

//###########
//Public APIs
//###########

#define WG_PP_AUTOFUNCTION_SPEC_SPLIT1TUPLEHEADFROMTOKENS(spec, nexttransform) \
  WG_PP_AUTOFUNCTION_SPEC_SPLITTUPLEHEADFROMTOKENS_IMPL1( \
    1, \
    spec, \
    nexttransform)

#define WG_PP_AUTOFUNCTION_SPEC_SPLIT2TUPLEHEADFROMTOKENS(spec, nexttransform) \
  WG_PP_AUTOFUNCTION_SPEC_SPLITTUPLEHEADFROMTOKENS_IMPL1( \
    2, \
    spec, \
    nexttransform)

//###########
//Impl Macros
//###########

#define WG_PP_AUTOFUNCTION_SPEC_SPLITTUPLEHEADFROMTOKENS_IMPL1( \
  tuplearity, spec, nexttransform) \
    BOOST_PP_EXPAND( \
      WG_PP_AUTOFUNCTION_SPEC_SPLITTUPLEHEADFROMTOKENS_IMPL2 \
        BOOST_PP_EXPAND( \
          BOOST_PP_LPAREN() \
            BOOST_PP_CAT( \
              WG_PP_ADDCOMMAAFTERTUPLE_, tuplearity) spec BOOST_PP_COMMA() \
            nexttransform \
          BOOST_PP_RPAREN() ))

#define WG_PP_AUTOFUNCTION_SPEC_SPLITTUPLEHEADFROMTOKENS_IMPL2( \
  head, rest, nexttransform) \
    head BOOST_PP_COMMA()\
    nexttransform \
    BOOST_PP_LPAREN() rest BOOST_PP_RPAREN()


#endif /* WG_PP_SPLITHEADFROMTOKENS_HH_ */
