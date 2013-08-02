#ifndef WG_PP_AUTOFUNCTOR_SPECNORMALIZE_HH_
#define WG_PP_AUTOFUNCTOR_SPECNORMALIZE_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/Seq.hh>
#include <WG/Local/Detail/Keywords.hh>
#include <WG/Local/Detail/FrontEnd/NamedParamParser.hh>
#include <WG/Local/Detail/FrontEnd/SplitHeadFromTokens.hh>
#include <WG/Local/Detail/FrontEnd/BoundVarDclnNormalize.hh>
#include <WG/Local/Detail/FrontEnd/SetVarDclnNormalize.hh>

//###########
//Public APIs
//###########

// Expands to the following:
//   (assignto) { (BOOST_PP_NIL) | (normalized-bound-tuple) }
//   (return) { (BOOST_PP_NIL) | (type) }
//   (parambind) { (BOOST_PP_NIL) | ( {normalized-bound-tuple}+ ) }
//   (paramset) { (BOOST_PP_NIL) | ( {normalized-set-tuple}+ ) }
//   (membind) { (BOOST_PP_NIL) | ( {normalized-bound-tuple}+ ) }
//   (memset) { (BOOST_PP_NIL) | ( {normalized-set-tuple}+ ) }
//   (errors) { (BOOST_PP_NIL) | (WG_PP_ERROR ...) }
//
// (For definition of terms see SymbolTable documentation.)
// EXCEPTION: every tuple in normalized-bound-tuple or normalized-set-tuple
//   maybe replaced with "WG_PP_ERROR ..." tokens.
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE(spec, istpl) \
  WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_IMPL( \
    spec BOOST_PP_NIL, \
    WG_PP_AUTOFUNCTOR_SPEC_OPTIONS_MAKE(istpl))

//###########
//Impl Macros
//###########

// Need to use these instead of BOOST_PP_EXPAND because for some reason the 
//  latter prevents the macro expansion of nested BOOST_PP_EXPANDs
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_EXPAND1(x) x
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_EXPAND2(x) x
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_EXPAND3(x) x
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_EXPAND4(x) x
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_EXPAND5(x) x
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_EXPAND6(x) x

#define WG_PP_AUTOFUNCTOR_SPEC_OPTIONS_MAKE(istpl) istpl
#define WG_PP_AUTOFUNCTOR_SPEC_OPTIONS_ISTPL(specoptions) specoptions

#define WG_PP_AUTOFUNCTOR_SPEC_CHOOSE_TPL(macro, specoptions) \
  BOOST_PP_IIF( \
    WG_PP_AUTOFUNCTOR_SPEC_OPTIONS_ISTPL(specoptions), \
    BOOST_PP_CAT(macro, _TPL), \
    macro)

#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_IMPL(spec, specoptions) \
  WG_PP_NAMEDPARAMPARSER_PARSE_AUTOFUNCTOR_ASSIGNTO( \
    BOOST_PP_IIF( \
      WG_PP_TOKENS_STARTWITH_VOID(spec), \
      WG_PP_TOKENS_EAT_HEADKEYWORD(spec), \
      spec), \
    specoptions)

//------------------------------------------------------------------------------
// Implementation Note:
// WG_PP_NAMEDPARAMPARSER_PARSE_FOUND_AUTOFUNCTOR_<keyword>2 cannot be factored
//   out into a common macro because it will result in an eventual recursive
//   call of itself.
// WG_PP_SPLITHEADTUPLEFROMTOKENS cannot apply nexttransform to the rest of
//   the tokens because it will result in an eventual recursive call of itself.
//------------------------------------------------------------------------------

#define WG_PP_NAMEDPARAMPARSER_PARSE_AUTOFUNCTOR_ASSIGNTO(spec, specoptions) \
  (assignto) \
  WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_EXPAND1( \
    WG_PP_NAMEDPARAMPARSER_MACRONAME( \
      spec, AUTOFUNCTOR, ASSIGNTO, RETURN) \
    WG_PP_NAMEDPARAMPARSER_MACROPARAMS( \
      spec, specoptions, AUTOFUNCTOR, ASSIGNTO, RETURN) )
#define WG_PP_NAMEDPARAMPARSER_PARSE_NOTFOUND_AUTOFUNCTOR_ASSIGNTO() \
  (BOOST_PP_NIL)
#define WG_PP_NAMEDPARAMPARSER_PARSE_FOUND_AUTOFUNCTOR_ASSIGNTO( \
  spec, specoptions, nexttransform) \
    WG_PP_NAMEDPARAMPARSER_PARSE_FOUND_AUTOFUNCTOR_ASSIGNTO2( \
      WG_PP_SPLITHEADTUPLEFROMTOKENS( \
        1, \
        WG_PP_TOKENS_EAT_HEADKEYWORD(spec), \
        WG_PP_AUTOFUNCTOR_SPEC_CHOOSE_TPL( \
          WG_PP_BOUNDVARDCLN_NORMALIZE, specoptions), \
        WG_PP_TUPLIZE, \
        WG_PP_TUPLIZE), \
      nexttransform, \
      specoptions)
