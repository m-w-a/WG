#ifndef WG_PP_LCLCONTEXT_CODEGEN_HH_
#define WG_PP_LCLCONTEXT_CODEGEN_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/BoundVarDclnNormalize.hh>
#include <WG/Local/Detail/PP/Translator/Utils.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/TypeAliaser.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/LclContext/SymbolTable.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/LclContext/Names.hh>
#include <WG/Local/LclClass.hh>
#include <WG/Local/Detail/LclContext/ScopeManagerGroup.hh>
#include <WG/Local/Detail/AutoSimulator/AutoSimulator.hh>

#ifdef BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
  #include <WG/Local/Detail/LclContext/AdhocScopeManagerProxyCpp03.hh>
#else
  #include <WG/Local/Detail/LclContext/AdhocScopeManagerProxyCpp11.hh>
#endif

//###########
//Public APIs
//###########

#define WG_PP_LCLCONTEXT_CODEGEN_START(symbtbl) \
  WG_PP_LCLCONTEXT_CODEGEN_START_IMPL(symbtbl)

#define WG_PP_LCLCONTEXT_CODEGEN_END() \
  WG_PP_LCLCONTEXT_CODEGEN_END_IMPL()

//###########
//Impl Macros
//###########

//-----
//Utils
//-----

#ifdef BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
  #define WG_PP_LCLCONTEXT_CG_LCLCLASS_TPLPARAM 0
#else
  #define WG_PP_LCLCONTEXT_CG_LCLCLASS_TPLPARAM 1
#endif

#ifdef BOOST_NO_EXCEPTIONS
  #define WG_PP_LCLCONTEXT_CG_NO_EXCEPTIONS 1
#else
  #define WG_PP_LCLCONTEXT_CG_NO_EXCEPTIONS 0
#endif

//--------------
//CodeGen::Start
//--------------

#define WG_PP_LCLCONTEXT_CG_SCOPEMNGREXPRSEQ(symbtbl) \
  BOOST_PP_SEQ_FOR_EACH( \
    WG_PP_LCLCONTEXT_CG_SCOPEMNGREXPRSEQ_ENTRY, \
    ~, \
    WG_PP_LCLCONTEXT_SYMBOLTABLE_SYMBOLS(symbtbl) )

// BOOST_PP_SEQ_FOR_EACH functor.
#define WG_PP_LCLCONTEXT_CG_SCOPEMNGREXPRSEQ_ENTRY(r, data, symbol) \
  ( \
    BOOST_PP_IIF( \
      WG_PP_LCLCONTEXT_SYMBOLTABLE_SYMBOL_CATEGORY_ISEXTANT(symbol), \
      WG_PP_LCLCONTEXT_CG_SCOPEMNGREXPRSEQ_EXTANTEXPR, \
      WG_PP_LCLCONTEXT_CG_SCOPEMNGREXPRSEQ_ADHOCEXPR) \
    (symbol) \
  )

#define WG_PP_LCLCONTEXT_CG_SCOPEMNGREXPRSEQ_EXTANTEXPR(symbol) \
  WG_PP_LCLCONTEXT_SYMBOLTABLE_EXTANTSYMBOL_SCOPEMNGREXPR(symbol)

#define WG_PP_LCLCONTEXT_CG_SCOPEMNGREXPRSEQ_ADHOCEXPR(symbol) \
  WG_PP_LCLCONTEXT_CG_SCOPEMNGREXPRSEQ_ADHOCEXPR2( \
    WG_PP_LCLCONTEXT_SYMBOLTABLE_ADHOCSYMBOL_ID(symbol) )

#define WG_PP_LCLCONTEXT_CG_SCOPEMNGREXPRSEQ_ADHOCEXPR2(indx) \
  static_cast<WG_PP_LCLCONTEXT_NAMES_ADHOCSCOPEMNGR_BASECLASSNAME(indx) &> \
  ( \
    WG_PP_LCLCONTEXT_NAMES_ADHOCSCOPEMNGR_OBJNAME(indx) \
  )

