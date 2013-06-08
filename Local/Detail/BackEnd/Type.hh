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

// parsedtype: explicit-or-deduced-type
// Result: a cpp type.
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_PARSEDTYPE_IFNONLOCALTYPE_ADDCONST(parsedtype) \
  WG_PP_PARSEDTYPE_IFNONLOCALTYPE_ADDCONST_IMPL(parsedtype)

// parsedtype: explicit-or-deduced-type
// Result: a cpp type.
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_PARSEDTYPE_IFNONLOCALTYPE_ADDREFERENCE(parsedtype) \
  WG_PP_PARSEDTYPE_IFNONLOCALTYPE_ADDREFERENCE_IMPL(parsedtype)

//// parsedtype: explicit-or-deduced-type
//// Result: a cpp type.
////
//// (For definition of terms see SymbolTable documentation.)
//WG_PP_PARSEDTYPE_IFNOTLOCALREFQUALIFIED_ADDREFERENCE

// parsedtype: explicit-or-deduced-type
// Result: a cpp type.
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_PARSEDTYPE_IFNONLOCALTYPE_ADDCONSTADDREFERENCE(parsedtype) \
  WG_PP_PARSEDTYPE_IFNONLOCALTYPE_ADDCONSTADDREFERENCE_IMPL(parsedtype)

//###########
//Impl Macros
//###########

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_IMPL(parsedtype) \
  WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_TRANSFORMIFNONLOCAL( \
    parsedtype, \
    WG_PP_IDENTITY)

#define WG_PP_PARSEDTYPE_ADDCONST(nonlocaltype) \
  boost::add_const<WG_PP_IDENTITY(nonlocaltype)>::type
#define WG_PP_PARSEDTYPE_IFNONLOCALTYPE_ADDCONST_IMPL(parsedtype) \
  WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_TRANSFORMIFNONLOCAL( \
    parsedtype, \
    WG_PP_PARSEDTYPE_ADDCONST)

#define WG_PP_PARSEDTYPE_ADDREFERENCE(nonlocaltype) \
  boost::add_reference<WG_PP_IDENTITY(nonlocaltype)>::type
#define WG_PP_PARSEDTYPE_IFNONLOCALTYPE_ADDREFERENCE_IMPL(parsedtype) \
  WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_TRANSFORMIFNONLOCAL( \
    parsedtype, \
    WG_PP_PARSEDTYPE_ADDREFERENCE)

#define WG_PP_PARSEDTYPE_ADDCONSTADDREFERENCE(nonlocaltype) \
  boost::add_reference< \
    boost::add_const<WG_PP_IDENTITY(nonlocaltype)>::type \
  >::type
#define WG_PP_PARSEDTYPE_IFNONLOCALTYPE_ADDCONSTADDREFERENCE_IMPL(parsedtype) \
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

#endif //WG_PP_PARSEDTYPE_HH_
