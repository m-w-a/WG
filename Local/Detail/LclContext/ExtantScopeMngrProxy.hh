#ifndef WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_HH_
#define WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_HH_

#include <boost/utility/addressof.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility.hpp>
#include <WG/Local/Detail/AutoSimulator/Detail/AutoAny.hh>

//###########
//Public APIs
//###########

namespace wg
{
namespace lclcontext
{
namespace detail
{

class extant_scopemngr_proxy;
typedef extant_scopemngr_proxy const & extant_scopemngr_proxy_t;

typedef void (*extant_exit_proxy_type)(extant_scopemngr_proxy_t, bool const);

}
}
}

// expr:
// mutable_boolean_flag:
//   See WG_AUTOSIMULATOR_AUTOANY_CAPTURE in AutoSimulator.hh
//
// Returns an obj of type extant_scopemngr_proxy_t.
#define WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_MAKE( \
  expr, mutable_boolean_flag) \
    WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_MAKE_IMPL( \
      expr, mutable_boolean_flag)

#define WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_ENTER( \
  scopemngr_proxy, expr) \
    WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_ENTER_IMPL(scopemngr_proxy, expr)

#define WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_EXIT( \
  scopemngr_proxy, expr) \
    WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_EXIT_IMPL(scopemngr_proxy, expr)

// Expands to an object of type extant_exit_proxy_type.
#define WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_EXITPROXY( \
  scopemngr_proxy, expr) \
    WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_EXITPROXY_IMPL( \
      scopemngr_proxy, expr)

//####
//Impl
//####

#define WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_MAKE_IMPL( \
  expr, mutable_boolean_flag) \
    ::wg::lclcontext::detail::make_extant_scopemngr_proxy( \
      WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(expr, mutable_boolean_flag) )

#define WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_ENTER_IMPL( \
  scopemngr_proxy, expr) \
    WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_DOWNCAST( \
      scopemngr_proxy, expr).enter()

#define WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_EXIT_IMPL( \
  scopemngr_proxy, expr) \
    WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_DOWNCAST( \
      scopemngr_proxy, expr).exit()

#define WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_EXITPROXY_IMPL( \
  scopemngr_proxy, expr) \
    ::wg::lclcontext::detail::make_extant_exit_proxy( \
      WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_DOWNCAST( \
        scopemngr_proxy, expr) )

#define WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_DOWNCAST( \
  scopemngr_proxy, expr) \
    ::wg::lclcontext::detail::extant_scopemngr_proxy_downcast( \
      scopemngr_proxy, \
      WG_AUTOSIMULATOR_DETAIL_AUTOANY_AUTOANYIMPL_DEDUCEDPTRTYPE(expr) )

namespace wg
{
namespace lclcontext
{
namespace detail
{

class extant_scopemngr_proxy
{
public:
  extant_scopemngr_proxy() {}
protected:
  extant_scopemngr_proxy(extant_scopemngr_proxy const &) {}
  extant_scopemngr_proxy(BOOST_RV_REF(extant_scopemngr_proxy) ) {}
private:
  BOOST_COPYABLE_AND_MOVABLE(extant_scopemngr_proxy)
private:
  // Declared and purposefully not defined.
  extant_scopemngr_proxy & operator=(extant_scopemngr_proxy);
};

template <typename AutoAnyImplType>
class extant_scopemngr_proxy_impl : public extant_scopemngr_proxy
{
public:
  typedef AutoAnyImplType auto_any_impl_type

public:
  // Purposefully capture by value so as to enable copy elision.
  // It is guaranteed that the parameter to this ctor will always be a rvalue.
  explicit extant_scopemngr_proxy_impl(auto_any_impl_type scopemngr)
  : m_did_call_exit(false),
    m_scopemngr(::boost::move(scopemngr))
  {}

