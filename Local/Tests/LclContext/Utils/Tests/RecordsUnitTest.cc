#include <gtest/gtest.h>
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

  EXPECT_EQ(Result::Failure, records.getRecordFor(ScopeManager::Id0).second);
  EXPECT_EQ(Result::Failure, recorder.markEntryCallFor(ScopeManager::Id0));
  EXPECT_EQ(Result::Failure, recorder.markExitCallFor(ScopeManager::Id0));
  EXPECT_EQ(Result::Failure, recorder.markScopeCompletionFor(ScopeManager::Id0));

  EXPECT_TRUE(records.isEntryCallOrderCorrect());
  EXPECT_TRUE(records.isExitCallOrderCorrect());
}

TEST(wg_lclcontext_utils_RecordKeeper, VerifyMutators)
{
  RecordKeeper records;
  detail::IRecorder recorder(records);

  recorder.makeRecordFor(ScopeManager::Id0);
  EXPECT_EQ(Result::Failure, recorder.makeRecordFor(ScopeManager::Id0));
  EXPECT_EQ(Result::Failure, recorder.makeRecordFor(ScopeManager::Id0, 1));

  EXPECT_EQ(Result::Failure, records.getRecordFor(ScopeManager::Id1).second);
  std::pair<Record const *, Result::Kind> rcdResult =
    records.getRecordFor(ScopeManager::Id0);
  EXPECT_EQ(Result::Success, rcdResult.second);
  Record const & rcd = *rcdResult.first;
  EXPECT_EQ(ScopeManager::Id0, rcd.id());

  EXPECT_EQ(Result::Failure, recorder.markEntryCallFor(ScopeManager::Id1));
  EXPECT_EQ(Result::Success, recorder.markEntryCallFor(ScopeManager::Id0));
  EXPECT_TRUE(rcd.didCallEnter());

  EXPECT_EQ(Result::Failure, recorder.markEntryWillThrowFor(ScopeManager::Id1));
  EXPECT_EQ(Result::Success, recorder.markEntryWillThrowFor(ScopeManager::Id0));

  EXPECT_EQ(Result::Failure, recorder.markExitCallFor(ScopeManager::Id1));
  EXPECT_EQ(Result::Success, recorder.markExitCallFor(ScopeManager::Id0));
  EXPECT_TRUE(rcd.didCallExit());

  EXPECT_EQ(Result::Failure, recorder.markScopeCompletionFor(ScopeManager::Id1));
  EXPECT_EQ(Result::Success, recorder.markScopeCompletionFor(ScopeManager::Id0));
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

  WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id0) );

  WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id0) );

  WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id0) );

  EXPECT_TRUE(records.isEntryCallOrderCorrect());
  EXPECT_TRUE(records.isExitCallOrderCorrect());
}

TEST(wg_lclcontext_utils_RecordKeeper, VerifyCallOrderForThreeRecords)
{
  // VerifyCorrectCallOrder
  {
    RecordKeeper records;
    detail::IRecorder recorder(records);

    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id0) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id1) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id2) );

    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id0) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id1) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id2) );

    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id2) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id1) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id0) );

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }

  // VerifyCorrectCallOrderForPositionalInsertion
  {
    RecordKeeper records;
    detail::IRecorder recorder(records);

    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id0) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id2) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id1, 1) );

    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id0) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id1) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id2) );

    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id2) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id1) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id0) );

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }

  // VerifyIncorrectEntryCallOrder
  {
    // CallOrder021
    {
      RecordKeeper records;
      detail::IRecorder recorder(records);

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id0) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id1) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id2) );

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id0) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id2) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id1) );

      EXPECT_FALSE(records.isEntryCallOrderCorrect());
    }

    // CallOrder102
    {
      RecordKeeper records;
      detail::IRecorder recorder(records);

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id0) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id1) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id2) );

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id1) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id0) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id2) );

      EXPECT_FALSE(records.isEntryCallOrderCorrect());
    }

    // CallOrder120
    {
      RecordKeeper records;
      detail::IRecorder recorder(records);

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id0) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id1) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id2) );

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id1) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id2) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id0) );

      EXPECT_FALSE(records.isEntryCallOrderCorrect());
    }

    // CallOrder201
    {
      RecordKeeper records;
      detail::IRecorder recorder(records);

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id0) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id1) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id2) );

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id2) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id0) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id1) );

      EXPECT_FALSE(records.isEntryCallOrderCorrect());
    }

    // CallOrder210
    {
      RecordKeeper records;
      detail::IRecorder recorder(records);

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id0) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id1) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id2) );

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id2) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id1) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id0) );

      EXPECT_FALSE(records.isEntryCallOrderCorrect());
    }
  }

  // VerifyIncorrectExitCallOrder
  {
    // CallOrder201
    {
      RecordKeeper records;
      detail::IRecorder recorder(records);

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id0) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id1) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id2) );

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id0) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id1) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id2) );

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id2) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id0) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id1) );

      EXPECT_TRUE(records.isEntryCallOrderCorrect());
      EXPECT_FALSE(records.isExitCallOrderCorrect());
    }

    // CallOrder120
    {
      RecordKeeper records;
      detail::IRecorder recorder(records);

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id0) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id1) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id2) );

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id0) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id1) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id2) );

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id1) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id2) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id0) );

      EXPECT_TRUE(records.isEntryCallOrderCorrect());
      EXPECT_FALSE(records.isExitCallOrderCorrect());
    }

    // CallOrder102
    {
      RecordKeeper records;
      detail::IRecorder recorder(records);

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id0) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id1) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id2) );

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id0) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id1) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id2) );

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id1) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id0) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id2) );

      EXPECT_TRUE(records.isEntryCallOrderCorrect());
      EXPECT_FALSE(records.isExitCallOrderCorrect());
    }

    // CallOrder021
    {
      RecordKeeper records;
      detail::IRecorder recorder(records);

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id0) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id1) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id2) );

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id0) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id1) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id2) );

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id0) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id2) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id1) );

      EXPECT_TRUE(records.isEntryCallOrderCorrect());
      EXPECT_FALSE(records.isExitCallOrderCorrect());
    }

    // CallOrder012
    {
      RecordKeeper records;
      detail::IRecorder recorder(records);

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id0) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id1) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id2) );

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id0) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id1) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id2) );

      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id0) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id1) );
      WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id2) );

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

    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id0) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id1) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id2) );

    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id0) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id1) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryWillThrowFor(ScopeManager::Id1) );

    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id1) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id0) );

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }

  // VerifyIncorrectEntryCallOrder
  {
    RecordKeeper records;
    detail::IRecorder recorder(records);

    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id0) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id1) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryWillThrowFor(ScopeManager::Id1) );

    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id1) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id0) );

    EXPECT_FALSE(records.isEntryCallOrderCorrect());
  }

  // VerifyIncorrectExitCallOrder
  {
    RecordKeeper records;
    detail::IRecorder recorder(records);

    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id0) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id1) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.makeRecordFor(ScopeManager::Id2) );

    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id0) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryCallFor(ScopeManager::Id1) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markEntryWillThrowFor(ScopeManager::Id1) );

    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id0) );
    WG_LCLCONTEXT_EXPECT_SUCCESS( recorder.markExitCallFor(ScopeManager::Id1) );

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_FALSE(records.isExitCallOrderCorrect());
  }
}
