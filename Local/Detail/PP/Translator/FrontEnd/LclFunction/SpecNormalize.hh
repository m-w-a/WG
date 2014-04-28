#ifndef WG_PP_LCLFUNCTION_SPECNORMALIZE_HH_
#define WG_PP_LCLFUNCTION_SPECNORMALIZE_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Translator/Keywords.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/LclFunction/Keywords.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/NamedParamParser.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/SplitHeadFromTokens.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/BoundVarDclnNormalize.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/SetVarDclnNormalize.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/ReturnTypeNormalize.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/LclFunction/ParamDclnNormalize.hh>

//###########
//Public APIs
//###########

// Expands to the following:
//   (return) { (BOOST_PP_NIL) | (type) }
//   (params) { (BOOST_PP_NIL) | ( {normalized-explicit-nlt-tuple}+ ) }
//   (varbind) { (BOOST_PP_NIL) | ( {normalized-bound-nlt-tuple}+ ) }
//   (varset) { (BOOST_PP_NIL) | ( {normalized-set-nlt-tuple}+ ) }
//   (errors) { (BOOST_PP_NIL) | (WG_PP_MARKER_ERROR ...) }
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE(spec, istpl) \
  WG_PP_LCLFUNCTION_SPEC_NORMALIZE_IMPL( \
    spec BOOST_PP_NIL, \
    WG_PP_LCLFUNCTION_SPEC_OPTIONS_MAKE(istpl))

//###########
//Impl Macros
//###########

// Need to use these instead of BOOST_PP_EXPAND because for some reason the
// latter prevents the macro expansion of nested BOOST_PP_EXPANDs
#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_EXPAND1(x) x
#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_EXPAND2(x) x
#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_EXPAND3(x) x
#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_EXPAND4(x) x

#define WG_PP_LCLFUNCTION_SPEC_OPTIONS_MAKE(istpl) istpl
#define WG_PP_LCLFUNCTION_SPEC_OPTIONS_ISTPL(specoptions) specoptions

#define WG_PP_LCLFUNCTION_SPEC_CHOOSE_TPL(macro, specoptions) \
  BOOST_PP_IIF( \
    WG_PP_LCLFUNCTION_SPEC_OPTIONS_ISTPL(specoptions), \
    BOOST_PP_CAT(macro, _TPL), \
    macro)

#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_IMPL(spec, specoptions) \
  WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE_RETURN( \
    BOOST_PP_IIF( \
      WG_PP_KEYWORDS_STARTSWITH_VOID(spec), \
      WG_PP_KEYWORDS_EATHEAD_VOID(spec), \
      spec), \
    specoptions)

#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE_STARTSWITH(keyword, tokens) \
  WG_PP_UCAT_ARG2(WG_PP_LCLFUNCTION_KEYWORDS_STARTSWITH, keyword) (tokens)

#define WG_PP_LCLFUNCTION_SPEC_NAMEDPARAMPARSER_MACRONAME( \
  spec, currentkeyword, nextkeyword) \
    WG_PP_NAMEDPARAMPARSER_MACRONAME( \
      spec, WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE, currentkeyword, nextkeyword)
#define WG_PP_LCLFUNCTION_SPEC_NAMEDPARAMPARSER_MACROPARAMS( \
  spec, specoptions, currentkeyword, nextkeyword) \
    WG_PP_NAMEDPARAMPARSER_MACROPARAMS( \
      spec, specoptions, WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE, \
      currentkeyword, nextkeyword)

//------------------------------------------------------------------------------
// Implementation Note:
// WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE_FOUND_<keyword>2 cannot be factored
//   out into a common macro because it will result in an eventual recursive
//   call of itself.
// WG_PP_SPLITHEADTUPLEFROMTOKENS cannot apply nexttransform to the rest of
//   the tokens because it will result in an eventual recursive call of itself.
//------------------------------------------------------------------------------

#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE_RETURN(spec, specoptions) \
  (return) \
  WG_PP_LCLFUNCTION_SPEC_NORMALIZE_EXPAND1( \
    WG_PP_LCLFUNCTION_SPEC_NAMEDPARAMPARSER_MACRONAME( \
      spec, RETURN, PARAMS) \
    WG_PP_LCLFUNCTION_SPEC_NAMEDPARAMPARSER_MACROPARAMS( \
      spec, specoptions, RETURN, PARAMS) )
#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE_NOTFOUND_RETURN() \
  (BOOST_PP_NIL)
#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE_FOUND_RETURN( \
  spec, specoptions, nexttransform) \
    WG_PP_LCLFUNCTION_SPEC_NORMALIZE_FOUND_RETURN2( \
      WG_PP_SPLITHEADTUPLEFROMTOKENS( \
        1, \
        WG_PP_LCLFUNCTION_KEYWORDS_EAT_HEADKEYWORD(spec), \
        WG_PP_LCLFUNCTION_SPEC_CHOOSE_TPL( \
          WG_PP_RETURNTYPE_NORMALIZE, specoptions), \
        WG_PP_TUPLIZE_ARG1, \
        WG_PP_TUPLIZE_ARG1), \
      nexttransform, \
      specoptions)
#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_FOUND_RETURN2( \
  head_rest_tuple, nexttransform, specoptions) \
    ( BOOST_PP_SEQ_ELEM(0, head_rest_tuple) ) \
    nexttransform( BOOST_PP_SEQ_ELEM(1, head_rest_tuple) , specoptions )

