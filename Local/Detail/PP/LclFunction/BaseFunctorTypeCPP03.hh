#ifndef WG_PP_LOCAL_DETAIL_LCLFUNCTION_BASEFUNCTORTYPECPP03_HH_
#define WG_PP_LOCAL_DETAIL_LCLFUNCTION_BASEFUNCTORTYPECPP03_HH_

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

#define WG_PP_BASEFUNCTORTYPE_OPERATORS_CPP03() \
  WG_PP_BASEFUNCTORTYPE_OPERATORS_CPP03_IMPL()

//###########
//Impl Macros
//###########

//--------------------
//Operator Param List.
//--------------------

#define WG_PP_BASEFUNCTORTYPE_OPERATOR_CPP03_PARAMLIST(argcount) \
  BOOST_PP_ENUM( \
    argcount, \
    WG_PP_BASEFUNCTORTYPE_OPERATOR_CPP03_PARAMLIST_ENTRY, \
    ~)

// BOOST_PP_ENUM functor.
#define WG_PP_BASEFUNCTORTYPE_OPERATOR_CPP03_PARAMLIST_ENTRY(z, indx, data) \
  typename boost::add_reference \
  < \
    typename boost::add_const \
    < \
      typename boost::mpl::at<parameter_types, boost::mpl::int_<indx> >::type \
    >::type \
  >::type BOOST_PP_CAT(arg, indx)

//--------------
//Operator Body.
//--------------

#define WG_PP_BASEFUNCTORTYPE_OPERATOR_CPP03_BODY(argcount) \
  BOOST_STATIC_ASSERT((base_functor_type::arity == argcount)); \
  return m_CallBack( \
    *this \
    BOOST_PP_ENUM_TRAILING_PARAMS(argcount, arg) \
    , m_CapturedVars);

//--------
//Operator
//--------

#define WG_PP_BASEFUNCTORTYPE_OPERATORS_CPP03_IMPL() \
  BOOST_PP_REPEAT( \
    WG_PP_LCLFUNCTION_MAX_ARGS, \
    WG_PP_BASEFUNCTORTYPE_OPERATOR_CPP03_OVERLOAD, \
    ~)

// BOOST_PP_REPEAT functor.
#define WG_PP_BASEFUNCTORTYPE_OPERATOR_CPP03_OVERLOAD(z, argcount, data) \
  result_type operator()( \
    WG_PP_BASEFUNCTORTYPE_OPERATOR_CPP03_PARAMLIST(argcount) ) const \
  { \
    WG_PP_BASEFUNCTORTYPE_OPERATOR_CPP03_BODY(argcount) \
  }

#endif /* WG_PP_LOCAL_DETAIL_LCLFUNCTION_BASEFUNCTORTYPECPP03_HH_ */
