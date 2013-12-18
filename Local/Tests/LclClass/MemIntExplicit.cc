#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/TestHelper.hh>
#include <WG/Local/LclClass.hh>
#include <boost/tuple/tuple.hpp>

TEST(wg_lclclass_memintexplicit, EnsureTypeOfNotUsed)
{
  try
  {
    WG_LCLCLASS(Local, memint ((int) value, 1.2f) )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISNOTCONST(value);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, value);

        EXPECT_EQ(1, value);
      }
    WG_LCLCLASS_END;

    Local obj;
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memintexplicit, OkIfMemTypeGloballyScoped)
{
  try
  {
    WG_LCLCLASS
    (Local,
      memint ((::boost::tuple<bool>) assigner, ::boost::make_tuple(true)) )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISNOTCONST(assigner);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
          ::boost::tuple<bool>, assigner);

        EXPECT_EQ(true, assigner.get<0>());
      }
    WG_LCLCLASS_END;

    Local obj;
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memintexplicit, OkIf3MemOfVaryingMutabilitySet)
{
  try
  {
    WG_LCLCLASS
    (CalculateVolume,
      memint
        ((short const) radius, 2)
        ((int const) height, 10)
        ((long) volume, radius * height) )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISCONST(radius);
        WG_TESTHELPER_ASSERT_ISCONST(height);
        WG_TESTHELPER_ASSERT_ISNOTCONST(volume);

        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(short, radius);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, height);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(long, volume);
      }
    WG_LCLCLASS_END;

    CalculateVolume c;
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memintexplicit, OkIfNoQlfdLocalTypeSet)
{
  try
  {
    WG_TESTHELPER_LOCALTYPE_DECLARE(SomeLocalClass);

    WG_LCLCLASS
    (UseLocalKeyword, memint (local(SomeLocalClass) obj, SomeLocalClass()) )
      void init()
      {
        WG_TESTHELPER_ASSERT_LOCALTYPE_ISNOTCONST(obj);
        WG_TESTHELPER_ASSERT_LOCALTYPE_ISSAMETYPE_MODULOCONSTANDREF(
          SomeLocalClass, obj);
      }
    WG_LCLCLASS_END;

    UseLocalKeyword ulk;
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memintexplicit, OkIfConstQlfdLocalTypeSet)
{
  try
  {
    WG_TESTHELPER_LOCALTYPE_DECLARE(SomeLocalClass);

    WG_LCLCLASS
    (UseLocalKeyword, memint (local(SomeLocalClass) const obj, SomeLocalClass()) )
      void init()
      {
        WG_TESTHELPER_ASSERT_LOCALTYPE_ISCONST(obj);
        WG_TESTHELPER_ASSERT_LOCALTYPE_ISSAMETYPE_MODULOCONSTANDREF(
          SomeLocalClass, obj);
      }
    WG_LCLCLASS_END;

    UseLocalKeyword ulk;
  }
  WG_GTEST_CATCH
}
