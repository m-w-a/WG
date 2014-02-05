#ifndef WG_PP_TYPEALIASER_HH_
#define WG_PP_TYPEALIASER_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/SymbolTableUtil.hh>
#include <WG/Local/Detail/PP/Translator/Utils.hh>
#include <WG/Local/Detail/PP/Translator/Markers.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/TypeExtractor.hh>
#include <WG/Local/Detail/PP/Translator/Utils.hh>

//###########
//Public APIs
//###########

//----------------------------------------------------------------------------//
// Whereever this file is included the appropiate SymbolTable.hh must
// also be included.
//----------------------------------------------------------------------------//

// Will create a struct named <typealiasername> that typedefs all
// WG_PP_MARKER_DEDUCEDTYPE marked types.
//
// symbtbl:
//   must have the following defined:
//     1) WG_PP_STUTIL_CALL_F2(DCLNS, suffix, symbtbl, symbtbl)
//
//  Where suffix is declared in specseq, and the macro itself expands to a
//  WG_PP_SEQ of parsed-explicit-or-deduced-typeS as defined in any
//  SymbolTable.hh
//
// specseq:
//   { ( (suffix)(aliasrootname)(gettypemacro)(settypemacro) ) }+
//
//   suffix:
//     The sequence of dclns whose types should be considered for aliasing.
//   aliasrootname:
//      The root name of the type alias.
//   gettypemacro:
//     A one arg macro that when applied to an element of declnseq expands to
//     the type associated with that sequence.
//   settypemacro:
//     A two arg macro whose first arg takes an element of declnseq and whose
//     second arg takes some tokens.
//     The purpose of this macro is replace the type associated with the first
//     arg with the second arg.
#define WG_PP_TYPEALIASER_DCLN(typealiasername, symbtbl, specseq) \
  WG_PP_TYPEALIASER_DCLN_IMPL(typealiasername, symbtbl, specseq)

// This macro is a WG_PP_STUTIL_REPLACESEQ callback.
// declnseq:
//    A WG_PP_SEQ.
// iteration:
//   See WG_PP_STUTIL_REPLACESEQ::callback
// specseq:
//   See WG_PP_TYPEALIASER_DCLN.
#define WG_PP_TYPEALIASER_REPLACEDEDUCEDTYPESEQ( \
  declnseq, iteration, istpl_typealiasername_specseq) \
    WG_PP_TYPEALIASER_REPLACEDEDUCEDTYPESEQ_IMPL( \
      declnseq, iteration, istpl_typealiasername_specseq)

//###########
//Impl Macros
//###########

//-----
//Utils
//-----

#define WG_PP_TYPEALIASER_SPEC_SUFFIX(spec) BOOST_PP_SEQ_ELEM(0, spec)
#define WG_PP_TYPEALIASER_SPEC_ALIASROOTNAME(spec) BOOST_PP_SEQ_ELEM(1, spec)
#define WG_PP_TYPEALIASER_SPEC_GETTYPEMACRO(spec) BOOST_PP_SEQ_ELEM(2, spec)
#define WG_PP_TYPEALIASER_SPEC_SETTYPEMACRO(spec) BOOST_PP_SEQ_ELEM(3, spec)

// indx:
//   The order in which types were aliased in the symbol table.
#define WG_PP_TYPEALIASER_ALIASNAME(aliasrootname, indx) \
  BOOST_PP_CAT(aliasrootname, indx)

//----------------------
//WG_PP_TYPEALIASER_DCLN
//----------------------

// Do not use typealiaser for wholesale aliasing of captured variables' types,
// since some of those captured types maybe local, and that information needs
// to be preserved for later codegen passes, where we have to choose between
// PPMP and TMP techniques to const/ref qualify these captured types.
#define WG_PP_TYPEALIASER_DCLN_IMPL(typealiasername, symbtbl, specseq) \
  WG_PP_TYPEALIASER_DCLN_IMPL2( \
    typealiasername, \
    ( BOOST_PP_NIL ) \
    WG_PP_TYPEALIASER_DEDUCEDTYPEDCLNSEQ(symbtbl, specseq) )

#define WG_PP_TYPEALIASER_DCLN_IMPL2(typealiasername, deducedtypedclnseq) \
  BOOST_PP_IF( \
    BOOST_PP_GREATER(WG_PP_SEQ_SIZE(deducedtypedclnseq), 1), \
    WG_PP_TYPEALIASER_DECLARE, \
    WG_PP_MAPTO_NOTHING_ARG2) (typealiasername, deducedtypedclnseq)

#define WG_PP_TYPEALIASER_DECLARE(typealiasername, deducedtypedclnseq) \
  struct typealiasername \
  { \
    WG_PP_SEQ_FLATTEN(BOOST_PP_SEQ_TAIL(deducedtypedclnseq)) \
  };

#define WG_PP_TYPEALIASER_DEDUCEDTYPEDCLNSEQ(symbtbl, specseq) \
  BOOST_PP_SEQ_FOR_EACH( \
    WG_PP_TYPEALIASER_DEDUCEDTYPEDCLNS, \
    symbtbl, \
    specseq)

