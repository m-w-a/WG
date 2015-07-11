#ifndef WG_PP_LCLFUNCTION_CODEGENCPP03_HH_
#define WG_PP_LCLFUNCTION_CODEGENCPP03_HH_

#include <boost/preprocessor.hpp>
#include <boost/mpl/vector.hpp>
#include <WG/Local/Detail/PP/Translator/BackEnd/LclFunction/SymbolTable.hh>
#include <WG/Local/Detail/LclFunction/GlobalFunctorTypeCPP03.hh>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/LclFunction/CodeGenUtils.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/ID.hh>

//###########
//Public APIs
//###########

#define WG_PP_LCLFUNCTION_CODEGEN_START(name, symbtbl) \
  WG_PP_LCLFUNCTION_CG_CPP03_START_IMPL(name, symbtbl)

#define WG_PP_LCLFUNCTION_CODEGEN_END() \
  WG_PP_LCLFUNCTION_CG_CPP03_END_IMPL()

//###########
//Impl Macros
//###########

//-----------------
//GlobalFunctorType
//-----------------

#define WG_PP_LCLFUNCTION_CG_CPP03_GLOBALFUNCTORTYPE_DCLN( \
  function_name, symbtbl, global_functor_type_name) \
    typedef WG_PP_LCLFUNCTION_CG_CPP03_GLOBALFUNCTORTYPE_TYPE( \
      function_name, symbtbl, global_functor_type_name) \
        global_functor_type_name ;

#define WG_PP_LCLFUNCTION_CG_CPP03_GLOBALFUNCTORTYPE_TYPE( \
  function_name, symbtbl, global_functor_type_name) \
    ::wg::lclfunction::detail::cpp03::global_functor_type \
    < \
      WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_RETURNTYPE(symbtbl) \
      ( \
        WG_PP_SEQ_ENUM(WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLNS_PARAMS(symbtbl)) \
      ), \
      WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPENAME(function_name) \
    >

//----------------
//LocalFunctorType
//----------------

#define WG_PP_LCLFUNCTION_CG_CPP03_LOCALFUNCTORTYPE_START(symbtbl, function_name) \
  struct local_functor_type \
    : public WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTORTYPE_NAME(function_name) \
  { \
  public: \
    typedef WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTORTYPE_NAME(function_name) \
      global_functor_type; \
    \
    WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTORTYPE_NONDEPENDENTDCLNS( \
      symbtbl, global_functor_type) \
    \
    static void set_caller(global_functor_type & functor) \
    { \
      functor.set_caller(&local_functor_type::user_callback); \
    } \
    \
  private: \
    /* Declared and purposefully not defined. This struct is uninstantiable */ \
    local_functor_type(); \
    /* Declared and purposefully not defined. This struct is uninstantiable */ \
    ~local_functor_type(); \
  private: \
    typedef WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPENAME(function_name) \
      captured_values_type; \
  private: \
    WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTORTYPE_USERCALLBACKMETHOD_START( \
      symbtbl, function_name, global_functor_type, captured_values_type)

#define WG_PP_LCLFUNCTION_CG_CPP03_LOCALFUNCTORTYPE_END() \
    WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTORTYPE_USERCALLBACKMETHOD_END() \
  };

//-------
//CodeGen
//-------

#define WG_PP_LCLFUNCTION_CG_CPP03_SCOPEDFUNCTOROBJ() functor

#define WG_PP_LCLFUNCTION_CG_CPP03_START_IMPL(function_name, symbtbl) \
  WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_DCLN(symbtbl, function_name) \
  \
  WG_PP_LCLFUNCTION_CG_CPP03_START_IMPL2( \
    function_name, \
    WG_PP_LCLFUNCTION_CGUTILS_REMOVEMARKERS( \
      WG_PP_LCLFUNCTION_CGUTILS_REPLACEDEDUCEDTYPES(symbtbl, function_name)) )

#define WG_PP_LCLFUNCTION_CG_CPP03_START_IMPL2(function_name, symbtbl) \
  WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPEDCLN(symbtbl, function_name) \
  \
  WG_PP_LCLFUNCTION_CG_CPP03_GLOBALFUNCTORTYPE_DCLN( \
    function_name, \
    symbtbl, \
    WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTORTYPE_NAME(function_name) ) \
  \
  WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTOROBJ_DCLN(symbtbl, function_name) \
  { \
   /* Don't FORGET the REFERENCE!!!!! */ \
    WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTORTYPE_NAME(function_name) & \
      WG_PP_LCLFUNCTION_CG_CPP03_SCOPEDFUNCTOROBJ() = function_name ; \
    \
    WG_PP_LCLFUNCTION_CG_CPP03_LOCALFUNCTORTYPE_START(symbtbl, function_name)

#define WG_PP_LCLFUNCTION_CG_CPP03_END_IMPL() \
    WG_PP_LCLFUNCTION_CG_CPP03_LOCALFUNCTORTYPE_END() \
    local_functor_type:: \
      set_caller( WG_PP_LCLFUNCTION_CG_CPP03_SCOPEDFUNCTOROBJ() ); \
  } //Block Scope.

#endif /* WG_PP_LCLFUNCTION_CODEGENCPP03_HH_ */
