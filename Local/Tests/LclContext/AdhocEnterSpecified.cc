#include <gtest/gtest.h>
#include <boost/config.hpp>
#include <WG/Local/LclContext.hh>

TEST(wg_lclcontext_adhoc, EnterSpecifiedCompletedScope)
{
  bool didCallEnter = false;
  bool wasScopeCompleted = false;

  WG_LCLCONTEXT(
    with_adhoc (ref didCallEnter)
      on_enter( didCallEnter = true )  )
  {
    EXPECT_TRUE(didCallEnter);
    wasScopeCompleted = true;
  }
  WG_LCLCONTEXT_END1

  EXPECT_TRUE(wasScopeCompleted);
}
