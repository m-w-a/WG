#ifndef WG_PP_LCLFUNCTION_CODEGENUTILS_HH_
#define WG_PP_LCLFUNCTION_CODEGENUTILS_HH_

#include <boost/preprocessor.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <WG/Local/Detail/PP/Translator/BackEnd/ID.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/LclFunction/SymbolTable.hh>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/Markers.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/TypeAliaser.hh>
#include <WG/Local/Detail/PP/LclFunction/FunctionOperatorUtils.hh>
#include <WG/Local/Detail/PP/LclFunction/ConstInvariance.hh>
#include <WG/Local/Detail/LclFunction/Binder.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/TypeExtractor.hh>

//###########
//Public APIs
//###########

// Expands to:
//   Line specific id.
#define WG_PP_LCLFUNCTION_CGUTILS_MAKENAMEUNIQUE(name) \
  WG_PP_LCLFUNCTION_CGUTILS_MAKENAMEUNIQUE_IMPL(name)

//------------
//TypesAliaser
//------------

#define WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_DCLN(symbtbl, function_name) \
  WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_DCLN_IMPL(symbtbl, function_name)

//----------------
//Intermediate Ops
//----------------

#define WG_PP_LCLFUNCTION_CGUTILS_REPLACEDEDUCEDTYPES(symbtbl, function_name) \
  WG_PP_LCLFUNCTION_CGUTILS_REPLACEDEDUCEDTYPES_IMPL(symbtbl, function_name)

#define WG_PP_LCLFUNCTION_CGUTILS_REMOVEMARKERS(symbtbl) \
  WG_PP_LCLFUNCTION_CGUTILS_REMOVEMARKERS_IMPL(symbtbl)

//--------------
//CapturedValues
//--------------

#define WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPENAME(function_name) \
  WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPENAME_IMPL(function_name)

#define WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPEDCLN(symbtbl, function_name) \
  WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPEDCLN_IMPL(symbtbl, function_name)

//-------------
//LocalFunction
//-------------

#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_RETURNTYPE(symbtbl) \
  WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_RETURNTYPE_IMPL(symbtbl)

//-------------
//GlobalFunctor
//-------------

// Expands to:
//   Line specific id.
#define WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTORTYPE_NAME(function_name) \
  WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTORTYPE_NAME_IMPL(function_name)

#define WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTOROBJ_DCLN( \
  symbtbl, function_name) \
    WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTOROBJ_DCLN_IMPL( \
      symbtbl, function_name)

//------------
//LocalFunctor
//------------

#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTORTYPE_STANDARDTYPENAMES_DCLN( \
  symbtbl, global_functor_type_name) \
    WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTORTYPE_STANDARDTYPENAMES_DCLN_IMPL1( \
      symbtbl, global_functor_type_name)

#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTORTYPE_USERCALLBACKMETHOD_START( \
  symbtbl, function_name, global_functor_type_name, captured_values_type_name) \
    WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTORTYPE_USERCALLBACKMETHOD_START_IMPL( \
      symbtbl, function_name, global_functor_type_name, captured_values_type_name)

#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTORTYPE_USERCALLBACKMETHOD_END() \
  WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTORTYPE_USERCALLBACKMETHOD_END_IMPL()

//###########
//Impl Macros
//###########

//-----
//Utils
//-----

#define WG_PP_LCLFUNCTION_CGUTILS_GLOBALID() WG_PP_ID_MAKE_GLOBAL(lclfunction)

#define WG_PP_LCLFUNCTION_CGUTILS_MAKENAMEUNIQUE_IMPL(name) \
  WG_PP_ID_CAT( \
    WG_PP_ID_CAT(WG_PP_LCLFUNCTION_CGUTILS_GLOBALID(), name), \
    __LINE__)

