#ifndef WG_PP_VARDCLNIMPLICIT_HH_
#define WG_PP_VARDCLNIMPLICIT_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/Keywords.hh>
#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_pointer.hpp>

//###########
//Public APIs
//###########

// Expands to the following:
//   (parsed-deduced-type) (var-name)
//
// (For definition of terms see SymbolTable documentation.)
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
    WG_PP_VARDCLNIMPLICIT_TUPLIZE_IMPL4( \
      addconst, \
      addref, \
      BOOST_PP_IIF( \
        WG_PP_TOKENS_STARTWITH_THISU(var), 1, 0), \
      var)

#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_IMPL4( \
  addconst, addref, isthisu, var) \
    ( BOOST_PP_CAT( \
        WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_, \
        BOOST_PP_CAT(BOOST_PP_CAT(addconst, addref), isthisu)) (var) ) \
    (var)

#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_000(bvar) \
  WG_PP_DEDUCEDTYPE BOOST_TYPEOF(bvar)
#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_010(bvar) \
  WG_PP_DEDUCEDTYPE boost::add_reference< BOOST_TYPEOF(bvar) >::type
#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_100(bvar) \
  WG_PP_DEDUCEDTYPE boost::add_const< BOOST_TYPEOF(bvar) >::type
#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_110(bvar) \
  WG_PP_DEDUCEDTYPE \
    boost::add_reference<boost::add_const< BOOST_TYPEOF(bvar) >::type>::type
#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_001(bvar) \
  WG_PP_DEDUCEDTYPE BOOST_TYPEOF(this)
#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_011(bvar) \
  WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_ERRMSG()
#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_101(bvar) \
  WG_PP_DEDUCEDTYPE \
    boost::add_const< \
      boost::add_pointer< \
        boost::add_const< \
          BOOST_TYPEOF(*this) >::type >::type >::type
#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_111(bvar) \
  WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_ERRMSG()

#define WG_PP_VARDCLNIMPLICIT_TUPLIZE_TYPE_ERRMSG() \
  BOOST_PP_ASSERT_MSG( \
    0, \
    "ERROR: ref keyword cannot be used in conjunction with this_ keyword.")

#endif //WG_PP_VARDCLNIMPLICIT_HH_
