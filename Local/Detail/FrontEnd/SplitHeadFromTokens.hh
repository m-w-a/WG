#ifndef WG_PP_SPLITHEADFROMTOKENS_HH_
#define WG_PP_SPLITHEADFROMTOKENS_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>

//###########
//Public APIs
//###########

#define WG_PP_SPLITHEADTUPLEFROMTOKENS( \
  tuplearity, spec, headtransform, nexttransform) \
    WG_PP_SPLITHEADTUPLEFROMTOKENS_IMPL1( \
      tuplearity, \
      spec, \
      headtransform, \
      nexttransform)

// spec: tokens prefixed by a sequence of same arity tuples followed by a non-tuple.
#define WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
  tuplearity, spec, headtransform, nexttransform) \
     WG_PP_SPLITHEADTUPLESEQFROMTOKENS_IMPL1( \
        tuplearity, \
        spec, \
        headtransform, \
        nexttransform)

//###########
//Impl Macros
//###########

#define WG_PP_SPLITHEADTUPLEFROMTOKENS_IMPL1( \
  tuplearity, spec, headtransform, nexttransform) \
    BOOST_PP_EXPAND( \
      WG_PP_SPLITHEADTUPLEFROMTOKENS_PROCESSSPLIT \
        BOOST_PP_EXPAND( \
          BOOST_PP_LPAREN() \
            BOOST_PP_CAT( \
              WG_PP_ADDCOMMAAFTERTUPLE_, tuplearity) spec BOOST_PP_COMMA() \
            headtransform BOOST_PP_COMMA() \
            nexttransform \
          BOOST_PP_RPAREN() ))

#define WG_PP_SPLITHEADTUPLESEQFROMTOKENS_IMPL1( \
  tuplearity, spec, headtransform, nexttransform) \
    BOOST_PP_EXPAND( \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS_IMPL2 \
      BOOST_PP_WHILE( \
        WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_PRED, \
        WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_OP, \
        WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_INITSTATE( \
          tuplearity, spec, headtransform, nexttransform)) \
    )

#define WG_PP_SPLITHEADTUPLESEQFROMTOKENS_IMPL2( \
  tuplearity, prefixedhead, rest, headtransform, nexttransform) \
    WG_PP_SPLITHEADTUPLEFROMTOKENS_PROCESSSPLIT( \
      BOOST_PP_CAT(WG_PP_OBJECT_, prefixedhead), \
      rest, \
      headtransform, \
      nexttransform)
    
#define WG_PP_SPLITHEADTUPLEFROMTOKENS_PROCESSSPLIT( \
  head, rest, headtransform, nexttransform) \
    headtransform(head) \
    nexttransform(rest)

#define WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_INITSTATE( \
  tuplearity, spec, headtransform, nexttransform) \
    ( \
      tuplearity, \
      EMPTY, \
      spec, \
      headtransform, \
      nexttransform \
    )
    
#define WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_STATEELEM( \
  indx, state) \
    BOOST_PP_TUPLE_ELEM(5, indx, state)
#define WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_ARITY( \
  state) \
    WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_STATEELEM( \
      0, state)
#define WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_HEAD( \
  state) \
    WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_STATEELEM( \
      1, state)
#define WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_REST( \
  state) \
    WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_STATEELEM( \
      2, state)

#define WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_PRED( \
  d, state) \
    WG_PP_ISNEXTTOKEN_A_TUPLE( \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_ARITY(state), \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_REST(state))


#define WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_OP( \
  d, state) \
    ( \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_ARITY(state), \
      \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_HEAD(state) \
      WG_PP_SPLITHEADTUPLEFROMTOKENS( \
        WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_ARITY(state),  \
        WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_REST(state), \
        WG_PP_IDENTITY, \
        BOOST_PP_TUPLE_EAT(1)), \
      \
      BOOST_PP_EXPAND( \
        BOOST_PP_TUPLE_EAT( \
          WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_ARITY( \
            state)) \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_REST(state)), \
      \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_STATEELEM( \
        3, state), \
      \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_STATEELEM( \
        4, state) \
    )

/*
// Debug Aid.
#define S1 (a) foo
#define S2 (a)(b)(c) foo
#define S3 (a,b) foo
#define S4 (a,b)(c,d) foo

#define head(x) x ,
#define next(z) z

WG_PP_SPLITHEADTUPLEFROMTOKENS(1, S1, head, next)
WG_PP_SPLITHEADTUPLEFROMTOKENS(2, S3, head, next)

WG_PP_SPLITHEADTUPLESEQFROMTOKENS(1, S2, head, next)
WG_PP_SPLITHEADTUPLESEQFROMTOKENS(2, S4, head, next)

//EXPECTED:
//(a) , foo
//(a,b) , foo
//(a)(b)(c) , foo
//(a,b)(c,d) , foo
*/
    
#endif /* WG_PP_SPLITHEADFROMTOKENS_HH_ */
