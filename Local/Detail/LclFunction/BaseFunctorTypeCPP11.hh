#ifndef WG_LCLFUNCTION_DETAIL_BASEFUNCTORTYPECPP11_HH_
#define WG_LCLFUNCTION_DETAIL_BASEFUNCTORTYPECPP11_HH_

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
#include <WG/Local/Detail/PP/LclFunction/BaseFunctorTypeCPP11.hh>

namespace wg
{
namespace lclfunction
{
namespace detail
{
namespace cpp11
{

// FUNCTOR: The local functor type (C++11).
// LCLFUNCTION: The specified local function type.
// CAPTUREDVARSTYPE: A tuple of captured local variables, if any.
template<
  typename FUNCTOR,
  typename LCLFUNCTION,
  typename CAPTUREDVARSTYPE>
class global_functor_type
{
public:
  typedef FUNCTOR functor_type;
  typedef LCLFUNCTION local_function_type;
  typedef CAPTUREDVARSTYPE captured_var_types;

private:
  // Synthesize the call back type. It's prototype should be:
  //
  //   typedef typename result_type<local_function_type>::type
  //     (*callback_type)(
  //       global_functor_type const &,
  //       param_types<local_function_type>,
  //       captured_var_types &);
  typedef
    typename boost::mpl::push_back
    <
      typename boost::mpl::push_front
      <
        typename boost::mpl::push_front
        <
          boost::function_types::parameter_types<local_function_type>,
          //const issue.
          global_functor_type const &
        >::type,
        typename boost::function_types::result_type<local_function_type>::type
      >::type,
      typename boost::add_reference<captured_var_types>::type
    >::type mpl_callback_type;

public:
  typedef
    typename boost::function_types::function_pointer<mpl_callback_type>::type
      callback_type;

public:
  explicit global_functor_type(captured_var_types const & vars)
  : m_CapturedVars(vars)
  {}

  typedef
    typename boost::function_types::result_type<local_function_type>::type
      result_type;

  typedef
    boost::function_types::parameter_types<local_function_type>
      parameter_types;

  static int const arity =
    boost::function_types::function_arity<local_function_type>::value;

  //--------------------------------------------------------------------------//
  // PP generate operator() methods up to WG_PP_LCLFUNCTION_MAX_ARGS params.
  // add_const add_ref params until very end.
  // Method const so as to be able to be called by const std::function.
  //--------------------------------------------------------------------------//

  //  result_type operator()() const
  //  {
  //    BOOST_STATIC_ASSERT((global_functor_type::arity == 0));
  //    return functor_type::user_callback(*this, m_CapturedVars);
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
  //    return functor_type::user_callback(*this, arg0, arg1, m_CapturedVars);
  //  }

  WG_PP_BASEFUNCTORTYPE_OPERATORS_CPP11()

private:
  // TODO:
  // Captured vars are mutable because their mutability is determined at the
  // point of their capture, and not by class methods.
  mutable captured_var_types m_CapturedVars;
};

}
}
}
}

#endif /* WG_LCLFUNCTION_DETAIL_BASEFUNCTORTYPECPP11_HH_ */
