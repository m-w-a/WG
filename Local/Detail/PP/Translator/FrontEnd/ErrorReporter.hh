#ifndef WG_PP_ERRORREPORTER_HH_
#define WG_PP_ERRORREPORTER_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/Utils.hh>
#include <WG/Local/Detail/PP/Translator/Markers.hh>

//###########
//Public APIs
//###########

// psble_error:
//   alphanumtoken ... | WG_PP_MARKER_ERROR ...
// expands to:
//   1) the tokens following WG_PP_MARKER_ERROR if psble_error starts with
//     WG_PP_MARKER_ERROR, else
//   2) nothing.
#define WG_PP_ERRORREPORTER_REPORT_ERRORTOKENS(psble_error) \
  WG_PP_ERRORREPORTER_REPORT_ERRORTOKENS_IMPL(psble_error)

// parseddataseq:
//   { (WG_PP_MARKER_ERROR ...) | (alphanumtoken ...) }+
//
// expands to:
//   1) nothing if parseddataseq does not have any elements starting with
//     WG_PP_MARKER_ERROR, else
//   2) the tokens following any WG_PP_MARKER_ERROR found at the
//     beginning of any element in the sequence.
#define WG_PP_ERRORREPORTER_REPORT_PARSEDSEQ(parseddataseq) \
  WG_PP_ERRORREPORTER_REPORT_PARSEDSEQ_IMPL(parseddataseq)

//###########
//Impl Macros
//###########

#define WG_PP_ERRORREPORTER_REPORT_ERRORTOKENS_IMPL(psble_error) \
  BOOST_PP_EXPR_IIF( \
    WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_ERROR(psble_error), \
    WG_PP_TRNSLTR_MARKERS_EATHEADMARKER(psble_error))

//----------------
//REPORT_PARSEDSEQ
//----------------

#define WG_PP_ERRORREPORTER_REPORT_PARSEDSEQ_IMPL(parseddataseq) \
  WG_PP_SEQ_NOTHING_FOR_EACH( \
    WG_PP_ERRORREPORTER_REPORT_PARSEDSEQ_ENTRY, \
    ~, \
    parseddataseq)

#define WG_PP_ERRORREPORTER_REPORT_PARSEDSEQ_ENTRY(r, data, parseddata) \
  BOOST_PP_EXPR_IIF( \
    WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_ERROR(parseddata), \
    WG_PP_TRNSLTR_MARKERS_EATHEADMARKER(parseddata) )

#endif /* WG_PP_ERRORREPORTER_HH_ */
