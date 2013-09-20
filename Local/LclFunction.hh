#ifndef WG_LCLFUNCTION_HH_
#define WG_LCLFUNCTION_HH_

#include <boost/config.hpp>

#if BOOST_NO_CXX11_VARIADIC_TEMPLATES
  #include <WG/Local/Detail/PP/Translator/BackEnd/LclFunction/CodeGenCPP03.hh>
#else
  //#include <WG/Local/Detail/PP/Translator/BackEnd/LclFunction/CodeGenCPP11.hh>
#endif

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/Translator/FrontEnd/ErrorReporter.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/LclFunction/SpecNormalize.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/LclFunction/SymbolTable.hh>

//###########
//Public APIs
//###########

#ifndef WG_PP_LCLFUNCTION_MAX_ARGS
  #define WG_PP_LCLFUNCTION_MAX_ARGS 15
#endif

#define WG_LCLFUNCTION(name, spec) \
  WG_PP_LCLFUNCTION_IMPL(name, spec)

#define WG_LCLFUNCTION_TPL(name, spec) \
  WG_PP_LCLFUNCTION_TPL_IMPL(name, spec)

//###########
//Impl Macros
//###########

#define WG_PP_LCLFUNCTION_EXPAND1(x) x

#define WG_PP_LCLFUNCTION_IMPL(name, spec) \
  WG_PP_LCLFUNCTION_CMNIMPL(name, 0, spec)

#define WG_PP_LCLFUNCTION_TPL_IMPL(name, spec) \
  WG_PP_LCLFUNCTION_CMNIMPL(name, 1, spec)

#define WG_PP_LCLFUNCTION_CMNIMPL(name, istpl, spec) \
  WG_PP_LCLFUNCTION_EXPAND1( \
    WG_PP_LCLFUNCTION_ERRORPASS \
    BOOST_PP_LPAREN() \
      name BOOST_PP_COMMA() \
      istpl BOOST_PP_COMMA() \
      BOOST_PP_SEQ_ENUM( WG_PP_LCLFUNCTION_SPEC_NORMALIZE(spec, istpl) ) \
    BOOST_PP_RPAREN() )

#define WG_PP_LCLFUNCTION_ERRORPASS( \
  name, \
  istpl, \
  m1, return_type, \
  m2, params_seq, \
  m3, varbind_seq, \
  m4, varset_seq, \
  errors, error_seq) \
    WG_PP_LCLFUNCTION_REPORTERROR_OR_CONTINUE( \
      name, istpl, return_type, params_seq, varbind_seq, varset_seq, \
      WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLESEQ(params_seq) \
      WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLESEQ(varbind_seq) \
      WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLESEQ(varset_seq) \
      WG_PP_ERRORREPORTER_REPORT_NRMLZDBNDTUPLESEQ(error_seq) BOOST_PP_NIL )

#define WG_PP_LCLFUNCTION_REPORTERROR_OR_CONTINUE( \
  name, istpl, return_type, params_seq, varbind_seq, varset_seq, \
  psbl_error_tokens) \
    BOOST_PP_IIF( \
      WG_PP_STARTS_WITH_BOOST_PP_NIL(psbl_error_tokens), \
      WG_PP_LCLFUNCTION_STARTCODEGEN, \
      WG_PP_LCLFUNCTION_REPORTERRORS) \
    ( \
      name, istpl, return_type, params_seq, varbind_seq, varset_seq, \
      psbl_error_tokens \
    )

#define WG_PP_LCLFUNCTION_REPORTERRORS( \
  name, istpl, return_type, params_seq, varbind_seq, varset_seq, \
  psbl_error_tokens) \
    psbl_error_tokens

#define WG_PP_LCLFUNCTION_STARTCODEGEN( \
  name, istpl, return_type, params_seq, varbind_seq, varset_seq, \
  psbl_error_tokens) \
    WG_PP_LCLFUNCTION_CODEGEN_START( \
      name, \
      WG_PP_LCLFUNCTION_SYMBOLTABLE_CREATE( \
        istpl, return_type, params_seq, varbind_seq, varset_seq) )

#define WG_PP_LCLFUNCTION_END_IMPL() \
  WG_PP_LCLFUNCTION_CODEGEN_END()

#endif /* WG_LCLFUNCTION_HH_ */
