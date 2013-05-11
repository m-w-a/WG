#include <gtest/gtest.h>
#include <WG/GTest/Exceptions.hh>
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include "RedirectEventListener.hh"

using namespace WG::GTEST::UnitTest;

TEST(wg_gtest, catch_okIfNoThrow)
{
  try
  {
    int const var = 10;
    EXPECT_EQ(10, var);
  }
  WG_GTEST_CATCH
}

TEST(wg_gtest, catch_okIfThrowsStdException)
{
  struct GTestEventListener : public ::testing::EmptyTestEventListener
  {
    virtual ~GTestEventListener() {}
    virtual void OnTestPartResult(
      const ::testing::TestPartResult& test_part_result)
    {
      m_TestPartResultMsg = test_part_result.message();
    }

    std::string const & testPartResultMsg() const
    {
      return m_TestPartResultMsg;
    }

    std::string m_TestPartResultMsg;
  } gtestLstnr;

  RedirectEventListenerInstance::get()->registerTargetEventListener(gtestLstnr);
  char const * errMsg = __FILE__;
  try
  {
    throw std::domain_error(errMsg);
  }
#undef ADD_FAILURE
#define ADD_FAILURE() GTEST_SUCCEED()
  WG_GTEST_CATCH
#undef ADD_FAILURE
#define ADD_FAILURE() GTEST_NONFATAL_FAILURE_("Failed")
  RedirectEventListenerInstance::get()->unregisterTargetEventListener();

  EXPECT_NE(
    std::string::npos,
    gtestLstnr.testPartResultMsg().rfind(errMsg));
}

TEST(wg_gtest, catch_okIfThrowsNonStdException)
{
  struct GTestEventListener : public ::testing::EmptyTestEventListener
  {
    virtual ~GTestEventListener() {}
    virtual void OnTestPartResult(
      const ::testing::TestPartResult& test_part_result)
    {
      m_TestPartResultMsg = test_part_result.message();
    }

    std::string const & testPartResultMsg() const
    {
      return m_TestPartResultMsg;
    }

    std::string m_TestPartResultMsg;
  } gtestLstnr;

  RedirectEventListenerInstance::get()->registerTargetEventListener(gtestLstnr);
  try
  {
    struct NonStdException {};
    throw NonStdException();
  }
#undef ADD_FAILURE
#define ADD_FAILURE() GTEST_SUCCEED()
  WG_GTEST_CATCH
#undef ADD_FAILURE
#define ADD_FAILURE() GTEST_NONFATAL_FAILURE_("Failed")
  RedirectEventListenerInstance::get()->unregisterTargetEventListener();

  std::string const expectedMsgEnding("Unexpected exception.");
  EXPECT_EQ(
    gtestLstnr.m_TestPartResultMsg.rfind(expectedMsgEnding) + expectedMsgEnding.size(),
    gtestLstnr.m_TestPartResultMsg.size());
}
