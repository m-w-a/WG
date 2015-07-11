#ifndef WG_PP_VARDCLN_IMPLICIT2_HH_
#define WG_PP_VARDCLN_IMPLICIT2_HH_

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
//   { ( WG_PP_MARKER_ERROR ... | WG_PP_MARKER_DEDUCEDTYPE parsed-deduced-type )
//     ( WG_PP_MARKER_ERROR ... | var-name ) }
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUNDDCLN(implicitvardcln, istpl) \
  WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUNDDCLN_IMPL(implicitvardcln, istpl)

// implicitvardcln:
//   implicit-type-var-dcln
// valueexpr:
//   value-expr
// Expands to the following:
//   { ( WG_PP_MARKER_ERROR ... | WG_PP_MARKER_DEDUCEDTYPE parsed-deduced-type )
//     ( WG_PP_MARKER_ERROR ... | var-name ) }
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_SETDCLN(implicitvardcln, valueexpr, istpl) \
  WG_PP_VARDCLN_IMPLICIT_TUPLIZE_SETDCLN_IMPL(implicitvardcln, valueexpr, istpl)

//###########
//Impl Macros
//###########

#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUNDDCLN_IMPL(implicitvardcln, istpl) \
  WG_PP_VARDCLN_IMPLICIT_COMPUTEQUALIFIERS( \
    implicitvardcln, \
    istpl, \
    WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUNDDCLN_IMPL2, \
    ~)

#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_BOUNDDCLN_IMPL2( \
  callbackdata, istpl, isconst, isref, varname, tuplizedvarname) \
    BOOST_PP_IIF( \
      WG_PP_KEYWORDS_STARTSWITH_THISU(varname), \
      WG_PP_VARDCLN_IMPLICIT_TUPLIZE_TYPE_THISU, \
      WG_PP_VARDCLN_IMPLICIT_TUPLIZE_TYPE) \
    (varname, istpl, isconst, isref) \
    \
    tuplizedvarname

#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_SETDCLN_IMPL( \
  implicitvardcln, valueexpr, istpl) \
    WG_PP_VARDCLN_IMPLICIT_COMPUTEQUALIFIERS( \
      implicitvardcln, \
      istpl, \
      WG_PP_VARDCLN_IMPLICIT_TUPLIZE_SETDCLN_IMPL2, \
      valueexpr)

#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_SETDCLN_IMPL2( \
  valueexpr, istpl, isconst, isref, varname, tuplizedvarname) \
    WG_PP_VARDCLN_IMPLICIT_TUPLIZE_TYPE(valueexpr, istpl, isconst, isref) \
    tuplizedvarname

//-----------------
//COMPUTEQUALIFIERS
//-----------------

// callback:
//   a function-like macro that will accept the following arguments:
//   "istpl, isconst, isref, varname, tuplizedvarname"
#define WG_PP_VARDCLN_IMPLICIT_COMPUTEQUALIFIERS( \
  implicitvardcln, istpl, callback, callbackdata) \
    WG_PP_VARDCLN_IMPLICIT_COMPUTEQUALIFIERS1( \
      implicitvardcln BOOST_PP_NIL, istpl, callback, callbackdata)

#define WG_PP_VARDCLN_IMPLICIT_COMPUTEQUALIFIERS1( \
  implicitvardcln, istpl, callback, callbackdata) \
    WG_PP_VARDCLN_IMPLICIT_COMPUTEQUALIFIERS2( \
      istpl, \
      callback, \
      callbackdata, \
      WG_PP_KEYWORDS_STARTSWITH_CONST(implicitvardcln), \
      BOOST_PP_IIF( \
        WG_PP_KEYWORDS_STARTSWITH_CONST(implicitvardcln), \
        WG_PP_KEYWORDS_EATHEAD_CONST(implicitvardcln), \
        implicitvardcln) )

#define WG_PP_VARDCLN_IMPLICIT_COMPUTEQUALIFIERS2( \
  istpl, callback, callbackdata, isconst, noconst_implicitvardcln) \
    WG_PP_VARDCLN_IMPLICIT_COMPUTEQUALIFIERS3( \
      istpl, \
      callback, \
      callbackdata, \
      isconst, \
      WG_PP_KEYWORDS_STARTSWITH_REF(noconst_implicitvardcln), \
      BOOST_PP_IIF( \
        WG_PP_KEYWORDS_STARTSWITH_REF(noconst_implicitvardcln), \
        WG_PP_KEYWORDS_EATHEAD_REF(noconst_implicitvardcln), \
        noconst_implicitvardcln) )

#define WG_PP_VARDCLN_IMPLICIT_COMPUTEQUALIFIERS3( \
  istpl, callback, callbackdata, isconst, isref, varname) \
    callback ( \
      callbackdata, \
      istpl, \
      isconst, \
      isref, \
      BOOST_PP_IIF( \
        WG_PP_STARTSWITH_BOOST_PP_NIL(varname), \
        varname BOOST_PP_EMPTY, \
        WG_PP_EATTAILTOKEN_BOOST_PP_NIL(varname) BOOST_PP_EMPTY) (), \
      WG_PP_VARDCLN_IMPLICIT_TUPLIZE_VAR(varname) )

//------------
//TUPLIZE_TYPE
//------------

#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_TYPE(expr, istpl, isconst, isref) \
  ( \
    BOOST_PP_CAT( \
      WG_PP_VARDCLN_IMPLICIT_TUPLIZE_TYPE_, \
      BOOST_PP_CAT(isconst, isref) ) \
    (expr, istpl) \
  )

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

//------------------
//TUPLIZE_TYPE_THISU
//------------------

#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_TYPE_THISU(bvar, istpl, isconst, isref) \
  ( \
    BOOST_PP_CAT( \
      WG_PP_VARDCLN_IMPLICIT_TUPLIZE_TYPE_THISU_, \
      BOOST_PP_CAT(isconst, isref) ) \
    (bvar, istpl) \
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

//--------------------
//TUPLIZE_VAR(varname)
//--------------------

#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_VAR(varname) \
  ( \
    BOOST_PP_IIF( \
      WG_PP_STARTSWITH_BOOST_PP_NIL(varname), \
      WG_PP_VARDCLN_IMPLICIT_TUPLIZE_VAR_ERROR, \
      WG_PP_EATTAILTOKEN_BOOST_PP_NIL) \
    (varname) \
  )

#define WG_PP_VARDCLN_IMPLICIT_TUPLIZE_VAR_ERROR(var) \
  WG_PP_MARKER_ERROR \
  WG_LCL_Error_missing_variable_name
#endif /* WG_PP_VARDCLN_IMPLICIT2_HH_ */
