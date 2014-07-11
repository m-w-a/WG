#ifndef WG_PP_LCLCONTEXT_SPECNORMALIZE_HH_
#define WG_PP_LCLCONTEXT_SPECNORMALIZE_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/LclContext/Keywords.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/BoundVarDclnNormalize.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/SplitHeadFromTokens.hh>
#include <WG/Local/Detail/PP/Translator/LclContext/Names.hh>

// Expands to the following:
//   (istplmarker) (0 | 1)
//   (isnoex) (0 | 1)
//   (symblsmarker) (symbolseq)
//
// symbolseq :=
//     symboltuple
//   | symbolseq symboltuple
//
// symboltuple :=
//    ( extantsymbol )
//  | ( adhocsymbol )
//
// extantsymbol :=
//   WG_PP_MARKER_NOOP
//   ( WG_PP_LCLCONTEXT_SCOPEMNGR_CATEGORY_WITHDCLN )
//   ( categoryno )
//   ( scopemngrseq )
//   ( nrmlzdenteredasseq )
//
// adhocsymbol :=
//   WG_PP_MARKER_NOOP
//   ( WG_PP_LCLCONTEXT_SCOPEMNGR_CATEGORY_WITHADHOCDCLN )
//   ( categoryno )
//   ( varbindseq )
//   ( onenterseq )
//   ( onexitseq )
//
// What ever terms not defined here are defined in SymbolTable.hh
#define WG_PP_LCLCONTEXT_SPECPARSER_PARSE(spec, istpl, isnoex) \
  WG_PP_LCLCONTEXT_SPECPARSER_PARSE_IMPL(spec, istpl, isnoex)

//###########
//Impl Macros
//###########

#define WG_PP_LCLCONTEXT_SPECPARSER_PARSE_IMPL(spec, istpl, isnoex) \
  (istplmrkr) (istpl) \
  (isnoexmrkr) (isnoex) \
  WG_PP_LCLCONTEXT_SPECPARSER_PARSE_INTO_INTERNALFORMAT( \
    spec BOOST_PP_NIL, \
    WG_PP_LCLCONTEXT_SPECPARSER_SPECOPTIONS_MAKE(istpl, isnoex) )

//------
// Utils
//------

#define WG_PP_LCLCONTEXT_SPECPARSER_EXPAND1(x) x
#define WG_PP_LCLCONTEXT_SPECPARSER_EXPAND2(x) x
#define WG_PP_LCLCONTEXT_SPECPARSER_EXPAND3(x) x
#define WG_PP_LCLCONTEXT_SPECPARSER_EXPAND4(x) x
#define WG_PP_LCLCONTEXT_SPECPARSER_EXPAND5(x) x
#define WG_PP_LCLCONTEXT_SPECPARSER_EXPAND6(x) x

#define WG_PP_LCLCONTEXT_SPECPARSER_SPECOPTIONS_MAKE(istpl, isnoex) \
  (istpl)(isnoex)
#define WG_PP_LCLCONTEXT_SPECPARSER_SPECOPTIONS_ISTPL(specoptions) \
  BOOST_PP_SEQ_ELEM(0, specoptions)
#define WG_PP_LCLCONTEXT_SPECPARSER_SPECOPTIONS_ISNOEX(specoptions) \
  BOOST_PP_SEQ_ELEM(1, specoptions)

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
  (symblsmarker) \
  ( \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_PARSEDSEQ(whilestate, ~) \
  )

