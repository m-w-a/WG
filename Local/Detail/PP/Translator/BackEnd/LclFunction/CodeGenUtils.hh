#ifndef WG_PP_LCLFUNCTION_CODEGENUTILS_HH_
#define WG_PP_LCLFUNCTION_CODEGENUTILS_HH_

#include <boost/preprocessor.hpp>
#include <boost/tuple/tuple.hpp>
#include <WG/Local/DetailPP/Translator/BackEnd/LclFunction/SymbolTable.hh>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/Markers.hh>

//###########
//Public APIs
//###########

#define WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVARSTYPE_DCLN( \
  symbtbl, captured_types_name) \
    WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVARSTYPE_DCLN_IMPL( \
      symbtbl, captured_types_name)

#define WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVARSTYPE_DCLN( \
  symbtbl, captured_vars_typename, captured_vars_objname) \
    WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVARSTYPE_DCLN_IMPL( \
      symbtbl, captured_vars_typename, captured_vars_objname)

#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTIONTYPENAME_DCLN( \
  symbtbl, local_function_type_name) \
    WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTIONTYPENAME_DCLN_IMPL( \
      symbtbl, local_function_type_name)

#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTIONTYPE_PARAMLIST(symbtbl) \
  WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTIONTYPE_PARAMLIST_IMPL(symbtbl)

//###########
//Impl Macros
//###########

//----------------
//CapturedVarsType
//----------------

#define WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVARSTYPE_DCLN_IMPL( \
  symbtbl, captured_types_name) \
    typedef WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDTYPES_TYPE(symbtbl) \
      captured_types_name ;

// Do not implicitly capture variables by reference since each call of a
// local function should get a clean captured-by-value state.
#define WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDTYPES_TYPE(symbtbl) \
  boost::tuple \
  < \
    WG_PP_SEQ_ENUM( \
      WG_PP_SEQ_JOIN_ARG2( \
        WG_PP_LCLFUNCTION_SYMBOLTABLE_TYPESEQ_BOUNDVAR(symbtbl), \
        WG_PP_LCLFUNCTION_SYMBOLTABLE_TYPESEQ_SETVAR(symbtbl) )) \
  >

//------------------------
//UnpackedCapturedVarsDcln
//------------------------

#define WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVARSTYPE_DCLN_IMPL( \
  symbtbl, captured_vars_typename, captured_vars_objname) \
    WG_PP_SEQ_FOR_EACH_I( \
      WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVARSTYPE_DCLN_ENTRY, \
      ( WG_PP_LCLFUNCTION_SYMBOLTABLE_ISTPL(symbtbl) ) \
        (captured_vars_typename)(captured_vars_objname), \
      WG_PP_SEQ_JOIN_ARG2( \
        WG_PP_LCLFUNCTION_SYMBOLTABLE_OBJSEQ_BOUNDVAR(symbtbl), \
        WG_PP_LCLFUNCTION_SYMBOLTABLE_OBJSEQ_SETVAR(symbtbl) ) )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVARSTYPE_DCLN_ENTRY( \
  r, istpl_cvtype_cvobj, indx, varname) \
    WG_PP_TRNSLTR_UTILS_ADDTYPENAME( \
      BOOST_PP_SEQ_ELEM(0, istpl_cvtype_cvobj)) \
    boost::tuples::element \
    <
      indx, \
      BOOST_PP_SEQ_ELEM(1, istpl_cvtype_cvobj) \
    >::type varname( BOOST_PP_SEQ_ELEM(2, istpl_cvtype_cvobj) .get<indx>() )

//---------------------------
//LocalFunctionType Name Dcln
//---------------------------

#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTIONTYPENAME_DCLN_IMPL( \
  symbtbl, local_function_type_name) \
    typedef \
      WG_PP_LCLFUNCTION_SYMBOLTABLE_RETTYPE(symbtbl) \
      ( local_function_type_name ) \
      ( \
        WG_PP_SEQ_ENUM( \
          WG_PP_LCLFUNCTION_SYMBOLTABLE_PARAMS(symtbl)) \
      ) ;

//---------------------------
//LocalFunctionType ParamList
//---------------------------

#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTIONTYPE_PARAMLIST_IMPL(symbtbl) \
  WG_PP_SEQ_ENUM( \
    WG_PP_SEQ_FOR_EACH_I( \
      WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTIONTYPE_PARAMLIST_ENTRY, \
      WG_PP_SEQ_JOIN_ARG2( \
        WG_PP_LCLFUNCTION_SYMBOLTABLE_TYPESEQ_BOUNDVAR(symbtbl), \
        WG_PP_LCLFUNCTION_SYMBOLTABLE_TYPESEQ_SETVAR(symbtbl)), \
      WG_PP_SEQ_JOIN_ARG2( \
        WG_PP_LCLFUNCTION_SYMBOLTABLE_OBJSEQ_BOUNDVAR(symbtbl), \
        WG_PP_LCLFUNCTION_SYMBOLTABLE_OBJSEQ_SETVAR(symbtbl)) ) )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTIONTYPE_PARAMLIST_ENTRY( \
  r, typeseq, indx, varname) \
    ( WG_PP_SEQ_ELEM(indx, typeseq) varname )

#endif /* WG_PP_LCLFUNCTION_CODEGENUTILS_HH_ */
