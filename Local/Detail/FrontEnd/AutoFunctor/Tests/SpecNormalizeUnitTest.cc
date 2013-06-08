#include "../SpecNormalize.hh"

//Unit Tests
#define T1 assignto (x)
#define T2 return (float)
#define T3 parambind (b)
#define T4 parambind ((long) b) (c)
#define T5 paramset ((int) x, 7)
#define T6 paramset ((int) x, 7) (local(Callback) y, 8)

#pragma wave trace(enable)
WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE(void)
BOOST_PP_EXPAND(WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE(T1))
BOOST_PP_EXPAND(WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE(T2))
BOOST_PP_EXPAND(WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE(T3))
BOOST_PP_EXPAND(WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE(T4))
BOOST_PP_EXPAND(WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE(T5))
BOOST_PP_EXPAND(WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE(T6))
#pragma wave trace(disable)

/*
//EXPECTED:
//See WG_PP_AUTOFUNCTOR_SPEC_NORMALIZE description.

(assignto) (BOOST_PP_NIL) (return) (BOOST_PP_NIL) (parambind) (BOOST_PP_NIL) (paramset) (BOOST_PP_NIL) (membind) (BOOST_PP_NIL) (memset) (BOOST_PP_NIL)
(assignto) ((BOOST_TYPEOF(x)) (x)) (return) (void) (parambind) (BOOST_PP_NIL) (paramset) (BOOST_PP_NIL) (membind) (BOOST_PP_NIL) (memset) (BOOST_PP_NIL)
(assignto) (BOOST_PP_NIL) (return) (float) (parambind) (BOOST_PP_NIL) (paramset) (BOOST_PP_NIL) (membind) (BOOST_PP_NIL) (memset) (BOOST_PP_NIL)
(assignto) (BOOST_PP_NIL) (return) (BOOST_PP_NIL) (parambind) ((BOOST_TYPEOF(b)) ) (b)) (paramset) (BOOST_PP_NIL) (membind) (BOOST_PP_NIL) (memset) (BOOST_PP_NIL)
(assignto) (BOOST_PP_NIL) (return) (BOOST_PP_NIL) (parambind) ((long) (b) (BOOST_TYPEOF(c)) ) (c)) (paramset) (BOOST_PP_NIL) (membind) (BOOST_PP_NIL) (memset) (BOOST_PP_NIL)
(assignto) (BOOST_PP_NIL) (return) (BOOST_PP_NIL) (parambind) (BOOST_PP_NIL) (paramset) ((int) (x) (7)) (membind) (BOOST_PP_NIL) (memset) (BOOST_PP_NIL)
(assignto) (BOOST_PP_NIL) (return) (BOOST_PP_NIL) (parambind) (BOOST_PP_NIL) (paramset) ((int) (x) (7) (local(Callback)) ( y ) (8)) (membind) (BOOST_PP_NIL) (memset) (BOOST_PP_NIL)
*/

//TODO
