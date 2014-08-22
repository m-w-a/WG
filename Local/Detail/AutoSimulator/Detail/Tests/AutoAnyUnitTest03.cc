#include <gtest/gtest.h>
#include <WG/Local/Detail/AutoSimulator/Detail/AutoAny.hh>

namespace
{
typedef ::wg::autosimulator::detail::auto_any const & auto_any_t;

struct ExpressionCategory
{
  enum Type
  {
    MutableRValue,
    ArrayOrMutableLValue,
    ConstNonArrayLValueOrConstRValue
  };
};

ExpressionCategory::Type expressionCategory(
  ::wg::autosimulator::detail::expr_category_mutable_rvalue)
{
  return ExpressionCategory::MutableRValue;
}

ExpressionCategory::Type expressionCategory(
  ::wg::autosimulator::detail::expr_category_array_or_mutable_lvalue)
{
  return ExpressionCategory::ArrayOrMutableLValue;
}

ExpressionCategory::Type expressionCategory(
  ::wg::autosimulator::detail::expr_category_const_nonarray_lvalue_or_const_rvalue)
{
  return ExpressionCategory::ConstNonArrayLValueOrConstRValue;
}

struct Cntnr {};
typedef Cntnr ArrayType[5];

Cntnr & mutableNonArrayLValue()
{
  static Cntnr toRet;
  return toRet;
}

Cntnr const & constNonArrayLValue()
{
  return mutableNonArrayLValue();
}

ArrayType & mutableArrayLValue()
{
  static ArrayType toRet;
  return toRet;
}

ArrayType const & constArrayLValue()
{
  return mutableArrayLValue();
}

Cntnr mutableRValue()
{
  return Cntnr();
}

Cntnr const constRValue()
{
  return Cntnr();
}

}

TEST(wg_autosimulator_detail_autoany_cpp03, MutableNonArrayLValue)
{
#define EXPR mutableNonArrayLValue()
  bool autosimFlag = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, autosimFlag);

  EXPECT_FALSE(WG_AUTOSIMULATOR_DETAIL_AUTOANY_ISRVALUE(obj, EXPR));
  EXPECT_EQ(
    ExpressionCategory::ArrayOrMutableLValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_cpp03, ConstNonArrayLValue)
{
#define EXPR constNonArrayLValue()
  bool autosimFlag = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, autosimFlag);

  EXPECT_FALSE(WG_AUTOSIMULATOR_DETAIL_AUTOANY_ISRVALUE(obj, EXPR));
  EXPECT_EQ(
    ExpressionCategory::ConstNonArrayLValueOrConstRValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_cpp03, MutableArrayLValue)
{
#define EXPR mutableArrayLValue()
  bool autosimFlag = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, autosimFlag);

  EXPECT_FALSE(WG_AUTOSIMULATOR_DETAIL_AUTOANY_ISRVALUE(obj, EXPR));
  EXPECT_EQ(
    ExpressionCategory::ArrayOrMutableLValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_cpp03, ConstArrayLValue)
{
#define EXPR constArrayLValue()
  bool autosimFlag = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, autosimFlag);

  EXPECT_FALSE(WG_AUTOSIMULATOR_DETAIL_AUTOANY_ISRVALUE(obj, EXPR));
  EXPECT_EQ(
    ExpressionCategory::ArrayOrMutableLValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_cpp03, MutableRValue)
{
#define EXPR mutableRValue()
  bool autosimFlag = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, autosimFlag);

  EXPECT_TRUE(WG_AUTOSIMULATOR_DETAIL_AUTOANY_ISRVALUE(obj, EXPR));
  EXPECT_EQ(
    ExpressionCategory::MutableRValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}

TEST(wg_autosimulator_detail_autoany_cpp03, ConstRValue)
{
#define EXPR constRValue()
  bool autosimFlag = false;
  auto_any_t obj =
    WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CAPTURE(EXPR, autosimFlag);

  EXPECT_TRUE(WG_AUTOSIMULATOR_DETAIL_AUTOANY_ISRVALUE(obj, EXPR));
  EXPECT_EQ(
    ExpressionCategory::ConstNonArrayLValueOrConstRValue,
    expressionCategory(WG_AUTOSIMULATOR_DETAIL_AUTOANY_EXPR_CATEGORY(EXPR)) );
#undef EXPR
}
