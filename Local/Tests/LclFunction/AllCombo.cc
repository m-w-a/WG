#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <WG/Local/Tests/Utils/Utils.hh>

TEST(wg_lclfunction_allcombo, Test)
{
  try
  {
    bool success = false;

    bool pinchOfSalt = true;
    int dashOfSugar = 0;

    WG_TEST_LCLFUNCTION
    (makeGingerBreadCookie,
      return (int)
      params (bool salt) (bool sugar)
      varbind (const pinchOfSalt)
      varset (const dos, dashOfSugar) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(makeGingerBreadCookie);

      WG_TEST_ASSERT_ISNOTCONST(salt);
      WG_TEST_ASSERT_ISNOTCONST(sugar);
      WG_TEST_ASSERT_ISCONST(pinchOfSalt);
      WG_TEST_ASSERT_ISCONST(dos);

      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(bool, salt);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(bool, sugar);
      WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(bool, pinchOfSalt);

      return
        salt == pinchOfSalt &&
        sugar == dos;
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(
      int, makeGingerBreadCookie(0,0));

    success = makeGingerBreadCookie(pinchOfSalt, dashOfSugar);
    WG_TEST_LCLFUNCTION_VERIFYCALL(makeGingerBreadCookie);

    EXPECT_TRUE(success);
  }
  WG_GTEST_CATCH
}
