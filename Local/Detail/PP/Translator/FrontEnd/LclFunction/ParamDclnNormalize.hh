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

#define WG_PP_LCLFUNCTION_PARAMDCLN_NORMALIZE_IMPL(paramdcln, istpl) \
  ( paramdcln )

#endif /* WG_PP_PARAMDCLNNORMALIZE_HH_ */
