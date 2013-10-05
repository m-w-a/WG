#ifndef WG_LOCAL_DETAIL_PP_PP_HH_
#define WG_LOCAL_DETAIL_PP_PP_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/TokenMatching.hh>

//###########
//Public APIs
//###########

// An object-like macro alternative to BOOST_PP_EMPTY.
// So one doesn't have to deal with the hassle of appending "()".
#define WG_PP_NOTHING

#define WG_PP_STARTSWITH_WG_PP_TRUE(tokens) \
  WG_PP_STARTSWITH_WG_PP_TRUE_IMPL(tokens)

#define WG_PP_STARTSWITH_BOOST_PP_NIL(tokens) \
  WG_PP_STARTSWITH_BOOST_PP_NIL_IMPL(tokens)
#define WG_PP_MATCHES_BOOST_PP_NIL(tokens) \
  WG_PP_MATCHES_BOOST_PP_NIL_IMPL(tokens)

#define WG_PP_EATHEADTOKEN_BOOST_PP_NIL(tokens) \
  WG_PP_EATHEADTOKEN_BOOST_PP_NIL_IMPL(tokens)
#define WG_PP_EATTAILTOKEN_BOOST_PP_NIL(tokens) \
  WG_PP_EATTAILTOKEN_BOOST_PP_NIL_IMPL(tokens)

// condition:
//   A 1-arg function macro that will be applied to arg and returns 0 or 1.
// truetransform:
//   A 1-arg function macro that will be applied to arg if condition(arg)
//   evaluated to 1.
// falsetransform:
//   A 1-arg function macro that will be applied to arg if condition(arg)
//   evaluated to 0.
#define WG_PP_CACHED_IIF(arg, condition, truetransform, falsetransform) \
  WG_PP_CACHED_IIF_IMPL(arg, condition, truetransform, falsetransform)

#define WG_PP_MAPTO_NOTHING_ARG1(x)
#define WG_PP_MAPTO_NOTHING_ARG2(a, b)
#define WG_PP_MAPTO_NOTHING_ARG3(a, b, c)
#define WG_PP_MAPTO_NOTHING_ARG4(a, b, c, d)

#define WG_PP_MAP_TO_WG_PP_TRUE_ARG1(x) WG_PP_TRUE
#define WG_PP_MAP_TO_WG_PP_TRUE_ARG2(x, y) WG_PP_TRUE

#define WG_PP_MAP_TO_0_ARG1(x) 0
#define WG_PP_MAP_TO_1_ARG1(x) 1

#define WG_PP_IDENTITY_ARG1(x) x
#define WG_PP_IDENTITY_ARG2(x, y) x y
#define WG_PP_IDENTITY_ARG3(x, y, z) x y z

#define WG_PP_TUPLIZE_ARG1(x) (x)
#define WG_PP_TUPLIZE_ARG2(x, y) (x, y)

#define WG_PP_ONETUPLIZE_ARG1(x) (x)
#define WG_PP_ONETUPLIZE_ARG2(x, y) (x)(y)

#define WG_PP_CAT_ARG3(a, b, c) \
  BOOST_PP_CAT(BOOST_PP_CAT(a, b), c)

#define WG_PP_CAT_ARG4(a, b, c, d) \
  BOOST_PP_CAT(WG_PP_CAT_ARG3(a, b, c), d)

#define WG_PP_CAT_ARG5(a, b, c, d, e) \
  BOOST_PP_CAT(WG_PP_CAT_ARG4(a, b, c, d), e)

// Expands to <a>_<b>
// Therefore a should not end in an underscore nor should b start with one.
#define WG_PP_UCAT_ARG2(a, b) \
  WG_PP_CAT_ARG3(a, _, b)

// Expands to <a>_<b>_<c>
// a: should not end in an underscore.
// b: should not begin or end in an underscore.
// c: should not begin with an underscore.
#define WG_PP_UCAT_ARG3(a, b, c) \
  WG_PP_UCAT_ARG2(WG_PP_UCAT_ARG2(a,b), c)

