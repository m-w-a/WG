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
    captured_obj, \
    WG_AUTOSIMULATOR_DETAIL_ENCODEDTYPEOF(expr), \
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(expr) )

namespace wg
{
namespace autosimulator
{
namespace detail
{

// WG_AUTOSIMULATOR_DETAIL_CONFIG_CONSTRVALUEDETECTION_COMPILETIME:
//   t is a rvalue
// WG_AUTOSIMULATOR_DETAIL_CONFIG_CONSTRVALUEDETECTION_RUNTIME:
//   never called
template <typename T, typename IsExprConst>
inline T const & value(
  auto_any const & opaqued_obj,
  type_wrapper<T, IsExprConst> *,
  ::boost::mpl::true_ *)
{
  return util::auto_any_cast<T, ::boost::mpl::true_>(opaqued_obj);
}

// WG_AUTOSIMULATOR_DETAIL_CONFIG_CONSTRVALUEDETECTION_COMPILETIME:
//   t is a lvalue
// WG_AUTOSIMULATOR_DETAIL_CONFIG_CONSTRVALUEDETECTION_RUNTIME:
//   t is an array (all arrays are lvalues) or a non-const lvalue
template <typename T, typename IsExprConst>
inline ::boost::mpl::if_<IsExprConst, T const, T>::type & value(
  auto_any const & opaqued_obj,
  type_wrapper<T, IsExprConst> *,
  ::boost::mpl::false_ *)
{
  return util::auto_any_cast<T, IsExprConst>(opaqued_obj);
}

#ifdef WG_AUTOSIMULATOR_DETAIL_CONFIG_CONSTRVALUEDETECTION_RUNTIME

// t is a const, non-array lvalue or it's an rvalue
template <typename T, typename IsExprConst>
inline T const & visit(
  auto_any const & opaqued_obj,
  type_wrapper<T, IsExprConst> *,
  bool *)
{
  return
    util::auto_any_cast
    <
      simple_variant<T>,
      ::boost::mpl::true_
    >(opaqued_obj).value();
}

#endif

}
}
}

#endif /* WG_SIMULATOR_DETAIL_VALUE_HH_ */
