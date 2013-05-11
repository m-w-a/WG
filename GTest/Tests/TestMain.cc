#include <gtest/gtest.h>
#include "RedirectEventListener.hh"

using namespace WG::GTEST::UnitTest;

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);

  ::testing::TestEventListeners & gtestLstnrs =
    ::testing::UnitTest::GetInstance()->listeners();

  TestEventListenerSp const spDefaultResultPrinter(
    gtestLstnrs.Release(gtestLstnrs.default_result_printer()));

  RedirectEventListenerInstance::init(spDefaultResultPrinter);
  gtestLstnrs.Append(RedirectEventListenerInstance::get());

  return RUN_ALL_TESTS();
}
