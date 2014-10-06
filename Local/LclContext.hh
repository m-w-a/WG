#ifndef WG_LCLCONTEXT_HH_
#define WG_LCLCONTEXT_HH_

#include <boost/preprocessor.hpp>
#include <WG/Local/Detail/PP/Translator/FrontEnd/LclContext/SpecNormalize.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/ErrorReporter.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/LclContext/SymbolTable.hh>
#include <WG/Local/Detail/PP/PP.hh>
#include <WG/Local/Detail/PP/Utils.hh>
#include <WG/Local/Detail/PP/Translator/BackEnd/LclContext/CodeGen.hh>

//###########
//Public APIs
//###########

#define WG_LCLCONTEXT(spec) \
  WG_PP_LCLCONTEXT_IMPL(0, spec)

#define WG_LCLCONTEXT_TPL(spec) \
  WG_PP_LCLCONTEXT_IMPL(1, spec)

#define WG_LCLCONTEXT_END1 \
  WG_PP_LCLCONTEXT_CODEGEN_END(1)

#define WG_LCLCONTEXT_END2 \
  WG_PP_LCLCONTEXT_CODEGEN_END(2)

#define WG_LCLCONTEXT_END3 \
  WG_PP_LCLCONTEXT_CODEGEN_END(3)

#define WG_LCLCONTEXT_END4 \
  WG_PP_LCLCONTEXT_CODEGEN_END(4)

#define WG_LCLCONTEXT_END5 \
  WG_PP_LCLCONTEXT_CODEGEN_END(5)

#define WG_LCLCONTEXT_END6 \
  WG_PP_LCLCONTEXT_CODEGEN_END(6)

#define WG_LCLCONTEXT_END7 \
  WG_PP_LCLCONTEXT_CODEGEN_END(7)

#define WG_LCLCONTEXT_END8 \
  WG_PP_LCLCONTEXT_CODEGEN_END(8)

#define WG_LCLCONTEXT_END9 \
  WG_PP_LCLCONTEXT_CODEGEN_END(9)

#define WG_LCLCONTEXT_END10 \
  WG_PP_LCLCONTEXT_CODEGEN_END(10)

//###########
//Impl Macros
//###########

#define WG_PP_LCLCONTEXT_EXPAND1(x) x

#define WG_PP_LCLCONTEXT_IMPL(istpl, spec) \
  WG_PP_LCLCONTEXT_EXPAND1( \
    WG_PP_LCLCONTEXT_ERROR_PASS \
    BOOST_PP_LPAREN() \
    istpl BOOST_PP_COMMA() \
    BOOST_PP_SEQ_ENUM( WG_PP_LCLCONTEXT_SPECPARSER_PARSE(spec, istpl) ) \
    BOOST_PP_RPAREN() )

#define WG_PP_LCLCONTEXT_ERROR_PASS( \
  istpl, \
  m1, extantsymbolcount, \
  m2, adhocsymbolcount, \
  m3, symbolseq) \
    WG_PP_LCLCONTEXT_REPORTERROR_OR_CONTINUE( \
      istpl, extantsymbolcount, adhocsymbolcount, symbolseq, \
      WG_PP_LCLCONTEXT_REPORTERROR_SYMBOLS(symbolseq) \
      BOOST_PP_NIL )

#define WG_PP_LCLCONTEXT_REPORTERROR_OR_CONTINUE( \
  istpl, extantsymbolcount, adhocsymbolcount, symbolseq, psbl_error_tokens) \
    BOOST_PP_IIF( \
      WG_PP_STARTSWITH_BOOST_PP_NIL(psbl_error_tokens), \
      WG_PP_LCLCONTEXT_STARTCODEGEN, \
      WG_PP_LCLCONTEXT_REPORTERRORS) \
    (istpl, extantsymbolcount, adhocsymbolcount, symbolseq, psbl_error_tokens)

#define WG_PP_LCLCONTEXT_REPORTERRORS( \
  istpl, extantsymbolcount, adhocsymbolcount, symbolseq, psbl_error_tokens) \
    WG_PP_EATTAILTOKEN_BOOST_PP_NIL(psbl_error_tokens)

#define WG_PP_LCLCONTEXT_STARTCODEGEN( \
  istpl, extantsymbolcount, adhocsymbolcount, symbolseq, psbl_error_tokens) \
    WG_PP_LCLCONTEXT_STARTCODEGEN2( \
      istpl, extantsymbolcount, adhocsymbolcount, \
      WG_PP_UTILS_SEQ_REMOVEHEADMARKERS(symbolseq) )

#define WG_PP_LCLCONTEXT_STARTCODEGEN2( \
  istpl, extantsymbolcount, adhocsymbolcount, symbolseq) \
    WG_PP_LCLCONTEXT_CODEGEN_START( \
      WG_PP_LCLCONTEXT_SYMBOLTABLE_CREATE( \
        istpl, extantsymbolcount, adhocsymbolcount, symbolseq))

//------------------------------------
//WG_PP_LCLCONTEXT_REPORTERROR_SYMBOLS
//------------------------------------

#define WG_PP_LCLCONTEXT_REPORTERROR_SYMBOLS(symbolseq) \
  BOOST_PP_SEQ_FOR_EACH( \
    WG_PP_LCLCONTEXT_REPORTERROR_SYMBOLS_ENTRY, \
    ~, \
    symbolseq)

// BOOST_PP_SEQ_FOR_EACH functor.
#define WG_PP_LCLCONTEXT_REPORTERROR_SYMBOLS_ENTRY(r, data, symbol) \
  WG_PP_ERRORREPORTER_REPORT_ERRORTOKENS(symbol)

#endif /* WG_LCLCONTEXT_HH_ */
