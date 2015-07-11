#include <gtest/gtest.h>
#include <WG/Local/Tests/Utils/Trilean.hh>

using namespace ::wg::lcl::test;

TEST(wg_tests_utils_trilean, DefaultCtor)
{
  Trilean t;
  EXPECT_EQ(Trilean::Undefined, t);
}

TEST(wg_tests_utils_trilean, OnArgCtor)
{
  // Undefined
  {
    Trilean t(Trilean::Undefined);
    EXPECT_EQ(Trilean::Undefined, t);
  }

  // True
  {
    Trilean t(Trilean::True);
    EXPECT_EQ(Trilean::True, t);
  }

  // False
  {
    Trilean t(Trilean::False);
    EXPECT_EQ(Trilean::False, t);
  }
}

TEST(wg_tests_utils_trilean, Equality)
{
  // Undefined
  {
    Trilean t(Trilean::Undefined);
    EXPECT_TRUE(Trilean::Undefined == t);
  }

  // True
  {
    Trilean t(Trilean::True);
    EXPECT_TRUE(Trilean::True == t);
  }

  // False
  {
    Trilean t(Trilean::False);
    EXPECT_TRUE(Trilean::False == t);
  }
}

TEST(wg_tests_utils_trilean, Inequality)
{
  // Undefined
  {
    Trilean t(Trilean::Undefined);
    EXPECT_FALSE(Trilean::Undefined != t);
  }

  // True
  {
    Trilean t(Trilean::True);
    EXPECT_FALSE(Trilean::True != t);
  }

  // False
  {
    Trilean t(Trilean::False);
    EXPECT_FALSE(Trilean::False != t);
  }
}