#define WG_PP_NAMEDPARAMPARSER_PARSE_FOUND_AUTOFUNCTOR_ASSIGNTO2( \
  head_rest_tuple, nexttransform, specoptions) \
    ( BOOST_PP_SEQ_ELEM(0, head_rest_tuple) ) \
    nexttransform( BOOST_PP_SEQ_ELEM(1, head_rest_tuple) , specoptions )

#define WG_PP_NAMEDPARAMPARSER_PARSE_AUTOFUNCTOR_RETURN(spec, specoptions) \
  (return) \
  WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_EXPAND2( \
    WG_PP_NAMEDPARAMPARSER_MACRONAME( \
      spec, AUTOFUNCTOR, RETURN, PARAMBIND) \
    WG_PP_NAMEDPARAMPARSER_MACROPARAMS( \
      spec, specoptions, AUTOFUNCTOR, RETURN, PARAMBIND) )
#define WG_PP_NAMEDPARAMPARSER_PARSE_NOTFOUND_AUTOFUNCTOR_RETURN() \
  (BOOST_PP_NIL)
#define WG_PP_NAMEDPARAMPARSER_PARSE_FOUND_AUTOFUNCTOR_RETURN( \
  spec, specoptions, nexttransform) \
    WG_PP_NAMEDPARAMPARSER_PARSE_FOUND_AUTOFUNCTOR_RETURN2( \
      WG_PP_SPLITHEADTUPLEFROMTOKENS( \
        1, \
        WG_PP_TOKENS_EAT_HEADKEYWORD(spec), \
        WG_PP_IDENTITY, \
        WG_PP_TUPLIZE, \
        WG_PP_TUPLIZE), \
      nexttransform, \
      specoptions)
#define WG_PP_NAMEDPARAMPARSER_PARSE_FOUND_AUTOFUNCTOR_RETURN2( \
  head_rest_tuple, nexttransform, specoptions) \
    ( BOOST_PP_SEQ_ELEM(0, head_rest_tuple) ) \
    nexttransform( BOOST_PP_SEQ_ELEM(1, head_rest_tuple) , specoptions )

#define WG_PP_NAMEDPARAMPARSER_PARSE_AUTOFUNCTOR_PARAMBIND(spec, specoptions) \
  (parambind) \
  WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_EXPAND3( \
    WG_PP_NAMEDPARAMPARSER_MACRONAME( \
      spec, AUTOFUNCTOR, PARAMBIND, PARAMSET) \
    WG_PP_NAMEDPARAMPARSER_MACROPARAMS( \
      spec, specoptions, AUTOFUNCTOR, PARAMBIND, PARAMSET) )
#define WG_PP_NAMEDPARAMPARSER_PARSE_NOTFOUND_AUTOFUNCTOR_PARAMBIND() \
  (BOOST_PP_NIL)
#define WG_PP_NAMEDPARAMPARSER_PARSE_FOUND_AUTOFUNCTOR_PARAMBIND( \
  spec, specoptions, nexttransform) \
    WG_PP_NAMEDPARAMPARSER_PARSE_FOUND_AUTOFUNCTOR_PARAMBIND2( \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
        1, \
        WG_PP_TOKENS_EAT_HEADKEYWORD(spec), \
        WG_PP_AUTOFUNCTOR_SPEC_CHOOSE_TPL( \
          WG_PP_BOUNDVARDCLN_NORMALIZE, specoptions), \
        WG_PP_TUPLIZE, \
        WG_PP_TUPLIZE), \
      nexttransform, \
      specoptions)
#define WG_PP_NAMEDPARAMPARSER_PARSE_FOUND_AUTOFUNCTOR_PARAMBIND2( \
  head_rest_tuple, nexttransform, specoptions) \
    ( BOOST_PP_SEQ_ELEM(0, head_rest_tuple) ) \
    nexttransform( BOOST_PP_SEQ_ELEM(1, head_rest_tuple) , specoptions )

#define WG_PP_NAMEDPARAMPARSER_PARSE_AUTOFUNCTOR_PARAMSET(spec, specoptions) \
  (paramset) \
  WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_EXPAND4( \
    WG_PP_NAMEDPARAMPARSER_MACRONAME( \
      spec, AUTOFUNCTOR, PARAMSET, MEMBIND) \
    WG_PP_NAMEDPARAMPARSER_MACROPARAMS( \
      spec, specoptions, AUTOFUNCTOR, PARAMSET, MEMBIND) )
#define WG_PP_NAMEDPARAMPARSER_PARSE_NOTFOUND_AUTOFUNCTOR_PARAMSET() \
  (BOOST_PP_NIL)
#define WG_PP_NAMEDPARAMPARSER_PARSE_FOUND_AUTOFUNCTOR_PARAMSET( \
  spec, specoptions, nexttransform) \
    WG_PP_NAMEDPARAMPARSER_PARSE_FOUND_AUTOFUNCTOR_PARAMSET2( \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
        2, \
        WG_PP_TOKENS_EAT_HEADKEYWORD(spec), \
        WG_PP_AUTOFUNCTOR_SPEC_CHOOSE_TPL( \
          WG_PP_SETVARDCLN_NORMALIZE, specoptions), \
        WG_PP_TUPLIZE, \
        WG_PP_TUPLIZE), \
      nexttransform, \
      specoptions)
