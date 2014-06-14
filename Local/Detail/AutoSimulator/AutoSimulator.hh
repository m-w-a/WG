#ifndef WG_AUTOSIMULATOR_HH_
#define WG_AUTOSIMULATOR_HH_

#include <WG/Local/Detail/AutoSimulator/Detail/AutoAny.hh>
#include <WG/Local/Detail/AutoSimulator/Detail/Visit.hh>

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

template <typename VisitorImpl, typename ReturnType = void>
struct visitor : private detail::visitor_base
{
  typedef ReturnType return_type;

  template <typename T>
  return_type visit(T & captured_obj)
  {
    return static_cast<VisitorImpl *>(this)->visit(captured_obj);
  }

  template <typename T>
  return_type visit(T const & captured_obj)
  {
    return static_cast<VisitorImpl *>(this)->visit(captured_obj);
  }
};

}
}

// Usage:
//   auto_any_t opaqued_captured_obj = WG_AUTOSIMULATOR_DETAIL_CAPTURE(...) ;
// expr:
//   The expr whose result will be captured without using BOOST_TYPEOF.
// is_rvalue_flag:
//   A mutable boolean flag.
#define WG_AUTOSIMULATOR_CAPTURE(expr, is_rvalue_flag) \
  WG_AUTOSIMULATOR_DETAIL_CAPTURE(expr, is_rvalue_flag)

// opaqued_captured_obj:
//   An auto_any_t object that was initialized via WG_AUTOSIMULATOR_CAPTURE.
// expr:
//   The expr that was passed to WG_AUTOSIMULATOR_CAPTURE.
// visitor:
//   A ::wg::rvalue_simulator::visitor object.
#define WG_AUTOSIMULATOR_VISIT(opaqued_captured_obj, expr, visitor) \
  WG_AUTOSIMULATOR_DETAIL_VISIT(opaqued_captured_obj, expr, visitor)

#endif /* WG_AUTOSIMULATOR_HH_ */
