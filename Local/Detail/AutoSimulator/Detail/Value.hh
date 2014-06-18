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
template <typename DT, typename C>
inline BOOST_DEDUCED_TYPENAME captured_type<DT, C>::rvalue &
  value(
    auto_any const & opaqued_obj,
    type_wrapper<DT, C> *,
    ::boost::mpl::true_ *)
{
  return util::auto_any_cast<DT const, ::boost::mpl::true_>(opaqued_obj);
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
  return *util::auto_any_cast<captured_type *, C>(opaqued_obj);
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
  simple_variant<DT const> const & variant =
    util::auto_any_cast<simple_variant<DT const>, ::boost::mpl::true_>(opaqued_obj);

  return *variant.get_value();
}

#endif

}
}
}

#endif /* WG_SIMULATOR_DETAIL_VALUE_HH_ */
