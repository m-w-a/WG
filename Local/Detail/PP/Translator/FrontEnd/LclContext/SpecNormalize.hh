#ifndef WG_PP_LCLCONTEXT_SPECNORMALIZE_HH_
#define WG_PP_LCLCONTEXT_SPECNORMALIZE_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/LclContext/Keywords.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/BoundVarDclnNormalize.hh>
#include <WG/Local/Detail/PP/Translator/LclContext/Names.hh>

// Expands to the following:
//   (istplmarker) (0 | 1)
//   (isnoex) (0 | )
//   (withasmrkr) ( withas_dcln_seq )
//   (withadhocmrkr) ( withadhoc_dcln_seq )
//   (enteredasmrkr) ( orderedenteredas_seq )
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
  (withasmrkr)  \
  ( WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_WITHAS(whilestate, ~) ) \
  (withadhocmrkr) \
  ( WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_WITHADHOC(whilestate, ~) ) \
  (enteredasmrkr) \
  ( WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ENTEREDASOBJS(whilestate, ~) )

//~~~~~~~~~~~~~~
// Parser::State
//~~~~~~~~~~~~~~

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_INITSTATE(spec, specoptions) \
  ( (specoptions), BOOST_PP_NIL, BOOST_PP_NIL, BOOST_PP_NIL, spec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATEELEM(indx, state) \
  BOOST_PP_TUPLE_ELEM(5, indx, state)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_SPECOPTIONS(\
  state, ignored) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATEELEM(0, state)
#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_WITHAS( \
  state, ignored) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATEELEM(1, state)
#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_WITHADHOC( \
  state, ignored) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATEELEM(2, state)
#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ENTEREDASOBJS( \
  state, ignored) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATEELEM(3, state)
#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_RESTSPEC( \
  state, ignored) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATEELEM(4, state)

// withasdcln:
//   See withas-dcln in SymbolTable.
#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_WITHASDCLN( \
  state, withasdcln, restspec) \
    ( \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_SPECOPTIONS(state, ~), \
      WG_PP_SEQ_JOIN_ARG2( \
        WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_WITHAS(state, ~), \
        (withasdcln) ), \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_WITHADHOC(state, ~), \
      WG_PP_SEQ_JOIN_ARG2( \
        WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ENTEREDASOBJS(state, ~), \
        WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_WITHASDCLN_ENTEREDASOBJ( \
          state, withasdcln) ), \
      restspec \
    )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_WITHASDCLN_ENTEREDASOBJ( \
  state, withasdcln) \
    BOOST_PP_IIF( \
      BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(withasdcln), 4), \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_WITHASDCLN_ENTEREDASOBJ4, \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_WITHASDCLN_ENTEREDASOBJ2) \
    (state, withasdcln)
#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_WITHASDCLN_ENTEREDASOBJ4( \
  state, withasdcln) \
    ( \
      ( BOOST_PP_SEQ_ELEM(1, withasdcln) ) \
      ( BOOST_PP_SEQ_ELEM(3, withasdcln) ) \
      ( \
        WG_PP_SEQ_SIZE( \
          WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_WITHAS(state, ~) ) \
      ) \
    )
#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_WITHASDCLN_ENTEREDASOBJ2( \
  state, withasdcln) \
    ( \
      ( BOOST_PP_SEQ_ELEM(1, withasdcln) ) \
    )

