#include <WG/Local/Tests/test.h>
#include <WG/Local/Detail/PP/Translator/Keywords.hh>

BEGIN WG_PP_KEYWORDS_EATHEAD_VOID(void 1) END
BEGIN ! (WG_PP_KEYWORDS_STARTSWITH_VOID(WG_PP_KEYWORDS_EATHEAD_VOID(type void))) END

BEGIN WG_PP_KEYWORDS_EATHEAD_TYPE(type 1) END
BEGIN ! (WG_PP_KEYWORDS_STARTSWITH_VOID(WG_PP_KEYWORDS_EATHEAD_TYPE(void void))) END

BEGIN WG_PP_KEYWORDS_EATHEAD_CONST(const 1) END
BEGIN ! (WG_PP_KEYWORDS_STARTSWITH_VOID(WG_PP_KEYWORDS_EATHEAD_CONST(ref void))) END

BEGIN WG_PP_KEYWORDS_EATHEAD_REF(ref 1) END
BEGIN ! (WG_PP_KEYWORDS_STARTSWITH_VOID(WG_PP_KEYWORDS_EATHEAD_REF(const void))) END

BEGIN WG_PP_KEYWORDS_STARTSWITH_VOID(void foo) END
BEGIN ! (WG_PP_KEYWORDS_STARTSWITH_VOID(this_ foo)) END

BEGIN WG_PP_KEYWORDS_STARTSWITH_THISU(this_ foo) END
BEGIN ! (WG_PP_KEYWORDS_STARTSWITH_THISU(void foo)) END

BEGIN WG_PP_KEYWORDS_STARTSWITH_TYPE(type foo) END
BEGIN ! (WG_PP_KEYWORDS_STARTSWITH_TYPE(lcltype foo)) END

BEGIN WG_PP_KEYWORDS_STARTSWITH_LOCAL(local foo) END
BEGIN ! (WG_PP_KEYWORDS_STARTSWITH_LOCAL(type foo)) END

BEGIN WG_PP_KEYWORDS_STARTSWITH_CONST(const foo) END
BEGIN ! (WG_PP_KEYWORDS_STARTSWITH_CONST(ref foo)) END

BEGIN WG_PP_KEYWORDS_STARTSWITH_REF(ref foo) END
BEGIN ! (WG_PP_KEYWORDS_STARTSWITH_REF(const foo)) END
