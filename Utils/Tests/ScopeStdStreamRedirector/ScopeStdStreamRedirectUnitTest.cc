#include <iostream>
#include <sstream>
#include <string>
#include <gtest/gtest.h>
#include <WG/Utils/ScopeStdStreamRedirector.hh>

using namespace WG::Utils;

TEST(wg_utils_scopedstdstreamredirector, cout_redirects)
{
  std::ostringstream oss;
  ScopeStdStreamRedirector redirectCout(std::cout, *oss.rdbuf());
  
  char testMsg[] = "Hello World!!";

  std::cout << testMsg;
  EXPECT_STREQ(oss.str().c_str(), testMsg);
}

TEST(wg_utils_scopedstdstreamredirector, cin_redirects)
{
  char testMsg[] = "Hello World!";
  std::istringstream iss(testMsg);

  ScopeStdStreamRedirector redirectCin(std::cin, *iss.rdbuf());

  std::string cinMsgPt1;
  std::string cinMsgPt2;
  std::cin >> cinMsgPt1 >> cinMsgPt2;
  EXPECT_STREQ(cinMsgPt1.c_str(), "Hello");
  EXPECT_STREQ(cinMsgPt2.c_str(), "World!");
}

TEST(wg_utils_scopedstdstreamredirector, redirects_in_scope_only)
{
  std::ostringstream strmToRedirect;
  
  {
    std::ostringstream oss;
    ScopeStdStreamRedirector redirectOStringStream(strmToRedirect, *oss.rdbuf());
    
    char testMsg[] = "Hello World!";
    
    strmToRedirect << testMsg;
    EXPECT_STREQ(oss.str().c_str(), testMsg);
  }
  
  char testMsg[] = "Hola Mundo!";
  
  strmToRedirect << testMsg;
  EXPECT_STREQ(strmToRedirect.str().c_str(), testMsg);
}

TEST(wg_utils_scopedstdstreamredirector, nullstreambuf)
{
  std::ostringstream strmToRedirect;
  ScopeStdStreamRedirector redirectToNull(strmToRedirect, getNullStreambuf());
  
  char testMsg[] = "Hello World!";
  
  strmToRedirect << testMsg;
  EXPECT_STREQ(strmToRedirect.str().c_str(), "");
}
