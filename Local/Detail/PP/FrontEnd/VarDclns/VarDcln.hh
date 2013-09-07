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

#define WG_PP_VARDCLN_ISEXPLICIT_NLT(vardcln) \
  WG_PP_VARDCLN_ISEXPLICIT_NLT_IMPL(vardcln)

//###########
//Impl Macros
//###########

#define WG_PP_VARDCLN_ISEXPLICIT_IMPL(vardcln) \
  BOOST_PP_IIF( \
    BOOST_PP_OR( \
      WG_PP_ISNEXTTOKEN_A_TUPLE(1, vardcln), \
      WG_PP_TOKENS_STARTWITH_LOCAL(vardcln)), \
    1, \
    0)

#define WG_PP_VARDCLN_ISEXPLICIT_NLT_IMPL(vardcln) \
  BOOST_PP_IIF( \
    WG_PP_ISNEXTTOKEN_A_TUPLE(1, vardcln), \
    1, \
    0)

#endif //WG_PP_VARDCLN_HH_
