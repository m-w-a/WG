#ifndef WG_PP_LCLCONTEXT_CODEGEN2_HH_
#define WG_PP_LCLCONTEXT_CODEGEN2_HH_

#include <boost/config.hpp>
#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/BoundVarDclnNormalize.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/TypeAliaser.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/LclContext/SymbolTable.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/LclContext/Names.hh>
#include <WG/Local/LclClass.hh>
#include <WG/Local/Detail/PP/Translator/Markers.hh>
#include <WG/Local/Detail/LclContext/ExtantScopeMngrProxy.hh>

//###########
//Public APIs
//###########

#define WG_PP_LCLCONTEXT_CODEGEN_START(symbtbl) \
  WG_PP_LCLCONTEXT_CODEGEN_START_IMPL(symbtbl)

#define WG_PP_LCLCONTEXT_CODEGEN_END(count) \
  WG_PP_LCLCONTEXT_CODEGEN_END_IMPL(count)

//###########
//Impl Macros
//###########

#ifdef BOOST_NO_EXCEPTIONS
  #define WG_PP_LCLCONTEXT_CG_NO_EXCEPTIONS 1
#else
  #define WG_PP_LCLCONTEXT_CG_NO_EXCEPTIONS 0
#endif

#define WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_TRYSTART() \
  BOOST_PP_IIF( \
    WG_PP_LCLCONTEXT_CG_NO_EXCEPTIONS, \
    BOOST_PP_EMPTY, \
    WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_TRYSTART_IMPL) ()

#define WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_TRYSTART_IMPL() \
  try \
  {

#define WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_TRYEND(scopemngr) \
  BOOST_PP_IIF( \
    WG_PP_LCLCONTEXT_CG_NO_EXCEPTIONS, \
    WG_PP_MAP_TONOTHING_ARG1, \
    WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_TRYEND_IMPL) (scopemngr)

#define WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_TRYEND_IMPL(scopemngr) \
  } \
  catch(...) \
  { \
    scopemngr . exit( WG_PP_LCLCONTEXT_CG_DIDSCOPECOMPLETEFLAG() ); \
    throw; \
  } \
  \
  scopemngr . exit(true);

#define WG_PP_LCLCONTEXT_CG_DIDSCOPECOMPLETEFLAG() \
  WG_PP_LCLCONTEXT_NAMES_MANGLE(did_scope_complete)

//--------------
//CodeGen::Start
//--------------

