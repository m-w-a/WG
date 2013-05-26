#ifndef WG_PP_SPLITHEADFROMTOKENS_HH_
#define WG_PP_SPLITHEADFROMTOKENS_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>

//###########
//Public APIs
//###########

// spec:
//   a sequence of tokens prefixed by a tuple of arity "tuplearity", followed by
//   at least another token.
// headtransform:
//   a 1-arg function macro to apply to the split head.
// headelemtransform:
//   a "tuplearity"-arg function macro to apply to the head tuple that was split.
// nexttransform:
//   a 1-arg function macro to apply to the rest of spec after the split
#define WG_PP_SPLITHEADTUPLEFROMTOKENS( \
  tuplearity, spec, headelemtransform, headtransform, nexttransform) \
    WG_PP_SPLITHEADTUPLEFROMTOKENS_IMPL1( \
      tuplearity, \
      spec, \
      headelemtransform, \
      headtransform, \
      nexttransform)

// spec: 
//   a sequence of tokens prefixed by some number of tuples of the same 
//   "tuplearity" arity, followed by a non-tuple.
//   a 1-arg function macro to apply to the split head.
// headelemtransform:
//   a "tuplearity"-arg function macro to apply to the head tuple that was split.
// nexttransform:
//   a 1-arg function macro to apply to the rest of spec after the split
#define WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
  tuplearity, spec, headelemtransform, headtransform, nexttransform) \
     WG_PP_SPLITHEADTUPLESEQFROMTOKENS_IMPL1( \
        tuplearity, \
        spec, \
        headelemtransform, \
        headtransform, \
        nexttransform)

//###########
//Impl Macros
//###########

// Work Around.
// Needed because using BOOST_PP_EXPAND on the public APIs will disable 
//   BOOST_PP_EXPAND internally.
#define WG_PP_SPLITHEADTUPLEFROMTOKENS_EXPAND1(x) x
#define WG_PP_SPLITHEADTUPLEFROMTOKENS_EXPAND2(x) x
#define WG_PP_SPLITHEADTUPLEFROMTOKENS_EXPAND3(x) x
#define WG_PP_SPLITHEADTUPLEFROMTOKENS_EXPAND4(x) x

#define WG_PP_SPLITHEADTUPLEFROMTOKENS_IMPL1( \
  tuplearity, spec, headelemtransform, headtransform, nexttransform) \
    WG_PP_SPLITHEADTUPLEFROMTOKENS_EXPAND1( \
      WG_PP_SPLITHEADTUPLEFROMTOKENS_IMPL2 \
        WG_PP_SPLITHEADTUPLEFROMTOKENS_EXPAND2( \
          BOOST_PP_LPAREN() \
            BOOST_PP_CAT( \
              WG_PP_ADDCOMMAAFTERTUPLE_, tuplearity) spec BOOST_PP_COMMA() \
            headelemtransform BOOST_PP_COMMA() \
            headtransform BOOST_PP_COMMA() \
            nexttransform \
          BOOST_PP_RPAREN() ))

#define WG_PP_SPLITHEADTUPLEFROMTOKENS_IMPL2( \
  head, rest, headelemtransform, headtransform, nexttransform) \
    WG_PP_SPLITHEADTUPLEFROMTOKENS_PROCESSSPLIT( \
      headelemtransform head, \
      rest, \
      headtransform, \
      nexttransform)

#define WG_PP_SPLITHEADTUPLESEQFROMTOKENS_IMPL1( \
  tuplearity, spec, headelemtransform, headtransform, nexttransform) \
    WG_PP_SPLITHEADTUPLEFROMTOKENS_EXPAND3( \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS_IMPL2 \
      BOOST_PP_WHILE( \
        WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_PRED, \
        WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_OP, \
        WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_INITSTATE( \
          tuplearity, spec, headelemtransform, headtransform, nexttransform)) \
    )

#define WG_PP_SPLITHEADTUPLESEQFROMTOKENS_IMPL2( \
  tuplearity, \
  prefixedhead, \
  rest, \
  headelemtransform, \
  headtransform, \
  nexttransform) \
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
  tuplearity, spec, headelemtransform, headtransform, nexttransform) \
    ( \
      tuplearity, \
      EMPTY, \
      spec, \
      headelemtransform, \
      headtransform, \
      nexttransform \
    )
    
#define WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_STATEELEM(indx, state) \
  BOOST_PP_TUPLE_ELEM(6, indx, state)
#define WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_ARITY(state) \
  WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_STATEELEM( \
    0, state)
#define WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_HEAD(state) \
  WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_STATEELEM( \
    1, state)
#define WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_REST(state) \
  WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_STATEELEM( \
    2, state)
#define WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_HEADELEMTRANSFORM(state) \
  WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_STATEELEM( \
    3, state)

#define WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_PRED( \
  d, state) \
    WG_PP_ISNEXTTOKEN_A_TUPLE( \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_ARITY(state), \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_REST(state))


#define WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_OP( \
  d, state) \
    ( \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_ARITY(state) \
      ,\
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_HEAD(state) \
      WG_PP_SPLITHEADTUPLEFROMTOKENS( \
        WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_ARITY(state),  \
        WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_REST(state), \
        WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_HEADELEMTRANSFORM(state), \
        WG_PP_IDENTITY, \
        BOOST_PP_TUPLE_EAT(1)) \
      ,\
      WG_PP_SPLITHEADTUPLEFROMTOKENS_EXPAND4( \
        BOOST_PP_TUPLE_EAT( \
          WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_ARITY( \
            state)) \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_REST(state)) \
      ,\
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_STATEELEM( \
        3, state) \
      ,\
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_STATEELEM( \
        4, state) \
      , \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS_WHILELOOP_STATEELEM( \
        5, state) \
    )

/*
// Debug Aid.
#define S1 (a) foo
#define S2 (a)(b)(c) foo
#define S3 (a,b) foo
#define S4 (a,b)(c,d) foo

#define quoteelem_1(x) (~x~)
#define quoteelem_2(x, y) (~x~, +y+)
#define head(x) x ,
#define next(z) z

WG_PP_SPLITHEADTUPLEFROMTOKENS(1, S1, WG_PP_TUPLIZE_1, head, next)
WG_PP_SPLITHEADTUPLEFROMTOKENS(2, S3, WG_PP_TUPLIZE_2, head, next)

WG_PP_SPLITHEADTUPLESEQFROMTOKENS(1, S2, quoteelem_1, head, next)
WG_PP_SPLITHEADTUPLESEQFROMTOKENS(2, S4, quoteelem_2, head, next)

//EXPECTED:
//(a) , foo
//(a, b) , foo
//(~a~) (~b~) (~c~) , foo
//(~a~, +b+) (~c~, +d+) , foo
*/
    
#endif /* WG_PP_SPLITHEADFROMTOKENS_HH_ */
