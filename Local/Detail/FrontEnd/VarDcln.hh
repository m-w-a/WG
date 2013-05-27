#ifndef WG_PP_VARDCLN_HH_
#define WG_PP_VARDCLN_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/Keywords.hh>

//###########
//Public APIs
//###########

#define WG_PP_VARDCLN_ISEXPLICIT(vardcln) \
  WG_PP_VARDCLN_ISEXPLICIT_IMPL(vardcln)

#define WG_PP_VARDCLN_ISIMPLICIT(vardcln) \
  BOOST_PP_NOT( \
    WG_PP_VARDCLN_ISEXPLICIT(vardcln))
  
//###########
//Impl Macros
//###########

#define WG_PP_VARDCLN_ISEXPLICIT_IMPL(vardcln) \
  BOOST_PP_IIF( \
    BOOST_PP_OR( \
      WG_PP_ISNEXTTOKEN_A_TUPLE(1, vardcln), \
      BOOST_PP_OR( \
        WG_PP_TOKENS_STARTWITH_LOCAL(vardcln), \
        WG_PP_TOKENS_STARTWITH_LOCALREF(vardcln))), \
    1, \
    0)

/*
//Unit Tests.
#define S1 (Foo *)
#define S2 local(Foo)
#define S3 localref(Foo &)
#define S4 const
#define S5 ref
#define S6 const ref

WG_PP_VARDCLN_ISEXPLICIT(S1)
WG_PP_VARDCLN_ISEXPLICIT(S2)
WG_PP_VARDCLN_ISEXPLICIT(S3)
WG_PP_VARDCLN_ISEXPLICIT(S4)
WG_PP_VARDCLN_ISEXPLICIT(S5)
WG_PP_VARDCLN_ISEXPLICIT(S6)

//EXPECTED:
//1
//1
//1
//0
//0
//0
*/

#endif //WG_PP_VARDCLN_HH_