#define WG_PP_LCLCONTEXT_CODEGEN_START_IMPL(symbtbl) \
  { \
    WG_PP_LCLCONTEXT_CG_ENTEREDAS_TYPEALIASORDCLN(symbtbl) \
    \
    bool WG_PP_LCLCONTEXT_CG_DIDSCOPECOMPLETEFLAG() = false; \
    \
    bool WG_PP_LCLCONTEXT_NAMES_SCOPEMNGR_AUTOSIMFLAGNAME() = false; \
    \
    WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS( \
      symbtbl, WG_PP_LCLCONTEXT_NAMES_SCOPEMNGR_AUTOSIMFLAGNAME() )

//------------------------
//EnteredAsTypeAliasorDcln
//------------------------

#define WG_PP_LCLCONTEXT_CG_EXTANTSYMBOLS(symbtbl) \
  BOOST_PP_IF( \
    WG_PP_LCLCONTEXT_SYMBOLTABLE_SYMBOLCOUNT_EXTANT(symbtbl), \
    WG_PP_LCLCONTEXT_CG_EXTANTSYMBOLS_NONEMPTY, \
    BOOST_PP_NIL WG_PP_MAPTO_NOTHING_ARG1) \
  (symbtbl)

#define WG_PP_LCLCONTEXT_CG_EXTANTSYMBOLS_NONEMPTY(symbtbl) \
  BOOST_PP_SEQ_FOR_EACH( \
    WG_PP_LCLCONTEXT_CG_EXTANTSYMBOLS_NONEMPTY_ENTRY, \
    ~, \
    WG_PP_LCLCONTEXT_SYMBOLTABLE_SYMBOLS(symbtbl) )

// BOOST_PP_SEQ_FOR_EACH functor.
#define WG_PP_LCLCONTEXT_CG_EXTANTSYMBOLS_NONEMPTY_ENTRY(r, data, symbol) \
  BOOST_PP_IIF( \
    WG_PP_LCLCONTEXT_SYMBOLTABLE_SYMBOL_CATEGORY_ISEXTANT(symbol), \
    WG_PP_LCLCONTEXT_CG_EXTANTSYMBOLS_NONEMPTY_ENTRY2, \
    WG_PP_MAPTO_NOTHING_ARG1) \
  (symbol)

#define WG_PP_LCLCONTEXT_CG_EXTANTSYMBOLS_NONEMPTY_ENTRY2(symbol) \
  BOOST_PP_IIF( \
    WG_PP_LCLCONTEXT_SYMBOLTABLE_EXTANTSYMBOL_ISENTRYCAPTURED(symbol), \
    WG_PP_TUPLIZE_ARG1, \
    WG_PP_LCLCONTEXT_CG_EXTANTSYMBOLS_NONEMPTY_VOIDENTRY) \
  (symbol)

#define WG_PP_LCLCONTEXT_CG_EXTANTSYMBOLS_NONEMPTY_VOIDENTRY(symbol) \
  ( \
    WG_PP_LCLCONTEXT_SYMBOLTABLE_EXTANTSYMBOL_CAPTUREDENTRY_REPLACE( \
      symbol, \
      ( WG_PP_MARKER_NOOP type(void) ) ( BOOST_PP_NIL ) ( BOOST_PP_NIL ) ) \
  )

#define WG_PP_LCLCONTEXT_CG_ENTEREDAS_TYPEALIASORDCLN_SPECSEQ() \
  ( \
    ( WG_PP_LCLCONTEXT_NAMES_ENTEREDASDCLNS_TYPEALIASOR_ALIASROOTNAME() ) \
    ( WG_PP_IDENTITY_ARG1 ) \
    ( WG_PP_LCLCONTEXT_SYMBOLTABLE_EXTANTSYMBOL_CAPTUREDENTRY_MARKEDTYPE ) \
  )

#define WG_PP_LCLCONTEXT_CG_ENTEREDAS_TYPEALIASORDCLN(symbtbl) \
  WG_PP_TYPEALIASER_DCLN( \
    WG_PP_LCLCONTEXT_NAMES_ENTEREDASDCLNS_TYPEALIASOR_CLASSNAME(), \
    ALLTYPES, \
    WG_PP_LCLCONTEXT_CG_EXTANTSYMBOLS(symbtbl), \
    WG_PP_LCLCONTEXT_CG_ENTEREDAS_TYPEALIASORDCLN_SPECSEQ() )

//---------------
//SCOPEENTERDCLNS
//---------------

#define WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS(symbtbl, autosimflag) \
  BOOST_PP_SEQ_FOR_EACH_I( \
    WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_ENTRY, \
    ( autosimflag ) \
    ( WG_PP_LCLCONTEXT_SYMBOLTABLE_ISTPL(symbtbl) ) \
    ( WG_PP_LCLCONTEXT_SYMBOLTABLE_CUSTOMENTRYHANDLER(symbtbl) ) , \
    WG_PP_LCLCONTEXT_SYMBOLTABLE_SYMBOLS(symbtbl) )

// BOOST_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_ENTRY( \
  r, autosimflag_istpl_customentryhandler, indx, symbol) \
    BOOST_PP_IIF( \
      WG_PP_LCLCONTEXT_SYMBOLTABLE_SYMBOL_CATEGORY_ISEXTANT(symbol), \
      WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_EXTANT, \
      WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_ADHOC) \
    ( \
      symbol, \
      indx, \
      BOOST_PP_SEQ_ELEM(0, autosimflag_istpl_customentryhandler), \
      BOOST_PP_SEQ_ELEM(1, autosimflag_istpl_customentryhandler), \
      BOOST_PP_SEQ_ELEM(2, autosimflag_istpl_customentryhandler) \
    )

//-----------------------
//SCOPEENTERDCLNS::EXTANT
//-----------------------

