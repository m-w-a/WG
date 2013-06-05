#ifndef WG_PP_AUTOFUNCTOR_CODEGEN_HH_
#define WG_PP_AUTOFUNCTOR_CODEGEN_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/BackEnd/SymbolTable.hh>
#include <WG/Local/Detail/BackEnd/Forwarder.hh>
#include <WG/Local/Detail/Seq.hh>

//###########
//Public APIs
//###########

#define WG_PP_AUTOFUNCTOR_CODEGEN_START(name, symbtble) \
  WG_PP_AUTOFUNCTOR_CODEGEN_START_IMPL(name, symbtble)

#define WG_PP_AUTOFUNCTOR_CODEGEN_END() \
  WG_PP_AUTOFUNCTOR_CODEGEN_END_IMPL()

//###########
//Impl Macros
//###########

#define WG_PP_AUTOFUNCTOR_CG_FORMATNAME(name) \
  BOOST_PP_CAT(wgXXXautofunctorXXX, name)

#define WG_PP_AUTOFUNCTOR_CG_FRWDR_TYPENAME() \
  WG_PP_AUTOFUNCTOR_CG_FORMATNAME(frwdr_type)

#define WG_PP_AUTOFUNCTOR_CG_FRWDR_OBJNAME() \
  WG_PP_AUTOFUNCTOR_CG_FORMATNAME(frwdr_obj)

#define WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_TYPENAME(name) \
  WG_PP_AUTOFUNCTOR_CG_FORMATNAME(name)

#define WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_OBJNAME() \
  WG_PP_AUTOFUNCTOR_CG_FORMATNAME(autofunctor)

#define WG_PP_AUTOFUNCTOR_CODEGEN_START_IMPL(name, symbtble) \
  { \
    WG_PP_FORWARDER_DCLN( \
      WG_PP_AUTOFUNCTOR_CG_FRWDR_TYPENAME(), \
      WG_PP_AUTOFUNCTOR_CG_FRWDR_OBJNAME(), \
      symbtble) \
    \
    WG_PP_AUTOFUNCTOR_CG_FNCTRDCLN_START(name, symbtble)

#define WG_PP_AUTOFUNCTOR_CODEGEN_END_IMPL() \
    WG_PP_AUTOFUNCTOR_CG_FNCTRDCLN_END() \
    WG_PP_AUTOFUNCTOR_CG_FNCTR_INVOKE() \
  }

#define WG_PP_AUTOFUNCTOR_CG_FNCTRDCLN_START(name, symbtbl) \
  struct WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_TYPENAME(name) \
  { \
    typedef WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_TYPENAME(name) self_type; \
    \
    void operator()(WG_PP_AUTOFUNCTOR_CG_FRWDR_TYPENAME() const & frwdr) \
    { \
      static_cast<void>(frwdr); \
      BOOST_PP_EXPR_IIF( \
        WG_PP_SYMBOLTABLE_EXISTS_ASSIGNEE(symbtbl), \
        WG_PP_FORWARDER_ACCESSOR_ASSIGNEE(frwdr) = ) \
      this->name( \
        WG_PP_SEQ_ENUM( \
          WG_PP_SEQ_JOIN2( \
            WG_PP_FORWARDER_ACCESSORWGSEQ_BOUNDPARAM( \
              frwdr, \
              WG_PP_SYMBOLTABLE_XXX_SIZE_BOUNDPARAM(symbtbl)), \
            WG_PP_FORWARDER_ACCESSORWGSEQ_SETPARAM( \
              frwdr, \
              WG_PP_SYMBOLTABLE_XXX_SIZE_SETPARAM(symbtbl)))) ); \
    } \
    WG_PP_SYMBOLTABLE_RETTYPE(symbtbl) \
      name \
      BOOST_PP_LPAREN() \
        WG_PP_AUTOFUNCTOR_CG_FUNC_PARAMLIST(symbtbl) \
      BOOST_PP_RPAREN()

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
  } WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_OBJNAME() ;

#define WG_PP_AUTOFUNCTOR_CG_FNCTR_INVOKE() \
  WG_PP_AUTOFUNCTOR_CG_AUTOFNCTR_OBJNAME() \
    BOOST_PP_LPAREN() \
      WG_PP_AUTOFUNCTOR_CG_FRWDR_OBJNAME() \
    BOOST_PP_RPAREN() ;

#endif //WG_PP_AUTOFUNCTOR_CODEGEN_HH_
