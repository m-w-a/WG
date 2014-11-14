#include <gtest/gtest.h>
#include <boost/config.hpp>
#include <WG/Local/LclContext.hh>
#include <WG/Local/Tests/Utils/Utils.hh>
#include <WG/Local/Tests/LclContext/Utils/Utils.hh>
#include <WG/Local/Tests/LclContext/Utils/Records.hh>
#include <WG/Local/Tests/LclContext/Utils/ScopeMngrTemplate.hh>

using namespace ::wg::lclcontext::detail::test;

TEST(wg_lclcontext_extant_capturedentry, ExplicitByValue)
{
  RecordKeeper records;
  ByRefEntryScopeMngr scpmngr(ScopeManager::Id0, records);
  Record const & rcd = records.getRecordFor(ScopeManager::Id0);

  EXPECT_FALSE(rcd.didCallEnter());
  WG_LCLCONTEXT( with(scpmngr) enter_as(type(EmptyCntr) entryObj) )
  {
    EXPECT_TRUE(rcd.didCallEnter());
    EXPECT_FALSE(rcd.didCallExit());
    EXPECT_FALSE(rcd.wasScopeCompleted());

    WG_TEST_ASSERT_ISNOTREFERENCE(entryObj, scpmngr.EntryObj);
    WG_TEST_ASSERT_ISNOTCONST(entryObj);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(EmptyCntr, entryObj);
  }
  WG_LCLCONTEXT_END1

  EXPECT_TRUE(rcd.didCallExit());
  EXPECT_TRUE(rcd.wasScopeCompleted());

  EXPECT_TRUE(records.isEntryCallOrderCorrect());
  EXPECT_TRUE(records.isExitCallOrderCorrect());
}

TEST(wg_lclcontext_extant_capturedentry, ExplicitByRef)
{
  RecordKeeper records;
  ByRefEntryScopeMngr scpmngr(ScopeManager::Id0, records);
  Record const & rcd = records.getRecordFor(ScopeManager::Id0);

  EXPECT_FALSE(rcd.didCallEnter());
  WG_LCLCONTEXT( with(scpmngr) enter_as(type(EmptyCntr &) entryObj) )
  {
    EXPECT_TRUE(rcd.didCallEnter());
    EXPECT_FALSE(rcd.didCallExit());
    EXPECT_FALSE(rcd.wasScopeCompleted());

    WG_TEST_ASSERT_ISREFERENCE(entryObj, scpmngr.EntryObj);
    WG_TEST_ASSERT_ISNOTCONST(entryObj);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(EmptyCntr, entryObj);
  }
  WG_LCLCONTEXT_END1

  EXPECT_TRUE(rcd.didCallExit());
  EXPECT_TRUE(rcd.wasScopeCompleted());

  EXPECT_TRUE(records.isEntryCallOrderCorrect());
  EXPECT_TRUE(records.isExitCallOrderCorrect());
}

TEST(wg_lclcontext_extant_capturedentry, ImplicitByValue)
{
  RecordKeeper records;
  ByRefEntryScopeMngr scpmngr(ScopeManager::Id0, records);
  Record const & rcd = records.getRecordFor(ScopeManager::Id0);

  EXPECT_FALSE(rcd.didCallEnter());
  WG_LCLCONTEXT( with(scpmngr) enter_as(entryObj) )
  {
    EXPECT_TRUE(rcd.didCallEnter());
    EXPECT_FALSE(rcd.didCallExit());
    EXPECT_FALSE(rcd.wasScopeCompleted());

    WG_TEST_ASSERT_ISNOTREFERENCE(entryObj, scpmngr.EntryObj);
    WG_TEST_ASSERT_ISNOTCONST(entryObj);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(EmptyCntr, entryObj);
  }
  WG_LCLCONTEXT_END1

  EXPECT_TRUE(rcd.didCallExit());
  EXPECT_TRUE(rcd.wasScopeCompleted());

  EXPECT_TRUE(records.isEntryCallOrderCorrect());
  EXPECT_TRUE(records.isExitCallOrderCorrect());
}

