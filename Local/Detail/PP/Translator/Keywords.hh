#ifndef WG_PP_TRANSLATOR_KEYWORDS_HH_
#define WG_PP_TRANSLATOR_KEYWORDS_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/TokenMatching.hh>
#include <WG/Local/Detail/PP/Seq.hh>

//###########
//Public APIs
//###########

//-------
//EatHead
//-------

#define WG_PP_KEYWORDS_EAT_HEADKEYWORD(tokens) \
  BOOST_PP_EXPAND( \
    BOOST_PP_CAT(WG_PP_KEYWORDS_EAT_, tokens))

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

#define WG_PP_KEYWORDS_EAT_void
#define WG_PP_KEYWORDS_EAT_this_
#define WG_PP_KEYWORDS_EAT_type
#define WG_PP_KEYWORDS_EAT_lcltype
#define WG_PP_KEYWORDS_EAT_const
#define WG_PP_KEYWORDS_EAT_ref

//-------
//Operand
//-------

#if ! BOOST_PP_VARIADICS

  #define WG_PP_KEYWORDS_TYPE_OPERAND_IMPL(typetuple) \
    BOOST_PP_SEQ_ELEM(0, WG_PP_KEYWORDS_EAT_HEADKEYWORD(typetuple) )

  #define WG_PP_KEYWORDS_LCLTYPE_OPERAND_IMPL(lcltypetuple) \
    BOOST_PP_SEQ_ELEM(0, WG_PP_KEYWORDS_EAT_HEADKEYWORD(lcltypetuple) )

#else

  #define WG_PP_KEYWORDS_TYPE_OPERAND_IMPL(typetuple) \
    WG_PP_KEYWORDS_NAMEDTUPLE_OPERAND( \
      typetuple, WG_PP_KEYWORDS_EAT_HEADKEYWORD)

  #define WG_PP_KEYWORDS_LCLTYPE_OPERAND_IMPL(lcltypetuple) \
    WG_PP_KEYWORDS_NAMEDTUPLE_OPERAND( \
      lcltypetuple, WG_PP_KEYWORDS_EAT_HEADKEYWORD)

  #define WG_PP_KEYWORDS_NAMEDTUPLE_OPERAND(namedtuple, eatnamemacro) \
    WG_PP_KEYWORDS_EXPAND1( \
      WG_PP_SEQ_FLATTEN \
      BOOST_PP_LPAREN() \
        BOOST_PP_VARIADIC_TO_SEQ \
          eatnamemacro(namedtuple) \
      BOOST_PP_RPAREN() )

#endif

//-------------
//AddCommaAfter
//-------------

#if ! BOOST_PP_VARIADICS

  #define WG_PP_KEYWORDS_ADDCOMMAAFTER_TYPETUPLE_IMPL( \
    typetuple_prefixed_tokens) \
      type \
      WG_PP_KEYWORDS_EXPAND2( \
        WG_PP_ADDCOMMA_AFTERTUPLE_ARITY1 \
        WG_PP_KEYWORDS_EAT_HEADKEYWORD(typetuple_prefixed_tokens) )

  #define WG_PP_KEYWORDS_ADDCOMMAAFTER_LCLTYPETUPLE_IMPL( \
    lcltypetuple_prefixed_tokens) \
      lcltype \
      WG_PP_KEYWORDS_EXPAND3( \
        WG_PP_ADDCOMMA_AFTERTUPLE_ARITY1 \
        WG_PP_KEYWORDS_EAT_HEADKEYWORD(lcltypetuple_prefixed_tokens) )

#else

  #define WG_PP_KEYWORDS_ADDCOMMAAFTER_TYPETUPLE_IMPL( \
    typetuple_prefixed_tokens) \
      type \
      WG_PP_KEYWORDS_EXPAND4( \
        WG_PP_ADDCOMMA_AFTERTUPLE_ARITYN \
        WG_PP_KEYWORDS_EAT_HEADKEYWORD(typetuple_prefixed_tokens) )

  #define WG_PP_KEYWORDS_ADDCOMMAAFTER_LCLTYPETUPLE_IMPL( \
    lcltypetuple_prefixed_tokens) \
      lcltype \
      WG_PP_KEYWORDS_EXPAND5( \
        WG_PP_ADDCOMMA_AFTERTUPLE_ARITYN \
        WG_PP_KEYWORDS_EAT_HEADKEYWORD(lcltypetuple_prefixed_tokens) )

#endif

#endif /* WG_PP_TRANSLATOR_KEYWORDS_HH_ */
