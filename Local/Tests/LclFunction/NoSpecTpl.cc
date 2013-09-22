#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>

namespace
{
typedef float ignored_type;
bool wasCalled = false;

template <typename T>
struct NoSpec
{
  static void run()
  {
    WG_LCLFUNCTION(nospec, void)
    {
      wasCalled = true;
    }WG_LCLFUNCTION_END;

    nospec();

    EXPECT_TRUE(wasCalled);
  }
};
}

TEST(wg_lclfunction_tpl, NoSpec)
{
  try
  {
    NoSpec<ignored_type>::run();
  }
  WG_GTEST_CATCH
}
