#include "RedirectEventListener.hh"

#define WG_GTEST_UNITTEST_REDIRECT(func_call) \
  if(m_pTargetEventListener) \
  { \
    m_pTargetEventListener->func_call; \
  } \
  else \
  { \
    m_spDefaultResultPrinter->func_call; \
  }

namespace WG
{
namespace GTEST
{
namespace UnitTest
{

//-----------------------------
//RedirectEventListenerInstance
//-----------------------------

void RedirectEventListenerInstance::init(
  TestEventListenerSp const spDefaultResultPrinter)
{
  m_Instance = new RedirectEventListener(spDefaultResultPrinter);
}

RedirectEventListener * RedirectEventListenerInstance::get()
{
  return m_Instance;
}

RedirectEventListener * RedirectEventListenerInstance::m_Instance = 0;

//---------------------
//RedirectEventListener
//---------------------

RedirectEventListener::RedirectEventListener(
  TestEventListenerSp const spDefaultResultPrinter)
: m_spDefaultResultPrinter(spDefaultResultPrinter),
  m_pTargetEventListener(0)
{
}

RedirectEventListener::~RedirectEventListener()
{
  m_pTargetEventListener = 0;
}

void RedirectEventListener::registerTargetEventListener(
  ::testing::TestEventListener & targetLstnr)
{
  m_pTargetEventListener = &targetLstnr;
}

void RedirectEventListener::unregisterTargetEventListener()
{
  m_pTargetEventListener = 0;
}

void RedirectEventListener::OnTestProgramStart(
  const ::testing::UnitTest& unit_test)
{
  WG_GTEST_UNITTEST_REDIRECT(OnTestProgramStart(unit_test));
}

void RedirectEventListener::OnTestIterationStart(
    const ::testing::UnitTest& unit_test,
    int iteration)
{
  WG_GTEST_UNITTEST_REDIRECT(OnTestIterationStart(unit_test, iteration));
}

void RedirectEventListener::OnEnvironmentsSetUpStart(
  const ::testing::UnitTest& unit_test)
{
  WG_GTEST_UNITTEST_REDIRECT(OnEnvironmentsSetUpStart(unit_test));
}

void RedirectEventListener::OnEnvironmentsSetUpEnd(
  const ::testing::UnitTest& unit_test)
{
  WG_GTEST_UNITTEST_REDIRECT(OnEnvironmentsSetUpEnd(unit_test));
}

void RedirectEventListener::OnTestCaseStart(
  const ::testing::TestCase& test_case)
{
  WG_GTEST_UNITTEST_REDIRECT(OnTestCaseStart(test_case));
}

void RedirectEventListener::OnTestStart(const ::testing::TestInfo& test_info)
{
  WG_GTEST_UNITTEST_REDIRECT(OnTestStart(test_info));
}

void RedirectEventListener::OnTestPartResult(
  const ::testing::TestPartResult& test_part_result)
{
  WG_GTEST_UNITTEST_REDIRECT(OnTestPartResult(test_part_result));
}

void RedirectEventListener::OnTestEnd(const ::testing::TestInfo& test_info)
{
  WG_GTEST_UNITTEST_REDIRECT(OnTestEnd(test_info));
}

void RedirectEventListener::OnTestCaseEnd(const ::testing::TestCase& test_case)
{
  WG_GTEST_UNITTEST_REDIRECT(OnTestCaseEnd(test_case));
}

void RedirectEventListener::OnEnvironmentsTearDownStart(
  const ::testing::UnitTest& unit_test)
{
  WG_GTEST_UNITTEST_REDIRECT(OnEnvironmentsTearDownStart(unit_test));
}

void RedirectEventListener::OnEnvironmentsTearDownEnd(
  const ::testing::UnitTest& unit_test)
{
  WG_GTEST_UNITTEST_REDIRECT(OnEnvironmentsTearDownEnd(unit_test));
}

void RedirectEventListener::OnTestIterationEnd(
  const ::testing::UnitTest& unit_test,
  int iteration)
{
  WG_GTEST_UNITTEST_REDIRECT(OnTestIterationEnd(unit_test, iteration));
}

void RedirectEventListener::OnTestProgramEnd(
  const ::testing::UnitTest& unit_test)
{
  WG_GTEST_UNITTEST_REDIRECT(OnTestProgramEnd(unit_test));
}

}
}
}
