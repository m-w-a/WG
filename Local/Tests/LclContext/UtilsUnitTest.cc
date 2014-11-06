#include <gtest/gtest.h>
#include <WG/Local/Tests/LclContext/Utils.hh>

using namespace ::wg::lclcontext::detail::test;

TEST(wg_lclcontext_utils_SimpleScopeMngr, VerifyStartState)
{
  RecordKeeper records;
  SimpleScopeMngr scopemngr(ScopeManager::Id0, records);

  Record & scopemngrState = records.back();

  EXPECT_FALSE(scopemngrState.didCallEnter());
  EXPECT_FALSE(scopemngrState.didCallExit());
  EXPECT_FALSE(scopemngrState.wasScopeCompleted());
}
