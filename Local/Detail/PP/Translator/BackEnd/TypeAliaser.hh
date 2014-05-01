#ifndef WG_PP_TYPEALIASER_HH_
#define WG_PP_TYPEALIASER_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/Utils.hh>
#include <WG/Local/Detail/PP/Translator/Markers.hh>
#include <WG/Local/Detail/PP/Translator/Keywords.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/TypeExtractor.hh>

//###########
//Public APIs
//###########

// Will create a struct named <typealiasername> that declares typedefs for all
// policy-marked types.
//
// WARNING:
//   Aliasing all types will lose information of which types where
//   declared/captured local. This information maybe necessary in later codegen
//   passes, where we have to choose between PPMP and TMP techniques to
//   const/ref qualify these types.
//
// replacementpolicy:
//   { ALLTYPES | DEDUCEDTYPES }
//
//   ALLTYPES: creates aliases for all types.
//   DEDUCEDTYPES:
//     creates aliases for only those types marked with
//     WG_PP_MARKER_DEDUCEDTYPE.
//
// specseq:
//   Each token of specseq must begin with a PP seq of at least size three.
//
//   {
//     (
//       (aliasrootname)(getdclnsmacro)(gettypemacro) {(*)}*
//     )
//   }+
//
//   aliasrootname:
//      The root name of the type alias.
//   getdclnsmacro:
//     A one arg macro that when applied to symbtbl expands to a WG_PP_SEQ
//     sequence of dclnS whose types should be considered for aliasing.
//   gettypemacro:
//     A one arg macro that when applied to an element of getdclnsmacro(symbtbl)
//     expands to the type associated with that dcln element.
#define WG_PP_TYPEALIASER_DCLN( \
  typealiasername, replacementpolicy, symbtbl, specseq) \
    WG_PP_TYPEALIASER_DCLN_IMPL( \
      typealiasername, replacementpolicy, symbtbl, specseq)

// WG_PP_STUTIL_REPLACESEQ callback.
// seq:
//   A WG_PP_SEQ.
// iteration:
//   See WG_PP_STUTIL_REPLACESEQ::callback
// dataseq:
//   {
//     (istpl)(typealiasername)(replacementpolicy)
//     { ( (aliasrootname)(gettypemacro)(settypemacro) ) }+
//   }
//
//   replacementpolicy:
//     Must match the one used in WG_PP_TYPEALIASER_DCLN to create typealiasername.
//   aliasrootname:
//     Must match the one used in WG_PP_TYPEALIASER_DCLN to create typealiasername.
//   gettypemacro:
//     Must match the one used in WG_PP_TYPEALIASER_DCLN to create typealiasername.
//   settypemacro:
//     A two arg macro whose first arg takes an element of getdclnsmacro(symbtbl)
//     and whose second arg takes some tokens, and when which expanded
//     replaces the type associated with the first arg with the second arg.
#define WG_PP_TYPEALIASER_REPLACETYPE(seq, iteration, dataseq) \
  WG_PP_TYPEALIASER_REPLACETYPE_IMPL(seq, iteration, dataseq)

//###########
//Impl Macros
//###########

//-----
//Utils
//-----

// indx:
//   The order in which types were aliased in the symbol table.
#define WG_PP_TYPEALIASER_ALIASNAME(aliasrootname, indx) \
  BOOST_PP_CAT(aliasrootname, indx)

//----------------------
//WG_PP_TYPEALIASER_DCLN
//----------------------

#define WG_PP_TYPEALIASER_DCLN_SPEC_ALIASROOTNAME(spec) BOOST_PP_SEQ_ELEM(0, spec)
#define WG_PP_TYPEALIASER_DCLN_SPEC_GETDCLNSMACRO(spec) BOOST_PP_SEQ_ELEM(1, spec)
#define WG_PP_TYPEALIASER_DCLN_SPEC_GETTYPEMACRO(spec) BOOST_PP_SEQ_ELEM(2, spec)

#define WG_PP_TYPEALIASER_DCLN_IMPL( \
  typealiasername, replacementpolicy, symbtbl, specseq) \
    WG_PP_TYPEALIASER_DCLN_IMPL2( \
      typealiasername, \
      ( BOOST_PP_NIL ) \
      WG_PP_TYPEALIASER_DCLNSEQ(replacementpolicy, symbtbl, specseq) )

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

