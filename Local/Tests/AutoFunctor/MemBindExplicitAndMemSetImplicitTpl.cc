#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

namespace
{
template <typename T1, typename T2, typename T3, typename T4, typename T5>
struct OkIfUsing21Combo
{
  static void run()
  {
    T1 volume = -1;
    T2 const pressure = 2;
    T3 const numMoles = 3;
    T4 const R = 5;
    T5 const temp = 4;

    WG_AUTOFUNCTOR_TPL
    (calculateVolume,
      membind ((int &) volume) ((int const) pressure)
      memset (numerator, numMoles * R * temp) )
    {
      this->volume = this->numerator / this->pressure;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(volume, 30);
  }
};
}
TEST(wg_autofunctor_membindexplicitandmemsetimplicittpl, OkIfUsing21Combo)
{
  try
  {
    OkIfUsing21Combo<int, int, int, int, int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2, typename T3, typename T4, typename T5>
struct OkIfLocalTypeBound
{
  static void run()
  {
    struct Input
    {
      T1 const pressure;
      T2 const numMoles;
      T3 const R;
      T4 const temp;
    } data = {2, 3, 5, 4};

    T5 volume = -1;
    WG_AUTOFUNCTOR_TPL
    (calculateVolume,
      membind (local(Input) data) memset (ref result, volume) )
    {
      this->result =
        (this->data.numMoles * this->data.R * this->data.temp) / this->data.pressure;
    }
    WG_AUTOFUNCTOR_END;

    EXPECT_EQ(volume, 30);
  }
};
}
TEST(wg_autofunctor_membindexplicitandmemsetimplicittpl, OkIfLocalTypeBound)
{
  try
  {
    OkIfLocalTypeBound<int, int, int, int, int>::run();
  }
  WG_GTEST_CATCH
}