// withadhocdcln:
//   See withadhoc-dcln in SymbolTable.
#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_WITHADHOCDCLN( \
  state, withadhocdcln, restspec) \
    ( \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_SPECOPTIONS(state, ~), \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_WITHAS(state, ~), \
      WG_PP_SEQ_JOIN_ARG2( \
        WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_WITHADHOC(state, ~), \
        (withadhocdcln) ), \
      WG_PP_SEQ_JOIN_ARG2( \
        WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ENTEREDASOBJS(state, ~), \
        ( \
          WG_PP_LCLCONTEXT_NAMES_ADHOCCNTXTMNGR_OBJ( \
            WG_PP_SEQ_SIZE( \
              WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_WITHADHOC(state, ~))) \
        ) ), \
      restspec \
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
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHAS1, \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP3) (state, spec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP3(state, spec) \
  BOOST_PP_IIF( \
    WG_PP_LCLCONTEXT_KEYWORDS_STARTSWITH_WITHADHOC(spec), \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHADHOC1, \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP3_ERROR ) (state, spec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP3_ERROR(state, spec) \
  WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_WITHASDCLN( \
    state, \
    (WG_PP_MARKER_ERROR BOOST_PP_CAT(Error_unrecognized_tokenXXX,spec))(BOOST_PP_NIL), \
    BOOST_PP_NIL)

//~~~~~~~~~~~~~~~~~~~
// Parser::Op::WithAs
//~~~~~~~~~~~~~~~~~~~

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHAS1( \
  state, spec) \
    WG_PP_LCLCONTEXT_SPECPARSER_EXPAND2( \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHAS2 \
      BOOST_PP_LPAREN() \
        state BOOST_PP_COMMA() \
        WG_PP_ADDCOMMA_AFTERTUPLE_ARITY1 \
        WG_PP_LCLCONTEXT_KEYWORDS_EAT_HEADKEYWORD(spec) \
      BOOST_PP_RPAREN() )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHAS2( \
  state, with_tuple, spec) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHAS5 \
    ( \
      state, \
      (with_tuple) \
      BOOST_PP_IIF( \
        WG_PP_LCLCONTEXT_KEYWORDS_STARTSWITH_AS(spec), \
        WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHAS3, \
        WG_PP_TUPLIZE_ARG1) (spec) \
    )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHAS3(spec) \
  WG_PP_LCLCONTEXT_SPECPARSER_EXPAND3( \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHAS4 \
    BOOST_PP_LPAREN() \
      WG_PP_ADDCOMMA_AFTERTUPLE_ARITY1 \
      WG_PP_LCLCONTEXT_KEYWORDS_EAT_HEADKEYWORD(spec) \
    BOOST_PP_RPAREN() )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHAS4( \
  as_tuple, restspec) \
    (as_tuple)(restspec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHAS5( \
  state, withtuple_astuple_restspec) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_WITHASDCLN( \
      state, \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHAS_WITHASDCLN( \
        WG_PP_LCLCONTEXT_SPECPARSER_SPECOPTIONS_ISTPL( \
          WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_SPECOPTIONS(state)), \
        withtuple_astuple_restspec), \
      BOOST_PP_SEQ_ELEM(2, withtuple_astuple_restspec) )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHAS_WITHASDCLN( \
  istpl, withtuple_astuple_restspec) \
    WG_PP_LCLCONTEXT_SPECPARSER_CHOOSE_TPL( \
      WG_PP_BOUNDVARDCLN_NORMALIZE, istpl) \
        ( BOOST_PP_SEQ_ELEM(0, withtuple_astuple_restspec) ) \
    BOOST_PP_IIF( \
      BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(withtuple_astuple_restspec), 3), \
      WG_PP_LCLCONTEXT_SPECPARSER_CHOOSE_TPL(WG_PP_BOUNDVARDCLN_NORMALIZE, istpl), \
      WG_PP_MAPTO_NOTHING_ARG1) \
    ( BOOST_PP_SEQ_ELEM(1, withtuple_astuple_restspec) )

//~~~~~~~~~~~~~~~~~~~~~
//Parser::Op::WithAdhoc
//~~~~~~~~~~~~~~~~~~~~~

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHADHOC1(state, spec) \
  WG_PP_LCLCONTEXT_SPECPARSER_EXPAND4( \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHADHOC2 \
    BOOST_PP_LPAREN() \
      state BOOST_PP_COMMA() \
      WG_PP_SPLITHEADTUPLESEQFROMTOKENS( \
        1, \
        WG_PP_LCLCONTEXT_KEYWORDS_EAT_HEADKEYWORD(spec), \
        WG_PP_LCLCONTEXT_SPECPARSER_CHOOSE_TPL( \
          WG_PP_BOUNDVARDCLN_NORMALIZE, \
          WG_PP_LCLCONTEXT_SPECPARSER_SPECOPTIONS_ISTPL( \
            WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_SPECOPTIONS(state) )), \
        WG_PP_TUPLIZE_ARG1, \
        WG_PP_IDENTITY) \
    BOOST_PP_RPAREN() )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHADHOC2( \
  state, withadhoctuple, spec) \
    BOOST_PP_IIF( \
      WG_PP_LCLCONTEXT_KEYWORDS_STARTSWITH_ONENTER(spec), \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHADHOC_ONENTER, \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHADHOC_SYNONENTER) \
    (state, withadhoctuple, spec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHADHOC_ONENTER( \
  state, withadhoctuple, spec) \
    WG_PP_LCLCONTEXT_SPECPARSER_EXPAND5( \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHADHOC3 \
      BOOST_PP_LPAREN() \
        state BOOST_PP_COMMA() \
        1 BOOST_PP_COMMA() \
        withadhoctuple \
        WG_PP_SPLITHEADTUPLEFROMTOKENS( \
          1, \
          WG_PP_LCLCONTEXT_KEYWORDS_EAT_HEADKEYWORD(spec), \
          WG_PP_TUPLIZE_ARG1, \
          WG_PP_IDENTITY, \
          WG_PP_IDENTITY) \
      BOOST_PP_RPAREN() )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHADHOC_SYNONENTER( \
  state, withadhoctuple, spec) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHADHOC3( \
      state, \
      0, \
      withadhoctuple ( return ; ), \
      spec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHADHOC3( \
  state, specifiedfunccount, withadhocpartialdcln, spec) \
    BOOST_PP_IIF( \
      WG_PP_LCLCONTEXT_KEYWORDS_STARTSWITH_ONEXIT(spec), \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHADHOC_ONEXIT, \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHADHOC_SYNONEXIT) \
    (state, specifiedfunccount, withadhocpartialdcln, spec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHADHOC_ONEXIT( \
  state, specifiedfunccount, withadhocpartialdcln, spec) \
    WG_PP_LCLCONTEXT_SPECPARSER_EXPAND6(\
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHADHOC4 \
      BOOST_PP_LPAREN() \
        state BOOST_PP_COMMA() \
        BOOST_PP_INC(specifiedfunccount) BOOST_PP_COMMA() \
        withadhocpartialdcln \
        WG_PP_SPLITHEADTUPLEFROMTOKENS( \
          1, \
          WG_PP_LCLCONTEXT_KEYWORDS_EAT_HEADKEYWORD(spec), \
          WG_PP_TUPLIZE_ARG1, \
          WG_PP_IDENTITY, \
          WG_PP_IDENTITY) \
      BOOST_PP_RPAREN() )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHADHOC_SYNONEXIT( \
  state, specifiedfunccount, withadhocpartialdcln, spec) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHADHOC4( \
      state, \
      specifiedfunccount, \
      withadhocpartialdcln ( return ; ), \
      spec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHADHOC4( \
  state, specifiedfunccount, withadhocdcln, restspec) \
    BOOST_PP_IIF( \
      BOOST_PP_EQUAL(specifiedfunccount, 0), \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHADHOC_ERROR, \
      WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_WITHADHOCDCLN) \
    (state, withadhocdcln, restspec)

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHADHOC_ERROR( \
  state, withadhocdcln, restspec) \
    WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_STATE_ADD_WITHADHOCDCLN( \
      state, \
      ( \
        ( \
          ( \
            WG_PP_MARKER_ERROR \
            WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHADHOC_ERROR_MSG() \
          ) \
          ( void ) \
        ) \
      ) \
      (BOOST_PP_NIL) \
      (BOOST_PP_NIL), \
      BOOST_PP_NIL )

#define WG_PP_LCLCONTEXT_SPECPARSER_WHILELOOP_OP_WITHADHOC_ERROR_MSG() \
  Error_withadhoc_requires_at_least_one_of_onenter_or_onexit_needs_to_be_specified

#endif /* WG_PP_LCLCONTEXT_SPECNORMALIZE_HH_ */