#define WG_PP_LCLCONTEXT_CODEGEN_START_IMPL(symbtbl) \
  { \
    WG_PP_LCLCONTEXT_CG_ENTEREDAS_TYPEALIASORDCLN(symbtbl) \
    \
    WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLNS(symbtbl) \
    \
    WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_INITIALIZATIONS(symbtbl) \
    \
    WG_PP_LCLCONTEXT_CODEGEN_START_IMPL2( \
      symbtbl, \
      WG_PP_LCLCONTEXT_CG_SCOPEMNGREXPRSEQ(symbtbl) )

#define WG_PP_LCLCONTEXT_CODEGEN_START_IMPL2(symbtbl, scopemngrexprseq) \
  ::wg::lclcontext::detail::scope_mngr_group_t \
    WG_PP_LCLCONTEXT_NAMES_SCOPEMNGRGRP_OBJNAME() = \
      WG_AUTOSIMULATOR_AUTOANYGROUP_ALLOC_CUSTOM( \
        ::wg::lclcontext::detail::scope_mngr_group, \
         scopemngrexprseq) ; \
  \
  bool WG_PP_LCLCONTEXT_NAMES_SCOPEMNGRGRP_AUTOSIMFLAGNAME() = false; \
  \
  WG_AUTOSIMULATOR_AUTOANYGROUP_INIT( \
    WG_PP_LCLCONTEXT_NAMES_SCOPEMNGRGRP_OBJNAME(), \
    WG_PP_LCLCONTEXT_NAMES_SCOPEMNGRGRP_AUTOSIMFLAGNAME(), \
    scopemngrexprseq); \
  \
  WG_PP_LCLCONTEXT_CG_TRYBLOCK(symbtbl) \
  { \
    WG_PP_LCLCONTEXT_CG_ENTERDCLNS( \
      symbtbl, \
      scopemngrexprseq, \
      WG_PP_LCLCONTEXT_NAMES_SCOPEMNGRGRP_OBJNAME() )

#define WG_PP_LCLCONTEXT_CG_TRYBLOCK(symbtbl) \
  BOOST_PP_IIF( \
    WG_PP_LCLCONTEXT_CG_NO_EXCEPTIONS, \
    BOOST_PP_EMPTY, \
    try BOOST_PP_EMPTY) ()

//------------
//CodeGen::End
//------------

#define WG_PP_LCLCONTEXT_CODEGEN_END_IMPL() \
    } \
    \
    BOOST_PP_IIF( \
      WG_PP_LCLCONTEXT_CG_NO_EXCEPTIONS, \
      BOOST_PP_EMPTY, \
      WG_PP_LCLCONTEXT_CG_CATCHBLOCK) () \
  }

#define WG_PP_LCLCONTEXT_CG_CATCHBLOCK() \
  catch(...) \
  { \
    WG_PP_LCLCONTEXT_NAMES_SCOPEMNGRGRP_OBJNAME() . mark_exception(); \
    throw; \
  }

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
    WG_PP_TUPLIZE_ARG1, \
    WG_PP_MAPTO_NOTHING_ARG1) \
  (symbol)

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
//AdhocScopeMngrs
//---------------

#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLNS(symbtbl) \
  WG_PP_SEQ_FOR_EACH( \
    WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLNS_ENTRY, \
    ~, \
    WG_PP_LCLCONTEXT_SYMBOLTABLE_SYMBOLS(symbtbl) )

// WG_PP_SEQ_FOR_EACH functor.
#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLNS_ENTRY(r, data, symbol) \
  BOOST_PP_IIF( \
    WG_PP_LCLCONTEXT_SYMBOLTABLE_SYMBOL_CATEGORY_ISADHOC(symbol), \
    WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN, \
    WG_PP_MAPTO_NOTHING_ARG3) \
  ( \
    WG_PP_LCLCONTEXT_NAMES_ADHOCSCOPEMNGR_CLASSNAME( \
      WG_PP_LCLCONTEXT_SYMBOLTABLE_ADHOCSYMBOL_ID(symbol)), \
    WG_PP_LCLCONTEXT_SYMBOLTABLE_ADHOCSYMBOL_ID(symbol), \
    symbol \
  )

#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN(classname, indx, symbol) \
  WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN_BASECLASS_TYPEDEFDCLN( \
    classname, indx) \
    \
  WG_LCLCLASS( \
    classname, \
    WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN_BASECLASS_SPECIFIER(indx) \
    memext WG_PP_LCLCONTEXT_SYMBOLTABLE_ADHOCSYMBOL_VARBINDSEQ(symbol) \
    WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN_BASECLASS_INITIALIZER(classname) \
  ) \
    \
    WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_ONEXITPROXY(classname) \
    \
    void on_enter() \
    { \
      WG_PP_SEQ_NOTHING_FLATTEN( \
        WG_PP_LCLCONTEXT_SYMBOLTABLE_ADHOCSYMBOL_ONENTERSEQ(symbol) ) ; \
    } \
    \
    void on_exit(bool const did_throw) \
    { \
      (void)did_throw; \
      WG_PP_SEQ_NOTHING_FLATTEN( \
        WG_PP_LCLCONTEXT_SYMBOLTABLE_ADHOCSYMBOL_ONEXITSEQ(symbol) ) ; \
    } \
    \
  WG_LCLCLASS_END ;