#define WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_EXTANT( \
  symbol, indx, autosimflag, istpl, customentryhandler) \
    ::wg::lclcontext::detail::extant_scopemngr_proxy_t \
      WG_PP_LCLCONTEXT_NAMES_SCOPEMNGR_OBJNAME(indx) = \
        WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_MAKE( \
          WG_PP_LCLCONTEXT_SYMBOLTABLE_EXTANTSYMBOL_SCOPEMNGREXPR(symbol), \
          autosimflag) ; \
    \
    WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_TRYSTART() \
    \
    BOOST_PP_IIF( \
      WG_PP_LCLCONTEXT_SYMBOLTABLE_EXTANTSYMBOL_ISENTRYCAPTURED(symbol), \
      WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_EXTANT_CAPTUREENTRY, \
      (void) WG_PP_MAPTO_NOTHING_ARG2) \
    (symbol, istpl) \
    \
    WG_LCLCONTEXT_DETAIL_EXTANTSCOPEMNGRPROXY_ENTER( \
      WG_PP_LCLCONTEXT_NAMES_SCOPEMNGR_OBJNAME(indx), \
      WG_PP_LCLCONTEXT_SYMBOLTABLE_EXTANTSYMBOL_SCOPEMNGREXPR(symbol), \
      WG_PP_TYPEALIASER_QUALIFIEDTYPENAME( \
        istpl, \
        WG_PP_LCLCONTEXT_NAMES_ENTEREDASDCLNS_TYPEALIASOR_CLASSNAME(), \
        WG_PP_LCLCONTEXT_NAMES_ENTEREDASDCLNS_TYPEALIASOR_ALIASROOTNAME(), \
        WG_PP_LCLCONTEXT_SYMBOLTABLE_EXTANTSYMBOL_ID(symbol) ) ) ; \
    \
    BOOST_PP_IIF( \
      WG_PP_STARTSWITH_BOOST_PP_NIL(customentryhandler), \
      WG_PP_MAPTO_NOTHING_ARG2, \
      WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_EXTANT_HANDLECUSTOMENTRY) \
    (symbol, customentryhandler)

#define WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_EXTANT_CAPTUREENTRY(symbol, istpl) \
  WG_PP_TYPEALIASER_QUALIFIEDTYPENAME( \
    istpl, \
    WG_PP_LCLCONTEXT_NAMES_ENTEREDASDCLNS_TYPEALIASOR_CLASSNAME(), \
    WG_PP_LCLCONTEXT_NAMES_ENTEREDASDCLNS_TYPEALIASOR_ALIASROOTNAME(), \
    WG_PP_LCLCONTEXT_SYMBOLTABLE_EXTANTSYMBOL_ID(symbol) ) \
      WG_PP_LCLCONTEXT_SYMBOLTABLE_EXTANTSYMBOL_CAPTUREDENTRY_OBJ(symbol) =

#define WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_EXTANT_HANDLECUSTOMENTRY( \
  symbol, customentryhandler) \
    customentryhandler ( \
      WG_PP_LCLCONTEXT_SYMBOLTABLE_EXTANTSYMBOL_CAPTUREDENTRY_OBJ(symbol) )

//----------------------
//SCOPEENTERDCLNS::ADHOC
//----------------------

#define WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_ADHOC( \
  symbol, indx, autosimflag, istpl, customentryhandler) \
    WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_ADHOC2( \
      symbol, \
      istpl, \
      WG_PP_LCLCONTEXT_NAMES_ADHOCSCOPEMNGR_CLASSNAME( \
        WG_PP_LCLCONTEXT_SYMBOLTABLE_ADHOCSYMBOL_ID(symbol)), \
      WG_PP_LCLCONTEXT_NAMES_SCOPEMNGR_OBJNAME(indx) )

