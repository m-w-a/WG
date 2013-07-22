#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/TestHelper.hh>

namespace
{
template <typename T1, typename T2, typename T3>
struct Const
{
  static void run()
  {
    T1 success = false;

    T2 pinchOfSalt = true;
    T3 dashOfSugar = 0;

    WG_AUTOFUNCTOR_TPL
    (makeGingerBreadCookie,
      assignto (success)
      return (int)
      parambind (pinchOfSalt) ((T3) dashOfSugar)
      paramset (temperature, 450.0f) ((double) bakingTime, 0.5)
      membind (pinchOfSalt) ((bool) dashOfSugar)
      memset (temperature, 450.0f) ((double) bakingTime, 0.5) ) const
    {
      return
        pinchOfSalt == this->pinchOfSalt &&
        dashOfSugar == this->dashOfSugar &&
        temperature == this->temperature &&
        bakingTime == this->bakingTime;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(success);
  }
};
}
TEST(wg_autofunctor_qualifierstpl, Const)
{
  try
  {
    Const<bool, bool, int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2, typename T3>
struct NoThrow
{
  static void run()
  {
    T1 success = false;

    T2 pinchOfSalt = true;
    T3 dashOfSugar = 0;

    WG_AUTOFUNCTOR_TPL
    (makeGingerBreadCookie,
      assignto (success)
      return (int)
      parambind (pinchOfSalt) ((T3) dashOfSugar)
      paramset (temperature, 450.0f) ((double) bakingTime, 0.5)
      membind (pinchOfSalt) ((bool) dashOfSugar)
      memset (temperature, 450.0f) ((double) bakingTime, 0.5) ) throw()
    {
      return
        pinchOfSalt == this->pinchOfSalt &&
        dashOfSugar == this->dashOfSugar &&
        temperature == this->temperature &&
        bakingTime == this->bakingTime;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(success);
  }
};
}
TEST(wg_autofunctor_qualifierstpl, NoThrow)
{
  try
  {
    NoThrow<bool, bool, int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2, typename T3>
struct ConstNoThrow
{
  static void run()
  {
    T1 success = false;

    T2 pinchOfSalt = true;
    T3 dashOfSugar = 0;

    WG_AUTOFUNCTOR_TPL
    (makeGingerBreadCookie,
      assignto (success)
      return (int)
      parambind (pinchOfSalt) ((T3) dashOfSugar)
      paramset (temperature, 450.0f) ((double) bakingTime, 0.5)
      membind (pinchOfSalt) ((bool) dashOfSugar)
      memset (temperature, 450.0f) ((double) bakingTime, 0.5) ) const throw()
    {
      return
        pinchOfSalt == this->pinchOfSalt &&
        dashOfSugar == this->dashOfSugar &&
        temperature == this->temperature &&
        bakingTime == this->bakingTime;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(success);
  }
};
}
TEST(wg_autofunctor_qualifierstpl, ConstNoThrow)
{
  try
  {
    ConstNoThrow<bool, bool, int>::run();
  }
  WG_GTEST_CATCH
}
