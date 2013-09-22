#ifndef WG_LCLFUNCTION_DETAIL_GLOBALFUNCTORTYPECPP03_HH_
#define WG_LCLFUNCTION_DETAIL_GLOBALFUNCTORTYPECPP03_HH_

#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/function_pointer.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include <WG/Local/Detail/PP/LclFunction/FunctionOperatorTypeCPP03.hh>

namespace wg
{
namespace lclfunction
{
namespace detail
{

WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_BASECLASS_DCLNS()

#define FUNCTIONOPERATORTYPE \
  WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_BASECLASS_NAME() \
  < \
    global_functor_type<LCLFUNCTIONTYPE, CAPTUREDVARSTYPE>, \
    LCLFUNCTIONTYPE, \
    boost::function_types::function_arity<LCLFUNCTIONTYPE>::value \
  >

// LCLFUNCTIONTYPE: The specified local function type.
// CAPTUREDVARSTYPE: A tuple of captured local variables, if any.
template<
  typename LCLFUNCTIONTYPE,
  typename CAPTUREDVARSTYPE>
class global_functor_type :
  private FUNCTIONOPERATORTYPE
{
  friend class FUNCTIONOPERATORTYPE;
  typedef FUNCTIONOPERATORTYPE function_operator_type;

#undef FUNCTIONOPERATORTYPE

public:
  typedef LCLFUNCTIONTYPE local_function_type;
  typedef CAPTUREDVARSTYPE captured_var_types;

private:
  // Synthesize the call back type. It's prototype should be:
  //
  //   typedef typename result_type<local_function_type>::type
  //     (*callback_type)(
  //       global_functor_type const &,
  //       param_types<local_function_type>,
  //       CAPTUREDVARSTYPE &);
  typedef
    typename boost::mpl::push_back
    <
      typename boost::mpl::push_front
      <
        typename boost::mpl::push_front
        <
          typename function_operator_type::parameter_types,
          global_functor_type const &
        >::type,
        typename function_operator_type::result_type
      >::type,
      captured_var_types const &
    >::type mpl_callback_type;

public:
  typedef
    typename boost::function_types::function_pointer<mpl_callback_type>::type
      callback_type;

public:
  explicit global_functor_type(captured_var_types const & vars)
  : m_CallBack(0),
    m_CapturedVars(vars)
  {}

  void set_caller(callback_type const callback)
  {
    this->m_CallBack = callback;
  }

  //--------------------------------------------------------------------------//
  // PP generate operator() methods up to WG_PP_LCLFUNCTION_MAX_ARGS params.
  // add_const add_ref params until very end.
  // Method const so as to be able to be called by const std::function.
  //--------------------------------------------------------------------------//

  //  result_type operator()() const
  //  {
  //    BOOST_STATIC_ASSERT((global_functor_type::arity == 0));
  //    return m_CallBack(*this, m_CapturedVars);
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
  //    return m_CallBack(*this, arg0, arg1, m_CapturedVars);
  //  }

  using function_operator_type::operator();

private:
  callback_type m_CallBack;
  // Note: the const-ness of m_CapturedVars will not propogate to it's member
  //   types if said types are references, since add_const<T &>::type is T.
  //   Hence no compile time errors will ensue when unpacking data to each
  //   individual captured var.
  captured_var_types m_CapturedVars;
};

}
}
}

#endif /* WG_LCLFUNCTION_DETAIL_GLOBALFUNCTORTYPECPP03_HH_ */
