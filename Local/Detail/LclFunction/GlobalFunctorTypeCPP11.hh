#ifndef WG_LCLFUNCTION_DETAIL_GLOBALFUNCTORTYPECPP11_HH_
#define WG_LCLFUNCTION_DETAIL_GLOBALFUNCTORTYPECPP11_HH_

#include <boost/function_types/function_arity.hpp>
#include <WG/Local/Detail/PP/LclFunction/FunctionOperatorTypeCPP11.hh>

namespace wg
{
namespace lclfunction
{
namespace detail
{
namespace cpp11
{

WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_DCLNS()

#define FUNCTIONOPERATORTYPE \
  WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP11_NAME() \
  < \
    global_functor_type<LOCALFUNCTORTYPE, LCLFUNCTIONTYPE, CAPTUREDVARSTYPE>, \
    LOCALFUNCTORTYPE, \
    LCLFUNCTIONTYPE, \
    boost::function_types::function_arity<LCLFUNCTIONTYPE>::value \
  >

// LOCALFUNCTORTYPE: The local functor type (C++11).
// LCLFUNCTIONTYPE: The specified local function type.
// CAPTUREDVARSTYPE: A tuple of captured local variables, if any.
template<
  typename LOCALFUNCTORTYPE,
  typename LCLFUNCTIONTYPE,
  typename CAPTUREDVARSTYPE>
class global_functor_type :
  private FUNCTIONOPERATORTYPE
{
  friend class FUNCTIONOPERATORTYPE;
  typedef FUNCTIONOPERATORTYPE function_operator_type;

#undef FUNCTIONOPERATORTYPE

public:
  typedef LOCALFUNCTORTYPE local_functor_type;
  typedef LCLFUNCTIONTYPE local_function_type;
  typedef CAPTUREDVARSTYPE captured_vars_type;

public:
  explicit global_functor_type(captured_vars_type const & vars)
  : m_CapturedVars(vars)
  {}

  //--------------------------------------------------------------------------//
  // PP generate operator() methods up to WG_PP_LCLFUNCTION_MAX_ARGS params.
  // add_const add_ref params until very end.
  // Method const so as to be able to be called by const std::function.
  //--------------------------------------------------------------------------//

  //  typedef
  //    typename boost::function_types::result_type<local_function_type>::type
  //      result_type;
  //
  //  typedef
  //    boost::function_types::parameter_types<local_function_type>
  //      parameter_types;
  //
  //  static int const arity =
  //    boost::function_types::function_arity<local_function_type>::value;
  //
  //  result_type operator()() const
  //  {
  //    BOOST_STATIC_ASSERT((global_functor_type::arity == 0));
  //    return local_functor_type::user_callback(*this, m_CapturedVars);
  //  }
  //
  // /* int operator()(int const & arg0, int const & arg1) const */
  //  result_type operator()(
  //    typename boost::add_reference
  //    <
  //      typename boost::add_const
  //      <
  //        typename boost::mpl::at<parameter_types, boost::mpl::int_<0> >::type
  //      >::type
  //    >::type arg0,
  //    typename boost::add_reference
  //    <
  //      typename boost::add_const
  //      <
  //        typename boost::mpl::at<parameter_types, boost::mpl::int_<1> >::type
  //      >::type
  //    >::type arg1) const
  //  {
  //    BOOST_STATIC_ASSERT((global_functor_type::arity == 2));
  //    return local_functor_type::user_callback(*this, arg0, arg1, m_CapturedVars);
  //  }

  using function_operator_type::operator();

private:
  // Note: the const-ness of m_CapturedVars will not propogate to it's member
  //   types if said types are references, since add_const<T &>::type is T.
  //   Hence no compile time errors will ensue when unpacking data to each
  //   individual captured var.
  captured_vars_type m_CapturedVars;
};

}
}
}
}

#endif /* WG_LCLFUNCTION_DETAIL_GLOBALFUNCTORTYPECPP11_HH_ */
