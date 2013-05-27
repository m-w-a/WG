#ifndef WG_PP_PARSEDTYPE_HH_
#define WG_PP_PARSEDTYPE_HH_

#include <boost/preprocessor.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
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
#define WG_PP_PARSEDTYPE_ADDCONST(parsedtype) \
  WG_PP_PARSEDTYPE_ADDCONST_IMPL(parsedtype)

// Result: a cpp type.
#define WG_PP_PARSEDTYPE_ADDREFERENCE(parsedtype) \
  WG_PP_PARSEDTYPE_ADDREFERENCE_IMPL(parsedtype)

// Result: a cpp type.
#define WG_PP_PARSEDTYPE_ADDCONSTADDREFERENCE(parsedtype) \
  WG_PP_PARSEDTYPE_ADDCONSTADDREFERENCE_IMPL(parsedtype)

//###########
//Impl Macros
//###########

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_IMPL(parsedtype) \
  BOOST_PP_IIF( \
    WG_PP_TOKENS_STARTWITH_LOCAL(parsedtype), \
    WG_PP_TOKENS_LOCAL_VALUE(parsedtype), \
    BOOST_PP_IIF( \
      WG_PP_TOKENS_STARTWITH_LOCALREF(parsedtype), \
      WG_PP_TOKENS_LOCALREF_VALUE(parsedtype), \
      parsedtype))
    
#define WG_PP_PARSEDTYPE_ADDCONST_IMPL(parsedtype) \
  BOOST_PP_IIF( \
    WG_PP_TOKENS_STARTWITH_LOCALREF(parsedtype), \
    WG_PP_TOKENS_LOCALREF_VALUE(parsedtype), \
    BOOST_PP_IIF( \
      WG_PP_TOKENS_STARTWITH_LOCAL(parsedtype), \
      WG_PP_TOKENS_LOCAL_VALUE(parsedtype), \
      boost::add_const<WG_PP_IDENTITY(parsedtype)>::type))

#define WG_PP_PARSEDTYPE_ADDREFERENCE_IMPL(parsedtype) \
  BOOST_PP_IIF( \
    WG_PP_TOKENS_STARTWITH_LOCALREF(parsedtype), \
    WG_PP_TOKENS_LOCALREF_VALUE(parsedtype), \
    BOOST_PP_IIF( \
      WG_PP_TOKENS_STARTWITH_LOCAL(parsedtype), \
      WG_PP_TOKENS_LOCAL_VALUE(parsedtype) &, \
      boost::add_reference<WG_PP_IDENTITY(parsedtype)>::type))
      
#define WG_PP_PARSEDTYPE_ADDCONSTADDREFERENCE_IMPL(parsedtype) \
  BOOST_PP_IIF( \
    WG_PP_TOKENS_STARTWITH_LOCALREF(parsedtype), \
    WG_PP_TOKENS_LOCALREF_VALUE(parsedtype), \
    BOOST_PP_IIF( \
      WG_PP_TOKENS_STARTWITH_LOCAL(parsedtype), \
      WG_PP_TOKENS_LOCAL_VALUE(parsedtype), \
      boost::add_reference< \
        boost::add_const<WG_PP_IDENTITY(parsedtype)>::type \
      >::type))

#endif //WG_PP_PARSEDTYPE_HH_
