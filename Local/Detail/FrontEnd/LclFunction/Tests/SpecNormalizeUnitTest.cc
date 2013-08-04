#include "../SpecNormalize.hh"

//Unit Tests
#define T1 return (int)
#define T2 params ((int x))
#define T3 params ((int x, long y))
#define T4 varbind ((long) b) (c)
#define T5 varbind ((long) b) (ref c)
#define T6 varset ((int) x, 7)
#define T7 varset ((int) x, 7) (y, 8.9f)

WG_PP_LCLFUNCTION_SPEC_NORMALIZE(void, 0)
BOOST_PP_EXPAND(WG_PP_LCLFUNCTION_SPEC_NORMALIZE(T1, 0))
BOOST_PP_EXPAND(WG_PP_LCLFUNCTION_SPEC_NORMALIZE(T2, 0))
BOOST_PP_EXPAND(WG_PP_LCLFUNCTION_SPEC_NORMALIZE(T3, 0))
BOOST_PP_EXPAND(WG_PP_LCLFUNCTION_SPEC_NORMALIZE(T4, 0))
BOOST_PP_EXPAND(WG_PP_LCLFUNCTION_SPEC_NORMALIZE(T5, 0))
BOOST_PP_EXPAND(WG_PP_LCLFUNCTION_SPEC_NORMALIZE(T6, 0))
BOOST_PP_EXPAND(WG_PP_LCLFUNCTION_SPEC_NORMALIZE(T7, 0))

/*
//EXPECTED:
(return) (BOOST_PP_NIL) (params) (BOOST_PP_NIL) (varbind) (BOOST_PP_NIL) (varset) (BOOST_PP_NIL) (errors) ( BOOST_PP_NIL )
(return) ( int ) (params) (BOOST_PP_NIL) (varbind) (BOOST_PP_NIL) (varset) (BOOST_PP_NIL) (errors) ( BOOST_PP_NIL )
(return) (BOOST_PP_NIL) (params) ( (int x) ) (varbind) (BOOST_PP_NIL) (varset) (BOOST_PP_NIL) (errors) ( BOOST_PP_NIL )
(return) (BOOST_PP_NIL) (params) ( (int x, long y) ) (varbind) (BOOST_PP_NIL) (varset) (BOOST_PP_NIL) (errors) ( BOOST_PP_NIL )
(return) (BOOST_PP_NIL) (params) (BOOST_PP_NIL) (varbind) ( (long) (b) ( WG_PP_DEDUCEDTYPE __typeof__(boost::type_of::ensure_obj(c)) ) (c) ) (varset) (BOOST_PP_NIL) (errors) ( BOOST_PP_NIL )
(return) (BOOST_PP_NIL) (params) (BOOST_PP_NIL) (varbind) ( (long) (b) ( WG_PP_DEDUCEDTYPE boost::add_reference< __typeof__(boost::type_of::ensure_obj(c)) >::type ) (c) ) (varset) (BOOST_PP_NIL) (errors) ( BOOST_PP_NIL )
(return) (BOOST_PP_NIL) (params) (BOOST_PP_NIL) (varbind) (BOOST_PP_NIL) (varset) ( (int) (x) (7) ) (errors) ( BOOST_PP_NIL )
(return) (BOOST_PP_NIL) (params) (BOOST_PP_NIL) (varbind) (BOOST_PP_NIL) (varset) ( (int) (x) (7) ( WG_PP_DEDUCEDTYPE __typeof__(boost::type_of::ensure_obj(8.9f)) ) (y) (8.9f) ) (errors) ( BOOST_PP_NIL )
*/
