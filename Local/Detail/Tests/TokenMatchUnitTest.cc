#include "test.h"
#include <WG/Local/Detail/TokenMatching.hh>

//---------------------------
//WG_PP_TOKENMATCH_BEGINSWITH
//---------------------------

#define WG_PP_TOKENMATCH_TEST_const_const WG_PP_TOKENMATCH_FRONTMATCH
#define WG_PP_TOKENMATCH_TEST_BEGINSWITHCONST(tokens) \
  WG_PP_TOKENMATCH_BEGINSWITH(tokens, WG_PP_TOKENMATCH_TEST_const_)

#define SingleTokenNoFrontMatch const_
#define SingleTokenFrontMatch const
#define MultiTokenNoFrontMatch const_ foo bar
#define MultiTokenFrontMatch const foo bar

BEGIN WG_PP_TOKENMATCH_TEST_BEGINSWITHCONST(SingleTokenNoFrontMatch) == 0 END
BEGIN WG_PP_TOKENMATCH_TEST_BEGINSWITHCONST(SingleTokenFrontMatch) == 1 END
BEGIN WG_PP_TOKENMATCH_TEST_BEGINSWITHCONST(MultiTokenNoFrontMatch) == 0 END
BEGIN WG_PP_TOKENMATCH_TEST_BEGINSWITHCONST(MultiTokenFrontMatch) == 1 END

//-------------------------
//WG_PP_TOKENMATCH_ENDSWITH
//-------------------------

#define const_const_WG_PP_TOKENMATCH_TEST WG_PP_TOKENMATCH_ENDMATCH
#define WG_PP_TOKENMATCH_TEST_ENDSWITHCONST(tokens) \
  WG_PP_TOKENMATCH_ENDSWITH(tokens, _const_WG_PP_TOKENMATCH_TEST)

#define SingleTokenNoEndMatch _const
#define SingleTokenEndMatch const
#define MultiTokenNoEndMatch foo bar const_
#define MultiTokenEndMatch foo bar const

BEGIN WG_PP_TOKENMATCH_TEST_ENDSWITHCONST(SingleTokenNoEndMatch) == 0 END
BEGIN WG_PP_TOKENMATCH_TEST_ENDSWITHCONST(SingleTokenEndMatch) == 1 END
BEGIN WG_PP_TOKENMATCH_TEST_ENDSWITHCONST(MultiTokenNoEndMatch) == 0 END
BEGIN WG_PP_TOKENMATCH_TEST_ENDSWITHCONST(MultiTokenEndMatch) == 1 END

//------------------------
//WG_PP_TOKENMATCH_MATCHES
//------------------------

#define WG_PP_TOKENMATCH_TEST2_const_const WG_PP_TOKENMATCH_EXACTMATCH
#define WG_PP_TOKENMATCH_TEST_MATCHESCONST(tokens) \
  WG_PP_TOKENMATCH_MATCHES(tokens, WG_PP_TOKENMATCH_TEST2_const_)

#define SingleTokenNoExactMatch1 const_
#define SingleTokenNoExactMatch2 lconst
#define SingleTokenExactMatch const
#define MultiTokenNoExactMatchButFrontMatch const a b c
#define MultiTokenNoExactMatchButEndMatch a b c const
#define MultiTokenNoExactMatchButMiddleMatch a b const c d

BEGIN WG_PP_TOKENMATCH_TEST_MATCHESCONST(SingleTokenNoExactMatch1) == 0 END
BEGIN WG_PP_TOKENMATCH_TEST_MATCHESCONST(SingleTokenNoExactMatch2) == 0 END
BEGIN WG_PP_TOKENMATCH_TEST_MATCHESCONST(SingleTokenExactMatch) == 1 END
BEGIN WG_PP_TOKENMATCH_TEST_MATCHESCONST(MultiTokenNoExactMatchButFrontMatch) == 0 END
BEGIN WG_PP_TOKENMATCH_TEST_MATCHESCONST(MultiTokenNoExactMatchButEndMatch) == 0 END
BEGIN WG_PP_TOKENMATCH_TEST_MATCHESCONST(MultiTokenNoExactMatchButMiddleMatch) == 0 END
