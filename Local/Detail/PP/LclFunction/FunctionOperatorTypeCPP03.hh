#ifndef WG_PP_LOCAL_DETAIL_LCLFUNCTION_FUNCTIONOPERATORTYPECPP03_HH_
#define WG_PP_LOCAL_DETAIL_LCLFUNCTION_FUNCTIONOPERATORTYPECPP03_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <boost/static_assert.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/parameter_types.hpp>

//###########
//Public APIs
//###########

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_BASECLASS_NAME() \
  WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_BASECLASS_NAME_IMPL()

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_BASECLASS_DCLNS() \
  WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_BASECLASS_DCLNS_IMPL()

//###########
//Impl Macros
//###########

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_OPERATOR_USERARGROOTNAME() arg

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_BASECLASS_NAME_IMPL() \
  base_functor_type

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_BASECLASS_DCLNS_IMPL() \
  /* Declared and purposefully not defined. */ \
  template \
  < \
    typename DERIVED, \
    typename LCLFUNCTIONTYPE, \
    int ARITY \
  > \
  struct WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_BASECLASS_NAME() ; \
  \
  /* Begin partial specializations. */ \
  BOOST_PP_REPEAT( \
    WG_PP_LCLFUNCTION_MAX_ARGS, \
    WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_BASECLASS_DCLNS_ENTRY, \
    ~)

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_BASECLASS_DCLNS_ENTRY( \
  z, argcount, data) \
    WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_BASECLASS(argcount)

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
  typename boost::add_reference \
  < \
    typename boost::add_const \
    < \
      typename boost::mpl::at<parameter_types, boost::mpl::int_<indx> >::type \
    >::type \
  >::type \
    BOOST_PP_CAT( \
      WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_OPERATOR_USERARGROOTNAME(), indx)

//--------------
//Operator Body.
//--------------

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_OPERATOR_BODY(argcount) \
  derived_type const * const dptr = static_cast<derived_type const *>(this); \
  return dptr->m_CallBack( \
    *dptr \
    BOOST_PP_ENUM_TRAILING_PARAMS( \
      argcount, \
      WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_OPERATOR_USERARGROOTNAME()) \
    , dptr->m_CapturedVars);

//--------
//Operator
//--------

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_OPERATOR_DCLN(argcount) \
  result_type operator()( \
    WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_OPERATOR_PARAMLIST(argcount) ) const \
  { \
    WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_OPERATOR_BODY(argcount) \
  }

//-----
//Class
//-----

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_BASECLASS(argcount) \
  template \
  < \
    typename DERIVED, \
    typename LCLFUNCTIONTYPE \
  > \
  class \
    WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_BASECLASS_NAME() \
    <DERIVED, LCLFUNCTIONTYPE, argcount> \
  { \
    typedef DERIVED derived_type; \
    typedef LCLFUNCTIONTYPE local_function_type; \
    \
  public: \
    typedef \
      typename boost::function_types::result_type<local_function_type>::type \
        result_type; \
    \
    typedef \
      boost::function_types::parameter_types<local_function_type> \
        parameter_types; \
    \
    static int const arity = argcount; \
    \
    WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_OPERATOR_DCLN(argcount) \
  };

#endif /* WG_PP_LOCAL_DETAIL_LCLFUNCTION_FUNCTIONOPERATORTYPECPP03_HH_ */
