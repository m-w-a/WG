#ifndef WG_PP_LCLFUNCTION_CODEGENCPP03_HH_
#define WG_PP_LCLFUNCTION_CODEGENCPP03_HH_

#include <boost/preprocessor.hpp>
#include <boost/tuple/tuple.hpp>
#include <WG/Local/DetailPP/Translator/BackEnd/LclFunction/SymbolTable.hh>
#include <WG/Local/Detail/LclFunction/BaseFunctorTypeCPP03.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/ID.hh>
#include <WG/Local/Detail/PP/Translator/Seq.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/LclFunction/CodeGenUtils.hh>

//###########
//Public APIs
//###########

#define WG_PP_LCLFUNCTION_CODEGEN_START(name, symbtbl) \
  WG_PP_LCLFUNCTION_CODEGEN_START_IMPL(name, symbtbl)

#define WG_PP_LCLFUNCTION_CODEGEN_END(name, symbtbl) \
  WG_PP_LCLFUNCTION_CODEGEN_END_IMPL(name, symbtbl)

//###########
//Impl Macros
//###########

//-----
//Utils
//-----

#define WG_PP_LCLFUNCTION_CG_GLOBALID() WG_PP_ID_MAKE_GLOBAL(lclfunction)

#define WG_PP_LCLFUNCTION_CG_FORMATNAME(name) \
  WG_PP_ID_CAT( \
    WG_PP_ID_CAT(WG_PP_LCLFUNCTION_CG_GLOBALID(), name), \
    __LINE__)

#define WG_PP_LCLFUNCTION_CG_CAPTUREDVARTYPES_NAME() \
  WG_PP_LCLFUNCTION_CG_FORMATNAME(capturedtypes)

#define WG_PP_LCLFUNCTION_CG_LOCALFUNCTIONTYPE_NAME() \
  WG_PP_LCLFUNCTION_CG_FORMATNAME(local_function_type)

#define WG_PP_LCLFUNCTION_CG_BASEFUNCTORTYPE_NAME() \
  WG_PP_LCLFUNCTION_CG_FORMATNAME(base_functor_type)

//---------------
//BaseFunctorType
//---------------

#define WG_PP_LCLFUNCTION_CG_BASEFUNCTORTYPE_DCLN( \
  symbtbl, base_functor_type_name) \
    typedef WG_PP_LCLFUNCTION_CG_BASEFUNCTORTYPE_TYPE( \
      symbtbl, base_functor_type_name) \
        base_functor_type_name ;

#define WG_PP_LCLFUNCTION_CG_BASEFUNCTORTYPE_TYPE( \
  symbtbl, base_functor_type_name) \
    wg::lclfunction::detail::base_functor_type \
    < \
      WG_PP_LCLFUNCTION_CG_LOCALFUNCTIONTYPE_NAME(), \
      WG_PP_LCLFUNCTION_CG_CAPTUREDVARTYPES_NAME() \
    >

//----------------
//LocalFunctionObj
//----------------

#define WG_PP_LCLFUNCTION_CG_LOCALFUNCTIONOBJ_DCLN(symbtbl, objname) \
  WG_PP_LCLFUNCTION_CG_BASEFUNCTORTYPE_NAME() function_name \
  /* Note: double parenthesis around ctor param to prevent most vexing parse */ \
  /* error. */ \
  (( \
    WG_PP_LCLFUNCTION_CG_CAPTUREDVARTYPES_NAME() \
    ( \
      WG_PP_SEQ_ENUM( \
        WG_PP_SEQ_JOIN_ARG2( \
          WG_PP_SEQ_REPLACE( \
            WG_PP_LCLFUNCTION_SYMBOLTABLE_OBJSEQ_BOUNDVAR(symbtbl), \
            WG_PP_LCLFUNCTION_SYMBOLTABLE_OBJSEQ_THISU_MARKER_BOUNDVAR(symbtbl), \
            this ), \
          WG_PP_LCLFUNCTION_SYMBOLTABLE_OBJSEQ_SETVAR(symbtbl) )) \
    ) \
  )) ;

//----------------
//LocalFunctorType
//----------------

#define WG_PP_LCLFUNCTION_CG_LOCALFUNCTORTYPE_START(symbtbl, function_name) \
  struct local_functor_type \
  { \
    typedef WG_PP_LCLFUNCTION_CG_CAPTUREDVARTYPES_NAME() captured_vars_type; \
    typedef WG_PP_LCLFUNCTION_CG_BASEFUNCTORTYPE_NAME() base_functor_type; \
    \
    void set_caller(base_functor_type & functor) \
    { \
      functor.set_caller(&local_functor_type::user_callback); \
    } \
    \
  private: \
    /* This functions prototype should match */ \
    /* base_functor_type::callback_type. */ \
    static WG_PP_LCLFUNCTION_SYMBOLTABLE_RETTYPE(symbtbl) user_callback( \
      base_functor_type const & function_name, \
      WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTIONTYPE_PARAMLIST(symbtbl), \
      captured_vars_type const & capturedvars) \
    { \
      /* To avoid unused var warnings. */ \
      (void)( function_name ); \
      \
      WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVARSTYPE_DCLN( \
        symbtbl, captured_vars_type, capturedvars) \
      \
      /* User provided definition.*/

#define WG_PP_LCLFUNCTION_CG_LOCALFUNCTORTYPE_END() \
    } /* user_callback */ \
  };

//-------
//CodeGen
//-------

#define WG_PP_LCLFUNCTION_CG_SCOPEDFUNCTOROBJ() functor

#define WG_PP_LCLFUNCTION_CODEGEN_START_IMPL(function_name, symbtbl) \
  WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVARSTYPE_DCLN( \
    symbtbl, \
    WG_PP_LCLFUNCTION_CG_CAPTUREDVARTYPES_NAME() ) \
  \
  WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTIONTYPENAME_DCLN( \
    symbtbl, \
    WG_PP_LCLFUNCTION_CG_LOCALFUNCTIONTYPE_NAME() ) \
  \
  WG_PP_LCLFUNCTION_CG_BASEFUNCTORTYPE_DCLN( \
    symbtbl, \
    WG_PP_LCLFUNCTION_CG_BASEFUNCTORTYPE_NAME() ) \
  \
  WG_PP_LCLFUNCTION_CG_LOCALFUNCTIONOBJ_DCLN(symbtbl, function_name) \
  { \
   /* Don't FORGET the REFERENCE!!!!! */ \
    WG_PP_LCLFUNCTION_CG_BASEFUNCTORTYPE_NAME() & \
      WG_PP_LCLFUNCTION_CG_SCOPEDFUNCTOROBJ() = function_name ; \
    \
    WG_PP_LCLFUNCTION_CG_LOCALFUNCTORTYPE_START(symbtbl, function_name)

#define WG_PP_LCLFUNCTION_CODEGEN_END_IMPL(name, symbtbl) \
    WG_PP_LCLFUNCTION_CG_LOCALFUNCTORTYPE_END() \
    local_functor_type local_functor_obj; \
    local_functor_obj.set_caller( WG_PP_LCLFUNCTION_CG_SCOPEDFUNCTOROBJ() ); \
  }

#endif /* WG_PP_LCLFUNCTION_CODEGENCPP03_HH_ */
