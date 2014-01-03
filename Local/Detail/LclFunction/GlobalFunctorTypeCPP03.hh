#ifndef WG_LCLFUNCTION_DETAIL_GLOBALFUNCTORTYPECPP03_HH_
#define WG_LCLFUNCTION_DETAIL_GLOBALFUNCTORTYPECPP03_HH_

#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/function_types/function_pointer.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include <WG/Local/Detail/PP/LclFunction/FunctionOperatorTypeCPP03.hh>
#include <WG/Local/Detail/PP/LclFunction/ConstInvariance.hh>

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
    global_functor_type \
    < \
      LCLFUNCTION_RETTYPE, \
      LCLFUNCTION_PARAMTYPES, \
      CAPTUREDVARSTYPE \
    >, \
    LCLFUNCTION_RETTYPE, \
    LCLFUNCTION_PARAMTYPES, \
    boost::mpl::size<LCLFUNCTION_PARAMTYPES>::value \
  >

// LCLFUNCTION_PARAMTYPES:
//   An mpl vector of the specified local function param
//   types.
// CAPTUREDVARSTYPE: A tuple of captured local variables, if any.
// NOTE:
//   USERCALLBACK method type cannot be passed as a template parameter to
//   this class because its signature contains the type of this class as a
//   parameter. Hence, it has to be constructed using TMP techniques.
template<
  typename LCLFUNCTION_RETTYPE,
  typename LCLFUNCTION_PARAMTYPES,
  typename CAPTUREDVARSTYPE>
class global_functor_type :
  public FUNCTIONOPERATORTYPE
{
  friend class FUNCTIONOPERATORTYPE;
  typedef FUNCTIONOPERATORTYPE base_class_type;

#undef FUNCTIONOPERATORTYPE

public:
  typedef CAPTUREDVARSTYPE captured_var_types;

private:
  typedef
    typename boost::mpl::transform
    <
      typename base_class_type::parameter_types,
      boost::add_reference<boost::mpl::_1>
    >::type add_refd_param_types;
  // Synthesize the call back type.
  // This functions prototype should match
  // local_functor_type_cpp03::user_callback.
  typedef
    typename boost::mpl::push_back
    <
      typename boost::mpl::push_front
      <
        typename boost::mpl::push_front
        <
          add_refd_param_types,
          global_functor_type WG_PP_LCLFUNCTION_CONSTINVARIANCE_KEYWORD_CONST &
        >::type,
        typename base_class_type::result_type
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

  using base_class_type::operator();

private:
  callback_type m_CallBack;
  // Mutable to allow this obj to be used with const std::function.
  WG_PP_LCLFUNCTION_CONSTINVARIANCE_KEYWORD_MUTABLE
    captured_var_types m_CapturedVars;
};

}
}
}

#endif /* WG_LCLFUNCTION_DETAIL_GLOBALFUNCTORTYPECPP03_HH_ */
