#include <gtest/gtest.h>
#include <WG/Local/Tests/LclFunction/Utils/TestLclFunction.hh>
#include <boost/type_traits/is_same.hpp>
#include <WG/Local/Tests/Utils/Utils.hh>

//---------------
//VarBindExplicit
//---------------

namespace
{
template <typename T>
struct VarBindExplicitByValue
{
  static void run()
  {
    T var = 11;

    WG_TEST_LCLFUNCTION_TPL(noop, varbind (type(T) var) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(noop);

      (void)var;
      EXPECT_TRUE(( boost::is_same<WG_LCLFUNCTION_VAR_TYPEOF(var), T>::value ));
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(noop),
      noop);

    noop();
    WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
  }
};
}
TEST(wg_lclfunction_typeof_tpl, VarBindExplicitByValue)
{
  VarBindExplicitByValue<int>::run();
}

namespace
{
template <typename T>
struct VarBindExplicitByRef
{
  static void run()
  {
    T var = 11;

    WG_TEST_LCLFUNCTION_TPL(noop, varbind (type(T &) var) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(noop);

      (void)var;
      EXPECT_TRUE(( boost::is_same<WG_LCLFUNCTION_VAR_TYPEOF(var), T &>::value ));
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(noop),
      noop);

    noop();
    WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
  }
};
}
TEST(wg_lclfunction_typeof_tpl, VarBindExplicitByRef)
{
  VarBindExplicitByRef<int>::run();
}

namespace
{
template <typename T>
struct VarBindExplicitByConst
{
  static void run()
  {
    T var = 11;

    WG_TEST_LCLFUNCTION_TPL(noop, varbind (type(T const) var) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(noop);

      (void)var;
      EXPECT_TRUE(( boost::is_same<WG_LCLFUNCTION_VAR_TYPEOF(var), T const>::value ));
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(noop),
      noop);

    noop();
    WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
  }
};
}
TEST(wg_lclfunction_typeof_tpl, VarBindExplicitByConst)
{
  VarBindExplicitByConst<int>::run();
}

//---------------
//VarBindImplicit
//---------------

namespace
{
template <typename T>
struct VarBindImplicit
{
  static void run()
  {
    T var = 11;

    WG_TEST_LCLFUNCTION_TPL(noop, varbind (var) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(noop);

      (void)var;
      EXPECT_TRUE((
        boost::is_same<WG_LCLFUNCTION_VAR_TYPEOF(var), BOOST_TYPEOF(var)>::value ));
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(noop),
      noop);

    noop();
    WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
  }
};
}
TEST(wg_lclfunction_typeof_tpl, VarBindImplicitByValue)
{
  VarBindImplicit<int>::run();
}

namespace
{
template <typename T>
struct VarBindImplicitByRef
{
  static void run()
  {
    T var = 11;

    WG_TEST_LCLFUNCTION_TPL(noop, varbind (ref var) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(noop);

      (void)var;
      EXPECT_TRUE((
        boost::is_same<WG_LCLFUNCTION_VAR_TYPEOF(var), BOOST_TYPEOF(var) &>::value ));
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(noop),
      noop);

    noop();
    WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
  }
};
}
TEST(wg_lclfunction_typeof_tpl, VarBindImplicitByRef)
{
  VarBindImplicitByRef<int>::run();
}

namespace
{
template <typename T>
struct VarBindImplicitByConst
{
  static void run()
  {
    T var = 11;

    WG_TEST_LCLFUNCTION_TPL(noop, varbind (const var) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(noop);

      (void)var;
      EXPECT_TRUE((
        boost::is_same
        <
          WG_LCLFUNCTION_VAR_TYPEOF(var),
          BOOST_TYPEOF(var) const
        >::value ));
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(noop),
      noop);

    noop();
    WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
  }
};
}
TEST(wg_lclfunction_typeof_tpl, VarBindImplicitByConst)
{
  VarBindImplicitByConst<int>::run();
}


namespace
{
template <typename T>
struct VarBindImplicitByConstRef
{
  static void run()
  {
    T var = 11;

    WG_TEST_LCLFUNCTION_TPL(noop, varbind (const ref var) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(noop);

      (void)var;
      EXPECT_TRUE((
        boost::is_same
        <
          WG_LCLFUNCTION_VAR_TYPEOF(var),
          BOOST_TYPEOF(var) const &
        >::value ));
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(noop),
      noop);

    noop();
    WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
  }
};
}
TEST(wg_lclfunction_typeof_tpl, VarBindImplicitByConstRef)
{
  VarBindImplicitByConstRef<int>::run();
}

//---------------
//VarSetExplicit
//---------------

