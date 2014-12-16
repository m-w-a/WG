#include <gtest/gtest.h>
#include <WG/Local/LclContext.hh>
#include <WG/Local/Tests/Utils/Utils.hh>
#include <WG/Local/Tests/LclContext/Utils/Utils.hh>
#include <WG/Local/Tests/LclContext/Utils/Records.hh>
#include <WG/Local/Tests/LclContext/Utils/ScopeMngrTemplate.hh>

using namespace ::wg::lclcontext::detail::test;

TEST(wg_lclcontext_extantandadhoc, Combo)
{
  RecordKeeper records;

  ByRefEntryScopeMngr scpmngr0(ScopeManager::Id0, records);
  SimpleScopeMngr scpmngr1(ScopeManager::Id1, records);

  WG_LCLCONTEXT(
    with(scpmngr0) enter_as(entryObj0)
    with_adhoc (ref scpmngr1)
      on_enter( scpmngr1.enter() )
      on_exit( scpmngr1.exit(scope_completed) )
    with(SimpleScopeMngr(ScopeManager::Id2, records)) )
  {
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

    EXPECT_TRUE(rcd0.didCallEnter());
    EXPECT_FALSE(rcd0.didCallExit());
    EXPECT_FALSE(rcd0.wasScopeCompleted());

    EXPECT_TRUE(rcd1.didCallEnter());
    EXPECT_FALSE(rcd1.didCallExit());
    EXPECT_FALSE(rcd1.wasScopeCompleted());

    EXPECT_TRUE(rcd2.didCallEnter());
    EXPECT_FALSE(rcd2.didCallExit());
    EXPECT_FALSE(rcd2.wasScopeCompleted());

    WG_TEST_ASSERT_ISNOTREFERENCE(entryObj0, scpmngr0.EntryObj);
    WG_TEST_ASSERT_ISNOTCONST(entryObj0);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(EmptyCntr, entryObj0);
  }
  WG_LCLCONTEXT_END3

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

  EXPECT_TRUE(rcd0.didCallExit());
  EXPECT_TRUE(rcd0.wasScopeCompleted());

  EXPECT_TRUE(rcd1.didCallExit());
  EXPECT_TRUE(rcd1.wasScopeCompleted());

  EXPECT_TRUE(rcd2.didCallExit());
  EXPECT_TRUE(rcd2.wasScopeCompleted());

  EXPECT_TRUE(records.isEntryCallOrderCorrect());
  EXPECT_TRUE(records.isExitCallOrderCorrect());
}

namespace
{

template <typename T1, typename T2, typename T3>
struct ComboInTemplate
{
  static void run()
  {
    RecordKeeper records;

    T1 scpmngr0(ScopeManager::Id0, records);
    T2 scpmngr1(ScopeManager::Id1, records);

    WG_LCLCONTEXT_TPL(
      with(scpmngr0) enter_as(entryObj0)
      with_adhoc (ref scpmngr1)
        on_enter( scpmngr1.enter() )
        on_exit( scpmngr1.exit(scope_completed) )
      with(T3(ScopeManager::Id2, records)) )
    {
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

      EXPECT_TRUE(rcd0.didCallEnter());
      EXPECT_FALSE(rcd0.didCallExit());
      EXPECT_FALSE(rcd0.wasScopeCompleted());

      EXPECT_TRUE(rcd1.didCallEnter());
      EXPECT_FALSE(rcd1.didCallExit());
      EXPECT_FALSE(rcd1.wasScopeCompleted());

      EXPECT_TRUE(rcd2.didCallEnter());
      EXPECT_FALSE(rcd2.didCallExit());
      EXPECT_FALSE(rcd2.wasScopeCompleted());

      WG_TEST_ASSERT_ISNOTREFERENCE(entryObj0, scpmngr0.EntryObj);
      WG_TEST_ASSERT_ISNOTCONST_TPL(entryObj0);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(EmptyCntr, entryObj0);
    }
    WG_LCLCONTEXT_END3

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

    EXPECT_TRUE(rcd0.didCallExit());
    EXPECT_TRUE(rcd0.wasScopeCompleted());

    EXPECT_TRUE(rcd1.didCallExit());
    EXPECT_TRUE(rcd1.wasScopeCompleted());

    EXPECT_TRUE(rcd2.didCallExit());
    EXPECT_TRUE(rcd2.wasScopeCompleted());

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }
};

}
TEST(wg_lclcontext_extantandadhoc, ComboInTemplate)
{
  ComboInTemplate<ByRefEntryScopeMngr, SimpleScopeMngr, SimpleScopeMngr>::run();
}
