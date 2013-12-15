#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <WG/Local/Tests/TestHelper.hh>
#include <WG/Local/LclClass.hh>
#include <boost/typeof/typeof.hpp>

namespace
{
template <typename T>
struct Mimic1Var
{
  static void run()
  {
    T var = false;

    WG_LCLCLASS_TPL(verifier, memlike (var) )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(var);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(bool, var);
      }
    public:
      T const & getVar() const { return var; }
    WG_LCLCLASS_END;

    verifier v(var);

    WG_TESTHELPER_ASSERT_ISNOTREFERENCE(var, v.getVar());
  }
};
}
TEST(wg_lclclass_memlike_tpl, Mimic1Var)
{
  try
  {
    Mimic1Var<bool>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct Mimic1VarByRef
{
  static void run()
  {
    T var = false;

    WG_LCLCLASS_TPL(verifier, memlike (ref var) )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(var);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(bool, var);
      }
    public:
      T const & getVar() const { return var; }
    WG_LCLCLASS_END;

    verifier v(var);

    WG_TESTHELPER_ASSERT_ISREFERENCE(var, v.getVar());
  }
};
}
TEST(wg_lclclass_memlike_tpl, Mimic1VarByRef)
{
  try
  {
    Mimic1VarByRef<bool>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct Mimic1VarByConst
{
  static void run()
  {
    T const red = 10;

    WG_LCLCLASS_TPL(verifier, memlike (const red) )
      void didMimicType() const
      {
        WG_TESTHELPER_ASSERT_ISCONST_TPL(red);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(int, red);
      }
    public:
      T const & getRed() const { return red; }
    WG_LCLCLASS_END;

    verifier v(red);

    WG_TESTHELPER_ASSERT_ISNOTREFERENCE(red, v.getRed());
  }
};
}
TEST(wg_lclclass_memlike_tpl, Mimic1VarByConst)
{
  try
  {
    Mimic1VarByConst<int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T>
struct Mimic1VarByConstRef
{
  static void run()
  {
    T blue = 10;

    WG_LCLCLASS_TPL(verifier, memlike (const ref blue) )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISCONST_TPL(blue);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(int, blue);
      }
    public:
      T const & getBlue() const
      {
        return blue;
      }
    WG_LCLCLASS_END;

    verifier v(blue);

    WG_TESTHELPER_ASSERT_ISREFERENCE(blue, v.getBlue());
  }
};
}
TEST(wg_lclclass_memlike_tpl, Mimic1VarByConstRef)
{
  try
  {
    Mimic1VarByConstRef<int>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
template <typename T1, typename T2, typename T3>
struct Mimic3Vars
{
  static void run()
  {
    T1 force = 0;
    T2 const mass = 10;
    T3 const velocity = 2;

    WG_LCLCLASS_TPL
    (calculateForce,
      memlike (ref force) (const mass) (const ref velocity)
    )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISNOTCONST_TPL(force);
        WG_TESTHELPER_ASSERT_ISCONST_TPL(mass);
        WG_TESTHELPER_ASSERT_ISCONST_TPL(velocity);

        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T1, force);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T2, mass);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(T3, velocity);
      }
    public:
      T1 const & getForce() const { return force; }
      T2 const & getMass() const { return mass; }
      T3 const & getVelocity() const { return velocity; }
    WG_LCLCLASS_END;

    calculateForce c(force, mass, velocity);

    WG_TESTHELPER_ASSERT_ISREFERENCE(force, c.getForce());
    WG_TESTHELPER_ASSERT_ISNOTREFERENCE(mass, c.getMass());
    WG_TESTHELPER_ASSERT_ISREFERENCE(velocity, c.getVelocity());
  }
};
}
TEST(wg_lclclass_memlike_tpl, Mimic3Vars)
{
  try
  {
    Mimic3Vars<short, int, long>::run();
  }
  WG_GTEST_CATCH
}

namespace
{
struct ignore;

template <typename IGNORED>
struct MimicThisU
{
  MimicThisU()
  {
    WG_LCLCLASS_TPL
    (verifier, memlike (this_) )
      void init()
      {
        WG_TESTHELPER_ASSERT_ISCONST_TPL(this_);
        WG_TESTHELPER_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
          MimicThisU *, this_);
      }
    public:
      BOOST_TYPEOF_TPL(this_) const & getThisU() const { return this_; }
    WG_LCLCLASS_END;

    verifier v(this);

    WG_TESTHELPER_ASSERT_ISREFERENCE(*this, *v.getThisU());
  }
};
}
TEST(wg_lclclass_memlike_tpl, MimicThisU)
{
  try
  {
    MimicThisU<ignore> obj;
  }
  WG_GTEST_CATCH
}
