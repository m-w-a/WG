#ifndef WG_PP_AUTOFUNCTION_BOUNDVARS_HH_
#define WG_PP_AUTOFUNCTION_BOUNDVARS_HH_

#include <boost/preprocessor.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_const.hpp>
#include <WG/Local/Detail/Keywords.hh>
#include <WG/Local/Detail/Seq.hh>
#include <WG/Local/Detail/SplitHeadFromTokens.hh>

//###########
//Public APIs
//###########

// Expands to the following:
//   {(deduced-bound-type) (bound-var-name)}+
#define WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZE(rawboundvarseq) \
  WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEIMPL(rawboundvarseq)

//###########
//Impl Macros
//###########
  
// Need to use these instead of BOOST_PP_EXPAND because for some reason the 
//  latter prevents the macro expansion of BOOST_PP_EXPANDs in these macros.
#define WG_PP_BOUNDVARS_EXPAND1(x) x
#define WG_PP_BOUNDVARS_EXPAND2(x) x
  
#define WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEIMPL(rawboundvarseq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEIMPL_OP, ~, rawboundvarseq)

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEIMPL_OP(r, data, indx, elem) \
  WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR(elem)
    
//------------------------
//Normalize BoundVar Tuple
//------------------------
  
#define WG_PP_AUTOFUNCTION_BOUNDVARS_ISMANUALBOUND(rawbvar) \
  BOOST_PP_IIF( \
    BOOST_PP_OR( \
      WG_PP_ISNEXTTOKEN_A_TUPLE(1, rawbvar), \
      BOOST_PP_OR( \
        WG_PP_TOKENS_STARTWITH_LOCAL(rawbvar), \
        WG_PP_TOKENS_STARTWITH_LOCALREF(rawbvar))), \
    1, \
    0)
  
#define WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR(rawbvar) \
  BOOST_PP_CAT( \
    WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR_, \
    BOOST_PP_IIF( \
      WG_PP_AUTOFUNCTION_BOUNDVARS_ISMANUALBOUND(rawbvar), \
      MANUAL, \
      AUTO)) (rawbvar)

#define WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR_MANUAL(rawbvar) \
  BOOST_PP_CAT( \
    WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR_MANUAL_, \
    BOOST_PP_EXPR_IIF(WG_PP_ISNEXTTOKEN_A_TUPLE(1, rawbvar), NONLOCAL) \
    BOOST_PP_EXPR_IIF(WG_PP_TOKENS_STARTWITH_LOCAL(rawbvar), LOCAL) \
    BOOST_PP_EXPR_IIF(WG_PP_TOKENS_STARTWITH_LOCALREF(rawbvar), LOCALREF) ) \
  (rawbvar)

#define WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR_MANUAL_NONLOCAL(rawbvar) \
  WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLEFROMTOKENS( \
    1, rawbvar, WG_PP_IDENTITY, WG_PP_TUPLIZE)

#define WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR_MANUAL_LOCAL(rawbvar) \
  BOOST_PP_CAT( \
    WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR_MANUAL_LOCAL_, \
    rawbvar) BOOST_PP_RPAREN()
#define WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR_MANUAL_LOCAL_local( \
  localvalue) \
    (local(localvalue)) BOOST_PP_LPAREN()

#define WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR_MANUAL_LOCALREF(rawbvar) \
  BOOST_PP_CAT( \
    WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR_MANUAL_LOCALREF_, \
    rawbvar) BOOST_PP_RPAREN()
#define WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR_MANUAL_LOCALREF_localref( \
  localrefvalue) \
    (localref(localrefvalue)) BOOST_PP_LPAREN()


#define WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR_AUTO(rawbvar) \
  WG_PP_BOUNDVARS_EXPAND1( \
    WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR_AUTO2 \
    BOOST_PP_IIF( \
      WG_PP_TOKENS_STARTWITH_CONST(rawbvar), \
      ( 1, WG_PP_TOKENS_EAT_HEADKEYWORD(rawbvar) ), \
      ( 0, rawbvar ) ))

#define WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR_AUTO2(addconst, rawbvar) \
  WG_PP_BOUNDVARS_EXPAND2( \
    WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR_AUTO3 \
    BOOST_PP_IIF( \
      WG_PP_TOKENS_STARTWITH_REF(rawbvar), \
      ( addconst, 1, WG_PP_TOKENS_EAT_HEADKEYWORD(rawbvar)), \
      ( addconst, 0, rawbvar )  ))

#define WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR_AUTO3( \
  addconst, addref, bvar) \
    ( BOOST_PP_CAT( \
      WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR_AUTO3_, \
      BOOST_PP_CAT( \
        addconst, \
        addref)) (bvar) ) \
    (bvar)

#define WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR_AUTO3_00(bvar) \
  BOOST_TYPEOF(bvar)
#define WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR_AUTO3_01(bvar) \
  boost::add_reference< BOOST_TYPEOF(bvar) >::type
#define WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR_AUTO3_10(bvar) \
  boost::add_const< BOOST_TYPEOF(bvar) >::type
#define WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR_AUTO3_11(bvar) \
  boost::add_reference<boost::add_const< BOOST_TYPEOF(bvar) >::type>::type
  
/*
//Debugging Aide.
#define S1 (T const * ) var1
#define S2 local(U) var2
#define S3 localref(Callback &) var3
#define S4 var4
#define S5 ref var5
#define S6 const var6
#define S7 const ref var7
*/
  
/*
//Debugging Aide.
WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR(S1)
WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR(S2)
WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR(S3)
WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR(S4)
WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR(S5)
WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR(S6)
WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZEBVAR(S7)

//EXPECTED:
//(T const *) (var1)
//(local(U) (var2)
//(localref(Callback &) (var3)
//( BOOST_TYPEOF(var4) ) (var4)
//( boost::add_reference< BOOST_TYPEOF(var5) >::type ) (var5)
//( boost::add_const< BOOST_TYPEOF(var6) >::type ) (var6)
//( boost::add_reference<boost::add_const< BOOST_TYPEOF(var7) >::type>::type ) (var7)
*/

/*
//Debugging Aide
#define bvarseq1 BOOST_PP_NIL
#define bvarseq2 (S2)
#define bvarseq3 (S1) (S2) (S3) (S4) (S5) (S6) (S7)

WG_PP_AUTOFUNCTION_BOUNDVARS_NORMALIZE(bvarseq3)
*/

#endif //WG_PP_AUTOFUNCTION_BOUNDVARS_HH_
