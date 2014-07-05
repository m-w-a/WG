#include <gtest/gtest.h>
#include <WG/Local/Detail/AutoSimulator/AutoSimulator.hh>
#include <WG/Local/Detail/AutoSimulator/Tests/Utils.hh>

namespace
{

struct CustomBase
{
  template <typename T>
  void finalize(T &)
  {
  }
};

typedef int A5[5];
typedef A5 const ConstA5;

struct Cntr
{
  Cntr()
  : value(11)
  {
  }

  int value;
};

Cntr mutableRValue()
{
  return Cntr();
}

Cntr const constRValue()
{
  return Cntr();
}

Cntr & mutableLValue()
{
  static Cntr toRet;
  return toRet;
}

Cntr const & constLValue()
{
  static Cntr toRet;
  return toRet;
}

}

using namespace ::wg::autosimulator;

TEST(wg_autosimulator_autoanygroup_custom, OneExpr)
{
  A5 arr = {0, 1, 2, 3, 5};

  bool isRValue = false;
#define EXPR (arr)
  CustomBase const & grp =
    WG_AUTOSIMULATOR_AUTOANYGROUP_ALLOC_CUSTOM(CustomBase, EXPR);
  WG_AUTOSIMULATOR_AUTOANYGROUP_INIT(grp, isRValue, EXPR);

  EXPECT_FALSE(
    detail::test::isConst(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)));
  EXPECT_EQ(5, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4]);

  WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4] = 15;
  EXPECT_EQ(15, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4]);
#undef EXPR
}

TEST(wg_autosimulator_autoanygroup_custom, MultiExpr)
{
  A5 arr = {0, 1, 2, 3, 5};
  ConstA5 carr = {10, 11, 12, 13, 15};

  bool isRValue = false;
#define EXPR \
  (arr)             (carr)              ( mutableRValue() ) \
  ( constRValue() ) ( mutableLValue() ) ( constLValue() )
  CustomBase const & grp =
    WG_AUTOSIMULATOR_AUTOANYGROUP_ALLOC_CUSTOM(CustomBase, EXPR);
  WG_AUTOSIMULATOR_AUTOANYGROUP_INIT(grp, isRValue, EXPR);

  {
    EXPECT_FALSE(
      detail::test::isConst(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)));
    EXPECT_EQ(5, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4]);

    WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4] = 15;
    EXPECT_EQ(15, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4]);
  }

  {
    EXPECT_TRUE(
      detail::test::isConst(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 1, EXPR)));
    EXPECT_EQ(15, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 1, EXPR)[4]);
  }

  {
    EXPECT_TRUE(
      detail::test::isConst(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 2, EXPR)));
    EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 2, EXPR).value);
  }

  {
    EXPECT_TRUE(
      detail::test::isConst(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 3, EXPR)));
    EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 3, EXPR).value);
  }

  {
    EXPECT_FALSE(
      detail::test::isConst(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 4, EXPR)));
    EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 4, EXPR).value);

    WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 4, EXPR).value = 22;
    EXPECT_EQ(22, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 4, EXPR).value);
  }

  {
    EXPECT_TRUE(
      detail::test::isConst(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 5, EXPR)));
    EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 5, EXPR).value);
  }
#undef EXPR
}
