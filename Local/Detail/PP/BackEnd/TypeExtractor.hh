#ifndef WG_PP_PARSEDTYPE_HH_
#define WG_PP_PARSEDTYPE_HH_

#include <boost/preprocessor.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Keywords.hh>

//----------------------------------------------------------------------------//
// This file contains utilities for extracting the true cpp type from the parsed
// types found in the symbol table.
//----------------------------------------------------------------------------//

//###########
//Public APIs
//###########

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
//   a cpp type that has the emulated metafunction add_reference applied to it
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDREFERENCE(parsedtype, istpl) \
  WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDREFERENCE_IMPL(parsedtype, istpl)

// parsedtype: parsed-explicit-or-deduced-type
// Result:
//   a cpp type that has the emulated metafunction add_const followed by the
//   emulated metafunction add_reference applied to it
//
// (For definition of terms see SymbolTable documentation.)
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE( \
  parsedtype, istpl) \
    WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE_IMPL( \
      parsedtype, istpl)

//###########
//Impl Macros
//###########

//-----
//Utils
//-----

#define WG_PP_PARSEDTYPE_ISLOCALTYPE(parsedtype) \
  WG_PP_KEYWORDS_STARTWITH_LOCAL(parsedtype)

#define WG_PP_PARSEDTYPE_ISNONLOCALTYPE(parsedtype) \
  BOOST_PP_NOT(WG_PP_PARSEDTYPE_ISLOCALTYPE(parsedtype))

#define WG_PP_PARSEDTYPE_NONLOCALTYPE_ADDCONST(nonlocaltype, istpl) \
  WG_PP_ADDTYPENAME(istpl) boost::add_const<WG_PP_IDENTITY_ARG1(nonlocaltype)>::type

#define WG_PP_PARSEDTYPE_NONLOCALTYPE_ADDREFERENCE(nonlocaltype, istpl) \
  WG_PP_ADDTYPENAME(istpl) boost::add_reference< \
    WG_PP_IDENTITY_ARG1(nonlocaltype) >::type

#define WG_PP_PARSEDTYPE_NONLOCALTYPE_ADDCONSTADDREFERENCE( \
  nonlocaltype, istpl) \
    WG_PP_ADDTYPENAME(istpl) boost::add_reference< \
      WG_PP_ADDTYPENAME(istpl) boost::add_const<WG_PP_IDENTITY_ARG1(nonlocaltype) \
      >::type \
    >::type

// elem: 0 or 1.
// Result:
//  local type operand or lib-type-qualifier-seq, depending on whether
//  elem was 0 or 1 respectively.
#define WG_PP_PARSEDTYPE_LOCALTYPE_PARSE(parsedtype, elem) \
  BOOST_PP_EXPAND( \
    WG_PP_PARSEDTYPE_LOCALTYPE_PARSE2 \
    BOOST_PP_LPAREN() \
      BOOST_PP_CAT( \
        WG_PP_PARSEDTYPE_LOCALTYPE_PARSE_, parsedtype) BOOST_PP_COMMA() \
      elem \
    BOOST_PP_RPAREN() )
#define WG_PP_PARSEDTYPE_LOCALTYPE_PARSE_local(operand) operand , BOOST_PP_NIL
#define WG_PP_PARSEDTYPE_LOCALTYPE_PARSE2(operand, prefixed_qualseq, elem) \
  BOOST_PP_IIF( \
    elem, \
    WG_PP_EATHEADTOKEN_BOOST_PP_NIL(prefixed_qualseq) BOOST_PP_EMPTY, \
    operand BOOST_PP_EMPTY) ()

//-------------------------------
//WG_PP_PARSEDTYPE_EXTRACTCPPTYPE
//-------------------------------

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_IMPL(parsedtype) \
  BOOST_PP_IIF( \
    WG_PP_PARSEDTYPE_ISLOCALTYPE(parsedtype), \
    WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_IMPL_LOCAL, \
    WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_IMPL_NONLOCAL) (parsedtype)

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_IMPL_NONLOCAL(parsedtype) \
  parsedtype

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_IMPL_LOCAL(parsedtype) \
  WG_PP_PARSEDTYPE_LOCALTYPE_OPERAND(parsedtype) \
  BOOST_PP_CAT( \
    WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_IMPL_LOCAL, \
    BOOST_PP_SEQ_CAT( \
      (_) WG_PP_PARSEDTYPE_LOCALTYPE_PARSE(parsedtype, 1)) )

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_IMPL_LOCAL_
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_IMPL_LOCAL_const const
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_IMPL_LOCAL_ref &
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_IMPL_LOCAL_constref const &

//------------------------------------------------
//WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDREFERENCE
//------------------------------------------------

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDREFERENCE_IMPL( \
  parsedtype, istpl) \
    BOOST_PP_IIF( \
      WG_PP_PARSEDTYPE_ISLOCALTYPE(parsedtype), \
      WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDREFERENCE_IMPL_LOCAL, \
      WG_PP_PARSEDTYPE_NONLOCALTYPE_ADDREFERENCE) (parsedtype, istpl)

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDREFERENCE_IMPL_LOCAL( \
  parsedtype, istpl) \
    WG_PP_PARSEDTYPE_LOCALTYPE_PARSE(parsedtype, 0) \
    BOOST_PP_CAT( \
      WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDREFERENCE_IMPL_LOCAL, \
      BOOST_PP_SEQ_CAT( \
        (_) WG_PP_PARSEDTYPE_LOCALTYPE_PARSE(parsedtype, 1)) )

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDREFERENCE_IMPL_LOCAL_ &
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDREFERENCE_IMPL_LOCAL_const const &
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDREFERENCE_IMPL_LOCAL_ref &
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDREFERENCE_IMPL_LOCAL_constref const &

//--------------------------------------------------------
//WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE
//--------------------------------------------------------

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE_IMPL( \
  parsedtype, istpl) \
    BOOST_PP_IIF( \
      WG_PP_PARSEDTYPE_ISLOCALTYPE(parsedtype), \
      WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE_IMPL_LOCAL, \
      WG_PP_PARSEDTYPE_NONLOCALTYPE_ADDCONSTADDREFERENCE) (parsedtype, istpl)

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE_IMPL_LOCAL( \
  parsedtype, istpl) \
    WG_PP_PARSEDTYPE_LOCALTYPE_PARSE(parsedtype, 0) \
    BOOST_PP_CAT( \
      WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE_IMPL_LOCAL, \
      BOOST_PP_SEQ_CAT( \
        (_) WG_PP_PARSEDTYPE_LOCALTYPE_PARSE(parsedtype, 1)) )

#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE_IMPL_LOCAL_ const &
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE_IMPL_LOCAL_const const &
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE_IMPL_LOCAL_ref &
#define WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AND_ADDCONSTADDREFERENCE_IMPL_LOCAL_constref const &

#endif //WG_PP_PARSEDTYPE_HH_
