#include <WG/Local/Detail/PP/Translator/FrontEnd/LclClass/SpecNormalize.hh>

//Unit Tests
#define D1 derives (foo)
#define D2 derives (public foo) (virtual bar) (private virtual ::bat<man>)
#define ML1 memlike (b)
#define ML2 memlike ((long) b) (c)
#define MS1 memset (x, 7)
#define MS2 memset ((int) x, 7) (local(Callback) y, 8)

BOOST_PP_EXPAND(WG_PP_LCLCLASS_SPEC_NORMALIZE(D1, 0))
BOOST_PP_EXPAND(WG_PP_LCLCLASS_SPEC_NORMALIZE(D2, 0))
BOOST_PP_EXPAND(WG_PP_LCLCLASS_SPEC_NORMALIZE(ML1, 0))
BOOST_PP_EXPAND(WG_PP_LCLCLASS_SPEC_NORMALIZE(ML2, 0))
BOOST_PP_EXPAND(WG_PP_LCLCLASS_SPEC_NORMALIZE(MS1, 0))
BOOST_PP_EXPAND(WG_PP_LCLCLASS_SPEC_NORMALIZE(MS2, 0))

/*
//EXPECTED:
(derives) ( foo ) (memlike) (BOOST_PP_NIL) (memset) (BOOST_PP_NIL) (errors) ( BOOST_PP_NIL )
(derives) ( public foo virtual bar private virtual ::bat<man> ) (memlike) (BOOST_PP_NIL) (memset) (BOOST_PP_NIL) (errors) ( BOOST_PP_NIL )
(derives) (BOOST_PP_NIL) (memlike) ( ( WG_PP_DEDUCEDTYPE ( BOOST_TYPEOF(b) ) (b) ) (memset) (BOOST_PP_NIL) (errors) ( BOOST_PP_NIL )
(derives) (BOOST_PP_NIL) (memlike) ( (WG_PP_NOOP (long)) ( b ) ( WG_PP_DEDUCEDTYPE ( BOOST_TYPEOF(c)) ) ) (c) ) (memset) (BOOST_PP_NIL) (errors) ( BOOST_PP_NIL )
(derives) (BOOST_PP_NIL) (memlike) (BOOST_PP_NIL) (memset) ( ( WG_PP_DEDUCEDTYPE ( BOOST_TYPEOF(7)) ) ) (x) (7) ) (errors) ( BOOST_PP_NIL )
(derives) (BOOST_PP_NIL) (memlike) (BOOST_PP_NIL) (memset) ( (WG_PP_NOOP (int)) ( x ) (7) ( WG_PP_NOOP local (Callback) ) (y) (8) ) (errors) ( BOOST_PP_NIL )
*/
