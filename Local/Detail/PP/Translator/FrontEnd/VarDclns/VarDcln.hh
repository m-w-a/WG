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

#define WG_PP_VARDCLN_ISEXPLICIT_LOCAL(vardcln) \
  BOOST_PP_IIF( \
    BOOST_PP_BITAND( \
      WG_PP_KEYWORDS_STARTSWITH_LCLTYPE(vardcln), \
      WG_PP_ISNEXTTOKEN_A_TUPLE( \
        1, \
        /* vardcln might itself be a keyword, therefore append BOOST_PP_NIL */ \
        /* to avoid empty macro arg UB in C++03. */ \
        WG_PP_KEYWORDS_EAT_HEADKEYWORD(vardcln BOOST_PP_NIL)) ), \
    1, \
    0)

#define WG_PP_VARDCLN_ISEXPLICIT_NONLOCAL(vardcln) \
  BOOST_PP_IIF( \
    BOOST_PP_BITAND( \
      WG_PP_KEYWORDS_STARTSWITH_TYPE(vardcln), \
      WG_PP_ISNEXTTOKEN_A_TUPLE( \
        1, \
        /* vardcln might itself be a keyword, therefore append BOOST_PP_NIL */ \
        /* to avoid empty macro arg UB in C++03. */ \
        WG_PP_KEYWORDS_EAT_HEADKEYWORD(vardcln BOOST_PP_NIL)) ), \
    1, \
    0)

#define WG_PP_VARDCLN_ISEXPLICIT_IMPL1(vardcln) \
  BOOST_PP_IIF( \
    BOOST_PP_BITOR( \
      WG_PP_VARDCLN_ISEXPLICIT_NONLOCAL(vardcln), \
      WG_PP_VARDCLN_ISEXPLICIT_LOCAL(vardcln) ), \
      1, \
      0)

#define WG_PP_VARDCLN_ISEXPLICIT_NLT_IMPL1(vardcln) \
  WG_PP_VARDCLN_ISEXPLICIT_NONLOCAL(vardcln)

#endif //WG_PP_VARDCLN_HH_
