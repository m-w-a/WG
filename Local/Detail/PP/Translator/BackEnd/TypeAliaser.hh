#ifndef WG_PP_TYPEALIASER_HH_
#define WG_PP_TYPEALIASER_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/Utils.hh>
#include <WG/Local/Detail/PP/Translator/Markers.hh>
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
//       (aliasrootname)(getdclnsmacro)(gettypemacro) {*}
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

// Replaces the types associated with the dclnS specified in specseq with types
// declared in typealiasername, where the latter is the name of the type that
// was created using WG_PP_TYPEALIASER_DCLN.
//
// replacementpolicy:
//   Must match the one used in WG_PP_TYPEALIASER_DCLN to create typealiasername.
//
// specseq:
//   {
//     (
//       (aliasrootname)(getdclnsmacro)(gettypemacro)(setdclnsmacro)(settypemacro)
//     )
//   }+
//
//   aliasrootname:
//     Must match the one used in WG_PP_TYPEALIASER_DCLN to create typealiasername.
//   getdclnsmacro:
//     Must match the one used in WG_PP_TYPEALIASER_DCLN to create typealiasername.
//   gettypemacro:
//     Must match the one used in WG_PP_TYPEALIASER_DCLN to create typealiasername.
//   setdclnsmacro:
//     A two arg macro that when applied to (symbtbl, replacement_dclns) replaces
//     some sequence of dclnS with replacement_dclns.
//   settypemacro:
//     A two arg macro whose first arg takes an element of getdclnsmacro(symbtbl)
//     and whose second arg takes some tokens, and when which expanded
//     replaces the type associated with the first arg with the second arg.
#define WG_PP_TYPEALIASER_REPLACETYPE( \
  symbtbl, istpl, typealiasername, replacementpolicy, specseq) \
    WG_PP_TYPEALIASER_REPLACETYPE_IMPL( \
      symbtbl, istpl, typealiasername, replacementpolicy, specseq)

//###########
//Impl Macros
//###########

//-----
//Utils
//-----

#define WG_PP_TYPEALIASER_DCLN_SPEC_ALIASROOTNAME(spec) BOOST_PP_SEQ_ELEM(0, spec)
#define WG_PP_TYPEALIASER_DCLN_SPEC_GETDCLNSMACRO(spec) BOOST_PP_SEQ_ELEM(1, spec)
#define WG_PP_TYPEALIASER_DCLN_SPEC_GETTYPEMACRO(spec) BOOST_PP_SEQ_ELEM(2, spec)

#define WG_PP_TYPEALIASER_REPLACETYPE_SPEC_ALIASROOTNAME(spec) BOOST_PP_SEQ_ELEM(0, spec)
#define WG_PP_TYPEALIASER_REPLACETYPE_SPEC_GETDCLNSMACRO(spec) BOOST_PP_SEQ_ELEM(1, spec)
#define WG_PP_TYPEALIASER_REPLACETYPE_SPEC_GETTYPEMACRO(spec) BOOST_PP_SEQ_ELEM(2, spec)
#define WG_PP_TYPEALIASER_REPLACETYPE_SPEC_SETDCLNSMACRO(spec) BOOST_PP_SEQ_ELEM(3, spec)
#define WG_PP_TYPEALIASER_REPLACETYPE_SPEC_SETTYPEMACRO(spec) BOOST_PP_SEQ_ELEM(4, spec)

// indx:
//   The order in which types were aliased in the symbol table.
#define WG_PP_TYPEALIASER_ALIASNAME(aliasrootname, indx) \
  BOOST_PP_CAT(aliasrootname, indx)

//----------------------
//WG_PP_TYPEALIASER_DCLN
//----------------------

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

#define WG_PP_TYPEALIASER_REPLACETYPE_IMPL( \
  symbtbl, istpl, typealiasername, replacementpolicy, specseq) \
    BOOST_PP_SEQ_FOR_EACH( \
      WG_PP_TYPEALIASER_REPLACETYPE_SPECENTRY, \
      (symbtbl)(istpl)(typealiasername)(replacementpolicy), \
      specseq )

