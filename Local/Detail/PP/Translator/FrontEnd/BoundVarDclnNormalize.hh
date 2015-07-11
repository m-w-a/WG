#ifndef WG_PP_BOUNDVARDCLNNORMALIZE_HH_
#define WG_PP_BOUNDVARDCLNNORMALIZE_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/Translator/FrontEnd/VarDclns/VarDcln.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/VarDclns/VarDclnExplicit.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/VarDclns/VarDclnImplicit.hh>

//###########
//Public APIs
//###########

//-----------------------------------------------------------------------------
// [1]
//
// marked-parsed-bound-var-dcln:
//   {
//       ( WG_PP_MARKER_ERROR ... )
//     |
//       (
//         WG_PP_MARKER_NOOP
//         ( parsed-explicit-or-deduced-type )
//         ( bound-var-name )
//       )
//   }
//
// marked-parsed-nlt-bound-var-dcln
//   {
//       ( WG_PP_MARKER_ERROR ... )
//     |
//       (
//         WG_PP_MARKER_NOOP
//         ( parsed-explicit-non-local-type-or-deduced-type )
//         ( bound-var-name )
//       )
//   }
//-----------------------------------------------------------------------------

// boundvardcln:
//   bound-var-dcln
// Expands to the following:
//   marked-parsed-bound-var-dcln
//
// (For definition of terms see [1] and SymbolTable documentation.)
#define WG_PP_BOUNDVARDCLN_NORMALIZE(boundvardcln) \
  WG_PP_BOUNDVARDCLN_NORMALIZE_IMPL(boundvardcln, 0)

// boundvardcln:
//   bound-var-dcln
// Expands to the following:
//   marked-parsed-bound-var-dcln
//
// (For definition of terms see [1] and SymbolTable documentation.)
#define WG_PP_BOUNDVARDCLN_NORMALIZE_TPL(boundvardcln) \
  WG_PP_BOUNDVARDCLN_NORMALIZE_IMPL(boundvardcln, 1)

// boundvardcln:
//   nlt-bound-var-dcln
// Expands to the following:
//   marked-parsed-nlt-bound-var-dcln
//
// (For definition of terms see [1] and SymbolTable documentation.)
#define WG_PP_BOUNDVARDCLN_NLT_NORMALIZE(boundvardcln) \
  WG_PP_BOUNDVARDCLN_NLT_NORMALIZE_IMPL(boundvardcln, 0)

// boundvardcln:
//   nlt-bound-var-dcln
// Expands to the following:
//   marked-parsed-nlt-bound-var-dcln
//
// (For definition of terms see [1] and SymbolTable documentation.)
#define WG_PP_BOUNDVARDCLN_NLT_NORMALIZE_TPL(boundvardcln) \
  WG_PP_BOUNDVARDCLN_NLT_NORMALIZE_IMPL(boundvardcln, 1)

//###########
//Impl Macros
//###########

#define WG_PP_BOUNDVARDCLN_NORMALIZE_IMPL(boundvardcln, istpl) \
  WG_PP_VARDCLN_PERCOLATEERROR_OR_CONTINUE( \
    BOOST_PP_IIF( \
      WG_PP_VARDCLN_ISEXPLICIT(boundvardcln), \
      WG_PP_VARDCLN_EXPLICIT_TUPLIZE, \
      WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUNDDCLN) \
    (boundvardcln, istpl) )

#define WG_PP_BOUNDVARDCLN_NLT_NORMALIZE_IMPL(boundvardcln, istpl) \
  WG_PP_VARDCLN_PERCOLATEERROR_OR_CONTINUE( \
    BOOST_PP_IIF( \
      WG_PP_VARDCLN_ISEXPLICIT_NLT(boundvardcln), \
      WG_PP_VARDCLN_EXPLICIT_NLT_TUPLIZE, \
      WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUNDDCLN) \
    (boundvardcln, istpl) )

#endif //WG_PP_BOUNDVARDCLNNORMALIZE_HH_
