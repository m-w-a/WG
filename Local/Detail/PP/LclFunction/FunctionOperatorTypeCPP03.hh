#ifndef WG_PP_LOCAL_DETAIL_LCLFUNCTION_FUNCTIONOPERATORTYPECPP03_HH_
#define WG_PP_LOCAL_DETAIL_LCLFUNCTION_FUNCTIONOPERATORTYPECPP03_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/LclFunction/FunctionOperatorUtils.hh>
#include <WG/Local/Detail/PP/LclFunction/ConstInvariance.hh>

//###########
//Public APIs
//###########

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_NAME() \
  WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_NAME_IMPL()

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_DCLNS() \
  WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_DCLNS_IMPL()

//###########
//Impl Macros
//###########

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_OPERATOR_ARGROOTNAME() arg

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_NAME_IMPL() \
  function_operator_type

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_DCLNS_IMPL() \
  /* Declared and purposefully not defined. */ \
  template \
  < \
    typename DERIVED, \
    typename LCLFUNCTION_RETTYPE, \
    typename LCLFUNCTION_PARAMTYPES, \
    int ARITY \
  > \
  class WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_NAME() ; \
  \
  /* Begin partial specializations. */ \
  BOOST_PP_REPEAT( \
    WG_PP_LCLFUNCTION_MAX_ARGS, \
    WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_DCLNS_ENTRY, \
    ~)

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_DCLNS_ENTRY( \
  z, argcount, data) \
    WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_CLASS(argcount)

//--------------------
//Operator Param List.
//--------------------

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_OPERATOR_PARAMLIST(argcount) \
  BOOST_PP_ENUM( \
    argcount, \
    WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_OPERATOR_PARAMLIST_ENTRY, \
    ~)

// BOOST_PP_ENUM functor.
#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_OPERATOR_PARAMLIST_ENTRY( \
  z, indx, data) \
    WG_PP_LCLFUNCTION_CGUTILS_FUNCTIONOPERATORUTILS_ARGTYPENAME(indx) \
    BOOST_PP_CAT( \
      WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_OPERATOR_ARGROOTNAME(), indx)

//--------------
//Operator Body.
//--------------

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_OPERATOR_BODY(argcount) \
  derived_type WG_PP_LCLFUNCTION_CONSTINVARIANCE_KEYWORD_CONST * const dptr = \
    static_cast \
    < \
      derived_type WG_PP_LCLFUNCTION_CONSTINVARIANCE_KEYWORD_CONST * \
    >(this); \
  return dptr->m_CallBack( \
    *dptr \
    BOOST_PP_ENUM_TRAILING_PARAMS( \
      argcount, \
      WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_OPERATOR_ARGROOTNAME()), \
      dptr->m_CapturedVars);

//--------
//Operator
//--------

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_OPERATOR_DCLN(argcount) \
  result_type operator()( \
    WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_OPERATOR_PARAMLIST(argcount) ) \
    WG_PP_LCLFUNCTION_CONSTINVARIANCE_KEYWORD_CONST \
  { \
    WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_OPERATOR_BODY(argcount) \
  }

//-----
//Class
//-----

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_CLASS(argcount) \
  /* Partial specialize on function operator arity. */ \
  template \
  < \
    typename DERIVED, \
    typename LCLFUNCTION_RETTYPE, \
    typename LCLFUNCTION_PARAMTYPES \
  > \
  class \
    WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_NAME() \
    <DERIVED, LCLFUNCTION_RETTYPE, LCLFUNCTION_PARAMTYPES, argcount> \
  { \
    typedef DERIVED derived_type; \
    \
  public: \
    WG_PP_LCLFUNCTION_CGUTILS_FUNCTIONOPERATORUTILS_FUNCTORCOMPONENTDCLNS( \
      LCLFUNCTION_RETTYPE, LCLFUNCTION_PARAMTYPES, argcount) \
    \
    /* The function operator that is exposed to the user and is the public */ \
    /* interface of the local function object. */ \
    /* This interface is created from WG_LCLFUNCTION's params specification. */ \
    WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_OPERATOR_DCLN(argcount) \
  };

#endif /* WG_PP_LOCAL_DETAIL_LCLFUNCTION_FUNCTIONOPERATORTYPECPP03_HH_ */
