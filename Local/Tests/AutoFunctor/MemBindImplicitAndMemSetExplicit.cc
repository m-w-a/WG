#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

TEST(wg_autofunctor_membindimplicitandmemsetexplicit, OkIfUsing21Combo)
{
  try
  {
    int volume = -1;
    int const pressure = 2;
    int const numMoles = 3;
    int const R = 5;
    int const temp = 4;

    WG_AUTOFUNCTOR
    (calculateVolume,
      membind (ref volume) (const pressure)
      memset ((int const) numerator, numMoles * R * temp) )
    {
      this->volume = this->numerator / this->pressure;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(volume, 30);
  }
  WG_GTEST_CATCH
}
