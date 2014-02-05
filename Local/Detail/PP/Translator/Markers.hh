#ifndef WG_LOCAL_DETAIL_TRANSLATOR_MARKERS_HH_
#define WG_LOCAL_DETAIL_TRANSLATOR_MARKERS_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/TokenMatching.hh>
#include <WG/Local/Detail/PP/Seq.hh>

//###########
//Public APIs
//###########

#define WG_PP_TRNSLTR_MARKERS_EATHEADMARKER(tokens) \
  WG_PP_TRNSLTR_MARKERS_EATHEADMARKER_IMPL(tokens)

#define WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_ERROR(tokens) \
  WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_ERROR_IMPL(tokens)

#define WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_DEDUCEDTYPE(tokens) \
  WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_DEDUCEDTYPE_IMPL(tokens)

#define WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_NOOP(tokens) \
  WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_NOOP_IMPL(tokens)

// WG_PP_STUTIL_REPLACESEQ callback.
// seq:
//   A WG_PP_SEQ.
// iteration:
//   See WG_PP_STUTIL_REPLACESEQ::callback
// dataseq:
//   { ( (gettypemacro)(settypemacro) ) }+
//
//   gettypemacro:
//     A one arg macro that when applied to an element of declnseq expands to
//     the type associated with that sequence.
//   settypemacro:
//     A two arg macro whose first arg takes an element of declnseq and whose
//     second arg takes some tokens.
//     The purpose of this macro is replace the type associated with the first
//     arg with the second arg.
#define WG_PP_TRNSLTR_MARKERS_ERASEMARKERSINSEQ(seq, iteration, dataseq) \
  WG_PP_TRNSLTR_MARKERS_ERASEMARKERSINSEQ_IMPL(seq, iteration, dataseq)

//###########
//Impl Macros
//###########

#define WG_PP_TRNSLTR_MARKERS_EATHEADMARKER_WG_PP_MARKER_ERROR
#define WG_PP_TRNSLTR_MARKERS_EATHEADMARKER_WG_PP_MARKER_DEDUCEDTYPE
#define WG_PP_TRNSLTR_MARKERS_EATHEADMARKER_WG_PP_MARKER_NOOP

#define WG_PP_TRNSLTR_MARKERS_EATHEADMARKER_IMPL(tokens) \
  BOOST_PP_CAT( \
    WG_PP_TRNSLTR_MARKERS_EATHEADMARKER_, \
    tokens)

//------------------
//WG_PP_MARKER_ERROR
//------------------

#define WG_PP_TRNSLTR_MARKERS_TOKENMATCH_BEGINSWITH_WG_PP_MARKER_ERROR_WG_PP_MARKER_ERROR \
  WG_PP_TOKENMATCH_FRONTMATCH
#define WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_ERROR_IMPL(tokens) \
  WG_PP_TOKENMATCH_BEGINSWITH(\
    tokens, \
    WG_PP_TRNSLTR_MARKERS_TOKENMATCH_BEGINSWITH_WG_PP_MARKER_ERROR_)

//------------------------
//WG_PP_MARKER_DEDUCEDTYPE
//------------------------

#define WG_PP_TRNSLTR_MARKERS_TOKENMATCH_BEGINSWITH_WG_PP_MARKER_DEDUCEDTYPE_WG_PP_MARKER_DEDUCEDTYPE \
  WG_PP_TOKENMATCH_FRONTMATCH
#define WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_DEDUCEDTYPE_IMPL(tokens) \
  WG_PP_TOKENMATCH_BEGINSWITH(\
    tokens, \
    WG_PP_TRNSLTR_MARKERS_TOKENMATCH_BEGINSWITH_WG_PP_MARKER_DEDUCEDTYPE_)

//-----------------
//WG_PP_MARKER_NOOP
//-----------------

#define WG_PP_TRNSLTR_MARKERS_TOKENMATCH_BEGINSWITH_WG_PP_MARKER_NOOP_WG_PP_MARKER_NOOP \
  WG_PP_TOKENMATCH_FRONTMATCH
#define WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_NOOP_IMPL(tokens) \
  WG_PP_TOKENMATCH_BEGINSWITH(\
    tokens, \
    WG_PP_TRNSLTR_MARKERS_TOKENMATCH_BEGINSWITH_WG_PP_MARKER_NOOP_)

//---------------------------------------
//WG_PP_TRNSLTR_MARKERS_ERASEMARKERSINSEQ
//---------------------------------------

#define WG_PP_TRNSLTR_MARKERS_ERASEMARKERSINSEQ_IMPL(seq, iteration, dataseq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_TRNSLTR_MARKERS_ERASEMARKERSINSEQ_REPLACETYPE1, \
    BOOST_PP_SEQ_ELEM(iteration, dataseq), \
    seq)

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_TRNSLTR_MARKERS_ERASEMARKERSINSEQ_REPLACETYPE1( \
  r, gettypemacro_settypemacro, indx, dcln) \
   WG_PP_TRNSLTR_MARKERS_ERASEMARKERSINSEQ_REPLACETYPE2( \
     BOOST_PP_SEQ_ELEM(0, gettypemacro_settypemacro), \
     BOOST_PP_SEQ_ELEM(1, gettypemacro_settypemacro), \
     indx, \
     dcln)

#define WG_PP_TRNSLTR_MARKERS_ERASEMARKERSINSEQ_REPLACETYPE2( \
  gettypemacro, settypemacro, indx, dcln) \
    ( \
      settypemacro( \
        dcln, \
         WG_PP_TRNSLTR_MARKERS_EATHEADMARKER(gettypemacro(dcln)) ) \
     )

#endif /* WG_LOCAL_DETAIL_TRANSLATOR_MARKERS_HH_ */