#define WG_PP_NAMEDPARAMPARSER_PARSE_FOUND_AUTOFUNCTOR_PARAMSET2( \
  head_rest_tuple, nexttransform, specoptions) \
    ( BOOST_PP_SEQ_ELEM(0, head_rest_tuple) ) \
    nexttransform( BOOST_PP_SEQ_ELEM(1, head_rest_tuple) , specoptions )

#define WG_PP_NAMEDPARAMPARSER_PARSE_AUTOFUNCTOR_MEMBIND(spec, specoptions) \
  (membind) \
  WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_EXPAND5( \
    WG_PP_NAMEDPARAMPARSER_MACRONAME( \
      spec, AUTOFUNCTOR, MEMBIND, MEMSET) \
    WG_PP_NAMEDPARAMPARSER_MACROPARAMS( \
      spec, specoptions, AUTOFUNCTOR, MEMBIND, MEMSET) )
#define WG_PP_NAMEDPARAMPARSER_PARSE_NOTFOUND_AUTOFUNCTOR_MEMBIND() \
  (BOOST_PP_NIL)
#define WG_PP_NAMEDPARAMPARSER_PARSE_FOUND_AUTOFUNCTOR_MEMBIND( \
  spec, specoptions, nexttransform) \
    WG_PP_NAMEDPARAMPARSER_PARSE_FOUND_AUTOFUNCTOR_MEMBIND2( \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
        1, \
        WG_PP_TOKENS_EAT_HEADKEYWORD(spec), \
        WG_PP_AUTOFUNCTOR_SPEC_CHOOSE_TPL( \
          WG_PP_BOUNDVARDCLN_NORMALIZE, specoptions), \
        WG_PP_TUPLIZE, \
        WG_PP_TUPLIZE), \
      nexttransform, \
      specoptions)
#define WG_PP_NAMEDPARAMPARSER_PARSE_FOUND_AUTOFUNCTOR_MEMBIND2( \
  head_rest_tuple, nexttransform, specoptions) \
    ( BOOST_PP_SEQ_ELEM(0, head_rest_tuple) ) \
    nexttransform( BOOST_PP_SEQ_ELEM(1, head_rest_tuple) , specoptions)

#define WG_PP_NAMEDPARAMPARSER_PARSE_AUTOFUNCTOR_MEMSET(spec, specoptions) \
  (memset) \
  WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_EXPAND6( \
    WG_PP_NAMEDPARAMPARSER_MACRONAME( \
      spec, AUTOFUNCTOR, MEMSET, ENDSPEC) \
    WG_PP_NAMEDPARAMPARSER_MACROPARAMS( \
      spec, specoptions, AUTOFUNCTOR, MEMSET, ENDSPEC) )
#define WG_PP_NAMEDPARAMPARSER_PARSE_NOTFOUND_AUTOFUNCTOR_MEMSET() \
  (BOOST_PP_NIL)
#define WG_PP_NAMEDPARAMPARSER_PARSE_FOUND_AUTOFUNCTOR_MEMSET( \
  spec, specoptions, nexttransform) \
    WG_PP_NAMEDPARAMPARSER_PARSE_FOUND_AUTOFUNCTOR_MEMSET2( \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
        2, \
        WG_PP_TOKENS_EAT_HEADKEYWORD(spec), \
        WG_PP_AUTOFUNCTOR_SPEC_CHOOSE_TPL( \
          WG_PP_SETVARDCLN_NORMALIZE, specoptions), \
        WG_PP_TUPLIZE, \
        WG_PP_TUPLIZE), \
      nexttransform, \
      specoptions)
#define WG_PP_NAMEDPARAMPARSER_PARSE_FOUND_AUTOFUNCTOR_MEMSET2( \
  head_rest_tuple, nexttransform, specoptions) \
    ( BOOST_PP_SEQ_ELEM(0, head_rest_tuple) ) \
    nexttransform( BOOST_PP_SEQ_ELEM(1, head_rest_tuple) , specoptions)

#define WG_PP_NAMEDPARAMPARSER_PARSE_AUTOFUNCTOR_ENDSPEC(spec, specoptions) \
  WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_VALIDATESPEC(spec)

// To be called after an attempt to parse the complete spec.
//   If the remaining spec is not BOOST_PP_NIL, then the head token(s) should
//   be a good indicator of where things went wrong.
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_VALIDATESPEC(spec) \
  (errors) \
  ( \
    BOOST_PP_IIF( \
      WG_PP_TOKENS_START_WITH_BOOST_PP_NIL(spec), \
      BOOST_PP_NIL BOOST_PP_EMPTY, \
      WG_PP_ERROR WG_PP_ID_CAT( \
        ERROR_Invalid_tokens, \
        WG_PP_TOKENS_EATTAILTOKEN_BOOST_PP_NIL(spec) BOOST_PP_EMPTY) ) () \
  )

#endif /* WG_PP_AUTOFUNCTOR_SPECNORMALIZE_HH_ */
