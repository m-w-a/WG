#include <gtest/gtest.h>
#include <boost/config.hpp>
#include <WG/Local/LclContext.hh>
#include <WG/Local/Tests/LclContext/Utils/Utils.hh>
#include <WG/Local/Tests/LclContext/Utils/Records.hh>
#include <WG/Local/Tests/LclContext/Utils/ScopeMngrTemplate.hh>

using namespace ::wg::lclcontext::detail::test;

TEST(wg_lclcontext_adhoc, EnterAndExitSpecifiedCompletedScope)
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

namespace
{

void returnInducedIncompletedScope(
  SimpleScopeMngr & scpmngr,
  Record const & rcd)
{
  EXPECT_FALSE(rcd.didCallEnter());
  WG_LCLCONTEXT(
    with_adhoc (ref scpmngr)
      on_enter( scpmngr.enter() )
      on_exit( scpmngr.exit(scope_completed) )  )
  {
    EXPECT_TRUE(rcd.didCallEnter());
    EXPECT_FALSE(rcd.didCallExit());
    EXPECT_FALSE(rcd.wasScopeCompleted());

    return;
  }
  WG_LCLCONTEXT_END1
}

}
TEST(wg_lclcontext_adhoc, EnterAndExitSpecifiedIncompletedScope)
{
  // GoToInducedIncompletedScope
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

      goto label1;
    }
    WG_LCLCONTEXT_END1

    label1:

    EXPECT_TRUE(rcd.didCallExit());
    EXPECT_FALSE(rcd.wasScopeCompleted());

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }

  // ReturnInducedIncompletedScope
  {
    RecordKeeper records;
    SimpleScopeMngr scpmngr(ScopeManager::Id0, records);
    Record const & rcd = records.getRecordFor(ScopeManager::Id0);

    returnInducedIncompletedScope(scpmngr, rcd);

    EXPECT_TRUE(rcd.didCallExit());
    EXPECT_FALSE(rcd.wasScopeCompleted());

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }

  // BreakInducedIncompletedScope
  {
    RecordKeeper records;
    SimpleScopeMngr scpmngr(ScopeManager::Id0, records);
    Record const & rcd = records.getRecordFor(ScopeManager::Id0);

    int counter = 1;
    while(counter > 0)
    {
      --counter;

      EXPECT_FALSE(rcd.didCallEnter());
      WG_LCLCONTEXT(
        with_adhoc (ref scpmngr)
          on_enter( scpmngr.enter() )
          on_exit( scpmngr.exit(scope_completed) ) )
      {
        EXPECT_TRUE(rcd.didCallEnter());
        EXPECT_FALSE(rcd.didCallExit());
        EXPECT_FALSE(rcd.wasScopeCompleted());

        break;
      }
      WG_LCLCONTEXT_END1
    }

    EXPECT_EQ(0, counter);

    EXPECT_TRUE(rcd.didCallExit());
    EXPECT_FALSE(rcd.wasScopeCompleted());

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }

  // ContinueInducedIncompletedScope
  {
    RecordKeeper records;
    SimpleScopeMngr scpmngr(ScopeManager::Id0, records);
    Record const & rcd = records.getRecordFor(ScopeManager::Id0);

    int counter = 1;
    while(counter > 0)
    {
      --counter;

      EXPECT_FALSE(rcd.didCallEnter());
      WG_LCLCONTEXT(
        with_adhoc (ref scpmngr)
          on_enter( scpmngr.enter() )
          on_exit( scpmngr.exit(scope_completed) ) )
      {
        EXPECT_TRUE(rcd.didCallEnter());
        EXPECT_FALSE(rcd.didCallExit());
        EXPECT_FALSE(rcd.wasScopeCompleted());

        continue;
      }
      WG_LCLCONTEXT_END1
    }

    EXPECT_EQ(0, counter);

    EXPECT_TRUE(rcd.didCallExit());
    EXPECT_FALSE(rcd.wasScopeCompleted());

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }

#ifndef BOOST_NO_EXCEPTIONS
  // ThrowInducedIncompletedScope
  {
    RecordKeeper records;
    SimpleScopeMngr scpmngr(ScopeManager::Id0, records);
    Record const & rcd = records.getRecordFor(ScopeManager::Id0);

    struct Exception1 {};

    bool didthrow = false;
    try
    {
      EXPECT_FALSE(rcd.didCallEnter());
      WG_LCLCONTEXT(
        with_adhoc (ref scpmngr)
          on_enter( scpmngr.enter() )
          on_exit( scpmngr.exit(scope_completed) ) )
      {
        EXPECT_TRUE(rcd.didCallEnter());
        EXPECT_FALSE(rcd.didCallExit());
        EXPECT_FALSE(rcd.wasScopeCompleted());

        throw Exception1();
      }
      WG_LCLCONTEXT_END1
    }
    catch(...)
    {
      didthrow = true;
    }

    EXPECT_TRUE(didthrow);

    EXPECT_TRUE(rcd.didCallExit());
    EXPECT_FALSE(rcd.wasScopeCompleted());

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }
#endif // BOOST_NO_EXCEPTIONS
}
