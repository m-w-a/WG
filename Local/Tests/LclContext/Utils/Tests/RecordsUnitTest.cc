#include <gtest/gtest.h>
#include <stdexcept>
#include <WG/Local/Tests/LclContext/Utils/Utils.hh>
#include <WG/Local/Tests/LclContext/Utils/Records.hh>
#include <WG/Local/Tests/LclContext/Utils/Detail/IRecorder.hh>

using namespace ::wg::lclcontext::detail::test;

TEST(wg_lclcontext_utils_Record, VerifyStartState)
{
  Record rcd(ScopeManager::Id0);

  EXPECT_EQ(ScopeManager::Id0, rcd.id());
  EXPECT_FALSE(rcd.didCallEnter());
  EXPECT_FALSE(rcd.didCallExit());
  EXPECT_FALSE(rcd.wasScopeCompleted());
}

TEST(wg_lclcontext_utils_Record, VerifyMutators)
{
  Record rcd(ScopeManager::Id0);

  rcd.markEntryCall();
  EXPECT_TRUE(rcd.didCallEnter());

  rcd.markExitCall();
  EXPECT_TRUE(rcd.didCallExit());

  rcd.markScopeCompletion();
  EXPECT_TRUE(rcd.wasScopeCompleted());
}

TEST(wg_lclcontext_utils_RecordKeeper, VerifyStartState)
{
  RecordKeeper records;
  detail::IRecorder recorder(records);

  EXPECT_THROW(records.getRecordFor(ScopeManager::Id0), std::invalid_argument);
  EXPECT_THROW(recorder.markEntryCallFor(ScopeManager::Id0), std::invalid_argument);
  EXPECT_THROW(recorder.markExitCallFor(ScopeManager::Id0), std::invalid_argument);
  EXPECT_THROW(recorder.markScopeCompletionFor(ScopeManager::Id0), std::invalid_argument);

  EXPECT_TRUE(records.isEntryCallOrderCorrect());
  EXPECT_TRUE(records.isExitCallOrderCorrect());
}

TEST(wg_lclcontext_utils_RecordKeeper, VerifyMutators)
{
  RecordKeeper records;
  detail::IRecorder recorder(records);

  recorder.makeRecordFor(ScopeManager::Id0);
  EXPECT_THROW(recorder.makeRecordFor(ScopeManager::Id0), std::invalid_argument);
  EXPECT_THROW(recorder.makeRecordFor(ScopeManager::Id0, 1), std::invalid_argument);

  EXPECT_THROW(records.getRecordFor(ScopeManager::Id1), std::invalid_argument);
  Record const & rcd = records.getRecordFor(ScopeManager::Id0);
  EXPECT_EQ(ScopeManager::Id0, rcd.id());

  EXPECT_THROW(recorder.markEntryCallFor(ScopeManager::Id1), std::invalid_argument);
  recorder.markEntryCallFor(ScopeManager::Id0);
  EXPECT_TRUE(rcd.didCallEnter());

  EXPECT_THROW(recorder.markEntryWillThrowFor(ScopeManager::Id1), std::invalid_argument);
  recorder.markEntryWillThrowFor(ScopeManager::Id0);

  EXPECT_THROW(recorder.markExitCallFor(ScopeManager::Id1), std::invalid_argument);
  recorder.markExitCallFor(ScopeManager::Id0);
  EXPECT_TRUE(rcd.didCallExit());

  EXPECT_THROW(recorder.markScopeCompletionFor(ScopeManager::Id1), std::invalid_argument);
  recorder.markScopeCompletionFor(ScopeManager::Id0);
  EXPECT_TRUE(rcd.wasScopeCompleted());
}

TEST(wg_lclcontext_utils_RecordKeeper, VerifyCallOrderForNoRecord)
{
  RecordKeeper records;

  EXPECT_TRUE(records.isEntryCallOrderCorrect());
  EXPECT_TRUE(records.isExitCallOrderCorrect());
}

TEST(wg_lclcontext_utils_RecordKeeper, VerifyCallOrderForOneRecord)
{
  RecordKeeper records;
  detail::IRecorder recorder(records);

  recorder.makeRecordFor(ScopeManager::Id0);

  recorder.markEntryCallFor(ScopeManager::Id0);

  recorder.markExitCallFor(ScopeManager::Id0);

  EXPECT_TRUE(records.isEntryCallOrderCorrect());
  EXPECT_TRUE(records.isExitCallOrderCorrect());
}

