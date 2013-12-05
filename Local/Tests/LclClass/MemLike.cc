//#include <gtest/gtest.h>
//#include <boost/typeof/typeof.hpp>
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
      void init()
      {
        WG_PP_TESTHELPER_ASSERT_ISNOTCONST(var);
        WG_PP_TESTHELPER_ASSERT_ISSAMETYPE(bool, BOOST_TYPEOF(var));
      }
      BOOST_TYPEOF(var) const & getVar() const { return var; }
    WG_LCLCLASS_END;

    verifier v(var);

    WG_TESTHELPER_ASSERT_ISNOTREFERENCE(var, v.getVar());
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memlike, Mimic1VarByRef)
{
  try
  {
    bool var = false;

    WG_LCLCLASS(verifier, memlike (ref var) )
      void init()
      {
        WG_PP_TESTHELPER_ASSERT_ISNOTCONST(var);
        WG_PP_TESTHELPER_ASSERT_ISSAMETYPE(bool, BOOST_TYPEOF(var));
      }
      BOOST_TYPEOF(var) const & getVar() const { return var; }
    WG_LCLCLASS_END;

    verifier v(var);

    WG_TESTHELPER_ASSERT_ISREFERENCE(var, v.getVar());
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
        WG_PP_TESTHELPER_ASSERT_ISCONST(red);
        WG_PP_TESTHELPER_ASSERT_ISSAMETYPE(int, BOOST_TYPEOF(red));
      }
      BOOST_TYPEOF(red) const & getRed() const { return red; }
    WG_LCLCLASS_END;

    verifier v(red);

    WG_TESTHELPER_ASSERT_ISNOTREFERENCE(red, v.getRed());
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memlike, Mimic1VarByConstRef)
{
  try
  {
    int blue = 10;

    WG_LCLCLASS(verifier, memlike (const ref blue) )
      void init()
      {
        WG_PP_TESTHELPER_ASSERT_ISCONST(blue);
        WG_PP_TESTHELPER_ASSERT_ISSAMETYPE(int, BOOST_TYPEOF(blue));
      }
      BOOST_TYPEOF(blue) const & getBlue() const
      {
        return blue;
      }
    WG_LCLCLASS_END;

    verifier v(blue);

    WG_TESTHELPER_ASSERT_ISREFERENCE(blue, v.getBlue());
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
      memlike (ref force) (const mass) (const ref velocity)
    )
      void init()
      {
        WG_PP_TESTHELPER_ASSERT_ISNOTCONST(force);
        WG_PP_TESTHELPER_ASSERT_ISCONST(mass);
        WG_PP_TESTHELPER_ASSERT_ISCONST(velocity);

        WG_PP_TESTHELPER_ASSERT_ISSAMETYPE(int, BOOST_TYPEOF(force));
        WG_PP_TESTHELPER_ASSERT_ISSAMETYPE(int, BOOST_TYPEOF(mass));
        WG_PP_TESTHELPER_ASSERT_ISSAMETYPE(int, BOOST_TYPEOF(velocity));
      }
      BOOST_TYPEOF(force) const & getForce() const { return force; }
      BOOST_TYPEOF(mass) const & getMass() const { return mass; }
      BOOST_TYPEOF(velocity) const & getVelocity() const { return velocity; }
    WG_LCLCLASS_END;

    calculateForce c(force, mass, velocity);

    WG_TESTHELPER_ASSERT_ISREFERENCE(force, c.getForce());
    WG_TESTHELPER_ASSERT_ISNOTREFERENCE(mass, c.getMass());
    WG_TESTHELPER_ASSERT_ISREFERENCE(velocity, c.getVelocity());
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
      void init()
      {
        WG_PP_TESTHELPER_ASSERT_ISCONST(this_);
        WG_PP_TESTHELPER_ASSERT_ISSAMETYPE(MimicThisU *, BOOST_TYPEOF(this_));
      }
      BOOST_TYPEOF(this_) const & getThisU() const { return this_; }
    WG_LCLCLASS_END;

    verifier v(this);

    WG_TESTHELPER_ASSERT_ISREFERENCE(this, c.getThisU());
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
