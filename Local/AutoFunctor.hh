#ifndef WG_AUTOFUNCTOR_HH_
#define WG_AUTOFUNCTOR_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/FrontEnd/AutoFunctor/SpecNormalize.hh>
#include <WG/Local/Detail/BackEnd/AutoFunctor/SymbolTable.hh>
#include <WG/Local/Detail/BackEnd/AutoFunctor/CodeGen.hh>

//###########
//Public APIs
//###########

#define WG_AUTOFUNCTOR(name, spec) \
  WG_PP_AUTOFUNCTOR_IMPL(name, spec)

#define WG_AUTOFUNCTOR_END \
  WG_AUTOFUNCTOR_END_IMPL()

#define WG_AUTOFUNCTOR_TYPE(name) \
  WG_PP_AUTOFUNCTOR_CODEGEN_TYPENAME(name)

//###########
//Impl Macros
//###########

#define WG_PP_AUTOFUNCTOR_EXPAND1(x) x

#define WG_PP_AUTOFUNCTOR_IMPL(name, spec) \
  WG_PP_AUTOFUNCTOR_CODEGEN_START( \
    name, \
    WG_PP_AUTOFUNCTOR_SYMBTABLE(WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE(spec, 0), 0))

#define WG_PP_AUTOFUNCTOR_SYMBTABLE(specseq, istpl) \
  WG_PP_AUTOFUNCTOR_EXPAND1( \
    WG_PP_AUTOFUNCTOR_SYMBTABLE2 \
    BOOST_PP_LPAREN() \
      BOOST_PP_SEQ_ENUM(specseq) BOOST_PP_COMMA() \
      istpl \
    BOOST_PP_RPAREN() )

#define WG_PP_AUTOFUNCTOR_SYMBTABLE2( \
  m1, assignto_seq, \
  m2, return_type, \
  m3, parambind_seq, \
  m4, paramset_seq, \
  m5, membind_seq, \
  m6, memset_seq, \
  istpl) \
    WG_PP_AUTOFUNCTOR_SYMBOLTABLE_CREATE( \
      istpl, \
      assignto_seq, \
      return_type, \
      parambind_seq, paramset_seq, \
      membind_seq, memset_seq)

#define WG_AUTOFUNCTOR_END_IMPL() \
  WG_PP_AUTOFUNCTOR_CODEGEN_END()

#endif /* WG_AUTOFUNCTOR_HH_ */
