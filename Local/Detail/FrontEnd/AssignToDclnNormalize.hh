#ifndef WG_PP_ASSIGNTODCLNNORMALIZE_HH_
#define WG_PP_ASSIGNTODCLNNORMALIZE_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/FrontEnd/VarDcln.hh>
#include <WG/Local/Detail/FrontEnd/VarDclnExplicit.hh>
#include <WG/Local/Detail/Keywords.hh>

//###########
//Public APIs
//###########

#define WG_PP_ASSIGNTODCLN_NORMALIZE(assigntodcln) \
  WG_PP_ASSIGNTODCLN_NORMALIZE_IMPL(assigntodcln)

//###########
//Impl Macros
//###########

#define WG_PP_ASSIGNTODCLN_NORMALIZE_IMPL(assigntodcln) \
  BOOST_PP_IIF( \
    WG_PP_VARDCLN_ISEXPLICIT(assigntodcln), \
    WG_PP_VARDCLNEXPLICIT_TUPLIZE, \
    WG_PP_ASSIGNTODCLN_IMPLICIT_TUPLIZE) (assigntodcln)

#define WG_PP_ASSIGNTODCLN_IMPLICIT_ERRMSG() \
  "ERROR: const and ref keywords may not be used with implicit assignto" \
  " declarations."
#define WG_PP_ASSIGNTODCLN_IMPLICIT_TUPLIZE(assigntodcln) \
  BOOST_PP_IIF( \
    BOOST_PP_OR( \
      WG_PP_TOKENS_STARTWITH_CONST(assigntodcln), \
      WG_PP_TOKENS_STARTWITH_REF(assigntodcln)), \
    BOOST_PP_ASSERT_MSG(0, WG_PP_ASSIGNTODCLN_IMPLICIT_ERRMSG()), \
    WG_PP_DEDUCEDTYPE BOOST_TYPEOF(bvar) )

#endif /* WG_PP_ASSIGNTODCLNNORMALIZE_HH_ */
