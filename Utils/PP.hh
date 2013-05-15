#ifndef WG_UTIL_PP_HH_
#define WG_UTIL_PP_HH_

//###########
//Public APIs
//###########

#define WG_PP_IS_NIL_TOKEN(x) BOOST_PP_LiST_IS_NIL(x)

#define WG_PP_IDENTITY(x) x
#define WG_PP_IDENTITY_1(x) WG_PP_IDENTITY(x)
#define WG_PP_IDENTITY_2(x, y) x y
#define WG_PP_IDENTITY_3(x, y, z) x y z

#define WG_PP_TOKENS_START_WITH_WG_PP_TRUE(tokens) \
  WG_PP_TOKENS_START_WITH_WG_PP_TRUE_IMPL(tokens)

#define WG_PP_MAP_1ARG_TO_TRUETOKEN(x) \
  WG_PP_TRUE
#define WG_PP_MAP_2ARG_TO_TRUETOKEN(x, y) \
  WG_PP_TRUE

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

#define WG_PP_TOKEN_MATCHES1_WG_PP_TRUE (1) /* unary */
#define WG_PP_TOKENS_START_WITH_WG_PP_TRUE_IMPL(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_TOKEN_MATCHES1_)

#endif /* WG_UTIL_PP_HH_ */
