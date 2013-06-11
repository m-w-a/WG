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
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_IFNONLOCALTYPE_ADDCONST(parsedtype) \
  WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_IFNONLOCALTYPE_ADDCONST_IMPL(parsedtype)

// parsedtype: explicit-or-deduced-type
// Result: a cpp type.
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_IFNONLOCALTYPE_ADDREFERENCE(parsedtype) \
  WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_IFNONLOCALTYPE_ADDREFERENCE_IMPL(parsedtype)

// parsedtype: explicit-or-deduced-type
// Result: a cpp type.
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_IFNOTQUALIFIEDLOCALREF_ADDREFERENCE( \
    parsedtype) \
      WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_IFNOTQUALIFIEDLOCALREF_ADDREFERENCE_IMPL( \
        parsedtype)

// parsedtype: explicit-or-deduced-type
// Result: a cpp type.
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_IFNONLOCALTYPE_ADDCONSTADDREFERENCE( \
  parsedtype) \
    WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_IFNONLOCALTYPE_ADDCONSTADDREFERENCE_IMPL( \
      parsedtype)

//###########
//Impl Macros
//###########

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_IMPL(parsedtype) \
  WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_TRANSFORMIF( \
    parsedtype, \
    WG_PP_IDENTITY, \
    WG_PP_MAP_TO_0_ARG1)

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_IFNONLOCALTYPE_ADDCONST_IMPL(parsedtype) \
  WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_TRANSFORMIF( \
    parsedtype, \
    WG_PP_PARSEDTYPE_NONLOCALTYPE_ADDCONST, \
    WG_PP_PARSEDTYPE_ISNONLOCALTYPE)

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_IFNONLOCALTYPE_ADDREFERENCE_IMPL( \
  parsedtype) \
    WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_TRANSFORMIF( \
      parsedtype, \
      WG_PP_PARSEDTYPE_NONLOCALTYPE_ADDREFERENCE, \
      WG_PP_PARSEDTYPE_ISNONLOCALTYPE)

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_IFNOTQUALIFIEDLOCALREF_ADDREFERENCE_IMPL( \
  parsedtype) \
    BOOST_PP_IIF( \
      WG_PP_TOKENS_STARTWITH_LOCAL(parsedtype), \
      WG_PP_PARSEDTYPE_LOCALTYPE_ADDREFERENCE( \
        WG_PP_TOKENS_LOCAL_VALUE(parsedtype)), \
      BOOST_PP_IIF( \
        WG_PP_TOKENS_STARTWITH_LOCALREF(parsedtype), \
        WG_PP_TOKENS_LOCALREF_VALUE(parsedtype), \
        WG_PP_PARSEDTYPE_NONLOCALTYPE_ADDREFERENCE(parsedtype)))

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_IFNONLOCALTYPE_ADDCONSTADDREFERENCE_IMPL(parsedtype) \
  WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_TRANSFORMIF( \
    parsedtype, \
    WG_PP_PARSEDTYPE_NONLOCALTYPE_ADDCONSTADDREFERENCE, \
    WG_PP_PARSEDTYPE_ISNONLOCALTYPE)

//-----------
//Transforms.
//-----------

#define WG_PP_PARSEDTYPE_NONLOCALTYPE_ADDCONST(nonlocaltype) \
  boost::add_const<WG_PP_IDENTITY(nonlocaltype)>::type

#define WG_PP_PARSEDTYPE_NONLOCALTYPE_ADDREFERENCE(nonlocaltype) \
  boost::add_reference<WG_PP_IDENTITY(nonlocaltype)>::type

#define WG_PP_PARSEDTYPE_LOCALTYPE_ADDREFERENCE(localtype) \
  localtype &

#define WG_PP_PARSEDTYPE_NONLOCALTYPE_ADDCONSTADDREFERENCE(nonlocaltype) \
  boost::add_reference< \
    boost::add_const<WG_PP_IDENTITY(nonlocaltype)>::type \
  >::type

//-----------
//Predicates.
//-----------

#define WG_PP_PARSEDTYPE_ISQUALIFIEDLOCAL(parsedtype) \
  WG_PP_TOKENS_STARTWITH_LOCAL(parsedtype)

#define WG_PP_PARSEDTYPE_ISQUALIFIEDLOCALREF(parsedtype) \
  WG_PP_TOKENS_STARTWITH_LOCALREF(parsedtype)

#define WG_PP_PARSEDTYPE_ISNOTQUALIFIEDLOCALREF(parsedtype) \
  BOOST_PP_NOT(WG_PP_PARSEDTYPE_ISQUALIFIEDLOCALREF(parsedtype))

#define WG_PP_PARSEDTYPE_ISLOCALTYPE(parsedtype) \
  BOOST_PP_OR( \
    WG_PP_PARSEDTYPE_ISQUALIFIEDLOCAL(parsedtype), \
    WG_PP_PARSEDTYPE_ISQUALIFIEDLOCALREF(parsedtype))

#define WG_PP_PARSEDTYPE_ISNONLOCALTYPE(parsedtype) \
  BOOST_PP_NOT(WG_PP_PARSEDTYPE_ISLOCALTYPE(parsedtype))

// transform:
//   a 1-arg function macro that will be applied to the extracted
//   cpp type if ...
// predicate:
//   a 1-arg function macro applied to the parsed type to determine if a
//   transform should take place. predicate should evaluate to 0 or 1.
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_TRANSFORMIF( \
  parsedtype, transform, predicate) \
    BOOST_PP_IIF( \
      predicate(parsedtype), \
      transform, \
      WG_PP_IDENTITY) \
      ( \
        BOOST_PP_IIF( \
          WG_PP_TOKENS_STARTWITH_LOCAL(parsedtype), \
          WG_PP_TOKENS_LOCAL_VALUE(parsedtype), \
          BOOST_PP_IIF( \
            WG_PP_TOKENS_STARTWITH_LOCALREF(parsedtype), \
            WG_PP_TOKENS_LOCALREF_VALUE(parsedtype), \
            parsedtype)) \
      )

#endif //WG_PP_PARSEDTYPE_HH_
