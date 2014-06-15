#ifndef WG_AUTOSIMULATOR_DETAIL_VISIT_HH_
#define WG_AUTOSIMULATOR_DETAIL_VISIT_HH_

#include <boost/config.hpp>
#include <boost/mpl/bool_fwd.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <WG/Local/Detail/AutoSimulator/Detail/Config.hh>
#include <WG/Local/Detail/AutoSimulator/Detail/TypeWrapper.hh>
#include <WG/Local/Detail/AutoSimulator/Detail/AutoAny.hh>

//###########
//Public APIs
//###########

#define WG_AUTOSIMULATOR_DETAIL_VISIT(opaqued_captured_obj, expr, visitor) \
  WG_AUTOSIMULATOR_DETAIL_VISIT_IMPL(opaqued_captured_obj, expr, visitor)

//####
//Impl
//####

#define WG_AUTOSIMULATOR_DETAIL_VISIT_IMPL( \
  opaqued_captured_obj, expr, visitor) \
    ::wg::autosimulator::detail::visit( \
      visitor, \
      opaqued_captured_obj, \
      WG_AUTOSIMULATOR_DETAIL_ENCODEDTYPEOF(expr), \
      WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(expr) )

namespace wg
{
namespace autosimulator
{
namespace detail
{

struct visitor_base
{
};

// WG_AUTOSIMULATOR_DETAIL_CONFIG_CONSTRVALUEDETECTION_COMPILETIME:
//   t is a rvalue
// WG_AUTOSIMULATOR_DETAIL_CONFIG_CONSTRVALUEDETECTION_RUNTIME:
//   never called
template <typename Visitor, typename T, typename IsExprConst>
inline BOOST_DEDUCED_TYPENAME Visitor::return_type
  visit(
    Visitor & visitor,
    auto_any const & opaqued_obj,
    type_wrapper<T, IsExprConst> *,
    ::boost::mpl::true_ *)
{
  BOOST_STATIC_ASSERT((::boost::is_base_of<visitor_base, Visitor>::value));
  // Since the captured expression was an rvalue, the captured object is not const.
  return visitor.visit(util::auto_any_cast<T, ::boost::mpl::false_>(opaqued_obj));
}

// WG_AUTOSIMULATOR_DETAIL_CONFIG_CONSTRVALUEDETECTION_COMPILETIME:
//   t is a lvalue
// WG_AUTOSIMULATOR_DETAIL_CONFIG_CONSTRVALUEDETECTION_RUNTIME:
//   t is an array (all arrays are lvalues) or a non-const lvalue
template <typename Visitor, typename T, typename IsExprConst>
inline BOOST_DEDUCED_TYPENAME Visitor::return_type
  visit(
    Visitor & visitor,
    auto_any const & opaqued_obj,
    type_wrapper<T, IsExprConst> *,
    ::boost::mpl::false_ *)
{
  BOOST_STATIC_ASSERT((::boost::is_base_of<visitor_base, Visitor>::value));
  // Since the captured expression was an lvalue, the type of the captured object
  // will be determined by IsExprConst.
  return visitor.visit(util::auto_any_cast<T, IsExprConst>(opaqued_obj));
}

#ifdef WG_AUTOSIMULATOR_DETAIL_CONFIG_CONSTRVALUEDETECTION_RUNTIME

// t is a const, non-array lvalue or it's an rvalue
template <typename Visitor, typename T, typename IsExprConst>
inline BOOST_DEDUCED_TYPENAME Visitor::return_type
  visit(
    Visitor & visitor,
    auto_any const & opaqued_obj,
    type_wrapper<T, IsExprConst> *,
    bool *)
{
  BOOST_STATIC_ASSERT((::boost::is_base_of<visitor_base, Visitor>::value));
  // Remember, the variant is mutably captured.
  return
    util::auto_any_cast
    <
      simple_variant<T>,
      ::boost::mpl::false_
    >(opaqued_obj).accept_visitor(visitor);
}

#endif

}
}
}

#endif /* WG_AUTOSIMULATOR_DETAIL_VISIT_HH_ */
