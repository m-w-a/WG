#ifndef WG_PP_AUTOFUNCTION_KEYWORDS_HH_
#define WG_PP_AUTOFUNCTION_KEYWORDS_HH_

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/local_function/detail/preprocessor/keyword/facility/is.hpp>

//###########
//Public APIs
//###########

#define WG_PP_TOKENS_EAT_HEADKEYWORD(tokens) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT(WG_PP_EAT_KEYWORD_, tokens))

#define WG_PP_TOKENS_STARTS_WITH_VOID(tokens) \
  WG_PP_TOKENS_STARTS_WITH_VOID_IMPL(tokens)

#define WG_PP_TOKENS_STARTS_WITH_THISU(tokens) \
  WG_PP_TOKENS_STARTS_WITH_THISU_IMPL(tokens)

#define WG_PP_TOKENS_STARTS_WITH_LOCAL(tokens) \
  WG_PP_TOKENS_STARTS_WITH_LOCAL_IMPL(tokens)

#define WG_PP_TOKENS_STARTS_WITH_LOCALREF(tokens) \
  WG_PP_TOKENS_STARTS_WITH_LOCALREF_IMPL(tokens)

#define WG_PP_TOKENS_STARTS_WITH_ASSIGNTO(tokens) \
  WG_PP_TOKENS_STARTS_WITH_ASSIGNTO_IMPL(tokens)

#define WG_PP_TOKENS_STARTS_WITH_RETURN(tokens) \
  WG_PP_TOKENS_STARTS_WITH_RETURN_IMPL(tokens)

#define WG_PP_TOKENS_STARTS_WITH_PARAMBIND(tokens) \
  WG_PP_TOKENS_STARTS_WITH_PARAMBIND_IMPL(tokens)

#define WG_PP_TOKENS_STARTS_WITH_PARAMSET(tokens) \
  WG_PP_TOKENS_STARTS_WITH_PARAMSET_IMPL(tokens)

#define WG_PP_TOKENS_STARTS_WITH_MEMBIND(tokens) \
  WG_PP_TOKENS_STARTS_WITH_MEMBIND_IMPL(tokens)

#define WG_PP_TOKENS_STARTS_WITH_MEMSET(tokens) \
  WG_PP_TOKENS_STARTS_WITH_MEMSET_IMPL(tokens)
  
//###########
//Impl Macros
//###########

#define WG_PP_AUTOFUNCTION_TOKEN_MATCHES2_void (1) /* unary */
#define WG_PP_TOKENS_STARTS_WITH_VOID_IMPL(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_AUTOFUNCTION_TOKEN_MATCHES2_)

#define WG_PP_AUTOFUNCTION_TOKEN_MATCHES3_this_ (1) /* unary */
#define WG_PP_TOKENS_STARTS_WITH_THISU_IMPL(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_AUTOFUNCTION_TOKEN_MATCHES3_)

#define WG_PP_AUTOFUNCTION_TOKEN_MATCHES4_local (1) /* unary */
#define WG_PP_TOKENS_STARTS_WITH_LOCAL_IMPL(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_AUTOFUNCTION_TOKEN_MATCHES4_)

#define WG_PP_AUTOFUNCTION_TOKEN_MATCHES5_localref (1) /* unary */
#define WG_PP_TOKENS_STARTS_WITH_LOCALREF_IMPL(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_AUTOFUNCTION_TOKEN_MATCHES5_)

#define WG_PP_AUTOFUNCTION_TOKEN_MATCHES6_assignto (1) /* unary */
#define WG_PP_TOKENS_STARTS_WITH_ASSIGNTO_IMPL(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_AUTOFUNCTION_TOKEN_MATCHES6_)

#define WG_PP_AUTOFUNCTION_TOKEN_MATCHES7_return (1) /* unary */
#define WG_PP_TOKENS_STARTS_WITH_RETURN_IMPL(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_AUTOFUNCTION_TOKEN_MATCHES7_)

#define WG_PP_AUTOFUNCTION_TOKEN_MATCHES8_parambind (1) /* unary */
#define WG_PP_TOKENS_STARTS_WITH_PARAMBIND_IMPL(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_AUTOFUNCTION_TOKEN_MATCHES8_)

#define WG_PP_AUTOFUNCTION_TOKEN_MATCHES9_paramset (1) /* unary */
#define WG_PP_TOKENS_STARTS_WITH_PARAMSET_IMPL(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_AUTOFUNCTION_TOKEN_MATCHES9_)

#define WG_PP_AUTOFUNCTION_TOKEN_MATCHES10_membind (1) /* unary */
#define WG_PP_TOKENS_STARTS_WITH_MEMBIND_IMPL(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_AUTOFUNCTION_TOKEN_MATCHES10_)

#define WG_PP_AUTOFUNCTION_TOKEN_MATCHES11_memset (1) /* unary */
#define WG_PP_TOKENS_STARTS_WITH_MEMSET_IMPL(tokens) \
  BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
    tokens, \
    WG_PP_AUTOFUNCTION_TOKEN_MATCHES11_)

#define WG_PP_EAT_KEYWORD_void
#define WG_PP_EAT_KEYWORD_thisu
#define WG_PP_EAT_KEYWORD_local
#define WG_PP_EAT_KEYWORD_localref
#define WG_PP_EAT_KEYWORD_assignto
#define WG_PP_EAT_KEYWORD_return
#define WG_PP_EAT_KEYWORD_parambind
#define WG_PP_EAT_KEYWORD_paramset
#define WG_PP_EAT_KEYWORD_membind
#define WG_PP_EAT_KEYWORD_memset

#endif /* WG_PP_AUTOFUNCTION_KEYWORDS_HH_ */
