#ifndef WG_PP_BOUNDVARDCLNNORMALIZE_HH_
#define WG_PP_BOUNDVARDCLNNORMALIZE_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/FrontEnd/VarDcln.hh>
#include <WG/Local/Detail/FrontEnd/VarDclnExplicit.hh>
#include <WG/Local/Detail/FrontEnd/VarDclnImplicit.hh>

//###########
//Public APIs
//###########

// Expands to the following:
//   {(parsed-explicit-or-deduced-type) (bound-var-name)}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_BOUNDVARDCLN_NORMALIZE(boundvardcln) \
  WG_PP_BOUNDVARDCLN_NORMALIZE_IMPL(boundvardcln, 0)

// Expands to the following:
//   {(parsed-explicit-or-deduced-type) (bound-var-name)}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_BOUNDVARDCLN_NORMALIZE_TPL(boundvardcln) \
  WG_PP_BOUNDVARDCLN_NORMALIZE_IMPL(boundvardcln, 1)

// Expands to the following:
//   {(parsed-explicit-non-local-type-or-deduced-type) (bound-var-name)}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_BOUNDVARDCLN_NLT_NORMALIZE(boundvardcln) \
  WG_PP_BOUNDVARDCLN_NLT_NORMALIZE_IMPL(boundvardcln, 0)

// Expands to the following:
//   {(parsed-explicit-non-local-type-or-deduced-type) (bound-var-name)}+
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_BOUNDVARDCLN_NLT_NORMALIZE_TPL(boundvardcln) \
  WG_PP_BOUNDVARDCLN_NLT_NORMALIZE_IMPL(boundvardcln, 1)

//###########
//Impl Macros
//###########

#define WG_PP_BOUNDVARDCLN_NORMALIZE_EXPAND1(x) x

#define WG_PP_BOUNDVARDCLN_NORMALIZE_IMPL(boundvardcln, istpl) \
  WG_PP_BOUNDVARDCLN_NORMALIZE_EXPAND1( \
    BOOST_PP_IIF( \
      WG_PP_VARDCLN_ISEXPLICIT(boundvardcln), \
      WG_PP_VARDCLN_EXPLICIT_TUPLIZE, \
      WG_PP_VARDCLN_IMPLICIT_TUPLIZE_1ARG) \
    BOOST_PP_IIF( \
      WG_PP_VARDCLN_ISEXPLICIT(boundvardcln), \
      (boundvardcln), \
      (boundvardcln, istpl) ) )

#define WG_PP_BOUNDVARDCLN_NORMALIZE_EXPAND2(x) x

#define WG_PP_BOUNDVARDCLN_NLT_NORMALIZE_IMPL(boundvardcln, istpl) \
  WG_PP_BOUNDVARDCLN_NORMALIZE_EXPAND2( \
    BOOST_PP_IIF( \
      WG_PP_VARDCLN_NLT_ISEXPLICIT(boundvardcln), \
      WG_PP_VARDCLN_EXPLICIT_NLT_TUPLIZE, \
      WG_PP_VARDCLN_IMPLICIT_TUPLIZE_1ARG) \
    BOOST_PP_IIF( \
      WG_PP_VARDCLN_NLT_ISEXPLICIT(boundvardcln), \
      (boundvardcln), \
      (boundvardcln, istpl) ) )

#endif //WG_PP_BOUNDVARDCLNNORMALIZE_HH_
