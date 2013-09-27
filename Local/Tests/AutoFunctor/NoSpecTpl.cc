#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

namespace
{
typedef float ignored_type;
bool autoFunctionCalled = false;

template <typename T>
struct NoSpec
{
  static void run()
  {
    WG_AUTOFUNCTOR_TPL(noParamsAutoFunctor, void)
    {
      autoFunctionCalled = true;
    }WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(autoFunctionCalled);
  }
};
}
TEST(wg_autofunctortpl, NoSpec)
{
  try
  {
    NoSpec<ignored_type>::run();
  }
  WG_GTEST_CATCH
}
