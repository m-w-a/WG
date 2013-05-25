#ifndef WG_PP_VARDCLNEXPLICIT_HH_
#define WG_PP_VARDCLNEXPLICIT_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/Keywords.hh>
#include <WG/Local/Detail/FrontEnd/SplitHeadFromTokens.hh>

//###########
//Public APIs
//###########

// Expands to the following:
//   (declared-type) (var-name)
#define WG_PP_VARDCLNEXPLICIT_TUPLIZE(explicitvardcln) \
  WG_PP_VARDCLNEXPLICIT_TUPLIZE_IMPL(explicitvardcln)
  
//###########
//Impl Macros
//###########

#define WG_PP_VARDCLNEXPLICIT_TUPLIZE_IMPL(explicitvardcln) \
  BOOST_PP_CAT( \
    WG_PP_VARDCLNEXPLICIT_TUPLIZE_IMPL_, \
    BOOST_PP_EXPR_IIF(WG_PP_ISNEXTTOKEN_A_TUPLE(1, explicitvardcln), NONLOCAL) \
    BOOST_PP_EXPR_IIF(WG_PP_TOKENS_STARTWITH_LOCAL(explicitvardcln), LOCAL) \
    BOOST_PP_EXPR_IIF(WG_PP_TOKENS_STARTWITH_LOCALREF(explicitvardcln), LOCALREF) ) \
  (explicitvardcln)

#define WG_PP_VARDCLNEXPLICIT_TUPLIZE_IMPL_NONLOCAL(explicitvardcln) \
  WG_PP_AUTOFUNCTION_SPEC_SPLITHEADTUPLEFROMTOKENS( \
    1, explicitvardcln, WG_PP_IDENTITY, WG_PP_TUPLIZE)

#define WG_PP_VARDCLNEXPLICIT_TUPLIZE_IMPL_LOCAL(explicitvardcln) \
  BOOST_PP_CAT( \
    WG_PP_VARDCLNEXPLICIT_TUPLIZE_IMPL_LOCAL_, \
    explicitvardcln) BOOST_PP_RPAREN()
#define WG_PP_VARDCLNEXPLICIT_TUPLIZE_IMPL_LOCAL_local( \
  localvalue) \
    (local(localvalue)) BOOST_PP_LPAREN()

#define WG_PP_VARDCLNEXPLICIT_TUPLIZE_IMPL_LOCALREF(explicitvardcln) \
  BOOST_PP_CAT( \
    WG_PP_VARDCLNEXPLICIT_TUPLIZE_IMPL_LOCALREF_, \
    explicitvardcln) BOOST_PP_RPAREN()
#define WG_PP_VARDCLNEXPLICIT_TUPLIZE_IMPL_LOCALREF_localref( \
  localrefvalue) \
    (localref(localrefvalue)) BOOST_PP_LPAREN()

/*
//Debugging Aide.
#define VDE1 (T const * ) var1
#define VDE2 local(U) var2
#define VDE3 localref(Callback &) var3

WG_PP_VARDCLNEXPLICIT_TUPLIZE(VDE1)
WG_PP_VARDCLNEXPLICIT_TUPLIZE(VDE2)
WG_PP_VARDCLNEXPLICIT_TUPLIZE(VDE3)

//EXPECTED:
//(T const *) (var1)
//(local(U) (var2)
//(localref(Callback &) (var3)
*/

#endif //WG_PP_VARDCLNEXPLICIT_HH_