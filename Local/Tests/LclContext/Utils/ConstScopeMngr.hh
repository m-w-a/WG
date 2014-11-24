#ifndef WG_LCLCONTEXT_DETAIL_TEST_CONSTSCOPEMNGR_HH_
#define WG_LCLCONTEXT_DETAIL_TEST_CONSTSCOPEMNGR_HH_

#include <WG/Local/Tests/LclContext/Utils/Utils.hh>
#include <WG/Local/Tests/LclContext/Utils/Records.hh>
#include <WG/Local/Tests/LclContext/Utils/Detail/IRecorder.hh>

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
    WG_LCLCONTEXT_EXPECT_SUCCESS( m_Recorder.makeRecordFor(m_Id) );
  }

  void enter() const
  {
    WG_LCLCONTEXT_EXPECT_SUCCESS( m_Recorder.markEntryCallFor(m_Id) );
  }

  void exit(bool const scope_completed) const
  {
    WG_LCLCONTEXT_EXPECT_SUCCESS( m_Recorder.markExitCallFor(m_Id) );
    if(scope_completed)
    {
      WG_LCLCONTEXT_EXPECT_SUCCESS( m_Recorder.markScopeCompletionFor(m_Id) );
    }
  }

private:
  ScopeManager::Id const m_Id;
  mutable detail::IRecorder m_Recorder;
};

}
}
}
}


#endif /* WG_LCLCONTEXT_DETAIL_TEST_CONSTSCOPEMNGR_HH_ */
