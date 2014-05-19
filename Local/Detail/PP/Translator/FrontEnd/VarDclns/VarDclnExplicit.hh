#ifndef WG_PP_VARDCLN_EXPLICIT_HH_
#define WG_PP_VARDCLN_EXPLICIT_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Translator/Keywords.hh>
#include <WG/Local/Detail/PP/Translator/Utils.hh>

//###########
//Public APIs
//###########

// explicitvardcln:
//   explicit-type-var-dcln
// Expands to the following:
//   (WG_PP_MARKER_NOOP parsed-explicit-type) (var-name)
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE(explicitvardcln, istpl) \
  WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL1(explicitvardcln)

// explicitvardcln:
//   explicit-type-var-dcln
// Expands to the following:
//   (WG_PP_MARKER_NOOP parsed-explicit-non-local-type) (var-name)
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_VARDCLN_EXPLICIT_NLT_TUPLIZE(explicitvardcln, istpl) \
  WG_PP_VARDCLN_EXPLICIT_TUPLIZE_NONLOCAL(explicitvardcln)

//###########
//Impl Macros
//###########

#define WG_PP_VARDCLN_EXPLICIT_EXPAND1(x) x
#define WG_PP_VARDCLN_EXPLICIT_EXPAND2(x) x

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL1(explicitvardcln) \
  BOOST_PP_IIF( \
    WG_PP_KEYWORDS_STARTSWITH_TYPE(explicitvardcln), \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_NONLOCAL, \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_LOCAL_OR_SPITERROR) (explicitvardcln)

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_LOCAL_OR_SPITERROR(explicitvardcln) \
  BOOST_PP_IIF( \
    WG_PP_KEYWORDS_STARTSWITH_LCLTYPE(explicitvardcln), \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_LOCAL, \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_MISSING_TYPE_ERROR) (explicitvardcln)

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_MISSING_TYPE_ERROR(explicitvardcln) \
  ( \
    WG_PP_MARKER_ERROR \
    WG_LCL_Error_missing_type_in_explicit_type_var_dcln \
  )

//-----------------------
// Non-Local Type Macros.
//-----------------------

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_NONLOCAL(explicitvardcln) \
  WG_PP_VARDCLN_EXPLICIT_EXPAND1( \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_NONLOCAL2 \
    BOOST_PP_LPAREN() \
      WG_PP_KEYWORDS_ADDCOMMAAFTER_TYPETUPLE(explicitvardcln) \
      BOOST_PP_NIL \
    BOOST_PP_RPAREN() )

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_NONLOCAL2(typetuple, var) \
  BOOST_PP_IIF( \
    WG_PP_STARTSWITH_BOOST_PP_NIL(var), \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_NONLOCAL_SPITERROR, \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_NONLOCAL3) (typetuple, var)

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_NONLOCAL_SPITERROR(typetuple, var) \
  ( \
    WG_PP_MARKER_ERROR \
    WG_LCL_Error_missing_variable_name \
  )

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_NONLOCAL3(typetuple, var) \
  (WG_PP_MARKER_NOOP typetuple) ( WG_PP_EATTAILTOKEN_BOOST_PP_NIL(var) )

//-------------------
// Local Type Macros.
//-------------------

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_LOCAL(explicitvardcln) \
  WG_PP_VARDCLN_EXPLICIT_EXPAND2( \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_LOCAL2 \
    BOOST_PP_LPAREN() \
      WG_PP_KEYWORDS_ADDCOMMAAFTER_LCLTYPETUPLE(explicitvardcln) \
      BOOST_PP_NIL \
    BOOST_PP_RPAREN() )

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_LOCAL2(lcltypetuple, tq_varname) \
  BOOST_PP_LPAREN() \
    WG_PP_MARKER_NOOP lcltypetuple \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_LOCAL3(tq_varname)

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_LOCAL3(tq_varname) \
  BOOST_PP_IIF( \
    WG_PP_KEYWORDS_STARTSWITH_CONST(tq_varname), \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_LOCAL4_CONST, \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_LOCAL5) (tq_varname)

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_LOCAL4_CONST(tq_varname) \
  (const) \
  WG_PP_VARDCLN_EXPLICIT_TUPLIZE_LOCAL5( \
    WG_PP_KEYWORDS_EATHEAD_CONST(tq_varname) )

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_LOCAL5(tq_varname) \
  BOOST_PP_IIF( \
    WG_PP_KEYWORDS_STARTSWITH_REF(tq_varname), \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_LOCAL5_REF, \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_LOCAL5_VARNAME) (tq_varname)

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_LOCAL5_REF(tq_varname) \
  (ref) \
  WG_PP_VARDCLN_EXPLICIT_TUPLIZE_LOCAL5_VARNAME( \
    WG_PP_KEYWORDS_EATHEAD_REF(tq_varname) )

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_LOCAL5_VARNAME(varname) \
  BOOST_PP_RPAREN() \
  ( \
    BOOST_PP_IIF( \
      WG_PP_STARTSWITH_BOOST_PP_NIL(varname), \
      WG_PP_VARDCLN_EXPLICIT_TUPLIZE_LOCAL5_VARNAME_ERROR, \
      WG_PP_EATTAILTOKEN_BOOST_PP_NIL) (varname)\
  )

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_LOCAL5_VARNAME_ERROR(varname) \
  WG_PP_MARKER_ERROR \
  WG_LCL_Error_missing_variable_name

#endif //WG_PP_VARDCLN_EXPLICIT_HH_
