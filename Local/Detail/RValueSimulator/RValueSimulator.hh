#ifndef WG_RVALUESIMULATOR_HH_
#define WG_RVALUESIMULATOR_HH_

#include <WG/Local/Detail/RValueSimulator/Capture.hh>

//###########
//Public APIs
//###########

namespace wg
{
namespace rvaluesimulator
{

template <typename VisitorImpl, typename ReturnType = void>
struct visitor
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
//   auto_any_t opaqued_captured_obj = WG_RVALUESIMULATOR_DETAIL_CAPTURE(...) ;
// expr:
//   The expr whose result will be captured without using BOOST_TYPEOF.
// is_rvalue_flag:
//   A mutable boolean flag.
#define WG_RVALUESIMULATOR_CAPTURE(expr, is_rvalue_flag) \
  WG_RVALUESIMULATOR_DETAIL_CAPTURE(expr, is_rvalue_flag)

// opaqued_captured_obj:
//   An auto_any_t object that was initialized via WG_RVALUESIMULATOR_CAPTURE.
// expr:
//   The expr that was passed to WG_RVALUESIMULATOR_CAPTURE.
// visitor:
//   A ::wg::rvalue_simulator::visitor object.
#define WG_RVALUESIMULATOR_VISIT(opaqued_captured_obj, expr, visitor) \
  WG_RVALUESIMULATOR_DETAIL_VISIT(opaqued_captured_obj, expr, visitor)

#endif /* WG_RVALUESIMULATOR_HH_ */
