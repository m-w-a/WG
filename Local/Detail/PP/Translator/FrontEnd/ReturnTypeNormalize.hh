#ifndef WG_PP_RETURNTYPENORMALIZE_HH_
#define WG_PP_RETURNTYPENORMALIZE_HH_

#include <boost/preprocessor.hpp>
#include <boost/utility/identity_type.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Translator/Keywords.hh>
#include <WG/Local/Detail/PP/Translator/Utils.hh>

//###########
//Public APIs
//###########

// returntype:
//   return-tuple element.
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_RETURNTYPE_NORMALIZE(returntype) \
  WG_PP_RETURNTYPE_NORMALIZE_IMPL(returntype, 0)

// returntype:
//   return-tuple element.
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_RETURNTYPE_NORMALIZE_TPL(returntype) \
  WG_PP_RETURNTYPE_NORMALIZE_IMPL(returntype, 1)

//###########
//Impl Macros
//###########

#define WG_PP_RETURNTYPE_NORMALIZE_IMPL(returntype, istpl) \
  returntype


#endif /* WG_PP_RETURNTYPENORMALIZE_HH_ */
