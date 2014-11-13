#include <gtest/gtest.h>
#include <boost/config.hpp>
#include <WG/Local/LclContext.hh>
#include <WG/Local/Tests/LclContext/Utils/Utils.hh>
#include <WG/Local/Tests/LclContext/Utils/Records.hh>
#include <WG/Local/Tests/LclContext/Utils/ScopeMngrTemplate.hh>
#include <WG/Local/Tests/LclContext/Utils/ConstScopeMngr.hh>

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

  struct Exception1 {};

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

TEST(wg_lclcontext_extant_uncapturedentry, MultiScopeMngrCompletedScope)
{
  RecordKeeper records;
  SimpleScopeMngr scpmngr0(ScopeManager::Id0, records);
  SimpleScopeMngr scpmngr1(ScopeManager::Id1, records);

  WG_LCLCONTEXT(
    with(scpmngr0)
    with(scpmngr1)
    with(SimpleScopeMngr(ScopeManager::Id2, records)) )
  {
    Record const & rcd0 = records.getRecordFor(ScopeManager::Id0);
    Record const & rcd1 = records.getRecordFor(ScopeManager::Id1);
    Record const & rcd2 = records.getRecordFor(ScopeManager::Id2);

    EXPECT_TRUE(rcd0.didCallEnter());
    EXPECT_FALSE(rcd0.didCallExit());
    EXPECT_FALSE(rcd0.wasScopeCompleted());

    EXPECT_TRUE(rcd1.didCallEnter());
    EXPECT_FALSE(rcd1.didCallExit());
    EXPECT_FALSE(rcd1.wasScopeCompleted());

    EXPECT_TRUE(rcd2.didCallEnter());
    EXPECT_FALSE(rcd2.didCallExit());
    EXPECT_FALSE(rcd2.wasScopeCompleted());
  }
  WG_LCLCONTEXT_END3

  Record const & rcd0 = records.getRecordFor(ScopeManager::Id0);
  Record const & rcd1 = records.getRecordFor(ScopeManager::Id1);
  Record const & rcd2 = records.getRecordFor(ScopeManager::Id2);

  EXPECT_TRUE(rcd0.didCallExit());
  EXPECT_TRUE(rcd0.wasScopeCompleted());

  EXPECT_TRUE(rcd1.didCallExit());
  EXPECT_TRUE(rcd1.wasScopeCompleted());

  EXPECT_TRUE(rcd2.didCallExit());
  EXPECT_TRUE(rcd2.wasScopeCompleted());

  EXPECT_TRUE(records.isEntryCallOrderCorrect());
  EXPECT_TRUE(records.isExitCallOrderCorrect());
}

TEST(wg_lclcontext_extant_uncapturedentry, MultiScopeMngrIncompletedScope)
{
  RecordKeeper records;
  SimpleScopeMngr scpmngr0(ScopeManager::Id0, records);
  SimpleScopeMngr scpmngr1(ScopeManager::Id1, records);

  WG_LCLCONTEXT(
    with(scpmngr0)
    with(scpmngr1)
    with(SimpleScopeMngr(ScopeManager::Id2, records)) )
  {
    Record const & rcd0 = records.getRecordFor(ScopeManager::Id0);
    Record const & rcd1 = records.getRecordFor(ScopeManager::Id1);
    Record const & rcd2 = records.getRecordFor(ScopeManager::Id2);

    EXPECT_TRUE(rcd0.didCallEnter());
    EXPECT_FALSE(rcd0.didCallExit());
    EXPECT_FALSE(rcd0.wasScopeCompleted());

    EXPECT_TRUE(rcd1.didCallEnter());
    EXPECT_FALSE(rcd1.didCallExit());
    EXPECT_FALSE(rcd1.wasScopeCompleted());

    EXPECT_TRUE(rcd2.didCallEnter());
    EXPECT_FALSE(rcd2.didCallExit());
    EXPECT_FALSE(rcd2.wasScopeCompleted());

    goto label1;
  }
  WG_LCLCONTEXT_END3

  label1:

  Record const & rcd0 = records.getRecordFor(ScopeManager::Id0);
  Record const & rcd1 = records.getRecordFor(ScopeManager::Id1);
  Record const & rcd2 = records.getRecordFor(ScopeManager::Id2);

  EXPECT_TRUE(rcd0.didCallExit());
  EXPECT_FALSE(rcd0.wasScopeCompleted());

  EXPECT_TRUE(rcd1.didCallExit());
  EXPECT_FALSE(rcd1.wasScopeCompleted());

  EXPECT_TRUE(rcd2.didCallExit());
  EXPECT_FALSE(rcd2.wasScopeCompleted());

  EXPECT_TRUE(records.isEntryCallOrderCorrect());
  EXPECT_TRUE(records.isExitCallOrderCorrect());
}

