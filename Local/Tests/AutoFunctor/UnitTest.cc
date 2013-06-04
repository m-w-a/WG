#include <gtest/gtest.h>
#include <WG/Local/AutoFunctor.hh>
#include <WG/GTest/Exceptions.hh>

/*
wg_utils_autofunctor
  void_params
  bound_params
    test1Arg
    test3ArgsVaryingMutability
  assigned_params
    test1Arg
    test3ArgsVaryingMutability
  bound_and_assigned_params
*/

TEST(wg_utils_autofunctor, bound_params)
{
  try
  {
    //test_okIf1ArgBound
    {
      bool didArgumentBind = false;

      WG_AUTOFUNCTOR(oneArgAutoFunctor,
        parambind ((bool &)didArgumentBind) )
      {
        didArgumentBind = true;
      }WG_AUTOFUNCTOR_END;

      EXPECT_TRUE(didArgumentBind);
    }

    //test_okIf3ArgsOfVaryingMutabilityBound
    {
      int force = 0;
      int const mass = 10;
      int const velocity = 2;

      WG_AUTOFUNCTOR(calculateForce,
        parambind ((int &) force) ((int const) mass) ((int const) velocity) )
      {
        force = mass * velocity;
      }WG_AUTOFUNCTOR_END;

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
          WG_AUTOFUNCTOR(bindThisU,
            parambind (local(SomeLocalClass * const) this_) )
          {
            this_->didBindThis = true;
          }WG_AUTOFUNCTOR_END;
        }
      } someLocalObj;

      EXPECT_TRUE(someLocalObj.didBindThis);
    }
  }
  WG_GTEST_CATCH
}

TEST(wg_utils_autofunctor, set_params)
{
  try
  {
    //test_okIf1ArgAssigned
    {
      struct
      {
        bool didAssign;
      } proxy = {false};

      WG_AUTOFUNCTOR(oneArgAutoFunctor,
        paramset ((bool &) didAssign, proxy.didAssign) )
      {
        didAssign = true;
      }WG_AUTOFUNCTOR_END;

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

      WG_AUTOFUNCTOR(calculateVolume,
        paramset ((int const) radius, cylinder.radius)
          ((int const) height, cylinder.height)
          ((int &) volume, cylinder.volume) )
      {
        volume = radius * height;
      }WG_AUTOFUNCTOR_END;

      EXPECT_EQ(cylinder.radius * cylinder.height, cylinder.volume);
    }
  }
  WG_GTEST_CATCH
}

TEST(wg_utils_autofunctor, local_keyword)
{
  try
  {
    struct SomeLocalClass
    {
      int value;
    } localObj = {10};

    static int newValue = 0;
    WG_AUTOFUNCTOR(useLocalKeyword,
      parambind (local(SomeLocalClass) localObj) )
    {
      localObj.value += 1;
      newValue = localObj.value;
    }WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
    EXPECT_EQ(newValue, 11);
  }
  WG_GTEST_CATCH
}

TEST(wg_utils_autofunctor, localref_keyword)
{
  try
  {
    struct SomeLocalClass
    {
      int value;
    } localObj = {0};

    WG_AUTOFUNCTOR(useLocalKeyword,
      parambind (localref(SomeLocalClass &) localObj) )
    {
      localObj.value = 10;
    }WG_AUTOFUNCTOR_END;

    EXPECT_EQ(localObj.value, 10);
  }
  WG_GTEST_CATCH
}

TEST(wg_utils_autofunctor, void_params)
{
  try
  {
    static bool autoFunctionCalled = false;

    WG_AUTOFUNCTOR(noParamsAutoFunctor, void)
    {
      autoFunctionCalled = true;
    }WG_AUTOFUNCTOR_END;

    EXPECT_TRUE(autoFunctionCalled);
  }
  WG_GTEST_CATCH
}

TEST(wg_utils_autofunctor, mixed_params)
{
  try
  {
    //test_okIf21Combo
    {
      int volume = -1;
      int const pressure = 2;
      int const numMoles = 3;
      int const R = 5;
      int const temp = 4;

      WG_AUTOFUNCTOR(calculateVolume,
        parambind ((int &) volume) ((int const) pressure)
        paramset ((int const) numerator, numMoles * R * temp) )
      {
        volume = numerator / pressure;
      }WG_AUTOFUNCTOR_END;

      EXPECT_EQ(volume, 30);
    }
  }
  WG_GTEST_CATCH
}

TEST(wg_utils_autofunctor, nonvoidret_assignedresult_recursive)
{
  try
  {
    int fib = 0;

    WG_AUTOFUNCTOR(calculateFibonacci,
      assignto ((int) fib)
      return (int)
      paramset ((int) input, 4) )
    {
      if(input > 1)
      {
        return calculateFibonacci(input - 1) + calculateFibonacci(input - 2);
      }
      else return input;
    }WG_AUTOFUNCTOR_END;

    EXPECT_EQ(fib, 3);
  }
  WG_GTEST_CATCH
}
