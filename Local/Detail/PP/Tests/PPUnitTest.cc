#include <WG/Local/Tests/test.h>
#include <WG/Local/Detail/PP.hh>

// WG_PP_START_WITH_WG_PP_TRUE
BEGIN WG_PP_START_WITH_WG_PP_TRUE(WG_PP_TRUE foo) == 1 END

// WG_PP_START_WITH_BOOST_PP_NIL
BEGIN WG_PP_START_WITH_BOOST_PP_NIL(BOOST_PP_NIL foo) == 1 END

// WG_PP_EATHEADTOKEN_BOOST_PP_NIL
BEGIN WG_PP_EATHEADTOKEN_BOOST_PP_NIL(BOOST_PP_NIL 1) == 1 END

// WG_PP_START_WITH_WG_PP_DEDUCEDTYPE
BEGIN WG_PP_START_WITH_WG_PP_DEDUCEDTYPE(WG_PP_DEDUCEDTYPE foo) == 1 END

// WG_PP_EATHEADTOKEN_WG_PP_DEDUCEDTYPE
BEGIN WG_PP_EATHEADTOKEN_WG_PP_DEDUCEDTYPE(WG_PP_DEDUCEDTYPE 1) == 1 END

// WG_PP_ISNEXTTOKEN_A_TUPLE
BEGIN WG_PP_ISNEXTTOKEN_A_TUPLE(1, BOOST_PP_NIL) == 0 END
BEGIN WG_PP_ISNEXTTOKEN_A_TUPLE(1, (foo) BOOST_PP_NIL) == 1 END
BEGIN WG_PP_ISNEXTTOKEN_A_TUPLE(2, BOOST_PP_NIL) == 0 END
BEGIN WG_PP_ISNEXTTOKEN_A_TUPLE(2, (foo, bar) BOOST_PP_NIL) == 1 END
