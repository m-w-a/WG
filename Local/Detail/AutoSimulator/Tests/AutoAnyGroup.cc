#include <gtest/gtest.h>
#include <WG/Local/Detail/AutoSimulator/AutoSimulator.hh>
#include <WG/Local/Detail/AutoSimulator/Tests/Utils.hh>

#include <algorithm>

using namespace ::wg::autosimulator;
using namespace ::wg::autosimulator::detail::test;

TEST(wg_autosimulator_autoanygroup, OneExpr)
{
  ExprGenerator expr;

  bool autosimFlag = false;
#define EXPR (expr.array())
  auto_any_group_t grp = WG_AUTOSIMULATOR_AUTOANYGROUP_ALLOC(EXPR);
  WG_AUTOSIMULATOR_AUTOANYGROUP_INIT(grp, autosimFlag, EXPR);

  EXPECT_FALSE(
    isConst(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)));
  EXPECT_EQ(4, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4]);

  WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4] = 24;
  EXPECT_EQ(24, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4]);
#undef EXPR
}

TEST(wg_autosimulator_autoanygroup, MultiExpr)
{
  ExprGenerator expr;

  bool autosimFlag = false;
#define EXPR \
  (expr.array())        (expr.constArray())     (expr.mutableRValue()) \
  (expr.constRValue())  (expr.mutableLValue())  (expr.constLValue()) \
  (expr.moveonlyMutableRValue()) (expr.moveonlyMutableLValue())

  auto_any_group_t grp = WG_AUTOSIMULATOR_AUTOANYGROUP_ALLOC(EXPR);
  WG_AUTOSIMULATOR_AUTOANYGROUP_INIT(grp, autosimFlag, EXPR);

  {
    EXPECT_FALSE(
      isConst(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)));
    EXPECT_EQ(4, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4]);

    WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4] = 44;
    EXPECT_EQ(44, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4]);
  }

  {
    EXPECT_TRUE(
      isConst(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 1, EXPR)));
    EXPECT_EQ(14, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 1, EXPR)[4]);
  }

  {
    EXPECT_FALSE(
      isConst(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 2, EXPR)));
    EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 2, EXPR).value);

    WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 2, EXPR).value = 22;
    EXPECT_EQ(22, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 2, EXPR).value);
  }

  {
    EXPECT_TRUE(
      isConst(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 3, EXPR)));
    EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 3, EXPR).value);
  }

  {
    EXPECT_FALSE(
      isConst(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 4, EXPR)));
    EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 4, EXPR).value);

    WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 4, EXPR).value = 44;
    EXPECT_EQ(44, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 4, EXPR).value);
  }

  {
    EXPECT_TRUE(
      isConst(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 5, EXPR)));
    EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 5, EXPR).value);
  }

  {
    EXPECT_FALSE(
      isConst(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 6, EXPR)) );
    EXPECT_EQ(121, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 6, EXPR).value);

    WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 6, EXPR).value = 122;
    EXPECT_EQ(122, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 6, EXPR).value);
  }

  {
    EXPECT_FALSE(
      isConst(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 7, EXPR)) );
    EXPECT_EQ(121, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 7, EXPR).value);

    WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 7, EXPR).value = 122;
    EXPECT_EQ(122, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 7, EXPR).value);
  }
#undef EXPR
}
