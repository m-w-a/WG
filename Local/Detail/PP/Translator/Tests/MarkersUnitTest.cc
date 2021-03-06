#include <WG/Local/Tests/Utils/PreprocessorUnitTester.hh>
#include <WG/Local/Detail/PP/Translator/Markers.hh>

// WG_PP_TRNSLTR_MARKERS_EATHEADMARKER
BEGIN WG_PP_TRNSLTR_MARKERS_EATHEADMARKER(WG_PP_MARKER_ERROR 1) == 1 END
BEGIN WG_PP_TRNSLTR_MARKERS_EATHEADMARKER(WG_PP_MARKER_DEDUCEDTYPE 1) == 1 END
BEGIN WG_PP_TRNSLTR_MARKERS_EATHEADMARKER(WG_PP_MARKER_NOOP 1) == 1 END

// WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_DEDUCEDTYPE
BEGIN WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_DEDUCEDTYPE(WG_PP_MARKER_DEDUCEDTYPE foo) == 1 END

// WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_ERROR
BEGIN WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_ERROR(WG_PP_MARKER_ERROR foo) == 1 END

// WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_NOOP
BEGIN WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_NOOP(WG_PP_MARKER_NOOP foo) == 1 END
