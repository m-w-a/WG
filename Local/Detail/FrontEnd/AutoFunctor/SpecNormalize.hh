#ifndef WG_PP_AUTOFUNCTOR_SPECNORMALIZE_HH_
#define WG_PP_AUTOFUNCTOR_SPECNORMALIZE_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/Seq.hh>
#include <WG/Local/Detail/Keywords.hh>
#include <WG/Local/Detail/FrontEnd/SplitHeadFromTokens.hh>
#include <WG/Local/Detail/FrontEnd/AssignToDclnNormalize.hh>
#include <WG/Local/Detail/FrontEnd/BoundVarDclnNormalize.hh>
#include <WG/Local/Detail/FrontEnd/SetVarDclnNormalize.hh>

//###########
//Public APIs
//###########

// Expands to the following:
//   (assignto) { (BOOST_PP_NIL) | (normalized-bound-tuple) }
//   (return) { (return_nrmlzd_type) }
//   (parambind) { (BOOST_PP_NIL) | ( {normalized-bound-tuple}+ ) }
//   (paramset) { (BOOST_PP_NIL) | ( {normalized-set-tuple}+ ) }
//   (membind) { (BOOST_PP_NIL) | ( {normalized-bound-tuple}+ ) }
//   (memset) { (BOOST_PP_NIL) | ( {normalized-set-tuple}+ ) }
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE(spec) \
  WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_IMPL(spec BOOST_PP_NIL)

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

#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_IMPL(spec) \
  WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_ASSIGNTO( \
    BOOST_PP_IIF( \
      WG_PP_TOKENS_STARTWITH_VOID(spec), \
      WG_PP_TOKENS_EAT_HEADKEYWORD(spec), \
      spec) )

#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZEIMPL_MACRONAME( \
  spec, currentkeyword, nextkeyword) \
    BOOST_PP_CAT( \
      WG_PP_AUTOFUNCTOR_SPEC_NORMALIZEIMPL_MACRONAME_IMPL, \
      BOOST_PP_CAT(WG_PP_TOKENS_STARTWITH_, currentkeyword) (spec)) \
      (spec, currentkeyword, nextkeyword)
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZEIMPL_MACRONAME_IMPL0( \
  spec, currentkeyword, nextkeyword) \
    BOOST_PP_CAT( \
      WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_NOTFOUNDHOOK_, currentkeyword) () \
    BOOST_PP_CAT( \
      WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_, nextkeyword)
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZEIMPL_MACRONAME_IMPL1( \
  spec, currentkeyword, nextkeyword) \
    BOOST_PP_CAT(WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_SEQ_, currentkeyword)

#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZEIMPL_MACROPARAMS( \
  spec, currentkeyword, nextkeyword) \
    BOOST_PP_CAT( \
      WG_PP_AUTOFUNCTOR_SPEC_NORMALIZEIMPL_MACROPARAMS_IMPL, \
      BOOST_PP_CAT(WG_PP_TOKENS_STARTWITH_, currentkeyword) (spec)) \
      (spec, currentkeyword, nextkeyword)
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZEIMPL_MACROPARAMS_IMPL0( \
  spec, currentkeyword, nextkeyword) \
    (spec)
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZEIMPL_MACROPARAMS_IMPL1( \
  spec, currentkeyword, nextkeyword) \
    (spec, \
     BOOST_PP_CAT( \
      WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_, \
      nextkeyword))

//------------------------------------------------------------------------------
// WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_<keyword>
// Algorithm Overview:
//   If head token matches <keyword>
//     then dispatch to WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_SEQ<keyword>
//     else call WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_NOTFOUNDHOOK_<keyword> and
//       then dispatch to WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_<next_keyword>
//------------------------------------------------------------------------------
// Implementation Note:
// WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_SEQ_...2 cannot be factored out into a
//   common macro because it will result in an eventual recursive call of itself.
// WG_PP_SPLITHEADTUPLEFROMTOKENS cannot apply nexttransform to the rest of
//   the tokens because it will result in an eventual recursive call of itself.
//------------------------------------------------------------------------------

