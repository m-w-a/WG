#include <gtest/gtest.h>
#include <boost/config.hpp>
#include <WG/Local/LclContext.hh>
#include <WG/Local/Tests/LclContext/Utils/Utils.hh>
#include <WG/Local/Tests/LclContext/Utils/Records.hh>
#include <WG/Local/Tests/LclContext/Utils/ScopeMngrTemplate.hh>

using namespace ::wg::lclcontext::detail::test;

TEST(wg_lclcontext_adhoc, EnterSpecifiedCompletedScope)
{
  RecordKeeper records;
  SimpleScopeMngr scpmngr(ScopeManager::Id0, records);
  Record const & rcd = records.getRecordFor(ScopeManager::Id0);

  EXPECT_FALSE(rcd.didCallEnter());
  WG_LCLCONTEXT(
    with_adhoc (ref scpmngr)
      on_enter( scpmngr.enter() )
      on_exit( scpmngr.exit(scope_completed) )  )
  {
    EXPECT_TRUE(rcd.didCallEnter());
    EXPECT_FALSE(rcd.didCallExit());
    EXPECT_FALSE(rcd.wasScopeCompleted());
  }
  WG_LCLCONTEXT_END1

  EXPECT_TRUE(rcd.didCallExit());
  EXPECT_TRUE(rcd.wasScopeCompleted());

  EXPECT_TRUE(records.isEntryCallOrderCorrect());
  EXPECT_TRUE(records.isExitCallOrderCorrect());
}
