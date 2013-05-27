#ifndef WG_PP_PARSEDTYPE_HH_
#define WG_PP_PARSEDTYPE_HH_

#include <boost/preprocessor.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <WG/Local/Detail/PP.hh>
#include <WG/Local/Detail/Keywords.hh>

//###########
//Public APIs
//###########

// parsedtype: explicit-or-deduced-type
// Result: a cpp type.
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(parsedtype) \
  WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_IMPL(parsedtype)

// Result: a cpp type.
#define WG_PP_PARSEDTYPE_IFNONLOCAL_ADDCONST(parsedtype) \
  WG_PP_PARSEDTYPE_IFNONLOCAL_ADDCONST_IMPL(parsedtype)

// Result: a cpp type.
#define WG_PP_PARSEDTYPE_IFNONLOCAL_ADDREFERENCE(parsedtype) \
  WG_PP_PARSEDTYPE_IFNONLOCAL_ADDREFERENCE_IMPL(parsedtype)

// Result: a cpp type.
#define WG_PP_PARSEDTYPE_IFNONLOCAL_ADDCONSTADDREFERENCE(parsedtype) \
  WG_PP_PARSEDTYPE_IFNONLOCAL_ADDCONSTADDREFERENCE_IMPL(parsedtype)

//###########
//Impl Macros
//###########

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_IMPL(parsedtype) \
  WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_TRANSFORMIFNONLOCAL( \
    parsedtype, \
    WG_PP_IDENTITY)

#define WG_PP_PARSEDTYPE_ADDCONST(nonlocaltype) \
  boost::add_const<WG_PP_IDENTITY(nonlocaltype)>::type
#define WG_PP_PARSEDTYPE_IFNONLOCAL_ADDCONST_IMPL(parsedtype) \
  WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_TRANSFORMIFNONLOCAL( \
    parsedtype, \
    WG_PP_PARSEDTYPE_ADDCONST)

#define WG_PP_PARSEDTYPE_ADDREFERENCE(nonlocaltype) \
  boost::add_reference<WG_PP_IDENTITY(nonlocaltype)>::type
#define WG_PP_PARSEDTYPE_IFNONLOCAL_ADDREFERENCE_IMPL(parsedtype) \
  WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_TRANSFORMIFNONLOCAL( \
    parsedtype, \
    WG_PP_PARSEDTYPE_ADDREFERENCE)

#define WG_PP_PARSEDTYPE_ADDCONSTADDREFERENCE(nonlocaltype) \
  boost::add_reference< \
    boost::add_const<WG_PP_IDENTITY(nonlocaltype)>::type \
  >::type
#define WG_PP_PARSEDTYPE_IFNONLOCAL_ADDCONSTADDREFERENCE_IMPL(parsedtype) \
  WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_TRANSFORMIFNONLOCAL( \
    parsedtype, \
    WG_PP_PARSEDTYPE_ADDCONSTADDREFERENCE)

// transform: a 1-arg function macro
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_TRANSFORMIFNONLOCAL( \
  parsedtype, transform) \
    BOOST_PP_IIF( \
      WG_PP_TOKENS_STARTWITH_LOCAL(parsedtype), \
      WG_PP_TOKENS_LOCAL_VALUE(parsedtype), \
      BOOST_PP_IIF( \
        WG_PP_TOKENS_STARTWITH_LOCALREF(parsedtype), \
        WG_PP_TOKENS_LOCALREF_VALUE(parsedtype), \
        transform(parsedtype) ))

/*
//Debugging Aide.
#define S1 Foo &
#define S2 local(Bar)
#define S3 localref(Bar &)

WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(S1)
WG_PP_PARSEDTYPE_IFNONLOCAL_ADDCONST(S1)
WG_PP_PARSEDTYPE_IFNONLOCAL_ADDREFERENCE(S1)
WG_PP_PARSEDTYPE_IFNONLOCAL_ADDCONSTADDREFERENCE(S1)

WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(S2)
WG_PP_PARSEDTYPE_IFNONLOCAL_ADDCONST(S2)
WG_PP_PARSEDTYPE_IFNONLOCAL_ADDREFERENCE(S2)
WG_PP_PARSEDTYPE_IFNONLOCAL_ADDCONSTADDREFERENCE(S2)

WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(S3)
WG_PP_PARSEDTYPE_IFNONLOCAL_ADDCONST(S3)
WG_PP_PARSEDTYPE_IFNONLOCAL_ADDREFERENCE(S3)
WG_PP_PARSEDTYPE_IFNONLOCAL_ADDCONSTADDREFERENCE(S3)

//EXPECTED:
Foo &
boost::add_const<Foo &>::type
boost::add_reference<Foo &>::type
boost::add_reference< boost::add_const<Foo &>::type >::type
Bar
Bar
Bar
Bar
Bar &
Bar &
Bar &
Bar &
*/

#endif //WG_PP_PARSEDTYPE_HH_
