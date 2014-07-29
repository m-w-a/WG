#include <boost/mpl/bool_fwd.hpp>
#include <gtest/gtest.h>
#include <WG/Local/Detail/AutoSimulator/Detail/TypeTraits.hh>

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

struct Empty
{
};

Empty & mutable_lvalue()
{
  std::cout << "mutable_lvalue";

  static Empty e;
  return e;
}

Empty const & const_lvalue()
{
  std::cout << "const_lvalue";

  static Empty const e;
  return e;
}

Empty mutable_rvalue()
{
  std::cout << "mutable_rvalue";
  return Empty();
}

Empty const const_rvalue()
{
  std::cout << "const_rvalue";
  return Empty();
}

}

using namespace ::wg::autosimulator::detail;

TEST(wg_autosimulator_detail_typetraits, IsMutableRValue)
{
  EXPECT_FALSE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLERVALUE(mutable_lvalue())));
  EXPECT_FALSE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLERVALUE(const_lvalue())));
  EXPECT_TRUE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLERVALUE(mutable_rvalue())));
  EXPECT_FALSE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLERVALUE(const_rvalue())));
}

TEST(wg_autosimulator_detail_typetraits, IsMutableLValue)
{
  EXPECT_TRUE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLELVALUE(mutable_lvalue())));
  EXPECT_FALSE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLELVALUE(const_lvalue())));
  EXPECT_FALSE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLELVALUE(mutable_rvalue())));
  EXPECT_FALSE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISMUTABLELVALUE(const_rvalue())));
}

TEST(wg_autosimulator_detail_typetraits, IsArray)
{
  typedef int Arr[5];
  typedef Arr const CArr;

  Arr arr;
  CArr carr;
  Empty nonarray;

  EXPECT_TRUE( WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISARRAY(arr) );
  EXPECT_TRUE( WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISARRAY(carr) );
  EXPECT_FALSE( WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISARRAY(nonarray) );
}

TEST(wg_autosimulator_detail_typetraits, IsExprConst)
{
  EXPECT_FALSE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISEXPRCONST(mutable_lvalue())));
  EXPECT_TRUE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISEXPRCONST(const_lvalue())));
  EXPECT_FALSE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISEXPRCONST(mutable_rvalue())));
  EXPECT_TRUE(boolean(WG_AUTOSIMULATOR_DETAIL_TYPETRAITS_ISEXPRCONST(const_rvalue())));
}
