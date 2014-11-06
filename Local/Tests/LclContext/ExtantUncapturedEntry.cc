#include <gtest/gtest.h>
#include <WG/Local/LclContext.hh>
#include <WG/Local/Tests/LclContext/Utils.hh>

using namespace ::wg::lclcontext::detail::test;

TEST(wg_lclcontext_extant_uncapturedentry, CompletedSTEPScope)
{
  RecordKeeper records;
  SimpleScopeMngr scopemngr(ScopeManager::Id0, records);
  Record & scopemngrRecord = records.back();

  EXPECT_FALSE(scopemngrRecord.didCallEnter());
  WG_LCLCONTEXT( with(scopemngr) )
  {
    EXPECT_TRUE(scopemngrRecord.didCallEnter());
    EXPECT_FALSE(scopemngrRecord.didCallExit());
    EXPECT_FALSE(scopemngrRecord.wasScopeCompleted());
  }
  WG_LCLCONTEXT_END1

  EXPECT_TRUE(scopemngrRecord.didCallExit());
  EXPECT_TRUE(scopemngrRecord.wasScopeCompleted());
}

TEST(wg_lclcontext_extant_uncapturedentry, GoToInducedIncompletedScope)
{
  RecordKeeper records;
  SimpleScopeMngr scopemngr(ScopeManager::Id0, records);
  Record & scopemngrRecord = records.back();

  EXPECT_FALSE(scopemngrRecord.didCallEnter());
  WG_LCLCONTEXT( with(scopemngr) )
  {
    EXPECT_TRUE(scopemngrRecord.didCallEnter());
    EXPECT_FALSE(scopemngrRecord.didCallExit());
    EXPECT_FALSE(scopemngrRecord.wasScopeCompleted());

    goto label1;
  }
  WG_LCLCONTEXT_END1

  label1:

  EXPECT_TRUE(scopemngrRecord.didCallExit());
  EXPECT_FALSE(scopemngrRecord.wasScopeCompleted());
}

namespace
{

void returnInducedIncompletedScope(
  SimpleScopeMngr & scopemngr,
  Record & scopemngrRecord)
{
  EXPECT_FALSE(scopemngrRecord.didCallEnter());
  WG_LCLCONTEXT( with(scopemngr) )
  {
    EXPECT_TRUE(scopemngrRecord.didCallEnter());
    EXPECT_FALSE(scopemngrRecord.didCallExit());
    EXPECT_FALSE(scopemngrRecord.wasScopeCompleted());

    return;
  }
  WG_LCLCONTEXT_END1
}

}

TEST(wg_lclcontext_extant_uncapturedentry, ReturnInducedIncompletedScope)
{
  RecordKeeper records;
  SimpleScopeMngr scopemngr(ScopeManager::Id0, records);
  Record & scopemngrRecord = records.back();

  returnInducedIncompletedScope(scopemngr, scopemngrRecord);

  EXPECT_TRUE(scopemngrRecord.didCallExit());
  EXPECT_FALSE(scopemngrRecord.wasScopeCompleted());
}

TEST(wg_lclcontext_extant_uncapturedentry, BreakInducedIncompletedScope)
{
  RecordKeeper records;
  SimpleScopeMngr scopemngr(ScopeManager::Id0, records);
  Record & scopemngrRecord = records.back();

  int counter = 1;
  while(counter > 0)
  {
    --counter;

    EXPECT_FALSE(scopemngrRecord.didCallEnter());
    WG_LCLCONTEXT( with(scopemngr) )
    {
      EXPECT_TRUE(scopemngrRecord.didCallEnter());
      EXPECT_FALSE(scopemngrRecord.didCallExit());
      EXPECT_FALSE(scopemngrRecord.wasScopeCompleted());

      break;
    }
    WG_LCLCONTEXT_END1
  }

  EXPECT_EQ(0, counter);

  EXPECT_TRUE(scopemngrRecord.didCallExit());
  EXPECT_FALSE(scopemngrRecord.wasScopeCompleted());
}

TEST(wg_lclcontext_extant_uncapturedentry, ContinueInducedIncompletedScope)
{
  RecordKeeper records;
  SimpleScopeMngr scopemngr(ScopeManager::Id0, records);
  Record & scopemngrRecord = records.back();

  int counter = 1;
  while(counter > 0)
  {
    --counter;

    EXPECT_FALSE(scopemngrRecord.didCallEnter());
    WG_LCLCONTEXT( with(scopemngr) )
    {
      EXPECT_TRUE(scopemngrRecord.didCallEnter());
      EXPECT_FALSE(scopemngrRecord.didCallExit());
      EXPECT_FALSE(scopemngrRecord.wasScopeCompleted());

      continue;
    }
    WG_LCLCONTEXT_END1
  }

  EXPECT_EQ(0, counter);

  EXPECT_TRUE(scopemngrRecord.didCallExit());
  EXPECT_FALSE(scopemngrRecord.wasScopeCompleted());
}

#ifndef BOOST_NO_EXCEPTIONS
TEST(wg_lclcontext_extant_uncapturedentry, ThrowInducedIncompletedScope)
{
  RecordKeeper records;
  SimpleScopeMngr scopemngr(ScopeManager::Id0, records);
  Record & scopemngrRecord = records.back();

  bool didthrow = false;
  try
  {
    EXPECT_FALSE(scopemngrRecord.didCallEnter());
    WG_LCLCONTEXT( with(scopemngr) )
    {
      EXPECT_TRUE(scopemngrRecord.didCallEnter());
      EXPECT_FALSE(scopemngrRecord.didCallExit());
      EXPECT_FALSE(scopemngrRecord.wasScopeCompleted());

      throw -1;
    }
    WG_LCLCONTEXT_END1
  }
  catch(...)
  {
    didthrow = true;
  }

  EXPECT_TRUE(didthrow);

  EXPECT_TRUE(scopemngrRecord.didCallExit());
  EXPECT_FALSE(scopemngrRecord.wasScopeCompleted());
}
#endif
