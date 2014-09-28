#include <vector>
#include <gtest/gtest.h>
#include <boost/utility/addressof.hpp>

#define WG_AUTOSIMULATOR_AUTOANYGROUP_CONFIG_PARAMS_MAX_ARITY 10

#include <WG/Local/Detail/AutoSimulator/AutoSimulator.hh>
#include <WG/Local/Detail/AutoSimulator/Tests/Utils.hh>

namespace
{

struct CustomBase
{
  template <typename T>
  void finalize(T & captured_obj)
  {
    if( captured_objs.empty() )
    {
      EXPECT_FALSE( captured_objs.empty() );
      return;
    }

    EXPECT_EQ( captured_objs.back(), ::boost::addressof(captured_obj) );
    captured_objs.pop_back();
  }

  typedef std::vector<void const *> opaqued_objptr_vec;
  mutable opaqued_objptr_vec captured_objs;
};

}

using namespace ::wg::autosimulator;
using namespace ::wg::autosimulator::detail::test;

TEST(wg_autosimulator_autoanygroup_custom, OneExpr)
{
  ExprGenerator expr;

  bool autosimFlag = false;
#define EXPR (expr.mutableArray())
  CustomBase const & grp =
    WG_AUTOSIMULATOR_AUTOANYGROUP_ALLOC_CUSTOM(CustomBase, EXPR);
  WG_AUTOSIMULATOR_AUTOANYGROUP_INIT(grp, autosimFlag, EXPR);

  grp.captured_objs.push_back(
    ::boost::addressof(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)));

  EXPECT_FALSE(
    isConst(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)));
  EXPECT_EQ(4, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4]);

  WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4] = 15;
  EXPECT_EQ(15, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4]);
#undef EXPR
}

TEST(wg_autosimulator_autoanygroup_custom, MultiExpr1)
{
  ExprGenerator expr;

  bool autosimFlag = false;
#define EXPR \
  (expr.mutableArray())          (expr.constArray())     \
  (expr.copyonlyMutableRValue()) (expr.copyonlyConstRValue())  \
  (expr.copyonlyMutableLValue()) (expr.copyonlyConstLValue()) \
  (expr.moveonlyMutableRValue()) (expr.moveonlyMutableLValue()) \
  (expr.moveonlyConstLValue())

  CustomBase const & grp =
    WG_AUTOSIMULATOR_AUTOANYGROUP_ALLOC_CUSTOM(CustomBase, EXPR);
  WG_AUTOSIMULATOR_AUTOANYGROUP_INIT(grp, autosimFlag, EXPR);

  grp.captured_objs.push_back(
    ::boost::addressof(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)));
  grp.captured_objs.push_back(
    ::boost::addressof(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 1, EXPR)));
  grp.captured_objs.push_back(
    ::boost::addressof(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 2, EXPR)));
  grp.captured_objs.push_back(
    ::boost::addressof(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 3, EXPR)));
  grp.captured_objs.push_back(
    ::boost::addressof(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 4, EXPR)));
  grp.captured_objs.push_back(
    ::boost::addressof(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 5, EXPR)));
  grp.captured_objs.push_back(
    ::boost::addressof(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 6, EXPR)));
  grp.captured_objs.push_back(
    ::boost::addressof(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 7, EXPR)));
  grp.captured_objs.push_back(
    ::boost::addressof(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 8, EXPR)));

  {
    EXPECT_FALSE(
      isConst(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)));
    EXPECT_EQ(4, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4]);

    WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4] = 15;
    EXPECT_EQ(15, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)[4]);
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

  {
    EXPECT_TRUE(
      isConst(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 8, EXPR)) );
    EXPECT_EQ(121, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 8, EXPR).value);
  }
#undef EXPR
}

TEST(wg_autosimulator_autoanygroup_custom, MultiExpr2)
{
  ExprGenerator expr;

  bool autosimFlag = false;
#define EXPR \
  (expr.copymoveMutableRValue()) (expr.copymoveConstRValue()) \
  (expr.copymoveMutableLValue()) (expr.copymoveConstLValue())

  CustomBase const & grp =
    WG_AUTOSIMULATOR_AUTOANYGROUP_ALLOC_CUSTOM(CustomBase, EXPR);
  WG_AUTOSIMULATOR_AUTOANYGROUP_INIT(grp, autosimFlag, EXPR);

  grp.captured_objs.push_back(
    ::boost::addressof(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)));
  grp.captured_objs.push_back(
    ::boost::addressof(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 1, EXPR)));
  grp.captured_objs.push_back(
    ::boost::addressof(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 2, EXPR)));
  grp.captured_objs.push_back(
    ::boost::addressof(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 3, EXPR)));

  {
    EXPECT_FALSE(
      isConst(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR)) );
    EXPECT_EQ(345, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR).value);

    WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR).value = 346;
    EXPECT_EQ(346, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 0, EXPR).value);
  }

  {
    EXPECT_TRUE(
      isConst(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 1, EXPR)) );
    EXPECT_EQ(345, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 1, EXPR).value);
  }

  {
    EXPECT_FALSE(
      isConst(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 2, EXPR)) );
    EXPECT_EQ(345, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 2, EXPR).value);

    WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 2, EXPR).value = 346;
    EXPECT_EQ(346, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 2, EXPR).value);
  }

  {
    EXPECT_TRUE(
      isConst(WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 3, EXPR)) );
    EXPECT_EQ(345, WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE(grp, 3, EXPR).value);
  }
#undef EXPR
}
