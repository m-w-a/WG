#ifndef WG_PP_ERRORREPORTER_HH_
#define WG_PP_ERRORREPORTER_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Seq.hh>

//###########
//Public APIs
//###########

// psble_error:
//   BOOST_PP_NIL | WG_PP_ERROR ...
// expands to:
//   1) nothing if BOOST_PP_NIL, or
//   2) the tokens following WG_PP_ERROR
#define WG_PP_ERRORREPORTER_REPORT_ERRORSEQ(psble_error) \
  WG_PP_ERRORREPORTER_REPORT_ERRORSEQ_IMPL(psble_error)

// psble_nrmlzd_bnd_tuple_seq:
//   (BOOST_PP_NIL) | ( {normalized-bound-tuple}+ )
// expands to:
//   1) nothing if BOOST_PP_NIL, or
//   2) to:
//     1) nothing, if there are no WG_PP_ERROR markers in any of the elements of
//       the normalized-bound-tuple sequence, else
//     2) tokens corresponding to the elements that had
//       WG_PP_ERROR markers, but ommitting the said marker.
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLESEQ(psble_nrmlzd_bnd_tuple_seq) \
  WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLESEQ_IMPL(psble_nrmlzd_bnd_tuple_seq)

// psble_nrmlzd_set_tuple_seq:
//   (BOOST_PP_NIL) | ( {normalized-set-tuple}+ )
// expands to:
//   1) nothing if BOOST_PP_NIL, or
//   2) to:
//     1) nothing, if there are no WG_PP_ERROR markers in any of the elements of
//       the normalized-bound-tuple sequence, else
//     2) tokens corresponding to the elements that had
//       WG_PP_ERROR markers, but ommitting the said marker.
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_ERRORREPORTER_REPORT_NRMLZDSETTUPLESEQ(psble_nrmlzd_set_tuple_seq) \
  WG_PP_ERRORREPORTER_REPORT_NRMLZDSETTUPLESEQ_IMPL(psble_nrmlzd_set_tuple_seq)

//###########
//Impl Macros
//###########

#define WG_PP_ERRORREPORTER_REPORT_ERRORSEQ_IMPL(psble_error) \
  BOOST_PP_EXPR_IIF( \
    WG_PP_START_WITH_WG_PP_ERROR(psble_error), \
    WG_PP_EATHEADTOKEN_WG_PP_ERROR(psble_error))

//-------------------------------------------------
//WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLESEQ_IMPL
//-------------------------------------------------

#define WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLESEQ_IMPL( \
  psble_nrmlzd_bnd_tuple_seq) \
    WG_PP_SEQ_IFNIL_THENMAPTO( \
      WG_PP_SEQ_FOR_EACH_I( \
        WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLE, \
        ~, \
        psble_nrmlzd_bnd_tuple_seq) BOOST_PP_EMPTY, \
      BOOST_PP_EMPTY) ()

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLE(r, data, indx, elem) \
  BOOST_PP_IIF( \
    WG_PP_IS_ODD(indx), \
    WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLE_ODD, \
    WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLE_EVEN) (elem)

#define WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLE_ODD(elem) \
  WG_PP_ERRORREPORTER_REPORT_ERRORSEQ(elem)

#define WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLE_EVEN(elem) \
  BOOST_PP_IIF( \
    WG_PP_ISNEXTTOKEN_A_TUPLE(1, elem), \
    WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLE_EVEN_TUPLE, \
    WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLE_EVEN_NONTUPLE) (elem)

#define WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLE_EVEN_TUPLE(elem)
#define WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLE_EVEN_NONTUPLE(elem) \
  WG_PP_ERRORREPORTER_REPORT_ERRORSEQ(elem)

//-------------------------------------------------
//WG_PP_ERRORREPORTER_REPORT_NRMLZDSETTUPLESEQ_IMPL
//-------------------------------------------------

#define WG_PP_ERRORREPORTER_REPORT_NRMLZDSETTUPLESEQ_IMPL( \
  psble_nrmlzd_set_tuple_seq) \
    WG_PP_SEQ_IFNIL_THENMAPTO( \
      WG_PP_SEQ_FOR_EACH_I( \
        WG_PP_ERRORREPORTER_REPORT_NRMLZDSETTUPLE, \
        ~, \
        psble_nrmlzd_set_tuple_seq) BOOST_PP_EMPTY, \
      BOOST_PP_EMPTY) ()

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_ERRORREPORTER_REPORT_NRMLZDSETTUPLE(r, data, indx, elem) \
  BOOST_PP_CAT( \
    WG_PP_ERRORREPORTER_REPORT_NRMLZDSETTUPLE_, \
    BOOST_PP_MOD(indx,3)) (elem)

#define WG_PP_ERRORREPORTER_REPORT_NRMLZDSETTUPLE_0(elem) \
  WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLE_EVEN(elem)

#define WG_PP_ERRORREPORTER_REPORT_NRMLZDSETTUPLE_1(elem) \
  WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLE_ODD(elem)

#define WG_PP_ERRORREPORTER_REPORT_NRMLZDSETTUPLE_2(elem)

#endif /* WG_PP_ERRORREPORTER_HH_ */
