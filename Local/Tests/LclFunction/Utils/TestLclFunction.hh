#ifndef WG_LOCAL_TESTS_TESTLCLFUNCTION_HH_
#define WG_LOCAL_TESTS_TESTLCLFUNCTION_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/LclFunction.hh>
#include <WG/Local/Tests/LclFunction/Utils/Detail/LclFunctionCallVerifier.hh>
#include <WG/Local/Tests/LclFunction/Utils/Detail/LclFunctionCallRegistrar.hh>

//###########
//Public APIs
//###########

//------------------------------------------------------------------------------//
//Description:
//  Use these macros to ensure that the declared local function is invoked at least
//  once in the test, else the test will fail. This is to ensure that we don't
//  forget to call the local function and generate false positives.
//How to Use:
//  All calls to WG_LCLFUNCTION/_TPL should be replaced with WG_TEST_LCLFUNCTION/_TPL
//  All calls to WG_LCLFUNCTION_END should be replaced with WG_TEST_LCLFUNCTION_END
//  WG_TEST_LCLFUNCTION_MARKCALL should be invoked in the local function body.
//  WG_TEST_LCLFUNCTION_VERIFYCALL should be invoked after the local function
//  has been invoked.
//How it Works:
//  WG_TEST_LCLFUNCTION/_TPL will register the lclfunction_name with a global
//  entity using a local RAII object. If neither WG_TEST_LCLFUNCTION_MARKCALL nor
//  WG_TEST_LCLFUNCTION_VERIFYCALL are invoked using the same lclfunction name
//  then the test will fail.
//------------------------------------------------------------------------------//

#define WG_TEST_LCLFUNCTION(name, spec)  \
  WG_TEST_LCLFUNCTION_IMPL(name, spec)

#define WG_TEST_LCLFUNCTION_TPL(name, spec)  \
  WG_TEST_LCLFUNCTION_TPL_IMPL(name, spec)

#define WG_TEST_LCLFUNCTION_END \
  WG_LCLFUNCTION_END

#define WG_TEST_LCLFUNCTION_MARKCALL(name) \
  WG_TEST_LCLFUNCTION_MARKCALL_IMPL(name)

#define WG_TEST_LCLFUNCTION_VERIFYCALL(name) \
  WG_TEST_LCLFUNCTION_VERIFYCALL_IMPL(name)

//###########
//Impl Macros
//###########

//-----
//Utils
//-----

#define WG_TEST_LCLFUNCTION_ID() wg_test_lclfunction

#define WG_TEST_LCLFUNCTION_VERIFIER_NAME(lclfunction_name) \
  BOOST_PP_CAT( \
    BOOST_PP_CAT(WG_TEST_LCLFUNCTION_ID(), XXX), \
    lclfunction_name)

//------------------------
//WG_TEST_LCLFUNCTION/_TPL
//------------------------

#define WG_TEST_LCLFUNCTION_IMPL(name, spec) \
  WG_TEST_LCLFUNCTION_COMMON(name) \
  WG_LCLFUNCTION(name, spec)

#define WG_TEST_LCLFUNCTION_TPL_IMPL(name, spec) \
  WG_TEST_LCLFUNCTION_COMMON(name) \
  WG_LCLFUNCTION_TPL(name, spec)

#define WG_TEST_LCLFUNCTION_COMMON(name) \
  ::wg::lclfunction::test::lclfunction_call_verifier \
    WG_TEST_LCLFUNCTION_VERIFIER_NAME(name) \
    (BOOST_PP_STRINGIZE(name), __FILE__, __LINE__) ;

//----------------------------
//WG_TEST_LCLFUNCTION_MARKCALL
//----------------------------

#define WG_TEST_LCLFUNCTION_MARKCALL_IMPL(name) \
  ::wg::lclfunction::test::lclfunction_registrar().register_call_for( name );

//------------------------------
//WG_TEST_LCLFUNCTION_VERIFYCALL
//------------------------------

#define WG_TEST_LCLFUNCTION_VERIFYCALL_IMPL(name) \
  WG_TEST_LCLFUNCTION_VERIFIER_NAME(name) . verify_call_to( name );

#endif /* WG_LOCAL_TESTS_TESTLCLFUNCTION_HH_ */
