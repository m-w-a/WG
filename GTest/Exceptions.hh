#ifndef WG_GTEST_EXCEPTIONS_HH_
#define WG_GTEST_EXCEPTIONS_HH_

#include <gtest/gtest.h>

//----------
//Public API
//----------

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