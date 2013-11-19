#ifndef WG_PP_TYPEALIASER_HH_
#define WG_PP_TYPEALIASER_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/SymbolTableUtil.hh>
#include <WG/Local/Detail/PP/Translator/Utils.hh>
#include <WG/Local/Detail/PP/Translator/Markers.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/TypeExtractor.hh>

//###########
//Public APIs
//###########

//----------------------------------------------------------------------------//
// Whereever this file is included the appropiate SymbolTable.hh must
// also be included
//----------------------------------------------------------------------------//

// Will create a struct named <typealiasername> that typedefs all the requested
// types to aliases that are accessible via the macros that
// follow. Note that the indx param in the said macros reflect the order in
// which the vars were encountered in the symbtbl, starting from the number 0.
//
// kind:
//   The kind of types to be aliased.
//   a token from the following the set: {ALLTYPES, IMPLICITTYPES}
//
// symbtbl:
//   must have the following defined:
//     1) WG_PP_STUTIL_CALL_F2(TYPESEQ, <suffix>, symbtbl)
//   where suffix is declared in specseq.
//
// specseq:
//   { ( (suffix)(varrootname) ) }+
//
//   varrootname:
//     the root name of the congruence class of variables whose types should
//     be aliased.
#define WG_PP_TYPEALIASER_DCLN(typealiasername, kind, symbtbl, specseq) \
  WG_PP_TYPEALIASER_DCLN_IMPL(typealiasername, kind, symbtbl, specseq)

#define WG_PP_TYPEALIASER_SPEC_SUFFIX(spec) BOOST_PP_SEQ_ELEM(0, spec)
#define WG_PP_TYPEALIASER_SPEC_VARROOTNAME(spec) BOOST_PP_SEQ_ELEM(1, spec)

#define WG_PP_TYPEALIASER_VARTYPENAME(spec, indx) \
  WG_PP_TYPEALIASER_VARTYPENAME_IMPL(spec, indx)

//###########
//Impl Macros
//###########

#define WG_PP_TYPEALIASER_VARTYPENAME_IMPL(spec, indx) \
  BOOST_PP_CAT( \
    WG_PP_TYPEALIASER_SPEC_VARROOTNAME(spec), \
    indx)

#define WG_PP_TYPEALIASER_DCLN_IMPL(typealiasername, kind, symbtbl, specseq) \
  struct typealiasername \
  { \
    BOOST_PP_SEQ_FOR_EACH( \
      WG_PP_TYPEALIASER_DEDUCEDTYPEDCLNS, \
      (kind)(symbtbl), \
      specseq) \
  };

// BOOST_PP_SEQ_FOR_EACH functor.
#define WG_PP_TYPEALIASER_DEDUCEDTYPEDCLNS(r, kind_symbtbl, spec) \
  BOOST_PP_IIF( \
    WG_PP_SEQ_ISNIL( \
      WG_PP_STUTIL_CALL_F2( \
        TYPESEQ, \
        WG_PP_TYPEALIASER_SPEC_SUFFIX(spec), \
        BOOST_PP_SEQ_ELEM(1, kind_symbtbl) )), \
    WG_PP_TYPEALIASER_DEDUCEDTYPEDCLNS_NONE, \
    WG_PP_TYPEALIASER_DEDUCEDTYPEDCLNS_PROCESS) (kind_symbtbl, spec)

#define WG_PP_TYPEALIASER_DEDUCEDTYPEDCLNS_NONE(kind_symbtbl, spec) // nothing

#define WG_PP_TYPEALIASER_DEDUCEDTYPEDCLNS_PROCESS(kind_symbtbl, spec) \
  WG_PP_SEQ_FOR_EACH_I( \
    BOOST_PP_CAT( \
      WG_PP_TYPEALIASER_DEDUCEDTYPEDCLN_, \
      BOOST_PP_SEQ_ELEM(0, kind_symbtbl) ) , \
    spec, \
    WG_PP_STUTIL_CALL_F2( \
      TYPESEQ, \
      WG_PP_TYPEALIASER_SPEC_SUFFIX(spec), \
      BOOST_PP_SEQ_ELEM(1, kind_symbtbl) ) )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_TYPEALIASER_DEDUCEDTYPEDCLN_IMPLICITTYPES( \
  r, spec, indx, marked_e_or_d_type) \
    BOOST_PP_EXPR_IIF( \
      WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_DEDUCEDTYPE(marked_e_or_d_type), \
      WG_PP_TYPEALIASER_DEDUCEDTYPEDCLN_IMPL( \
        spec, \
        indx, \
        marked_e_or_d_type ) )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_TYPEALIASER_DEDUCEDTYPEDCLN_ALLTYPES( \
  r, spec, indx, marked_e_or_d_type) \
    WG_PP_TYPEALIASER_DEDUCEDTYPEDCLN_IMPL( \
      spec, \
      indx, \
      marked_e_or_d_type)

#define WG_PP_TYPEALIASER_DEDUCEDTYPEDCLN_IMPL( \
  spec, indx, marked_e_or_d_type) \
    typedef \
      WG_PP_PARSEDTYPE_EXTRACTCPPTYPE( \
        WG_PP_TRNSLTR_MARKERS_EATHEADMARKER(marked_e_or_d_type)) \
    WG_PP_TYPEALIASER_VARTYPENAME(spec, indx) ;

#endif /* WG_PP_TYPEALIASER_HH_ */
