#ifndef WG_PP_LOCAL_DETAIL_LCLFUNCTION_BASEFUNCTORTYPECPP11_HH_
#define WG_PP_LOCAL_DETAIL_LCLFUNCTION_BASEFUNCTORTYPECPP11_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <boost/static_assert.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>

//###########
//Public APIs
//###########

#define WG_PP_BASEFUNCTORTYPE_OPERATORS_CPP11() \
  WG_PP_BASEFUNCTORTYPE_OPERATORS_CPP11_IMPL()

//###########
//Impl Macros
//###########

#define WG_PP_BASEFUNCTORTYPE_OPERATOR_CPP03_USERARGROOTNAME() arg

//--------------------
//Operator Param List.
//--------------------

#define WG_PP_BASEFUNCTORTYPE_OPERATOR_CPP11_PARAMLIST(argcount) \
  BOOST_PP_ENUM( \
    argcount, \
    WG_PP_BASEFUNCTORTYPE_OPERATOR_CPP11_PARAMLIST_ENTRY, \
    ~)

// BOOST_PP_ENUM functor.
#define WG_PP_BASEFUNCTORTYPE_OPERATOR_CPP11_PARAMLIST_ENTRY(z, indx, data) \
  typename boost::add_reference \
  < \
    typename boost::add_const \
    < \
      typename boost::mpl::at<parameter_types, boost::mpl::int_<indx> >::type \
    >::type \
  >::type \
    BOOST_PP_CAT( \
      WG_PP_BASEFUNCTORTYPE_OPERATOR_CPP03_USERARGROOTNAME(), indx)

//--------------
//Operator Body.
//--------------

#define WG_PP_BASEFUNCTORTYPE_OPERATOR_CPP11_BODY(argcount) \
  BOOST_STATIC_ASSERT((global_functor_type::arity == argcount)); \
  return functor_type::user_callback( \
    *this \
    BOOST_PP_ENUM_TRAILING_PARAMS( \
      argcount, \
      WG_PP_BASEFUNCTORTYPE_OPERATOR_CPP03_USERARGROOTNAME()) \
    , this->m_CapturedVars);

//--------
//Operator
//--------

#define WG_PP_BASEFUNCTORTYPE_OPERATORS_CPP11_IMPL() \
  BOOST_PP_REPEAT( \
    WG_PP_LCLFUNCTION_MAX_ARGS, \
    WG_PP_BASEFUNCTORTYPE_OPERATOR_CPP11_OVERLOAD, \
    ~)

// BOOST_PP_REPEAT functor.
#define WG_PP_BASEFUNCTORTYPE_OPERATOR_CPP11_OVERLOAD(z, argcount, data) \
  result_type operator()( \
    WG_PP_BASEFUNCTORTYPE_OPERATOR_CPP11_PARAMLIST(argcount) ) const \
  { \
    WG_PP_BASEFUNCTORTYPE_OPERATOR_CPP11_BODY(argcount) \
  }

#endif /* WG_PP_LOCAL_DETAIL_LCLFUNCTION_BASEFUNCTORTYPECPP11_HH_ */