// tokens:
//   A sequence of tokens whose head token is either a tuple of arity
//   tuplearity, or not a tuple.
#define WG_PP_ISNEXTTOKEN_A_TUPLE(tuplearity, tokens) \
  WG_PP_ISNEXTTOKEN_A_TUPLE_IMPL(tuplearity, tokens)

// Usage: BOOST_PP_EXPAND(WG_PP_ADDCOMMA_AFTERTUPLE_ARG##arity some-tuple-token)
#define WG_PP_ADDCOMMA_AFTERTUPLE_ARITY1(x) (x) BOOST_PP_COMMA()
#define WG_PP_ADDCOMMA_AFTERTUPLE_ARITY2(x, y) (x, y) BOOST_PP_COMMA()

#define WG_PP_IS_ODD(num) BOOST_PP_MOD(num,2)
#define WG_PP_IS_EVEN(num) \
  BOOST_PP_NOT(WG_PP_IS_ODD(num))

#define WG_PP_IS_MOD3_R0(num) \
  BOOST_PP_EQUAL(BOOST_PP_MOD(num,3), 0)
#define WG_PP_IS_MOD3_R1(num) \
  BOOST_PP_EQUAL(BOOST_PP_MOD(num,3), 1)
#define WG_PP_IS_MOD3_R2(num) \
  BOOST_PP_EQUAL(BOOST_PP_MOD(num,3), 2)

//###########
//Impl Macros
//###########

#define WG_PP_TOKENMATCH_BEGINSWITH_WG_PP_TRUE_WG_PP_TRUE WG_PP_TOKENMATCH_FRONTMATCH
#define WG_PP_STARTSWITH_WG_PP_TRUE_IMPL(tokens) \
  WG_PP_TOKENMATCH_BEGINSWITH(\
    tokens, \
    WG_PP_TOKENMATCH_BEGINSWITH_WG_PP_TRUE_)

#define WG_PP_TOKENMATCH_BEGINSWITH_BOOST_PP_NIL_BOOST_PP_NIL WG_PP_TOKENMATCH_FRONTMATCH
#define WG_PP_STARTSWITH_BOOST_PP_NIL_IMPL(tokens) \
  WG_PP_TOKENMATCH_BEGINSWITH(\
    tokens, \
    WG_PP_TOKENMATCH_BEGINSWITH_BOOST_PP_NIL_)

#define WG_PP_TOKENMATCH_MATCHES_BOOST_PP_NIL_BOOST_PP_NIL WG_PP_TOKENMATCH_EXACTMATCH
#define WG_PP_MATCHES_BOOST_PP_NIL_IMPL(tokens) \
  WG_PP_TOKENMATCH_MATCHES( \
    tokens, \
    WG_PP_TOKENMATCH_MATCHES_BOOST_PP_NIL_)

#define WG_PP_MAPTONOTHING_BOOST_PP_NIL_BOOST_PP_NIL
#define WG_PP_EATHEADTOKEN_BOOST_PP_NIL_IMPL(tokens) \
  BOOST_PP_CAT(WG_PP_MAPTONOTHING_BOOST_PP_NIL_, tokens)

#define BOOST_PP_NIL_BOOST_PP_NIL_WG_PP_MAPTONOTHING
#define WG_PP_EATTAILTOKEN_BOOST_PP_NIL_IMPL(tokens) \
  BOOST_PP_CAT(tokens, _BOOST_PP_NIL_WG_PP_MAPTONOTHING)

#define WG_PP_CACHED_IIF_IMPL(arg, condition, truetransform, falsetransform) \
  BOOST_PP_IIF( \
    condition(arg), \
    truetransform, \
    falsetransform) (arg)

#define WG_PP_ISNEXTTOKEN_A_TUPLE_IMPL(tuplearity, tokens) \
  WG_PP_STARTSWITH_WG_PP_TRUE( \
    BOOST_PP_CAT(WG_PP_MAP_TO_WG_PP_TRUE_ARG, tuplearity) tokens)

#endif /* WG_LOCAL_DETAIL_PP_PP_HH_ */