TEST(wg_lclcontext_extant_capturedentry, ImplicitByConstValue)
{
  RecordKeeper records;
  ByRefEntryScopeMngr scpmngr(ScopeManager::Id0, records);
  Record const & rcd = records.getRecordFor(ScopeManager::Id0);

  EXPECT_FALSE(rcd.didCallEnter());
  WG_LCLCONTEXT( with(scpmngr) enter_as(const entryObj) )
  {
    EXPECT_TRUE(rcd.didCallEnter());
    EXPECT_FALSE(rcd.didCallExit());
    EXPECT_FALSE(rcd.wasScopeCompleted());

    WG_TEST_ASSERT_ISNOTREFERENCE(entryObj, scpmngr.EntryObj);
    WG_TEST_ASSERT_ISCONST(entryObj);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(EmptyCntr, entryObj);
  }
  WG_LCLCONTEXT_END1

  EXPECT_TRUE(rcd.didCallExit());
  EXPECT_TRUE(rcd.wasScopeCompleted());

  EXPECT_TRUE(records.isEntryCallOrderCorrect());
  EXPECT_TRUE(records.isExitCallOrderCorrect());
}

TEST(wg_lclcontext_extant_capturedentry, ImplicitByRef)
{
  RecordKeeper records;
  ByRefEntryScopeMngr scpmngr(ScopeManager::Id0, records);
  Record const & rcd = records.getRecordFor(ScopeManager::Id0);

  EXPECT_FALSE(rcd.didCallEnter());
  WG_LCLCONTEXT( with(scpmngr) enter_as(ref entryObj) )
  {
    EXPECT_TRUE(rcd.didCallEnter());
    EXPECT_FALSE(rcd.didCallExit());
    EXPECT_FALSE(rcd.wasScopeCompleted());

    WG_TEST_ASSERT_ISREFERENCE(entryObj, scpmngr.EntryObj);
    WG_TEST_ASSERT_ISNOTCONST(entryObj);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(EmptyCntr, entryObj);
  }
  WG_LCLCONTEXT_END1

  EXPECT_TRUE(rcd.didCallExit());
  EXPECT_TRUE(rcd.wasScopeCompleted());

  EXPECT_TRUE(records.isEntryCallOrderCorrect());
  EXPECT_TRUE(records.isExitCallOrderCorrect());
}

TEST(wg_lclcontext_extant_capturedentry, ImplicitByConstRef)
{
  RecordKeeper records;
  ByRefEntryScopeMngr scpmngr(ScopeManager::Id0, records);
  Record const & rcd = records.getRecordFor(ScopeManager::Id0);

  EXPECT_FALSE(rcd.didCallEnter());
  WG_LCLCONTEXT( with(scpmngr) enter_as(const ref entryObj) )
  {
    EXPECT_TRUE(rcd.didCallEnter());
    EXPECT_FALSE(rcd.didCallExit());
    EXPECT_FALSE(rcd.wasScopeCompleted());

    WG_TEST_ASSERT_ISREFERENCE(entryObj, scpmngr.EntryObj);
    WG_TEST_ASSERT_ISCONST(entryObj);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(EmptyCntr, entryObj);
  }
  WG_LCLCONTEXT_END1

  EXPECT_TRUE(rcd.didCallExit());
  EXPECT_TRUE(rcd.wasScopeCompleted());

  EXPECT_TRUE(records.isEntryCallOrderCorrect());
  EXPECT_TRUE(records.isExitCallOrderCorrect());
}

