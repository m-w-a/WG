#ifndef WG_PP_LOCAL_DETAIL_LCLFUNCTION_FUNCTIONOPERATORUTILS_HH_
#define WG_PP_LOCAL_DETAIL_LCLFUNCTION_FUNCTIONOPERATORUTILS_HH_

#include <boost/preprocessor.hpp>

#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/parameter_types.hpp>

//###########
//Public APIs
//###########

#define WG_PP_LCLFUNCTION_CGUTILS_FUNCTIONOPERATORUTILS_FUNCTORCOMPONENTDCLNS( \
  tpl_param_local_function_rettype, tpl_param_local_function_params, arity) \
    WG_PP_LCLFUNCTION_CGUTILS_FUNCTIONOPERATORUTILS_FUNCTORCOMPONENTDCLNS_IMPL( \
      tpl_param_local_function_rettype, tpl_param_local_function_params, arity)

#define WG_PP_LCLFUNCTION_CGUTILS_FUNCTIONOPERATORUTILS_ARGTYPENAME(indx) \
  WG_PP_LCLFUNCTION_CGUTILS_FUNCTIONOPERATORUTILS_ARGTYPENAME_IMPL(indx)

//###########
//Impl Macros
//###########

#define \
  WG_PP_LCLFUNCTION_CGUTILS_FUNCTIONOPERATORUTILS_FUNCTORCOMPONENTDCLNS_IMPL( \
    tpl_param_local_function_rettype, tpl_param_local_function_params, arity_) \
      \
      typedef tpl_param_local_function_rettype result_type; \
      \
      typedef tpl_param_local_function_params parameter_types; \
      \
      WG_PP_LCLFUNCTION_FUNCTIONOPERATORUTILS_ARGTYPEDCLNS(arity_) \
      \
      static int const arity = arity_; \

#define WG_PP_LCLFUNCTION_CGUTILS_FUNCTIONOPERATORUTILS_ARGTYPENAME_IMPL(indx) \
  BOOST_PP_CAT( \
    arg, \
    BOOST_PP_CAT( \
      BOOST_PP_INC(indx), \
      _type))

#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORUTILS_ARGTYPEDCLNS(arity) \
  BOOST_PP_REPEAT( \
    arity, \
    WG_PP_LCLFUNCTION_FUNCTIONOPERATORUTILS_ARGTYPEDCLNS_ENTRY, \
    ~)

// BOOST_PP_REPEAT functor.
#define WG_PP_LCLFUNCTION_FUNCTIONOPERATORUTILS_ARGTYPEDCLNS_ENTRY( \
  z, indx, data) \
  typedef \
    typename boost::mpl::at<parameter_types, boost::mpl::int_<indx> >::type \
      WG_PP_LCLFUNCTION_CGUTILS_FUNCTIONOPERATORUTILS_ARGTYPENAME(indx) ;

#endif /* WG_PP_LOCAL_DETAIL_LCLFUNCTION_FUNCTIONOPERATORUTILS_HH_ */
