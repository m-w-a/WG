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
#define WG_PP_TOKENS_EATHEADTOKEN_BOOST_PP_NIL(tokens) \
  WG_PP_TOKENS_EATHEADTOKEN_BOOST_PP_NIL_IMPL(tokens)
#define WG_PP_TOKENS_EATTAILTOKEN_BOOST_PP_NIL(tokens) \
  WG_PP_TOKENS_EATTAILTOKEN_BOOST_PP_NIL_IMPL(tokens)

#define WG_PP_TOKENS_START_WITH_WG_PP_ERROR(tokens) \
  WG_PP_TOKENS_START_WITH_WG_PP_ERROR_IMPL(tokens)
#define WG_PP_TOKENS_EATHEADTOKEN_WG_PP_ERROR(tokens) \
  WG_PP_TOKENS_EATHEADTOKEN_WG_PP_ERROR_IMPL(tokens)

#define WG_PP_TOKENS_START_WITH_WG_PP_DEDUCEDTYPE(tokens) \
  WG_PP_TOKENS_START_WITH_WG_PP_DEDUCEDTYPE_IMPL(tokens)
#define WG_PP_TOKENS_EATHEADTOKEN_WG_PP_DEDUCEDTYPE(tokens) \
  WG_PP_TOKENS_EATHEADTOKEN_WG_PP_DEDUCEDTYPE_IMPL(tokens)

#define WG_PP_MAP_TO_NOTHING(x)
#define WG_PP_MAP_TO_NOTHING1(x)
#define WG_PP_MAP_TO_NOTHING2(a, b)
#define WG_PP_MAP_TO_NOTHING3(a, b, c)
#define WG_PP_MAP_TO_NOTHING4(a, b, c, d)

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

#define WG_PP_CAT3(a, b, c) \
  BOOST_PP_CAT(BOOST_PP_CAT(a, b), c)

#define WG_PP_CAT4(a, b, c, d) \
  BOOST_PP_CAT(WG_PP_CAT3(a, b, c), d)

#define WG_PP_CAT5(a, b, c, d, e) \
  BOOST_PP_CAT(WG_PP_CAT4(a, b, c, d), e)

// Expands to <base>_<moduleid>_<tail>.
// Therfore neither of base, moduleid, or tail should end with an underscore.
#define WG_PP_INTERFACE_CAT(base, moduleid, tail) \
  WG_PP_CAT5(base, _, moduleid, _, tail)

// Expands to <a>_<b>
// Therefore a should not end in an underscore nor should b start with one.
#define WG_PP_UCAT(a, b) \
  WG_PP_CAT3(a, _, b)

// Expands to <a>_<b>_<c>
// a: should not end in an underscore.
// b: should not begin or end in an underscore.
// c: should not begin with an underscore.
#define WG_PP_UCAT3(a, b, c) \
  WG_PP_UCAT(WG_PP_UCAT(a,b), c)

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

#define WG_PP_ADDTYPENAME(istpl) \
  BOOST_PP_EXPR_IIF(istpl, typename)

#define WG_PP_TYPEOF(istpl, expr) \
  BOOST_PP_IIF( \
    istpl, \
    BOOST_TYPEOF_TPL, \
    BOOST_TYPEOF) (expr)

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

#define WG_PP_TOKENS_MAPTONOTHING_BOOST_PP_NIL_BOOST_PP_NIL
#define WG_PP_TOKENS_EATHEADTOKEN_BOOST_PP_NIL_IMPL(tokens) \
  BOOST_PP_CAT(WG_PP_TOKENS_MAPTONOTHING_BOOST_PP_NIL_, tokens)

#define BOOST_PP_NIL_BOOST_PP_NIL_WG_PP_TOKENS_MAPTONOTHING
#define WG_PP_TOKENS_EATTAILTOKEN_BOOST_PP_NIL_IMPL(tokens) \
  BOOST_PP_CAT(tokens, _BOOST_PP_NIL_WG_PP_TOKENS_MAPTONOTHING)

#define WG_PP_TOKEN_MATCHES_WG_PP_ERROR_WG_PP_ERROR (1) /* unary */
#define WG_PP_TOKENS_START_WITH_WG_PP_ERROR_IMPL(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_TOKEN_MATCHES_WG_PP_ERROR_)

#define WG_PP_TOKENS_MAPTONOTHING_WG_PP_ERROR_WG_PP_ERROR
#define WG_PP_TOKENS_EATHEADTOKEN_WG_PP_ERROR_IMPL(tokens) \
  BOOST_PP_CAT(WG_PP_TOKENS_MAPTONOTHING_WG_PP_ERROR_, tokens)

#define WG_PP_TOKEN_MATCHES_WG_PP_DEDUCEDTYPE_WG_PP_DEDUCEDTYPE (1) /* unary */
#define WG_PP_TOKENS_START_WITH_WG_PP_DEDUCEDTYPE_IMPL(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_TOKEN_MATCHES_WG_PP_DEDUCEDTYPE_)

#define WG_PP_TOKENS_MAPTONOTHING_WG_PP_DEDUCEDTYPE_WG_PP_DEDUCEDTYPE
#define WG_PP_TOKENS_EATHEADTOKEN_WG_PP_DEDUCEDTYPE_IMPL(tokens) \
  BOOST_PP_CAT(WG_PP_TOKENS_MAPTONOTHING_WG_PP_DEDUCEDTYPE_, tokens)

#define WG_PP_ISNEXTTOKEN_A_TUPLE_IMPL(tuplearity, tokens) \
  WG_PP_TOKENS_START_WITH_WG_PP_TRUE( \
    BOOST_PP_CAT(WG_PP_MAP_TO_TRUETOKEN_ARG, tuplearity) tokens)

#endif /* WG_PP_PP_HH_ */
