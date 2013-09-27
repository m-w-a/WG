#ifndef WG_PP_PARAMDCLNNORMALIZE_HH_
#define WG_PP_PARAMDCLNNORMALIZE_HH_

#include <boost/preprocessor.hpp>
#include <boost/utility/identity_type.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Translator/Utils.hh>
#include <WG/Local/Detail/PP/Translator/Keywords.hh>

//###########
//Public APIs
//###########

#define WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE(paramdcln) \
  WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE_IMPL(paramdcln, 0)

#define WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE_TPL(paramdcln) \
  WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE_IMPL(paramdcln, 1)

//###########
//Impl Macros
//###########

#define WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE_EXPAND1(x) x

#define WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE_IMPL(paramdcln, istpl) \
  BOOST_PP_IIF( \
    WG_PP_ISNEXTTOKEN_A_TUPLE(1, paramdcln), \
    WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE_NOPREFIX1, \
    WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE_NONTUPLE) \
  (paramdcln, istpl)

#define WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE_NONTUPLE(paramdcln, istpl) \
  BOOST_PP_IIF( \
    WG_PP_KEYWORDS_STARTSWITH_PPESCAPE(paramdcln), \
    WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE_PPESCAPE, \
    WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE_NONTUPLE_ERROR) \
  (paramdcln, istpl)

#define WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE_NONTUPLE_ERROR(paramdcln, ignored) \
  ( \
    WG_PP_ERROR \
      BOOST_PP_CAT( \
        ERROR_missing_type_in_params_dcln_near_token_, \
        paramdcln) \
  )

#define WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE_NOPREFIX1(paramdcln, ignore) \
  WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE_EXPAND1( \
    WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE_NOPREFIX2 paramdcln) \
  BOOST_PP_RPAREN()

#define WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE_NOPREFIX2(param) \
  (param) BOOST_PP_LPAREN()

#define WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE_PPESCAPE(paramdcln, istpl) \
  BOOST_PP_LPAREN() \
    WG_PP_TRNSLTR_UTILS_ADDTYPENAME(istpl) \
    BOOST_PP_CAT(WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE_, paramdcln) \
  BOOST_PP_RPAREN()

#define WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE_ppescape(paren_wrapped_param) \
  BOOST_IDENTITY_TYPE(paren_wrapped_param) \
  BOOST_PP_RPAREN() BOOST_PP_LPAREN()

#endif /* WG_PP_PARAMDCLNNORMALIZE_HH_ */
