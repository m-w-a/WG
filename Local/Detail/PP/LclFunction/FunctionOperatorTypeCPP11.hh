#ifndef WG_PP_LOCAL_DETAIL_LCLFUNCTION_FUNCTIONOPERATORTYPECPP11_HH_
#define WG_PP_LOCAL_DETAIL_LCLFUNCTION_FUNCTIONOPERATORTYPECPP11_HH_

#include <boost/preprocessor.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <WG/Local/Detail/LclFunction/GlobalFunctorBaseType.hh>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/LclFunction/FunctionOperatorUtils.hh>
#include <WG/Local/Detail/PP/LclFunction/ConstInvariance.hh>

//###########
//Public APIs
//###########

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_NAME() \
  WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_NAME_IMPL()

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_DCLNS() \
  WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_DCLNS_IMPL()

//###########
//Impl Macros
//###########

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_OPERATOR_ARGROOTNAME() arg

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_NAME_IMPL() \
  function_operator_type

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_DCLNS_IMPL() \
  /* Instantiation of this class will always fail because the local function */ \
  /* arity exceeds WG_PP_LCLFUNCTION_CONFIG_PARAMS_MAX_ARITY. */ \
  /* This is accomplished by making the destructor private. */ \
  /* Note: this class purposefully does not derive from global_functor_base_type */ \
  /*   since this is an invalid class. This fact is used to unit test that */ \
  /*   WG_PP_LCLFUNCTION_CONFIG_PARAMS_MAX_ARITY actually works. */ \
  template \
  < \
    typename Derived, \
    typename LclFunctionType, \
    typename LocalFunctorType, \
    int Arity = ::boost::function_types::function_arity<LclFunctionType>::value \
  > \
  class WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_NAME() \
  { \
  public: \
    typedef LclFunctionType function_type; \
    enum { arity = Arity }; \
    typedef \
      typename ::boost::function_types::result_type<function_type>::type \
         result_type; \
  protected: \
    typedef \
      ::boost::function_types::parameter_types<function_type> \
         parameter_types; \
  private: \
    /* Declared and purposefully not defined. */ \
    ~WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_NAME()(); \
  }; \
  \
  /* Begin partial specializations. */ \
  BOOST_PP_REPEAT( \
    BOOST_PP_INC(WG_PP_LCLFUNCTION_CONFIG_PARAMS_MAX_ARITY), \
    WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_DCLNS_ENTRY, \
    ~)

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_DCLNS_ENTRY( \
  z, argcount, data) \
  WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_CLASS(argcount)

//--------------------
//Operator Param List.
//--------------------

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_OPERATOR_PARAMLIST( \
  argcount) \
    BOOST_PP_ENUM( \
      argcount, \
      WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_OPERATOR_PARAMLIST_ENTRY, \
      ~)

// BOOST_PP_ENUM functor.
#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_OPERATOR_PARAMLIST_ENTRY( \
  z, indx, data) \
    WG_PP_LCLFUNCTION_CGUTILS_FUNCTIONOPERATORUTILS_ARGTYPENAME(indx) \
    BOOST_PP_CAT( \
      WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_OPERATOR_ARGROOTNAME(), indx)

//--------------
//Operator Body.
//--------------

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_OPERATOR_BODY(argcount) \
  derived_type WG_PP_LCLFUNCTION_CONSTINVARIANCE_KEYWORD_CONST * const dptr = \
    static_cast \
    < \
      derived_type WG_PP_LCLFUNCTION_CONSTINVARIANCE_KEYWORD_CONST * \
    >(this); \
  return local_functor_type::user_callback( \
    *dptr \
    BOOST_PP_ENUM_TRAILING_PARAMS( \
      argcount, \
      WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_OPERATOR_ARGROOTNAME()), \
    dptr->m_CapturedVars);

//--------
//Operator
//--------

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_OPERATOR_DCLN(argcount) \
  result_type operator()( \
    WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_OPERATOR_PARAMLIST(argcount) ) \
    WG_PP_LCLFUNCTION_CONSTINVARIANCE_KEYWORD_CONST \
  { \
    WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_OPERATOR_BODY(argcount) \
  }

//-----
//Class
//-----

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_CLASS(argcount) \
  /* Partial specialize on function operator Arity. */ \
  template \
  < \
    typename Derived, \
    typename LclFunctionType, \
    typename LocalFunctorType \
  > \
  class \
    WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_NAME() \
    < \
      Derived, \
      LclFunctionType, \
      LocalFunctorType, \
      argcount \
    > \
  : public global_functor_base_type \
  { \
    typedef Derived derived_type; \
    typedef LocalFunctorType local_functor_type; \
    \
    WG_PP_LCLFUNCTION_CGUTILS_FUNCTIONOPERATORUTILS_FUNCTORCOMPONENTDCLNS( \
      LclFunctionType, argcount) \
    \
    /* The function operator that is exposed to the user and is the public */ \
    /* interface of the local function object. */ \
    /* This interface is created from WG_LCLFUNCTION's params specification. */ \
    WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_OPERATOR_DCLN(argcount) \
  };

#endif /* WG_PP_LOCAL_DETAIL_LCLFUNCTION_FUNCTIONOPERATORTYPECPP11_HH_ */
