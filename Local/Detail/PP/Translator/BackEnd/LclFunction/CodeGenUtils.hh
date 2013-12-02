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

#define WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_DCLN(symbtbl) \
  WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_DCLN_IMPL(symbtbl)

// For specs:
//   see WG_PP_STUTIL_USETYPEALIASER(...)
#define WG_PP_LCLFUNCTION_USETYPEALIASER(symbtbl) \
  WG_PP_LCLFUNCTION_CGUITILS_USETYPEALIASER_IMPL(symbtbl)

//--------------
//CapturedValues
//--------------

#define WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPENAME() \
  WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPENAME_IMPL()

#define WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPEDCLN(symbtbl) \
  WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPEDCLN_IMPL(symbtbl)

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
#define WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTORTYPE_NAME() \
  WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTORTYPE_NAME_IMPL()

#define WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTOROBJ_DCLN(symbtbl, objname) \
  WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTOROBJ_DCLN_IMPL(symbtbl, objname)

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
//   BOOST_PP_NIL_ | {non-local-type}+
//
// symbtbl_type_seq:
//   { ( non-local-type ) }+
#define WG_PP_LCLFUNCTION_CGUTILS_TYPESEQ_TO_CAPTUREDTYPESEQ( \
  istpl, symbtbl_type_seq) \
    WG_PP_SEQ_FOR_EACH( \
      WG_PP_LCLFUNCTION_CGUTILS_TYPESEQ_TO_CAPTUREDTYPESEQ_TRANSFORM, \
      istpl, \
      symbtbl_type_seq)

// WG_PP_SEQ_FOR_EACH functor.
#define WG_PP_LCLFUNCTION_CGUTILS_TYPESEQ_TO_CAPTUREDTYPESEQ_TRANSFORM( \
  r, istpl, elem) \
    ( \
      WG_PP_TRNSLTR_UTILS_ADDTYPENAME(istpl) \
      wg::local::detail::bind_traits \
      < \
        WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(elem) \
      >::binder_type \
    )

//------------
//TypesAliaser
//------------

// Expands to:
//   Line specific id.
#define WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_NAME() \
  WG_PP_LCLFUNCTION_CGUTILS_MAKENAMEUNIQUE(captured_types_aliaser)

#define WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_SPECSEQ() \
  ( (BOUNDVAR)(varbind) )( (SETVAR)(varset) )

#define WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_DCLN_IMPL(symbtbl) \
  WG_PP_TYPEALIASER_DCLN( \
    WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_NAME(), \
    IMPLICITTYPES, \
    symbtbl, \
    WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_SPECSEQ() )

#define WG_PP_LCLFUNCTION_CGUITILS_USETYPEALIASER_IMPL(symbtbl) \
  WG_PP_STUTIL_USETYPEALIASER( \
    symbtbl, \
    WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_NAME(), \
    IMPLICITTYPES, \
    WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_SPECSEQ() )

//--------------
//CapturedValues
//--------------

#define WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPENAME_IMPL() \
  WG_PP_LCLFUNCTION_CGUTILS_MAKENAMEUNIQUE(captured_values_type)

#define WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPEDCLN_IMPL(symbtbl) \
    typedef WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPE(symbtbl) \
      WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPENAME() ;

#define WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPE(symbtbl) \
  boost::tuple \
  < \
    WG_PP_SEQ_ENUM( \
      WG_PP_SEQ_JOIN_ARG2( \
        WG_PP_LCLFUNCTION_CGUTILS_TYPESEQ_TO_CAPTUREDTYPESEQ( \
          WG_PP_LCLFUNCTION_SYMBOLTABLE_ISTPL(symbtbl), \
          WG_PP_LCLFUNCTION_SYMBOLTABLE_TYPESEQ_BOUNDVAR(symbtbl)), \
        WG_PP_LCLFUNCTION_CGUTILS_TYPESEQ_TO_CAPTUREDTYPESEQ( \
          WG_PP_LCLFUNCTION_SYMBOLTABLE_ISTPL(symbtbl), \
          WG_PP_LCLFUNCTION_SYMBOLTABLE_TYPESEQ_SETVAR(symbtbl)) )) \
  >

