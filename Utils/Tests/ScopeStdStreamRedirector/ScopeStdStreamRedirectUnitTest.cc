#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <WG/Utils/ScopeStdStreamRedirector.hh>

using namespace WG::Utils;

TEST(wg_utils, cout_redirects)
{
  std::ostringstream oss;
  ScopeStdStreamRedirector(std::cout, oss.rdbuf());
  
  char testMsg[] = "Hello World!\n";
  
  std::cout << testMsg;
  EXPECT_STREQ(oss.str(), testMsg);
}

TEST(wg_utils, cin_redirects)
{
  std::istringstream iss;
  ScopeStdStreamRedirector(std::cin, iss.rdbuf());
  
  char testMsg[] = "Hello World!\n";
  
  testMsg >> std::cin;
  EXPECT_STREQ(iss.str(), testMsg);
}

TEST(wg_utils, redirects_in_scope_only)
{
  std::ostringstream strmToRedirect;
  
  {
    std::ostringstream oss;
    ScopeStdStreamRedirector(strmToRedirect, oss.rdbuf());
    
    char testMsg[] = "Hello World!\n";
    
    strmToRedirect << testMsg;
    EXPECT_STREQ(oss.str(), testMsg);
  }
  
  char testMsg[] = "Hola Mundo!";
  
  strmToRedirect << testMsg;
  EXPECT_STREQ(strmToRedirect.str(), testMsg);
}

TEST(wg_utils, nullstreambuf)
{
  std::ostringstream strmToRedirect;
  ScopeStdStreamRedirector(strmToRedirect, getNullStreambuf());
  
  char testMsg[] = "Hello World!\n";
  
  strmToRedirect << testMsg;
  EXPECT_STREQ(strmToRedirect.str(), "");
}