// BOOST_PP_SEQ_FOR_EACH functor.
#define WG_PP_TYPEALIASER_DEDUCEDTYPEDCLNS(r, symbtbl, spec) \
  BOOST_PP_IIF( \
    WG_PP_SEQ_ISNIL( \
      WG_PP_STUTIL_CALL_F2( \
        DCLNS, \
        WG_PP_TYPEALIASER_SPEC_SUFFIX(spec), \
        symbtbl, \
        symbtbl)), \
    WG_PP_MAPTO_NOTHING_ARG2, \
    WG_PP_TYPEALIASER_DEDUCEDTYPEDCLNS_PROCESS) (symbtbl, spec)

#define WG_PP_TYPEALIASER_DEDUCEDTYPEDCLNS_PROCESS(symbtbl, spec) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_TYPEALIASER_DEDUCEDTYPEDCLN_IMPLICITTYPES, \
    spec, \
    WG_PP_STUTIL_CALL_F2( \
      DCLNS, \
      WG_PP_TYPEALIASER_SPEC_SUFFIX(spec), \
      symbtbl, \
      symbtbl ) )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_TYPEALIASER_DEDUCEDTYPEDCLN_IMPLICITTYPES( \
  r, spec, indx, dcln) \
    BOOST_PP_EXPR_IIF( \
      WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_DEDUCEDTYPE( \
        WG_PP_TYPEALIASER_SPEC_GETTYPEMACRO(spec) (dcln) ), \
      WG_PP_TYPEALIASER_DEDUCEDTYPEDCLN_IMPL( \
        spec, \
        indx, \
        WG_PP_TYPEALIASER_SPEC_GETTYPEMACRO(spec) (dcln) ) )

#define WG_PP_TYPEALIASER_DEDUCEDTYPEDCLN_IMPL( \
  spec, indx, marked_e_or_d_type) \
  ( \
    typedef \
      WG_PP_PARSEDTYPE_EXTRACTCPPTYPE( \
        WG_PP_TRNSLTR_MARKERS_EATHEADMARKER(marked_e_or_d_type)) \
      WG_PP_TYPEALIASER_ALIASNAME( \
        WG_PP_TYPEALIASER_SPEC_ALIASROOTNAME(spec), indx) ; \
  )

//---------------------------------------
//WG_PP_TYPEALIASER_REPLACEDEDUCEDTYPESEQ
//---------------------------------------

#define WG_PP_TYPEALIASER_REPLACEDEDUCEDTYPESEQ_IMPL( \
  declnseq, iteration, istpl_typealiasername_specseq) \
    WG_PP_SEQ_FOR_EACH_I( \
      WG_PP_TYPEALIASER_REPLACEDEDUCEDTYPE1, \
      BOOST_PP_SEQ_FIRST_N( \
        2, istpl_typealiasername_specseq) \
      BOOST_PP_SEQ_ELEM( \
        iteration, \
        BOOST_PP_SEQ_REST_N( \
          2, istpl_typealiasername_specseq) ) , \
      declnseq )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_TYPEALIASER_REPLACEDEDUCEDTYPE1( \
  r, istpl_typealiasername_spec, indx, entry) \
    WG_PP_TYPEALIASER_REPLACEDEDUCEDTYPE2( \
      BOOST_PP_SEQ_ELEM(0, istpl_typealiasername_spec), \
      BOOST_PP_SEQ_ELEM(1, istpl_typealiasername_spec), \
      BOOST_PP_SEQ_REST_N(2, istpl_typealiasername_spec), \
      indx, \
      entry)

#define WG_PP_TYPEALIASER_REPLACEDEDUCEDTYPE2( \
  istpl, typealiasername, spec, indx, dcln) \
  ( \
    BOOST_PP_IIF( \
      WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_DEDUCEDTYPE( \
        WG_PP_TYPEALIASER_SPEC_GETTYPEMACRO(spec) (dcln) ), \
      WG_PP_TYPEALIASER_REPLACEDEDUCEDTYPE3, \
      WG_PP_TYPEALIASER_REPLACEDEDUCEDTYPE_THEREISNODEDUCEDTYPE) \
      (istpl, typealiasername, settypemacro, spec, indx, dcln) \
  )

#define WG_PP_TYPEALIASER_REPLACEDEDUCEDTYPE_THEREISNODEDUCEDTYPE( \
  istpl, typealiasername, settypemacro, spec, indx, dcln) \
    dcln

#define WG_PP_TYPEALIASER_REPLACEDEDUCEDTYPE3( \
  istpl, typealiasername, settypemacro, spec, indx, dcln) \
    WG_PP_TYPEALIASER_SPEC_SETTYPEMACRO(spec) \
    ( \
      dcln, \
      WG_PP_TYPEALIASER_REPLACEDEDUCEDTYPE4( \
        istpl, \
        typealiasername, \
        WG_PP_TYPEALIASER_SPEC_ALIASROOTNAME(spec), \
        indx) \
    )

#define WG_PP_TYPEALIASER_REPLACEDEDUCEDTYPE4( \
  istpl, typealiasername, aliasrootname, indx) \
    /* TODO: should this marker be changed to WG_PP_NOOP or something else? */ \
    WG_PP_MARKER_DEDUCEDTYPE \
    type( \
      WG_PP_TRNSLTR_UTILS_ADDTYPENAME(istpl) \
      typealiasername::WG_PP_TYPEALIASER_ALIASNAME(aliasrootname, indx) \
    )

#endif /* WG_PP_TYPEALIASER_HH_ */