#define WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVALUES_DCLN( \
  symbtbl, captured_values_typename, captured_values_objname) \
    WG_PP_SEQ_NOTHING_FOR_EACH_I( \
      WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVALUES_DCLN_ENTRY, \
      ( WG_PP_LCLFUNCTION_SYMBOLTABLE_ISTPL(symbtbl) ) \
      ( captured_values_objname ) \
      ( WG_PP_SEQ_JOIN_ARG2( \
          WG_PP_LCLFUNCTION_SYMBOLTABLE_TYPESEQ_BOUNDVAR(symbtbl), \
          WG_PP_LCLFUNCTION_SYMBOLTABLE_TYPESEQ_SETVAR(symbtbl) ) ) , \
      WG_PP_SEQ_JOIN_ARG2( \
        WG_PP_LCLFUNCTION_SYMBOLTABLE_OBJSEQ_BOUNDVAR(symbtbl), \
        WG_PP_LCLFUNCTION_SYMBOLTABLE_OBJSEQ_SETVAR(symbtbl) ) )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVALUES_DCLN_ENTRY( \
  r, istpl_cvobj_vartypeseq, indx, varname) \
    WG_PP_TRNSLTR_UTILS_ADDTYPENAME( \
      BOOST_PP_SEQ_ELEM(0, istpl_cvobj_vartypeseq)) \
    boost::add_reference \
    < \
      WG_PP_PARSEDTYPE_EXTRACTCPPTYPE( \
        BOOST_PP_SEQ_ELEM(indx, BOOST_PP_SEQ_ELEM(2, istpl_cvobj_vartypeseq)) ) \
    >::type \
    varname \
      ( \
        WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVALUES_TUPLEELEMENTACCESS( \
          BOOST_PP_SEQ_ELEM(0, istpl_cvobj_vartypeseq), \
          BOOST_PP_SEQ_ELEM(1, istpl_cvobj_vartypeseq), \
          indx) \
      ) ;

#define WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVALUES_TUPLEELEMENTACCESS( \
  istpl, cvobj, indx) \
    cvobj . BOOST_PP_EXPR_IIF(istpl, template) get<indx>()


//-------------
//LocalFunction
//-------------

#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_RETURNTYPE_IMPL(symbtbl) \
  BOOST_PP_IIF( \
    WG_PP_LCLFUNCTION_SYMBOLTABLE_EXISTS_RETTYPE(symbtbl), \
    WG_PP_LCLFUNCTION_SYMBOLTABLE_RETTYPE(symbtbl), \
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
    WG_PP_LCLFUNCTION_SYMBOLTABLE_TYPESEQ_PARAMS(symbtbl), \
    WG_PP_LCLFUNCTION_SYMBOLTABLE_OBJSEQ_PARAMS(symbtbl) )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TRAILINGPARAMLIST_ENTRY_0( \
  r, typeseq, indx, varname) \
    , WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TRAILINGPARAMLIST_ENTRY_CMN( \
        typeseq, indx, varname)

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TRAILINGPARAMLIST_ENTRY_1( \
  r, typeseq, indx, varname) \
    , typename \
      WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TRAILINGPARAMLIST_ENTRY_CMN( \
        typeseq, indx, varname)

#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TRAILINGPARAMLIST_ENTRY_CMN( \
  typeseq, indx, varname) \
    boost::add_reference< WG_PP_SEQ_ELEM(indx, typeseq) >::type varname

//-------------
//GlobalFunctor
//-------------

#define  WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTORTYPE_NAME_IMPL() \
  WG_PP_LCLFUNCTION_CGUTILS_MAKENAMEUNIQUE(global_functor_type)

#define WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTOROBJ_DCLN_IMPL(symbtbl, objname) \
  WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTORTYPE_NAME() objname \
  /* Note: double parenthesis around ctor param to prevent most vexing parse */ \
  /* error. */ \
  (( \
    WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPENAME() \
    ( \
      WG_PP_SEQ_ENUM( \
        WG_PP_SEQ_JOIN_ARG2( \
          WG_PP_SEQ_REPLACE( \
            WG_PP_LCLFUNCTION_SYMBOLTABLE_OBJSEQ_BOUNDVAR(symbtbl), \
            WG_PP_LCLFUNCTION_SYMBOLTABLE_OBJSEQ_THISU_MARKER_BOUNDVAR(symbtbl), \
            this ), \
          WG_PP_LCLFUNCTION_SYMBOLTABLE_VALUESEQ_SETVAR(symbtbl) )) \
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
        WG_PP_LCLFUNCTION_SYMBOLTABLE_TYPESEQ_PARAMS(symbtbl)), \
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
        symbtbl, captured_values_type_name, capturedvalues) \
      \
      /* User provided definition.*/

#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTORTYPE_USERCALLBACKMETHOD_END_IMPL() \
    }

#endif /* WG_PP_LCLFUNCTION_CODEGENUTILS_HH_ */
