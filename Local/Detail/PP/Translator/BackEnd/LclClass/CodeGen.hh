#ifndef WG_PP_LCLCLASS_CODEGEN_HH_
#define WG_PP_LCLCLASS_CODEGEN_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/Seq.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/LclClass/SymbolTable.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/ID.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/TypeAliaser.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/LocalOperandSyntaxCheck.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/SymbolTableUtil.hh>
#include <WG/Local/Detail/LclClass/Initializer.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/TypeExtractor.hh>

//###########
//Public APIs
//###########

#define WG_PP_LCLCLASS_CODEGEN_START(name, symbtbl) \
  WG_PP_LCLCLASS_CODEGEN_START_IMPL(name, symbtbl)

#define WG_PP_LCLCLASS_CODEGEN_END() \
  WG_PP_LCLCLASS_CODEGEN_END_IMPL()

//###########
//Impl Macros
//###########

//-----
//Utils
//-----

#define WG_PP_LCLCLASS_CG_GLOBALID() WG_PP_ID_MAKE_GLOBAL(lclclass)

#define WG_PP_LCLCLASS_CG_FORMATNAME(name) \
  WG_PP_ID_CAT(WG_PP_LCLCLASS_CG_GLOBALID(), name)

#define WG_PP_LCLCLASS_CG_LOCALOPERANDSSYNTAXCHECKER_NAME(classname) \
  WG_PP_ID_CAT( \
    WG_PP_LCLCLASS_CG_FORMATNAME(localoperandsyntaxchecker), \
    WG_PP_ID_CAT( \
      classname, \
      __LINE__))

#define WG_PP_LCLCLASS_CG_TYPEALIASER_NAME(classname) \
  WG_PP_ID_CAT( \
    WG_PP_LCLCLASS_CG_FORMATNAME(typealiaser), \
    WG_PP_ID_CAT( \
      classname, \
      __LINE__))

#define WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_PARAMROOTNAME() param

//------------------------------
//LocalOperandSyntaxCheck Utils.
//------------------------------

#define WG_PP_LCLCLASS_CG_LOCALOPERANDSSYNTAXCHECKER_SPECSEQ() \
  ( \
    (MEMEXT)(memdecl) \
    (WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_GETTYPE_MEMEXT) \
    (WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_OBJ_MEMEXT) \
  ) \
  ( \
    (MEMINT)(memint) \
    (WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_GETTYPE_MEMINT) \
    (WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_OBJ_MEMINT) \
  )

//------------------
//TypeAliaser Utils.
//------------------

// Skip MEMINT since any of the variables whose types it is deduced from must
// already be in scope.
#define WG_PP_LCLCLASS_CG_TYPEALIASER_SPECSEQ() \
  ( \
    (MEMEXT)(memlike) \
    (WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_GETTYPE_MEMEXT) \
    (WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_SETTYPE_MEMEXT) \
  )

//-------------------
//EraseMarkers Utils.
//-------------------
#define WG_PP_LCLCLASS_CG_ERASEMARKERSCALLBACKDATASEQ() \
  ( \
    (WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_GETTYPE_MEMEXT) \
    (WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_SETTYPE_MEMEXT) \
  ) \
  ( \
    (WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_GETTYPE_MEMINT) \
    (WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_SETTYPE_MEMINT) \
  )

//------------
//The CodeGen.
//------------

#define WG_PP_LCLCLASS_CODEGEN_START_IMPL(name, symbtbl) \
  WG_PP_TYPEALIASER_DCLN( \
    WG_PP_LCLCLASS_CG_TYPEALIASER_NAME(name), \
    symbtbl, \
    WG_PP_LCLCLASS_CG_TYPEALIASER_SPECSEQ() ) \
  WG_PP_LCLCLASS_CODEGEN_START_IMPL2( \
    name, \
    WG_PP_STUTIL_REPLACESEQ( \
      symbtbl, \
      (MEMEXT), \
      WG_PP_TYPEALIASER_REPLACEDEDUCEDTYPESEQ, \
      ( WG_PP_LCLCLASS_SYMBOLTABLE_ISTPL(symbtbl) ) \
      ( WG_PP_LCLCLASS_CG_TYPEALIASER_NAME(name) ) \
      WG_PP_LCLCLASS_CG_TYPEALIASER_SPECSEQ() ) )

#define WG_PP_LCLCLASS_CODEGEN_START_IMPL2(name, symbtbl) \
  WG_PP_LCLCLASS_CODEGEN_START_IMPL3( \
    name, \
    WG_PP_STUTIL_REPLACESEQ( \
      symbtbl, \
      (MEMEXT)(MEMINT), \
      WG_PP_TRNSLTR_MARKERS_ERASEMARKERSINSEQ, \
      WG_PP_LCLCLASS_CG_ERASEMARKERSCALLBACKDATASEQ() ) )

#define WG_PP_LCLCLASS_CODEGEN_START_IMPL3(name, symbtbl) \
  WG_PP_LOCALOPERANDSYNTAXCHECK_DCLN( \
    WG_PP_LCLCLASS_CG_LOCALOPERANDSSYNTAXCHECKER_NAME(name), \
    symbtbl, \
    WG_PP_LCLCLASS_CG_LOCALOPERANDSSYNTAXCHECKER_SPECSEQ() ) \
  class name WG_PP_LCLCLASS_CG_LCLCLASS_BASESPECIFIERDCLN(symbtbl) \
  { \
  private: \
    WG_PP_LCLCLASS_CG_LCLCLASS_MEMDCLNS(symbtbl) \
  public: \
    explicit name ( WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_PARAMLIST(symbtbl) ) \
    WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_INITLIST(symbtbl) \
    { \
      this->init(); \
    } \
  private:

#define WG_PP_LCLCLASS_CODEGEN_END_IMPL() \
  };

