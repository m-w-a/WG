#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/TestHelper.hh>
#include <WG/Local/LclClass.hh>
#include <boost/tuple/tuple.hpp>

namespace
{
struct ignore;
}

namespace
{
template <typename IGNORED>
struct OkIfMemValueGloballyScoped
{
  static void run()
  {
    WG_LCLCLASS_TPL
    (Local,
      memint (assigner, ::boost::make_tuple(true)) )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(assigner);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
          ::boost::tuple<bool>, assigner);

        EXPECT_EQ(true, assigner.get<0>());
      }
    WG_LCLCLASS_END;

    Local obj;
  }
};
}
TEST(wg_lclclass_memintimplicit_tpl, OkIfMemValueGloballyScoped)
{
  try
  {
    OkIfMemValueGloballyScoped<ignore>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename IGNORED>
struct OkIf3MemOfVaryingMutabilitySet
{
  static void run()
  {
    WG_LCLCLASS_TPL
    (CalculateVolume,
      memint
        (const radius, 2)
        (height, 10ul)
        (volume, radius * height) )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISCONST_TPL(radius);
        WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(height);
        WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(volume);

        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(int, radius);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(unsigned long, height);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(unsigned long, volume);
      }
    WG_LCLCLASS_END;

    CalculateVolume c;
  }
};
}
TEST(wg_lclclass_memintimplicit_tpl, OkIf3MemOfVaryingMutabilitySet)
{
  try
  {
    OkIf3MemOfVaryingMutabilitySet<ignore>::run();
  }
  WG_GTEST_CATCH
}
