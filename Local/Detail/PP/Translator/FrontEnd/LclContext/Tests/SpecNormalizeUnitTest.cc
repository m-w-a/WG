#include <WG/Local/Detail/PP/Translator/FrontEnd/LclContext/SpecNormalize.hh>

int main()
{

#define SPEC2 with(expr)
#define SPEC21 with(expr) entered_as(foo)
#define SPEC22 with(expr) entered_as(type(int) foo)

  //WG_PP_LCLCONTEXT_SPECPARSER_PARSE(SPEC2, 0, 0)
  //WG_PP_LCLCONTEXT_SPECPARSER_PARSE(SPEC21, 0, 0)
  //WG_PP_LCLCONTEXT_SPECPARSER_PARSE(SPEC22, 0, 0)

#define SPEC1 with_adhoc
#define SPEC11 with_adhoc onenter(xxx)
#define SPEC12 with_adhoc onexit(yyy)
#define SPEC13 with_adhoc onenter(xxx) onexit(yyy)

  //WG_PP_LCLCONTEXT_SPECPARSER_PARSE(SPEC1, 0, 0)
  //WG_PP_LCLCONTEXT_SPECPARSER_PARSE(SPEC11, 0, 0)
  //WG_PP_LCLCONTEXT_SPECPARSER_PARSE(SPEC12, 0, 0)
  //WG_PP_LCLCONTEXT_SPECPARSER_PARSE(SPEC13, 0, 0)

#define SPEC3 with_adhoc( (a) (type(int) b) )
#define SPEC31 with_adhoc( (a) (type(int) b) ) onenter(xxx)
#define SPEC32 with_adhoc( (a) (type(int) b) ) onexit(yyy)
#define SPEC33 with_adhoc( (a) (type(int) b) ) onenter(xxx) onexit(yyy)

  //WG_PP_LCLCONTEXT_SPECPARSER_PARSE(SPEC3, 0, 0)
  //WG_PP_LCLCONTEXT_SPECPARSER_PARSE(SPEC31, 0, 0)
  //WG_PP_LCLCONTEXT_SPECPARSER_PARSE(SPEC32, 0, 0)
  //WG_PP_LCLCONTEXT_SPECPARSER_PARSE(SPEC33, 0, 0)

  return 0;
}
