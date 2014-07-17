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
  : m_is_exception_active(false)
  {}

  void mark_exception()
  {
    m_is_exception_active = true;
  }

  bool is_exception_active() const
  {
    return m_is_exception_active;
  }

protected:
  template <typename T>
  void finalize(T & member)
  {
    member.on_exit(m_is_exception_active);
  }

private:
  bool m_is_exception_active;
};

}
}
}

#endif /* WG_LCLCONTEXT_DETAIL_SCOPEMANAGERGROUP_HH_ */