namespace
{
template <typename T>
struct VarSetExplicitByValue
{
  static void run()
  {
    WG_TEST_LCLFUNCTION_TPL(noop, varset (type(T) var, 5) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(noop);

      (void)var;
      EXPECT_TRUE(( boost::is_same<WG_LCLFUNCTION_VAR_TYPEOF(var), T>::value ));
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(noop),
      noop);

    noop();
    WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
  }
};
}
TEST(wg_lclfunction_typeof_tpl, VarSetExplicitByValue)
{
  VarSetExplicitByValue<int>::run();
}


namespace
{
template <typename T>
struct VarSetExplicitByRef
{
  static void run()
  {
    T var = 11;

    WG_TEST_LCLFUNCTION_TPL(noop, varset (type(T &) var, var) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(noop);

      (void)var;
      EXPECT_TRUE(( boost::is_same<WG_LCLFUNCTION_VAR_TYPEOF(var), T &>::value ));
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(noop),
      noop);

    noop();
    WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
  }
};
}
TEST(wg_lclfunction_typeof_tpl, VarSetExplicitByRef)
{
  VarSetExplicitByRef<int>::run();
}

namespace
{
template <typename T>
struct VarSetExplicitByConst
{
  static void run()
  {
    WG_TEST_LCLFUNCTION_TPL(noop, varset (type(T const) var, 5) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(noop);

      (void)var;
      EXPECT_TRUE(( boost::is_same<WG_LCLFUNCTION_VAR_TYPEOF(var), T const>::value ));
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(noop),
      noop);

    noop();
    WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
  }
};
}
TEST(wg_lclfunction_typeof_tpl, VarSetExplicitByConst)
{
  VarSetExplicitByConst<int>::run();
}

//--------------
//VarSetImplicit
//--------------

namespace
{
template <typename T>
struct VarSetImplicitByValue
{
  static void run()
  {
    WG_TEST_LCLFUNCTION_TPL(noop, varset (var, 11) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(noop);

      (void)var;
      EXPECT_TRUE((
        boost::is_same<WG_LCLFUNCTION_VAR_TYPEOF(var), BOOST_TYPEOF(var)>::value ));
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(noop),
      noop);

    noop();
    WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
  }
};
}
TEST(wg_lclfunction_typeof_tpl, VarSetImplicitByValue)
{
  VarSetImplicitByValue<void>::run();
}

namespace
{
template <typename T>
struct VarSetImplicitByRef
{
  static void run()
  {
    T var = 11;

    WG_TEST_LCLFUNCTION_TPL(noop, varset (ref var, var) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(noop);

      (void)var;
      EXPECT_TRUE((
        boost::is_same<WG_LCLFUNCTION_VAR_TYPEOF(var), BOOST_TYPEOF(var) &>::value ));
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(noop),
      noop);

    noop();
    WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
  }
};
}
TEST(wg_lclfunction_typeof_tpl, VarSetImplicitByRef)
{
  VarSetImplicitByRef<int>::run();
}

namespace
{
template <typename T>
struct VarSetImplicitByConst
{
  static void run()
  {
    WG_TEST_LCLFUNCTION_TPL(noop, varset (const var, 11) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(noop);

      (void)var;
      EXPECT_TRUE((
        boost::is_same
        <
          WG_LCLFUNCTION_VAR_TYPEOF(var),
          BOOST_TYPEOF(var) const
        >::value ));
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(noop),
      noop);

    noop();
    WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
  }
};
}
TEST(wg_lclfunction_typeof_tpl, VarSetImplicitByConst)
{
  VarSetImplicitByConst<int>::run();
}

namespace
{
template <typename T>
struct VarSetImplicitByConstRef
{
  static void run()
  {
    T var = 11;

    WG_TEST_LCLFUNCTION_TPL(noop, varset (const ref var, var) )
    {
      WG_TEST_LCLFUNCTION_MARKCALL(noop);

      (void)var;
      EXPECT_TRUE((
        boost::is_same
        <
          WG_LCLFUNCTION_VAR_TYPEOF(var),
          BOOST_TYPEOF(var) const &
        >::value ));
    }
    WG_TEST_LCLFUNCTION_END;

    WG_TEST_ASSERT_ISSAMETYPE_MODULOCONSTANDREF_TPL(
      WG_LCLFUNCTION_TYPENAME(noop),
      noop);

    noop();
    WG_TEST_LCLFUNCTION_VERIFYCALL(noop);
  }
};
}
TEST(wg_lclfunction_typeof_tpl, VarSetImplicitByConstRef)
{
  VarSetImplicitByConstRef<int>::run();
}
