#ifndef WG_PP_VARDCLN_IMPLICIT_HH_
#define WG_PP_VARDCLN_IMPLICIT_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/Translator/Keywords.hh>
#include <WG/Local/Detail/PP/PP.hh>
#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <WG/Local/Detail/PP/Translator/Utils.hh>

//###########
//Public APIs
//###########

// implicitvardcln:
//   implicit-type-var-dcln
// Expands to the following:
//   (WG_PP_MARKER_DEDUCEDTYPE parsed-deduced-type) (var-name)
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_1ARG(implicitvardcln, istpl) \
  WG_PP_VARDCLN_IMPLICIT_TUPLIZE(implicitvardcln, 0, BOOST_PP_NIL, istpl)

// implicitvardcln:
//   implicit-type-var-dcln
// valueexpr:
//   value-expr
// Expands to the following:
//   (WG_PP_MARKER_DEDUCEDTYPE parsed-deduced-type) (var-name)
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_2ARG(implicitvardcln, valueexpr, istpl) \
  WG_PP_VARDCLN_IMPLICIT_TUPLIZE(implicitvardcln, 1, valueexpr, istpl)
  
//###########
//Impl Macros
//###########

// Need to use these instead of BOOST_PP_EXPAND because for some reason the 
//  latter prevents the macro expansion of BOOST_PP_EXPANDs in these macros.
#define WG_PP_VARDCLN_IMPLICIT_EXPAND1(x) x
#define WG_PP_VARDCLN_IMPLICIT_EXPAND2(x) x

#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE( \
  implicitvardcln, hasvalueexpr, valueexpr, istpl) \
    WG_PP_VARDCLN_IMPLICIT_TUPLIZE1( \
      implicitvardcln BOOST_PP_NIL, hasvalueexpr, valueexpr, istpl)

#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE1( \
  implicitvardcln, hasvalueexpr, valueexpr, istpl) \
    WG_PP_VARDCLN_IMPLICIT_EXPAND1( \
      WG_PP_VARDCLN_IMPLICIT_TUPLIZE2 \
      BOOST_PP_IIF( \
        WG_PP_KEYWORDS_STARTSWITH_CONST(implicitvardcln), \
        ( 1, WG_PP_KEYWORDS_EATHEAD_CONST(implicitvardcln), hasvalueexpr, \
          valueexpr, istpl ), \
        ( 0, implicitvardcln, hasvalueexpr, valueexpr, istpl ) ))

#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE2( \
  isconstqualified, implicitvardcln, hasvalueexpr, valueexpr, istpl) \
    WG_PP_VARDCLN_IMPLICIT_EXPAND2( \
      BOOST_PP_IIF( \
        BOOST_PP_COMPL(hasvalueexpr), \
        WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUND, \
        WG_PP_VARDCLN_IMPLICIT_TUPLIZE_SET) \
      BOOST_PP_LPAREN() \
        isconstqualified BOOST_PP_COMMA() \
        BOOST_PP_SEQ_ENUM( \
          BOOST_PP_IIF( \
            WG_PP_KEYWORDS_STARTSWITH_REF(implicitvardcln), \
            (1)  ( WG_PP_KEYWORDS_EATHEAD_REF(implicitvardcln) ), \
            (0) ( implicitvardcln ) ) \
          BOOST_PP_EXPR_IIF( \
            hasvalueexpr, \
            ( valueexpr ) ) \
          (istpl) ) \
      BOOST_PP_RPAREN() )

#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_SET( \
  isconstqualified, isrefqualified, var, valueexpr, istpl) \
    ( \
      BOOST_PP_CAT( \
        WG_PP_VARDCLN_IMPLICIT_TUPLIZE_TYPE_, \
        BOOST_PP_CAT(isconstqualified, isrefqualified) ) (valueexpr, istpl) \
    ) \
    ( WG_PP_VARDCLN_IMPLICIT_TUPLIZE_VAR(var) )

#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUND( \
  isconstqualified, isrefqualified, var, istpl) \
    ( \
      BOOST_PP_IIF( \
        WG_PP_STARTSWITH_BOOST_PP_NIL(var), \
        BOOST_PP_NIL WG_PP_MAPTO_NOTHING_ARG4, \
        WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUND_TYPE) \
      (isconstqualified, isrefqualified, var, istpl) \
    ) \
    ( WG_PP_VARDCLN_IMPLICIT_TUPLIZE_VAR(var) )