// BOOST_PP_SEQ_FOR_EACH functor.
#define WG_PP_TYPEALIASER_REPLACETYPE_SPECENTRY( \
  r, symbtbl_istpl_typealiasername_replacementpolicy, spec) \
    WG_PP_TYPEALIASER_REPLACETYPE_SPEC_SETDCLNSMACRO(spec) \
    ( \
      BOOST_PP_SEQ_ELEM(0, symbtbl_istpl_typealiasername_replacementpolicy), \
      WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLNSEQ( \
        BOOST_PP_SEQ_REST_N(1, symbtbl_istpl_typealiasername_replacementpolicy) \
        (spec), \
        WG_PP_TYPEALIASER_REPLACETYPE_SPEC_GETDCLNSMACRO(spec) \
        ( \
          BOOST_PP_SEQ_ELEM( \
            0, \
            symbtbl_istpl_typealiasername_replacementpolicy) \
        ) ) \
    )

#define WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLNSEQ( \
  istpl_typealiasername_replacementpolicy_spec, dclns_to_replace) \
    WG_PP_SEQ_FOR_EACH_I( \
      WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLNENTRY, \
      istpl_typealiasername_replacementpolicy_spec, \
      dclns_to_replace)

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLNENTRY( \
  r, istpl_typealiasername_replacementpolicy_spec, indx, dcln) \
    ( \
      WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN( \
        BOOST_PP_SEQ_ELEM(0, istpl_typealiasername_replacementpolicy_spec), \
        BOOST_PP_SEQ_ELEM(1, istpl_typealiasername_replacementpolicy_spec), \
        BOOST_PP_SEQ_ELEM(2, istpl_typealiasername_replacementpolicy_spec), \
        BOOST_PP_SEQ_ELEM(3, istpl_typealiasername_replacementpolicy_spec), \
        indx, \
        dcln) \
    )

#define WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN( \
  istpl, typealiasername, replacementpolicy, spec, indx, dcln) \
    WG_PP_UCAT_ARG2( \
      WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN, \
      replacementpolicy) \
    (istpl, typealiasername, spec, indx, dcln)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN_ALLTYPES
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN_ALLTYPES( \
  istpl, typealiasername, spec, indx, dcln) \
    WG_PP_TYPEALIASER_REPLACETYPE_SPEC_SETTYPEMACRO(spec) \
    ( \
      dcln, \
      WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN_ALLTYPES2 \
      (istpl, typealiasername, spec, indx, dcln) \
    )

#define WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN_ALLTYPES2( \
  istpl, typealiasername, spec, indx, dcln) \
    WG_PP_MARKER_NOOP \
    type \
    ( \
      WG_PP_TRNSLTR_UTILS_ADDTYPENAME(istpl) \
      typealiasername::WG_PP_TYPEALIASER_ALIASNAME( \
        WG_PP_TYPEALIASER_REPLACETYPE_SPEC_ALIASROOTNAME(spec), indx) \
    )

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN_DEDUCEDTYPES
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN_DEDUCEDTYPES( \
  istpl, typealiasername, spec, indx, dcln) \
    BOOST_PP_IIF( \
      WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_DEDUCEDTYPE( \
        WG_PP_TYPEALIASER_REPLACETYPE_SPEC_GETTYPEMACRO(spec) \
        (dcln) ), \
      WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN_ALLTYPES, \
      WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN_NONE) \
    (istpl, typealiasername, spec, indx, dcln)

#define WG_PP_TYPEALIASER_REPLACETYPE_REPLACEMENTDCLN_NONE( \
  istpl, typealiasername, spec, indx, dcln) \
    dcln

#endif /* WG_PP_TYPEALIASER_HH_ */