#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_ASSIGNTO(spec) \
  (assignto) \
  WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_EXPAND1( \
    WG_PP_AUTOFUNCTOR_SPEC_NORMALIZEIMPL_MACRONAME(spec, ASSIGNTO, RETURN) \
    WG_PP_AUTOFUNCTOR_SPEC_NORMALIZEIMPL_MACROPARAMS(spec, ASSIGNTO, RETURN) )
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_NOTFOUNDHOOK_ASSIGNTO() \
  (BOOST_PP_NIL)
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_SEQ_ASSIGNTO(spec, nexttransform) \
  WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_SEQ_ASSIGNTO2( \
    WG_PP_SPLITHEADTUPLEFROMTOKENS( \
      1, \
      WG_PP_TOKENS_EAT_HEADKEYWORD(spec), \
      WG_PP_ASSIGNTODCLN_NORMALIZE, \
      WG_PP_TUPLIZE, \
      WG_PP_TUPLIZE), \
    nexttransform)
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_SEQ_ASSIGNTO2( \
  head_rest_tuple, nexttransform) \
    ( BOOST_PP_SEQ_ELEM(0, head_rest_tuple) ) \
    nexttransform( BOOST_PP_SEQ_ELEM(1, head_rest_tuple) )

#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_RETURN(spec) \
  (return) \
  WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_EXPAND2( \
    WG_PP_AUTOFUNCTOR_SPEC_NORMALIZEIMPL_MACRONAME(spec, RETURN, PARAMBIND) \
    WG_PP_AUTOFUNCTOR_SPEC_NORMALIZEIMPL_MACROPARAMS(spec, RETURN, PARAMBIND) )
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_NOTFOUNDHOOK_RETURN() \
  (void)
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_SEQ_RETURN(spec, nexttransform) \
  WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_SEQ_RETURN2( \
    WG_PP_SPLITHEADTUPLEFROMTOKENS( \
      1, \
      WG_PP_TOKENS_EAT_HEADKEYWORD(spec), \
      WG_PP_IDENTITY, \
      WG_PP_TUPLIZE, \
      WG_PP_TUPLIZE), \
    nexttransform)
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_SEQ_RETURN2( \
  head_rest_tuple, nexttransform) \
    ( BOOST_PP_SEQ_ELEM(0, head_rest_tuple) ) \
    nexttransform( BOOST_PP_SEQ_ELEM(1, head_rest_tuple) )

#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_PARAMBIND(spec) \
  (parambind) \
  WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_EXPAND3( \
    WG_PP_AUTOFUNCTOR_SPEC_NORMALIZEIMPL_MACRONAME(spec, PARAMBIND, PARAMSET) \
    WG_PP_AUTOFUNCTOR_SPEC_NORMALIZEIMPL_MACROPARAMS(spec, PARAMBIND, PARAMSET) )
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_NOTFOUNDHOOK_PARAMBIND() \
  (BOOST_PP_NIL)
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_SEQ_PARAMBIND(spec, nexttransform) \
  WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_SEQ_PARAMBIND2( \
    WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
      1, \
      WG_PP_TOKENS_EAT_HEADKEYWORD(spec), \
      WG_PP_BOUNDVARDCLN_NORMALIZE, \
      WG_PP_TUPLIZE, \
      WG_PP_TUPLIZE), \
    nexttransform)
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_SEQ_PARAMBIND2( \
  head_rest_tuple, nexttransform) \
    ( BOOST_PP_SEQ_ELEM(0, head_rest_tuple) ) \
    nexttransform( BOOST_PP_SEQ_ELEM(1, head_rest_tuple) )