//----------------------------------
//AdhocScopeMngr::BaseClassSpecifier
//----------------------------------

#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN_BASECLASS_TYPEDEFDCLN( \
  classname, indx) \
    BOOST_PP_IIF( \
      WG_PP_LCLCONTEXT_CG_LCLCLASS_TPLPARAM, \
      WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN_BASECLASS_TYPEDEFDCLN_CPP11, \
      WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN_BASECLASS_TYPEDEFDCLN_CPP03) \
    (classname, indx)

#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN_BASECLASS_TYPEDEFDCLN_CPP11( \
  classname, indx) \
    typedef \
      ::wg::lclcontext::detail::cpp11::adhoc_scope_manager_proxy \
      < \
        classname \
      > WG_PP_LCLCONTEXT_NAMES_ADHOCSCOPEMNGR_BASECLASSNAME(indx) ;

#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN_BASECLASS_TYPEDEFDCLN_CPP03( \
  classname, indx) \
    typedef \
      ::wg::lclcontext::detail::cpp03::adhoc_scope_manager_proxy \
        WG_PP_LCLCONTEXT_NAMES_ADHOCSCOPEMNGR_BASECLASSNAME(indx) ;

#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN_BASECLASS_SPECIFIER(indx) \
  derives (public WG_PP_LCLCONTEXT_NAMES_ADHOCSCOPEMNGR_BASECLASSNAME(indx) )

//------------------------------------
//AdhocScopeMngr::BaseClassInitializer
//------------------------------------

#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN_BASECLASS_INITIALIZER(classname) \
    BOOST_PP_IIF( \
      WG_PP_LCLCONTEXT_CG_LCLCLASS_TPLPARAM, \
      WG_PP_MAPTO_NOTHING_ARG1, \
      WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN_BASECLASS_INITIALIZER_CPP03) \
    (classname)

#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN_BASECLASS_INITIALIZER_CPP03( \
  classname) \
    baseinit \
    ( \
      ::wg::lclcontext::detail::cpp11::adhoc_scope_manager_proxy( \
        & classname ::on_exit_proxy) \
    )

//---------------------------
//AdhocScopeMngr::OnExitProxy
//---------------------------

#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_ONEXITPROXY(classname) \
  BOOST_PP_IIF( \
    WG_PP_LCLCONTEXT_CG_LCLCLASS_TPLPARAM, \
    WG_PP_MAPTO_NOTHING_ARG1, \
    WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_ONEXITPROXY_CPP03) \
  (classname)

#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_ONEXITPROXY_CPP03(classname) \
  static void on_exit_proxy( \
    ::wg::lclcontext::detail::cpp03::adhoc_scope_manager_proxy * const base, \
    bool const did_throw) \
  { \
    static_cast<classname *>(base)->on_exit(did_throw); \
  }

//-----------------------------
//AdhocScopeMngrInitializations
//-----------------------------

#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_INITIALIZATIONS(symbtbl) \
  BOOST_PP_IF( \
    WG_PP_LCLCONTEXT_SYMBOLTABLE_SYMBOLCOUNT_ADHOC(symbtbl), \
    WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_INITIALIZATIONS2, \
    WG_PP_MAPTO_NOTHING_ARG1) \
  (symbtbl)

#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_INITIALIZATIONS2(symbtbl) \
  BOOST_PP_SEQ_FOR_EACH( \
    WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_INITIALIZATIONS_ENTRY, \
    ~, \
    WG_PP_LCLCONTEXT_SYMBOLTABLE_SYMBOLS(symbtbl) )

// BOOST_PP_SEQ_FOR_EACH functor.
#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_INITIALIZATIONS_ENTRY( \
  r, data, symbol) \
    BOOST_PP_IIF( \
      WG_PP_LCLCONTEXT_SYMBOLTABLE_SYMBOL_CATEGORY_ISEXTANT(symbol), \
      WG_PP_MAPTO_NOTHING_ARG1, \
      WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_INITIALIZATION) \
    (symbol)

