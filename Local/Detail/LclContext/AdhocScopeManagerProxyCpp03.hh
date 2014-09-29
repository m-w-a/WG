#ifndef WG_LCLCONTEXT_DETAIL_ADHOCSCOPEMANAGERPROXYCPP03_HH_
#define WG_LCLCONTEXT_DETAIL_ADHOCSCOPEMANAGERPROXYCPP03_HH_

namespace wg
{
namespace lclcontext
{
namespace detail
{
namespace cpp03
{

class adhoc_scope_manager_proxy
{
public:
  typedef void (*callback_type)(adhoc_scope_manager_proxy *, bool);

public:
  explicit adhoc_scope_manager_proxy(callback_type callback)
  : m_callback(callback)
  {}

  void on_exit(bool const exception_active)
  {
    m_callback(this, exception_active);
  }

private:
  callback_type m_callback;
};

}
}
}
}


#endif /* WG_LCLCONTEXT_DETAIL_ADHOCSCOPEMANAGERPROXYCPP03_HH_ */