//~~~~~~~~~~~~~~
// Parser::State
//~~~~~~~~~~~~~~

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_INITSTATE(spec, specoptions) \
  ( specoptions, 0, 0, BOOST_PP_NIL, spec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATEELEM(indx, state) \
  BOOST_PP_TUPLE_ELEM(5, indx, state)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_SPECOPTIONS(\
  state, ignored) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATEELEM(0, state)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_EXTANTCOUNT( \
  state, ignored) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATEELEM(1, state)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADHOCCOUNT( \
  state, ignored) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATEELEM(2, state)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_PARSEDSEQ( \
  state, ignored) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATEELEM(3, state)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_RESTSPEC( \
  state, ignored) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATEELEM(4, state)

// withasdcln:
//   See extantsymbol in SymbolTable.
#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_EXTANTSYMBOL( \
  state, withasdcln, restspec) \
    ( \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_SPECOPTIONS(state, ~), \
      BOOST_PP_INC( \
        WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_EXTANTCOUNT(state, ~) ), \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADHOCCOUNT(state, ~), \
      WG_PP_SEQ_JOIN_ARG2( \
        WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_PARSEDSEQ(state, ~), \
        ( withasdcln ) ), \
      restspec \
    )

// withadhocdcln:
//   See adhocsymbol in SymbolTable.
#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_ADHOCSYMBOL( \
  state, withadhocdcln, restspec) \
    ( \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_SPECOPTIONS(state, ~), \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_EXTANTCOUNT(state, ~), \
      BOOST_PP_INC( \
        WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADHOCCOUNT(state, ~) ), \
      WG_PP_SEQ_JOIN_ARG2( \
        WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_PARSEDSEQ(state, ~), \
        ( withadhocdcln ) ), \
      restspec \
    )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_PARSEERROR( \
  state, errortokens) \
    ( \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_SPECOPTIONS(state, ~), \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_EXTANTCOUNT(state, ~), \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADHOCCOUNT(state, ~), \
      ( errortokens ), \
      BOOST_PP_NIL \
    )

//~~~~~~~~~~~~~~~~~~
// Parser::Predicate
//~~~~~~~~~~~~~~~~~~

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_PRED(d, state) \
  BOOST_PP_COMPL( \
    WG_PP_STARTSWITH_BOOST_PP_NIL( \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_RESTSPEC( \
        state, ignore)))

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
        BOOST_PP_CAT(WG_LCLCONTEXT_Error_unrecognized_tokenXXX,spec) )

