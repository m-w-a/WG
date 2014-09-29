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
  : m_didthrow(false)
  {}

  void mark_exception() const
  {
    m_didthrow = true;
  }

  bool did_throw() const
  {
    return m_didthrow;
  }

protected:
  template <typename T>
  void finalize(T & member)
  {
    member.exit(m_didthrow);
  }

private:
  mutable bool m_didthrow;
};

}
}
}

#endif /* WG_LCLCONTEXT_DETAIL_SCOPEMANAGERGROUP_HH_ */
