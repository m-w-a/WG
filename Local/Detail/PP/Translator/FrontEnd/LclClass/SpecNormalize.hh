#ifndef WG_PP_LCLCLASS_SPECNORMALIZE_HH_
#define WG_PP_LCLCLASS_SPECNORMALIZE_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Translator/Keywords.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/NamedParamParser.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/SplitHeadFromTokens.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/BoundVarDclnNormalize.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/SetVarDclnNormalize.hh>

//###########
//Public APIs
//###########

// Expands to the following:
//   (derives) { (BOOST_PP_NIL) | ( derives-tuple-seq ) }
//   (memlike) { (BOOST_PP_NIL) | ( {normalized-bound-tuple}+ ) }
//   (memset) { (BOOST_PP_NIL) | ( {normalized-set-tuple}+ ) }
//
// (For definition of terms see SymbolTable documentation.)
// EXCEPTION:
//   every tuple in normalized-bound-tuple or normalized-set-tuple
//   maybe replaced with "WG_PP_ERROR ..." tokens.
#define WG_PP_LCLCLASS_SPEC_NORMALIZE(spec, istpl) \
  WG_PP_LCLCLASS_SPEC_NORMALIZE_IMPL( \
    spec BOOST_PP_NIL, \
    WG_PP_LCLCLASS_SPEC_OPTIONS_MAKE(istpl))

//###########
//Impl Macros
//###########

// Need to use these instead of BOOST_PP_EXPAND because for some reason the
// latter prevents the macro expansion of nested BOOST_PP_EXPANDs
#define WG_PP_LCLCLASS_SPEC_NORMALIZE_EXPAND1(x) x
#define WG_PP_LCLCLASS_SPEC_NORMALIZE_EXPAND2(x) x
#define WG_PP_LCLCLASS_SPEC_NORMALIZE_EXPAND3(x) x

#define WG_PP_LCLCLASS_SPEC_OPTIONS_MAKE(istpl) istpl
#define WG_PP_LCLCLASS_SPEC_OPTIONS_ISTPL(specoptions) specoptions

#define WG_PP_LCLCLASS_SPEC_CHOOSE_TPL(macro, specoptions) \
  BOOST_PP_IIF( \
    WG_PP_LCLCLASS_SPEC_OPTIONS_ISTPL(specoptions), \
    BOOST_PP_CAT(macro, _TPL), \
    macro)

#define WG_PP_LCLCLASS_SPEC_NORMALIZE_IMPL(spec, specoptions) \
  WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_DERIVES(spec, specoptions)

//------------------------------------------------------------------------------
// Implementation Note:
// WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_FOUND_<keyword>2 cannot be factored
//   out into a common macro because it will result in an eventual recursive
//   call of itself.
// WG_PP_SPLITHEADTUPLEFROMTOKENS cannot apply nexttransform to the rest of
//   the tokens because it will result in an eventual recursive call of itself.
//------------------------------------------------------------------------------

#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_DERIVES(spec, specoptions) \
  (derives) \
  WG_PP_LCLCLASS_SPEC_NORMALIZE_EXPAND1( \
    WG_PP_NAMEDPARAMPARSER_MACRONAME( \
      spec,  WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE, DERIVES, MEMLIKE) \
    WG_PP_NAMEDPARAMPARSER_MACROPARAMS( \
      spec, specoptions, WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE, DERIVES, MEMLIKE) )
#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_NOTFOUND_DERIVES() \
  (BOOST_PP_NIL)
#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_FOUND_DERIVES( \
  spec, specoptions, nexttransform) \
    WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_FOUND_DERIVES2( \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
        1, \
        WG_PP_KEYWORDS_EAT_HEADKEYWORD(spec), \
        WG_PP_IDENTITY_ARG1, \
        WG_PP_TUPLIZE_ARG1, \
        WG_PP_TUPLIZE_ARG1), \
      nexttransform, \
      specoptions)
