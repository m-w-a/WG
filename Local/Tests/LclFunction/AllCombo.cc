#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>

TEST(wg_lclfunction_allcombo, Test)
{
  try
  {
    bool success = false;

    bool pinchOfSalt = true;
    int dashOfSugar = 0;

    WG_LCLFUNCTION
    (makeGingerBreadCookie,
      return (int)
      params ((bool) salt) ((bool) sugar)
      varbind (const pinchOfSalt)
      varset (const dos, dashOfSugar) )
    {
      return
        salt == pinchOfSalt &&
        sugar == dos;
    }
    WG_LCLFUNCTION_END;

    success = makeGingerBreadCookie(pinchOfSalt, dashOfSugar);

    EXPECT_TRUE(success);
  }
  WG_GTEST_CATCH
}
