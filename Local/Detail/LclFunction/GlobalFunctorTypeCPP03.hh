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

WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_DCLNS()

#define FUNCTIONOPERATORTYPE \
  WG_PP_LCLFUNCTION_FUNCTIONOPERATORTYPE_CPP03_NAME() \
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
  //       global_functor_type &,
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
          global_functor_type &
        >::type,
        typename function_operator_type::result_type
      >::type,
      captured_var_types &
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
