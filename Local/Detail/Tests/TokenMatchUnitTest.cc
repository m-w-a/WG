#include "test.h"
#include <WG/Local/Detail/TokenMatching.hh>

//-------------------------
//WG_PP_TOKENMATCH_ENDSWITH
//-------------------------

#define const_const_WG_PP_TOKENMATCH_TEST ) (
#define WG_PP_TOKENS_END_WITH_CONST(tokens) \
  WG_PP_TOKENMATCH_ENDSWITH(tokens, _const_WG_PP_TOKENMATCH_TEST)

#define SingleTokenNoEndMatch _const
BEGIN WG_PP_TOKENS_END_WITH_CONST(SingleTokenNoEndMatch) == 0 END

#define SingleTokenEndMatch const
BEGIN WG_PP_TOKENS_END_WITH_CONST(SingleTokenEndMatch) == 1 END

#define MultiTokenNoEndMatch foo bar const_
BEGIN WG_PP_TOKENS_END_WITH_CONST(MultiTokenNoEndMatch) == 0 END

#define MultiTokenEndMatch foo bar const
BEGIN WG_PP_TOKENS_END_WITH_CONST(MultiTokenEndMatch) == 1 END
