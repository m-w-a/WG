#ifndef WG_AUTOFUNCTION2_HH_
#define WG_AUTOFUNCTION2_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/Seq.hh>
#include <WG/Local/Detail/AltSeq.hh>
#include <WG/Local/Detail/Keywords.hh>
#include <WG/Local/Detail/ExpandN.hh>
#include <WG/Local/Detail/SplitHeadFromTokens.hh>

#define WG_PP_AUTOFUNCTION_SPEC_PROCESS(spec) \
  WG_PP_EXPANDN( \
    ( WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_ASSIGNTO(spec BOOST_PP_NIL) ), \
    4)

// Recursive macro emulation.
// This sets up a potentially recursive macro invocation without actually
//  invoking it by using BOOST_PP_[L|R]PAREN instead of '(' and ')' tokens.
//  The recursion is carried out when this macro is expand and reexpanded until
//  it can expand no further. (See
//  https://groups.google.com/group/comp.std.c/msg/8df0e3ae560adb3e?hl=en)
// Process spec if it's head token matches currentkeyword by passing control to
//  WG_PP_AUTOFUNCTION_PROCESS_<CURRENTKEYWORD>,
//  else call WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_<NEXTKEYWORD>
#define WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_IMPL( \
  spec, currentkeyword, nextkeyword) \
    BOOST_PP_IIF( \
      BOOST_PP_CAT(WG_PP_TOKENS_STARTS_WITH_, currentkeyword) (spec), \
      BOOST_PP_CAT(WG_PP_AUTOFUNCTION_PROCESS_, currentkeyword), \
      (BOOST_PP_NIL) \
      BOOST_PP_CAT(WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_, nextkeyword)) \
    BOOST_PP_LPAREN() \
      BOOST_PP_SEQ_ENUM( \
        BOOST_PP_IIF( \
          BOOST_PP_CAT(WG_PP_TOKENS_STARTS_WITH_, currentkeyword) (spec), \
          (spec) \
          (BOOST_PP_CAT( \
            WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_, \
            nextkeyword)), \
          (spec) )) \
    BOOST_PP_RPAREN()

// Well expand to comma(s) containing tokens.
#define WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_ASSIGNTO(spec) \
  WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_IMPL \
  BOOST_PP_LPAREN() spec, ASSIGNTO, RETURN BOOST_PP_RPAREN()
#define WG_PP_AUTOFUNCTION_PROCESS_ASSIGNTO(spec, nexttransform) \
  (assignto) \
  WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLEFROMTOKENS( \
    2, WG_PP_TOKENS_EAT_HEADKEYWORD(spec), BOOST_PP_COMMA, nexttransform)

#define WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_RETURN(spec) \
  WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_IMPL \
  BOOST_PP_LPAREN() spec, RETURN, PARAMBIND BOOST_PP_RPAREN()
#define WG_PP_AUTOFUNCTION_PROCESS_RETURN(spec, nexttransform) \
  (return) \
  WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLEFROMTOKENS( \
    1, WG_PP_TOKENS_EAT_HEADKEYWORD(spec), BOOST_PP_COMMA, nexttransform)

#define WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_PARAMBIND(spec) \
  WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_IMPL \
  BOOST_PP_LPAREN() spec, PARAMBIND, PARAMSET BOOST_PP_RPAREN()
#define WG_PP_AUTOFUNCTION_PROCESS_PARAMBIND(spec, nexttransform) \
  (parambind) \
  nexttransform \
  BOOST_PP_LPAREN() \
    WG_PP_TOKENS_EAT_HEADKEYWORD(spec) \
  BOOST_PP_RPAREN()

#define WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_PARAMSET(spec) \
  WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_IMPL \
  BOOST_PP_LPAREN() spec, PARAMSET, MEMBIND BOOST_PP_RPAREN()
#define WG_PP_AUTOFUNCTION_PROCESS_PARAMSET(spec, nextransform) \
  (paramset) \
  nexttransform \
  BOOST_PP_LPAREN() \
    WG_PP_TOKENS_EAT_HEADKEYWORD(spec) \
  BOOST_PP_RPAREN()

#define WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_MEMBIND(spec) \
  WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_IMPL \
  BOOST_PP_LPAREN() spec, MEMBIND, MEMSET BOOST_PP_RPAREN()
#define WG_PP_AUTOFUNCTION_PROCESS_MEMBIND(spec, nexttransform) \
  (membind) \
  nexttransform \
  BOOST_PP_LPAREN() \
    WG_PP_TOKENS_EAT_HEADKEYWORD(spec) \
  BOOST_PP_RPAREN()

#define WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_MEMSET(spec) \
  WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_IMPL \
  BOOST_PP_LPAREN() spec, MEMSET, ENDSPEC BOOST_PP_RPAREN()
#define WG_PP_AUTOFUNCTION_PROCESS_MEMSET(spec, nexttransform) \
  (memset) \
  nexttransform \
  BOOST_PP_LPAREN() \
    WG_PP_TOKENS_EAT_HEADKEYWORD(spec) \
  BOOST_PP_RPAREN()

#define WG_PP_AUTOFUNCTION_SPEC_PROCESSIFHEAD_ENDSPEC(spec)

#endif /* WG_AUTOFUNCTION2_HH_ */
