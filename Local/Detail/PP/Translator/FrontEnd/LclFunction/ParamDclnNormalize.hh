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

// Expands to the following:
//   {normalized-explicit-nlt-tuple}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE(paramdcln) \
  WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE_IMPL(paramdcln, 0)

// Expands to the following:
//   {normalized-explicit-nlt-tuple}+
//
// (For definition of terms see SymbolTable documentation.)
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
    WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE_NONTUPLE_ERROR) \
  (paramdcln, istpl)

#define WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE_NONTUPLE_ERROR(paramdcln, ignored) \
  ( \
    WG_PP_MARKER_ERROR \
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

#endif /* WG_PP_PARAMDCLNNORMALIZE_HH_ */
