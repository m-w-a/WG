#ifndef WG_PP_LCLCONTEXT_CODEGEN_HH_
#define WG_PP_LCLCONTEXT_CODEGEN_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/Utils.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/TypeAliaser.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/LclContext/SymbolTable.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/LclContext/Names.hh>
#include <WG/Local/LclClass.hh>

//###########
//Public APIs
//###########

#define WG_PP_LCLCONTEXT_CODEGEN_START(symbtbl) \
  WG_PP_LCLCONTEXT_CODEGEN_START_IMPL(symbtbl)

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

#define WG_PP_LCLCONTEXT_CG_EXTANTSYMBOL_ALIASEDCAPTUREDENTRYTYPE(istpl, symbol) \
  WG_PP_TRNSLTR_UTILS_ADDTYPENAME(istpl) \
  WG_PP_LCLCONTEXT_NAMES_ENTEREDASDCLNS_TYPEALIASOR_CLASSNAME() :: \
    BOOST_PP_CAT( \
      WG_PP_LCLCONTEXT_NAMES_ENTEREDASDCLNS_TYPEALIASOR_ALIASROOTNAME(), \
      WG_PP_LCLCONTEXT_SYMBOLTABLE_EXTANTSYMBOL_ID(symbol) )

//-------
//CodeGen
//-------

#define WG_PP_LCLCONTEXT_CODEGEN_START_IMPL(symbtbl) \
  { \
    WG_PP_LCLCONTEXT_CG_ENTEREDAS_TYPEALIASORDCLN(symbtbl) \
    \
    WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLNS(symbtbl)

//------------------------
//EnteredAsTypeAliasorDcln
//------------------------

#define WG_PP_LCLCONTEXT_CG_EXTANTSYMBOLS(symbtbl) \
  BOOST_PP_IIF( \
    WG_PP_LCLCONTEXT_SYMBOLTABLE_SYMBOLCOUNT_EXTANT(symbtbl), \
    WG_PP_LCLCONTEXT_CG_EXTANTSYMBOLS_NONEMPTY, \
    BOOST_PP_NIL WG_PP_MAPTO_NOTHING_ARG1) \
  (symbtbl)

#define WG_PP_LCLCONTEXT_CG_EXTANTSYMBOLS_NONEMPTY(symbtbl) \
  BOOST_PP_SEQ_FOR_EACH( \
    WG_PP_LCLCONTEXT_CG_EXTANTSYMBOLS_NONEMPTY_ENTRY, \
    ~, \
    WG_PP_LCLCONTEXT_SYMBOLTABLE_SYMBOLS(symbtbl) )

#define WG_PP_LCLCONTEXT_CG_EXTANTSYMBOLS_NONEMPTY_ENTRY(r, data, symbol) \
  BOOST_PP_IIF( \
    WG_PP_LCLCONTEXT_SYMBOLTABLE_SYMBOL_CATEGORY_ISEXTANT(symbol), \
    WG_PP_TUPLIZE_ARG1, \
    WG_PP_MAPTO_NOTHING_ARG1) \
  (symbol)

#define WG_PP_LCLCONTEXT_CG_ENTEREDAS_TYPEALIASORDCLN_SPECSEQ() \
  ( \
    ( WG_PP_LCLCONTEXT_NAMES_ENTEREDASDCLNS_TYPEALIASOR_ALIASROOTNAME() ) \
    ( WG_PP_LCLCONTEXT_CG_EXTANTSYMBOLS ) \
    ( WG_PP_LCLCONTEXT_SYMBOLTABLE_EXTANTSYMBOL_CAPTUREDENTRYTYPE ) \
  )

#define WG_PP_LCLCONTEXT_CG_ENTEREDAS_TYPEALIASORDCLN(symbtbl) \
  WG_PP_TYPEALIASER_DCLN( \
    WG_PP_LCLCONTEXT_NAMES_ENTEREDASDCLNS_TYPEALIASOR_CLASSNAME(), \
    DEDUCEDTYPES, \
    symbtbl, \
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
    WG_PP_MAPTO_NOTHING_ARG2) \
  ( \
    WG_PP_LCLCONTEXT_NAMES_ADHOCSCOPEMNGR_CLASSNAME( \
      WG_PP_LCLCONTEXT_SYMBOLTABLE_ADHOCSYMBOL_ID(symbol)), \
    symbol \
  )

#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN(classname, symbol) \
  WG_LCLCLASS( \
    classname, \
    WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN_BASECLASS_SPECIFIER( \
      classname, symbol) \
    memext WG_PP_LCLCONTEXT_SYMBOLTABLE_ADHOCSYMBOL_VARBINDSEQ(symbol) \
    WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN_BASECLASS_INITIALIZER( \
      classname, symbol) ) \
    \
    WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_ONEXITPROXY(classname, symbol) \
    \
    void on_enter() \
    { \
      WG_PP_SEQ_NOTHING_FLATTEN( \
        WG_PP_LCLCONTEXT_SYMBOLTABLE_ADHOCSYMBOL_ONENTERSEQ(symbol) ) ; \
    } \
    \
    void on_exit(bool const is_exception_active) \
    { \
      (void)is_exception_active; \
      WG_PP_SEQ_NOTHING_FLATTEN( \
        WG_PP_LCLCONTEXT_SYMBOLTABLE_ADHOCSYMBOL_ONEXITSEQ(symbol) ) ; \
    } \
    \
  WG_LCLCLASS_END ;

//----------------------------------
//AdhocScopeMngr::BaseClassSpecifier
//----------------------------------

#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN_BASECLASS_SPECIFIER( \
  classname, symbol) \
    BOOST_PP_IIF( \
      WG_PP_LCLCONTEXT_CG_LCLCLASS_TPLPARAM, \
      WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN_BASECLASS_SPECIFIER_CPP11, \
      WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN_BASECLASS_SPECIFIER_CPP03) \
    (classname, symbol)

