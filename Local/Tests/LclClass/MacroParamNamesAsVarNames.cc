#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclClass.hh>

TEST(wg_lclclass_macroparamnamesasvarnames, ImplicitlyTyped)
{
  try
  {
    bool type = true;

    WG_LCLCLASS(Local,
      memext (type) memint (lcltype, 'a') )
        void init()
        {
          EXPECT_EQ(true, type);
          EXPECT_EQ('a', lcltype);
        }
    WG_LCLCLASS_END;

    Local l(type);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_macroparamnamesasvarnames, ExplicitlyTyped)
{
  try
  {
    struct SomeLocalType
    {
      char value;
    };

    SomeLocalType slo = {'a'};

    WG_LCLCLASS(Local,
      memext (lcltype(SomeLocalType) lcltype) memint (type(bool) type, true) )
        void init()
        {
          EXPECT_EQ('a', lcltype.value);
          EXPECT_EQ(true, type);
        }
    WG_LCLCLASS_END;

    Local l(slo);
  }
  WG_GTEST_CATCH
}
