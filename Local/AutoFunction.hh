#ifndef WG_AUTOFUNCTION_HH_
#define WG_AUTOFUNCTION_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/FrontEnd/AutoFunction/SpecNormalize.hh>
#include <WG/Local/Detail/BackEnd/SymbolTable.hh>
#include <WG/Local/Detail/BackEnd/AutoFunction/CodeGen.hh>

//###########
//Public APIs
//###########

#define WG_AUTOFUNCTION(name, spec) \
  WG_PP_AUTOFUNCTION_IMPL(name, spec)

#define WG_AUTOFUNCTION_END \
  WG_AUTOFUNCTION_END_IMPL()

//###########
//Impl Macros
//###########

#define WG_PP_AUTOFUNCTION_EXPAND1(x) x

#define WG_PP_AUTOFUNCTION_IMPL(name, spec) \
  WG_PP_AUTOFUNCTOR_CODEGEN_START( \
    name, \
    WG_PP_AUTOFUNCTION_SYMBTABLE(WG_PP_AUTOFUNCTION_SPEC_NORMALIZE(spec)))

#define WG_PP_AUTOFUNCTION_SYMBTABLE(specseq) \
  WG_PP_AUTOFUNCTION_EXPAND1( \
    WG_PP_AUTOFUNCTION_SYMBTABLE2 \
    BOOST_PP_LPAREN() \
      BOOST_PP_SEQ_ENUM(specseq) \
    BOOST_PP_RPAREN() )

#define WG_PP_AUTOFUNCTION_SYMBTABLE2( \
  m1, assignto_seq, \
  m2, return_type, \
  m3, parambind_seq, \
  m4, paramset_seq, \
  m5, membind_seq, \
  m6, memset_seq) \
    WG_PP_SYMBOLTABLE_CREATE( \
      assignto_seq, return_type, parambind_seq, paramset_seq)

#define WG_AUTOFUNCTION_END_IMPL() \
  WG_PP_AUTOFUNCTOR_CODEGEN_END()

#endif /* WG_AUTOFUNCTION_HH_ */
