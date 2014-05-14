#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/Utils/Utils.hh>

namespace
{
template <typename T1, typename T2, typename T3>
struct TestTpl
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
      memset (temperature, 450.0f) ((double) bakingTime, 0.5) )
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
TEST(wg_autofunctor_allcombotpl, Test)
{
  try
  {
    TestTpl<bool, bool, int>::run();
  }
  WG_GTEST_CATCH
}
