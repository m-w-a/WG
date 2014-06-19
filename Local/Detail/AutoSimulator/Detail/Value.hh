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

#define WG_AUTOSIMULATOR_DETAIL_AUTOANY_DOWNCAST(enclosed_type, opaqued_obj) \
  captured_obj( static_cast<auto_any_impl<enclosed_type> const &>(opaqued_obj) )

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
template <typename DT, typename C>
inline BOOST_DEDUCED_TYPENAME captured_type<DT, C>::rvalue &
  value(
    auto_any const & opaqued_obj,
    type_wrapper<DT, C> *,
    ::boost::mpl::true_ *)
{
  return WG_AUTOSIMULATOR_DETAIL_AUTOANY_DOWNCAST(DT const, opaqued_obj);
}

// WG_AUTOSIMULATOR_DETAIL_CONFIG_CONSTRVALUEDETECTION_COMPILETIME:
//   t is a lvalue
// WG_AUTOSIMULATOR_DETAIL_CONFIG_CONSTRVALUEDETECTION_RUNTIME:
//   t is an array (all arrays are lvalues) or a non-const lvalue
template <typename DT, typename C>
inline BOOST_DEDUCED_TYPENAME captured_type<DT, C>::lvalue &
  value(
    auto_any const & opaqued_obj,
    type_wrapper<DT, C> *,
    ::boost::mpl::false_ *)
{
  typedef
    BOOST_DEDUCED_TYPENAME captured_type<DT, C>::lvalue
      captured_type;

  return WG_AUTOSIMULATOR_DETAIL_AUTOANY_DOWNCAST(captured_type *, opaqued_obj);
}

#ifdef WG_AUTOSIMULATOR_DETAIL_CONFIG_CONSTRVALUEDETECTION_RUNTIME

// t is a const, non-array lvalue or it's an rvalue
template <typename DT, typename C>
inline BOOST_DEDUCED_TYPENAME captured_type<DT, C>::const_lvalue_or_rvalue &
  value(
    auto_any const & opaqued_obj,
    type_wrapper<DT, C> *,
    bool *)
{
  typedef simple_variant<DT const> variant_t;

  return
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_DOWNCAST(
      variant_t,
      opaqued_obj);
}

#endif

}
}
}

#endif /* WG_SIMULATOR_DETAIL_VALUE_HH_ */