TEST(wg_lclcontext_extant_uncapturedentry, NestedCompletedScope)
{
  RecordKeeper records;

  SimpleScopeMngr scpmngr(ScopeManager::Id3, records);
  Record const & rcd = records.getRecordFor(ScopeManager::Id3);

  WG_LCLCONTEXT( with(scpmngr) )
  {
    EXPECT_TRUE(rcd.didCallEnter());
    EXPECT_FALSE(rcd.didCallExit());
    EXPECT_FALSE(rcd.wasScopeCompleted());

    SimpleScopeMngr scpmngr0(ScopeManager::Id0, records);
    SimpleScopeMngr scpmngr1(ScopeManager::Id1, records);

    WG_LCLCONTEXT(
      with(scpmngr0)
      with(scpmngr1)
      with(SimpleScopeMngr(ScopeManager::Id2, records)) )
    {
      Record const & rcd0 = records.getRecordFor(ScopeManager::Id0);
      Record const & rcd1 = records.getRecordFor(ScopeManager::Id1);
      Record const & rcd2 = records.getRecordFor(ScopeManager::Id2);

      EXPECT_TRUE(rcd0.didCallEnter());
      EXPECT_FALSE(rcd0.didCallExit());
      EXPECT_FALSE(rcd0.wasScopeCompleted());

      EXPECT_TRUE(rcd1.didCallEnter());
      EXPECT_FALSE(rcd1.didCallExit());
      EXPECT_FALSE(rcd1.wasScopeCompleted());

      EXPECT_TRUE(rcd2.didCallEnter());
      EXPECT_FALSE(rcd2.didCallExit());
      EXPECT_FALSE(rcd2.wasScopeCompleted());
    }
    WG_LCLCONTEXT_END3

    Record const & rcd0 = records.getRecordFor(ScopeManager::Id0);
    Record const & rcd1 = records.getRecordFor(ScopeManager::Id1);
    Record const & rcd2 = records.getRecordFor(ScopeManager::Id2);

    EXPECT_TRUE(rcd0.didCallExit());
    EXPECT_TRUE(rcd0.wasScopeCompleted());

    EXPECT_TRUE(rcd1.didCallExit());
    EXPECT_TRUE(rcd1.wasScopeCompleted());

    EXPECT_TRUE(rcd2.didCallExit());
    EXPECT_TRUE(rcd2.wasScopeCompleted());
  }
  WG_LCLCONTEXT_END1

  EXPECT_TRUE(rcd.didCallExit());
  EXPECT_TRUE(rcd.wasScopeCompleted());

  EXPECT_TRUE(records.isEntryCallOrderCorrect());
  EXPECT_TRUE(records.isExitCallOrderCorrect());
}