#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_FOUND_DERIVES2( \
  head_rest_tuple, nexttransform, specoptions) \
    ( BOOST_PP_SEQ_ELEM(0, head_rest_tuple) ) \
    nexttransform( BOOST_PP_SEQ_ELEM(1, head_rest_tuple) , specoptions )

#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_MEMLIKE(spec, specoptions) \
  (memlike) \
  WG_PP_LCLCLASS_SPEC_NORMALIZE_EXPAND2( \
    WG_PP_NAMEDPARAMPARSER_MACRONAME( \
      spec,  WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE, MEMLIKE, MEMSET) \
    WG_PP_NAMEDPARAMPARSER_MACROPARAMS( \
      spec, specoptions, WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE, MEMLIKE, MEMSET) )
#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_NOTFOUND_MEMLIKE() \
  (BOOST_PP_NIL)
#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_FOUND_MEMLIKE( \
  spec, specoptions, nexttransform) \
    WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_FOUND_MEMLIKE2( \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
        1, \
        WG_PP_KEYWORDS_EAT_HEADKEYWORD(spec), \
        WG_PP_LCLCLASS_SPEC_CHOOSE_TPL( \
          WG_PP_BOUNDVARDCLN_NORMALIZE, specoptions), \
        WG_PP_TUPLIZE_ARG1, \
        WG_PP_TUPLIZE_ARG1), \
      nexttransform, \
      specoptions)
#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_FOUND_MEMLIKE2( \
  head_rest_tuple, nexttransform, specoptions) \
    ( BOOST_PP_SEQ_ELEM(0, head_rest_tuple) ) \
    nexttransform( BOOST_PP_SEQ_ELEM(1, head_rest_tuple) , specoptions)

#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_MEMSET(spec, specoptions) \
  (memset) \
  WG_PP_LCLCLASS_SPEC_NORMALIZE_EXPAND3( \
    WG_PP_NAMEDPARAMPARSER_MACRONAME( \
      spec,  WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE, MEMSET, ENDSPEC) \
    WG_PP_NAMEDPARAMPARSER_MACROPARAMS( \
      spec, specoptions, WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE, MEMSET, ENDSPEC) )
#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_NOTFOUND_MEMSET() \
  (BOOST_PP_NIL)
#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_FOUND_MEMSET( \
  spec, specoptions, nexttransform) \
    WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_FOUND_MEMSET2( \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
        2, \
        WG_PP_KEYWORDS_EAT_HEADKEYWORD(spec), \
        WG_PP_LCLCLASS_SPEC_CHOOSE_TPL( \
          WG_PP_SETVARDCLN_NORMALIZE, specoptions), \
        WG_PP_TUPLIZE_ARG1, \
        WG_PP_TUPLIZE_ARG1), \
      nexttransform, \
      specoptions)
#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_FOUND_MEMSET2( \
  head_rest_tuple, nexttransform, specoptions) \
    ( BOOST_PP_SEQ_ELEM(0, head_rest_tuple) ) \
    nexttransform( BOOST_PP_SEQ_ELEM(1, head_rest_tuple) , specoptions)

#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_ENDSPEC(spec, specoptions) \
  WG_PP_LCLCLASS_SPEC_NORMALIZE_VALIDATESPEC(spec)

// To be called after an attempt to parse the complete spec.
//   If the remaining spec is not BOOST_PP_NIL, then the head token(s) should
//   be a good indicator of where things went wrong.
#define WG_PP_LCLCLASS_SPEC_NORMALIZE_VALIDATESPEC(spec) \
  (errors) \
  ( \
    BOOST_PP_IIF( \
      WG_PP_STARTSWITH_BOOST_PP_NIL(spec), \
      BOOST_PP_NIL BOOST_PP_EMPTY, \
      WG_PP_ERROR WG_PP_ID_CAT( \
        ERROR_Invalid_tokens, \
        WG_PP_EATTAILTOKEN_BOOST_PP_NIL(spec) BOOST_PP_EMPTY) ) () \
  )

#endif /* WG_PP_LCLCLASS_SPECNORMALIZE_HH_ */
