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
