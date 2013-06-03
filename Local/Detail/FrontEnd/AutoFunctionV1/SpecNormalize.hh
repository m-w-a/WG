#ifndef WG_PP_AUTOFUNCTIONV1_SPECNORMALIZE_HH_
#define WG_PP_AUTOFUNCTIONV1_SPECNORMALIZE_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/Seq.hh>
#include <WG/Local/Detail/AltSeq.hh>
#include <WG/Local/Detail/Keywords.hh>

//###########
//Public APIs
//###########

#define WG_PP_AUTOFUNCTIONV1_SPECNORMALIZE( \
  bresult_seq, ret_type, bp_seq, ap_alt_seq) \
    WG_PP_AUTOFUNCTIONV1_SPECNORMALIZE_IMPL( \
      bresult_seq, ret_type, bp_seq, ap_alt_seq)

//###########
//Impl Macros
//###########

//------------------------
//AssignedPSeq & BoundPSeq
//------------------------

#define WG_PP_AFV1_SN_BOUNDPSEQ_ISVOID(bp_seq) \
  BOOST_PP_IIF( \
    BOOST_PP_AND( \
      BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(bp_seq), 1), \
      WG_PP_TOKENS_STARTWITH_VOID( \
        BOOST_PP_EXPAND(WG_PP_IDENTITY bp_seq BOOST_PP_NIL))), \
      1, \
      0)

#define WG_PP_AFV1_SN_ASSIGNEDPSEQ_ISVOID(ap_alt_seq) \
  BOOST_PP_IIF( \
    WG_PP_ISNEXTTOKEN_A_TUPLE( \
      2, BOOST_PP_TUPLE_EAT(1) ap_alt_seq BOOST_PP_NIL), \
    0, \
    BOOST_PP_IIF( \
      WG_PP_TOKENS_STARTWITH_VOID( \
        BOOST_PP_EXPAND(WG_PP_IDENTITY ap_alt_seq BOOST_PP_NIL)), \
      1, \
      0))

#define WG_PP_AUTOFUNCTIONV1_SPECNORMALIZE_IMPL( \
  bresult_seq, ret_type, bp_seq, ap_alt_seq) \
    WG_PP_SYMBOLTABLE_CREATE( \
      BOOST_PP_IIF( \
        WG_PP_AFV1_SN_BOUNDPSEQ_ISVOID(bresult_seq), \
        BOOST_PP_NIL, \
        bresult_seq), \
      BOOST_PP_SEQ_ELEM(0, ret_type), \
      BOOST_PP_IIF( \
        WG_PP_AFV1_SN_BOUNDPSEQ_ISVOID(bp_seq), \
        BOOST_PP_NIL, \
        bp_seq), \
      BOOST_PP_IIF( \
        WG_PP_AFV1_SN_ASSIGNEDPSEQ_ISVOID(ap_alt_seq), \
        BOOST_PP_NIL, \
        WG_PP_ALTSEQ_LINEARIZE(ap_alt_seq)))

#endif /* WG_PP_AUTOFUNCTIONV1_SPECNORMALIZE_HH_ */
