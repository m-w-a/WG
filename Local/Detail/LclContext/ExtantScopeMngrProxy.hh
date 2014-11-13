#ifndef WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_HH_
#define WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_HH_

#include <boost/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility.hpp>
#include <WG/Local/Detail/AutoSimulator/Detail/AutoAny.hh>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_void.hpp>

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
  istpl, scopemngr_proxy, expr, rettype) \
    WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_ENTER_IMPL( \
      istpl, scopemngr_proxy, expr, rettype)

#define WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_EXIT( \
  scopemngr_proxy, expr, scope_completed) \
    WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_EXIT_IMPL( \
      scopemngr_proxy, expr, scope_completed)

#define WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_EXITPROXY( \
  scopemngr_proxy, scope_completed) \
    WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_EXITPROXY_IMPL( \
      scopemngr_proxy, scope_completed)

//####
//Impl
//####

#define WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_MAKE_IMPL( \
  expr, mutable_boolean_flag) \
    ::wg::lclcontext::detail::make_extant_scopemngr_proxy( \
      WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(expr, mutable_boolean_flag) )

#define WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_ADDTPL_0
#define WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_ADDTPL_1 template
#define WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_ADDTPL(istpl) \
  BOOST_PP_CAT(WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_ADDTPL_, istpl)

#define WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_ENTER_IMPL( \
  istpl, scopemngr_proxy, expr, rettype) \
    WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_DOWNCAST( \
      scopemngr_proxy, expr) . \
        WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_ADDTPL(istpl) enter<rettype>()

#define WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_EXIT_IMPL( \
  scopemngr_proxy, expr, scope_completed) \
    WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_DOWNCAST( \
      scopemngr_proxy, expr).exit( scope_completed )

#define WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_EXITPROXY_IMPL( \
  scopemngr_proxy, scope_completed) \
    scopemngr_proxy.exit( scope_completed )

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

typedef void (*extant_exit_proxy_type)(extant_scopemngr_proxy_t, bool const);

class extant_scopemngr_proxy
{
public:
  explicit extant_scopemngr_proxy(extant_exit_proxy_type const exit_proxy)
  : m_exitproxy(exit_proxy)
  {}

  void exit(bool const scope_completed) const
  {
    m_exitproxy(*this, scope_completed);
  }

protected:
  extant_scopemngr_proxy(extant_scopemngr_proxy const & rhs)
  : m_exitproxy(rhs.m_exitproxy)
  {}

  extant_scopemngr_proxy(BOOST_RV_REF(extant_scopemngr_proxy) rhs)
  : m_exitproxy(rhs.m_exitproxy)
  {}

private:
  BOOST_COPYABLE_AND_MOVABLE(extant_scopemngr_proxy)
private:
  // Declared and purposefully not defined.
  extant_scopemngr_proxy & operator=(extant_scopemngr_proxy);
private:
  extant_exit_proxy_type const m_exitproxy;
};

template <typename AutoAnyImplType>
class extant_scopemngr_proxy_impl : public extant_scopemngr_proxy
{
public:
  typedef AutoAnyImplType auto_any_impl_type;

public:
  // Purposefully capture by value so as to enable copy elision.
  // It is guaranteed that the parameter to this ctor will always be a rvalue.
  explicit extant_scopemngr_proxy_impl(auto_any_impl_type scopemngr)
  : extant_scopemngr_proxy(::boost::addressof(exit_proxy)),
    m_didcallexit(false),
    m_scopemngr(::boost::move(scopemngr))
  {}

  extant_scopemngr_proxy_impl(BOOST_RV_REF(extant_scopemngr_proxy_impl) rhs)
  : extant_scopemngr_proxy(::boost::move(static_cast<extant_scopemngr_proxy &>(rhs))),
    m_didcallexit(rhs.m_didcallexit),
    m_scopemngr(::boost::move(rhs.m_scopemngr))
  {}

  ~extant_scopemngr_proxy_impl() BOOST_NOEXCEPT_IF(false)
  {
    this->exit(false);
  }

  template <typename R>
  typename ::boost::enable_if< ::boost::is_void<R>, R>::type
    enter() const
  {
    (void)WG_AUTOSIMULATOR_DETAIL_AUTOANY_AUTOANYIMPL_VALUE(m_scopemngr).enter();
  }

  template <typename R>
  typename ::boost::disable_if< ::boost::is_void<R>, R>::type
    enter() const
  {
    return WG_AUTOSIMULATOR_DETAIL_AUTOANY_AUTOANYIMPL_VALUE(m_scopemngr).enter();
  }

  void exit(bool const scope_completed) const
  {
    if( ! m_didcallexit )
    {
      m_didcallexit = true;
      WG_AUTOSIMULATOR_DETAIL_AUTOANY_AUTOANYIMPL_VALUE(m_scopemngr).exit(scope_completed);
    }
  }

private:
  BOOST_COPYABLE_AND_MOVABLE(extant_scopemngr_proxy_impl)
private:
  // Declared and purposefully not defined.
  extant_scopemngr_proxy_impl & operator=(extant_scopemngr_proxy_impl);
private:
  static void exit_proxy(
    extant_scopemngr_proxy_t scopemngr_proxy,
    bool const scope_completed)
  {
    static_cast
    <
      extant_scopemngr_proxy_impl<AutoAnyImplType> const *
    >(::boost::addressof(scopemngr_proxy))->exit(scope_completed);
  }
private:
  // Objects of this type will always be accessed through a base class
  // const reference, therefore declare all members as mutable.
  mutable bool m_didcallexit;
  mutable auto_any_impl_type m_scopemngr;
};

template <typename ExprCategory, typename CapturedType, typename EnableIfDummyArg>
// Purposefully capture by value so as to enable copy elision.
// It is guaranteed that the parameter to this ctor will always be a rvalue.
extant_scopemngr_proxy_impl
<
  ::wg::autosimulator::detail::auto_any_impl
  <
    ExprCategory,
    CapturedType,
    EnableIfDummyArg
  >
>
make_extant_scopemngr_proxy(
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
  > *)
{
  typedef
    ::wg::autosimulator::detail::auto_any_impl
    <
      ExprCategory,
      CapturedType,
      EnableIfDummyArg
    >
      scopemngr_type;
  return
    *static_cast
    <
      extant_scopemngr_proxy_impl<scopemngr_type> const *
    >(::boost::addressof(scopemngr_proxy));
}

}
}
}

#endif /* WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_HH_ */
