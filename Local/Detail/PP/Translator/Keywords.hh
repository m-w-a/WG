#ifndef WG_PP_TRANSLATOR_KEYWORDS_HH_
#define WG_PP_TRANSLATOR_KEYWORDS_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/TokenMatching.hh>

//###########
//Public APIs
//###########

//-------
//Keyword
//-------

#define WG_PP_KEYWORDS_TYPE type
#define WG_PP_KEYWORDS_LCLTYPE lcltype

//-------
//EatHead
//-------

#define WG_PP_KEYWORDS_EATHEAD_VOID(tokens) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT(WG_PP_KEYWORDS_EATHEAD_VOID_, tokens))

#define WG_PP_KEYWORDS_EATHEAD_TYPE(tokens) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT(WG_PP_KEYWORDS_EATHEAD_TYPE_, tokens))

#define WG_PP_KEYWORDS_EATHEAD_LCLTYPE(tokens) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT(WG_PP_KEYWORDS_EATHEAD_LCLTYPE_, tokens))

#define WG_PP_KEYWORDS_EATHEAD_CONST(tokens) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT(WG_PP_KEYWORDS_EATHEAD_CONST_, tokens))

#define WG_PP_KEYWORDS_EATHEAD_REF(tokens) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT(WG_PP_KEYWORDS_EATHEAD_REF_, tokens))

//----------
//StartsWith
//----------

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

//-------
//Operand
//-------

#define WG_PP_KEYWORDS_REPLACEOPERAND(keyword_tuple, replacement) \
  WG_PP_KEYWORDS_REPLACEOPERAND_IMPL(keyword_tuple, replacement)

#define WG_PP_KEYWORDS_TYPE_OPERAND(typetuple) \
  WG_PP_KEYWORDS_TYPE_OPERAND_IMPL(typetuple)

#define WG_PP_KEYWORDS_LCLTYPE_OPERAND(lcltypetuple) \
  WG_PP_KEYWORDS_LCLTYPE_OPERAND_IMPL(lcltypetuple)

//-------------
//AddCommaAfter
//-------------

#define WG_PP_KEYWORDS_ADDCOMMAAFTER_TYPETUPLE(typetuple_prefixed_tokens) \
  WG_PP_KEYWORDS_ADDCOMMAAFTER_TYPETUPLE_IMPL(typetuple_prefixed_tokens)

#define WG_PP_KEYWORDS_ADDCOMMAAFTER_LCLTYPETUPLE(lcltypetuple_prefixed_tokens) \
  WG_PP_KEYWORDS_ADDCOMMAAFTER_LCLTYPETUPLE_IMPL(lcltypetuple_prefixed_tokens)

//###########
//Impl Macros
//###########

//-----
//Utils
//-----

#define WG_PP_KEYWORDS_EXPAND1(x) x
#define WG_PP_KEYWORDS_EXPAND2(x) x
#define WG_PP_KEYWORDS_EXPAND3(x) x
#define WG_PP_KEYWORDS_EXPAND4(x) x
#define WG_PP_KEYWORDS_EXPAND5(x) x

//----------
//StartsWith
//----------

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

//-------
//EatHead
//-------

#define WG_PP_KEYWORDS_EATHEAD_VOID_void
#define WG_PP_KEYWORDS_EATHEAD_TYPE_type
#define WG_PP_KEYWORDS_EATHEAD_LCLTYPE_lcltype
#define WG_PP_KEYWORDS_EATHEAD_CONST_const
#define WG_PP_KEYWORDS_EATHEAD_REF_ref

//-------
//Operand
//-------

#define WG_PP_KEYWORDS_REPLACEOPERAND_IMPL(keyword_tuple, replacement) \
  BOOST_PP_IIF( \
    WG_PP_KEYWORDS_STARTSWITH_TYPE(keyword_tuple), \
    WG_PP_KEYWORDS_TYPE, \
    BOOST_PP_IIF( \
      WG_PP_KEYWORDS_STARTSWITH_LCLTYPE(keyword_tuple), \
      WG_PP_KEYWORDS_LCLTYPE, \
      WG_PP_MARKER_ERROR \
      WG_LCL_Error_invalid_internal_state WG_PP_MAPTO_NOTHING_ARG1) ) \
    ( replacement )

#define WG_PP_KEYWORDS_TYPE_OPERAND_IMPL(typetuple) \
  WG_PP_KEYWORDS_NAMEDTUPLE_OPERAND( \
    typetuple, WG_PP_KEYWORDS_EATHEAD_TYPE)

#define WG_PP_KEYWORDS_LCLTYPE_OPERAND_IMPL(lcltypetuple) \
  WG_PP_KEYWORDS_NAMEDTUPLE_OPERAND( \
    lcltypetuple, WG_PP_KEYWORDS_EATHEAD_LCLTYPE)

#define WG_PP_KEYWORDS_NAMEDTUPLE_OPERAND(namedtuple, eatnamemacro) \
  WG_PP_KEYWORDS_EXPAND1( \
    WG_PP_IDENTITY_ARG1 eatnamemacro(namedtuple) )


//-------------
//AddCommaAfter
//-------------

#if ! BOOST_PP_VARIADICS

  #define WG_PP_KEYWORDS_ADDCOMMAAFTER_TYPETUPLE_IMPL( \
    typetuple_prefixed_tokens) \
      WG_PP_KEYWORDS_TYPE \
      WG_PP_ADDCOMMA_AFTERTUPLE( \
        1, \
        WG_PP_KEYWORDS_EATHEAD_TYPE(typetuple_prefixed_tokens) )

  #define WG_PP_KEYWORDS_ADDCOMMAAFTER_LCLTYPETUPLE_IMPL( \
    lcltypetuple_prefixed_tokens) \
      WG_PP_KEYWORDS_LCLTYPE \
      WG_PP_ADDCOMMA_AFTERTUPLE( \
        1, \
        WG_PP_KEYWORDS_EATHEAD_LCLTYPE(lcltypetuple_prefixed_tokens) )

#else

  #define WG_PP_KEYWORDS_ADDCOMMAAFTER_TYPETUPLE_IMPL( \
    typetuple_prefixed_tokens) \
      WG_PP_KEYWORDS_TYPE \
      WG_PP_ADDCOMMA_AFTERTUPLE_V( \
        WG_PP_KEYWORDS_EATHEAD_TYPE(typetuple_prefixed_tokens) )

  #define WG_PP_KEYWORDS_ADDCOMMAAFTER_LCLTYPETUPLE_IMPL( \
    lcltypetuple_prefixed_tokens) \
      WG_PP_KEYWORDS_LCLTYPE \
      WG_PP_ADDCOMMA_AFTERTUPLE_V( \
        WG_PP_KEYWORDS_EATHEAD_LCLTYPE(lcltypetuple_prefixed_tokens) )

#endif

#endif /* WG_PP_TRANSLATOR_KEYWORDS_HH_ */
