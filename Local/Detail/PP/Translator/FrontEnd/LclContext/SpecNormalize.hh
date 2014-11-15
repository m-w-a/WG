#ifndef WG_PP_LCLCONTEXT_SPECNORMALIZE_HH_
#define WG_PP_LCLCONTEXT_SPECNORMALIZE_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/LclContext/Keywords.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/BoundVarDclnNormalize.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/SplitHeadFromTokens.hh>

// Expands to the following:
//   (extantsymblcount) (unsigned-integer)
//   (adhocsymblcount) (unsigned-integer)
//   (symblsmarker) (marked-symbol-seq)
//
// marked-symbol-seq :=
//     marked-symbol-tuple
//   | marked-symbol-seq marked-symbol-tuple
//
// symbol-tuple :=
//     ( marker symbol )
//   | ( marker error-token )
//
// marker := WG_PP_MARKER_NOOP | WG_PP_MARKER_ERROR
//
// error-token := Some token(s).
//
// What ever terms not defined here are defined in SymbolTable.hh
#define WG_PP_LCLCONTEXT_SPECPARSER_PARSE(spec, istpl) \
  WG_PP_LCLCONTEXT_SPECPARSER_PARSE_IMPL(spec, istpl)

//###########
//Impl Macros
//###########

#define WG_PP_LCLCONTEXT_SPECPARSER_PARSE_IMPL(spec, istpl) \
  WG_PP_LCLCONTEXT_SPECPARSER_PARSE_INTO_INTERNALFORMAT( \
    spec BOOST_PP_NIL, \
    WG_PP_LCLCONTEXT_SPECPARSER_SPECOPTIONS_MAKE(istpl) )

//------
// Utils
//------

#define WG_PP_LCLCONTEXT_SPECPARSER_EXPAND1(x) x
#define WG_PP_LCLCONTEXT_SPECPARSER_EXPAND2(x) x
#define WG_PP_LCLCONTEXT_SPECPARSER_EXPAND3(x) x
#define WG_PP_LCLCONTEXT_SPECPARSER_EXPAND4(x) x
#define WG_PP_LCLCONTEXT_SPECPARSER_EXPAND5(x) x
#define WG_PP_LCLCONTEXT_SPECPARSER_EXPAND6(x) x
#define WG_PP_LCLCONTEXT_SPECPARSER_EXPAND7(x) x

#define WG_PP_LCLCONTEXT_SPECPARSER_SPECOPTIONS_MAKE(istpl) \
  (istpl)
#define WG_PP_LCLCONTEXT_SPECPARSER_SPECOPTIONS_ISTPL(specoptions) \
  BOOST_PP_SEQ_ELEM(0, specoptions)

#define WG_PP_LCLCONTEXT_SPECPARSER_CHOOSE_TPL(macro, specoptions) \
  BOOST_PP_IIF( \
    WG_PP_LCLCONTEXT_SPECPARSER_SPECOPTIONS_ISTPL(specoptions), \
    BOOST_PP_CAT(macro, _TPL), \
    macro)

//-------
// Parser
//-------

// spec: Expected to end with BOOST_PP_NIL
#define WG_PP_LCLCONTEXT_SPECPARSER_PARSE_INTO_INTERNALFORMAT(spec, specoptions) \
  WG_PP_LCLCONTEXT_SPECPARSER_PARSE_INTO_INTERNALFORMAT2( \
    BOOST_PP_WHILE( \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_PRED, \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP1, \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_INITSTATE(spec, specoptions) ) )

#define WG_PP_LCLCONTEXT_SPECPARSER_PARSE_INTO_INTERNALFORMAT2(whilestate) \
  (extantsymblcount) \
  ( WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_EXTANTCOUNT(whilestate) ) \
  (adhocsymblcount) \
  ( WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADHOCCOUNT(whilestate) ) \
  (symblsmarker) \
  ( \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_PARSEDSEQ(whilestate) \
  )