#define WG_PP_TYPEALIASER_DCLNSEQ( \
  replacementpolicy, symbtbl, specseq) \
    BOOST_PP_SEQ_FOR_EACH( \
      WG_PP_TYPEALIASER_DCLNENTRY, \
      (replacementpolicy)(symbtbl), \
      specseq)

// BOOST_PP_SEQ_FOR_EACH functor.
#define WG_PP_TYPEALIASER_DCLNENTRY(r, replacementpolicy_symbtbl, spec) \
  WG_PP_TYPEALIASER_DCLNENTRY2( \
    BOOST_PP_SEQ_ELEM(0, replacementpolicy_symbtbl), \
    BOOST_PP_SEQ_ELEM(1, replacementpolicy_symbtbl), \
    spec)

#define WG_PP_TYPEALIASER_DCLNENTRY2(replacementpolicy, symbtbl, spec) \
  BOOST_PP_IIF( \
    WG_PP_SEQ_ISNIL( \
      WG_PP_TYPEALIASER_DCLN_SPEC_GETDCLNSMACRO(spec) (symbtbl)), \
    WG_PP_MAPTO_NOTHING_ARG3, \
    WG_PP_TYPEALIASER_DCLNTUPLE_PROCESS) (replacementpolicy, symbtbl, spec)

#define WG_PP_TYPEALIASER_DCLNTUPLE_PROCESS(replacementpolicy, symbtbl, spec) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_UCAT_ARG2(WG_PP_TYPEALIASER_DCLNTUPLE, replacementpolicy), \
    spec, \
    WG_PP_TYPEALIASER_DCLN_SPEC_GETDCLNSMACRO(spec) (symbtbl) )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_TYPEALIASER_DCLNTUPLE_ALLTYPES( \
  r, spec, indx, dcln) \
    WG_PP_TYPEALIASER_DCLNTUPLE_IMPL( \
      spec, \
      indx, \
      WG_PP_TYPEALIASER_DCLN_SPEC_GETTYPEMACRO(spec) (dcln) )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_TYPEALIASER_DCLNTUPLE_DEDUCEDTYPES( \
  r, spec, indx, dcln) \
    BOOST_PP_EXPR_IIF( \
      WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_DEDUCEDTYPE( \
        WG_PP_TYPEALIASER_DCLN_SPEC_GETTYPEMACRO(spec) (dcln) ), \
      WG_PP_TYPEALIASER_DCLNTUPLE_IMPL( \
        spec, \
        indx, \
        WG_PP_TYPEALIASER_DCLN_SPEC_GETTYPEMACRO(spec) (dcln) ) )

#define WG_PP_TYPEALIASER_DCLNTUPLE_IMPL( \
  spec, indx, marked_e_or_d_type) \
  ( \
    typedef \
      WG_PP_PARSEDTYPE_EXTRACTCPPTYPE( \
        WG_PP_TRNSLTR_MARKERS_EATHEADMARKER(marked_e_or_d_type)) \
      WG_PP_TYPEALIASER_ALIASNAME( \
        WG_PP_TYPEALIASER_DCLN_SPEC_ALIASROOTNAME(spec), indx) ; \
  )

//-----------------------------
//WG_PP_TYPEALIASER_REPLACETYPE
//-----------------------------

#define WG_PP_TYPEALIASER_REPLACETYPE_DATASEQ_ISTPL(dataseq) \
  BOOST_PP_SEQ_ELEM(0, dataseq)
#define WG_PP_TYPEALIASER_REPLACETYPE_DATASEQ_TYPEALIASERNAME(dataseq) \
  BOOST_PP_SEQ_ELEM(1, dataseq)
#define WG_PP_TYPEALIASER_REPLACETYPE_DATASEQ_REPLACEMENTPOLICY(dataseq) \
  BOOST_PP_SEQ_ELEM(2, dataseq)
#define WG_PP_TYPEALIASER_REPLACETYPE_DATASEQ_DCLNSPECSEQ(dataseq) \
  BOOST_PP_SEQ_REST_N(3, dataseq)
