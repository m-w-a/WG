#ifndef WG_PP_PP_HH_
#define WG_PP_PP_HH_

#include <boost/preprocessor.hpp>
#include <boost/local_function/detail/preprocessor/keyword/facility/is.hpp>

//###########
//Public APIs
//###########

#define WG_PP_NOTHING

#define WG_PP_TOKENS_START_WITH_WG_PP_TRUE(tokens) \
  WG_PP_TOKENS_START_WITH_WG_PP_TRUE_IMPL(tokens)

#define WG_PP_TOKENS_START_WITH_BOOST_PP_NIL(tokens) \
  WG_PP_TOKENS_START_WITH_BOOST_PP_NIL_IMPL(tokens)

#define WG_PP_TOKENS_START_WITH_WG_PP_DEDUCEDTYPE(tokens) \
  WG_PP_TOKENS_START_WITH_WG_PP_DEDUCEDTYPE_IMPL(tokens)

#define WG_PP_TOKENS_EATHEADTOKEN_WG_PP_DEDUCEDTYPE(tokens) \
  WG_PP_TOKENS_EATHEADTOKEN_WG_PP_DEDUCEDTYPE_IMPL(tokens)

#define WG_PP_IDENTITY(x) x
#define WG_PP_IDENTITY_1(x) WG_PP_IDENTITY(x)
#define WG_PP_IDENTITY_2(x, y) x y
#define WG_PP_IDENTITY_3(x, y, z) x y z

#define WG_PP_TUPLIZE(x) (x)
#define WG_PP_TUPLIZE_1(x) WG_PP_TUPLIZE(x)
#define WG_PP_TUPLIZE_2(x, y) (x, y)

#define WG_PP_1TUPLIZE(x) (x)
#define WG_PP_1TUPLIZE_1(x) WG_PP_1TUPLIZE(x)
#define WG_PP_1TUPLIZE_2(x, y) (x)(y)

// tokens:
//   A sequence of tokens whose head token is either a tuple of arity
//   tuplearity, or not a tuple.
#define WG_PP_ISNEXTTOKEN_A_TUPLE(tuplearity, tokens) \
  WG_PP_ISNEXTTOKEN_A_TUPLE_IMPL(tuplearity, tokens)

// Usage: BOOST_PP_EXPAND(WG_PP_ADDCOMMAAFTERTUPLE_# some-tuple-token)
#define WG_PP_ADDCOMMAAFTERTUPLE_1(x) (x) BOOST_PP_COMMA()
#define WG_PP_ADDCOMMAAFTERTUPLE_2(x, y) (x, y) BOOST_PP_COMMA()

#define WG_PP_MAP_TO_TRUETOKEN_ARG1(x) \
  WG_PP_TRUE
#define WG_PP_MAP_TO_TRUETOKEN_ARG2(x, y) \
  WG_PP_TRUE

#define WG_PP_MAP_TO_0_ARG1(x) 0
#define WG_PP_MAP_TO_1_ARG1(x) 1

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

#define WG_PP_TOKEN_MATCHES_WG_PP_TRUE_WG_PP_TRUE (1) /* unary */
#define WG_PP_TOKENS_START_WITH_WG_PP_TRUE_IMPL(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_TOKEN_MATCHES_WG_PP_TRUE_)

#define WG_PP_TOKEN_MATCHES_BOOST_PP_NIL_BOOST_PP_NIL (1) /* unary */
#define WG_PP_TOKENS_START_WITH_BOOST_PP_NIL_IMPL(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_TOKEN_MATCHES_BOOST_PP_NIL_)

#define WG_PP_TOKEN_MATCHES_WG_PP_DEDUCEDTYPE_WG_PP_DEDUCEDTYPE (1) /* unary */
#define WG_PP_TOKENS_START_WITH_WG_PP_DEDUCEDTYPE_IMPL(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_TOKEN_MATCHES_WG_PP_DEDUCEDTYPE_)

#define WG_PP_TOKENS_MAPTONOTHING_WG_PP_DEDUCEDTYPE
#define WG_PP_TOKENS_EATHEADTOKEN_WG_PP_DEDUCEDTYPE_IMPL(tokens) \
  BOOST_PP_CAT(WG_PP_TOKENS_MAPTONOTHING_, tokens)

#define WG_PP_ISNEXTTOKEN_A_TUPLE_IMPL(tuplearity, tokens) \
  WG_PP_TOKENS_START_WITH_WG_PP_TRUE( \
    BOOST_PP_CAT(WG_PP_MAP_TO_TRUETOKEN_ARG, tuplearity) tokens)

#endif /* WG_PP_PP_HH_ */
