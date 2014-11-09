#include <gtest/gtest.h>
#include <WG/Local/LclContext.hh>
#include <WG/Local/Tests/LclContext/Utils.hh>

using namespace ::wg::lclcontext::detail::test;

TEST(wg_lclcontext_extant_uncapturedentry, CompletedScope)
{
  RecordKeeper records;
  SimpleScopeMngr scpmngr(ScopeManager::Id0, records);
  Record const & rcd = records.getRecordFor(ScopeManager::Id0);

  EXPECT_FALSE(rcd.didCallEnter());
  WG_LCLCONTEXT( with(scpmngr) )
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

TEST(wg_lclcontext_extant_uncapturedentry, GoToInducedIncompletedScope)
{
  RecordKeeper records;
  SimpleScopeMngr scpmngr(ScopeManager::Id0, records);
  Record const & rcd = records.getRecordFor(ScopeManager::Id0);

  EXPECT_FALSE(rcd.didCallEnter());
  WG_LCLCONTEXT( with(scpmngr) )
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

namespace
{

void returnInducedIncompletedScope(
  SimpleScopeMngr & scpmngr,
  Record const & rcd)
{
  EXPECT_FALSE(rcd.didCallEnter());
  WG_LCLCONTEXT( with(scpmngr) )
  {
    EXPECT_TRUE(rcd.didCallEnter());
    EXPECT_FALSE(rcd.didCallExit());
    EXPECT_FALSE(rcd.wasScopeCompleted());

    return;
  }
  WG_LCLCONTEXT_END1
}

}

TEST(wg_lclcontext_extant_uncapturedentry, ReturnInducedIncompletedScope)
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

TEST(wg_lclcontext_extant_uncapturedentry, BreakInducedIncompletedScope)
{
  RecordKeeper records;
  SimpleScopeMngr scpmngr(ScopeManager::Id0, records);
  Record const & rcd = records.getRecordFor(ScopeManager::Id0);

  int counter = 1;
  while(counter > 0)
  {
    --counter;

    EXPECT_FALSE(rcd.didCallEnter());
    WG_LCLCONTEXT( with(scpmngr) )
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

TEST(wg_lclcontext_extant_uncapturedentry, ContinueInducedIncompletedScope)
{
  RecordKeeper records;
  SimpleScopeMngr scpmngr(ScopeManager::Id0, records);
  Record const & rcd = records.getRecordFor(ScopeManager::Id0);

  int counter = 1;
  while(counter > 0)
  {
    --counter;

    EXPECT_FALSE(rcd.didCallEnter());
    WG_LCLCONTEXT( with(scpmngr) )
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
TEST(wg_lclcontext_extant_uncapturedentry, ThrowInducedIncompletedScope)
{
  RecordKeeper records;
  SimpleScopeMngr scpmngr(ScopeManager::Id0, records);
  Record const & rcd = records.getRecordFor(ScopeManager::Id0);

  bool didthrow = false;
  try
  {
    EXPECT_FALSE(rcd.didCallEnter());
    WG_LCLCONTEXT( with(scpmngr) )
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
#endif
