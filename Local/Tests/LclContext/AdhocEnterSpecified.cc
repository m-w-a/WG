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

namespace
{

template <typename T>
struct EnterSpecifiedInTemplate
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
TEST(wg_lclcontext_adhoc, EnterSpecifiedInTemplate)
{
  EnterSpecifiedInTemplate<bool>::run();
}
