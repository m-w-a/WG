#ifndef WG_PP_AUTOFUNCTOR_CODEGEN_HH_
#define WG_PP_AUTOFUNCTOR_CODEGEN_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/BackEnd/SymbolTable.hh>
#include <WG/Local/Detail/BackEnd/Forwarder.hh>
#include <WG/Local/Detail/Seq.hh>

//###########
//Public APIs
//###########

//###########
//Impl Macros
//###########

#define WG_PP_AUTOFUNCTOR_CG_FORMATNAME(name) \
  BOOST_PP_CAT(WG_PP_IDENTITY(wgXXXautofunctorXXX), name)

#define WG_PP_AUTOFUNCTOR_CG_FRWDR_TYPENAME() \
  WG_PP_AUTOFUNCTOR_CG_FORMATNAME(frwdr_type)

#define WG_PP_AUTOFUNCTOR_CG_FRWDR_OBJNAME() \
  WG_PP_AUTOFUNCTOR_CG_FORMATNAME(frwdr_obj)

#define WG_PP_AUTOFUNCTOR_CG_DEFN(name, symbtbl) \
  struct WG_PP_AUTOFUNCTOR_CG_FORMATNAME(name) \
  { \
    void operator()(WG_PP_AUTOFUNCTOR_CG_FRWDR_TYPENAME() const & frwdr) \
    { \
      static_cast<void>(frwdr); \
      BOOST_PP_EXPR_IIF( \
        WG_PP_SYMBOLTABLE_ASSIGNEDTO_EXISTS(pseq), \
        WG_PP_FORWARDER_ACCESSOR_ASSIGNTO(frwdr) = ) \
      this->name( \
        WG_PP_SEQ_ENUM( \
          WG_PP_SEQ_JOIN2( \
            WG_PP_FORWARDER_ACCESSORWGSEQ_PARAMBIND( \
              frwdr, \
              WG_PP_SYMBOLTABLE_PARAMBIND_XXX_SIZE(symbtbl)), \
            WG_PP_FORWARDER_ACCESSORWGSEQ_PARAMSET( \
              frwdr, \
              WG_PP_SYMBOLTABLE_PARAMSET_XXX_SIZE(symbtbl)))) ); \
    } \
    TODO

#endif //WG_PP_AUTOFUNCTOR_CODEGEN_HH_