#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_INITIALIZATION(symbol) \
  WG_PP_LCLCONTEXT_NAMES_ADHOCSCOPEMNGR_CLASSNAME( \
    WG_PP_LCLCONTEXT_SYMBOLTABLE_ADHOCSYMBOL_ID(symbol)) \
  WG_PP_LCLCONTEXT_NAMES_ADHOCSCOPEMNGR_OBJNAME( \
    WG_PP_LCLCONTEXT_SYMBOLTABLE_ADHOCSYMBOL_ID(symbol)) \
  ( \
    WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_INITIALIZATION_ARGS(symbol) \
  ) ;

#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_INITIALIZATION_ARGS(symbol) \
  WG_PP_SEQ_ENUM( \
    WG_PP_SEQ_FOR_EACH( \
      WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_INITIALIZATION_ARGS_ENTRY, \
      ~, \
      WG_PP_LCLCONTEXT_SYMBOLTABLE_ADHOCSYMBOL_VARBINDSEQ(symbol) ) )

// WG_PP_SEQ_FOR_EACH functor.
#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_INITIALIZATION_ARGS_ENTRY( \
  r, data, boundvardcln) \
    ( \
      BOOST_PP_SEQ_ELEM(1, WG_PP_BOUNDVARDCLN_NLT_NORMALIZE(boundvardcln)) \
    )

//----------
//EnterDclns
//----------

#define WG_PP_LCLCONTEXT_CG_ENTERDCLNS(symbtbl, scopemngrexprseq, scopemngrgrp) \
  BOOST_PP_SEQ_FOR_EACH_I( \
    WG_PP_LCLCONTEXT_CG_ENTERDCLNS_ENTRY, \
    ( WG_PP_LCLCONTEXT_SYMBOLTABLE_ISTPL(symbtbl) ) \
      (scopemngrexprseq) (scopemngrgrp), \
    WG_PP_LCLCONTEXT_SYMBOLTABLE_SYMBOLS(symbtbl) )

// BOOST_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_LCLCONTEXT_CG_ENTERDCLNS_ENTRY(r, data, indx, symbol) \
  BOOST_PP_IIF( \
    WG_PP_LCLCONTEXT_SYMBOLTABLE_SYMBOL_CATEGORY_ISEXTANT(symbol), \
    WG_PP_LCLCONTEXT_CG_EXTANT_ENTERDCLN, \
    WG_PP_LCLCONTEXT_CG_ADHOC_ENTERDCLN) \
  ( \
    indx, \
    symbol, \
    BOOST_PP_SEQ_ELEM(0, data), \
    BOOST_PP_SEQ_ELEM(1, data), \
    BOOST_PP_SEQ_ELEM(2, data) \
  )

#define WG_PP_LCLCONTEXT_CG_EXTANT_ENTERDCLN( \
  indx, symbol, istpl, scopemngrexprseq, scopemngrgrp) \
    BOOST_PP_IIF( \
      WG_PP_LCLCONTEXT_SYMBOLTABLE_EXTANTSYMBOL_ISENTRYCAPTURED(symbol), \
      WG_PP_LCLCONTEXT_CG_EXTANT_ENTERDCLN_CAPTUREENTRY, \
      (void) WG_PP_MAPTO_NOTHING_ARG2) \
    (symbol, istpl) \
    \
    WG_AUTOSIMULATOR_AUTOANYGROUP_ITEMVALUE( \
      scopemngrgrp, \
      indx, \
      scopemngrexprseq) . enter() ;

#define WG_PP_LCLCONTEXT_CG_EXTANT_ENTERDCLN_CAPTUREENTRY(symbol, istpl) \
  WG_PP_TYPEALIASER_QUALIFIEDTYPENAME( \
    istpl, \
    WG_PP_LCLCONTEXT_NAMES_ENTEREDASDCLNS_TYPEALIASOR_CLASSNAME(), \
    WG_PP_LCLCONTEXT_NAMES_ENTEREDASDCLNS_TYPEALIASOR_ALIASROOTNAME(), \
    WG_PP_LCLCONTEXT_SYMBOLTABLE_EXTANTSYMBOL_ID(symbol) ) \
      WG_PP_LCLCONTEXT_SYMBOLTABLE_EXTANTSYMBOL_CAPTUREDENTRY_OBJ(symbol) =

#define WG_PP_LCLCONTEXT_CG_ADHOC_ENTERDCLN( \
  indx, symbol, istpl, scopemngrexprseq, scopemngrgrp) \
    WG_PP_LCLCONTEXT_NAMES_ADHOCSCOPEMNGR_OBJNAME( \
      WG_PP_LCLCONTEXT_SYMBOLTABLE_ADHOCSYMBOL_ID(symbol) ) . enter() ;

#endif /* WG_PP_LCLCONTEXT_CODEGEN_HH_ */
