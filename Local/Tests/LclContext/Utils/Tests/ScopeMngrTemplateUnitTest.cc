#include <gtest/gtest.h>
#include <stdexcept>
#include <WG/Local/Tests/LclContext/Utils/Utils.hh>
#include <WG/Local/Tests/LclContext/Utils/Records.hh>
#include <WG/Local/Tests/LclContext/Utils/ScopeMngrTemplate.hh>

using namespace ::wg::lclcontext::detail::test;

TEST(wg_lclcontext_utils_SimpleScopeMngr, VerifyStartState)
{
  RecordKeeper records;
  SimpleScopeMngr scopemngr(ScopeManager::Id0, records);

  std::pair<Record const *, Result::Kind> queryRetVal =
    records.getRecordFor(ScopeManager::Id0);
  WG_LCLCONTEXT_EXPECT_SUCCESS(queryRetVal.second);
  Record const & rcd = *queryRetVal.first;

  EXPECT_FALSE(rcd.didCallEnter());
  EXPECT_FALSE(rcd.didCallExit());
  EXPECT_FALSE(rcd.wasScopeCompleted());
  EXPECT_FALSE(records.isEntryCallOrderCorrect());
  EXPECT_TRUE(records.isExitCallOrderCorrect());
}

TEST(wg_lclcontext_utils_SimpleScopeMngr, VerifyMutatorsForOneObject)
{
  // ExitFalse
  {
    RecordKeeper records;
    SimpleScopeMngr scopemngr(ScopeManager::Id0, records);

    std::pair<Record const *, Result::Kind> queryRetVal =
      records.getRecordFor(ScopeManager::Id0);
    WG_LCLCONTEXT_EXPECT_SUCCESS(queryRetVal.second);
    Record const & rcd = *queryRetVal.first;

    scopemngr.enter();
    EXPECT_TRUE(rcd.didCallEnter());

    scopemngr.exit(false);
    EXPECT_TRUE(rcd.didCallExit());
    EXPECT_FALSE(rcd.wasScopeCompleted());

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }

  // ExitTrue
  {
    RecordKeeper records;
    SimpleScopeMngr scopemngr(ScopeManager::Id0, records);

    std::pair<Record const *, Result::Kind> queryRetVal =
      records.getRecordFor(ScopeManager::Id0);
    WG_LCLCONTEXT_EXPECT_SUCCESS(queryRetVal.second);
    Record const & rcd = *queryRetVal.first;

    scopemngr.enter();
    EXPECT_TRUE(rcd.didCallEnter());

    scopemngr.exit(true);
    EXPECT_TRUE(rcd.didCallExit());
    EXPECT_TRUE(rcd.wasScopeCompleted());

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }
}