TEST(wg_lclcontext_utils_RecordKeeper, VerifyCallOrderForThreeRecords)
{
  // VerifyCorrectCallOrder
  {
    RecordKeeper records;
    detail::IRecorder recorder(records);

    recorder.makeRecordFor(ScopeManager::Id0);
    recorder.makeRecordFor(ScopeManager::Id1);
    recorder.makeRecordFor(ScopeManager::Id2);

    recorder.markEntryCallFor(ScopeManager::Id0);
    recorder.markEntryCallFor(ScopeManager::Id1);
    recorder.markEntryCallFor(ScopeManager::Id2);

    recorder.markExitCallFor(ScopeManager::Id2);
    recorder.markExitCallFor(ScopeManager::Id1);
    recorder.markExitCallFor(ScopeManager::Id0);

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }

  // VerifyCorrectCallOrderForPositionalInsertion
  {
    RecordKeeper records;
    detail::IRecorder recorder(records);

    recorder.makeRecordFor(ScopeManager::Id0);
    recorder.makeRecordFor(ScopeManager::Id2);
    recorder.makeRecordFor(ScopeManager::Id1, 1);

    recorder.markEntryCallFor(ScopeManager::Id0);
    recorder.markEntryCallFor(ScopeManager::Id1);
    recorder.markEntryCallFor(ScopeManager::Id2);

    recorder.markExitCallFor(ScopeManager::Id2);
    recorder.markExitCallFor(ScopeManager::Id1);
    recorder.markExitCallFor(ScopeManager::Id0);

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }

  // VerifyIncorrectEntryCallOrder
  {
    // CallOrder021
    {
      RecordKeeper records;
      detail::IRecorder recorder(records);

      recorder.makeRecordFor(ScopeManager::Id0);
      recorder.makeRecordFor(ScopeManager::Id1);
      recorder.makeRecordFor(ScopeManager::Id2);

      recorder.markEntryCallFor(ScopeManager::Id0);
      recorder.markEntryCallFor(ScopeManager::Id2);
      recorder.markEntryCallFor(ScopeManager::Id1);

      EXPECT_FALSE(records.isEntryCallOrderCorrect());
    }

    // CallOrder102
    {
      RecordKeeper records;
      detail::IRecorder recorder(records);

      recorder.makeRecordFor(ScopeManager::Id0);
      recorder.makeRecordFor(ScopeManager::Id1);
      recorder.makeRecordFor(ScopeManager::Id2);

      recorder.markEntryCallFor(ScopeManager::Id1);
      recorder.markEntryCallFor(ScopeManager::Id0);
      recorder.markEntryCallFor(ScopeManager::Id2);

      EXPECT_FALSE(records.isEntryCallOrderCorrect());
    }

    // CallOrder120
    {
      RecordKeeper records;
      detail::IRecorder recorder(records);

      recorder.makeRecordFor(ScopeManager::Id0);
      recorder.makeRecordFor(ScopeManager::Id1);
      recorder.makeRecordFor(ScopeManager::Id2);

      recorder.markEntryCallFor(ScopeManager::Id1);
      recorder.markEntryCallFor(ScopeManager::Id2);
      recorder.markEntryCallFor(ScopeManager::Id0);

      EXPECT_FALSE(records.isEntryCallOrderCorrect());
    }

    // CallOrder201
    {
      RecordKeeper records;
      detail::IRecorder recorder(records);

      recorder.makeRecordFor(ScopeManager::Id0);
      recorder.makeRecordFor(ScopeManager::Id1);
      recorder.makeRecordFor(ScopeManager::Id2);

      recorder.markEntryCallFor(ScopeManager::Id2);
      recorder.markEntryCallFor(ScopeManager::Id0);
      recorder.markEntryCallFor(ScopeManager::Id1);

      EXPECT_FALSE(records.isEntryCallOrderCorrect());
    }

    // CallOrder210
    {
      RecordKeeper records;
      detail::IRecorder recorder(records);

      recorder.makeRecordFor(ScopeManager::Id0);
      recorder.makeRecordFor(ScopeManager::Id1);
      recorder.makeRecordFor(ScopeManager::Id2);

      recorder.markEntryCallFor(ScopeManager::Id2);
      recorder.markEntryCallFor(ScopeManager::Id1);
      recorder.markEntryCallFor(ScopeManager::Id0);

      EXPECT_FALSE(records.isEntryCallOrderCorrect());
    }
  }

  // VerifyIncorrectExitCallOrder
  {
    // CallOrder201
    {
      RecordKeeper records;
      detail::IRecorder recorder(records);

      recorder.makeRecordFor(ScopeManager::Id0);
      recorder.makeRecordFor(ScopeManager::Id1);
      recorder.makeRecordFor(ScopeManager::Id2);

      recorder.markEntryCallFor(ScopeManager::Id0);
      recorder.markEntryCallFor(ScopeManager::Id1);
      recorder.markEntryCallFor(ScopeManager::Id2);

      recorder.markExitCallFor(ScopeManager::Id2);
      recorder.markExitCallFor(ScopeManager::Id0);
      recorder.markExitCallFor(ScopeManager::Id1);

      EXPECT_TRUE(records.isEntryCallOrderCorrect());
      EXPECT_FALSE(records.isExitCallOrderCorrect());
    }

    // CallOrder120
    {
      RecordKeeper records;
      detail::IRecorder recorder(records);

      recorder.makeRecordFor(ScopeManager::Id0);
      recorder.makeRecordFor(ScopeManager::Id1);
      recorder.makeRecordFor(ScopeManager::Id2);

      recorder.markEntryCallFor(ScopeManager::Id0);
      recorder.markEntryCallFor(ScopeManager::Id1);
      recorder.markEntryCallFor(ScopeManager::Id2);

      recorder.markExitCallFor(ScopeManager::Id1);
      recorder.markExitCallFor(ScopeManager::Id2);
      recorder.markExitCallFor(ScopeManager::Id0);

      EXPECT_TRUE(records.isEntryCallOrderCorrect());
      EXPECT_FALSE(records.isExitCallOrderCorrect());
    }

    // CallOrder102
    {
      RecordKeeper records;
      detail::IRecorder recorder(records);

      recorder.makeRecordFor(ScopeManager::Id0);
      recorder.makeRecordFor(ScopeManager::Id1);
      recorder.makeRecordFor(ScopeManager::Id2);

      recorder.markEntryCallFor(ScopeManager::Id0);
      recorder.markEntryCallFor(ScopeManager::Id1);
      recorder.markEntryCallFor(ScopeManager::Id2);

      recorder.markExitCallFor(ScopeManager::Id1);
      recorder.markExitCallFor(ScopeManager::Id0);
      recorder.markExitCallFor(ScopeManager::Id2);

      EXPECT_TRUE(records.isEntryCallOrderCorrect());
      EXPECT_FALSE(records.isExitCallOrderCorrect());
    }

    // CallOrder021
    {
      RecordKeeper records;
      detail::IRecorder recorder(records);

      recorder.makeRecordFor(ScopeManager::Id0);
      recorder.makeRecordFor(ScopeManager::Id1);
      recorder.makeRecordFor(ScopeManager::Id2);

      recorder.markEntryCallFor(ScopeManager::Id0);
      recorder.markEntryCallFor(ScopeManager::Id1);
      recorder.markEntryCallFor(ScopeManager::Id2);

      recorder.markExitCallFor(ScopeManager::Id0);
      recorder.markExitCallFor(ScopeManager::Id2);
      recorder.markExitCallFor(ScopeManager::Id1);

      EXPECT_TRUE(records.isEntryCallOrderCorrect());
      EXPECT_FALSE(records.isExitCallOrderCorrect());
    }

    // CallOrder012
    {
      RecordKeeper records;
      detail::IRecorder recorder(records);

      recorder.makeRecordFor(ScopeManager::Id0);
      recorder.makeRecordFor(ScopeManager::Id1);
      recorder.makeRecordFor(ScopeManager::Id2);

      recorder.markEntryCallFor(ScopeManager::Id0);
      recorder.markEntryCallFor(ScopeManager::Id1);
      recorder.markEntryCallFor(ScopeManager::Id2);

      recorder.markExitCallFor(ScopeManager::Id0);
      recorder.markExitCallFor(ScopeManager::Id1);
      recorder.markExitCallFor(ScopeManager::Id2);

      EXPECT_TRUE(records.isEntryCallOrderCorrect());
      EXPECT_FALSE(records.isExitCallOrderCorrect());
    }
  }
}

