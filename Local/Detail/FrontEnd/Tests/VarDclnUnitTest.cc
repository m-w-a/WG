#include <WG/Local/Detail/Tests/test.h>
#include "../VarDcln.hh"

//Unit Tests.
#define S1 (Foo *)
#define S2 local(Foo)
#define S2_1 local(Foo *) const
#define S2_2 local(Foo *) ref
#define S2_3 local(Foo *) const ref
#define S4 const
#define S5 ref
#define S6 const ref

/*
WG_PP_VARDCLN_ISEXPLICIT(S1)
WG_PP_VARDCLN_ISEXPLICIT(S2_1)
WG_PP_VARDCLN_ISEXPLICIT(S2_2)
WG_PP_VARDCLN_ISEXPLICIT(S2_3)
WG_PP_VARDCLN_ISEXPLICIT(S4)
WG_PP_VARDCLN_ISEXPLICIT(S5)
WG_PP_VARDCLN_ISEXPLICIT(S6)

//EXPECTED:
//1
//1
//1
//0
//0
//0
*/

BEGIN WG_PP_VARDCLN_ISEXPLICIT(S1) == 1 END
BEGIN WG_PP_VARDCLN_ISEXPLICIT(S2_1) == 1 END
BEGIN WG_PP_VARDCLN_ISEXPLICIT(S2_2) == 1 END
BEGIN WG_PP_VARDCLN_ISEXPLICIT(S2_3) == 1 END
BEGIN WG_PP_VARDCLN_ISEXPLICIT(S4) == 0 END
BEGIN WG_PP_VARDCLN_ISEXPLICIT(S5) == 0 END
BEGIN WG_PP_VARDCLN_ISEXPLICIT(S6) == 0 END
