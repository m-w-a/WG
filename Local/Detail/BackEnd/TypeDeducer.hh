#ifndef WG_PP_TYPEDEDUCER_HH_
#define WG_PP_TYPEDEDUCER_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/Seq.hh>
#include <WG/Local/Detail/BackEnd/SymbolTable.hh>

//###########
//Public APIs
//###########

// Will create a struct named <typededucername> that typedefs all the types
// of implicitly-typed vars to aliases that are accessible via the macros that
// follow. Note that the indx param in the said macros reflect the order in
// which they appeared when declared, starting from the number 0.
#define WG_PP_TYPEDEDUCER_DCLN(typededucername, symbtbl) \
  WG_PP_TYPEDEDUCER_DCLN_IMPL(typededucername, symbtbl)

#define WG_PP_TYPEDEDUCER_TYPENAME_ASSIGNEE(indx) \
  WG_PP_TYPEDEDUCER_TYPENAME_ASSIGNEE_IMPL(indx)

#define WG_PP_TYPEDEDUCER_TYPENAME_BOUNDPARAM(indx) \
  WG_PP_TYPEDEDUCER_TYPENAME_BOUNDPARAM_IMPL(indx)

#define WG_PP_TYPEDEDUCER_TYPENAME_BOUNDMEM(indx) \
  WG_PP_TYPEDEDUCER_TYPENAME_BOUNDMEM_IMPL(indx)

//###########
//Impl Macros
//###########

#define WG_PP_TYPEDEDUCER_TYPENAME_ASSIGNEE_IMPL(indx) \
  WG_PP_TYPEDEDUCER_TYPENAME( \
    WG_PP_TYPEDEDUCER_TYPEROOTNAME_ASSIGNEE(), indx)

#define WG_PP_TYPEDEDUCER_TYPENAME_BOUNDPARAM_IMPL(indx) \
  WG_PP_TYPEDEDUCER_TYPENAME( \
    WG_PP_TYPEDEDUCER_TYPEROOTNAME_BOUNDPARAM(), indx)

#define WG_PP_TYPEDEDUCER_TYPENAME_BOUNDMEM_IMPL(indx) \
  WG_PP_TYPEDEDUCER_TYPENAME( \
    WG_PP_TYPEDEDUCER_TYPEROOTNAME_BOUNDMEM(), indx)

#define WG_PP_TYPEDEDUCER_TYPEROOTNAME_ASSIGNEE() assignee
#define WG_PP_TYPEDEDUCER_TYPEROOTNAME_BOUNDPARAM() boundparam
#define WG_PP_TYPEDEDUCER_TYPEROOTNAME_BOUNDMEM() boundmem

#define WG_PP_TYPEDEDUCER_TYPENAME(rootname, indx) \
  BOOST_PP_CAT(rootname, indx)

// TODO: add BOUNDMEM/SETMEM
#define WG_PP_TYPEDEDUCER_DCLN_IMPL(typededucername, symbtbl) \
  struct typededucername \
  { \
    WG_PP_TYPEDEDUCER_DEDUCEDTYPEDCLNS(ASSIGNEE, symbtbl) \
    WG_PP_TYPEDEDUCER_DEDUCEDTYPEDCLNS(BOUNDPARAM, symbtbl) \
  };

// The following need to be defined:
//   WG_PP_TYPEDEDUCER_TYPENAME_<suffix>
//   WG_PP_SYMBOLTABLE_TYPESEQ_<suffix>
#define WG_PP_TYPEDEDUCER_DEDUCEDTYPEDCLNS(suffix, symbtbl) \
  BOOST_PP_IIF( \
    WG_PP_TOKENS_START_WITH_BOOST_PP_NIL( \
      BOOST_PP_CAT(WG_PP_SYMBOLTABLE_TYPESEQ_, suffix) (symbtbl)), \
    WG_PP_TYPEDEDUCER_DEDUCEDTYPEDCLNS_NONE, \
    WG_PP_TYPEDEDUCER_DEDUCEDTYPEDCLNS_PROCESS) (suffix, symbtbl)

#define WG_PP_TYPEDEDUCER_DEDUCEDTYPEDCLNS_NONE(suffix, symbtbl) // nothing
#define WG_PP_TYPEDEDUCER_DEDUCEDTYPEDCLNS_PROCESS(suffix, symbtbl) \
  WG_PP_SEQ_FOR_EACH_I( \
    WG_PP_TYPEDEDUCER_DEDUCEDTYPEDCLN, \
    BOOST_PP_CAT(WG_PP_TYPEDEDUCER_TYPENAME_, suffix), \
    BOOST_PP_CAT(WG_PP_SYMBOLTABLE_TYPESEQ_, suffix) (symbtbl)  )

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_TYPEDEDUCER_DEDUCEDTYPEDCLN(r, namer, indx, e_or_d_type) \
  BOOST_PP_EXPR_IIF( \
    WG_PP_TOKENS_START_WITH_WG_PP_DEDUCEDTYPE(e_or_d_type), \
    WG_PP_TYPEDEDUCER_DEDUCEDTYPEDCLN_IMPL(namer, indx, e_or_d_type) )

#define WG_PP_TYPEDEDUCER_DEDUCEDTYPEDCLN_IMPL(namer, indx, deduced_type) \
  typedef WG_PP_TOKENS_EATHEADTOKEN_WG_PP_DEDUCEDTYPE(deduced_type) \
  namer(indx) ;


#endif /* WG_PP_TYPEDEDUCER_HH_ */