TEST(wg_lclcontext_extant_uncapturedentry, NestedPartiallyCompletedScope)
{
  RecordKeeper records;

  SimpleScopeMngr scpmngr(ScopeManager::Id3, records);
  Record const & rcd = records.getRecordFor(ScopeManager::Id3);

  WG_LCLCONTEXT( with(scpmngr) )
  {
    EXPECT_TRUE(rcd.didCallEnter());
    EXPECT_FALSE(rcd.didCallExit());
    EXPECT_FALSE(rcd.wasScopeCompleted());

    SimpleScopeMngr scpmngr0(ScopeManager::Id0, records);
    SimpleScopeMngr scpmngr1(ScopeManager::Id1, records);

    WG_LCLCONTEXT(
      with(scpmngr0)
      with(scpmngr1)
      with(SimpleScopeMngr(ScopeManager::Id2, records)) )
    {
      Record const & rcd0 = records.getRecordFor(ScopeManager::Id0);
      Record const & rcd1 = records.getRecordFor(ScopeManager::Id1);
      Record const & rcd2 = records.getRecordFor(ScopeManager::Id2);

      EXPECT_TRUE(rcd0.didCallEnter());
      EXPECT_FALSE(rcd0.didCallExit());
      EXPECT_FALSE(rcd0.wasScopeCompleted());

      EXPECT_TRUE(rcd1.didCallEnter());
      EXPECT_FALSE(rcd1.didCallExit());
      EXPECT_FALSE(rcd1.wasScopeCompleted());

      EXPECT_TRUE(rcd2.didCallEnter());
      EXPECT_FALSE(rcd2.didCallExit());
      EXPECT_FALSE(rcd2.wasScopeCompleted());

      goto label1;
    }
    WG_LCLCONTEXT_END3

    label1:

    Record const & rcd0 = records.getRecordFor(ScopeManager::Id0);
    Record const & rcd1 = records.getRecordFor(ScopeManager::Id1);
    Record const & rcd2 = records.getRecordFor(ScopeManager::Id2);

    EXPECT_TRUE(rcd0.didCallExit());
    EXPECT_FALSE(rcd0.wasScopeCompleted());

    EXPECT_TRUE(rcd1.didCallExit());
    EXPECT_FALSE(rcd1.wasScopeCompleted());

    EXPECT_TRUE(rcd2.didCallExit());
    EXPECT_FALSE(rcd2.wasScopeCompleted());
  }
  WG_LCLCONTEXT_END1

  EXPECT_TRUE(rcd.didCallExit());
  EXPECT_TRUE(rcd.wasScopeCompleted());

  EXPECT_TRUE(records.isEntryCallOrderCorrect());
  EXPECT_TRUE(records.isExitCallOrderCorrect());
}

TEST(wg_lclcontext_extant_uncapturedentry, NestedIncompletedScope)
{
  RecordKeeper records;

  SimpleScopeMngr scpmngr(ScopeManager::Id3, records);
  Record const & rcd = records.getRecordFor(ScopeManager::Id3);

  WG_LCLCONTEXT( with(scpmngr) )
  {
    EXPECT_TRUE(rcd.didCallEnter());
    EXPECT_FALSE(rcd.didCallExit());
    EXPECT_FALSE(rcd.wasScopeCompleted());

    SimpleScopeMngr scpmngr0(ScopeManager::Id0, records);
    SimpleScopeMngr scpmngr1(ScopeManager::Id1, records);

    WG_LCLCONTEXT(
      with(scpmngr0)
      with(scpmngr1)
      with(SimpleScopeMngr(ScopeManager::Id2, records)) )
    {
      Record const & rcd0 = records.getRecordFor(ScopeManager::Id0);
      Record const & rcd1 = records.getRecordFor(ScopeManager::Id1);
      Record const & rcd2 = records.getRecordFor(ScopeManager::Id2);

      EXPECT_TRUE(rcd0.didCallEnter());
      EXPECT_FALSE(rcd0.didCallExit());
      EXPECT_FALSE(rcd0.wasScopeCompleted());

      EXPECT_TRUE(rcd1.didCallEnter());
      EXPECT_FALSE(rcd1.didCallExit());
      EXPECT_FALSE(rcd1.wasScopeCompleted());

      EXPECT_TRUE(rcd2.didCallEnter());
      EXPECT_FALSE(rcd2.didCallExit());
      EXPECT_FALSE(rcd2.wasScopeCompleted());

      goto label1;
    }
    WG_LCLCONTEXT_END3

    label1:

    Record const & rcd0 = records.getRecordFor(ScopeManager::Id0);
    Record const & rcd1 = records.getRecordFor(ScopeManager::Id1);
    Record const & rcd2 = records.getRecordFor(ScopeManager::Id2);

    EXPECT_TRUE(rcd0.didCallExit());
    EXPECT_FALSE(rcd0.wasScopeCompleted());

    EXPECT_TRUE(rcd1.didCallExit());
    EXPECT_FALSE(rcd1.wasScopeCompleted());

    EXPECT_TRUE(rcd2.didCallExit());
    EXPECT_FALSE(rcd2.wasScopeCompleted());

    goto label2;
  }
  WG_LCLCONTEXT_END1

  label2:

  EXPECT_TRUE(rcd.didCallExit());
  EXPECT_FALSE(rcd.wasScopeCompleted());

  EXPECT_TRUE(records.isEntryCallOrderCorrect());
  EXPECT_TRUE(records.isExitCallOrderCorrect());
}

