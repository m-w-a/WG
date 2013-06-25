#ifndef WG_PP_AUTOFUNCTOR_CODEGEN_HH_
#define WG_PP_AUTOFUNCTOR_CODEGEN_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/BackEnd/SymbolTable.hh>
#include <WG/Local/Detail/BackEnd/Forwarder.hh>
#include <WG/Local/Detail/Seq.hh>
#include <WG/Local/Detail/BackEnd/TypeDeducer.hh>
#include <WG/Local/Detail/BackEnd/ID.hh>
#include <WG/Local/Detail/BackEnd/LocalOperandSyntaxCheck.hh>
#include <WG/Local/Detail/BackEnd/SymbolTableUtil.hh>

//###########
//Public APIs
//###########

#define WG_PP_AUTOFUNCTOR_CODEGEN_START(name, symbtbl) \
  WG_PP_AUTOFUNCTOR_CODEGEN_START_IMPL(name, symbtbl)

#define WG_PP_AUTOFUNCTOR_CODEGEN_END() \
  WG_PP_AUTOFUNCTOR_CODEGEN_END_IMPL()

//###########
//Impl Macros
//###########

//-----
//Utils
//-----

#define WG_PP_AUTOFUNCTOR_CG_EXPAND1(x) x

#define WG_PP_AUTOFUNCTOR_GLOBALID() WG_PP_ID_MAKE_GLOBAL(autofunctor)

#define WG_PP_AUTOFUNCTOR_CG_FORMATNAME(name) \
  WG_PP_ID_CAT(WG_PP_AUTOFUNCTOR_GLOBALID(), name)

#define WG_PP_AUTOFUNCTOR_CG_LOCALOPERANDSYNTAXCHECKER_NAME() \
  WG_PP_AUTOFUNCTOR_CG_FORMATNAME(localoperandsyntaxchecker)

#define WG_PP_AUTOFUNCTOR_CG_TYPEDEDUCER_NAME() \
  WG_PP_AUTOFUNCTOR_CG_FORMATNAME(typededucer)

#define WG_PP_AUTOFUNCTOR_CG_FRWDR_TYPENAME() \
  WG_PP_AUTOFUNCTOR_CG_FORMATNAME(frwdr_type)

#define WG_PP_AUTOFUNCTOR_CG_FRWDR_OBJNAME() \
  WG_PP_AUTOFUNCTOR_CG_FORMATNAME(frwdr_obj)

#define WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_TYPENAME(name) \
  WG_PP_AUTOFUNCTOR_CG_FORMATNAME(name)

#define WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_OBJNAME() \
  WG_PP_AUTOFUNCTOR_CG_FORMATNAME(autofunctor)

#define WG_PP_AUTOFUNCTOR_COMMONSPECSEQ() \
  ( (ASSIGNEE)(assignee) ) \
  ( (BOUNDPARAM)(parambind) ) \
  ( (SETPARAM)(paramset) ) \
  ( (BOUNDMEM)(membind) ) \
  ( (SETMEM)(memset) )

//------------------------------
//LocalOperandSyntaxCheck Utils.
//------------------------------

#define WG_PP_AUTOFUNCTOR_CODEGEN_LOPRNDSYNTAXCHECK_SPECSEQ() \
  WG_PP_AUTOFUNCTOR_COMMONSPECSEQ()

//------------------
//TypeDeducer Utils.
//------------------

#define WG_PP_AUTOFUNCTOR_CODEGEN_TYPEDDCR_SPECSEQ() \
  WG_PP_AUTOFUNCTOR_COMMONSPECSEQ()

//----------------
//Forwarder Utils.
//----------------

#define WG_PP_AUTOFUNCTOR_CODEGEN_FWRDR_SPEC_ASSIGNEE() \
  (ASSIGNEE)(REF)(assignee)(DONOTREPLACETHISU)
#define WG_PP_AUTOFUNCTOR_CODEGEN_FWRDR_SPEC_BOUNDPARAM() \
  (BOUNDPARAM)(CONSTREF)(parambind)(REPLACETHISU)
