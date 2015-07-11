#ifndef WG_AUTOFUNCTOR_HH_
#define WG_AUTOFUNCTOR_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/Translator/FrontEnd/AutoFunctor/SpecNormalize.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/ErrorReporter.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/AutoFunctor/SymbolTable.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/AutoFunctor/CodeGen.hh>

//###########
//Public APIs
//###########

#define WG_AUTOFUNCTOR_TYPE(name) \
  WG_PP_AUTOFUNCTOR_CODEGEN_TYPENAME(name)

#define WG_AUTOFUNCTOR(name, spec) \
  WG_PP_AUTOFUNCTOR_IMPL(name, spec)

#define WG_AUTOFUNCTOR_TPL(name, spec) \
  WG_PP_AUTOFUNCTOR_TPL_IMPL(name, spec)

#define WG_AUTOFUNCTOR_END \
  WG_PP_AUTOFUNCTOR_END_IMPL()

//###########
//Impl Macros
//###########

#define WG_PP_AUTOFUNCTOR_EXPAND1(x) x

#define WG_PP_AUTOFUNCTOR_IMPL(name, spec) \
  WG_PP_AUTOFUNCTOR_CMNIMPL(name, 0, spec)

#define WG_PP_AUTOFUNCTOR_TPL_IMPL(name, spec) \
  WG_PP_AUTOFUNCTOR_CMNIMPL(name, 1, spec)

#define WG_PP_AUTOFUNCTOR_CMNIMPL(name, istpl, spec) \
  WG_PP_AUTOFUNCTOR_EXPAND1( \
    WG_PP_AUTOFUNCTOR_CMNIMPL_ERRORPASS \
    BOOST_PP_LPAREN() \
      name BOOST_PP_COMMA() \
      istpl BOOST_PP_COMMA() \
      BOOST_PP_SEQ_ENUM(WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE(spec, istpl)) \
    BOOST_PP_RPAREN() )

#define WG_PP_AUTOFUNCTOR_CMNIMPL_ERRORPASS( \
  name, \
  istpl, \
  m1, assignto_seq, \
  m2, return_type, \
  m3, parambind_seq, \
  m4, paramset_seq, \
  m5, membind_seq, \
  m6, memset_seq, \
  errors, error_seq) \
    WG_PP_AUTOFUNCTOR_CMNIMPL_REPORTERROR_OR_CONTINUE( \
      name, \
      istpl, \
      assignto_seq, \
      return_type, \
      parambind_seq, paramset_seq, \
      membind_seq, memset_seq, \
      WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLESEQ(assignto_seq) \
      WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLESEQ(parambind_seq) \
      WG_PP_ERRORREPORTER_REPORT_NRMLZDSETTUPLESEQ(paramset_seq) \
      WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLESEQ(membind_seq) \
      WG_PP_ERRORREPORTER_REPORT_NRMLZDSETTUPLESEQ(memset_seq) \
      WG_PP_ERRORREPORTER_REPORT_ERRORTOKENS(error_seq) BOOST_PP_NIL)

#define WG_PP_AUTOFUNCTOR_CMNIMPL_REPORTERROR_OR_CONTINUE(\
  name, \
  istpl, \
  assignto_seq, \
  return_type, \
  parambind_seq, paramset_seq, \
  membind_seq, memset_seq, \
  psbl_error_tokens) \
    BOOST_PP_IIF( \
      WG_PP_STARTSWITH_BOOST_PP_NIL(psbl_error_tokens), \
      WG_PP_AUTOFUNCTOR_CMNIMPL_STARTCODEGEN, \
      WG_PP_AUTOFUNCTOR_CMNIMPL_REPORTERRORS) \
    ( \
      name, \
      istpl, \
      assignto_seq, \
      return_type, \
      parambind_seq, paramset_seq, \
      membind_seq, memset_seq, \
      psbl_error_tokens \
    )

#define WG_PP_AUTOFUNCTOR_CMNIMPL_REPORTERRORS( \
  name, \
  istpl, \
  assignto_seq, \
  return_type, \
  parambind_seq, paramset_seq, \
  membind_seq, memset_seq, \
  psbl_error_tokens) \
    psbl_error_tokens

#define WG_PP_AUTOFUNCTOR_CMNIMPL_STARTCODEGEN( \
  name, \
  istpl, \
  assignto_seq, \
  return_type, \
  parambind_seq, paramset_seq, \
  membind_seq, memset_seq, \
  psbl_error_tokens) \
    WG_PP_AUTOFUNCTOR_CODEGEN_START( \
      name, \
      WG_PP_AUTOFUNCTOR_SYMBOLTABLE_CREATE( \
        istpl, \
        assignto_seq, \
        return_type, \
        parambind_seq, paramset_seq, \
        membind_seq, memset_seq) )

#define WG_PP_AUTOFUNCTOR_END_IMPL() \
  WG_PP_AUTOFUNCTOR_CODEGEN_END()

#endif /* WG_AUTOFUNCTOR_HH_ */
