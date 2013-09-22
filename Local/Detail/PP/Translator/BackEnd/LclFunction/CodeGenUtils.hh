#ifndef WG_PP_LCLFUNCTION_CODEGENUTILS_HH_
#define WG_PP_LCLFUNCTION_CODEGENUTILS_HH_

#include <boost/preprocessor.hpp>
#include <boost/tuple/tuple.hpp>
#include <WG/Local/Detail/PP/Translator/BackEnd/ID.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/LclFunction/SymbolTable.hh>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/Markers.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/TypeAliaser.hh>

//###########
//Public APIs
//###########

// Expands to:
//   Line specific id.
#define WG_PP_LCLFUNCTION_CGUTILS_BASEFUNCTORTYPE_NAME() \
  WG_PP_LCLFUNCTION_CGUTILS_BASEFUNCTORTYPE_NAME_IMPL()

//------------
//TypesAliaser
//------------

// Expands to:
//   Line specific id.
#define WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_NAME() \
  WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_NAME_IMPL()

#define WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_DCLN(symbtbl) \
    WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_DCLN_IMPL(symbtbl)

// For specs:
//   see WG_PP_STUTIL_USETYPEALIASER(...)
#define WG_PP_LCLFUNCTION_USETYPEALIASER(symbtbl) \
  WG_PP_LCLFUNCTION_USETYPEALIASER_IMPL(symbtbl)

//--------------
//CapturedValues
//--------------

#define WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPENAME() \
  WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPENAME_IMPL()

#define WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPEDCLN(symbtbl) \
    WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPEDCLN_IMPL(symbtbl)

#define WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVALUES_DCLN( \
  symbtbl, captured_values_typename, captured_values_objname) \
    WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVALUES_DCLN_IMPL( \
      symbtbl, captured_values_typename, captured_values_objname)

//-------------
//LocalFunction
//-------------

// Expands to:
//   Line specific id.
#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TYPENAME() \
  WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TYPENAME_IMPL()

// Expands to:
//   The typedefed alias of the user specified local function with name:
//   WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TYPENAME().
#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TYPEDCLN( \
  symbtbl, local_function_type_name) \
    WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TYPEDCLN_IMPL( \
      symbtbl, local_function_type_name)

#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_RETURNTYPE(symbtbl) \
  WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_RETURNTYPE_IMPL(symbtbl)

// Expands to:
//   Comma seperated parameter list of the user specified local function.
#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TRAILINGPARAMLIST(symbtbl) \
  WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TRAILINGPARAMLIST_IMPL(symbtbl)

//###########
//Impl Macros
//###########

//-----
//Utils
//-----

#define WG_PP_LCLFUNCTION_CGUTILS_GLOBALID() WG_PP_ID_MAKE_GLOBAL(lclfunction)

#define WG_PP_LCLFUNCTION_CGUTILS_FORMATNAME(name) \
  WG_PP_ID_CAT( \
    WG_PP_ID_CAT(WG_PP_LCLFUNCTION_CGUTILS_GLOBALID(), name), \
    __LINE__)

#define  WG_PP_LCLFUNCTION_CGUTILS_BASEFUNCTORTYPE_NAME_IMPL() \
  WG_PP_LCLFUNCTION_CGUTILS_FORMATNAME(base_functor_type)

//------------
//TypesAliaser
//------------

#define WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_NAME_IMPL() \
  WG_PP_LCLFUNCTION_CGUTILS_FORMATNAME(captured_types_aliaser)

#define WG_PP_LCLFUNCTION_CG_TYPEALIASER_SPECSEQ() \
  ( (BOUNDVAR)(varbind) )( (SETVAR)(varset) )

#define WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_DCLN_IMPL(symbtbl) \
  WG_PP_TYPEALIASER_DCLN( \
    WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_NAME(), \
    ALLTYPES, \
    symbtbl, \
    WG_PP_LCLFUNCTION_CG_TYPEALIASER_SPECSEQ() )

#define WG_PP_LCLFUNCTION_USETYPEALIASER_IMPL(symbtbl) \
  WG_PP_STUTIL_USETYPEALIASER( \
    symbtbl, \
    WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_NAME(), \
    ALLTYPES, \
    WG_PP_LCLFUNCTION_CG_TYPEALIASER_SPECSEQ() )

//--------------
//CapturedValues
//--------------

