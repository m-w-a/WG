#ifndef WG_PP_AUTOFUNCTION_BOUNDTUPLESEQ_HH_
#define WG_PP_AUTOFUNCTION_BOUNDTUPLESEQ_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/Keywords.hh>
#include <WG/Local/Detail/Seq.hh>
#include <WG/Local/Detail/FrontEnd/VarDcln.hh>
#include <WG/Local/Detail/FrontEnd/VarDclnExplicit.hh>
#include <WG/Local/Detail/FrontEnd/VarDclnImplicit.hh>

//###########
//Public APIs
//###########

// Expands to the following:
//   {(explicit-or-deduced-bound-type) (bound-var-name)}+
#define WG_PP_AUTOFUNCTION_BOUNDTUPLESEQ_NORMALIZE(boundtupleseq) \
  WG_PP_AUTOFUNCTION_BOUNDTUPLESEQ_NORMALIZEIMPL(boundtupleseq)

//###########
//Impl Macros
//###########
  
#define WG_PP_AUTOFUNCTION_BOUNDTUPLESEQ_NORMALIZEIMPL(boundtupleseq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_AUTOFUNCTION_BOUNDTUPLESEQ_NORMALIZEIMPL_OP, ~, boundtupleseq)

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_AUTOFUNCTION_BOUNDTUPLESEQ_NORMALIZEIMPL_OP(r, data, indx, elem) \
  WG_PP_AUTOFUNCTION_BOUNDTUPLESEQ_NORMALIZEBVAR(elem)

#define WG_PP_AUTOFUNCTION_BOUNDTUPLESEQ_NORMALIZEBVAR(boundvardcln) \
  BOOST_PP_IIF( \
    WG_PP_VARDCLN_ISEXPLICIT(boundvardcln), \
    WG_PP_VARDCLNEXPLICIT_TUPLIZE, \
    WG_PP_VARDCLNIMPLICIT_TUPLIZE) (boundvardcln)

//Debugging Aide.
#define S1 (T const * ) var1
#define S2 local(U) var2
#define S3 localref(Callback &) var3
#define S4 var4
#define S5 ref var5
#define S6 const var6
#define S7 const ref var7

#define btseq1 BOOST_PP_NIL
#define btseq2 (S2)
#define btseq3 (S1) (S2) (S3) (S4) (S5) (S6) (S7)

WG_PP_AUTOFUNCTION_BOUNDTUPLESEQ_NORMALIZE(btseq3)

#endif //WG_PP_AUTOFUNCTION_BOUNDTUPLESEQ_HH_