#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE_PARAMS(spec, specoptions) \
  (params) \
  WG_PP_LCLFUNCTION_SPEC_NORMALIZE_EXPAND2( \
    WG_PP_LCLFUNCTION_SPEC_NAMEDPARAMPARSER_MACRONAME( \
      spec, PARAMS, VARBIND) \
    WG_PP_LCLFUNCTION_SPEC_NAMEDPARAMPARSER_MACROPARAMS( \
      spec, specoptions, PARAMS, VARBIND) )
#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE_NOTFOUND_PARAMS() \
  (BOOST_PP_NIL)
#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE_FOUND_PARAMS( \
  spec, specoptions, nexttransform) \
    WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE_FOUND_PARAMS2( \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
        1, \
        WG_PP_LCLFUNCTION_KEYWORDS_EAT_HEADKEYWORD(spec), \
        WG_PP_LCLFUNCTION_SPEC_CHOOSE_TPL( \
          WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE, specoptions), \
        WG_PP_TUPLIZE_ARG1, \
        WG_PP_TUPLIZE_ARG1), \
      nexttransform, \
      specoptions)
#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE_FOUND_PARAMS2( \
  head_rest_tuple, nexttransform, specoptions) \
    ( BOOST_PP_SEQ_ELEM(0, head_rest_tuple) ) \
    nexttransform( BOOST_PP_SEQ_ELEM(1, head_rest_tuple) , specoptions )

#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE_VARBIND(spec, specoptions) \
  (varbind) \
  WG_PP_LCLFUNCTION_SPEC_NORMALIZE_EXPAND3( \
    WG_PP_LCLFUNCTION_SPEC_NAMEDPARAMPARSER_MACRONAME( \
      spec, VARBIND, VARSET) \
    WG_PP_LCLFUNCTION_SPEC_NAMEDPARAMPARSER_MACROPARAMS( \
      spec, specoptions, VARBIND, VARSET) )
#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE_NOTFOUND_VARBIND() \
  (BOOST_PP_NIL)
#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE_FOUND_VARBIND( \
  spec, specoptions, nexttransform) \
    WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE_FOUND_VARBIND2( \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
        1, \
        WG_PP_LCLFUNCTION_KEYWORDS_EAT_HEADKEYWORD(spec), \
        WG_PP_LCLFUNCTION_SPEC_CHOOSE_TPL( \
          WG_PP_BOUNDVARDCLN_NLT_NORMALIZE, specoptions), \
        WG_PP_TUPLIZE_ARG1, \
        WG_PP_TUPLIZE_ARG1), \
      nexttransform, \
      specoptions)
#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE_FOUND_VARBIND2( \
  head_rest_tuple, nexttransform, specoptions) \
    ( BOOST_PP_SEQ_ELEM(0, head_rest_tuple) ) \
    nexttransform( BOOST_PP_SEQ_ELEM(1, head_rest_tuple) , specoptions )

#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE_VARSET(spec, specoptions) \
  (varset) \
  WG_PP_LCLFUNCTION_SPEC_NORMALIZE_EXPAND4( \
    WG_PP_LCLFUNCTION_SPEC_NAMEDPARAMPARSER_MACRONAME( \
      spec, VARSET, ENDSPEC) \
    WG_PP_LCLFUNCTION_SPEC_NAMEDPARAMPARSER_MACROPARAMS( \
      spec, specoptions, VARSET, ENDSPEC) )
#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE_NOTFOUND_VARSET() \
  (BOOST_PP_NIL)
#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE_FOUND_VARSET( \
  spec, specoptions, nexttransform) \
    WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE_FOUND_VARSET2( \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
        2, \
        WG_PP_LCLFUNCTION_KEYWORDS_EAT_HEADKEYWORD(spec), \
        WG_PP_LCLFUNCTION_SPEC_CHOOSE_TPL( \
          WG_PP_SETVARDCLN_NLT_NORMALIZE, specoptions), \
        WG_PP_TUPLIZE_ARG1, \
        WG_PP_TUPLIZE_ARG1), \
      nexttransform, \
      specoptions)
#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE_FOUND_VARSET2( \
  head_rest_tuple, nexttransform, specoptions) \
    ( BOOST_PP_SEQ_ELEM(0, head_rest_tuple) ) \
    nexttransform( BOOST_PP_SEQ_ELEM(1, head_rest_tuple) , specoptions )

#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_PARSE_ENDSPEC(spec, specoptions) \
  WG_PP_LCLFUNCTION_SPEC_NORMALIZE_VALIDATESPEC(spec)

// To be called after an attempt to parse the complete spec.
//   If the remaining spec is not BOOST_PP_NIL, then the head token(s) should
//   be a good indicator of where things went wrong.
#define WG_PP_LCLFUNCTION_SPEC_NORMALIZE_VALIDATESPEC(spec) \
  (errors) \
  ( \
    BOOST_PP_IIF( \
      WG_PP_STARTSWITH_BOOST_PP_NIL(spec), \
      BOOST_PP_NIL BOOST_PP_EMPTY, \
      WG_PP_MARKER_ERROR WG_PP_ID_CAT( \
        ERROR_Invalid_tokens, \
        WG_PP_EATTAILTOKEN_BOOST_PP_NIL(spec) BOOST_PP_EMPTY) ) () \
  )

#endif /* WG_PP_LCLFUNCTION_SPECNORMALIZE_HH_ */