#ifndef BOOST_NO_EXCEPTIONS

TEST(wg_lclcontext_extant_uncapturedentry, EnterThrows)
{
  // OneDclnContextOneScopeMngrThrows
  {
    RecordKeeper records;
    EnterThrowsScopeMngr scpmngr(ScopeManager::Id0, records);
    Record const & rcd = records.getRecordFor(ScopeManager::Id0);

    bool didEnterThrow = false;
    try
    {
      EXPECT_FALSE(rcd.didCallEnter());
      WG_LCLCONTEXT( with(scpmngr) )
      {
        ADD_FAILURE() << "Unreachable code executed.";
      }
      WG_LCLCONTEXT_END1
    }
    catch(EnterException const &)
    {
      didEnterThrow = true;
    }

    EXPECT_TRUE(didEnterThrow);

    EXPECT_TRUE(rcd.didCallEnter());
    EXPECT_TRUE(rcd.didCallExit());
    EXPECT_FALSE(rcd.wasScopeCompleted());

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }

  // MultiDclnContextOneScopeMngrThrows
  {
    RecordKeeper records;
    SimpleScopeMngr scpmngr0(ScopeManager::Id0, records);
    SimpleScopeMngr scpmngr2(ScopeManager::Id2, records);

    bool didEnterThrow = false;
    try
    {
      WG_LCLCONTEXT(
        with(scpmngr0)
        with(EnterThrowsScopeMngr(ScopeManager::Id1, records, 1))
        with(scpmngr2) )
      {
        ADD_FAILURE() << "Unreachable code executed.";
      }
      WG_LCLCONTEXT_END3
    }
    catch(EnterException const &)
    {
      didEnterThrow = true;
    }

    EXPECT_TRUE(didEnterThrow);

    Record const & rcd0 = records.getRecordFor(ScopeManager::Id0);
    Record const & rcd1 = records.getRecordFor(ScopeManager::Id1);
    Record const & rcd2 = records.getRecordFor(ScopeManager::Id2);

    EXPECT_TRUE(rcd0.didCallEnter());
    EXPECT_TRUE(rcd0.didCallExit());
    EXPECT_FALSE(rcd0.wasScopeCompleted());

    EXPECT_TRUE(rcd1.didCallEnter());
    EXPECT_TRUE(rcd1.didCallExit());
    EXPECT_FALSE(rcd1.wasScopeCompleted());

    EXPECT_FALSE(rcd2.didCallEnter());
    EXPECT_FALSE(rcd2.didCallExit());
    EXPECT_FALSE(rcd2.wasScopeCompleted());

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }

  // MultiDclnContextMultiScopeMngrThrow
  {
    RecordKeeper records;
    EnterThrowsScopeMngr scpmngr0(ScopeManager::Id0, records);
    EnterThrowsScopeMngr scpmngr2(ScopeManager::Id2, records);

    bool didEnterThrow = false;
    try
    {
      WG_LCLCONTEXT(
        with(scpmngr0)
        with(SimpleScopeMngr(ScopeManager::Id1, records, 1))
        with(scpmngr2) )
      {
        ADD_FAILURE() << "Unreachable code executed.";
      }
      WG_LCLCONTEXT_END3
    }
    catch(EnterException const &)
    {
      didEnterThrow = true;
    }

    EXPECT_TRUE(didEnterThrow);

    Record const & rcd0 = records.getRecordFor(ScopeManager::Id0);
    EXPECT_THROW(records.getRecordFor(ScopeManager::Id1), std::invalid_argument);
    Record const & rcd2 = records.getRecordFor(ScopeManager::Id2);

    EXPECT_TRUE(rcd0.didCallEnter());
    EXPECT_TRUE(rcd0.didCallExit());
    EXPECT_FALSE(rcd0.wasScopeCompleted());

    EXPECT_FALSE(rcd2.didCallEnter());
    EXPECT_FALSE(rcd2.didCallExit());
    EXPECT_FALSE(rcd2.wasScopeCompleted());

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }
}

