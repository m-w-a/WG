#ifndef WG_PP_UTILS_HH_
#define WG_PP_UTILS_HH_

#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/Markers.hh>

//###########
//Public APIs
//###########

#define WG_PP_UTILS_SEQ_REMOVEHEADMARKERS(wgseq) \
  WG_PP_UTILS_SEQ_REMOVEHEADMARKERS_IMPL(wgseq)

//###########
//Impl Macros
//###########

#define WG_PP_UTILS_SEQ_REMOVEHEADMARKERS_IMPL(wgseq) \
  WG_PP_SEQ_FOR_EACH( \
    WG_PP_UTILS_SEQ_REMOVEHEADMARKERS_ENTRY, \
    ~, \
    wgseq)

#define WG_PP_UTILS_SEQ_REMOVEHEADMARKERS_ENTRY(r, data, elem) \
  ( \
    WG_PP_TRNSLTR_MARKERS_EATHEADMARKER(elem) \
  )

#endif /* WG_PP_UTILS_HH_ */
