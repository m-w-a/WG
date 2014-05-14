#ifndef WG_GTEST_EXCEPTIONS_HH_
#define WG_GTEST_EXCEPTIONS_HH_

#include <gtest/gtest.h>

//----------
//Public API
//----------

//Rationale:
//  gtest 1.5
//  (Not needed for versions 1.6/1.7)
//
//  http://code.google.com/p/googletest/wiki/V1_5_AdvancedGuide#
//  Suppressing_Pop-ups_Caused_by_Exceptions
//
//  Availability: Windows. GTEST_CATCH_EXCEPTIONS and --gtest_catch_exceptions
//  have no effect on Google Test's behavior on Linux or Mac, even if exceptions
//  are enabled. It is possible to add support for catching exceptions on these
//  platforms, but it is not implemented yet.
#define WG_GTEST_CATCH \
  catch(std::exception const & ex) \
  { \
      WG_GTEST_INTERNAL_REPORTSTDEXCEPTION(ex); \
  } \
  catch(...) \
  { \
      WG_GTEST_INTERNAL_REPORTUNKNOWNEXCEPTION(); \
  }
  
//------------
//Impl Macros.
//------------

#define WG_GTEST_INTERNAL_REPORTUNKNOWNEXCEPTION() \
  ADD_FAILURE() << "Unexpected exception.";

#define WG_GTEST_INTERNAL_REPORTSTDEXCEPTION(ex) \
  ADD_FAILURE() << "Unexpected exception: " << ex.what();
  
#endif //WG_GTEST_EXCEPTIONS_HH_
