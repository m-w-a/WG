#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/Utils/Utils.hh>
#include <WG/Local/LclClass.hh>

namespace
{
template <typename T1, typename T2, typename T3>
struct OkIf3MemOfVaryingMutabilitySet
{
  static void run()
  {
    T1 const radius = 2;
    T2 const height = 10;
    T3 volume = -1;

    WG_LCLCLASS_TPL
    (CalculateVolume,
      memext (const radius) (type(int) height) (const volume) )
      void init()
      {
        WG_TEST_ASSERT_ISCONST_TPL(radius);
        WG_TEST_ASSERT_ISNOTCONST_TPL(height);
        WG_TEST_ASSERT_ISCONST_TPL(volume);

        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T1, radius);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T2, height);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T3, volume);

        EXPECT_EQ(2, radius);
        EXPECT_EQ(10, height);
        EXPECT_EQ(20, volume);
      }
    WG_LCLCLASS_END;

    CalculateVolume c(radius, height, radius * height);
  }
};
}
TEST(wg_lclclass_memextexplicitandimplicit_tpl, OkIf3MemOfVaryingMutabilitySet)
{
  try
  {
    OkIf3MemOfVaryingMutabilitySet<short, int, long>::run();
  }
  WG_GTEST_CATCH
}