// Expands to:
//   BOOST_PP_NIL | {non-local-type}+
//
// symbtbl_type_seq:
//   { ( non-local-type ) }+
#define WG_PP_LCLFUNCTION_CGUTILS_TYPESEQ_TO_CAPTUREDTYPESEQ( \
  istpl, gettypemacro, dcln_seq) \
    WG_PP_SEQ_FOR_EACH( \
      WG_PP_LCLFUNCTION_CGUTILS_TYPESEQ_TO_CAPTUREDTYPESEQ_TRANSFORM, \
      (istpl)(gettypemacro), \
      dcln_seq)

// WG_PP_SEQ_FOR_EACH functor.
#define WG_PP_LCLFUNCTION_CGUTILS_TYPESEQ_TO_CAPTUREDTYPESEQ_TRANSFORM( \
  r, istpl_gettypemacro, dcln) \
    WG_PP_LCLFUNCTION_CGUTILS_TYPESEQ_TO_CAPTUREDTYPESEQ_TRANSFORM_TUPLE( \
      BOOST_PP_SEQ_ELEM(0, istpl_gettypemacro), \
      BOOST_PP_SEQ_ELEM(1, istpl_gettypemacro), \
      dcln)

#define WG_PP_LCLFUNCTION_CGUTILS_TYPESEQ_TO_CAPTUREDTYPESEQ_TRANSFORM_TUPLE( \
  istpl, getttypemacro, dcln) \
    ( \
      WG_PP_TRNSLTR_UTILS_ADDTYPENAME(istpl) \
      wg::local::detail::bind_traits \
      < \
        WG_PP_PARSEDTYPE_EXTRACTCPPTYPE( getttypemacro(dcln) ) \
      >::binder_type \
    )

//------------
//TypesAliaser
//------------

// Expands to:
//   Line specific id.
#define WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_NAME(function_name) \
  WG_PP_LCLFUNCTION_CGUTILS_MAKENAMEUNIQUE( \
    WG_PP_ID_CAT(captured_types_aliaser, function_name))

#define WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_DCLN_SPECSEQ() \
  ( \
    (varbind) \
    (WG_PP_LCLFUNCTION_SYMBOLTABLE_GETDCLNS_BOUNDVAR) \
    (WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_GETTYPE_BOUNDVAR) \
  ) \
  ( \
    (varset) \
    (WG_PP_LCLFUNCTION_SYMBOLTABLE_GETDCLNS_SETVAR) \
    (WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_GETTYPE_SETVAR) \
  )

#define WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_REPLACER_SPECSEQ() \
  ( \
    (WG_PP_LCLFUNCTION_SYMBOLTABLE_GETDCLNS_BOUNDVAR) \
    (WG_PP_LCLFUNCTION_SYMBOLTABLE_SETDCLNS_BOUNDVAR) \
  ) \
  ( \
    (WG_PP_LCLFUNCTION_SYMBOLTABLE_GETDCLNS_SETVAR) \
    (WG_PP_LCLFUNCTION_SYMBOLTABLE_SETDCLNS_SETVAR) \
  )

#define WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_REPLACER_CALLBACKDATA( \
  istpl, typealiasername, replacementpolicy) \
    (istpl) \
    (typealiasername) \
    (replacementpolicy) \
    ( \
      (varbind) \
      (WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_GETTYPE_BOUNDVAR) \
      (WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_SETTYPE_BOUNDVAR) \
    ) \
    ( \
      (varset) \
      (WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_GETTYPE_SETVAR) \
      (WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_SETTYPE_SETVAR) \
    )

#define WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_DCLN_IMPL(symbtbl, function_name) \
  WG_PP_TYPEALIASER_DCLN( \
    WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_NAME(function_name), \
    DEDUCEDTYPES, \
    symbtbl, \
    WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_DCLN_SPECSEQ() )

//-------------------
//EraseMarkers Utils.
//-------------------

