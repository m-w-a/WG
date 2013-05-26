#ifndef WG_PP_BOUNDVARDCLNNORMALIZE_HH_
#define WG_PP_BOUNDVARDCLNNORMALIZE_HH_

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
#define WG_PP_AUTOFUNCTION_BOUNDVARDCLN_NORMALIZE(boundvardcln) \
  WG_PP_AUTOFUNCTION_BOUNDVARDCLN_NORMALIZE_IMPL(boundvardcln)

//###########
//Impl Macros
//###########

#define WG_PP_AUTOFUNCTION_BOUNDVARDCLN_NORMALIZE_IMPL(boundvardcln) \
  BOOST_PP_IIF( \
    WG_PP_VARDCLN_ISEXPLICIT(boundvardcln), \
    WG_PP_VARDCLNEXPLICIT_TUPLIZE, \
    WG_PP_VARDCLNIMPLICIT_TUPLIZE) (boundvardcln)

/*
//Debugging Aide.
#define S1 (T const * ) var1
#define S2 local(U) var2
#define S3 localref(Callback &) var3
#define S4 var4
#define S5 ref var5
#define S6 const var6
#define S7 const ref var7

WG_PP_AUTOFUNCTION_BOUNDVARDCLN_NORMALIZE(S1)
WG_PP_AUTOFUNCTION_BOUNDVARDCLN_NORMALIZE(S2)
WG_PP_AUTOFUNCTION_BOUNDVARDCLN_NORMALIZE(S3)
WG_PP_AUTOFUNCTION_BOUNDVARDCLN_NORMALIZE(S4)
WG_PP_AUTOFUNCTION_BOUNDVARDCLN_NORMALIZE(S5)
WG_PP_AUTOFUNCTION_BOUNDVARDCLN_NORMALIZE(S6)
WG_PP_AUTOFUNCTION_BOUNDVARDCLN_NORMALIZE(S7)

//EXPECTED:
//(T const *) (var1)
//(local(U)) ( var2 )
//(localref(Callback &)) ( var3 )
//( BOOST_TYPEOF(var4) ) (var4)
//( boost::add_reference< BOOST_TYPEOF(var5) >::type ) (var5)
//( boost::add_const< BOOST_TYPEOF(var6) >::type ) (var6)
//( boost::add_reference<boost::add_const< BOOST_TYPEOF(var7) >::type>::type ) (var7)
*/

#endif //WG_PP_BOUNDVARDCLNNORMALIZE_HH_
