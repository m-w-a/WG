#ifndef WG_LCLFUNCTION_DETAIL_GLOBALFUNCTORTYPECPP11_HH_
#define WG_LCLFUNCTION_DETAIL_GLOBALFUNCTORTYPECPP11_HH_

#include <boost/function_types/result_type.hpp>
#include <boost/function_types/parameter_types.hpp>
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
    typename ::boost::function_types::result_type<LCLFUNCTIONTYPE>::type, \
    ::boost::function_types::parameter_types<LCLFUNCTIONTYPE>, \
    ::boost::function_types::function_arity<LCLFUNCTIONTYPE>::value \
  >

// LOCALFUNCTORTYPE: The local functor type (C++11).
// LCLFUNCTIONTYPE: The specified local function type.
// CAPTUREDVARSTYPE: A tuple of captured local variables, if any.
template<
  typename LOCALFUNCTORTYPE,
  typename LCLFUNCTIONTYPE,
  typename CAPTUREDVARSTYPE>
class global_functor_type :
  public FUNCTIONOPERATORTYPE
{
  friend class FUNCTIONOPERATORTYPE;
  typedef FUNCTIONOPERATORTYPE base_class_type;

#undef FUNCTIONOPERATORTYPE

public:
  typedef LCLFUNCTIONTYPE function_type;
  typedef CAPTUREDVARSTYPE captured_vars_type;

public:
  explicit global_functor_type(captured_vars_type const & vars)
  : m_CapturedVars(vars)
  {}

  using base_class_type::operator();

private:
  // Mutable to allow this obj to be used with const std::function.
  WG_PP_LCLFUNCTION_CONSTINVARIANCE_KEYWORD_MUTABLE
    captured_vars_type m_CapturedVars;
};

}
}
}
}

#endif /* WG_LCLFUNCTION_DETAIL_GLOBALFUNCTORTYPECPP11_HH_ */