TEST(wg_lclcontext_utils_SimpleScopeMngr, VerifyMutatorsForThreeObjects)
{
  // VerifyCorrectCallOrder
  {
    RecordKeeper records;
    SimpleScopeMngr scpmngr0(ScopeManager::Id0, records);
    SimpleScopeMngr scpmngr1(ScopeManager::Id1, records);
    SimpleScopeMngr scpmngr2(ScopeManager::Id2, records);

    std::pair<Record const *, Result::Kind> queryRetVal;

    queryRetVal = records.getRecordFor(ScopeManager::Id0);
    WG_LCLCONTEXT_EXPECT_SUCCESS(queryRetVal.second);
    Record const & rcd0 = *queryRetVal.first;

    queryRetVal = records.getRecordFor(ScopeManager::Id1);
    WG_LCLCONTEXT_EXPECT_SUCCESS(queryRetVal.second);
    Record const & rcd1 = *queryRetVal.first;

    queryRetVal = records.getRecordFor(ScopeManager::Id2);
    WG_LCLCONTEXT_EXPECT_SUCCESS(queryRetVal.second);
    Record const & rcd2 = *queryRetVal.first;

    scpmngr0.enter();
    scpmngr1.enter();
    scpmngr2.enter();

    EXPECT_TRUE(rcd0.didCallEnter());
    EXPECT_TRUE(rcd1.didCallEnter());
    EXPECT_TRUE(rcd2.didCallEnter());

    scpmngr2.exit(false);
    scpmngr1.exit(true);
    scpmngr0.exit(false);

    EXPECT_TRUE(rcd0.didCallExit());
    EXPECT_FALSE(rcd0.wasScopeCompleted());
    EXPECT_TRUE(rcd1.didCallExit());
    EXPECT_TRUE(rcd1.wasScopeCompleted());
    EXPECT_TRUE(rcd2.didCallExit());
    EXPECT_FALSE(rcd2.wasScopeCompleted());

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }

  // VerifyIncorrectEntryCallOrder
  {
    // CallOrder021
    {
      RecordKeeper records;
      SimpleScopeMngr scpmngr0(ScopeManager::Id0, records);
      SimpleScopeMngr scpmngr1(ScopeManager::Id1, records);
      SimpleScopeMngr scpmngr2(ScopeManager::Id2, records);

      scpmngr0.enter();
      scpmngr2.enter();
      scpmngr1.enter();

      EXPECT_FALSE(records.isEntryCallOrderCorrect());
    }

    // CallOrder102
    {
      RecordKeeper records;
      SimpleScopeMngr scpmngr0(ScopeManager::Id0, records);
      SimpleScopeMngr scpmngr1(ScopeManager::Id1, records);
      SimpleScopeMngr scpmngr2(ScopeManager::Id2, records);

      scpmngr1.enter();
      scpmngr0.enter();
      scpmngr2.enter();

      EXPECT_FALSE(records.isEntryCallOrderCorrect());
    }

    // CallOrder120
    {
      RecordKeeper records;
      SimpleScopeMngr scpmngr0(ScopeManager::Id0, records);
      SimpleScopeMngr scpmngr1(ScopeManager::Id1, records);
      SimpleScopeMngr scpmngr2(ScopeManager::Id2, records);

      scpmngr1.enter();
      scpmngr2.enter();
      scpmngr0.enter();

      EXPECT_FALSE(records.isEntryCallOrderCorrect());
    }

    // CallOrder201
    {
      RecordKeeper records;
      SimpleScopeMngr scpmngr0(ScopeManager::Id0, records);
      SimpleScopeMngr scpmngr1(ScopeManager::Id1, records);
      SimpleScopeMngr scpmngr2(ScopeManager::Id2, records);

      scpmngr2.enter();
      scpmngr0.enter();
      scpmngr1.enter();

      EXPECT_FALSE(records.isEntryCallOrderCorrect());
    }

    // CallOrder210
    {
      RecordKeeper records;
      SimpleScopeMngr scpmngr0(ScopeManager::Id0, records);
      SimpleScopeMngr scpmngr1(ScopeManager::Id1, records);
      SimpleScopeMngr scpmngr2(ScopeManager::Id2, records);

      scpmngr2.enter();
      scpmngr1.enter();
      scpmngr0.enter();

      EXPECT_FALSE(records.isEntryCallOrderCorrect());
    }
  }

  // VerifyIncorrectExitCallOrder
  {
    // CallOrder201
    {
      RecordKeeper records;
      SimpleScopeMngr scpmngr0(ScopeManager::Id0, records);
      SimpleScopeMngr scpmngr1(ScopeManager::Id1, records);
      SimpleScopeMngr scpmngr2(ScopeManager::Id2, records);

      scpmngr0.enter();
      scpmngr1.enter();
      scpmngr2.enter();

      scpmngr2.exit(false);
      scpmngr0.exit(true);
      scpmngr1.exit(false);

      EXPECT_TRUE(records.isEntryCallOrderCorrect());
      EXPECT_FALSE(records.isExitCallOrderCorrect());
    }

    // CallOrder120
    {
      RecordKeeper records;
      SimpleScopeMngr scpmngr0(ScopeManager::Id0, records);
      SimpleScopeMngr scpmngr1(ScopeManager::Id1, records);
      SimpleScopeMngr scpmngr2(ScopeManager::Id2, records);

      scpmngr0.enter();
      scpmngr1.enter();
      scpmngr2.enter();

      scpmngr1.exit(false);
      scpmngr2.exit(true);
      scpmngr0.exit(false);

      EXPECT_TRUE(records.isEntryCallOrderCorrect());
      EXPECT_FALSE(records.isExitCallOrderCorrect());
    }

    // CallOrder102
    {
      RecordKeeper records;
      SimpleScopeMngr scpmngr0(ScopeManager::Id0, records);
      SimpleScopeMngr scpmngr1(ScopeManager::Id1, records);
      SimpleScopeMngr scpmngr2(ScopeManager::Id2, records);

      scpmngr0.enter();
      scpmngr1.enter();
      scpmngr2.enter();

      scpmngr1.exit(false);
      scpmngr0.exit(true);
      scpmngr2.exit(false);

      EXPECT_TRUE(records.isEntryCallOrderCorrect());
      EXPECT_FALSE(records.isExitCallOrderCorrect());
    }

    // CallOrder021
    {
      RecordKeeper records;
      SimpleScopeMngr scpmngr0(ScopeManager::Id0, records);
      SimpleScopeMngr scpmngr1(ScopeManager::Id1, records);
      SimpleScopeMngr scpmngr2(ScopeManager::Id2, records);

      scpmngr0.enter();
      scpmngr1.enter();
      scpmngr2.enter();

      scpmngr0.exit(false);
      scpmngr2.exit(true);
      scpmngr1.exit(false);

      EXPECT_TRUE(records.isEntryCallOrderCorrect());
      EXPECT_FALSE(records.isExitCallOrderCorrect());
    }

    // CallOrder012
    {
      RecordKeeper records;
      SimpleScopeMngr scpmngr0(ScopeManager::Id0, records);
      SimpleScopeMngr scpmngr1(ScopeManager::Id1, records);
      SimpleScopeMngr scpmngr2(ScopeManager::Id2, records);

      scpmngr0.enter();
      scpmngr1.enter();
      scpmngr2.enter();

      scpmngr0.exit(false);
      scpmngr1.exit(true);
      scpmngr2.exit(false);

      EXPECT_TRUE(records.isEntryCallOrderCorrect());
      EXPECT_FALSE(records.isExitCallOrderCorrect());
    }
  }
}

