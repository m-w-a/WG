#include <WG/Local/Tests/Utils/PreprocessorUnitTester.hh>
#include <WG/Local/Detail/PP/Translator/FrontEnd/LclClass/Keywords.hh>

BEGIN WG_PP_LCLCLASS_KEYWORDS_EAT_HEADKEYWORD(derives 1) END
BEGIN WG_PP_LCLCLASS_KEYWORDS_EAT_HEADKEYWORD(memext 1) END
BEGIN WG_PP_LCLCLASS_KEYWORDS_EAT_HEADKEYWORD(memint 1) END
BEGIN WG_PP_LCLCLASS_KEYWORDS_EAT_HEADKEYWORD(baseinit 1) END

BEGIN WG_PP_LCLCLASS_KEYWORDS_STARTSWITH_DERIVES(derives foo) END
BEGIN WG_PP_LCLCLASS_KEYWORDS_STARTSWITH_MEMEXT(memext foo) END
BEGIN WG_PP_LCLCLASS_KEYWORDS_STARTSWITH_MEMINT(memint foo) END
BEGIN WG_PP_LCLCLASS_KEYWORDS_STARTSWITH_BASEINIT(baseinit foo) END