namespace
{

template <typename T>
struct InTemplateExplicitByValue
{
  static void run()
  {
    RecordKeeper records;
    T scpmngr(ScopeManager::Id0, records);
    Record const & rcd = records.getRecordFor(ScopeManager::Id0);

    EXPECT_FALSE(rcd.didCallEnter());
    WG_LCLCONTEXT_TPL( with(scpmngr) enter_as(type(EmptyCntr) entryObj) )
    {
      EXPECT_TRUE(rcd.didCallEnter());
      EXPECT_FALSE(rcd.didCallExit());
      EXPECT_FALSE(rcd.wasScopeCompleted());

      WG_TEST_ASSERT_ISNOTREFERENCE(entryObj, scpmngr.EntryObj);
      WG_TEST_ASSERT_ISNOTCONST_TPL(entryObj);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(EmptyCntr, entryObj);
    }
    WG_LCLCONTEXT_END1

    EXPECT_TRUE(rcd.didCallExit());
    EXPECT_TRUE(rcd.wasScopeCompleted());

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }
};

}
TEST(wg_lclcontext_extant_capturedentry, InTemplateExplicitByValue)
{
  InTemplateExplicitByValue<ByRefEntryScopeMngr>::run();
}

namespace
{

template <typename T>
struct InTemplateImplicitByConstRef
{
  static void run()
  {
    RecordKeeper records;
    T scpmngr(ScopeManager::Id0, records);
    Record const & rcd = records.getRecordFor(ScopeManager::Id0);

    EXPECT_FALSE(rcd.didCallEnter());
    WG_LCLCONTEXT_TPL( with(scpmngr) enter_as(const ref entryObj) )
    {
      EXPECT_TRUE(rcd.didCallEnter());
      EXPECT_FALSE(rcd.didCallExit());
      EXPECT_FALSE(rcd.wasScopeCompleted());

      WG_TEST_ASSERT_ISREFERENCE(entryObj, scpmngr.EntryObj);
      WG_TEST_ASSERT_ISCONST_TPL(entryObj);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(EmptyCntr, entryObj);
    }
    WG_LCLCONTEXT_END1

    EXPECT_TRUE(rcd.didCallExit());
    EXPECT_TRUE(rcd.wasScopeCompleted());

    EXPECT_TRUE(records.isEntryCallOrderCorrect());
    EXPECT_TRUE(records.isExitCallOrderCorrect());
  }
};

}
TEST(wg_lclcontext_extant_capturedentry, InTemplateImplicitByConstRef)
{
  InTemplateImplicitByConstRef<ByRefEntryScopeMngr>::run();
}

TEST(wg_lclcontext_extant_capturedentry, ExplicitMultiDclnContext)
{
  RecordKeeper records;
  ByRefEntryScopeMngr scpmngr0(ScopeManager::Id0, records);
  ByRefEntryScopeMngr scpmngr1(ScopeManager::Id1, records);

  WG_LCLCONTEXT(
    with(scpmngr0) enter_as(type(EmptyCntr) entryObj0)
    with(scpmngr1) enter_as(type(EmptyCntr &) entryObj1)
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

    WG_TEST_ASSERT_ISNOTREFERENCE(entryObj0, scpmngr0.EntryObj);
    WG_TEST_ASSERT_ISNOTCONST(entryObj0);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(EmptyCntr, entryObj0);

    WG_TEST_ASSERT_ISREFERENCE(entryObj1, scpmngr1.EntryObj);
    WG_TEST_ASSERT_ISNOTCONST(entryObj1);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(EmptyCntr, entryObj1);
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

TEST(wg_lclcontext_extant_capturedentry, ImplicitMultiDclnContext)
{
  RecordKeeper records;
  ByRefEntryScopeMngr scpmngr0(ScopeManager::Id0, records);
  ByRefEntryScopeMngr scpmngr1(ScopeManager::Id1, records);

  WG_LCLCONTEXT(
    with(scpmngr0) enter_as(entryObj0)
    with(scpmngr1) enter_as(ref entryObj1)
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

    WG_TEST_ASSERT_ISNOTREFERENCE(entryObj0, scpmngr0.EntryObj);
    WG_TEST_ASSERT_ISNOTCONST(entryObj0);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(EmptyCntr, entryObj0);

    WG_TEST_ASSERT_ISREFERENCE(entryObj1, scpmngr1.EntryObj);
    WG_TEST_ASSERT_ISNOTCONST(entryObj1);
    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(EmptyCntr, entryObj1);
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
