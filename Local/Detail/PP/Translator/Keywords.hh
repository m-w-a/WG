#ifndef WG_PP_TRANSLATOR_KEYWORDS_HH_
#define WG_PP_TRANSLATOR_KEYWORDS_HH_

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <WG/Local/Detail/PP/TokenMatching.hh>

//###########
//Public APIs
//###########

#define WG_PP_KEYWORDS_EAT_HEADKEYWORD(tokens) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT(WG_PP_KEYWORDS_EAT_, tokens))

#define WG_PP_KEYWORDS_STARTSWITH_VOID(tokens) \
  WG_PP_KEYWORDS_STARTSWITH_VOID_IMPL(tokens)

#define WG_PP_KEYWORDS_STARTSWITH_THISU(tokens) \
  WG_PP_KEYWORDS_STARTSWITH_THISU_IMPL(tokens)

#define WG_PP_KEYWORDS_STARTSWITH_TYPE(tokens) \
  WG_PP_KEYWORDS_STARTSWITH_TYPE_IMPL(tokens)

#define WG_PP_KEYWORDS_STARTSWITH_LCLTYPE(tokens) \
  WG_PP_KEYWORDS_STARTSWITH_LCLTYPE_IMPL(tokens)

#define WG_PP_KEYWORDS_STARTSWITH_CONST(tokens) \
  WG_PP_KEYWORDS_STARTSWITH_CONST_IMPL(tokens)

#define WG_PP_KEYWORDS_STARTSWITH_REF(tokens) \
  WG_PP_KEYWORDS_STARTSWITH_REF_IMPL(tokens)

//###########
//Impl Macros
//###########

#define WG_PP_KEYWORDS_BEGINSWITH_void_void WG_PP_TOKENMATCH_FRONTMATCH
#define WG_PP_KEYWORDS_STARTSWITH_VOID_IMPL(tokens) \
  WG_PP_TOKENMATCH_BEGINSWITH(\
    tokens, \
    WG_PP_KEYWORDS_BEGINSWITH_void_)

#define WG_PP_KEYWORDS_BEGINSWITH_thisu_this_ WG_PP_TOKENMATCH_FRONTMATCH
#define WG_PP_KEYWORDS_STARTSWITH_THISU_IMPL(tokens) \
  WG_PP_TOKENMATCH_BEGINSWITH(\
    tokens, \
    WG_PP_KEYWORDS_BEGINSWITH_thisu_)

#define WG_PP_KEYWORDS_BEGINSWITH_type_type WG_PP_TOKENMATCH_FRONTMATCH
#define WG_PP_KEYWORDS_STARTSWITH_TYPE_IMPL(tokens) \
  WG_PP_TOKENMATCH_BEGINSWITH(\
    tokens, \
    WG_PP_KEYWORDS_BEGINSWITH_type_)

#define WG_PP_KEYWORDS_BEGINSWITH_lcltype_lcltype WG_PP_TOKENMATCH_FRONTMATCH
#define WG_PP_KEYWORDS_STARTSWITH_LCLTYPE_IMPL(tokens) \
  WG_PP_TOKENMATCH_BEGINSWITH(\
    tokens, \
    WG_PP_KEYWORDS_BEGINSWITH_lcltype_)

#define WG_PP_KEYWORDS_BEGINSWITH_const_const WG_PP_TOKENMATCH_FRONTMATCH
#define WG_PP_KEYWORDS_STARTSWITH_CONST_IMPL(tokens) \
  WG_PP_TOKENMATCH_BEGINSWITH(\
    tokens, \
    WG_PP_KEYWORDS_BEGINSWITH_const_)

#define WG_PP_KEYWORDS_BEGINSWITH_ref_ref WG_PP_TOKENMATCH_FRONTMATCH
#define WG_PP_KEYWORDS_STARTSWITH_REF_IMPL(tokens) \
  WG_PP_TOKENMATCH_BEGINSWITH(\
    tokens, \
    WG_PP_KEYWORDS_BEGINSWITH_ref_)

#define WG_PP_KEYWORDS_EAT_void
#define WG_PP_KEYWORDS_EAT_this_
#define WG_PP_KEYWORDS_EAT_type
#define WG_PP_KEYWORDS_EAT_lcltype
#define WG_PP_KEYWORDS_EAT_const
#define WG_PP_KEYWORDS_EAT_ref

#endif /* WG_PP_TRANSLATOR_KEYWORDS_HH_ */