#define WG_PP_LCLFUNCTION_CGUTILS_ERASEMARKERS_SPECSEQ() \
  ( \
    (WG_PP_LCLFUNCTION_SYMBOLTABLE_GETDCLNS_BOUNDVAR) \
    (WG_PP_LCLFUNCTION_SYMBOLTABLE_SETDCLNS_BOUNDVAR) \
  ) \
  ( \
    (WG_PP_LCLFUNCTION_SYMBOLTABLE_GETDCLNS_SETVAR) \
    (WG_PP_LCLFUNCTION_SYMBOLTABLE_SETDCLNS_SETVAR) \
  )

#define WG_PP_LCLFUNCTION_CGUTILS_ERASEMARKERS_CALLBACKDATA() \
  ( \
    (WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_GETTYPE_BOUNDVAR) \
    (WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_SETTYPE_BOUNDVAR) \
  ) \
  ( \
    (WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_GETTYPE_SETVAR) \
    (WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_SETTYPE_SETVAR) \
  )

//----------------
//Intermediate Ops
//----------------

#define WG_PP_LCLFUNCTION_CGUTILS_REPLACEDEDUCEDTYPES_IMPL(symbtbl, function_name) \
  WG_PP_STUTIL_REPLACESEQ( \
    symbtbl, \
    WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_REPLACER_SPECSEQ(), \
    WG_PP_TYPEALIASER_REPLACETYPE, \
    WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_REPLACER_CALLBACKDATA( \
      WG_PP_LCLFUNCTION_SYMBOLTABLE_ISTPL(symbtbl), \
      WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_NAME(function_name), \
      DEDUCEDTYPES) )

#define WG_PP_LCLFUNCTION_CGUTILS_REMOVEMARKERS_IMPL(symbtbl) \
  WG_PP_STUTIL_REPLACESEQ( \
    symbtbl, \
    WG_PP_LCLFUNCTION_CGUTILS_ERASEMARKERS_SPECSEQ(), \
    WG_PP_TRNSLTR_MARKERS_ERASEMARKERSINSEQ, \
    WG_PP_LCLFUNCTION_CGUTILS_ERASEMARKERS_CALLBACKDATA() )

//--------------
//CapturedValues
//--------------

#define WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPENAME_IMPL(function_name) \
  WG_PP_LCLFUNCTION_CGUTILS_MAKENAMEUNIQUE( \
    WG_PP_ID_CAT(captured_values_type, function_name))

#define WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPEDCLN_IMPL( \
  symbtbl, function_name) \
    typedef WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPE(symbtbl) \
      WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPENAME(function_name) ;

#define WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPE(symbtbl) \
  boost::tuple \
  < \
    WG_PP_SEQ_ENUM( \
      WG_PP_SEQ_JOIN_ARG2( \
        WG_PP_LCLFUNCTION_CGUTILS_TYPESEQ_TO_CAPTUREDTYPESEQ( \
          WG_PP_LCLFUNCTION_SYMBOLTABLE_ISTPL(symbtbl), \
          WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_GETTYPE_BOUNDVAR, \
          WG_PP_LCLFUNCTION_SYMBOLTABLE_GETDCLNS_BOUNDVAR(symbtbl)), \
        WG_PP_LCLFUNCTION_CGUTILS_TYPESEQ_TO_CAPTUREDTYPESEQ( \
          WG_PP_LCLFUNCTION_SYMBOLTABLE_ISTPL(symbtbl), \
          WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_GETTYPE_SETVAR, \
          WG_PP_LCLFUNCTION_SYMBOLTABLE_GETDCLNS_SETVAR(symbtbl)) )) \
  >

#define WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVALUES_DCLN( \
  symbtbl, captured_values_objname) \
    WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVALUES_DCLN2( \
      symbtbl, \
      captured_values_objname, \
      0, \
      BOUNDVAR) \
    WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVALUES_DCLN2( \
      symbtbl, \
      captured_values_objname, \
      WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLNS_SIZE_BOUNDVAR(symbtbl), \
      SETVAR)

