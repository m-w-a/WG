#ifndef WG_PP_VARDCLN_EXPLICIT_HH_
#define WG_PP_VARDCLN_EXPLICIT_HH_

#include <boost/preprocessor.hpp>
#include <boost/utility/identity_type.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Translator/Keywords.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/SplitHeadFromTokens.hh>
#include <WG/Local/Detail/PP/Translator/Utils.hh>

//###########
//Public APIs
//###########

// explicitvardcln:
//   explicit-type-var-dcln
// Expands to the following:
//   (parsed-explicit-type) (var-name)
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE(explicitvardcln, istpl) \
  WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL1(explicitvardcln, istpl)

// explicitvardcln:
//   explicit-type-var-dcln
// Expands to the following:
//   (parsed-explicit-non-local-type) (var-name)
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_VARDCLN_EXPLICIT_NLT_TUPLIZE(explicitvardcln, istpl) \
  WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_NONLOCAL1(explicitvardcln, istpl)

//###########
//Impl Macros
//###########

#define WG_PP_VARDCLN_EXPLICIT_EXPAND1(x) x
#define WG_PP_VARDCLN_EXPLICIT_EXPAND2(x) x
#define WG_PP_VARDCLN_EXPLICIT_EXPAND3(x) x

#define WG_PP_VARDCLN_EXPLICIT_ISNONLOCALTYPE(explicitvardcln) \
  BOOST_PP_IIF( \
    WG_PP_ISNEXTTOKEN_A_TUPLE(1, explicitvardcln), \
    WG_PP_MAP_TO_1_ARG1, \
    WG_PP_KEYWORDS_STARTSWITH_PPESCAPE) (explicitvardcln)

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL1(explicitvardcln, istpl) \
  BOOST_PP_IIF( \
    WG_PP_VARDCLN_EXPLICIT_ISNONLOCALTYPE(explicitvardcln), \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_NONLOCAL1, \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL2) (explicitvardcln, istpl)

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL2(explicitvardcln, ignore) \
  BOOST_PP_IIF( \
    WG_PP_KEYWORDS_STARTSWITH_LOCAL(explicitvardcln), \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL, \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_MISSING_TYPE_ERRMSG) (explicitvardcln)

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_MISSING_TYPE_ERRMSG(explicitvardcln) \
  ( WG_PP_ERROR ERROR_missing_type_in_explicit_type_var_dcln )

//-----------------------
// Non-Local Type Macros.
//-----------------------

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_NONLOCAL_PPESCAPE( \
  explicittype, istpl) \
    BOOST_PP_LPAREN() \
    WG_PP_TRNSLTR_UTILS_ADDTYPENAME(istpl) \
    BOOST_PP_CAT( \
      WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_NONLOCAL_, \
      explicittype) \
    BOOST_PP_RPAREN()
#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_NONLOCAL_ppescape(explicittype) \
  BOOST_IDENTITY_TYPE (explicittype) \
  BOOST_PP_RPAREN() BOOST_PP_LPAREN()

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_NONLOCAL1(explicitvardcln, istpl) \
  BOOST_PP_IIF( \
    WG_PP_ISNEXTTOKEN_A_TUPLE(1, explicitvardcln), \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_NONPREFIXED_NONLOCAL1, \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_NONLOCAL_PPESCAPE) \
  (explicitvardcln, istpl)

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_NONPREFIXED_NONLOCAL1( \
  explicitvardcln, ignore) \
    WG_PP_VARDCLN_EXPLICIT_EXPAND1( \
      WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_NONPREFIXED_NONLOCAL2 explicitvardcln) \
    BOOST_PP_RPAREN()
#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_NONPREFIXED_NONLOCAL2(explicittype) \
  (explicittype) BOOST_PP_LPAREN()

//-------------------
// Local Type Macros.
//-------------------

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
    WG_PP_KEYWORDS_STARTSWITH_CONST(tq_varname), \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL4_CONST, \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL5) (tq_varname)

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL4_CONST(tq_varname) \
  (const) \
  WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL5( \
    WG_PP_KEYWORDS_EAT_HEADKEYWORD(tq_varname) )

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL5(tq_varname) \
  BOOST_PP_IIF( \
    WG_PP_KEYWORDS_STARTSWITH_REF(tq_varname), \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL5_REF, \
    WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL5_VARNAME) (tq_varname)

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL5_REF(tq_varname) \
  (ref) \
  WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL5_VARNAME( \
    WG_PP_KEYWORDS_EAT_HEADKEYWORD(tq_varname) )

#define WG_PP_VARDCLN_EXPLICIT_TUPLIZE_IMPL_LOCAL5_VARNAME(varname) \
  BOOST_PP_RPAREN() (varname)

#endif //WG_PP_VARDCLN_EXPLICIT_HH_
