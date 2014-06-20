#ifndef WG_AUTOSIMULATOR_HH_
#define WG_AUTOSIMULATOR_HH_

#include <WG/Local/Detail/AutoSimulator/Detail/AutoAny.hh>

//###########
//Public APIs
//###########

namespace wg
{
namespace autosimulator
{

namespace detail
{
struct auto_any;
}

//------------------------------------------------------------------------------
//auto_any_t
//  General utility for putting an object of any type into automatic storage.
//------------------------------------------------------------------------------
typedef detail::auto_any const & auto_any_t;

}
}

// This macro is used to emulate C++11 auto-deduced reference objects without
// the use of any of Boost.Typeof utilities. In C++11 speak, this macro emulates
// the following using cases:
//   auto & v = expr; // For expressions that are lvalues or const rvalues, else
//   auto const & v = expr; // For expressions that are mutable rvalues.
//
//   Note: "auto & v = expr;" for expressions that are mutable rvalues is
//     ill-formed since it's attempting to bind a rvalue to a non-const reference.
// Usage:
//   auto_any_t captured_obj = WG_AUTOSIMULATOR_DETAIL_CAPTURE(...) ;
// expr:
//   The expr whose result will be captured without using Boost.Typeof.
// is_rvalue_flag:
//   A mutable boolean flag.
#define WG_AUTOSIMULATOR_CAPTURE(expr, is_rvalue_flag) \
  WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(expr, is_rvalue_flag)

#define WG_AUTOSIMULATOR_AUTOANY_VALUE(captured_obj, expr) \
  WG_AUTOSIMULATOR_DETAIL_AUTOANY_VALUE(captured_obj, expr)

#endif /* WG_AUTOSIMULATOR_HH_ */
