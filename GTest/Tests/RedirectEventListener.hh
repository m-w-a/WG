#ifndef WG_GTEST_TESTS_REDIRECTEVENTLISTENER_HH_
#define WG_GTEST_TESTS_REDIRECTEVENTLISTENER_HH_

#include <gtest/gtest.h>
#include <memory.hpp>
#include <WG/Utils/ClassMethodDisablers.hh>

namespace WG
{
namespace GTEST
{
namespace UnitTest
{

//----------
//Fwd Dclns.
//----------

class RedirectEventListener;

//--------
//Typedefs
//--------

typedef std::tr1::shared_ptr< ::testing::TestEventListener> TestEventListenerSp;

//-----
//Types
//-----

class RedirectEventListenerInstance
{
public:
  static void init(TestEventListenerSp const spDefaultResultPrinter);
  static RedirectEventListener * get();
private:
  static RedirectEventListener * m_Instance;
};

class RedirectEventListener : public ::testing::TestEventListener
{
public:
  explicit RedirectEventListener(
    TestEventListenerSp const spDefaultResultPrinter);
  virtual ~RedirectEventListener();

  WG_DISABLE_DEFAULT_CTOR(RedirectEventListener);
  WG_DISABLE_COPY_CTOR(RedirectEventListener);
  WG_DISABLE_COPY_ASSIGNMENT(RedirectEventListener);

public:
  void registerTargetEventListener(
    ::testing::TestEventListener & targetLstnr);
  void unregisterTargetEventListener();

  // Fired before any test activity starts.
  virtual void OnTestProgramStart(const ::testing::UnitTest& unit_test);

  // Fired before each iteration of tests starts. There may be more than
  // one iteration if GTEST_FLAG(repeat) is set. iteration is the iteration
  // index, starting from 0.
  virtual void OnTestIterationStart(
    const ::testing::UnitTest& unit_test,
    int iteration);

  // Fired before environment set-up for each iteration of tests starts.
  virtual void OnEnvironmentsSetUpStart(const ::testing::UnitTest& unit_test);

  // Fired after environment set-up for each iteration of tests ends.
  virtual void OnEnvironmentsSetUpEnd(const ::testing::UnitTest& unit_test);

  // Fired before the test case starts.
  virtual void OnTestCaseStart(const ::testing::TestCase& test_case);

  // Fired before the test starts.
  virtual void OnTestStart(const ::testing::TestInfo& test_info);

  // Fired after a failed assertion or a SUCCEED() invocation.
  virtual void OnTestPartResult(
    const ::testing::TestPartResult& test_part_result);

  // Fired after the test ends.
  virtual void OnTestEnd(const ::testing::TestInfo& test_info);

  // Fired after the test case ends.
  virtual void OnTestCaseEnd(const ::testing::TestCase& test_case);

  // Fired before environment tear-down for each iteration of tests starts.
  virtual void OnEnvironmentsTearDownStart(
    const ::testing::UnitTest& unit_test);

  // Fired after environment tear-down for each iteration of tests ends.
  virtual void OnEnvironmentsTearDownEnd(const ::testing::UnitTest& unit_test);

  // Fired after each iteration of tests finishes.
  virtual void OnTestIterationEnd(
    const ::testing::UnitTest& unit_test,
    int iteration);

  // Fired after all test activities have ended.
  virtual void OnTestProgramEnd(const ::testing::UnitTest& unit_test);

private:
  TestEventListenerSp const m_spDefaultResultPrinter;
  ::testing::TestEventListener * m_pTargetEventListener;
};

}
}
}

#endif /* WG_GTEST_TESTS_REDIRECTEVENTLISTENER_HH_ */
