#ifndef WG_PP_VARDCLN_EXPLICIT_HH_
#define WG_PP_VARDCLN_EXPLICIT_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Translator/Keywords.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/SplitHeadFromTokens.hh>

//###########
//Public APIs
//###########

// Expands to the following:
//   (parsed-explicit-type) (var-name)
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE(explicitvardcln) \
  WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL(explicitvardcln)

// Expands to the following:
//   (parsed-explicit-non-local-type) (var-name)
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_VARDCLN_EXPLICIT_NLT_TUPLIZE(explicitvardcln) \
  WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_NONLOCAL(explicitvardcln)

//###########
//Impl Macros
//###########

#define WG_PP_VARDCLN_EXPLICIT_EXPAND1(x) x
#define WG_PP_VARDCLN_EXPLICIT_EXPAND2(x) x

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL(explicitvardcln) \
  BOOST_PP_CAT( \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_, \
    BOOST_PP_EXPR_IIF(WG_PP_ISNEXTTOKEN_A_TUPLE(1, explicitvardcln), NONLOCAL) \
    BOOST_PP_EXPR_IIF(WG_PP_KEYWORDS_STARTWITH_LOCAL(explicitvardcln), LOCAL) \
    BOOST_PP_EMPTY) () \
  (explicitvardcln)

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_BOOST_PP_EMPTY() \
  ( WG_PP_ERROR ERROR_missing_type_in_explicit_type_var_dcln )

// NOTE: can't use WG_PP_SPLITHEADTUPLEFROMTOKENS in implementation because
//   this macro will/might be called via a WG_PP_SPLITHEADTUPLEFROMTOKENS
//   callback macro, thus disabling the implementation's own 
//   WG_PP_SPLITHEADTUPLEFROMTOKENS invocation.
#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_NONLOCAL(explicitvardcln) \
  WG_PP_VARDCLN_EXPLICIT_EXPAND1( \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_NONLOCAL1 \
    BOOST_PP_LPAREN() \
      WG_PP_ADDCOMMA_AFTERTUPLE_ARG1 explicitvardcln \
    BOOST_PP_RPAREN() )
#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_NONLOCAL1(type, varname) \
  type (varname)

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL(explicitvardcln) \
  WG_PP_VARDCLN_EXPLICIT_EXPAND2( \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL2 \
    BOOST_PP_LPAREN() \
      BOOST_PP_CAT( \
        WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL_, \
        explicitvardcln) \
    BOOST_PP_RPAREN() )
#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL_local(localvalue) \
  localvalue BOOST_PP_COMMA()

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL2(localvalue, tq_varname) \
  BOOST_PP_LPAREN() \
    local (localvalue) WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL3(tq_varname)

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL3(tq_varname) \
  BOOST_PP_IIF( \
    WG_PP_KEYWORDS_STARTWITH_CONST(tq_varname), \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL4_CONST, \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL5) (tq_varname)

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL4_CONST(tq_varname) \
  (const) \
  WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL5( \
    WG_PP_KEYWORDS_EAT_HEADKEYWORD(tq_varname) )

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL5(tq_varname) \
  BOOST_PP_IIF( \
    WG_PP_KEYWORDS_STARTWITH_REF(tq_varname), \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL5_REF, \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL5_VARNAME) (tq_varname)

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL5_REF(tq_varname) \
  (ref) \
  WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL5_VARNAME( \
    WG_PP_KEYWORDS_EAT_HEADKEYWORD(tq_varname) )

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL5_VARNAME(varname) \
  BOOST_PP_RPAREN() (varname)

#endif //WG_PP_VARDCLN_EXPLICIT_HH_
