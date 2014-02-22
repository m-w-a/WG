#ifndef WG_PP_BOUNDVARDCLNNORMALIZE_HH_
#define WG_PP_BOUNDVARDCLNNORMALIZE_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/Translator/FrontEnd/VarDclns/VarDcln.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/VarDclns/VarDclnExplicit.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/VarDclns/VarDclnImplicit.hh>

//###########
//Public APIs
//###########

// boundvardcln:
//   bound-var-dcln
// Expands to the following:
//   (parsed-explicit-or-deduced-type) (bound-var-name)
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_BOUNDVARDCLN_NORMALIZE(boundvardcln) \
  WG_PP_BOUNDVARDCLN_NORMALIZE_IMPL(boundvardcln, 0)

// boundvardcln:
//   bound-var-dcln
// Expands to the following:
//   (parsed-explicit-or-deduced-type) (bound-var-name)
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_BOUNDVARDCLN_NORMALIZE_TPL(boundvardcln) \
  WG_PP_BOUNDVARDCLN_NORMALIZE_IMPL(boundvardcln, 1)

// boundvardcln:
//   nlt-bound-var-dcln
// Expands to the following:
//   (parsed-explicit-non-local-type-or-deduced-type) (bound-var-name)
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_BOUNDVARDCLN_NLT_NORMALIZE(boundvardcln) \
  WG_PP_BOUNDVARDCLN_NLT_NORMALIZE_IMPL(boundvardcln, 0)

// boundvardcln:
//   nlt-bound-var-dcln
// Expands to the following:
//   (parsed-explicit-non-local-type-or-deduced-type) (bound-var-name)
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_BOUNDVARDCLN_NLT_NORMALIZE_TPL(boundvardcln) \
  WG_PP_BOUNDVARDCLN_NLT_NORMALIZE_IMPL(boundvardcln, 1)

//###########
//Impl Macros
//###########

#define WG_PP_BOUNDVARDCLN_NORMALIZE_IMPL(boundvardcln, istpl) \
  BOOST_PP_IIF( \
    WG_PP_VARDCLN_ISEXPLICIT(boundvardcln), \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE, \
    WG_PP_VARDCLN_IMPLICIT_TUPLIZE_1ARG) \
  (boundvardcln, istpl)

#define WG_PP_BOUNDVARDCLN_NLT_NORMALIZE_IMPL(boundvardcln, istpl) \
  BOOST_PP_IIF( \
    WG_PP_VARDCLN_ISEXPLICIT_NLT(boundvardcln), \
    WG_PP_VARDCLN_EXPLICIT_NLT_TUPLIZE, \
    WG_PP_VARDCLN_IMPLICIT_TUPLIZE_1ARG) \
  (boundvardcln, istpl)

#endif //WG_PP_BOUNDVARDCLNNORMALIZE_HH_
