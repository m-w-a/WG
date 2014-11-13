#ifndef WG_LCLCONTEXT_DETAIL_TEST_CONSTSCOPEMNGR_HH_
#define WG_LCLCONTEXT_DETAIL_TEST_CONSTSCOPEMNGR_HH_

#include <WG/Local/Tests/LclContext/Utils/Utils.hh>
#include <WG/Local/Tests/LclContext/Utils/Records.hh>

namespace wg
{
namespace lclcontext
{
namespace detail
{
namespace test
{

class ConstScopeMngr
{
public:
  explicit ConstScopeMngr(ScopeManager::Id const id, RecordKeeper & records)
  : m_Id(id),
    m_Records(records)
  {
    m_Records.makeRecordFor(m_Id);
  }

  void enter() const
  {
    m_Records.markEntryCallFor(m_Id);
  }

  void exit(bool const scope_completed) const
  {
    m_Records.markExitCallFor(m_Id);
    if(scope_completed)
    {
      m_Records.markScopeCompletionFor(m_Id);
    }
  }

private:
  ScopeManager::Id const m_Id;
  RecordKeeper & m_Records;
};

}
}
}
}


#endif /* WG_LCLCONTEXT_DETAIL_TEST_CONSTSCOPEMNGR_HH_ */
