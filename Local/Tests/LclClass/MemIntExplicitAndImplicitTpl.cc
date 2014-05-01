#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/TestHelper.hh>
#include <WG/Local/LclClass.hh>

namespace
{
struct ignore;
}

namespace
{
template <typename IGNORED>
struct OkIf3MemOfVaryingMutabilitySet
{
  static void run()
  {
    WG_LCLCLASS
    (CalculateVolume,
      memint
        (const radius, 2)
        (height, 10)
        (type(long const) volume, radius * height) )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISCONST(radius);
        WG_TESTHELPER_ASSERT_ISNOTCONST(height);
        WG_TESTHELPER_ASSERT_ISCONST(volume);

        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(long, volume);
      }
    WG_LCLCLASS_END;

    CalculateVolume c;
  }
};
}
TEST(wg_lclclass_memintexplicitandimplicit_tpl, OkIf3MemOfVaryingMutabilitySet)
{
  try
  {
    OkIf3MemOfVaryingMutabilitySet<ignore>::run();
  }
  WG_GTEST_CATCH
}