  extant_scopemngr_proxy_impl(BOOST_RV_REF(extant_scopemngr_proxy_impl) rhs)
  : extant_scopemngr_proxy(::boost::move(static_cast<extant_scopemngr_proxy &>(rhs))),
    m_did_call_exit(rhs.m_did_call_exit),
    m_scopemngr(::boost::move(rhs.m_scopemngr))
  {}

  ~extant_scopemngr_proxy_impl()
  {
    this->exit();
  }

  template <typename R>
  R enter() const
  {
    return WG_AUTOSIMULATOR_DETAIL_AUTOANY_AUTOANYIMPL_VALUE(m_scopemngr).enter();
  }

  void exit(bool const didthrow) const
  {
    if( ! m_did_call_exit )
    {
      m_did_call_exit = true;
      WG_AUTOSIMULATOR_DETAIL_AUTOANY_AUTOANYIMPL_VALUE(m_scopemngr).exit(didthrow);
    }
  }

private:
  // Declared and purposefully not defined.
  extant_scopemngr_proxy_impl & operator=(extant_scopemngr_proxy_impl);
private:
  BOOST_COPYABLE_AND_MOVABLE(extant_scopemngr_proxy_impl)
private:
  // Objects of this type will always be accessed through a base class
  // const reference, therefore declare all members as mutable.
  mutable bool m_did_call_exit;
  mutable auto_any_impl_type m_scopemngr;
};

template <typename ExprCategory, typename CapturedType, typename EnableIfDummyArg>
// Purposefully capture by value so as to enable copy elision.
// It is guaranteed that the parameter to this ctor will always be a rvalue.
extant_scopemngr_proxy make_extant_scopemngr_proxy(
  ::wg::autosimulator::detail::auto_any_impl
  <
    ExprCategory,
    CapturedType,
    EnableIfDummyArg
  > scopemngr)
{
  typedef
    ::wg::autosimulator::detail::auto_any_impl
    <
      ExprCategory,
      CapturedType,
      EnableIfDummyArg
    >
      scopemngr_type;
  return extant_scopemngr_proxy_impl<scopemngr_type>(scopemngr);
}

template <typename ExprCategory, typename CapturedType, typename EnableIfDummyArg>
extant_scopemngr_proxy_impl
<
  ::wg::autosimulator::detail::auto_any_impl
  <
    ExprCategory,
    CapturedType,
    EnableIfDummyArg
  >
> const &
extant_scopemngr_proxy_downcast(
  extant_scopemngr_proxy_t scopemngr_proxy,
  ::wg::autosimulator::detail::auto_any_impl
  <
    ExprCategory,
    CapturedType,
    EnableIfDummyArg
  > const *)
{
  typedef
    ::wg::autosimulator::detail::auto_any_impl
    <
      ExprCategory,
      CapturedType,
      EnableIfDummyArg
    > const
      scopemngr_type;
  return
    *static_cast
    <
      extant_scopemngr_proxy_impl<scopemngr_type> const *
    >(::boost::addressof(scopemngr_proxy));
}

template <typename AutoAnyImplType>
extant_exit_proxy_type make_extant_exit_proxy(
  extant_scopemngr_proxy_impl<AutoAnyImplType> const & scopemngr_proxy)
{
  struct extant_exit_proxy
  {
    static void impl(
      extant_scopemngr_proxy_t scopemngr_proxy,
      bool const didthrow)
    {
      static_cast
      <
        extant_scopemngr_proxy_impl<AutoAnyImplType> const *
      >(::boost::addressof(scopemngr_proxy))->exit(didthrow);
    }
  };

  return ::boost::addressof(extant_exit_proxy::impl);
}

//TODO: to remove.
//template <typename AutoAnyImplType>
//void extant_exit_proxy_impl(
//  extant_scopemngr_proxy const * scopemngr_proxy,
//  bool const didthrow)
//{
//  static_cast
//  <
//    extant_scopemngr_proxy_impl<AutoAnyImplType> const *
//  >(scopemngr_proxy)->exit(didthrow);
//}

}
}
}

#endif /* WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_HH_ */
