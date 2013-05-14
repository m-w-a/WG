#include <gtest/gtest.h>
#include <WG/Utils/AutoFunction.hh>
#include <WG/GTest/Exceptions.hh>

/*
wg_utils_autofunction
  void_params
  bound_params
    test1Arg
    test3ArgsVaryingMutability
  assigned_params
    test1Arg
    test3ArgsVaryingMutability
  bound_and_assigned_params
*/

TEST(wg_utils_autofunction, void_params)
{
  try
  {
    static bool autoFunctionCalled = false;

    WG_AUTOFUNCTION(noParamsAutoFunction, (void), (void))
    {
      autoFunctionCalled = true;
    }WG_AUTOFUNCTION_END;

    EXPECT_TRUE(autoFunctionCalled);
  }
  WG_GTEST_CATCH
}

TEST(wg_utils_autofunction, bound_params)
{
  try
  {
    //test_okIf1ArgBound
    {
      bool didArgumentBind = false;

      WG_AUTOFUNCTION(oneArgAutoFunction, (bool &)(didArgumentBind), (void))
      {
        didArgumentBind = true;
      }WG_AUTOFUNCTION_END;

      EXPECT_TRUE(didArgumentBind);
    }

    //test_okIf3ArgsOfVaryingMutabilityBound
    {
      int force = 0;
      int const mass = 10;
      int const velocity = 2;

      WG_AUTOFUNCTION(
        calculateForce,
        (int &)(force) (int const)(mass) (int const)(velocity),
        (void))
      {
        force = mass * velocity;
      }WG_AUTOFUNCTION_END;

      EXPECT_EQ(force, 20);
    }

    //test_okWhenKeywordThisUBound
    {
      struct SomeLocalClass
      {
        bool didBindThis;

        SomeLocalClass()
        : didBindThis(false)
        {
          WG_AUTOFUNCTION(
            bindThisU,
            (local(SomeLocalClass * const))(this_),
            (void))
          {
            this_->didBindThis = true;
          }WG_AUTOFUNCTION_END;
        }
      } someLocalObj;

      EXPECT_TRUE(someLocalObj.didBindThis);
    }
  }
  WG_GTEST_CATCH
}

TEST(wg_utils_autofunction, assigned_params)
{
  try
  {
    //test_okIf1ArgAssigned
    {
      struct
      {
        bool didAssign;
      } proxy = {false};

      WG_AUTOFUNCTION(
        oneArgAutoFunction, (void), (bool &)(didAssign, proxy.didAssign))
      {
        didAssign = true;
      }WG_AUTOFUNCTION_END;

      EXPECT_TRUE(proxy.didAssign);
    }

    //test_okIfokIf3ArgsOfVaryingMutabilityAssigned
    {
      struct
      {
        int radius;
        int height;
        int volume;
      } cylinder = {2, 10, -1};

      WG_AUTOFUNCTION(
        calculateVolume,
        (void),
        (int const)(radius, cylinder.radius)
        (int const)(height, cylinder.height)
        (int &)(volume, cylinder.volume)
      )
      {
        volume = radius * height;
      }WG_AUTOFUNCTION_END;

      EXPECT_EQ(cylinder.radius * cylinder.height, cylinder.volume);
    }
  }
  WG_GTEST_CATCH
}

TEST(wg_utils_autofunction, local_keyword)
{
  try
  {
    struct SomeLocalClass
    {
      int value;
    } localObj = {0};

    WG_AUTOFUNCTION(
      useLocalKeyword,
      (local(SomeLocalClass &))(localObj),
      (void))
    {
      localObj.value = 10;
    }WG_AUTOFUNCTION_END;

    EXPECT_EQ(localObj.value, 10);
  }
  WG_GTEST_CATCH
}
