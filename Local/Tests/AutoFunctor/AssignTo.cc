#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

TEST(wg_autofunctor_assignto, OkIfNonLocalExplicit)
{
  try
  {
    bool didAssign = 0;

    WG_AUTOFUNCTOR(assign, assignto ((bool) didAssign) )
    {
      return true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didAssign);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_assignto, OkIfNonLocalImplicit)
{
  try
  {
    bool didAssign = 0;

    WG_AUTOFUNCTOR(assign, assignto (didAssign) )
    {
      return true;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(didAssign);
  }
  WG_GTEST_CATCH
}
