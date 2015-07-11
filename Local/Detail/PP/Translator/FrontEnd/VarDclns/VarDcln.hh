#ifndef WG_PP_VARDCLN_HH_
#define WG_PP_VARDCLN_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Translator/Keywords.hh>
#include <WG/Local/Detail/PP/Translator/Markers.hh>

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

// type_varname:
//   {
//     ( WG_PP_MARKER_ERROR ... |
//       WG_PP_MARKER_<NOOP | DEDUCED> parsed-explicit-or-deduced-type )
//     ( WG_PP_MARKER_ERROR ... | var-name )
//     ...
//   }
//
// Expands to:
//   {
//       (
//         WG_PP_MARKER_NOOP
//         ( WG_PP_MARKER_<NOOP | DEDUCED> parsed-explicit-or-deduced-type )
//         ( var-name )
//         ...
//       )
//     | ( WG_PP_MARKER_ERROR .... )
//   }
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_VARDCLN_PERCOLATEERROR_OR_CONTINUE(type_varname) \
  WG_PP_VARDCLN_PERCOLATEERROR_OR_CONTINUE_IMPL(type_varname)

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
        WG_PP_KEYWORDS_EATHEAD_LCLTYPE(vardcln BOOST_PP_NIL)) ), \
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
        WG_PP_KEYWORDS_EATHEAD_TYPE(vardcln BOOST_PP_NIL)) ), \
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

//--------------------------
//PERCOLATEERROR_OR_CONTINUE
//--------------------------

#define WG_PP_VARDCLN_PERCOLATEERROR_OR_CONTINUE_IMPL(parsedtype_varname) \
  WG_PP_VARDCLN_EXPLICIT_TUPLIZE_LOCAL_PERCOLATEERROR_OR_CONTINUE2( \
    parsedtype_varname, \
    BOOST_PP_EXPR_IIF( \
      WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_ERROR( \
        BOOST_PP_SEQ_ELEM(0, parsedtype_varname)), \
      WG_PP_TRNSLTR_MARKERS_EATHEADMARKER( \
        BOOST_PP_SEQ_ELEM(0, parsedtype_varname) ) ) \
    BOOST_PP_EXPR_IIF( \
      WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_ERROR( \
        BOOST_PP_SEQ_ELEM(1, parsedtype_varname)), \
      WG_PP_TRNSLTR_MARKERS_EATHEADMARKER( \
        BOOST_PP_SEQ_ELEM(1, parsedtype_varname)) ) \
    BOOST_PP_NIL)

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_LOCAL_PERCOLATEERROR_OR_CONTINUE2( \
  parsedtype_varname, psblerrors) \
    BOOST_PP_IIF( \
      WG_PP_STARTSWITH_BOOST_PP_NIL(psblerrors), \
      ( WG_PP_MARKER_NOOP parsedtype_varname ), \
      ( WG_PP_MARKER_ERROR WG_PP_EATTAILTOKEN_BOOST_PP_NIL(psblerrors) ) )


#endif //WG_PP_VARDCLN_HH_
