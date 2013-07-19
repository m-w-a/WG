#ifndef WG_PP_TYPEDEDUCER_HH_
#define WG_PP_TYPEDEDUCER_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/Seq.hh>

//###########
//Public APIs
//###########

//----------------------------------------------------------------------------//
//#include <.../SymbolTable.hh>
// Whereever this file is included, then the appropiate SymbolTable.hh must
// also be included
//----------------------------------------------------------------------------//

// Will create a struct named <typededucername> that typedefs all the types
// of implicitly-typed vars to aliases that are accessible via the macros that
// follow. Note that the indx param in the said macros reflect the order in
// which the vars were encountered in the symbtbl, starting from the number 0.
//
// symbtbl:
//   must have the following defined:
//     1) WG_PP_SYMBOLTABLE_TYPESEQ_<suffix>
//   where suffix is declared in specseq.
//
// specseq:
//   { ( (suffix)(varrootname) ) }+
//
//   varrootname:
//     the root name of the congruence class of variables whose types should
//     be deduced.
#define WG_PP_TYPEDEDUCER_DCLN(typededucername, symbtbl, specseq) \
  WG_PP_TYPEDEDUCER_DCLN_IMPL(typededucername, symbtbl, specseq)

#define WG_PP_TYPEDEDUCER_SPEC_SUFFIX(spec) BOOST_PP_SEQ_ELEM(0, spec)
#define WG_PP_TYPEDEDUCER_SPEC_VARROOTNAME(spec) BOOST_PP_SEQ_ELEM(1, spec)

#define WG_PP_TYPEDEDUCER_TYPENAME(spec, indx) \
  WG_PP_TYPEDEDUCER_TYPENAME_IMPL(spec, indx)

//###########
//Impl Macros
//###########

#define WG_PP_TYPEDEDUCER_TYPENAME_IMPL(spec, indx) \
  BOOST_PP_CAT( \
    WG_PP_TYPEDEDUCER_SPEC_VARROOTNAME(spec), \
    indx)

#define WG_PP_TYPEDEDUCER_DCLN_IMPL(typededucername, symbtbl, specseq) \
  struct typededucername \
  { \
    BOOST_PP_SEQ_FOR_EACH( \
      WG_PP_TYPEDEDUCER_DEDUCEDTYPEDCLNS, \
      symbtbl, \
      specseq) \
  };

// BOOST_PP_SEQ_FOR_EACH functor.
#define WG_PP_TYPEDEDUCER_DEDUCEDTYPEDCLNS(r, symbtbl, spec) \
  BOOST_PP_IIF( \
    WG_PP_TOKENS_START_WITH_BOOST_PP_NIL( \
      BOOST_PP_CAT( \
        WG_PP_SYMBOLTABLE_TYPESEQ_, \
        WG_PP_TYPEDEDUCER_SPEC_SUFFIX(spec)) (symbtbl)), \
    WG_PP_TYPEDEDUCER_DEDUCEDTYPEDCLNS_NONE, \
    WG_PP_TYPEDEDUCER_DEDUCEDTYPEDCLNS_PROCESS) (symbtbl, spec)

#define WG_PP_TYPEDEDUCER_DEDUCEDTYPEDCLNS_NONE(symbtbl, spec) // nothing

#define WG_PP_TYPEDEDUCER_DEDUCEDTYPEDCLNS_PROCESS(symbtbl, spec) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_TYPEDEDUCER_DEDUCEDTYPEDCLN, \
    spec, \
    BOOST_PP_CAT( \
      WG_PP_SYMBOLTABLE_TYPESEQ_, \
      WG_PP_TYPEDEDUCER_SPEC_SUFFIX(spec)) (symbtbl)  )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_TYPEDEDUCER_DEDUCEDTYPEDCLN(r, spec, indx, e_or_d_type) \
  BOOST_PP_EXPR_IIF( \
    WG_PP_TOKENS_START_WITH_WG_PP_DEDUCEDTYPE(e_or_d_type), \
    WG_PP_TYPEDEDUCER_DEDUCEDTYPEDCLN_IMPL(spec, indx, e_or_d_type) )

#define WG_PP_TYPEDEDUCER_DEDUCEDTYPEDCLN_IMPL( \
  spec, indx, deduced_type) \
    typedef WG_PP_TOKENS_EATHEADTOKEN_WG_PP_DEDUCEDTYPE(deduced_type) \
    WG_PP_TYPEDEDUCER_TYPENAME(spec, indx) ;

#endif /* WG_PP_TYPEDEDUCER_HH_ */
