#ifndef WG_AUTOFUNCTION2_HH_
#define WG_AUTOFUNCTION2_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/Seq.hh>
#include <WG/Local/Detail/Keywords.hh>
#include <WG/Local/Detail/FrontEnd/SplitHeadFromTokens.hh>

//###########
//Public APIs
//###########

// Expands to the following:
//   (assignto) [(BOOST_PP_NIL) | (2tuple)]
//   (return) [(BOOST_PP_NIL) | (1tuple)]
//   (parambind) [(BOOST_PP_NIL) | (1tuple-seq-after-parambind-before-nxtkywd)]
//   (paramset) [(BOOST_PP_NIL) | (1tuple-seq-after-paramset-before-nxtkywd)]
//   (membind) [(BOOST_PP_NIL) | (1tuple-seq-after-membind-before-nxtkywd)]
//   (memset) [(BOOST_PP_NIL) | (1tuple-seq-after-memset-before-nxtkywd)]
#define WG_PP_AUTOFUNCTION_SPEC_PROCESS(spec) \
  WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_ASSIGNTO(spec BOOST_PP_NIL)

//###########
//Impl Macros
//###########

// Need to use these instead of BOOST_PP_EXPAND because for some reason the 
//  latter prevents the macro expansion of nested BOOST_PP_EXPANDs
#define WG_PP_AUTOFUNCTION_EXPAND1(x) x
#define WG_PP_AUTOFUNCTION_EXPAND2(x) x
#define WG_PP_AUTOFUNCTION_EXPAND3(x) x
#define WG_PP_AUTOFUNCTION_EXPAND4(x) x
#define WG_PP_AUTOFUNCTION_EXPAND5(x) x
#define WG_PP_AUTOFUNCTION_EXPAND6(x) x

#define WG_PP_AUTOFUNCTION_PROCESSIFHEADIMPL_MACRONAME( \
  spec, currentkeyword, nextkeyword) \
    BOOST_PP_CAT( \
      WG_PP_AUTOFUNCTION_PROCESSIFHEADIMPL_MACRONAME_IMPL, \
      BOOST_PP_CAT(WG_PP_TOKENS_STARTWITH_, currentkeyword) (spec)) \
      (spec, currentkeyword, nextkeyword)
#define WG_PP_AUTOFUNCTION_PROCESSIFHEADIMPL_MACRONAME_IMPL0( \
  spec, currentkeyword, nextkeyword) \
    (BOOST_PP_NIL) \
      BOOST_PP_CAT(WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_, nextkeyword)
#define WG_PP_AUTOFUNCTION_PROCESSIFHEADIMPL_MACRONAME_IMPL1( \
  spec, currentkeyword, nextkeyword) \
    BOOST_PP_CAT(WG_PP_AUTOFUNCTION_PROCESS_, currentkeyword)

#define WG_PP_AUTOFUNCTION_PROCESSIFHEADIMPL_MACROPARAMS( \
  spec, currentkeyword, nextkeyword) \
    BOOST_PP_CAT( \
      WG_PP_AUTOFUNCTION_PROCESSIFHEADIMPL_MACROPARAMS_IMPL, \
      BOOST_PP_CAT(WG_PP_TOKENS_STARTWITH_, currentkeyword) (spec)) \
      (spec, currentkeyword, nextkeyword)
#define WG_PP_AUTOFUNCTION_PROCESSIFHEADIMPL_MACROPARAMS_IMPL0( \
  spec, currentkeyword, nextkeyword) \
    (spec)
#define WG_PP_AUTOFUNCTION_PROCESSIFHEADIMPL_MACROPARAMS_IMPL1( \
  spec, currentkeyword, nextkeyword) \
    (spec, \
     BOOST_PP_CAT( \
      WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_, \
      nextkeyword))

//------------------------------------------------------------------------------
// WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_<...>
// Algorithm Overview:
//   If head token matches <keyword>
//     then process tokens upto nextkeyword, and apply transform to rest of 
//       tokens starting from nextkeyword.
//     else output (BOOST_PP_NIL) and apply transform to rest of tokens 
//       starting from nextkeyword.
//------------------------------------------------------------------------------

#define WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_ASSIGNTO(spec) \
  (assignto) \
  WG_PP_AUTOFUNCTION_EXPAND1( \
    WG_PP_AUTOFUNCTION_PROCESSIFHEADIMPL_MACRONAME(spec, ASSIGNTO, RETURN) \
    WG_PP_AUTOFUNCTION_PROCESSIFHEADIMPL_MACROPARAMS(spec, ASSIGNTO, RETURN) )
#define WG_PP_AUTOFUNCTION_PROCESS_ASSIGNTO(spec, nexttransform) \
  WG_PP_SPLITHEADTUPLEFROMTOKENS( \
    2, WG_PP_TOKENS_EAT_HEADKEYWORD(spec), WG_PP_TUPLIZE, nexttransform)