//~~~~~~~~~~~~~~
// Parser::State
//~~~~~~~~~~~~~~

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_INITSTATE(spec, specoptions) \
  ( specoptions, 0, 0, BOOST_PP_NIL, spec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATEELEM(indx, state) \
  BOOST_PP_TUPLE_ELEM(5, indx, state)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_SPECOPTIONS(state) \
  WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATEELEM(0, state)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_EXTANTCOUNT(state) \
  WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATEELEM(1, state)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADHOCCOUNT(state) \
  WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATEELEM(2, state)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_PARSEDSEQ(state) \
  WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATEELEM(3, state)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_RESTSPEC(state) \
  WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATEELEM(4, state)

// extantsymbol:
//   See SymbolTable.
#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_EXTANTSYMBOL( \
  state, extantsymbol, restspec) \
    ( \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_SPECOPTIONS(state), \
      BOOST_PP_INC( \
        WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_EXTANTCOUNT(state) ), \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADHOCCOUNT(state), \
      WG_PP_SEQ_JOIN_ARG2( \
        WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_PARSEDSEQ(state), \
        ( extantsymbol ) ), \
      restspec \
    )

// adhocsymbol:
//   See SymbolTable.
#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_ADHOCSYMBOL( \
  state, adhocsymbol, restspec) \
    ( \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_SPECOPTIONS(state), \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_EXTANTCOUNT(state), \
      BOOST_PP_INC( \
        WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADHOCCOUNT(state) ), \
      WG_PP_SEQ_JOIN_ARG2( \
        WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_PARSEDSEQ(state), \
        ( adhocsymbol ) ), \
      restspec \
    )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_PARSEERROR( \
  state, errortokens) \
    ( \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_SPECOPTIONS(state), \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_EXTANTCOUNT(state), \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADHOCCOUNT(state), \
      ( errortokens ), \
      BOOST_PP_NIL \
    )

//~~~~~~~~~~~~~~~~~~
// Parser::Predicate
//~~~~~~~~~~~~~~~~~~

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_PRED(d, state) \
  BOOST_PP_COMPL( \
    WG_PP_STARTSWITH_BOOST_PP_NIL( \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_RESTSPEC(state) ) )

