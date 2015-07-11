#include <gtest/gtest.h>
#include <WG/Local/LclContext.hh>
#include <WG/Local/Tests/Utils/Utils.hh>
#include <WG/Local/Tests/LclContext/Utils/Utils.hh>
#include <WG/Local/Tests/LclContext/Utils/Records.hh>
#include <WG/Local/Tests/LclContext/Utils/ScopeMngrTemplate.hh>

using namespace ::wg::lclcontext::detail::test;

#define WG_LOCAL_TESTS_LCLCONTEXT_MULTIPLEUSEINSAMEMACRO() \
  \
  RecordKeeper records; \
  \
  SimpleScopeMngr scpmngr(ScopeManager::Id3, records); \
  std::pair<Record const *, Result::Kind> queryRetVal = \
    records.getRecordFor(ScopeManager::Id3); \
  WG_LCLCONTEXT_EXPECT_SUCCESS(queryRetVal.second); \
  Record const & rcd = *queryRetVal.first; \
  \
  WG_LCLCONTEXT( \
    with_adhoc (ref scpmngr) \
    on_enter(scpmngr.enter();) \
    on_exit(scpmngr.exit(scope_completed);) ) \
  { \
    EXPECT_TRUE(rcd.didCallEnter()); \
    EXPECT_FALSE(rcd.didCallExit()); \
    EXPECT_FALSE(rcd.wasScopeCompleted()); \
    \
    SimpleScopeMngr scpmngr0(ScopeManager::Id0, records); \
    ByRefEntryScopeMngr scpmngr1(ScopeManager::Id1, records); \
    \
    WG_LCLCONTEXT( \
      with(scpmngr0) \
      with(scpmngr1) enter_as(ref entry1) \
      with(SimpleScopeMngr(ScopeManager::Id2, records)) ) \
    { \
      std::pair<Record const *, Result::Kind> queryRetVal; \
      \
      queryRetVal = records.getRecordFor(ScopeManager::Id0); \
      WG_LCLCONTEXT_EXPECT_SUCCESS(queryRetVal.second); \
      Record const & rcd0 = *queryRetVal.first; \
      \
      queryRetVal = records.getRecordFor(ScopeManager::Id1); \
      WG_LCLCONTEXT_EXPECT_SUCCESS(queryRetVal.second); \
      Record const & rcd1 = *queryRetVal.first; \
      \
      queryRetVal = records.getRecordFor(ScopeManager::Id2); \
      WG_LCLCONTEXT_EXPECT_SUCCESS(queryRetVal.second); \
      Record const & rcd2 = *queryRetVal.first; \
      \
      EXPECT_TRUE(rcd0.didCallEnter()); \
      EXPECT_FALSE(rcd0.didCallExit()); \
      EXPECT_FALSE(rcd0.wasScopeCompleted()); \
      \
      EXPECT_TRUE(rcd1.didCallEnter()); \
      EXPECT_FALSE(rcd1.didCallExit()); \
      EXPECT_FALSE(rcd1.wasScopeCompleted()); \
      \
      EXPECT_TRUE(rcd2.didCallEnter()); \
      EXPECT_FALSE(rcd2.didCallExit()); \
      EXPECT_FALSE(rcd2.wasScopeCompleted()); \
      \
      WG_TEST_ASSERT_ISREFERENCE(entry1, scpmngr1.EntryObj); \
      WG_TEST_ASSERT_ISNOTCONST(entry1); \
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(EmptyCntr, entry1); \
    } \
    WG_LCLCONTEXT_END3 \
    \
    std::pair<Record const *, Result::Kind> queryRetVal; \
    \
    queryRetVal = records.getRecordFor(ScopeManager::Id0); \
    WG_LCLCONTEXT_EXPECT_SUCCESS(queryRetVal.second); \
    Record const & rcd0 = *queryRetVal.first; \
    \
    queryRetVal = records.getRecordFor(ScopeManager::Id1); \
    WG_LCLCONTEXT_EXPECT_SUCCESS(queryRetVal.second); \
    Record const & rcd1 = *queryRetVal.first; \
    \
    queryRetVal = records.getRecordFor(ScopeManager::Id2); \
    WG_LCLCONTEXT_EXPECT_SUCCESS(queryRetVal.second); \
    Record const & rcd2 = *queryRetVal.first; \
    \
    EXPECT_TRUE(rcd0.didCallExit()); \
    EXPECT_TRUE(rcd0.wasScopeCompleted()); \
    \
    EXPECT_TRUE(rcd1.didCallExit()); \
    EXPECT_TRUE(rcd1.wasScopeCompleted()); \
    \
    EXPECT_TRUE(rcd2.didCallExit()); \
    EXPECT_TRUE(rcd2.wasScopeCompleted()); \
  } \
  WG_LCLCONTEXT_END1 \
  \
  EXPECT_TRUE(rcd.didCallExit()); \
  EXPECT_TRUE(rcd.wasScopeCompleted()); \
  \
  EXPECT_TRUE(records.isEntryCallOrderCorrect()); \
  EXPECT_TRUE(records.isExitCallOrderCorrect());

TEST(wg_lclcontext_multipleuseinsamemacro, Test)
{
  WG_LOCAL_TESTS_LCLCONTEXT_MULTIPLEUSEINSAMEMACRO()
}