#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN_BASECLASS_SPECIFIER_CPP11( \
  classname, symbol) \
    derives (public ::wg::lclcontext::detail::cpp11::adhoc_scope_manager_proxy \
      < \
        classname \
      >)

#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN_BASECLASS_SPECIFIER_CPP03( \
  classname, symbol) \
    derives (public ::wg::lclcontext::detail::cpp03::adhoc_scope_manager_proxy)

//------------------------------------
//AdhocScopeMngr::BaseClassInitializer
//------------------------------------

#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN_BASECLASS_INITIALIZER( \
  classname, symbol) \
    BOOST_PP_IIF( \
      WG_PP_LCLCONTEXT_CG_LCLCLASS_TPLPARAM, \
      WG_PP_MAPTO_NOTHING_ARG2, \
      WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN_BASECLASS_INITIALIZER_CPP03) \
    (classname, symbol)

#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_DCLN_BASECLASS_INITIALIZER_CPP03( \
  classname, symbol) \
    baseinit \
    ( \
      ::wg::lclcontext::detail::cpp11::adhoc_scope_manager_proxy( \
        & classname ::on_exit_proxy) \
    )

//---------------------------
//AdhocScopeMngr::OnExitProxy
//---------------------------

#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_ONEXITPROXY(classname, symbol) \
  BOOST_PP_IIF( \
    WG_PP_LCLCONTEXT_CG_LCLCLASS_TPLPARAM, \
    WG_PP_MAPTO_NOTHING_ARG2, \
    WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_ONEXITPROXY_CPP03) \
  (classname, symbol)

#define WG_PP_LCLCONTEXT_CG_ADHOCSCOPEMNGR_ONEXITPROXY_CPP03(classname, symbol) \
  static void on_exit_proxy( \
    ::wg::lclcontext::detail::cpp03::adhoc_scope_manager_proxy * const base, \
    bool const is_exception_active) \
  { \
    static_cast<classname *>(base)->on_exit(is_exception_active); \
  }

#endif /* WG_PP_LCLCONTEXT_CODEGEN_HH_ */