//~~~~~~~~~~~
// Parser::Op
//~~~~~~~~~~~

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP1(d, state) \
  WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP2( \
    state, \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_RESTSPEC(state) )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP2(state, spec) \
  BOOST_PP_IIF( \
    WG_PP_LCLCONTEXT_KEYWORDS_STARTSWITH_WITH(spec), \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT, \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP3) (state, spec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP3(state, spec) \
  BOOST_PP_IIF( \
    WG_PP_LCLCONTEXT_KEYWORDS_STARTSWITH_WITHADHOC(spec), \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC, \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ERROR_UNRECOGNIZEDNAMEDPARAMETER ) \
  (state, spec)

#define \
  WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ERROR_UNRECOGNIZEDNAMEDPARAMETER( \
    state, spec) \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_PARSEERROR( \
        state, \
        WG_PP_MARKER_ERROR \
        BOOST_PP_CAT( \
          WG_LCLCONTEXT_Error_unrecognized_tokenXXX, \
          WG_PP_EATTAILTOKEN_BOOST_PP_NIL(spec) ) )

//~~~~~~~~~~~~~~~~~~~
// Parser::Op::WithAs
//~~~~~~~~~~~~~~~~~~~

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT( \
  state, spec) \
    WG_PP_LCLCONTEXT_SPECPARSER_EXPAND1( \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT2 \
      BOOST_PP_LPAREN() \
        state BOOST_PP_COMMA() \
        WG_PP_SPLITHEADTUPLEFROMTOKENS( \
          1, \
          WG_PP_LCLCONTEXT_KEYWORDS_EAT_HEADKEYWORD(spec), \
          WG_PP_TUPLIZE_ARG1, \
          WG_PP_ADDCOMMA_AFTERTOKENS, \
          WG_PP_IDENTITY_ARG1) \
      BOOST_PP_RPAREN() )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT2( \
  state, scopemngrtuple, spec) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_SAVESYMBOL \
    ( \
      state, \
      ( scopemngrtuple ) \
      BOOST_PP_IIF( \
        WG_PP_LCLCONTEXT_KEYWORDS_STARTSWITH_ENTERAS(spec), \
        WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_ENTEREDASDCLN, \
        (BOOST_PP_NIL) WG_PP_TUPLIZE_ARG1) \
      (spec) \
    )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_ENTEREDASDCLN(spec) \
  WG_PP_LCLCONTEXT_SPECPARSER_EXPAND2( \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_ENTEREDASDCLN2 \
    BOOST_PP_LPAREN() \
      WG_PP_SPLITHEADTUPLEFROMTOKENS( \
        1, \
        WG_PP_LCLCONTEXT_KEYWORDS_EAT_HEADKEYWORD(spec), \
        WG_PP_TUPLIZE_ARG1, \
        WG_PP_ADDCOMMA_AFTERTOKENS, \
        WG_PP_IDENTITY_ARG1) \
    BOOST_PP_RPAREN() )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_ENTEREDASDCLN2( \
  as_tuple, restspec) \
    as_tuple (restspec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_SAVESYMBOL( \
  state, scopemngrtuple_optionalasdcln_restspec) \
    WG_PP_LCLCONTEXT_SPECPARSER_EXPAND7( \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_SAVESYMBOL2 \
      BOOST_PP_LPAREN() \
        state BOOST_PP_COMMA() \
        BOOST_PP_SEQ_ENUM(scopemngrtuple_optionalasdcln_restspec) \
      BOOST_PP_RPAREN() )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_SAVESYMBOL2( \
  state, scopemngrtuple, optionalasdcln, restspec) \
    BOOST_PP_IIF( \
      WG_PP_STARTSWITH_BOOST_PP_NIL(optionalasdcln), \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_SAVESYMBOL_FINAL, \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_SAVESYMBOL3) \
    (state, scopemngrtuple, optionalasdcln, restspec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_SAVESYMBOL3( \
  state, scopemngrtuple, asdcln, restspec) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_SAVESYMBOL4( \
      state, \
      scopemngrtuple, \
      BOOST_PP_IIF( \
        WG_PP_LCLCONTEXT_SPECPARSER_SPECOPTIONS_ISTPL( \
          WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_SPECOPTIONS(state) ), \
        WG_PP_SETVARDCLN_NLT_NORMALIZE_TPL, \
        WG_PP_SETVARDCLN_NLT_NORMALIZE) \
      (asdcln, scopemngrtuple . enter() ), \
      restspec )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_SAVESYMBOL4( \
  state, scopemngrtuple, markedparsedastuple, restspec) \
    BOOST_PP_IIF( \
      WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_ERROR( \
        BOOST_PP_SEQ_ELEM(0, markedparsedastuple)), \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_ADDERROR, \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_SAVESYMBOL_FINAL) \
    ( \
      state, \
      scopemngrtuple, \
      WG_PP_TRNSLTR_MARKERS_EATHEADMARKER( \
        BOOST_PP_SEQ_ELEM(0, markedparsedastuple)), \
      restspec \
    )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_ADDERROR( \
  state, scopemngrtuple, errortuple, restspec) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_PARSEERROR( \
      state, \
      BOOST_PP_SEQ_ELEM(0, errortuple) )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_SAVESYMBOL_FINAL( \
  state, scopemngrtuple, optionalparsedsetvardcln, restspec) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_EXTANTSYMBOL( \
      state, \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_MAKESYMBOL( \
        state, scopemngrtuple, optionalparsedsetvardcln), \
      restspec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_MAKESYMBOL( \
  state, scopemngrtuple, optionalparsedsetvardcln) \
    WG_PP_MARKER_NOOP \
    ( WG_PP_LCLCONTEXT_SYMBOL_CATEGORY_EXTANT ) \
    ( 0 ) \
    ( WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_EXTANTCOUNT(state) ) \
    scopemngrtuple \
    ( optionalparsedsetvardcln )

//~~~~~~~~~~~~~~~~~~~~~
//Parser::Op::WithAdhoc
//~~~~~~~~~~~~~~~~~~~~~

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC(state, spec) \
  WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC5( \
    state, \
    BOOST_PP_IIF( \
      WG_PP_ISNEXTTOKEN_A_TUPLE( \
        1, WG_PP_LCLCONTEXT_KEYWORDS_EAT_HEADKEYWORD(spec) ), \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC_BOUNDVARDCLNS, \
      (BOOST_PP_NIL) WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC2) \
    (state, WG_PP_LCLCONTEXT_KEYWORDS_EAT_HEADKEYWORD(spec)) )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC_BOUNDVARDCLNS( \
  state, spec) \
    WG_PP_LCLCONTEXT_SPECPARSER_EXPAND3( \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC_BOUNDVARDCLNS2 \
      BOOST_PP_LPAREN() \
        state BOOST_PP_COMMA() \
        WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
          1, \
          spec, \
          WG_PP_TUPLIZE_ARG1, \
          WG_PP_ADDCOMMA_AFTERTOKENS, \
          WG_PP_IDENTITY_ARG1) \
      BOOST_PP_RPAREN() )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC_BOUNDVARDCLNS2( \
  state, boundvarseq, spec) \
    ( boundvarseq ) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC2(state, spec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC2(state, spec) \
  BOOST_PP_IIF( \
    WG_PP_LCLCONTEXT_KEYWORDS_STARTSWITH_ONENTER(spec), \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC_ONENTERDCLN, \
    (BOOST_PP_NIL) WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC3) \
  (state, spec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC_ONENTERDCLN(state, spec) \
  WG_PP_LCLCONTEXT_SPECPARSER_EXPAND4( \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC_ONENTERDCLN2 \
    BOOST_PP_LPAREN() \
      state BOOST_PP_COMMA() \
      WG_PP_SPLITHEADTUPLEFROMTOKENS( \
        1, \
        WG_PP_LCLCONTEXT_KEYWORDS_EAT_HEADKEYWORD(spec), \
        WG_PP_TUPLIZE_ARG1, \
        WG_PP_ADDCOMMA_AFTERTOKENS, \
        WG_PP_IDENTITY_ARG1) \
    BOOST_PP_RPAREN() )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC_ONENTERDCLN2( \
  state, onenterseq, spec) \
    ( onenterseq ) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC3(state, spec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC3(state, spec) \
  BOOST_PP_IIF( \
    WG_PP_LCLCONTEXT_KEYWORDS_STARTSWITH_ONEXIT(spec), \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC_ONEXITDCLN, \
    (BOOST_PP_NIL) WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC4) \
  (state, spec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC_ONEXITDCLN(state, spec) \
  WG_PP_SPLITHEADTUPLEFROMTOKENS( \
    1, \
    WG_PP_LCLCONTEXT_KEYWORDS_EAT_HEADKEYWORD(spec), \
    WG_PP_TUPLIZE_ARG1, \
    WG_PP_TUPLIZE_ARG1, \
    WG_PP_TUPLIZE_ARG1)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC4(state, spec) \
  ( spec )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC5( \
  state, varbindseqtuple_onenterseqtuple_onexitseqtuple_spectuple) \
    WG_PP_LCLCONTEXT_SPECPARSER_EXPAND5 ( \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC6 \
      BOOST_PP_LPAREN() \
        state BOOST_PP_COMMA() \
        BOOST_PP_SEQ_ENUM( \
          varbindseqtuple_onenterseqtuple_onexitseqtuple_spectuple) \
      BOOST_PP_RPAREN() )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC6( \
  state, varbindseq, onenterseq, onexitseq, spec) \
    BOOST_PP_IIF( \
      WG_PP_SEQ_ISNIL( \
        WG_PP_SEQ_JOIN_ARG2(onenterseq, onexitseq) ), \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC_ERROR_MISSINGHANDLER, \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC_SAVESYMBOL) \
    (state, varbindseq, onenterseq, onexitseq, spec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC_ERROR_MISSINGHANDLER( \
  state, varbindseq, onenterseq, onexitseq, spec) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_PARSEERROR( \
      state, \
      WG_PP_MARKER_ERROR WG_LCLCONTEXT_Error_adhoc_scope_manager_missing_handler)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC_SAVESYMBOL( \
  state, varbindseq, onenterseq, onexitseq, spec) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_ADHOCSYMBOL( \
      state, \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC_MAKESYMBOL( \
        state, varbindseq, onenterseq, onexitseq), \
      spec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC_MAKESYMBOL( \
  state, varbindseq, onenterseq, onexitseq) \
    WG_PP_MARKER_NOOP \
    ( WG_PP_LCLCONTEXT_SYMBOL_CATEGORY_ADHOC ) \
    ( 1 ) \
    ( WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADHOCCOUNT(state) ) \
    ( varbindseq ) \
    ( onenterseq ) \
    ( onexitseq )

#endif /* WG_PP_LCLCONTEXT_SPECNORMALIZE_HH_ */
