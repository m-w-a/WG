#include <gtest/gtest.h>
#include <WG/Local/AutoFunction.hh>
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

TEST(wg_utils_autofunction, bound_params)
{
  try
  {
    //test_okIf1ArgBound
    {
      bool didArgumentBind = false;

      WG_AUTOFUNCTION_BIND(
        (void), (void), oneArgAutoFunction, (bool &)(didArgumentBind))
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

      WG_AUTOFUNCTION_BIND(
        (void), (void),
        calculateForce,
        (int &)(force) (int const)(mass) (int const)(velocity))
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
          WG_AUTOFUNCTION_BIND(
            (void), (void),
            bindThisU,
            (local(SomeLocalClass * const))(this_))
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

      WG_AUTOFUNCTION_ASSIGN(
        (void), (void),
        oneArgAutoFunction,
        (bool &)(didAssign, proxy.didAssign))
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

      WG_AUTOFUNCTION_ASSIGN(
        (void), (void),
        calculateVolume,
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
    } localObj = {10};

    static int newValue = 0;
    WG_AUTOFUNCTION_BIND(
      (void), (void), useLocalKeyword, (local(SomeLocalClass))(localObj))
    {
      localObj.value += 1;
      newValue = localObj.value;
    }WG_AUTOFUNCTION_END;

    EXPECT_EQ(localObj.value, 10);
    EXPECT_EQ(newValue, 11);
  }
  WG_GTEST_CATCH
}

TEST(wg_utils_autofunction, localref_keyword)
{
  try
  {
    struct SomeLocalClass
    {
      int value;
    } localObj = {0};

    WG_AUTOFUNCTION_BIND(
      (void), (void),
      useLocalKeyword,
      (localref(SomeLocalClass &))(localObj))
    {
      localObj.value = 10;
    }WG_AUTOFUNCTION_END;

    EXPECT_EQ(localObj.value, 10);
  }
  WG_GTEST_CATCH
}

TEST(wg_utils_autofunction, void_params)
{
  try
  {
    static bool autoFunctionCalled = false;

    WG_AUTOFUNCTION((void), (void), noParamsAutoFunction, (void), (void))
    {
      autoFunctionCalled = true;
    }WG_AUTOFUNCTION_END;

    EXPECT_TRUE(autoFunctionCalled);
  }
  WG_GTEST_CATCH
}

TEST(wg_utils_autofunction, mixed_params)
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

      WG_AUTOFUNCTION(
        (void), (void),
        calculateVolume,
        (int &)(volume)
        (int const)(pressure),
        (int const)(numerator, numMoles * R * temp))
      {
        volume = numerator / pressure;
      }WG_AUTOFUNCTION_END;

      EXPECT_EQ(volume, 30);
    }
  }
  WG_GTEST_CATCH
}

TEST(wg_utils_autofunction, nonvoidret_assignedresult_recursive)
{
  try
  {
    int fib = 0;

    WG_AUTOFUNCTION_ASSIGN(
      (int)(fib), (int),
      calculateFibonacci,
      (int)(input, 4))
    {
      if(input > 1)
      {
        return calculateFibonacci(input - 1) + calculateFibonacci(input - 2);
      }
      else return input;
    }WG_AUTOFUNCTION_END;

    EXPECT_EQ(fib, 3);
  }
  WG_GTEST_CATCH
}