#define WG_PP_AUTOFUNCTOR_CODEGEN_FWRDR_SPEC_SETPARAM() \
  (SETPARAM)(CONSTREF)(paramset)(DONOTREPLACETHISU)
#define WG_PP_AUTOFUNCTOR_CODEGEN_FWRDR_SPEC_BOUNDMEM() \
  (BOUNDMEM)(CONSTREF)(membind)(REPLACETHISU)
#define WG_PP_AUTOFUNCTOR_CODEGEN_FWRDR_SPEC_SETMEM() \
  (SETMEM)(CONSTREF)(memset)(DONOTREPLACETHISU)

#define WG_PP_AUTOFUNCTOR_CODEGEN_FWRDR_SPECSEQ() \
  ( WG_PP_AUTOFUNCTOR_CODEGEN_FWRDR_SPEC_ASSIGNEE() ) \
  ( WG_PP_AUTOFUNCTOR_CODEGEN_FWRDR_SPEC_BOUNDPARAM() ) \
  ( WG_PP_AUTOFUNCTOR_CODEGEN_FWRDR_SPEC_SETPARAM() ) \
  ( WG_PP_AUTOFUNCTOR_CODEGEN_FWRDR_SPEC_BOUNDMEM() ) \
  ( WG_PP_AUTOFUNCTOR_CODEGEN_FWRDR_SPEC_SETMEM() )

//------------
//The CodeGen.
//------------

#define WG_PP_AUTOFUNCTOR_CODEGEN_START_IMPL(name, symbtbl) \
  { \
    WG_PP_LOCALOPERANDSYNTAXCHECK_DCLN( \
      WG_PP_AUTOFUNCTOR_CG_LOCALOPERANDSYNTAXCHECKER_NAME(), \
      symbtbl, \
      WG_PP_AUTOFUNCTOR_CODEGEN_LOPRNDSYNTAXCHECK_SPECSEQ()) \
    WG_PP_TYPEDEDUCER_DCLN( \
      WG_PP_AUTOFUNCTOR_CG_TYPEDEDUCER_NAME(), \
      symbtbl, \
      WG_PP_AUTOFUNCTOR_CODEGEN_TYPEDDCR_SPECSEQ()) \
    WG_PP_AUTOFUNCTOR_CODEGEN_START_IMPL2( \
      name, \
      WG_PP_STUTIL_USETYPEDEDUCER( \
        symbtbl, \
        WG_PP_AUTOFUNCTOR_CG_TYPEDEDUCER_NAME(), \
        WG_PP_AUTOFUNCTOR_CODEGEN_TYPEDDCR_SPECSEQ()) )

#define WG_PP_AUTOFUNCTOR_CODEGEN_START_IMPL2(name, symbtbl) \
    WG_PP_FORWARDER_DCLN( \
      WG_PP_AUTOFUNCTOR_CG_FRWDR_TYPENAME(), \
      WG_PP_AUTOFUNCTOR_CG_FRWDR_OBJNAME(), \
      symbtbl, \
      WG_PP_AUTOFUNCTOR_CODEGEN_FWRDR_SPECSEQ()) \
    \
    WG_PP_AUTOFUNCTOR_CG_FNCTRDCLN_START(name, symbtbl)

#define WG_PP_AUTOFUNCTOR_CODEGEN_END_IMPL() \
    WG_PP_AUTOFUNCTOR_CG_FNCTRDCLN_END() \
    WG_PP_AUTOFUNCTOR_CG_FNCTR_INVOKE() \
  }

