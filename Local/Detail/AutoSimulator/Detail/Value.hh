#ifndef WG_SIMULATOR_DETAIL_VALUE_HH_
#define WG_SIMULATOR_DETAIL_VALUE_HH_

#include <boost/config.hpp>
#include <boost/mpl/bool_fwd.hpp>
#include <WG/Local/Detail/AutoSimulator/Detail/Config.hh>
#include <WG/Local/Detail/AutoSimulator/Detail/TypeWrapper.hh>
#include <WG/Local/Detail/AutoSimulator/Detail/AutoAny.hh>

//###########
//Public APIs
//###########

#define WG_AUTOSIMULATOR_DETAIL_VALUE(captured_obj, expr) \
  WG_AUTOSIMULATOR_DETAIL_VALUE_IMPL(captured_obj, expr)

//####
//Impl
//####

#define WG_AUTOSIMULATOR_DETAIL_VALUE_IMPL(captured_obj, expr) \
  ::wg::autosimulator::detail::value( \
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(expr), \
    captured_obj, \
    WG_AUTOSIMULATOR_DETAIL_ENCODEDTYPEOF(expr))

#define WG_AUTOSIMULATOR_DETAIL_AUTOANY_DOWNCAST(auto_any_impl_type, opaqued_obj) \
  captured_obj( static_cast<auto_any_impl_type const &>(opaqued_obj) )

namespace wg
{
namespace autosimulator
{
namespace detail
{

template
<
  typename ExprCategory,
  typename NonConstNonRefExprType,
  typename IsExprConst
>
inline BOOST_DEDUCED_TYPENAME
  dfta_traits
  <
    ExprCategory,
    NonConstNonRefExprType,
    IsExprConst
  >::captured_expr_type &
    value(
      ExprCategory,
      auto_any const & opaqued_obj,
      type_wrapper<NonConstNonRefExprType, IsExprConst> *)
{
  typedef BOOST_DEDUCED_TYPENAME
    dfta_traits
    <
      ExprCategory,
      NonConstNonRefExprType,
      IsExprConst
    >::auto_any_impl_type
      auto_any_impl_type;

  return WG_AUTOSIMULATOR_DETAIL_AUTOANY_DOWNCAST(
    auto_any_impl_type,
    opaqued_obj);
}

}
}
}

#endif /* WG_SIMULATOR_DETAIL_VALUE_HH_ */
