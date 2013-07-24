#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>
#include <boost/typeof/typeof.hpp>
#include <WG/Local/Tests/TestHelper.hh>

TEST(wg_autofunctor_qualifiers, Const)
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
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_qualifiers, NoThrow)
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
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_qualifiers, ConstNoThrow)
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
  WG_GTEST_CATCH
}
