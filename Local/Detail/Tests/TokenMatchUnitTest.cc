#include "test.h"
#include <WG/Local/Detail/TokenMatching.hh>

//---------------------------
//WG_PP_TOKENMATCH_BEGINSWITH
//---------------------------

#define WG_PP_TOKENMATCH_TEST_const_const ) (
#define WG_PP_TOKENMATCH_TEST_BEGINSWITHCONST(tokens) \
  WG_PP_TOKENMATCH_BEGINSWITH(tokens, WG_PP_TOKENMATCH_TEST_const_)

#define SingleTokenNoFrontMatch const_
BEGIN WG_PP_TOKENMATCH_TEST_BEGINSWITHCONST(SingleTokenNoFrontMatch) == 0 END

#define SingleTokenFrontMatch const
BEGIN WG_PP_TOKENMATCH_TEST_BEGINSWITHCONST(SingleTokenFrontMatch) == 1 END

#define MultiTokenNoFrontMatch const_ foo bar
BEGIN WG_PP_TOKENMATCH_TEST_BEGINSWITHCONST(MultiTokenNoFrontMatch) == 0 END

#define MultiTokenFrontMatch const foo bar
BEGIN WG_PP_TOKENMATCH_TEST_BEGINSWITHCONST(MultiTokenFrontMatch) == 1 END

//-------------------------
//WG_PP_TOKENMATCH_ENDSWITH
//-------------------------

#define const_const_WG_PP_TOKENMATCH_TEST ) (
#define WG_PP_TOKENMATCH_TEST_ENDSWITHCONST(tokens) \
  WG_PP_TOKENMATCH_ENDSWITH(tokens, _const_WG_PP_TOKENMATCH_TEST)

#define SingleTokenNoEndMatch _const
BEGIN WG_PP_TOKENMATCH_TEST_ENDSWITHCONST(SingleTokenNoEndMatch) == 0 END

#define SingleTokenEndMatch const
BEGIN WG_PP_TOKENMATCH_TEST_ENDSWITHCONST(SingleTokenEndMatch) == 1 END

#define MultiTokenNoEndMatch foo bar const_
BEGIN WG_PP_TOKENMATCH_TEST_ENDSWITHCONST(MultiTokenNoEndMatch) == 0 END

#define MultiTokenEndMatch foo bar const
BEGIN WG_PP_TOKENMATCH_TEST_ENDSWITHCONST(MultiTokenEndMatch) == 1 END