#define WG_PP_TYPEALIASER_REPLACETYPE_DATASEQ_DCLNSPEC_ALIASROOTNAME(dclnspec) \
  BOOST_PP_SEQ_ELEM(0, dclnspec)
#define WG_PP_TYPEALIASER_REPLACETYPE_DATASEQ_DCLNSPEC_GETTYPEMACRO(dclnspec) \
  BOOST_PP_SEQ_ELEM(1, dclnspec)
#define WG_PP_TYPEALIASER_REPLACETYPE_DATASEQ_DCLNSPEC_SETTYPEMACRO(dclnspec) \
  BOOST_PP_SEQ_ELEM(2, dclnspec)

#define WG_PP_TYPEALIASER_REPLACETYPE_IMPL(seq, iteration, dataseq) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLNTUPLE, \
    (iteration)(dataseq), \
    seq)

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLNTUPLE( \
  r, iteration_dataseq, indx, dcln) \
    ( \
      WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN( \
        BOOST_PP_SEQ_ELEM(0, iteration_dataseq), \
        BOOST_PP_SEQ_ELEM(1, iteration_dataseq), \
        indx, \
        dcln) \
    )

#define WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN( \
  iteration, dataseq, indx, dcln) \
    WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN2( \
      WG_PP_TYPEALIASER_REPLACETYPE_DATASEQ_ISTPL(dataseq), \
      WG_PP_TYPEALIASER_REPLACETYPE_DATASEQ_TYPEALIASERNAME(dataseq), \
      WG_PP_TYPEALIASER_REPLACETYPE_DATASEQ_REPLACEMENTPOLICY(dataseq), \
      BOOST_PP_SEQ_ELEM( \
        iteration, \
        WG_PP_TYPEALIASER_REPLACETYPE_DATASEQ_DCLNSPECSEQ(dataseq) ), \
      indx, \
      dcln)

#define WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN2( \
  istpl, typealiasername, replacementpolicy, dclnspec, indx, dcln) \
    WG_PP_UCAT_ARG2( \
      WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN, \
      replacementpolicy) \
    (istpl, typealiasername, dclnspec, indx, dcln)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN_ALLTYPES
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN_ALLTYPES( \
  istpl, typealiasername, dclnspec, indx, dcln) \
    WG_PP_TYPEALIASER_REPLACETYPE_DATASEQ_DCLNSPEC_SETTYPEMACRO(dclnspec) \
    ( \
      dcln, \
      WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN_ALLTYPES2 \
      (istpl, typealiasername, dclnspec, indx, dcln) \
    )

#define WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN_ALLTYPES2( \
  istpl, typealiasername, dclnspec, indx, dcln) \
    WG_PP_MARKER_NOOP \
    WG_PP_KEYWORDS_REPLACEOPERAND \
    ( \
      WG_PP_TRNSLTR_MARKERS_EATHEADMARKER( \
        WG_PP_TYPEALIASER_REPLACETYPE_DATASEQ_DCLNSPEC_GETTYPEMACRO(dclnspec) \
        (dcln) ), \
      WG_PP_TRNSLTR_UTILS_ADDTYPENAME(istpl) \
      typealiasername::WG_PP_TYPEALIASER_ALIASNAME( \
        WG_PP_TYPEALIASER_REPLACETYPE_DATASEQ_DCLNSPEC_ALIASROOTNAME(dclnspec), \
        indx) \
    )

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN_DEDUCEDTYPES
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN_DEDUCEDTYPES( \
  istpl, typealiasername, dclnspec, indx, dcln) \
    BOOST_PP_IIF( \
      WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_DEDUCEDTYPE( \
        WG_PP_TYPEALIASER_REPLACETYPE_DATASEQ_DCLNSPEC_GETTYPEMACRO(dclnspec) \
        (dcln) ), \
      WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN_ALLTYPES, \
      WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN_NONE) \
    (istpl, typealiasername, dclnspec, indx, dcln)

#define WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN_NONE( \
  istpl, typealiasername, dclnspec, indx, dcln) \
    dcln

#endif /* WG_PP_TYPEALIASER_HH_ */
