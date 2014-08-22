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

}

using namespace ::wg::autosimulator;

TEST(wg_autosimulator_autoanygroup_custom, OneExpr)
{
  detail::test::ExprGenerator expr;

  bool autosimFlag = false;
#define EXPR (expr.array())
  CustomBase const & grp =
    WG_AUTOSIMULATOR_AUTOANYGROUP_ALLOC_CUSTOM(CustomBase, EXPR);
  WG_AUTOSIMULATOR_AUTOANYGROUP_INIT(grp, autosimFlag, EXPR);

  EXPECT_FALSE(
    detail::test::isConstLValue(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)));
  EXPECT_EQ(4, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4]);

  WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4] = 15;
  EXPECT_EQ(15, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4]);
#undef EXPR
}

TEST(wg_autosimulator_autoanygroup_custom, MultiExpr)
{
  detail::test::ExprGenerator expr;

  bool autosimFlag = false;
#define EXPR \
  (expr.array())        (expr.constArray())     (expr.mutableRValue()) \
  (expr.constRValue())  (expr.mutableLValue())  (expr.constLValue())

  CustomBase const & grp =
    WG_AUTOSIMULATOR_AUTOANYGROUP_ALLOC_CUSTOM(CustomBase, EXPR);
  WG_AUTOSIMULATOR_AUTOANYGROUP_INIT(grp, autosimFlag, EXPR);

  {
    EXPECT_FALSE(
      detail::test::isConstLValue(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)));
    EXPECT_EQ(4, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4]);

    WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4] = 15;
    EXPECT_EQ(15, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4]);
  }

  {
    EXPECT_TRUE(
      detail::test::isConstLValue(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 1, EXPR)));
    EXPECT_EQ(14, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 1, EXPR)[4]);
  }

  {
    EXPECT_FALSE(
      detail::test::isConstLValue(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 2, EXPR)));
    EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 2, EXPR).value);

    WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 2, EXPR).value = 22;
    EXPECT_EQ(22, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 2, EXPR).value);
  }

  {
    EXPECT_TRUE(
      detail::test::isConstLValue(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 3, EXPR)));
    EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 3, EXPR).value);
  }

  {
    EXPECT_FALSE(
      detail::test::isConstLValue(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 4, EXPR)));
    EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 4, EXPR).value);

    WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 4, EXPR).value = 44;
    EXPECT_EQ(44, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 4, EXPR).value);
  }

  {
    EXPECT_TRUE(
      detail::test::isConstLValue(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 5, EXPR)));
    EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 5, EXPR).value);
  }
#undef EXPR
}
