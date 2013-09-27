#ifndef WG_PP_VARDCLN_HH_
#define WG_PP_VARDCLN_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Translator/Keywords.hh>

//###########
//Public APIs
//###########

// vardcln:
//   type-var-dcln
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_VARDCLN_ISEXPLICIT(vardcln) \
  WG_PP_VARDCLN_ISEXPLICIT_IMPL1(vardcln)

// NLT:
//   Stands for non-local type.
// vardcln:
//   type-var-dcln
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_VARDCLN_ISEXPLICIT_NLT(vardcln) \
  WG_PP_VARDCLN_ISEXPLICIT_NLT_IMPL1(vardcln)

//###########
//Impl Macros
//###########

#define WG_PP_VARDCLN_ISEXPLICIT_IMPL1(vardcln) \
  BOOST_PP_IIF( \
    WG_PP_ISNEXTTOKEN_A_TUPLE(1, vardcln), \
    WG_PP_MAP_TO_1_ARG1, \
    WG_PP_VARDCLN_ISEXPLICIT_IMPL2) (vardcln)

#define WG_PP_VARDCLN_ISEXPLICIT_IMPL2(vardcln) \
  BOOST_PP_IIF( \
    BOOST_PP_OR( \
      WG_PP_KEYWORDS_STARTSWITH_LOCAL(vardcln), \
      WG_PP_KEYWORDS_STARTSWITH_PPESCAPE(vardcln) ), \
    1, \
    0)

#define WG_PP_VARDCLN_ISEXPLICIT_NLT_IMPL1(vardcln) \
  BOOST_PP_IIF( \
    WG_PP_ISNEXTTOKEN_A_TUPLE(1, vardcln), \
    WG_PP_MAP_TO_1_ARG1, \
    WG_PP_VARDCLN_ISEXPLICIT_NLT_IMPL2) (vardcln)

#define WG_PP_VARDCLN_ISEXPLICIT_NLT_IMPL2(vardcln) \
  BOOST_PP_IIF( \
    WG_PP_KEYWORDS_STARTSWITH_PPESCAPE(vardcln), \
    1, \
    0)

#endif //WG_PP_VARDCLN_HH_
