//#include <gtest/gtest.h>
//#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/TestHelper.hh>
#include <WG/Local/LclClass.hh>
#include "BaseClasses.hh"

TEST(wg_lclclass_memlike, Mimic1Var)
{
  try
  {
    bool var = false;

    WG_LCLCLASS(verifier, memlike (var) )
      void operator()()
      {
        bool * is_bool = &var;
      }
    WG_LCLCLASS_END;
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memlike, Mimic1VarByRef)
{
  try
  {
    bool var = false;

    WG_LCLCLASS(verifier, memdecl ((bool *) pVar) memlike (ref var) )
      void init()
      {
        bool is_ref = (pVar == &var);
        EXPECT_TRUE(is_ref);
      }
    WG_LCLCLASS_END;

    verifier v(&var, var);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memlike, Mimic1VarByConst)
{
  try
  {
    int const red = 10;

    WG_LCLCLASS(verifier, memlike (const red) )
      void didMimicType() const
      {
        enum { is_const = red };
        int const * is_int = &red;
      }
    WG_LCLCLASS_END;
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memlike, Mimic1VarByConstRef)
{
  try
  {
    int blue = 10;

    WG_LCLCLASS(verifier, memdecl ((int *) pBlue) memlike (const ref blue) )
      void init()
      {
        enum { is_const = blue };
        bool is_ref = (pBlue == &blue);
        EXPECT_TRUE(is_ref);
      }
    WG_LCLCLASS_END;

    verifier v(&blue, blue);
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memlike, Mimic3Vars)
{
  try
  {
    int force = 0;
    int const mass = 10;
    int const velocity = 2;

    WG_LCLCLASS
    (calculateForce,
      memdecl ((int *) pForce) ((int const *) pMass) ((int const *) pVelocity)
      memlike (ref force) (const mass) (const ref velocity)
    )
      void init()
      {
        bool is_ref_force = (pForce == &force);
        EXPECT_TRUE(is_ref_force);

        enum { is_const_mass = mass };
        bool is_not_ref_mass = (pMass != &mass);
        EXPECT_TRUE(is_not_ref_mass);

        enum{ is_const_velocity = velocity };
        bool is_ref_velocity = (pVelocity == &velocity);
        EXPECT_TRUE(pVelocity == &velocity);
      }
    WG_LCLCLASS_END;

    calculateForce c(&force, &mass, &velocity, force, mass, velocity);
  }
  WG_GTEST_CATCH
}

namespace
{
struct MimicThisU
{
  MimicThisU()
  {
    WG_LCLCLASS
    (verifier, memlike (this_) )
    WG_LCLCLASS_END;

    verifier v(this);
  }
};
}
TEST(wg_lclclass_memlike, MimicThisU)
{
  try
  {
    MimicThisU obj;
  }
  WG_GTEST_CATCH
}
