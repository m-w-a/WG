#ifndef WG_PP_SPLITHEADFROMTOKENS_HH_
#define WG_PP_SPLITHEADFROMTOKENS_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>

//###########
//Public APIs
//###########

// delimiter: an no-arg object macro that will be invoked between the split head
//  and the transform of the rest of the tokens.
#define WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLEFROMTOKENS( \
  tuplearity, spec, delimiter, nexttransform) \
    WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLEFROMTOKENS_IMPL1( \
      tuplearity, \
      spec, \
      delimiter, \
      nexttransform)

// spec: tokens prefixed by a sequence of same arity tuples followed by a non-tuple.
#define WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS( \
  tuplearity, spec, delimiter, nexttransform) \
     WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_IMPL1( \
        tuplearity, \
        spec, \
        delimiter, \
        nexttransform)

//###########
//Impl Macros
//###########

#define WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLEFROMTOKENS_IMPL1( \
  tuplearity, spec, delimiter, nexttransform) \
    BOOST_PP_EXPAND( \
      WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLEFROMTOKENS_PROCESSSPLIT \
        BOOST_PP_EXPAND( \
          BOOST_PP_LPAREN() \
            BOOST_PP_CAT( \
              WG_PP_ADDCOMMAAFTERTUPLE_, tuplearity) spec BOOST_PP_COMMA() \
            delimiter BOOST_PP_COMMA() \
            nexttransform \
          BOOST_PP_RPAREN() ))

#define WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_IMPL1( \
  tuplearity, spec, delimiter, nexttransform) \
    BOOST_PP_EXPAND( \
      WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_IMPL2 \
      BOOST_PP_WHILE( \
        WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_PRED, \
        WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_OP, \
        WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_INITSTATE( \
          tuplearity, spec, delimiter, nexttransform)) \
    )

#define WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_IMPL2( \
  tuplearity, prefixedhead, rest, delimiter, transform) \
    WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLEFROMTOKENS_PROCESSSPLIT( \
      BOOST_PP_CAT(WG_PP_OBJECT_, prefixedhead), \
      rest, \
      delimiter, \
      transform)
    
#define WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLEFROMTOKENS_PROCESSSPLIT( \
  head, rest, delimiter, nexttransform) \
    head delimiter() \
    nexttransform \
    BOOST_PP_LPAREN() rest BOOST_PP_RPAREN()

#define WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_INITSTATE( \
  tuplearity, spec, delimiter, nexttransform) \
    ( \
      tuplearity, \
      EMPTY, \
      spec, \
      delimiter, \
      nexttransform \
    )
    
#define WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_STATEELEM( \
  indx, state) \
    BOOST_PP_TUPLE_ELEM(5, indx, state)
#define WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_ARITY( \
  state) \
    WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_STATEELEM( \
      0, state)
#define WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_HEAD( \
  state) \
    WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_STATEELEM( \
      1, state)
#define WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_REST( \
  state) \
    WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_STATEELEM( \
      2, state)

#define WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_PRED( \
  d, state) \
    WG_PP_ISNEXTTOKEN_A_TUPLE( \
      WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_ARITY(state), \
      WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_REST(state))


#define WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_OP( \
  d, state) \
    ( \
      WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_ARITY(state), \
      \
      WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_HEAD(state) \
      WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLEFROMTOKENS( \
        WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_ARITY(state),  \
        WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_REST(state), \
        BOOST_PP_EMPTY, \
        BOOST_PP_TUPLE_EAT(1)), \
      \
      BOOST_PP_EXPAND( \
        BOOST_PP_TUPLE_EAT( \
          WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_ARITY( \
            state)) \
      WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_REST(state)), \
      \
      WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_STATEELEM( \
        3, state), \
      \
      WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_STATEELEM( \
        4, state) \
    )

/* Debug Aid.
#define S1 (a) foo
#define S2 (a)(b)(c) foo
#define S3 (a,b) foo
#define S4 (a,b)(c,d) foo

#define next(z) z

WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLEFROMTOKENS(1, S1, BOOST_PP_COMMA, next)
WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLEFROMTOKENS(2, S3, BOOST_PP_COMMA, next)

WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS(1, S2, BOOST_PP_COMMA, next)
WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLESEQFROMTOKENS(2, S4, BOOST_PP_COMMA, next)
*/
    
#endif /* WG_PP_SPLITHEADFROMTOKENS_HH_ */
