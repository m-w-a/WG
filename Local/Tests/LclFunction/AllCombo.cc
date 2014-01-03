#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/LclFunction.hh>
#include <WG/Local/Tests/TestHelper.hh>

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
      WG_TESTHELPER_ASSERT_ISNOTCONST(salt);
      WG_TESTHELPER_ASSERT_ISNOTCONST(sugar);
      WG_TESTHELPER_ASSERT_ISCONST(pinchOfSalt);
      WG_TESTHELPER_ASSERT_ISCONST(dos);

      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(bool, salt);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(bool, sugar);
      WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(bool, pinchOfSalt);

      return
        salt == pinchOfSalt &&
        sugar == dos;
    }
    WG_LCLFUNCTION_END;

    WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
      int, makeGingerBreadCookie(0,0));

    success = makeGingerBreadCookie(pinchOfSalt, dashOfSugar);

    EXPECT_TRUE(success);
  }
  WG_GTEST_CATCH
}