#define WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_RETURN(spec) \
  (return) \
  WG_PP_AUTOFUNCTION_EXPAND2( \
    WG_PP_AUTOFUNCTION_PROCESSIFHEADIMPL_MACRONAME(spec, RETURN, PARAMBIND) \
    WG_PP_AUTOFUNCTION_PROCESSIFHEADIMPL_MACROPARAMS(spec, RETURN, PARAMBIND) )
#define WG_PP_AUTOFUNCTION_PROCESS_RETURN(spec, nexttransform) \
  WG_PP_SPLITHEADTUPLEFROMTOKENS( \
    1, WG_PP_TOKENS_EAT_HEADKEYWORD(spec), WG_PP_TUPLIZE, nexttransform)

#define WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_PARAMBIND(spec) \
  (parambind) \
  WG_PP_AUTOFUNCTION_EXPAND3( \
    WG_PP_AUTOFUNCTION_PROCESSIFHEADIMPL_MACRONAME(spec, PARAMBIND, PARAMSET) \
    WG_PP_AUTOFUNCTION_PROCESSIFHEADIMPL_MACROPARAMS(spec, PARAMBIND, PARAMSET) )
#define WG_PP_AUTOFUNCTION_PROCESS_PARAMBIND(spec, nexttransform) \
  WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
    1, WG_PP_TOKENS_EAT_HEADKEYWORD(spec), WG_PP_TUPLIZE, nexttransform)

#define WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_PARAMSET(spec) \
  (paramset) \
  WG_PP_AUTOFUNCTION_EXPAND4( \
    WG_PP_AUTOFUNCTION_PROCESSIFHEADIMPL_MACRONAME(spec, PARAMSET, MEMBIND) \
    WG_PP_AUTOFUNCTION_PROCESSIFHEADIMPL_MACROPARAMS(spec, PARAMSET, MEMBIND) )
#define WG_PP_AUTOFUNCTION_PROCESS_PARAMSET(spec, nexttransform) \
  WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
    2, WG_PP_TOKENS_EAT_HEADKEYWORD(spec), WG_PP_TUPLIZE, nexttransform)

#define WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_MEMBIND(spec) \
  (membind) \
  WG_PP_AUTOFUNCTION_EXPAND5( \
    WG_PP_AUTOFUNCTION_PROCESSIFHEADIMPL_MACRONAME(spec, MEMBIND, MEMSET) \
    WG_PP_AUTOFUNCTION_PROCESSIFHEADIMPL_MACROPARAMS(spec, MEMBIND, MEMSET) )
#define WG_PP_AUTOFUNCTION_PROCESS_MEMBIND(spec, nexttransform) \
  WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
    1, WG_PP_TOKENS_EAT_HEADKEYWORD(spec), WG_PP_TUPLIZE, nexttransform)

#define WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_MEMSET(spec) \
  (memset) \
  WG_PP_AUTOFUNCTION_EXPAND6( \
    WG_PP_AUTOFUNCTION_PROCESSIFHEADIMPL_MACRONAME(spec, MEMSET, ENDSPEC) \
    WG_PP_AUTOFUNCTION_PROCESSIFHEADIMPL_MACROPARAMS(spec, MEMSET, ENDSPEC) )
#define WG_PP_AUTOFUNCTION_PROCESS_MEMSET(spec, nexttransform) \
  WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
    2, WG_PP_TOKENS_EAT_HEADKEYWORD(spec), WG_PP_TUPLIZE, nexttransform)

#define WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_ENDSPEC(spec)


//Debugging Aide
#define T1 assignto (x, 7)
#define T2 return (float)
#define T3 parambind (b)
#define T4 parambind (b)(c)
#define T5 paramset (x, 7)
#define T6 paramset (x, 7) (y, 8)

#pragma wave trace(enable)
BOOST_PP_EXPAND(WG_PP_AUTOFUNCTION_SPEC_PROCESS(T1))
BOOST_PP_EXPAND(WG_PP_AUTOFUNCTION_SPEC_PROCESS(T2))
BOOST_PP_EXPAND(WG_PP_AUTOFUNCTION_SPEC_PROCESS(T3))
BOOST_PP_EXPAND(WG_PP_AUTOFUNCTION_SPEC_PROCESS(T4))
BOOST_PP_EXPAND(WG_PP_AUTOFUNCTION_SPEC_PROCESS(T5))
BOOST_PP_EXPAND(WG_PP_AUTOFUNCTION_SPEC_PROCESS(T6))
#pragma wave trace(disable)

//EXPECTED:
//See WG_PP_AUTOFUNCTION_SPEC_PROCESS description.


#endif /* WG_AUTOFUNCTION2_HH_ */
