#ifndef WG_LOCAL_DETAIL_TRANSLATOR_UTILS_HH_
#define WG_LOCAL_DETAIL_TRANSLATOR_UTILS_HH_

#include <boost/preprocessor.hpp>

//###########
//Public APIs
//###########

#define WG_PP_TRNSLTR_UTILS_ADDTYPENAME(istpl) \
  BOOST_PP_EXPR_IIF(istpl, typename)

#define WG_PP_TRNSLTR_UTILS_TYPEOF(istpl, expr) \
  BOOST_PP_IIF( \
    istpl, \
    BOOST_TYPEOF_TPL, \
    BOOST_TYPEOF) (expr)

//###########
//Impl Macros
//###########

#endif /* WG_LOCAL_DETAIL_TRANSLATOR_UTILS_HH_ */
