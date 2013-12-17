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
  ( (MEMDECL)(memdecl) ) \
  ( (MEMSET)(memset) )

//------------------
//TypeAliaser Utils.
//------------------

// Skip MEMDECL since it will never have deduced types.
#define WG_PP_LCLCLASS_CG_TYPEALIASER_SPECSEQ() \
  ( (MEMLIKE)(memlike) )

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
      (TYPESEQ_MEMLIKE), \
      WG_PP_TYPEALIASER_REPLACEDEDUCEDTYPESEQ, \
      ( WG_PP_LCLCLASS_SYMBOLTABLE_ISTPL(symbtbl) ) \
      ( WG_PP_LCLCLASS_CG_TYPEALIASER_NAME(name) ) \
      WG_PP_LCLCLASS_CG_TYPEALIASER_SPECSEQ() ) )

#define WG_PP_LCLCLASS_CODEGEN_START_IMPL2(name, symbtbl) \
  WG_PP_LCLCLASS_CODEGEN_START_IMPL3( \
    name, \
    WG_PP_STUTIL_REPLACESEQ( \
      symbtbl, \
      (TYPESEQ_MEMDECL)(TYPESEQ_MEMLIKE)(TYPESEQ_MEMSET), \
      WG_PP_TRNSLTR_MARKERS_ERASEMARKERSINSEQ, \
      ~) )

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
      init(); \
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
    WG_PP_LCLCLASS_SYMBOLTABLE_OBJSEQ_MEMDECL(symbtbl), \
    WG_PP_LCLCLASS_SYMBOLTABLE_TYPESEQ_MEMDECL(symbtbl) ) \
  WG_PP_SEQ_NOTHING_FOR_EACH_I( \
    WG_PP_LCLCLASS_CG_LCLCLASS_MEMDCLN, \
    WG_PP_LCLCLASS_SYMBOLTABLE_OBJSEQ_MEMLIKE(symbtbl), \
    WG_PP_LCLCLASS_SYMBOLTABLE_TYPESEQ_MEMLIKE(symbtbl) ) \
  WG_PP_SEQ_NOTHING_FOR_EACH_I( \
    WG_PP_LCLCLASS_CG_LCLCLASS_MEMDCLN, \
    WG_PP_LCLCLASS_SYMBOLTABLE_OBJSEQ_MEMSET(symbtbl), \
    WG_PP_LCLCLASS_SYMBOLTABLE_TYPESEQ_MEMSET(symbtbl) )

// WG_PP_SEQ_NOTHING_FOR_EACH_I functor.
#define WG_PP_LCLCLASS_CG_LCLCLASS_MEMDCLN(r, objseq, indx, parsedtype) \
  WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(parsedtype) WG_PP_SEQ_ELEM(indx, objseq) ;

//------------------------
//LclClass Ctor ParamList.
//------------------------

#define WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_PARAMLIST(symbtbl) \
  WG_PP_SEQ_ENUM( \
    WG_PP_SEQ_FOR_EACH_I( \
      WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_PARAM, \
      WG_PP_LCLCLASS_SYMBOLTABLE_ISTPL(symbtbl), \
      WG_PP_SEQ_JOIN_ARG2( \
        WG_PP_LCLCLASS_SYMBOLTABLE_TYPESEQ_MEMDECL(symbtbl), \
        WG_PP_LCLCLASS_SYMBOLTABLE_TYPESEQ_MEMLIKE(symbtbl)) ))

// WG_PP_SEQ_NOTHING_FOR_EACH_I functor.
#define WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_PARAM(r, istpl, indx, parsedtype) \
  ( \
    WG_PP_PARSEDTYPE_EXTRACTCPPTYPE_AS_CALLTRAITSPARAMTYPE(parsedtype, istpl) \
    BOOST_PP_CAT(WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_PARAMROOTNAME(), indx) \
  )

//----------------------
//LclClass Ctor InitList
//----------------------

#define WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_INITLIST(symbtbl) \
  BOOST_PP_EXPR_IF( WG_PP_LCLCLASS_SYMBOLTABLE_TOTALXXX_SIZE(symbtbl), : ) \
  WG_PP_SEQ_ENUM( \
    WG_PP_SEQ_JOIN_ARG2( \
      WG_PP_SEQ_FOR_EACH_I( \
        WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_INITWITHPARAMS, \
        ~, \
        WG_PP_SEQ_JOIN_ARG2( \
          WG_PP_LCLCLASS_SYMBOLTABLE_OBJSEQ_MEMDECL(symbtbl), \
          WG_PP_LCLCLASS_SYMBOLTABLE_OBJSEQ_MEMLIKE(symbtbl)) ), \
      WG_PP_SEQ_FOR_EACH_I( \
        WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_INITWITHVALUES, \
        WG_PP_LCLCLASS_SYMBOLTABLE_VALUESEQ_MEMSET(symbtbl), \
        WG_PP_LCLCLASS_SYMBOLTABLE_OBJSEQ_MEMSET(symbtbl)) ))

// WG_PP_SEQ_NOTHING_FOR_EACH_I functor.
#define WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_INITWITHPARAMS(r, data, indx, memname) \
  ( \
    memname( \
      BOOST_PP_CAT(WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_PARAMROOTNAME(), indx) ) \
  )

// WG_PP_SEQ_NOTHING_FOR_EACH_I functor.
#define WG_PP_LCLCLASS_CG_LCLCLASS_CTOR_INITWITHVALUES( \
  r, valueseq, indx, memname) \
    ( \
      memname( WG_PP_SEQ_ELEM(indx, valueseq) ) \
    )

#endif /* WG_PP_LCLCLASS_CODEGEN_HH_ */
