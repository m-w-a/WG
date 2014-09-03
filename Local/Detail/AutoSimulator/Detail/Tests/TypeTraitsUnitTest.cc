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

#define ISMUTABLERVALUE(x) \
  boolean( \
    WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLERVALUE(x) )

TEST(wg_autosimulator_detail_typetraits, IsMutableRValue)
{
  ExprGenerator expr;

  EXPECT_FALSE( ISMUTABLERVALUE( expr.mutableArray()                  ));
  EXPECT_FALSE( ISMUTABLERVALUE( expr.constArray()             ));

  EXPECT_FALSE( ISMUTABLERVALUE( expr.copyonlyMutableLValue()  ));
  EXPECT_FALSE( ISMUTABLERVALUE( expr.copyonlyConstLValue()    ));
  EXPECT_TRUE(  ISMUTABLERVALUE(  expr.copyonlyMutableRValue()  ));
  EXPECT_FALSE( ISMUTABLERVALUE( expr.copyonlyConstRValue()    ));

  EXPECT_TRUE(  ISMUTABLERVALUE( expr.moveonlyMutableRValue()   ));
  EXPECT_FALSE( ISMUTABLERVALUE( expr.moveonlyMutableLValue()  ));
  EXPECT_FALSE( ISMUTABLERVALUE( expr.moveonlyConstLValue()    ));
}

#define ISMUTABLELVALUE(x) \
  boolean( \
    WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLELVALUE(x) )

TEST(wg_autosimulator_detail_typetraits, IsMutableLValue)
{
  ExprGenerator expr;

  EXPECT_TRUE(  ISMUTABLELVALUE(  expr.mutableArray()                  ));
  EXPECT_FALSE( ISMUTABLELVALUE( expr.constArray()             ));

  EXPECT_TRUE(  ISMUTABLELVALUE(  expr.copyonlyMutableLValue()  ));
  EXPECT_FALSE( ISMUTABLELVALUE( expr.copyonlyConstLValue()    ));
  EXPECT_FALSE( ISMUTABLELVALUE( expr.copyonlyMutableRValue()  ));
  EXPECT_FALSE( ISMUTABLELVALUE( expr.copyonlyConstRValue()    ));

  EXPECT_FALSE( ISMUTABLELVALUE( expr.moveonlyMutableRValue()  ));
  EXPECT_TRUE( ISMUTABLELVALUE( expr.moveonlyMutableLValue()  ));
  EXPECT_FALSE( ISMUTABLELVALUE( expr.moveonlyConstLValue()    ));
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

#define ISEXPRCONST(x) \
  boolean( \
    WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISEXPRCONST(x) )

TEST(wg_autosimulator_detail_typetraits, IsExprConst)
{
  ExprGenerator expr;

  EXPECT_FALSE( ISEXPRCONST( expr.mutableArray()                     ));
  EXPECT_TRUE( ISEXPRCONST( expr.constArray()                 ));

  EXPECT_FALSE( ISEXPRCONST( expr.copyonlyMutableLValue()     ));
  EXPECT_TRUE(  ISEXPRCONST( expr.copyonlyConstLValue()       ));
  EXPECT_FALSE( ISEXPRCONST( expr.copyonlyMutableRValue()     ));
  EXPECT_TRUE(  ISEXPRCONST( expr.copyonlyConstRValue()       ));

  EXPECT_FALSE( ISEXPRCONST( expr.moveonlyMutableRValue()     ));
  EXPECT_FALSE( ISEXPRCONST( expr.moveonlyMutableLValue()     ));
  EXPECT_TRUE(  ISEXPRCONST( expr.moveonlyConstLValue()       ));
}