TEST(wg_lclcontext_extant_uncapturedentry, ExitThrows)
{
  // OneDclnContextOneScopeMngrThrows
  {
    RecordKeeper records;
    ExitThrowsScopeMngr scpmngr(ScopeManager::Id0, records);
    Record const & rcd = records.getRecordFor(ScopeManager::Id0);

    bool didExitThrow = false;
    try
    {
      EXPECT_FALSE(rcd.didCallEnter());
      WG_LCLCONTEXT( with(scpmngr) )
      {
        EXPECT_TRUE(rcd.didCallEnter());
        EXPECT_FALSE(rcd.didCallExit());
        EXPECT_FALSE(rcd.wasScopeCompleted());
      }
      WG_LCLCONTEXT_END1;
    }
    catch(ExitException const &)
    {
      didExitThrow = true;
    }

    EXPECT_TRUE(didExitThrow);

    EXPECT_TRUE(rcd.didCallEnter());
    EXPECT_TRUE(rcd.didCallExit());
    EXPECT_TRUE(rcd.wasScopeCompleted());

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }

  // MultiDclnContextOneScopeMngrThrows
  {
    RecordKeeper records;
    SimpleScopeMngr scpmngr0(ScopeManager::Id0, records);
    SimpleScopeMngr scpmngr2(ScopeManager::Id2, records);

    bool didExitThrow = false;
    try
    {
      WG_LCLCONTEXT(
        with(scpmngr0)
        with(ExitThrowsScopeMngr(ScopeManager::Id1, records, 1))
        with(scpmngr2) )
      {
        Record const & rcd0 = records.getRecordFor(ScopeManager::Id0);
        Record const & rcd1 = records.getRecordFor(ScopeManager::Id1);
        Record const & rcd2 = records.getRecordFor(ScopeManager::Id2);

        EXPECT_TRUE(rcd0.didCallEnter());
        EXPECT_FALSE(rcd0.didCallExit());
        EXPECT_FALSE(rcd0.wasScopeCompleted());

        EXPECT_TRUE(rcd1.didCallEnter());
        EXPECT_FALSE(rcd1.didCallExit());
        EXPECT_FALSE(rcd1.wasScopeCompleted());

        EXPECT_TRUE(rcd2.didCallEnter());
        EXPECT_FALSE(rcd2.didCallExit());
        EXPECT_FALSE(rcd2.wasScopeCompleted());
      }
      WG_LCLCONTEXT_END3
    }
    catch(ExitException const &)
    {
      didExitThrow = true;
    }

    EXPECT_TRUE(didExitThrow);

    Record const & rcd0 = records.getRecordFor(ScopeManager::Id0);
    Record const & rcd1 = records.getRecordFor(ScopeManager::Id1);
    Record const & rcd2 = records.getRecordFor(ScopeManager::Id2);

    EXPECT_TRUE(rcd0.didCallExit());
    EXPECT_TRUE(rcd0.wasScopeCompleted());

    EXPECT_TRUE(rcd1.didCallExit());
    EXPECT_TRUE(rcd1.wasScopeCompleted());

    EXPECT_TRUE(rcd2.didCallExit());
    EXPECT_TRUE(rcd2.wasScopeCompleted());

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }

  // MultiDclnContextMultiScopeMngrThrow
  {
    RecordKeeper records;
    ExitThrowsScopeMngr scpmngr0(ScopeManager::Id0, records);
    ExitThrowsScopeMngr scpmngr2(ScopeManager::Id2, records);

    bool didExitThrow = false;
    try
    {
      WG_LCLCONTEXT(
        with(scpmngr0)
        with(SimpleScopeMngr(ScopeManager::Id1, records, 1))
        with(scpmngr2) )
      {
        Record const & rcd0 = records.getRecordFor(ScopeManager::Id0);
        Record const & rcd1 = records.getRecordFor(ScopeManager::Id1);
        Record const & rcd2 = records.getRecordFor(ScopeManager::Id2);

        EXPECT_TRUE(rcd0.didCallEnter());
        EXPECT_FALSE(rcd0.didCallExit());
        EXPECT_FALSE(rcd0.wasScopeCompleted());

        EXPECT_TRUE(rcd1.didCallEnter());
        EXPECT_FALSE(rcd1.didCallExit());
        EXPECT_FALSE(rcd1.wasScopeCompleted());

        EXPECT_TRUE(rcd2.didCallEnter());
        EXPECT_FALSE(rcd2.didCallExit());
        EXPECT_FALSE(rcd2.wasScopeCompleted());
      }
      WG_LCLCONTEXT_END3
    }
    catch(ExitException const &)
    {
      didExitThrow = true;
    }

    EXPECT_TRUE(didExitThrow);

    Record const & rcd0 = records.getRecordFor(ScopeManager::Id0);
    Record const & rcd1 = records.getRecordFor(ScopeManager::Id1);
    Record const & rcd2 = records.getRecordFor(ScopeManager::Id2);

    EXPECT_TRUE(rcd0.didCallExit());
    EXPECT_TRUE(rcd0.wasScopeCompleted());

    EXPECT_TRUE(rcd1.didCallExit());
    EXPECT_TRUE(rcd1.wasScopeCompleted());

    EXPECT_TRUE(rcd2.didCallExit());
    EXPECT_TRUE(rcd2.wasScopeCompleted());

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }

  // NestedThrow
  {
    RecordKeeper records;

    SimpleScopeMngr scpmngr(ScopeManager::Id3, records);
    Record const & rcd = records.getRecordFor(ScopeManager::Id3);

    bool didExitThrow = false;
    try
    {
      WG_LCLCONTEXT( with(scpmngr) )
      {
        EXPECT_TRUE(rcd.didCallEnter());
        EXPECT_FALSE(rcd.didCallExit());
        EXPECT_FALSE(rcd.wasScopeCompleted());

        WG_LCLCONTEXT(
          with(ExitThrowsScopeMngr(ScopeManager::Id2, records)) )
        {
          Record const & rcd2 = records.getRecordFor(ScopeManager::Id2);

          EXPECT_TRUE(rcd2.didCallEnter());
          EXPECT_FALSE(rcd2.didCallExit());
          EXPECT_FALSE(rcd2.wasScopeCompleted());
        }
        WG_LCLCONTEXT_END1
      }
      WG_LCLCONTEXT_END1
    }
    catch(ExitException const &)
    {
      didExitThrow = true;
    }

    EXPECT_TRUE(didExitThrow);

    EXPECT_TRUE(rcd.didCallExit());
    EXPECT_FALSE(rcd.wasScopeCompleted());

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }
}