#define WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_ADHOC2( \
  symbol, istpl, adhocclass, adhocobj) \
    BOOST_PP_IIF( \
      istpl, \
      WG_LCLCLASS_TPL, \
      WG_LCLCLASS) \
    ( \
      adhocclass, \
      memext WG_PP_LCLCONTEXT_SYMBOLTABLE_ADHOCSYMBOL_VARBINDSEQ(symbol) \
      memint (type(bool) m_didcallexit, false) \
    ) \
      void enter() \
      { \
        WG_PP_LCLCONTEXT_SYMBOLTABLE_ADHOCSYMBOL_ONENTERSEQ(symbol) \
      } \
      \
      void exit(bool const scope_completed) \
      { \
        m_didcallexit = true; \
        (void)scope_completed; \
        WG_PP_LCLCONTEXT_SYMBOLTABLE_ADHOCSYMBOL_ONEXITSEQ(symbol) \
      } \
      \
      ~ adhocclass () BOOST_NOEXCEPT_IF(false) \
      { \
        if( ! m_didcallexit ) \
        { \
          this->exit(false); \
        } \
      } \
      \
    WG_LCLCLASS_END ; \
    \
    adhocclass \
      adhocobj( \
        WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_ADHOC_SCOPEMNGROBJINITARGS( \
          symbol) ) ; \
    \
    WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_TRYSTART() \
    \
    adhocobj . enter() ;

#define WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_ADHOC_SCOPEMNGROBJINITARGS(symbol) \
  WG_PP_SEQ_ENUM( \
    WG_PP_SEQ_FOR_EACH( \
      WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_ADHOC_SCOPEMNGROBJINITARGS_ENTRY, \
      ~, \
      WG_PP_LCLCONTEXT_SYMBOLTABLE_ADHOCSYMBOL_VARBINDSEQ(symbol) ))

// WG_PP_SEQ_FOR_EACH functor.
#define WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_ADHOC_SCOPEMNGROBJINITARGS_ENTRY( \
  r, data, boundvardcln) \
    ( \
      WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_ADHOC_SCOPEMNGROBJINITARGS_ENTRY2( \
        BOOST_PP_SEQ_ELEM(0, WG_PP_BOUNDVARDCLN_NLT_NORMALIZE(boundvardcln)) ) \
    )

#define WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_ADHOC_SCOPEMNGROBJINITARGS_ENTRY2( \
  error_or_markedseq) \
    BOOST_PP_IIF( \
      WG_PP_TRNSLTR_MARKERS_STARTSWITH_WG_PP_MARKER_ERROR(error_or_markedseq), \
      WG_PP_TRNSLTR_MARKERS_EATHEADMARKER, \
      WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_ADHOC_SCOPEMNGROBJINITARGS_ENTRY3) \
    ( error_or_markedseq )

#define WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_ADHOC_SCOPEMNGROBJINITARGS_ENTRY3( \
  markedseq) \
    BOOST_PP_SEQ_ELEM( \
      1, \
      WG_PP_TRNSLTR_MARKERS_EATHEADMARKER(markedseq) )

//------------
//CodeGen::End
//------------

#define WG_PP_LCLCONTEXT_CODEGEN_END_IMPL(count) \
  WG_PP_LCLCONTEXT_CG_DIDSCOPECOMPLETEFLAG() = true; \
  \
  WG_PP_LCLCONTEXT_CG_END_TRYEND( \
    BOOST_PP_SEQ_REVERSE( \
      BOOST_PP_REPEAT( \
        count, \
        WG_PP_LCLCONTEXT_CG_END_SCOPEMNGRSEQ_ENTRY, \
        ~) ) ) \
  }

// BOOST_PP_REPEAT functor.
#define WG_PP_LCLCONTEXT_CG_END_SCOPEMNGRSEQ_ENTRY(z, indx, data) \
  ( WG_PP_LCLCONTEXT_NAMES_SCOPEMNGR_OBJNAME(indx) )

#define WG_PP_LCLCONTEXT_CG_END_TRYEND(scopemngr_seq) \
  BOOST_PP_SEQ_FOR_EACH( \
    WG_PP_LCLCONTEXT_CG_END_TRYEND_ENTRY, \
    ~, \
    scopemngr_seq)

// BOOST_PP_SEQ_FOR_EACH functor.
#define WG_PP_LCLCONTEXT_CG_END_TRYEND_ENTRY(r, data, scopemngr) \
  WG_PP_LCLCONTEXT_CG_SCOPEENTERDCLNS_TRYEND(scopemngr)

#endif /* WG_PP_LCLCONTEXT_CODEGEN2_HH_ */