#define WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPENAME_IMPL() \
  WG_PP_LCLFUNCTION_CGUTILS_FORMATNAME(captured_values_type)

#define WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPEDCLN_IMPL(symbtbl) \
    typedef WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPE(symbtbl) \
      WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPENAME() ;

// Do not implicitly capture variables by reference since each call of a
// local function should get a clean captured-by-value state.
#define WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPE(symbtbl) \
  boost::tuple \
  < \
    WG_PP_SEQ_ENUM( \
      WG_PP_SEQ_JOIN_ARG2( \
        WG_PP_LCLFUNCTION_SYMBOLTABLE_TYPESEQ_BOUNDVAR(symbtbl), \
        WG_PP_LCLFUNCTION_SYMBOLTABLE_TYPESEQ_SETVAR(symbtbl) )) \
  >

#define WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVALUES_DCLN_IMPL( \
  symbtbl, captured_values_typename, captured_values_objname) \
    WG_PP_SEQ_NOTHING_FOR_EACH_I( \
      WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVALUES_DCLN_ENTRY, \
      ( WG_PP_LCLFUNCTION_SYMBOLTABLE_ISTPL(symbtbl) ) \
        (captured_values_typename)(captured_values_objname), \
      WG_PP_SEQ_JOIN_ARG2( \
        WG_PP_LCLFUNCTION_SYMBOLTABLE_OBJSEQ_BOUNDVAR(symbtbl), \
        WG_PP_LCLFUNCTION_SYMBOLTABLE_OBJSEQ_SETVAR(symbtbl) ) )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVALUES_DCLN_ENTRY( \
  r, istpl_cvtype_cvobj, indx, varname) \
    WG_PP_TRNSLTR_UTILS_ADDTYPENAME( \
      BOOST_PP_SEQ_ELEM(0, istpl_cvtype_cvobj)) \
    boost::tuples::element \
    < \
      indx, \
      BOOST_PP_SEQ_ELEM(1, istpl_cvtype_cvobj) \
    >::type varname( BOOST_PP_SEQ_ELEM(2, istpl_cvtype_cvobj) .get<indx>() )

//-------------
//LocalFunction
//-------------

#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TYPENAME_IMPL() \
  WG_PP_LCLFUNCTION_CGUTILS_FORMATNAME(local_function_type)

#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_RETURNTYPE_IMPL(symbtbl) \
  BOOST_PP_IIF( \
    WG_PP_LCLFUNCTION_SYMBOLTABLE_EXISTS_RETTYPE(symbtbl), \
    WG_PP_LCLFUNCTION_SYMBOLTABLE_RETTYPE(symbtbl), \
    void)

#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TYPEDCLN_IMPL( \
  symbtbl, local_function_type_name) \
    typedef \
      WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_RETURNTYPE(symbtbl) \
      ( local_function_type_name ) \
      ( \
          WG_PP_LCLFUNCTION_SYMBOLTABLE_PARAMSLIST(symbtbl) \
      ) ;

#define WG_PP_LCLFUNCTION_SYMBOLTABLE_PARAMSLIST(symbtbl) \
  WG_PP_SEQ_ENUM( \
    WG_PP_SEQ_FOR_EACH_I( \
      WG_PP_LCLFUNCTION_SYMBOLTABLE_PARAMSLIST_ENTRY, \
      WG_PP_LCLFUNCTION_SYMBOLTABLE_TYPESEQ_PARAMS(symbtbl), \
      WG_PP_LCLFUNCTION_SYMBOLTABLE_OBJSEQ_PARAMS(symbtbl)) )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_LCLFUNCTION_SYMBOLTABLE_PARAMSLIST_ENTRY( \
  r, typeseq, indx, varname) \
    ( \
      WG_PP_SEQ_ELEM(indx, typeseq) varname \
    )

#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TRAILINGPARAMLIST_IMPL(symbtbl) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TRAILINGPARAMLIST_ENTRY, \
    WG_PP_LCLFUNCTION_SYMBOLTABLE_TYPESEQ_PARAMS(symbtbl), \
    WG_PP_LCLFUNCTION_SYMBOLTABLE_OBJSEQ_PARAMS(symbtbl) )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TRAILINGPARAMLIST_ENTRY( \
  r, typeseq, indx, varname) \
    , WG_PP_SEQ_ELEM(indx, typeseq) varname

#endif /* WG_PP_LCLFUNCTION_CODEGENUTILS_HH_ */