#define WG_PP_AUTOFUNCTOR_CG_FNCTRDCLN_START(name, symbtbl) \
  struct WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_TYPENAME(name) \
  { \
  private: \
    WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_MEM_DCLNS(symbtbl) \
  public: \
    typedef WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_TYPENAME(name) self_type; \
    \
    explicit WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_TYPENAME(name) ( \
      WG_PP_AUTOFUNCTOR_CG_FRWDR_TYPENAME() const & frwdr) \
      WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_CTOR_INITLIST(frwdr, symbtbl) \
    {} \
    void operator()(WG_PP_AUTOFUNCTOR_CG_FRWDR_TYPENAME() const & frwdr) \
    { \
      static_cast<void>(frwdr); \
      BOOST_PP_EXPR_IIF( \
        WG_PP_SYMBOLTABLE_EXISTS_ASSIGNEE(symbtbl), \
        WG_PP_AUTOFUNCTOR_CG_FRWDR_ACCESSOR_ASSIGNEE(frwdr, symbtbl) = ) \
      this->name \
      ( \
        WG_PP_AUTOFUNCTOR_CG_FUNCTOR_CALLLIST(frwdr, symbtbl) \
      ); \
    } \
    WG_PP_AUTOFUNCTOR_CG_FUNCTOR_RETURNTYPE(symbtbl) \
      name \
      BOOST_PP_LPAREN() \
        WG_PP_AUTOFUNCTOR_CG_FUNC_PARAMLIST(symbtbl) \
      BOOST_PP_RPAREN()

//----------------------
//AutoFunctor Mem Dclns.
//----------------------

#define WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_MEM_DCLNS(symbtbl) \
  WG_PP_SEQ_ENUM( \
    WG_PP_SEQ_JOIN( \
      WG_PP_SEQ_FOR_EACH_I( \
        WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_MEM_DCLN, \
        WG_PP_SYMBOLTABLE_OBJSEQ_BOUNDMEM(symbtbl), \
        WG_PP_SYMBOLTABLE_TYPESEQ_BOUNDMEM(symbtbl)) , \
      WG_PP_SEQ_FOR_EACH_I( \
        WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_MEM_DCLN, \
        WG_PP_SYMBOLTABLE_OBJSEQ_SETMEM(symbtbl), \
        WG_PP_SYMBOLTABLE_TYPESEQ_SETMEM(symbtbl)) ))

#define WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_MEM_DCLN(r, objseq, indx, type) \
  ( type WG_PP_SEQ_ELEM(indx, objseq) ; )

//-----------------------
//AutoFunctor CTor Dclns.
//-----------------------

#define WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_CTOR_INITLIST(frwdr, symbtbl) \
  WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_CTOR_INITLIST2( \
    WG_PP_SEQ_JOIN( \
      WG_PP_SEQ_FOR_EACH_I( \
        WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_CTOR_INITENTRY, \
        (frwdr)(WG_PP_FORWARDER_SPEC_VARROOTNAME( \
          WG_PP_AUTOFUNCTOR_CODEGEN_FWRDR_SPEC_BOUNDMEM())), \
        WG_PP_SYMBOLTABLE_OBJSEQ_BOUNDMEM(symbtbl)) , \
      WG_PP_SEQ_FOR_EACH_I( \
        WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_CTOR_INITENTRY, \
        (frwdr)(WG_PP_FORWARDER_SPEC_VARROOTNAME( \
          WG_PP_AUTOFUNCTOR_CODEGEN_FWRDR_SPEC_SETMEM())), \
        WG_PP_SYMBOLTABLE_OBJSEQ_SETMEM(symbtbl)) ))

#define WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_CTOR_INITENTRY( \
  r, localfrwdrobjname_varrootname, indx, memname) \
    ( \
      memname \
      ( \
        WG_PP_FORWARDER_ACCESSOR( \
          BOOST_PP_SEQ_ELEM(0, localfrwdrobjname_varrootname), \
          BOOST_PP_SEQ_ELEM(1, localfrwdrobjname_varrootname), \
          indx) \
      ) \
    )

#define WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_CTOR_INITLIST2(initseq) \
  BOOST_PP_EXPR_IIF( \
    BOOST_PP_NOT( \
      WG_PP_TOKENS_START_WITH_BOOST_PP_NIL(initseq)), \
      WG_PP_IDENTITY(:) ) \
  WG_PP_SEQ_ENUM(initseq)

//-----------------
//AutoFunctor Misc.
//-----------------

