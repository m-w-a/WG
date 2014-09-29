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

namespace
{
template <typename T>
struct OkIfOneBaseInited
{
  static void run()
  {
    WG_LCLCLASS_TPL(
      Local,
      derives (public T)
      baseinit (T(10)) )
    WG_LCLCLASS_END;

    Local l;

    EXPECT_EQ(10, l.value1);
  }
};
}

TEST(wg_lclclass_baseinit_tpl, OkIfOneBaseInited)
{
  OkIfOneBaseInited<Base1>::run();
}


namespace
{
template <typename T1, typename T2, typename T3>
struct OkIfThreeBasesInited
{
  static void run()
  {
    WG_LCLCLASS_TPL(
      Local,
      derives (public T1) (protected T2) (private T3)
      baseinit (T1(10)) (T2(11)) (T3(12)) )

    void init()
    {
      EXPECT_EQ(10, this->value1);
      EXPECT_EQ(11, this->value2);
      EXPECT_EQ(12, this->value3);
    }

    WG_LCLCLASS_END;

    Local l;
  }
};
}

TEST(wg_lclclass_baseinit_tpl, OkIfThreeBasesInited)
{
  OkIfThreeBasesInited<Base1, Base2, Base3>::run();
}
