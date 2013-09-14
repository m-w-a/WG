#include <WG/Local/AutoFunctor.hh>
#include <WG/Local/Tests/test.h>
#include <WG/Local/Detail/PP/TokenMatching.hh>

#define \
  WG_PP_REFTHISU_TOKENMATCH_BEGINSWITH_ERROR_ref_keyword_cannot_be_used_with_thisu_keyword \
    WG_PP_TOKENMATCH_FRONTMATCH
#define WG_PP_KEYWORDS_STARTSWITH_REFTHISU_ERRMSG(tokens) \
  WG_PP_TOKENMATCH_BEGINSWITH(\
    tokens, \
    WG_PP_REFTHISU_TOKENMATCH_BEGINSWITH_)

// Illegal usage of "ref this_" in parambind.
BEGIN WG_PP_KEYWORDS_STARTSWITH_REFTHISU_ERRMSG(
  WG_AUTOFUNCTOR(test, parambind (ref this_) ) ) == 1 END

// Illegal usage of "ref this_" in membind.
BEGIN WG_PP_KEYWORDS_STARTSWITH_REFTHISU_ERRMSG( \
  WG_AUTOFUNCTOR(test, membind (ref this_) ) ) == 1 END