#define WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVALUES_DCLN2( \
  symbtbl, captured_values_objname, offset, suffix) \
    WG_PP_SEQ_NOTHING_FOR_EACH_I( \
      WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVALUES_DCLN_ENTRY, \
      ( WG_PP_LCLFUNCTION_SYMBOLTABLE_ISTPL(symbtbl) ) \
      (captured_values_objname) \
      (offset) \
      ( WG_PP_UCAT_ARG2(WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_GETTYPE,suffix) ) \
      ( WG_PP_UCAT_ARG2(WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_OBJ,suffix) ), \
      WG_PP_UCAT_ARG2(WG_PP_LCLFUNCTION_SYMBOLTABLE_GETDCLNS,suffix) (symbtbl) )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVALUES_DCLN_ENTRY( \
  r, istpl_cvobj_offset_gettypemacro_getobjmacro, indx, dcln) \
    WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVALUES_DCLN_ENTRY_IMPL( \
      BOOST_PP_SEQ_ELEM(0, istpl_cvobj_offset_gettypemacro_getobjmacro), \
      BOOST_PP_SEQ_ELEM(1, istpl_cvobj_offset_gettypemacro_getobjmacro), \
      BOOST_PP_SEQ_ELEM(2, istpl_cvobj_offset_gettypemacro_getobjmacro), \
      BOOST_PP_SEQ_ELEM(3, istpl_cvobj_offset_gettypemacro_getobjmacro), \
      BOOST_PP_SEQ_ELEM(4, istpl_cvobj_offset_gettypemacro_getobjmacro), \
      indx, \
      dcln)

#define WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVALUES_DCLN_ENTRY_IMPL( \
  istpl, cvobjname, offset, gettypemacro, getobjmacro, indx, dcln) \
    WG_PP_TRNSLTR_UTILS_ADDTYPENAME(istpl) \
    boost::add_reference \
    < \
      WG_PP_PARSEDTYPE_EXTRACTCPPTYPE( gettypemacro(dcln) ) \
    >::type \
    getobjmacro(dcln) \
      ( cvobjname . BOOST_PP_EXPR_IIF(istpl, template) get<indx + offset>() ) ;

//-------------
//LocalFunction
//-------------

#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_RETURNTYPE_IMPL(symbtbl) \
  BOOST_PP_IIF( \
    WG_PP_LCLFUNCTION_SYMBOLTABLE_EXISTS_RETTYPE(symbtbl), \
    WG_PP_PARSEDTYPE_EXTRACTCPPTYPE( \
      WG_PP_LCLFUNCTION_SYMBOLTABLE_RETTYPE(symbtbl)), \
    void)

// Expands to:
//   Comma seperated add_referenced parameter list of the user specified
//   local function. The add_reference is for efficiency, since the parameter
//   values are being forwarded from another function.
#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TRAILINGPARAMLIST(symbtbl) \
  WG_PP_SEQ_NOTHING_FOR_EACH_I( \
    BOOST_PP_CAT( \
      WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TRAILINGPARAMLIST_ENTRY_, \
      WG_PP_LCLFUNCTION_SYMBOLTABLE_ISTPL(symbtbl) ), \
    ~, \
    WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLNS_PARAMS(symbtbl) )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TRAILINGPARAMLIST_ENTRY_0( \
  r, data, indx, dcln) \
    , WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TRAILINGPARAMLIST_ENTRY_CMN(dcln)

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TRAILINGPARAMLIST_ENTRY_1( \
  r, data, indx, dcln) \
    , typename \
      WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TRAILINGPARAMLIST_ENTRY_CMN(dcln)

#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TRAILINGPARAMLIST_ENTRY_CMN( \
  dcln) \
    boost::add_reference \
    < \
      WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_TYPE_PARAMS(dcln) \
    >::type WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_OBJ_PARAMS(dcln)

