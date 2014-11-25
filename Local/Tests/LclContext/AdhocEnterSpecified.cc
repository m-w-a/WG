#include <gtest/gtest.h>
#include <boost/config.hpp>
#include <WG/Local/LclContext.hh>

TEST(wg_lclcontext_adhoc_enterspecified, CompletedScope)
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

namespace
{

template <typename T>
struct InTemplate
{
  static void run()
  {
    T didCallEnter = false;
    T wasScopeCompleted = false;

    WG_LCLCONTEXT_TPL(
      with_adhoc (ref didCallEnter)
        on_enter( didCallEnter = true )  )
    {
      EXPECT_TRUE(didCallEnter);
      wasScopeCompleted = true;
    }
    WG_LCLCONTEXT_END1

    EXPECT_TRUE(wasScopeCompleted);
  }
};

}
TEST(wg_lclcontext_adhoc_enterspecified, InTemplate)
{
  InTemplate<bool>::run();
}
