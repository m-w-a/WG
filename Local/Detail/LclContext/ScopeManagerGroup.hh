#ifndef WG_LCLCONTEXT_DETAIL_SCOPEMANAGERGROUP_HH_
#define WG_LCLCONTEXT_DETAIL_SCOPEMANAGERGROUP_HH_

namespace wg
{
namespace lclcontext
{
namespace detail
{

struct scope_mngr_group;
typedef scope_mngr_group const & scope_mngr_group_t;

struct scope_mngr_group
{
  scope_mngr_group()
  : m_did_throw(false)
  {}

  void mark_exception()
  {
    m_did_throw = true;
  }

  bool did_throw() const
  {
    return m_did_throw;
  }

protected:
  template <typename T>
  void finalize(T & member)
  {
    member.on_exit(m_did_throw);
  }

private:
  bool m_did_throw;
};

}
}
}

#endif /* WG_LCLCONTEXT_DETAIL_SCOPEMANAGERGROUP_HH_ */