//-------------------
//BaseSpecifier Dcln.
//-------------------

#define WG_PP_LCLCLASS_CG_LCLCLASS_BASESPECIFIERDCLN(symbtbl) \
  : WG_PP_LCLCLASS_CG_LCLCLASS_BASESPECIFIERS(symbtbl)

#define WG_PP_LCLCLASS_CG_LCLCLASS_BASESPECIFIERS(symbtbl) \
  WG_PP_SEQ_ENUM( \
    WG_PP_SEQ_JOIN_ARG2( \
      (private ::wg::lclclass::detail::initializer), \
      WG_PP_LCLCLASS_SYMBOLTABLE_DERIVESSEQ(symbtbl) ) )

//-------------------
//LclClass Mem Dclns.
//-------------------

#define WG_PP_LCLCLASS_CG_LCLCLASS_MEMDCLNS(symbtbl) \
  WG_PP_SEQ_NOTHING_FOR_EACH_I( \
    WG_PP_LCLCLASS_CG_LCLCLASS_MEMDCLN, \
    (WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_GETTYPE_MEMEXT) \
    (WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_OBJ_MEMEXT), \
    WG_PP_LCLCLASS_SYMBOLTABLE_DCLNS_MEMEXT(symbtbl) ) \
  WG_PP_SEQ_NOTHING_FOR_EACH_I( \
    WG_PP_LCLCLASS_CG_LCLCLASS_MEMDCLN, \
    (WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_GETTYPE_MEMINT) \
    (WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_OBJ_MEMINT), \
    WG_PP_LCLCLASS_SYMBOLTABLE_DCLNS_MEMINT(symbtbl) )

// WG_PP_SEQ_NOTHING_FOR_EACH_I functor.
#define WG_PP_LCLCLASS_CG_LCLCLASS_MEMDCLN( \
  r, gettypemacro_getobjmacro, indx, dcln) \
    WG_PP_LCLCLASS_CG_LCLCLASS_MEMDCLN2( \
      BOOST_PP_SEQ_ELEM(0, gettypemacro_getobjmacro), \
      BOOST_PP_SEQ_ELEM(1, gettypemacro_getobjmacro), \
      dcln )

#define WG_PP_LCLCLASS_CG_LCLCLASS_MEMDCLN2(gettypemacro, getobjmacro, dcln) \
  WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(gettypemacro(dcln)) getobjmacro(dcln) ;

//------------------------
//LclClass Ctor ParamList.
//------------------------

#define WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_PARAMLIST(symbtbl) \
  WG_PP_SEQ_ENUM( \
    WG_PP_SEQ_FOR_EACH_I( \
      WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_PARAM, \
      WG_PP_LCLCLASS_SYMBOLTABLE_ISTPL(symbtbl), \
      WG_PP_LCLCLASS_SYMBOLTABLE_DCLNS_MEMEXT(symbtbl) ))

// WG_PP_SEQ_NOTHING_FOR_EACH_I functor.
#define WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_PARAM(r, istpl, indx, memextdcln) \
  ( \
    WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AS_CALLTRAITSPARAMTYPE( \
      WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_GETTYPE_MEMEXT(memextdcln), \
      istpl) \
    BOOST_PP_CAT(WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_PARAMROOTNAME(), indx) \
  )

//----------------------
//LclClass Ctor InitList
//----------------------

#define WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_INITLIST(symbtbl) \
  BOOST_PP_EXPR_IF( WG_PP_LCLCLASS_SYMBOLTABLE_DCLNS_TOTALSIZE(symbtbl), : ) \
  WG_PP_SEQ_ENUM( \
    WG_PP_SEQ_JOIN_ARG2( \
      WG_PP_SEQ_FOR_EACH_I( \
        WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_INITWITHPARAMS, \
        ~, \
        WG_PP_LCLCLASS_SYMBOLTABLE_DCLNS_MEMEXT(symbtbl) ), \
      WG_PP_SEQ_FOR_EACH_I( \
        WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_INITWITHVALUES, \
        ~, \
        WG_PP_LCLCLASS_SYMBOLTABLE_DCLNS_MEMINT(symbtbl)) ))

// WG_PP_SEQ_NOTHING_FOR_EACH_I functor.
#define WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_INITWITHPARAMS( \
  r, data, indx, memextdcln) \
    ( \
      WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_OBJ_MEMEXT(memextdcln) \
        ( BOOST_PP_CAT(WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_PARAMROOTNAME(), indx) ) \
    )

// WG_PP_SEQ_NOTHING_FOR_EACH_I functor.
#define WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_INITWITHVALUES( \
  r, data, indx, memintdcln) \
    WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_INITWITHVALUES2( \
      WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_OBJ_MEMINT(memintdcln), \
      WG_PP_LCLCLASS_SYMBOLTABLE_DCLN_VALUE_MEMINT(memintdcln) )

#define WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_INITWITHVALUES2(objname, objvalue) \
    ( \
      objname( objvalue ) \
    )

#endif /* WG_PP_LCLCLASS_CODEGEN_HH_ */
