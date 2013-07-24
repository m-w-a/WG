#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/TestHelper.hh>

TEST(wg_autofunctor_allcombo, Test)
{
  try
  {
    bool success = false;

    bool pinchOfSalt = true;
    int dashOfSugar = 0;

    WG_AUTOFUNCTOR
    (makeGingerBreadCookie,
      assignto (success)
      return (int)
      parambind (pinchOfSalt) ((bool) dashOfSugar)
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
  WG_GTEST_CATCH
}
