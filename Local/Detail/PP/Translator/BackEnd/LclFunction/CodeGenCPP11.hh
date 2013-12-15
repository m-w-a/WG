#ifndef WG_PP_LCLFUNCTION_CODEGENCPP11_HH_
#define WG_PP_LCLFUNCTION_CODEGENCPP11_HH_

#include <boost/preprocessor.hpp>
#include <boost/mpl/vector.hpp>
#include <WG/Local/Detail/PP/Translator/BackEnd/LclFunction/SymbolTable.hh>
#include <WG/Local/Detail/LclFunction/GlobalFunctorTypeCPP11.hh>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/LclFunction/CodeGenUtils.hh>

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
  symbtbl, global_functor_type_name, local_functor_type_name) \
  typedef WG_PP_LCLFUNCTION_CG_CPP11_GLOBALFUNCTORTYPE_TYPE( \
    symbtbl, local_functor_type_name) \
      global_functor_type_name ;

#define WG_PP_LCLFUNCTION_CG_CPP11_GLOBALFUNCTORTYPE_TYPE( \
  symbtbl, local_functor_type_name) \
    wg::lclfunction::detail::cpp11::global_functor_type \
    < \
      local_functor_type_name, \
      WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTION_RETURNTYPE(symbtbl), \
      boost::mpl::vector \
      < \
        WG_PP_SEQ_ENUM( WG_PP_LCLFUNCTION_SYMBOLTABLE_TYPESEQ_PARAMS(symbtbl) ) \
      >, \
      WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPENAME() \
    >

//----------------
//LocalFunctorType
//----------------

#define WG_PP_LCLFUNCTION_CG_CPP11_LOCALFUNCTORTYPE_NAME() \
  WG_PP_LCLFUNCTION_CGUTILS_MAKENAMEUNIQUE(local_functor_type)

#define WG_PP_LCLFUNCTION_CG_CPP11_LOCALFUNCTORTYPE_START( \
  symbtbl, function_name) \
    struct WG_PP_LCLFUNCTION_CG_CPP11_LOCALFUNCTORTYPE_NAME() \
    { \
      typedef WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPENAME() \
        captured_vars_type; \
      typedef WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTORTYPE_NAME() \
        global_functor_type; \
      \
      WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTORTYPE_STANDARDTYPENAMES_DCLN( \
        symbtbl, global_functor_type) \
      \
      WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTORTYPE_USERCALLBACKMETHOD_START( \
        symbtbl, function_name, global_functor_type, captured_vars_type)

#define WG_PP_LCLFUNCTION_CG_CPP11_LOCALFUNCTORTYPE_END() \
      WG_PP_LCLFUNCTION_CGUTILS_LOCALFUNCTORTYPE_USERCALLBACKMETHOD_END() \
    };

//-------
//CodeGen
//-------

#define WG_PP_LCLFUNCTION_CG_CPP11_START_IMPL(function_name, symbtbl) \
  WG_PP_LCLFUNCTION_CGUTILS_TYPEALIASER_DCLN(symbtbl) \
  \
  WG_PP_LCLFUNCTION_CG_CPP11_START_IMPL2( \
    function_name, \
    WG_PP_LCLFUNCTION_CGUTILS_USETYPEALIASER(symbtbl) )

#define WG_PP_LCLFUNCTION_CG_CPP11_START_IMPL2(function_name, symbtbl) \
  \
  WG_PP_LCLFUNCTION_CGUTILS_CAPTUREDVALUES_TYPEDCLN(symbtbl) \
  \
  struct WG_PP_LCLFUNCTION_CG_CPP11_LOCALFUNCTORTYPE_NAME() ; \
  WG_PP_LCLFUNCTION_CG_CPP11_GLOBALFUNCTORTYPE_DCLN( \
    symbtbl, \
    WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTORTYPE_NAME(), \
    WG_PP_LCLFUNCTION_CG_CPP11_LOCALFUNCTORTYPE_NAME()) \
  \
  WG_PP_LCLFUNCTION_CGUTILS_GLOBALFUNCTOROBJ_DCLN(symbtbl, function_name) \
  \
  WG_PP_LCLFUNCTION_CG_CPP11_LOCALFUNCTORTYPE_START(symbtbl, function_name)

#define WG_PP_LCLFUNCTION_CG_CPP11_END_IMPL() \
  WG_PP_LCLFUNCTION_CG_CPP11_LOCALFUNCTORTYPE_END()

#endif /* WG_PP_LCLFUNCTION_CODEGENCPP11_HH_ */
