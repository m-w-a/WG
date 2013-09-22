#ifndef WG_PP_LCLFUNCTION_CODEGENCPP03_HH_
#define WG_PP_LCLFUNCTION_CODEGENCPP03_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/Translator/BackEnd/LclFunction/SymbolTable.hh>
#include <WG/Local/Detail/LclFunction/BaseFunctorTypeCPP03.hh>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/LclFunction/CodeGenUtils.hh>

//###########
//Public APIs
//###########

#define WG_PP_LCLFUNCTION_CODEGEN_START(name, symbtbl) \
  WG_PP_LCLFUNCTION_CODEGEN_START_IMPL(name, symbtbl)

#define WG_PP_LCLFUNCTION_CODEGEN_END() \
  WG_PP_LCLFUNCTION_CODEGEN_END_IMPL()

//###########
//Impl Macros
//###########

//---------------
//BaseFunctorType
//---------------

#define WG_PP_LCLFUNCTION_CG_BASEFUNCTORTYPE_DCLN( \
  symbtbl, global_functor_type_name) \
    typedef WG_PP_LCLFUNCTION_CG_BASEFUNCTORTYPE_TYPE( \
      symbtbl, global_functor_type_name) \
        global_functor_type_name ;

#define WG_PP_LCLFUNCTION_CG_BASEFUNCTORTYPE_TYPE( \
  symbtbl, global_functor_type_name) \
    wg::lclfunction::detail::global_functor_type \
    < \
      WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TYPENAME(), \
      WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPENAME() \
    >

//----------------
//LocalFunctionObj
//----------------

#define WG_PP_LCLFUNCTION_CG_LOCALFUNCTIONOBJ_DCLN(symbtbl, objname) \
  WG_PP_LCLFUNCTION_CGUTILS_BASEFUNCTORTYPE_NAME() objname \
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
          WG_PP_LCLFUNCTION_SYMBOLTABLE_OBJSEQ_SETVAR(symbtbl) )) \
    ) \
  )) ;

//----------------
//LocalFunctorType
//----------------

#define WG_PP_LCLFUNCTION_CG_LOCALFUNCTORTYPE_START(symbtbl, function_name) \
  struct local_functor_type \
  { \
    typedef WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPENAME() captured_values_type; \
    typedef WG_PP_LCLFUNCTION_CGUTILS_BASEFUNCTORTYPE_NAME() global_functor_type; \
    \
    void set_caller(global_functor_type & functor) \
    { \
      functor.set_caller(&local_functor_type::user_callback); \
    } \
    \
  private: \
    /* This functions prototype should match */ \
    /* global_functor_type::callback_type. */ \
    static WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_RETURNTYPE(symbtbl) \
      user_callback( \
        global_functor_type const & function_name \
        WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TRAILINGPARAMLIST(symbtbl), \
        captured_values_type const & capturedvalues) \
    { \
      /* To avoid unused var warnings. */ \
      static_cast<void>( function_name ); \
      \
      WG_PP_LCLFUNCTION_CGUTILS_UNPACKEDCAPTUREDVALUES_DCLN( \
        symbtbl, captured_values_type, capturedvalues) \
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
  WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_DCLN(symbtbl) \
  \
  WG_PP_LCLFUNCTION_CODEGEN_START_IMPL2( \
    function_name, \
    WG_PP_LCLFUNCTION_USETYPEALIASER(symbtbl) )

#define WG_PP_LCLFUNCTION_CODEGEN_START_IMPL2(function_name, symbtbl) \
  WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPEDCLN(symbtbl) \
  \
  WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TYPEDCLN( \
    symbtbl, \
    WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_TYPENAME() ) \
  \
  WG_PP_LCLFUNCTION_CG_BASEFUNCTORTYPE_DCLN( \
    symbtbl, \
    WG_PP_LCLFUNCTION_CGUTILS_BASEFUNCTORTYPE_NAME() ) \
  \
  WG_PP_LCLFUNCTION_CG_LOCALFUNCTIONOBJ_DCLN(symbtbl, function_name) \
  { \
   /* Don't FORGET the REFERENCE!!!!! */ \
    WG_PP_LCLFUNCTION_CGUTILS_BASEFUNCTORTYPE_NAME() & \
      WG_PP_LCLFUNCTION_CG_SCOPEDFUNCTOROBJ() = function_name ; \
    \
    WG_PP_LCLFUNCTION_CG_LOCALFUNCTORTYPE_START(symbtbl, function_name)

#define WG_PP_LCLFUNCTION_CODEGEN_END_IMPL() \
    WG_PP_LCLFUNCTION_CG_LOCALFUNCTORTYPE_END() \
    local_functor_type local_functor_obj; \
    local_functor_obj.set_caller( WG_PP_LCLFUNCTION_CG_SCOPEDFUNCTOROBJ() ); \
  } //Block Scope.

#endif /* WG_PP_LCLFUNCTION_CODEGENCPP03_HH_ */