//-------------
//GlobalFunctor
//-------------

#define  WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTORTYPE_NAME_IMPL(function_name) \
  WG_PP_LCLFUNCTION_CGUTILS_MAKENAMEUNIQUE( \
    WG_PP_ID_CAT(global_functor_type, function_name))

#define WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTOROBJ_DCLN_IMPL( \
  symbtbl, function_name) \
  WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTORTYPE_NAME(function_name) function_name \
  /* Note: double parenthesis around ctor param to prevent most vexing parse */ \
  /* error. */ \
  (( \
    WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPENAME(function_name) \
    ( \
      WG_PP_SEQ_ENUM( \
        WG_PP_SEQ_JOIN_ARG2( \
          WG_PP_SEQ_REPLACE( \
            WG_PP_SEQ_APPLY_TRANSFORM( \
              WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_OBJ_BOUNDVAR, \
              WG_PP_LCLFUNCTION_SYMBOLTABLE_GETDCLNS_BOUNDVAR(symbtbl) ), \
            WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLNS_THISU_MARKER_BOUNDVAR(symbtbl), \
            this ), \
          WG_PP_SEQ_APPLY_TRANSFORM( \
            WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLN_VALUE_SETVAR, \
            WG_PP_LCLFUNCTION_SYMBOLTABLE_GETDCLNS_SETVAR(symbtbl) ) )) \
    ) \
  )) ;

//------------
//LocalFunctor
//------------

#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTORTYPE_STANDARDTYPENAMES_DCLN_IMPL1( \
  symbtbl, global_functor_type_name) \
    WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTORTYPE_STANDARDTYPENAMES_DCLN_IMPL2( \
      symbtbl, \
      global_functor_type_name, \
      WG_PP_LCLFUNCTION_SYMBOLTABLE_ISTPL(symbtbl) )

#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTORTYPE_STANDARDTYPENAMES_DCLN_IMPL2( \
  symbtbl, global_functor_type_name, istpl) \
    typedef WG_PP_TRNSLTR_UTILS_ADDTYPENAME(istpl) \
      global_functor_type_name::result_type result_type ; \
    BOOST_PP_REPEAT( \
      WG_PP_SEQ_SIZE( \
        WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLNS_PARAMS(symbtbl)), \
      WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTORTYPE_STANDARDTYPENAMES_DCLN_ARGTYPES, \
      WG_PP_TRNSLTR_UTILS_ADDTYPENAME(istpl) global_functor_type_name )

// BOOST_PP_REPEAT functor.
#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTORTYPE_STANDARDTYPENAMES_DCLN_ARGTYPES( \
  z, indx, scope_prefix_tokens) \
    typedef scope_prefix_tokens:: \
      WG_PP_LCLFUNCTION_CGUTILS_FUNCTIONOPERATORUTILS_ARGTYPENAME(indx) \
        WG_PP_LCLFUNCTION_CGUTILS_FUNCTIONOPERATORUTILS_ARGTYPENAME(indx) ;

#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTORTYPE_USERCALLBACKMETHOD_START_IMPL( \
  symbtbl, \
  function_name, \
  global_functor_type_name, \
  captured_values_type_name) \
    static WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_RETURNTYPE(symbtbl) \
      user_callback( \
        global_functor_type_name \
          WG_PP_LCLFUNCTION_CONSTINVARIANCE_KEYWORD_CONST & function_name \
        WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TRAILINGPARAMLIST(symbtbl), \
        captured_values_type_name & capturedvalues) \
    { \
      /* To avoid unused var warnings. */ \
      static_cast<void>( function_name ); \
      \
      WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVALUES_DCLN( \
        symbtbl, capturedvalues) \
      \
      /* User provided definition.*/

#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTORTYPE_USERCALLBACKMETHOD_END_IMPL() \
    }

#endif /* WG_PP_LCLFUNCTION_CODEGENUTILS_HH_ */