#define WG_PP_AUTOFUNCTOR_CG_FRWDR_ACCESSOR_ASSIGNEE(objname, symbtbl) \
  WG_PP_FORWARDER_ACCESSOR( \
    objname, \
    WG_PP_FORWARDER_SPEC_VARROOTNAME( \
      WG_PP_AUTOFUNCTOR_CODEGEN_FWRDR_SPEC_ASSIGNEE()), \
    0)

#define WG_PP_AUTOFUNCTOR_CG_FUNCTOR_CALLLIST(objname, symbtbl) \
  WG_PP_SEQ_ENUM( \
    WG_PP_SEQ_JOIN2( \
      WG_PP_FORWARDER_ACCESSORWGSEQ( \
        objname, \
        WG_PP_FORWARDER_SPEC_VARROOTNAME( \
          WG_PP_AUTOFUNCTOR_CODEGEN_FWRDR_SPEC_BOUNDPARAM()), \
        WG_PP_SYMBOLTABLE_XXX_SIZE_BOUNDPARAM(symbtbl)), \
      WG_PP_FORWARDER_ACCESSORWGSEQ( \
        objname, \
        WG_PP_FORWARDER_SPEC_VARROOTNAME( \
          WG_PP_AUTOFUNCTOR_CODEGEN_FWRDR_SPEC_SETPARAM()), \
        WG_PP_SYMBOLTABLE_XXX_SIZE_SETPARAM(symbtbl))))

#define WG_PP_AUTOFUNCTOR_CG_FUNCTOR_RETURNTYPE(symbtbl) \
  BOOST_PP_IIF( \
    WG_PP_SYMBOLTABLE_EXISTS_RETTYPE(symbtbl), \
    WG_PP_SYMBOLTABLE_RETTYPE(symbtbl), \
    BOOST_PP_IIF( \
      WG_PP_SYMBOLTABLE_EXISTS_ASSIGNEE(symbtbl), \
      WG_PP_PARSEDTYPE_EXTRACTCPPTYPE( \
        WG_PP_SEQ_CAT(WG_PP_SYMBOLTABLE_TYPESEQ_ASSIGNEE(symbtbl))), \
      void))

//--------------------------
//AutoFunctor FUNC ParamList
//--------------------------

#define WG_PP_AUTOFUNCTOR_CG_FUNC_PARAMLIST(symbtbl) \
  WG_PP_SEQ_ENUM( \
    WG_PP_SEQ_FOR_EACH_I( \
      WG_PP_AUTOFUNCTOR_CG_FUNC_PARAMENTRY, \
      WG_PP_SEQ_JOIN( \
        WG_PP_SYMBOLTABLE_OBJSEQ_BOUNDPARAM(symbtbl), \
        WG_PP_SYMBOLTABLE_OBJSEQ_SETPARAM(symbtbl)), \
      WG_PP_SEQ_JOIN( \
        WG_PP_SYMBOLTABLE_TYPESEQ_BOUNDPARAM(symbtbl), \
        WG_PP_SYMBOLTABLE_TYPESEQ_SETPARAM(symbtbl))))

// WG_PP_SEQ_FOR_EACH_I functor.
#define WG_PP_AUTOFUNCTOR_CG_FUNC_PARAMENTRY(r, obj_seq, indx, elem) \
  BOOST_PP_LPAREN() \
    WG_PP_PARSEDTYPE_EXTRACTCPPTYPE(elem) WG_PP_SEQ_ELEM(indx, obj_seq) \
  BOOST_PP_RPAREN()

#define WG_PP_AUTOFUNCTOR_CG_FNCTRDCLN_END() \
  } WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_OBJNAME() ( \
    WG_PP_AUTOFUNCTOR_CG_FRWDR_OBJNAME() ) ;

#define WG_PP_AUTOFUNCTOR_CG_FNCTR_INVOKE() \
  WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_OBJNAME() \
    BOOST_PP_LPAREN() \
      WG_PP_AUTOFUNCTOR_CG_FRWDR_OBJNAME() \
    BOOST_PP_RPAREN() ;

#endif //WG_PP_AUTOFUNCTOR_CODEGEN_HH_