#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_PARAMSET(spec) \
  (paramset) \
  WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_EXPAND4( \
    WG_PP_AUTOFUNCTOR_SPEC_NORMALIZEIMPL_MACRONAME(spec, PARAMSET, MEMBIND) \
    WG_PP_AUTOFUNCTOR_SPEC_NORMALIZEIMPL_MACROPARAMS(spec, PARAMSET, MEMBIND) )
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_NOTFOUNDHOOK_PARAMSET() \
  (BOOST_PP_NIL)
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_SEQ_PARAMSET(spec, nexttransform) \
  WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_SEQ_PARAMSET2( \
    WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
      2, \
      WG_PP_TOKENS_EAT_HEADKEYWORD(spec), \
      WG_PP_SETVARDCLNNORMALIZE, \
      WG_PP_TUPLIZE, \
      WG_PP_TUPLIZE), \
    nexttransform)
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_SEQ_PARAMSET2( \
  head_rest_tuple, nexttransform) \
    ( BOOST_PP_SEQ_ELEM(0, head_rest_tuple) ) \
    nexttransform( BOOST_PP_SEQ_ELEM(1, head_rest_tuple) )

#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_MEMBIND(spec) \
  (membind) \
  WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_EXPAND5( \
    WG_PP_AUTOFUNCTOR_SPEC_NORMALIZEIMPL_MACRONAME(spec, MEMBIND, MEMSET) \
    WG_PP_AUTOFUNCTOR_SPEC_NORMALIZEIMPL_MACROPARAMS(spec, MEMBIND, MEMSET) )
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_NOTFOUNDHOOK_MEMBIND() \
  (BOOST_PP_NIL)
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_SEQ_MEMBIND(spec, nexttransform) \
  WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_SEQ_MEMBIND2( \
    WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
      1, \
      WG_PP_TOKENS_EAT_HEADKEYWORD(spec), \
      WG_PP_BOUNDVARDCLN_NORMALIZE, \
      WG_PP_TUPLIZE, \
      WG_PP_TUPLIZE), \
    nexttransform)
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_SEQ_MEMBIND2( \
  head_rest_tuple, nexttransform) \
    ( BOOST_PP_SEQ_ELEM(0, head_rest_tuple) ) \
    nexttransform( BOOST_PP_SEQ_ELEM(1, head_rest_tuple) )

#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_MEMSET(spec) \
  (memset) \
  WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_EXPAND6( \
    WG_PP_AUTOFUNCTOR_SPEC_NORMALIZEIMPL_MACRONAME(spec, MEMSET, ENDSPEC) \
    WG_PP_AUTOFUNCTOR_SPEC_NORMALIZEIMPL_MACROPARAMS(spec, MEMSET, ENDSPEC) )
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_NOTFOUNDHOOK_MEMSET() \
  (BOOST_PP_NIL)
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_SEQ_MEMSET(spec, nexttransform) \
  WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_SEQ_MEMSET2( \
    WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
      2, \
      WG_PP_TOKENS_EAT_HEADKEYWORD(spec), \
      WG_PP_SETVARDCLNNORMALIZE, \
      WG_PP_TUPLIZE, \
      WG_PP_TUPLIZE), \
    nexttransform)
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_SEQ_MEMSET2( \
  head_rest_tuple, nexttransform) \
    ( BOOST_PP_SEQ_ELEM(0, head_rest_tuple) ) \
    nexttransform( BOOST_PP_SEQ_ELEM(1, head_rest_tuple) )

#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_ENDSPEC(spec) \
  WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_VALIDATESPEC(spec)

// To be called after an attempt to parse the complete spec.
//   If the remaining spec is not BOOST_PP_NIL, then the head token(s) should
//   be a good indicator of where things went wrong.
#define WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE_VALIDATESPEC(spec) \
  BOOST_PP_EXPR_IIF( \
    BOOST_PP_NOT( \
      WG_PP_TOKENS_START_WITH_BOOST_PP_NIL(spec)), \
    BOOST_PP_ASSERT_MSG( \
      0, "ERROR: Invalid token(s): (Excluding trailing BOOST_PP_NIL)" \
    BOOST_PP_ASSERT_MSG( \
      0, BOOST_PP_STRINGIZE(spec)) ))

#endif /* WG_PP_AUTOFUNCTOR_SPECNORMALIZE_HH_ */
