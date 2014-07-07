#ifndef WG_LCLCLASS_HH_
#define WG_LCLCLASS_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/LclClass/SpecNormalize.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/ErrorReporter.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/LclClass/SymbolTable.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/LclClass/CodeGen.hh>

//###########
//Public APIs
//###########

#define WG_LCLCLASS(name, spec) \
  WG_PP_LCLCLASS_IMPL(name, spec)

#define WG_LCLCLASS_TPL(name, spec) \
  WG_PP_LCLCLASS_TPL_IMPL(name, spec)

#define WG_LCLCLASS_END \
  WG_PP_LCLCLASS_END_IMPL()

//###########
//Impl Macros
//###########

#define WG_PP_LCLCLASS_EXPAND1(x) x

#define WG_PP_LCLCLASS_IMPL(name, spec) \
  WG_PP_LCLCLASS_CMNIMPL(name, 0, spec)

#define WG_PP_LCLCLASS_TPL_IMPL(name, spec) \
  WG_PP_LCLCLASS_CMNIMPL(name, 1, spec)

#define WG_PP_LCLCLASS_CMNIMPL(name, istpl, spec) \
  WG_PP_LCLCLASS_EXPAND1( \
    WG_PP_LCLCLASS_CMNIMPL_ERRORPASS \
    BOOST_PP_LPAREN() \
      name BOOST_PP_COMMA() \
      istpl BOOST_PP_COMMA() \
      BOOST_PP_SEQ_ENUM(WG_PP_LCLCLASS_SPEC_NORMALIZE(spec, istpl)) \
    BOOST_PP_RPAREN() )

#define WG_PP_LCLCLASS_CMNIMPL_ERRORPASS( \
  name, \
  istpl, \
  m1, derives_seq, \
  m2, memext_seq, \
  m3, memint_seq, \
  m4, baseinit_seq, \
  errors, error_seq) \
    WG_PP_LCLCLASS_CMNIMPL_REPORTERROR_OR_CONTINUE( \
      name, \
      istpl, \
      derives_seq, \
      memext_seq, \
      memint_seq, \
      baseinit_seq, \
      WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLESEQ(memext_seq) \
      WG_PP_ERRORREPORTER_REPORT_NRMLZDSETTUPLESEQ(memint_seq) \
      WG_PP_ERRORREPORTER_REPORT_ERRORSEQ(error_seq) BOOST_PP_NIL)

#define WG_PP_LCLCLASS_CMNIMPL_REPORTERROR_OR_CONTINUE(\
  name, \
  istpl, \
  derives_seq, \
  memext_seq, \
  memint_seq, \
  baseinit_seq, \
  psbl_error_tokens) \
    BOOST_PP_IIF( \
      WG_PP_STARTSWITH_BOOST_PP_NIL(psbl_error_tokens), \
      WG_PP_LCLCLASS_CMNIMPL_STARTCODEGEN, \
      WG_PP_LCLCLASS_CMNIMPL_REPORTERRORS) \
    ( \
      name, \
      istpl, \
      derives_seq, \
      memext_seq, \
      memint_seq, \
      baseinit_seq, \
      psbl_error_tokens \
    )

#define WG_PP_LCLCLASS_CMNIMPL_REPORTERRORS( \
  name, \
  istpl, \
  derives_seq, \
  memext_seq, \
  memint_seq, \
  baseinit_seq, \
  psbl_error_tokens) \
    WG_PP_EATTAILTOKEN_BOOST_PP_NIL(psbl_error_tokens)

#define WG_PP_LCLCLASS_CMNIMPL_STARTCODEGEN( \
  name, \
  istpl, \
  derives_seq, \
  memext_seq, \
  memint_seq, \
  baseinit_seq, \
  psbl_error_tokens) \
    WG_PP_LCLCLASS_CODEGEN_START( \
      name, \
      WG_PP_LCLCLASS_SYMBOLTABLE_CREATE( \
        istpl, \
        derives_seq, \
        memext_seq, \
        memint_seq, \
        baseinit_seq) )

#define WG_PP_LCLCLASS_END_IMPL() \
  WG_PP_LCLCLASS_CODEGEN_END()

#endif /* WG_LCLCLASS_HH_ */
