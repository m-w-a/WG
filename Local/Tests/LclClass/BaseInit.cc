#include <gtest/gtest.h>
#include <WG/Local/LclClass.hh>

namespace
{

struct Base1
{
  explicit Base1(int v)
  : value1(v)
  {}

  int value1;
};

struct Base2
{
  explicit Base2(int v)
  : value2(v)
  {}

  int value2;
};

struct Base3
{
  explicit Base3(int v)
  : value3(v)
  {}

  int value3;
};

}

TEST(wg_lclclass_baseinit, OkIfOneBaseInited)
{
  WG_LCLCLASS(
    Local,
    derives (public Base1)
    baseinit (Base1(10)) )
  WG_LCLCLASS_END;

  Local l;

  EXPECT_EQ(10, l.value1);
}

TEST(wg_lclclass_baseinit, OkIfThreeBasesInited)
{
  WG_LCLCLASS(
    Local,
    derives (public Base1) (protected Base2) (private Base3)
    baseinit (Base1(10)) (Base2(11)) (Base3(12)) )

  void init()
  {
    EXPECT_EQ(10, value1);
    EXPECT_EQ(11, value2);
    EXPECT_EQ(12, value3);
  }

  WG_LCLCLASS_END;

  Local l;
}
