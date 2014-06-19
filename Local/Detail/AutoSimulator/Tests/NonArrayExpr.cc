#include <gtest/gtest.h>
#include <WG/Local/Detail/AutoSimulator/AutoSimulator.hh>
#include <WG/Local/Detail/AutoSimulator/Tests/Utils.hh>

namespace
{

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

TEST(wg_autosimulator, MutableRValueExpr)
{
#define EXPR mutableRValue()
  bool isRvalue = false;
  auto_any_t obj = WG_AUTOSIMULATOR_CAPTURE(EXPR, isRvalue);

  EXPECT_TRUE(detail::test::isConst(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);
#undef EXPR
}

TEST(wg_autosimulator, ConstRValueExpr)
{
#define EXPR constRValue()
  bool isRvalue = false;
  auto_any_t obj = WG_AUTOSIMULATOR_CAPTURE(EXPR, isRvalue);

  EXPECT_TRUE(detail::test::isConst(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);
#undef EXPR
}

TEST(wg_autosimulator, MutableLValueExpr)
{
#define EXPR mutableLValue()
  bool isRvalue = false;
  auto_any_t obj = WG_AUTOSIMULATOR_CAPTURE(EXPR, isRvalue);

  EXPECT_FALSE(detail::test::isConst(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);

  WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value = 12;
  EXPECT_EQ(12, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);
#undef EXPR
}

TEST(wg_autosimulator, ConstLValueExpr)
{
#define EXPR constLValue()
  bool isRvalue = false;
  auto_any_t obj = WG_AUTOSIMULATOR_CAPTURE(EXPR, isRvalue);

  EXPECT_TRUE(detail::test::isConst(WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR)));
  EXPECT_EQ(11, WG_AUTOSIMULATOR_AUTOANY_VALUE(obj, EXPR).value);
#undef EXPR
}