//~~~~~~~~~~~~~~~~~~~
// Parser::Op::WithAs
//~~~~~~~~~~~~~~~~~~~

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT( \
  state, spec) \
    WG_PP_LCLCONTEXT_SPECPARSER_EXPAND2( \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT2 \
      BOOST_PP_LPAREN() \
        state BOOST_PP_COMMA() \
        WG_PP_SPLITHEADTUPLEFROMTOKENS( \
          1, \
          WG_PP_LCLCONTEXT_KEYWORDS_EAT_HEADKEYWORD(spec), \
          WG_PP_TUPLIZE_ARG1, \
          WG_PP_ADDCOMMA_AFTERTUPLE_ARITY1, \
          WG_PP_IDENTITY_ARG1) \
      BOOST_PP_RPAREN() )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT2( \
  state, scopemngrtuple, spec) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_SAVESYMBOL \
    ( \
      state, \
      (scopemngrtuple) \
      BOOST_PP_IIF( \
        WG_PP_LCLCONTEXT_KEYWORDS_STARTSWITH_ENTEREDAS(spec), \
        WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_ENTEREDASDCLN, \
        (BOOST_PP_NIL) WG_PP_TUPLIZE_ARG1) (spec) \
    )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_ENTEREDASDCLN(spec) \
  WG_PP_LCLCONTEXT_SPECPARSER_EXPAND3( \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_ENTEREDASDCLN2 \
    BOOST_PP_LPAREN() \
      WG_PP_SPLITHEADTUPLEFROMTOKENS( \
        1, \
        WG_PP_LCLCONTEXT_KEYWORDS_EAT_HEADKEYWORD(spec), \
        WG_PP_TUPLIZE_ARG1, \
        WG_PP_ADDCOMMA_AFTERTUPLE_ARITY1, \
        WG_PP_IDENTITY_ARG1) \
    BOOST_PP_RPAREN() )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_ENTEREDASDCLN2( \
  as_tuple, restspec) \
    (as_tuple)(restspec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_SAVESYMBOL( \
  state, withseqtuple_asseqtuple_restspectuple) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_EXTANTSYMBOL( \
      state, \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_MAKESYMBOL( \
        WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_SPECOPTIONS(state), \
        WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_EXTANTCOUNT(state, ~), \
        withseqtuple_asseqtuple_restspectuple ), \
      BOOST_PP_SEQ_ELEM(2, withseqtuple_asseqtuple_restspectuple) )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_EXTANT_MAKESYMBOL( \
  specoptions, categoryno, withseqtuple_asseqtuple_restspectuple) \
    WG_PP_MARKER_NOOP \
    ( WG_PP_LCLCONTEXT_SCOPEMNGR_CATEGORY_WITHDCLN ) \
    ( categoryno ) \
    ( BOOST_PP_SEQ_ELEM(0, withseqtuple_asseqtuple_restspectuple) ) \
    ( \
      BOOST_PP_IIF( \
        WG_PP_SEQ_ISNIL(BOOST_PP_SEQ_ELEM(1, withseqtuple_asseqtuple_restspectuple)), \
        WG_PP_IDENTITY_ARG1, \
        WG_PP_LCLCONTEXT_SPECPARSER_CHOOSE_TPL( \
          WG_PP_BOUNDVARDCLN_NORMALIZE, specoptions)) \
      ( BOOST_PP_SEQ_ELEM(1, withseqtuple_asseqtuple_restspectuple) ) \
    )

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
    (state, spec) )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC_BOUNDVARDCLNS( \
  state, spec) \
    WG_PP_LCLCONTEXT_SPECPARSER_EXPAND4( \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC_BOUNDVARDCLNS2( \
      BOOST_PP_LPAREN() \
        state BOOST_PP_COMMA() \
        WG_PP_SPLITHEADTUPLEFROMTOKENS( \
          1, \
          WG_PP_LCLCONTEXT_KEYWORDS_EAT_HEADKEYWORD(spec), \
          WG_PP_TUPLIZE_ARG1, \
          WG_PP_ADDCOMMA_AFTERTUPLE_ARITY1, \
          WG_PP_IDENTITY_ARG1) \
      BOOST_PP_RPAREN() )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC_BOUNDVARDCLNS2( \
  state, boundvarseqtuple, spec) \
    boundvarseqtuple \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC2(state, spec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC2(state, spec) \
  BOOST_PP_IIF( \
    WG_PP_LCLCONTEXT_KEYWORDS_STARTSWITH_ONENTER(spec), \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC_ONENTERDCLN, \
    (BOOST_PP_NIL) WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC3) \
  (state, spec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC_ONENTERDCLN(state, spec) \
  WG_PP_LCLCONTEXT_SPECPARSER_EXPAND5( \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC_ONENTERDCLN2 \
    BOOST_PP_LPAREN() \
      state BOOST_PP_COMMA() \
      WG_PP_SPLITHEADTUPLEFROMTOKENS( \
        1, \
        WG_PP_LCLCONTEXT_KEYWORDS_EAT_HEADKEYWORD(spec), \
        WG_PP_TUPLIZE_ARG1, \
        WG_PP_ADDCOMMA_AFTERTUPLE_ARITY1, \
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
    WG_PP_LCLCONTEXT_SPECPARSER_EXPAND6 ( \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_ADHOC6 \
      BOOST_PP_LPAREN() \
        state BOOST_PP_COMMA() \
        BOOST_PP_ENUM(varbindseqtuple_onenterseqtuple_onexitseqtuple_spectuple) \
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
    ( WG_PP_LCLCONTEXT_SCOPEMNGR_CATEGORY_WITHADHOCDCLN ) \
    ( WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADHOCCOUNT(state, ~) \
    ( varbindseq ) \
    ( onenterseq ) \
    ( onexitseq ) )

#endif /* WG_PP_LCLCONTEXT_SPECNORMALIZE_HH_ */
