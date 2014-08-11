#include <boost/mpl/bool_fwd.hpp>
#include <gtest/gtest.h>
#include <WG/Local/Detail/AutoSimulator/Detail/TypeTraits.hh>
#include <WG/Local/Detail/AutoSimulator/Tests/Utils.hh>

namespace
{

bool boolean(::boost::mpl::true_ *)
{
  return true;
}

bool boolean(::boost::mpl::false_ *)
{
  return false;
}

}

using ::wg::autosimulator::detail::test::ExprGenerator;

TEST(wg_autosimulator_detail_typetraits, IsMutableRValue)
{
  ExprGenerator expr;

  EXPECT_FALSE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLERVALUE(expr.mutableLValue())));
  EXPECT_FALSE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLERVALUE(expr.constLValue())));
  EXPECT_TRUE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLERVALUE(expr.mutableRValue())));
  EXPECT_FALSE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLERVALUE(expr.constRValue())));
}

TEST(wg_autosimulator_detail_typetraits, IsMutableLValue)
{
  ExprGenerator expr;

  EXPECT_TRUE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLELVALUE(expr.mutableLValue())));
  EXPECT_FALSE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLELVALUE(expr.constLValue())));
  EXPECT_FALSE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLELVALUE(expr.mutableRValue())));
  EXPECT_FALSE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLELVALUE(expr.constRValue())));
}

namespace
{

typedef int Arr[5];
typedef Arr const ConstArr;

Arr & arrayRef()
{
  static Arr arr;
  return arr;
}

ConstArr & constArrayRef()
{
  static ConstArr carr = {10, 11, 12, 13, 14};
  return carr;
}

struct Empty {};

}

TEST(wg_autosimulator_detail_typetraits, IsArray)
{
  Arr arr;
  ConstArr carr = {10, 11, 12, 13, 14};
  Empty nonarray;

  EXPECT_TRUE( boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISARRAY(arrayRef())) );
  EXPECT_TRUE( boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISARRAY(constArrayRef())) );
  EXPECT_TRUE( boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISARRAY(arr)) );
  EXPECT_TRUE( boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISARRAY(carr)) );
  EXPECT_FALSE( boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISARRAY(nonarray)) );
}

TEST(wg_autosimulator_detail_typetraits, IsExprConst)
{
  ExprGenerator expr;

  EXPECT_FALSE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISEXPRCONST(expr.mutableLValue())));
  EXPECT_TRUE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISEXPRCONST(expr.constLValue())));
  EXPECT_FALSE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISEXPRCONST(expr.mutableRValue())));
  EXPECT_TRUE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISEXPRCONST(expr.constRValue())));
}