#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUND_TYPE( \
  isconstqualified, isrefqualified, var, istpl) \
    BOOST_PP_CAT( \
      BOOST_PP_IIF( \
        WG_PP_KEYWORDS_STARTSWITH_THISU(var), \
        WG_PP_VARDCLN_IMPLICIT_TUPLIZE_TYPE_THISU_, \
        WG_PP_VARDCLN_IMPLICIT_TUPLIZE_TYPE_), \
      BOOST_PP_CAT(isconstqualified, isrefqualified) ) \
    (WG_PP_EATTAILTOKEN_BOOST_PP_NIL(var), istpl)

#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_VAR(var) \
  BOOST_PP_IIF( \
    WG_PP_STARTSWITH_BOOST_PP_NIL(var), \
    WG_PP_VARDCLN_IMPLICIT_TUPLIZE_VAR_ERROR, \
    WG_PP_EATTAILTOKEN_BOOST_PP_NIL) (var)

#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_VAR_ERROR(var) \
  WG_PP_MARKER_ERROR \
  WG_LCL_Error_missing_variable_name

#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_TYPE_00(expr, istpl) \
  WG_PP_MARKER_DEDUCEDTYPE \
  WG_PP_KEYWORDS_TYPE ( WG_PP_TRNSLTR_UTILS_TYPEOF(istpl, expr) )
#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_TYPE_01(expr, istpl) \
  WG_PP_MARKER_DEDUCEDTYPE \
    WG_PP_KEYWORDS_TYPE ( WG_PP_TRNSLTR_UTILS_ADDTYPENAME(istpl) \
      ::boost::add_reference< WG_PP_TRNSLTR_UTILS_TYPEOF(istpl, expr) >::type )
#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_TYPE_10(expr, istpl) \
  WG_PP_MARKER_DEDUCEDTYPE \
    WG_PP_KEYWORDS_TYPE ( WG_PP_TRNSLTR_UTILS_ADDTYPENAME(istpl) \
      ::boost::add_const< WG_PP_TRNSLTR_UTILS_TYPEOF(istpl, expr) >::type )
#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_TYPE_11(expr, istpl) \
  WG_PP_MARKER_DEDUCEDTYPE \
    WG_PP_KEYWORDS_TYPE \
    ( \
      WG_PP_TRNSLTR_UTILS_ADDTYPENAME(istpl) ::boost::add_reference \
      < \
        WG_PP_TRNSLTR_UTILS_ADDTYPENAME(istpl) ::boost::add_const \
        < \
          WG_PP_TRNSLTR_UTILS_TYPEOF(istpl, expr) \
        >::type \
      >::type \
    )

#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_TYPE_THISU_00(bvar, istpl) \
  WG_PP_MARKER_DEDUCEDTYPE \
  WG_PP_KEYWORDS_TYPE ( WG_PP_TRNSLTR_UTILS_TYPEOF(istpl, this) const )
#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_TYPE_THISU_01(bvar, istpl) \
  WG_PP_VARDCLN_IMPLICIT_TUPLIZE_TYPE_THISU_ERRMSG()
#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_TYPE_THISU_10(bvar, istpl) \
  WG_PP_MARKER_DEDUCEDTYPE \
  WG_PP_KEYWORDS_TYPE \
  ( \
    WG_PP_TRNSLTR_UTILS_ADDTYPENAME(istpl) ::boost::add_const \
    < \
      WG_PP_TRNSLTR_UTILS_ADDTYPENAME(istpl) ::boost::add_pointer \
      < \
        WG_PP_TRNSLTR_UTILS_ADDTYPENAME(istpl) ::boost::add_const \
        < \
          WG_PP_TRNSLTR_UTILS_TYPEOF(istpl, *this) \
        >::type \
      >::type \
    >::type \
  )
#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_TYPE_THISU_11(bvar, istpl) \
  WG_PP_VARDCLN_IMPLICIT_TUPLIZE_TYPE_THISU_ERRMSG()

#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_TYPE_THISU_ERRMSG() \
  WG_PP_MARKER_ERROR \
  WG_LCL_Error_ref_keyword_cannot_be_used_with_thisu_keyword

#endif //WG_PP_VARDCLN_IMPLICIT_HH_