TEST(wg_lclcontext_extant_uncapturedentry, EnterAndExitThrow)
{
  // OneDclnContextOneScopeMngrThrows
  {
    RecordKeeper records;
    EnterAndExitThrowScopeMngr scpmngr(ScopeManager::Id0, records);
    Record const & rcd = records.getRecordFor(ScopeManager::Id0);

    bool didExitThrow = false;
    try
    {
      EXPECT_FALSE(rcd.didCallEnter());
      WG_LCLCONTEXT( with(scpmngr) )
      {
        ADD_FAILURE() << "Unreachable code executed.";
      }
      WG_LCLCONTEXT_END1;
    }
    catch(ExitException const &)
    {
      didExitThrow = true;
    }

    EXPECT_TRUE(didExitThrow);

    EXPECT_TRUE(rcd.didCallEnter());
    EXPECT_TRUE(rcd.didCallExit());
    EXPECT_FALSE(rcd.wasScopeCompleted());

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }

  // MultiDclnContextOneScopeMngrThrows
  {
    RecordKeeper records;
    SimpleScopeMngr scpmngr0(ScopeManager::Id0, records);
    SimpleScopeMngr scpmngr2(ScopeManager::Id2, records);

    bool didExitThrow = false;
    try
    {
      WG_LCLCONTEXT(
        with(scpmngr0)
        with(EnterAndExitThrowScopeMngr(ScopeManager::Id1, records, 1))
        with(scpmngr2) )
      {
        ADD_FAILURE() << "Unreachable code executed.";
      }
      WG_LCLCONTEXT_END3
    }
    catch(ExitException const &)
    {
      didExitThrow = true;
    }

    EXPECT_TRUE(didExitThrow);

    Record const & rcd0 = records.getRecordFor(ScopeManager::Id0);
    Record const & rcd1 = records.getRecordFor(ScopeManager::Id1);
    Record const & rcd2 = records.getRecordFor(ScopeManager::Id2);

    EXPECT_TRUE(rcd0.didCallEnter());
    EXPECT_TRUE(rcd0.didCallExit());
    EXPECT_FALSE(rcd0.wasScopeCompleted());

    EXPECT_TRUE(rcd1.didCallEnter());
    EXPECT_TRUE(rcd1.didCallExit());
    EXPECT_FALSE(rcd1.wasScopeCompleted());

    EXPECT_FALSE(rcd2.didCallEnter());
    EXPECT_FALSE(rcd2.didCallExit());
    EXPECT_FALSE(rcd2.wasScopeCompleted());

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }

  // MultiDclnContextMultiScopeMngrThrow
  {
    RecordKeeper records;
    EnterAndExitThrowScopeMngr scpmngr0(ScopeManager::Id0, records);
    EnterAndExitThrowScopeMngr scpmngr2(ScopeManager::Id2, records);

    bool didExitThrow = false;
    try
    {
      WG_LCLCONTEXT(
        with(scpmngr0)
        with(SimpleScopeMngr(ScopeManager::Id1, records, 1))
        with(scpmngr2) )
      {
        ADD_FAILURE() << "Unreachable code executed.";
      }
      WG_LCLCONTEXT_END3
    }
    catch(ExitException const &)
    {
      didExitThrow = true;
    }

    EXPECT_TRUE(didExitThrow);

    Record const & rcd0 = records.getRecordFor(ScopeManager::Id0);
    EXPECT_THROW(records.getRecordFor(ScopeManager::Id1), std::invalid_argument);
    Record const & rcd2 = records.getRecordFor(ScopeManager::Id2);

    EXPECT_TRUE(rcd0.didCallEnter());
    EXPECT_TRUE(rcd0.didCallExit());
    EXPECT_FALSE(rcd0.wasScopeCompleted());

    EXPECT_FALSE(rcd2.didCallEnter());
    EXPECT_FALSE(rcd2.didCallExit());
    EXPECT_FALSE(rcd2.wasScopeCompleted());

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }
}

TEST(wg_lclcontext_extant_uncapturedentry, ConstScopeMngr)
{
  RecordKeeper records;
  ConstScopeMngr const scpmngr(ScopeManager::Id0, records);
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

#endif // BOOST_NO_EXCEPTIONS
