#ifndef WG_LCLCONTEXT_DETAIL_NOOPSCOPEMANAGER_HH_
#define WG_LCLCONTEXT_DETAIL_NOOPSCOPEMANAGER_HH_

namespace wg
{
namespace lclcontext
{
namespace detail
{

struct noop_scope_mngr
{
  void enter() {}
  void exit(bool const) {}
};

}
}
}

#endif /* WG_LCLCONTEXT_DETAIL_NOOPSCOPEMANAGER_HH_ */
