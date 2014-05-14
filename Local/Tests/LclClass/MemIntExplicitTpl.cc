#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/Utils/Utils.hh>
#include <WG/Local/LclClass.hh>

namespace
{
template <typename T>
struct EnsureTypeOfNotUsed
{
  static void run()
  {
    WG_LCLCLASS_TPL(Local, memint (type(T) value, 1.2f) )
      void init()
      {
        WG_TEST_ASSERT_ISNOTCONST_TPL(value);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T, value);

        EXPECT_EQ(1, value);
      }
    WG_LCLCLASS_END;

    Local obj;
  }
};
}
TEST(wg_lclclass_memintexplicit_tpl, EnsureTypeOfNotUsed)
{
  try
  {
    EnsureTypeOfNotUsed<int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2, typename T3>
struct OkIf3MemOfVaryingMutabilitySet
{
  static void run()
  {
    WG_LCLCLASS_TPL
    (CalculateVolume,
      memint
        (type(T1 const) radius, 2)
        (type(T2 const) height, 10)
        (type(T3) volume, radius * height) )
      void init()
      {
        WG_TEST_ASSERT_ISCONST_TPL(radius);
        WG_TEST_ASSERT_ISCONST_TPL(height);
        WG_TEST_ASSERT_ISNOTCONST_TPL(volume);

        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T1, radius);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T2, height);
        WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T3, volume);
      }
    WG_LCLCLASS_END;

    CalculateVolume c;
  }
};
}
TEST(wg_lclclass_memintexplicit_tpl, OkIf3MemOfVaryingMutabilitySet)
{
  try
  {
    OkIf3MemOfVaryingMutabilitySet<short, int, long>::run();
  }
  WG_GTEST_CATCH
}
