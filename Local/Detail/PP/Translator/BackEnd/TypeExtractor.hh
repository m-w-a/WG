#ifndef WG_PP_PARSEDTYPE_HH_
#define WG_PP_PARSEDTYPE_HH_

#include <boost/preprocessor.hpp>
#include <boost/call_traits.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Translator/Keywords.hh>
#include <WG/Local/Detail/PP/Translator/Utils.hh>

//----------------------------------------------------------------------------//
// This file contains utilities for extracting the true cpp type from the parsed
// types found in the symbol table.
//----------------------------------------------------------------------------//

//###########
//Public APIs
//###########

#define WG_PP_PARSEDTYPE_ISLOCALTYPE(parsedtype) \
  WG_PP_PARSEDTYPE_ISLOCALTYPE_IMPL(parsedtype)

// parsedlocaltype: parsed-local-type
// Result: local-nonconst-nonref-type
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_PARSEDTYPE_LOCALTYPE_OPERAND(parsedlocaltype) \
  WG_PP_PARSEDTYPE_LOCALTYPE_PARSE(parsedlocaltype, 0)

// parsedtype: parsed-explicit-or-deduced-type
// Result: a cpp type.
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(parsedtype) \
  WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_IMPL(parsedtype)

// parsedtype: parsed-explicit-or-deduced-type
// Result:
//   1) if type non-local: boost::call_traits<extracted-type>::type
//   2) else:
//     1) if C++03: "extracted-local-type const &", else:
//     2) boost::call_traits<extracted-type>::type
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AS_CALLTRAITSPARAMTYPE( \
 parsedtype, istpl) \
   WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AS_CALLTRAITSPARAMTYPE_IMPL(parsedtype, istpl)

//###########
//Impl Macros
//###########

//-----
//Utils
//-----

#define WG_PP_PARSEDTYPE_EXPAND1(x) x

#define WG_PP_PARSEDTYPE_ISLOCALTYPE_IMPL(parsedtype) \
  BOOST_PP_IIF( \
    WG_PP_KEYWORDS_STARTSWITH_LCLTYPE(parsedtype), \
    1, \
    0)

// elem: 0 or 1.
// Result:
//  local type operand or lib-type-qualifier-seq, depending on whether
//  elem was 0 or 1 respectively.
#define WG_PP_PARSEDTYPE_LOCALTYPE_PARSE(parsedtype, elem) \
  WG_PP_PARSEDTYPE_EXPAND1( \
    WG_PP_PARSEDTYPE_LOCALTYPE_PARSE2 \
    BOOST_PP_LPAREN() \
      WG_PP_KEYWORDS_ADDCOMMAAFTER_LCLTYPETUPLE(parsedtype) \
      BOOST_PP_EMPTY BOOST_PP_COMMA() \
      elem \
    BOOST_PP_RPAREN() )

#define WG_PP_PARSEDTYPE_LOCALTYPE_PARSE2( \
  lcltypetuple, prefixed_qualseq, elem) \
    BOOST_PP_IIF( \
      elem, \
      prefixed_qualseq, \
      WG_PP_KEYWORDS_LCLTYPE_OPERAND(lcltypetuple) BOOST_PP_EMPTY) ()

//-------------------------------
//WG_PP_PARSEDTYPE_EXTRACTCPPTYPE
//-------------------------------

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_IMPL(parsedtype) \
  BOOST_PP_IIF( \
    WG_PP_PARSEDTYPE_ISLOCALTYPE(parsedtype), \
    WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_LOCAL, \
    WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_NONLOCAL) (parsedtype)

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_NONLOCAL(parsedtype) \
  BOOST_PP_TUPLE_ELEM(1, 0, WG_PP_KEYWORDS_EAT_HEADKEYWORD(parsedtype))

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_LOCAL(parsedtype) \
  WG_PP_PARSEDTYPE_LOCALTYPE_OPERAND(parsedtype) \
  BOOST_PP_CAT( \
    WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_LOCAL, \
    BOOST_PP_SEQ_CAT( \
      (_) WG_PP_PARSEDTYPE_LOCALTYPE_PARSE(parsedtype, 1)) )

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_LOCAL_
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_LOCAL_const const
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_LOCAL_ref &
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_LOCAL_constref const &

//------------------------------------------------------
//WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AS_CALLTRAITSPARAMTYPE
//------------------------------------------------------

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AS_CALLTRAITSPARAMTYPE_IMPL( \
  parsedtype, istpl) \
    BOOST_PP_IIF( \
      WG_PP_PARSEDTYPE_ISLOCALTYPE(parsedtype), \
      WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AS_CALLTRAITSPARAMTYPE_LOCAL, \
      WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AS_CALLTRAITSPARAMTYPE_NONLOCAL) \
    (parsedtype, istpl)

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AS_CALLTRAITSPARAMTYPE_NONLOCAL( \
  parsedtype, istpl) \
    WG_PP_TRNSLTR_UTILS_ADDTYPENAME(istpl) \
    boost::call_traits \
    < \
      WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_NONLOCAL(parsedtype) \
    >::param_type

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
  #define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AS_CALLTRAITSPARAMTYPE_LOCAL( \
    parsedtype, istpl) \
      WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE_LOCAL( \
        parsedtype, istpl)
#else
  #define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AS_CALLTRAITSPARAMTYPE_LOCAL( \
    parsedtype, istpl) \
      WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AS_CALLTRAITSPARAMTYPE_NONLOCAL( \
        /* Put arg into correct form by mimicking non-local type. */ \
        type( WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_LOCAL(parsedtype) ), \
        istpl)
#endif

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE_LOCAL( \
  parsedtype, istpl) \
    WG_PP_PARSEDTYPE_LOCALTYPE_OPERAND(parsedtype) \
    BOOST_PP_CAT( \
      WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE_LOCAL, \
      BOOST_PP_SEQ_CAT( \
        (_) WG_PP_PARSEDTYPE_LOCALTYPE_PARSE(parsedtype, 1)) )

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE_LOCAL_ const &
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE_LOCAL_const const &
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE_LOCAL_ref &
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE_LOCAL_constref const &

#endif //WG_PP_PARSEDTYPE_HH_