TEST(
  wg_lclcontext_utils_RecordKeeper,
  VerifyCallOrderForThreeRecordsInPresenceOfThrow)
{
  // VerifyCorrectCallOrder
  {
    RecordKeeper records;
    detail::IRecorder recorder(records);

    recorder.makeRecordFor(ScopeManager::Id0);
    recorder.makeRecordFor(ScopeManager::Id1);
    recorder.makeRecordFor(ScopeManager::Id2);

    recorder.markEntryCallFor(ScopeManager::Id0);
    recorder.markEntryCallFor(ScopeManager::Id1);
    recorder.markEntryWillThrowFor(ScopeManager::Id1);

    recorder.markExitCallFor(ScopeManager::Id1);
    recorder.markExitCallFor(ScopeManager::Id0);

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }

  // VerifyIncorrectEntryCallOrder
  {
    RecordKeeper records;
    detail::IRecorder recorder(records);

    recorder.makeRecordFor(ScopeManager::Id0);
    recorder.makeRecordFor(ScopeManager::Id1);
    recorder.markEntryWillThrowFor(ScopeManager::Id1);

    recorder.markEntryCallFor(ScopeManager::Id1);
    recorder.markEntryCallFor(ScopeManager::Id0);

    EXPECT_FALSE(records.isEntryCallOrderCorrect());
  }

  // VerifyIncorrectExitCallOrder
  {
    RecordKeeper records;
    detail::IRecorder recorder(records);

    recorder.makeRecordFor(ScopeManager::Id0);
    recorder.makeRecordFor(ScopeManager::Id1);
    recorder.makeRecordFor(ScopeManager::Id2);

    recorder.markEntryCallFor(ScopeManager::Id0);
    recorder.markEntryCallFor(ScopeManager::Id1);
    recorder.markEntryWillThrowFor(ScopeManager::Id1);

    recorder.markExitCallFor(ScopeManager::Id0);
    recorder.markExitCallFor(ScopeManager::Id1);

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_FALSE(records.isExitCallOrderCorrect());
  }
}
