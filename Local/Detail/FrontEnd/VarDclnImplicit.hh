#ifndef WG_PP_VARDCLNIMPLICIT_HH_
#define WG_PP_VARDCLNIMPLICIT_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/Keywords.hh>
#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_const.hpp>

//###########
//Public APIs
//###########

#define WG_PP_VARDCLNIMPLICIT_TUPLIZE(implicitvardcln) \
  WG_PP_VARDCLNIMPLICIT_TUPLIZE_IMPL(implicitvardcln)
  
//###########
//Impl Macros
//###########

// Need to use these instead of BOOST_PP_EXPAND because for some reason the 
//  latter prevents the macro expansion of BOOST_PP_EXPANDs in these macros.
#define WG_PP_VARDCLNIMPLICIT_EXPAND1(x) x
#define WG_PP_VARDCLNIMPLICIT_EXPAND2(x) x

#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_IMPL(implicitvardcln) \
  WG_PP_VARDCLNIMPLICIT_EXPAND1( \
    WG_PP_VARDCLNIMPLICIT_TUPLIZE_IMPL2 \
    BOOST_PP_IIF( \
      WG_PP_TOKENS_STARTWITH_CONST(implicitvardcln), \
      ( 1, WG_PP_TOKENS_EAT_HEADKEYWORD(implicitvardcln) ), \
      ( 0, implicitvardcln ) ))

#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_IMPL2(addconst, implicitvardcln) \
  WG_PP_VARDCLNIMPLICIT_EXPAND2( \
    WG_PP_VARDCLNIMPLICIT_TUPLIZE_IMPL3 \
    BOOST_PP_IIF( \
      WG_PP_TOKENS_STARTWITH_REF(implicitvardcln), \
      ( addconst, 1, WG_PP_TOKENS_EAT_HEADKEYWORD(implicitvardcln)), \
      ( addconst, 0, implicitvardcln )  ))

#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_IMPL3( \
  addconst, addref, var) \
    ( BOOST_PP_CAT( \
      WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_, \
      BOOST_PP_CAT( \
        addconst, \
        addref)) (var) ) \
    (var)

#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_00(bvar) \
  BOOST_TYPEOF(bvar)
#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_01(bvar) \
  boost::add_reference< BOOST_TYPEOF(bvar) >::type
#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_10(bvar) \
  boost::add_const< BOOST_TYPEOF(bvar) >::type
#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_11(bvar) \
  boost::add_reference<boost::add_const< BOOST_TYPEOF(bvar) >::type>::type

/*
//Debugging Aide.
#define VDI1 var1
#define VDI2 ref var2
#define VDI3 const var3
#define VDI4 const ref var4

WG_PP_VARDCLNIMPLICIT_TUPLIZE(VDI1)
WG_PP_VARDCLNIMPLICIT_TUPLIZE(VDI2)
WG_PP_VARDCLNIMPLICIT_TUPLIZE(VDI3)
WG_PP_VARDCLNIMPLICIT_TUPLIZE(VDI4)

//EXPECTED:
//( BOOST_TYPEOF(var4) ) (var4)
//( boost::add_reference< BOOST_TYPEOF(var5) >::type ) (var5)
//( boost::add_const< BOOST_TYPEOF(var6) >::type ) (var6)
//( boost::add_reference<boost::add_const< BOOST_TYPEOF(var7) >::type>::type ) (var7)
*/

#endif //WG_PP_VARDCLNIMPLICIT_HH_
