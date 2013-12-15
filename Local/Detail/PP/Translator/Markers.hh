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

#define WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_ERROR(tokens) \
  WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_ERROR_IMPL(tokens)

#define WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_DEDUCEDTYPE(tokens) \
  WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_DEDUCEDTYPE_IMPL(tokens)

#define WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_NOOP(tokens) \
  WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_NOOP_IMPL(tokens)

// WG_PP_STUTIL_REPLACESEQ callback.
// seq:
//   A WG_PP_SEQ.
#define WG_PP_TRNSLTR_MARKERS_ERASEMARKERSINSEQ(seq, iteration, data) \
  WG_PP_TRNSLTR_MARKERS_ERASEMARKERSINSEQ_IMPL(seq)

//###########
//Impl Macros
//###########

#define WG_PP_TRNSLTR_MARKERS_EATHEADMARKER_WG_PP_ERROR
#define WG_PP_TRNSLTR_MARKERS_EATHEADMARKER_WG_PP_MARKER_DEDUCEDTYPE
#define WG_PP_TRNSLTR_MARKERS_EATHEADMARKER_WG_PP_MARKER_NOOP

#define WG_PP_TRNSLTR_MARKERS_EATHEADMARKER_IMPL(tokens) \
  BOOST_PP_CAT( \
    WG_PP_TRNSLTR_MARKERS_EATHEADMARKER_, \
    tokens)

//-----------
//WG_PP_ERROR
//-----------

#define WG_PP_TRNSLTR_MARKERS_TOKENMATCH_BEGINSWITH_WG_PP_ERROR_WG_PP_ERROR \
  WG_PP_TOKENMATCH_FRONTMATCH
#define WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_ERROR_IMPL(tokens) \
  WG_PP_TOKENMATCH_BEGINSWITH(\
    tokens, \
    WG_PP_TRNSLTR_MARKERS_TOKENMATCH_BEGINSWITH_WG_PP_ERROR_)

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

#define WG_PP_TRNSLTR_MARKERS_ERASEMARKERSINSEQ_IMPL(seq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_TRNSLTR_MARKERS_ERASEMARKERSINSEQ_REPLACETUPLE, \
    ~, \
    seq)

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_TRNSLTR_MARKERS_ERASEMARKERSINSEQ_REPLACETUPLE( \
  r, ignored, indx, entry) \
    ( \
      WG_PP_TRNSLTR_MARKERS_EATHEADMARKER(entry) \
    )

#endif /* WG_LOCAL_DETAIL_TRANSLATOR_MARKERS_HH_ */
