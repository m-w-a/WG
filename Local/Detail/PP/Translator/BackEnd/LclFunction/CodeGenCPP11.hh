#ifndef WG_PP_LCLFUNCTION_CODEGENCPP11_HH_
#define WG_PP_LCLFUNCTION_CODEGENCPP11_HH_

#include <boost/preprocessor.hpp>
#include <boost/mpl/vector.hpp>
#include <WG/Local/Detail/LclFunction/GlobalFunctorTypeCPP11.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/LclFunction/SymbolTable.hh>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/LclFunction/CodeGenUtils.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/ID.hh>

//###########
//Public APIs
//###########

#define WG_PP_LCLFUNCTION_CODEGEN_START(name, symbtbl) \
  WG_PP_LCLFUNCTION_CG_CPP11_START_IMPL(name, symbtbl)

#define WG_PP_LCLFUNCTION_CODEGEN_END() \
  WG_PP_LCLFUNCTION_CG_CPP11_END_IMPL()

//###########
//Impl Macros
//###########

//-----------------
//GlobalFunctorType
//-----------------

#define WG_PP_LCLFUNCTION_CG_CPP11_GLOBALFUNCTORTYPE_DCLN( \
  symbtbl, function_name) \
    typedef WG_PP_LCLFUNCTION_CG_CPP11_GLOBALFUNCTORTYPE_TYPE( \
      symbtbl, function_name) \
        WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTORTYPE_NAME(function_name) ;

#define WG_PP_LCLFUNCTION_CG_CPP11_GLOBALFUNCTORTYPE_TYPE( \
  symbtbl, function_name) \
    ::wg::lclfunction::detail::cpp11::global_functor_type \
    < \
      WG_PP_LCLFUNCTION_CG_CPP11_LOCALFUNCTORTYPE_NAME(function_name), \
      WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_RETURNTYPE(symbtbl) \
      ( \
        WG_PP_SEQ_ENUM(WG_PP_LCLFUNCTION_SYMBOLTABLE_DCLNS_PARAMS(symbtbl)) \
      ), \
      WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPENAME(function_name) \
    >

//----------------
//LocalFunctorType
//----------------

#define WG_PP_LCLFUNCTION_CG_CPP11_LOCALFUNCTORTYPE_NAME(function_name) \
  WG_PP_LCLFUNCTION_CGUTILS_MAKENAMEUNIQUE( \
    WG_PP_ID_CAT(local_functor_type, function_name))

#define WG_PP_LCLFUNCTION_CG_CPP11_LOCALFUNCTORTYPE_START( \
  symbtbl, function_name) \
    struct WG_PP_LCLFUNCTION_CG_CPP11_LOCALFUNCTORTYPE_NAME(function_name) \
      : public WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTORTYPE_NAME(function_name) \
    { \
    public: \
      typedef WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPENAME(function_name) \
        captured_vars_type; \
      typedef WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTORTYPE_NAME(function_name) \
        global_functor_type; \
    private: \
      /* Declared and purposefully not defined. This struct is uninstantiable */ \
      WG_PP_LCLFUNCTION_CG_CPP11_LOCALFUNCTORTYPE_NAME(function_name)(); \
      /* Declared and purposefully not defined. This struct is uninstantiable */ \
      ~WG_PP_LCLFUNCTION_CG_CPP11_LOCALFUNCTORTYPE_NAME(function_name)(); \
      \
    public: \
      WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTORTYPE_NONDEPENDENTDCLNS( \
        symbtbl, global_functor_type) \
      WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTORTYPE_USERCALLBACKMETHOD_START( \
        symbtbl, function_name, global_functor_type, captured_vars_type)

#define WG_PP_LCLFUNCTION_CG_CPP11_LOCALFUNCTORTYPE_END() \
      WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTORTYPE_USERCALLBACKMETHOD_END() \
    };

//-------
//CodeGen
//-------

#define WG_PP_LCLFUNCTION_CG_CPP11_START_IMPL(function_name, symbtbl) \
  WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_DCLN(symbtbl, function_name) \
  \
  WG_PP_LCLFUNCTION_CG_CPP11_START_IMPL2( \
    function_name, \
    WG_PP_LCLFUNCTION_CGUTILS_REMOVEMARKERS( \
      WG_PP_LCLFUNCTION_CGUTILS_REPLACEDEDUCEDTYPES(symbtbl, function_name)) )

#define WG_PP_LCLFUNCTION_CG_CPP11_START_IMPL2(function_name, symbtbl) \
  \
  WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPEDCLN(symbtbl, function_name) \
  \
  struct WG_PP_LCLFUNCTION_CG_CPP11_LOCALFUNCTORTYPE_NAME(function_name) ; \
  WG_PP_LCLFUNCTION_CG_CPP11_GLOBALFUNCTORTYPE_DCLN(symbtbl, function_name) \
  \
  WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTOROBJ_DCLN(symbtbl, function_name) \
  \
  WG_PP_LCLFUNCTION_CG_CPP11_LOCALFUNCTORTYPE_START(symbtbl, function_name)

#define WG_PP_LCLFUNCTION_CG_CPP11_END_IMPL() \
  WG_PP_LCLFUNCTION_CG_CPP11_LOCALFUNCTORTYPE_END()

#endif /* WG_PP_LCLFUNCTION_CODEGENCPP11_HH_ */