TEST(wg_lclcontext_utils_EnterThrowsScopeMngr, VerifyEnterThrows)
{
  RecordKeeper records;
  EnterThrowsScopeMngr scpmngr(ScopeManager::Id0, records);

  std::pair<Record const *, Result::Kind> queryRetVal =
    records.getRecordFor(ScopeManager::Id0);
  WG_LCLCONTEXT_EXPECT_SUCCESS(queryRetVal.second);
  Record const & rcd = *queryRetVal.first;

  EXPECT_THROW(scpmngr.enter(), EnterException);
  EXPECT_TRUE(rcd.didCallEnter());

  scpmngr.exit(false);
  EXPECT_TRUE(rcd.didCallExit());
  EXPECT_FALSE(rcd.wasScopeCompleted());

  EXPECT_TRUE(records.isEntryCallOrderCorrect());
  EXPECT_TRUE(records.isExitCallOrderCorrect());
}

TEST(wg_lclcontext_utils_EnterThrowsScopeMngr, VerifyExitThrows)
{
  RecordKeeper records;
  ExitThrowsScopeMngr scpmngr(ScopeManager::Id0, records);

  std::pair<Record const *, Result::Kind> queryRetVal =
    records.getRecordFor(ScopeManager::Id0);
  WG_LCLCONTEXT_EXPECT_SUCCESS(queryRetVal.second);
  Record const & rcd = *queryRetVal.first;

  scpmngr.enter();
  EXPECT_TRUE(rcd.didCallEnter());

  EXPECT_THROW(scpmngr.exit(false), ExitException);
  EXPECT_TRUE(rcd.didCallExit());
  EXPECT_FALSE(rcd.wasScopeCompleted());

  EXPECT_TRUE(records.isEntryCallOrderCorrect());
  EXPECT_TRUE(records.isExitCallOrderCorrect());
}

TEST(wg_lclcontext_utils_EnterThrowsScopeMngr, VerifyEnterAndExitThrow)
{
  RecordKeeper records;
  EnterAndExitThrowScopeMngr scpmngr(ScopeManager::Id0, records);

  std::pair<Record const *, Result::Kind> queryRetVal =
    records.getRecordFor(ScopeManager::Id0);
  WG_LCLCONTEXT_EXPECT_SUCCESS(queryRetVal.second);
  Record const & rcd = *queryRetVal.first;

  EXPECT_THROW(scpmngr.enter(), EnterException);
  EXPECT_TRUE(rcd.didCallEnter());

  EXPECT_THROW(scpmngr.exit(false), ExitException);
  EXPECT_TRUE(rcd.didCallExit());
  EXPECT_FALSE(rcd.wasScopeCompleted());

  EXPECT_TRUE(records.isEntryCallOrderCorrect());
  EXPECT_TRUE(records.isExitCallOrderCorrect());
}
