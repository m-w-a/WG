#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

TEST(wg_autofunctor_membindexplicitandmemsetimplicit, OkIfUsing21Combo)
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
      membind ((int &) volume) ((int const) pressure)
      memset (numerator, numMoles * R * temp) )
    {
      this->volume = this->numerator / this->pressure;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(volume, 30);
  }
  WG_GTEST_CATCH
}

TEST(wg_autofunctor_membindexplicitandmemsetimplicit, OkIfLocalTypeBound)
{
  try
  {
    struct Input
    {
      int const pressure;
      int const numMoles;
      int const R;
      int const temp;
    } data = {2, 3, 5, 4};

    int volume = -1;
    WG_AUTOFUNCTOR
    (calculateVolume,
      membind (local(Input) data) memset (ref result, volume) )
    {
      this->result =
        (this->data.numMoles * this->data.R * this->data.temp) / this->data.pressure;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(volume, 30);
  }
  WG_GTEST_CATCH
}
