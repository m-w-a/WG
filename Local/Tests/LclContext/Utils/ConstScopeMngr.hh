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
    m_Recorder(records)
  {
    m_Recorder.makeRecordFor(m_Id);
  }

  void enter() const
  {
    m_Recorder.markEntryCallFor(m_Id);
  }

  void exit(bool const scope_completed) const
  {
    m_Recorder.markExitCallFor(m_Id);
    if(scope_completed)
    {
      m_Recorder.markScopeCompletionFor(m_Id);
    }
  }

private:
  ScopeManager::Id const m_Id;
  mutable IRecorder m_Recorder;
};

}
}
}
}


#endif /* WG_LCLCONTEXT_DETAIL_TEST_CONSTSCOPEMNGR_HH_ */
