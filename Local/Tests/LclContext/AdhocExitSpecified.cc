#include <gtest/gtest.h>
#include <boost/config.hpp>
#include <WG/Local/LclContext.hh>

TEST(wg_lclcontext_adhoc, ExitSpecifiedCompletedScope)
{
  bool wasScopeExecuted = false;
  bool didCallExit = false;
  bool wasScopeCompleted = false;

  WG_LCLCONTEXT(
    with_adhoc (ref didCallExit) (ref wasScopeCompleted)
      on_exit(didCallExit = true; this->wasScopeCompleted = scope_completed;) )
  {
    wasScopeExecuted = true;
  }
  WG_LCLCONTEXT_END1

  EXPECT_TRUE(wasScopeExecuted);
  EXPECT_TRUE(didCallExit);
  EXPECT_TRUE(wasScopeCompleted);
}

namespace
{

void returnInducedIncompletedScope(
  bool & wasScopeExecuted,
  bool & didCallExit,
  bool & wasScopeCompleted)
{
  WG_LCLCONTEXT(
    with_adhoc (ref didCallExit) (ref wasScopeCompleted)
      on_exit(didCallExit = true; this->wasScopeCompleted = scope_completed;) )
  {
    wasScopeExecuted = true;
    return;
  }
  WG_LCLCONTEXT_END1
}

}
TEST(wg_lclcontext_adhoc, ExitSpecifiedIncompletedScope)
{
  // GoToInducedIncompletedScope
  {
    bool wasScopeExecuted = false;
    bool didCallExit = false;
    bool wasScopeCompleted = false;

    WG_LCLCONTEXT(
      with_adhoc (ref didCallExit) (ref wasScopeCompleted)
        on_exit(didCallExit = true; this->wasScopeCompleted = scope_completed;) )
    {
      wasScopeExecuted = true;
      goto label1;
    }
    WG_LCLCONTEXT_END1

    label1:

    EXPECT_TRUE(wasScopeExecuted);
    EXPECT_TRUE(didCallExit);
    EXPECT_FALSE(wasScopeCompleted);
  }

  // ReturnInducedIncompletedScope
  {
    bool wasScopeExecuted = false;
    bool didCallExit = false;
    bool wasScopeCompleted = false;

    returnInducedIncompletedScope(
      wasScopeExecuted,
      didCallExit,
      wasScopeCompleted);

    EXPECT_TRUE(wasScopeExecuted);
    EXPECT_TRUE(didCallExit);
    EXPECT_FALSE(wasScopeCompleted);
  }

  // BreakInducedIncompletedScope
  {
    bool wasScopeExecuted = false;
    bool didCallExit = false;
    bool wasScopeCompleted = false;

    int counter = 1;
    while(counter > 0)
    {
      --counter;

      WG_LCLCONTEXT(
        with_adhoc (ref didCallExit) (ref wasScopeCompleted)
          on_exit(didCallExit = true; this->wasScopeCompleted = scope_completed;) )
      {
        wasScopeExecuted = true;
        break;
      }
      WG_LCLCONTEXT_END1
    }

    EXPECT_EQ(0, counter);

    EXPECT_TRUE(wasScopeExecuted);
    EXPECT_TRUE(didCallExit);
    EXPECT_FALSE(wasScopeCompleted);
  }

  // ContinueInducedIncompletedScope
  {
    bool wasScopeExecuted = false;
    bool didCallExit = false;
    bool wasScopeCompleted = false;

    int counter = 1;
    while(counter > 0)
    {
      --counter;

      WG_LCLCONTEXT(
        with_adhoc (ref didCallExit) (ref wasScopeCompleted)
          on_exit(didCallExit = true; this->wasScopeCompleted = scope_completed;) )
      {
        wasScopeExecuted = true;
        continue;
      }
      WG_LCLCONTEXT_END1
    }

    EXPECT_EQ(0, counter);

    EXPECT_TRUE(wasScopeExecuted);
    EXPECT_TRUE(didCallExit);
    EXPECT_FALSE(wasScopeCompleted);
  }

#ifndef BOOST_NO_EXCEPTIONS
  {
    bool wasScopeExecuted = false;
    bool didCallExit = false;
    bool wasScopeCompleted = false;

    bool didthrow = false;
    struct Exception1 {};
    try
    {
      WG_LCLCONTEXT(
        with_adhoc (ref didCallExit) (ref wasScopeCompleted)
          on_exit(didCallExit = true; this->wasScopeCompleted = scope_completed;) )
      {
        wasScopeExecuted = true;
        throw Exception1();
      }
      WG_LCLCONTEXT_END1
    }
    catch(Exception1 const &)
    {
      didthrow = true;
    }

    EXPECT_TRUE(didthrow);

    EXPECT_TRUE(wasScopeExecuted);
    EXPECT_TRUE(didCallExit);
    EXPECT_FALSE(wasScopeCompleted);
  }
#endif // BOOST_NO_EXCEPTIONS
}
