#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

TEST(wg_autofunctor, NoSpec)
{
  try
  {
    static bool autoFunctionCalled = false;

    WG_AUTOFUNCTOR(noParamsAutoFunctor, void)
    {
      autoFunctionCalled = true;
    }WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(autoFunctionCalled);
  }
  WG_GTEST_CATCH
}
