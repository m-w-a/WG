#ifndef WG_LCLCONTEXT_DETAIL_ADHOCSCOPEMANAGERPROXYCPP11_HH_
#define WG_LCLCONTEXT_DETAIL_ADHOCSCOPEMANAGERPROXYCPP11_HH_

namespace wg
{
namespace lclcontext
{
namespace detail
{
namespace cpp11
{

template <typename Derived>
class adhoc_scope_manager_proxy
{
public:
  void on_exit(bool const exception_active)
  {
    static_cast<Derived *>(this)->on_exit(exception_active);
  }
};

}
}
}
}

#endif /* WG_LCLCONTEXT_DETAIL_ADHOCSCOPEMANAGERPROXYCPP11_HH_ */
