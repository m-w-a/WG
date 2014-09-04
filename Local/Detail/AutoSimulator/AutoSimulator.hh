#ifndef WG_AUTOSIMULATOR_HH_
#define WG_AUTOSIMULATOR_HH_

#include <WG/Local/Detail/AutoSimulator/Detail/AutoAny.hh>
#include <WG/Local/Detail/AutoSimulator/Detail/AutoAnyGroup.hh>

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
struct auto_any_group;
}

//------------------------------------------------------------------------------
//auto_any_t
//auto_any_group_t
//  General utility for putting an object of any type into automatic storage.
//------------------------------------------------------------------------------
typedef detail::auto_any const & auto_any_t;
typedef detail::auto_any_group const & auto_any_group_t;

}
}

// This macro is used to emulate C++11 auto-deduced universal references without
// the use of any of Boost.Typeof utilities. In C++11 speak, this macro emulates
// the following using case:
//   auto && v = expr;
//
// Limitations:
//   1) This macro cannot work for noncopyable const rvalues. This is because such
//    values cannot be copied nor moved, therefore their lifetime cannot be
//    portably extended to the end of scope.
//   2) This macro cannot work for noncopyable, nonmovable mutable rvalues.
//   3) To be used with this macro, noncopyable lvalues have to satisfy one
//     of the following critieron:
//     a) their type must derive from ::boost::noncopyable, or
//     b) their copy constructor must be marked "= delete", or
//     c) they must be marked with BOOST_MOVABLE_BUT_NOT_COPYABLE, or
//     d) a specialization of ::boost::copy_constructible must be made for their
//       type. (See .../libs/type_traits/doc/html/boost_typetraits/user_defined.html)
//
// Usage:
//   auto_any_t captured_obj = WG_AUTOSIMULATOR_DETAIL_CAPTURE(...) ;
//
// expr:
//   The expr whose result will be captured without using Boost.Typeof.
#define WG_AUTOSIMULATOR_AUTOANY_CAPTURE(expr, mutable_boolean_flag) \
  WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(expr, mutable_boolean_flag)

#define WG_AUTOSIMULATOR_AUTOANY_VALUE(captured_obj, expr) \
  WG_AUTOSIMULATOR_DETAIL_AUTOANY_VALUE(captured_obj, expr)

// This macro is the group analog of WG_AUTOSIMULATOR_AUTOANY_CAPTURE.
//
// Usage:
//   auto_any_group_t objs = WG_AUTOSIMULATOR_AUTOANYGROUP_ALLOC(...);
//
// exprseq:
//   A Boost.Preprocessor sequence of C++ expressions.
//
// WG_AUTOSIMULATOR_AUTOANYGROUP_CONFIG_PARAMS_MAX_ARITY:
//   This object-like macro defines the max number of expressions that may
//   makeup exprseq. If not defined by the user it defaults to 5. The maximum
//   is determined by the number of elements that boost::tuple handle, which
//   currently stands at 10.
//   To use this macro, define before the first inclusion of this header in the
//   required translation unit.
#define WG_AUTOSIMULATOR_AUTOANYGROUP_ALLOC(exprseq) \
  WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_MAKEGROUP(exprseq)

// This macro is an analog of WG_AUTOSIMULATOR_AUTOANYGROUP_ALLOC where the user
// specifies a custom baseclass.
//
// Usage:
//   baseclass const & objs = WG_AUTOSIMULATOR_AUTOANYGROUP_ALLOC(...);
//
// baseclass:
//   Must be default constructible.
//   Must define the following protected method:
//     template <typename T> void finalize(T &);
//   As part of the derived class's destructor, finalize will be called with the
//   value of each captured expression in the reverse order in which those
//   expressions appeared in exprseq.
//
// Also:
//   See WG_AUTOSIMULATOR_AUTOANYGROUP_ALLOC.
#define WG_AUTOSIMULATOR_AUTOANYGROUP_ALLOC_CUSTOM(baseclass, exprseq) \
  WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_MAKECUSTOMGROUP(baseclass, exprseq)

// Must be called to initialize allocated_obj with the value of the expressions
// in exprseq. Each expression will be evaluated in the order in which it
// appears in exprseq.
//
// Usage:
//   bool is_rvalue = false;
//   WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_INITGROUP(
//     allocated_obj,
//     is_rvalue,
//     (expr1) (expr2) ...);
#define WG_AUTOSIMULATOR_AUTOANYGROUP_INIT( \
  allocated_obj, mutable_boolean_flag, exprseq) \
    WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_INITGROUP( \
      allocated_obj, mutable_boolean_flag, exprseq)

#define WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, itemno, exprseq) \
  WG_AUTOSIMULATOR_DETAIL_AUTOANYGROUP_ITEM_VALUE(grp, itemno, exprseq)

#endif /* WG_AUTOSIMULATOR_HH_ */
