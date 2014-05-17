#ifndef WG_PP_LCLCLASS_SPECNORMALIZE_HH_
#define WG_PP_LCLCLASS_SPECNORMALIZE_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/LclClass/Keywords.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/NamedParamParser.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/SplitHeadFromTokens.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/BoundVarDclnNormalize.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/SetVarDclnNormalize.hh>

//###########
//Public APIs
//###########

// Expands to the following:
//   (derives) { (BOOST_PP_NIL) | ( derives-tuple-seq ) }
//   (memext) { (BOOST_PP_NIL) | ( {normalized-bound-tuple}+ ) }
//   (memint) { (BOOST_PP_NIL) | ( {normalized-set-tuple}+ ) }
//   (errors) { (BOOST_PP_NIL) | (WG_PP_MARKER_ERROR ...) }
//
// (For definition of terms see SymbolTable documentation.)
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

#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_STARTSWITH(keyword, tokens) \
  WG_PP_UCAT_ARG2(WG_PP_LCLCLASS_KEYWORDS_STARTSWITH, keyword) (tokens)

#define WG_PP_LCLCLASS_SPEC_NAMEDPARAMPARSER_MACRONAME( \
  spec, currentkeyword, nextkeyword) \
    WG_PP_NAMEDPARAMPARSER_MACRONAME( \
      spec, WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE, currentkeyword, nextkeyword)
#define WG_PP_LCLCLASS_SPEC_NAMEDPARAMPARSER_MACROPARAMS( \
  spec, specoptions, currentkeyword, nextkeyword) \
    WG_PP_NAMEDPARAMPARSER_MACROPARAMS( \
      spec, specoptions, WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE, \
      currentkeyword, nextkeyword)

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
    WG_PP_LCLCLASS_SPEC_NAMEDPARAMPARSER_MACRONAME( \
      spec, DERIVES, MEMEXT) \
    WG_PP_LCLCLASS_SPEC_NAMEDPARAMPARSER_MACROPARAMS( \
      spec, specoptions, DERIVES, MEMEXT) )
#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_NOTFOUND_DERIVES() \
  (BOOST_PP_NIL)
#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_FOUND_DERIVES( \
  spec, specoptions, nexttransform) \
    WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_FOUND_DERIVES2( \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
        1, \
        WG_PP_LCLCLASS_KEYWORDS_EAT_HEADKEYWORD(spec), \
        WG_PP_TUPLIZE_ARG1, \
        WG_PP_TUPLIZE_ARG1, \
        WG_PP_TUPLIZE_ARG1), \
      nexttransform, \
      specoptions)
#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_FOUND_DERIVES2( \
  head_rest_tuple, nexttransform, specoptions) \
    ( BOOST_PP_SEQ_ELEM(0, head_rest_tuple) ) \
    nexttransform( BOOST_PP_SEQ_ELEM(1, head_rest_tuple) , specoptions )

#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_MEMEXT(spec, specoptions) \
  (memext) \
  WG_PP_LCLCLASS_SPEC_NORMALIZE_EXPAND2( \
    WG_PP_LCLCLASS_SPEC_NAMEDPARAMPARSER_MACRONAME( \
      spec, MEMEXT, MEMINT) \
    WG_PP_LCLCLASS_SPEC_NAMEDPARAMPARSER_MACROPARAMS( \
      spec, specoptions, MEMEXT, MEMINT) )
#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_NOTFOUND_MEMEXT() \
  (BOOST_PP_NIL)
#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_FOUND_MEMEXT( \
  spec, specoptions, nexttransform) \
    WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_FOUND_MEMEXT2( \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
        1, \
        WG_PP_LCLCLASS_KEYWORDS_EAT_HEADKEYWORD(spec), \
        WG_PP_LCLCLASS_SPEC_CHOOSE_TPL( \
          WG_PP_BOUNDVARDCLN_NORMALIZE, specoptions), \
        WG_PP_TUPLIZE_ARG1, \
        WG_PP_TUPLIZE_ARG1), \
      nexttransform, \
      specoptions)
#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_FOUND_MEMEXT2( \
  head_rest_tuple, nexttransform, specoptions) \
    ( BOOST_PP_SEQ_ELEM(0, head_rest_tuple) ) \
    nexttransform( BOOST_PP_SEQ_ELEM(1, head_rest_tuple) , specoptions)

#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_MEMINT(spec, specoptions) \
  (memint) \
  WG_PP_LCLCLASS_SPEC_NORMALIZE_EXPAND3( \
    WG_PP_LCLCLASS_SPEC_NAMEDPARAMPARSER_MACRONAME( \
      spec, MEMINT, ENDSPEC) \
    WG_PP_LCLCLASS_SPEC_NAMEDPARAMPARSER_MACROPARAMS( \
      spec, specoptions, MEMINT, ENDSPEC) )
#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_NOTFOUND_MEMINT() \
  (BOOST_PP_NIL)
#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_FOUND_MEMINT( \
  spec, specoptions, nexttransform) \
    WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_FOUND_MEMINT2( \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
        2, \
        WG_PP_LCLCLASS_KEYWORDS_EAT_HEADKEYWORD(spec), \
        WG_PP_LCLCLASS_SPEC_CHOOSE_TPL( \
          WG_PP_SETVARDCLN_NORMALIZE, specoptions), \
        WG_PP_TUPLIZE_ARG1, \
        WG_PP_TUPLIZE_ARG1), \
      nexttransform, \
      specoptions)
#define WG_PP_LCLCLASS_SPEC_NORMALIZE_PARSE_FOUND_MEMINT2( \
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
      BOOST_PP_NIL, \
      WG_PP_MARKER_ERROR WG_LCLCLASS_Error_Invalid_named_parameter) \
  )

#endif /* WG_PP_LCLCLASS_SPECNORMALIZE_HH_ */
