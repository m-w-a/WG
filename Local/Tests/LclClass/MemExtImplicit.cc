#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/TestHelper.hh>
#include <WG/Local/LclClass.hh>
#include <boost/typeof/typeof.hpp>

TEST(wg_lclclass_memextimplicit, Mimic1Var)
{
  try
  {
    bool var = false;

    WG_LCLCLASS(Local, memext (var) )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISNOTCONST(var);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(bool, var);
      }
    public:
      BOOST_TYPEOF(var) const & getVar() const { return var; }
    WG_LCLCLASS_END;

    Local v(var);

    WG_TESTHELPER_ASSERT_ISNOTREFERENCE(var, v.getVar());
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memextimplicit, Mimic1VarByRef)
{
  try
  {
    bool var = false;

    WG_LCLCLASS(Local, memext (ref var) )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISNOTCONST(var);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(bool, var);
      }
    public:
      BOOST_TYPEOF(var) const & getVar() const { return var; }
    WG_LCLCLASS_END;

    Local v(var);

    WG_TESTHELPER_ASSERT_ISREFERENCE(var, v.getVar());
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memextimplicit, Mimic1VarByConst)
{
  try
  {
    int const red = 10;

    WG_LCLCLASS(Local, memext (const red) )
      void didMimicType() const
      {
        WG_TESTHELPER_ASSERT_ISCONST(red);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, red);
      }
    public:
      BOOST_TYPEOF(red) const & getRed() const { return red; }
    WG_LCLCLASS_END;

    Local v(red);

    WG_TESTHELPER_ASSERT_ISNOTREFERENCE(red, v.getRed());
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memextimplicit, Mimic1VarByConstRef)
{
  try
  {
    int blue = 10;

    WG_LCLCLASS(Local, memext (const ref blue) )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISCONST(blue);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, blue);
      }
    public:
      BOOST_TYPEOF(blue) const & getBlue() const
      {
        return blue;
      }
    WG_LCLCLASS_END;

    Local v(blue);

    WG_TESTHELPER_ASSERT_ISREFERENCE(blue, v.getBlue());
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memextimplicit, Mimic3Vars)
{
  try
  {
    int force = 0;
    int const mass = 10;
    int const velocity = 2;

    WG_LCLCLASS
    (CalculateForce,
      memext (ref force) (const mass) (const ref velocity)
    )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISNOTCONST(force);
        WG_TESTHELPER_ASSERT_ISCONST(mass);
        WG_TESTHELPER_ASSERT_ISCONST(velocity);

        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, force);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, mass);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(int, velocity);
      }
    public:
      BOOST_TYPEOF(force) const & getForce() const { return force; }
      BOOST_TYPEOF(mass) const & getMass() const { return mass; }
      BOOST_TYPEOF(velocity) const & getVelocity() const { return velocity; }
    WG_LCLCLASS_END;

    CalculateForce c(force, mass, velocity);

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
    (Local, memext (this_) )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISCONST(this_);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF(MimicThisU *, this_);
      }
    public:
      BOOST_TYPEOF(this_) const & getThisU() const { return this_; }
    WG_LCLCLASS_END;

    Local v(this);

    WG_TESTHELPER_ASSERT_ISREFERENCE(*this, *v.getThisU());
  }
};
}
TEST(wg_lclclass_memextimplicit, MimicThisU)
{
  try
  {
    MimicThisU obj;
  }
  WG_GTEST_CATCH
}

TEST(wg_lclclass_memextimplicit, OkIfMultipleUseInSameScope)
{
  try
  {
    int var = 1;

    WG_LCLCLASS(Local1, memext (ref var) )
      void init() { ++var; }
    WG_LCLCLASS_END;

    WG_LCLCLASS(Local2, memext (ref var) )
      void init() { ++var; }
    WG_LCLCLASS_END;

    Local1 v1(var);
    Local2 v2(var);

    EXPECT_EQ(3, var);
  }
  WG_GTEST_CATCH
}
