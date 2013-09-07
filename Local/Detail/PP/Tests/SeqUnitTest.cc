#include <WG/Local/Tests/test.h>
#include <WG/Local/Detail/PP/Seq.hh>

int const BOOST_PP_NIL = 123456789;

#define SN1 BOOST_PP_NIL
#define SN2 BOOST_PP_NIL
#define S1 (1)
#define S2 (2)(3)
#define S3 (4)(5)(6)

// SEQ_IFNIL_THENCLEAR
BEGIN WG_PP_SEQ_IFNIL_THENCLEAR(SN1) 11 == 11 END
BEGIN WG_PP_SEQ_CAT( WG_PP_SEQ_IFNIL_THENCLEAR(S2) ) == 23 END

// SEQ_IFNIL_THENMAPTO
BEGIN WG_PP_SEQ_IFNIL_THENMAPTO(SN1, 1) == 1 END
BEGIN WG_PP_SEQ_CAT(WG_PP_SEQ_IFNIL_THENMAPTO(S2, 1)) == 23 END

// SEQ_IS_INDEX_LAST
BEGIN WG_PP_SEQ_IS_INDEX_LAST(3, 1) == 0 END
BEGIN WG_PP_SEQ_IS_INDEX_LAST(3, 2) == 1 END

// SEQ_CAT
BEGIN WG_PP_SEQ_CAT(SN1) == BOOST_PP_NIL END
BEGIN WG_PP_SEQ_CAT(S1) == 1 END
BEGIN WG_PP_SEQ_CAT(S2) == 23 END

// SEQ_ELEM
BEGIN WG_PP_SEQ_ELEM(1, SN1) == BOOST_PP_NIL END
BEGIN WG_PP_SEQ_ELEM(BOOST_PP_NIL, S2) == BOOST_PP_NIL END
BEGIN WG_PP_SEQ_ELEM(1, S3) == 5 END

// SEQ_JOIN
BEGIN WG_PP_SEQ_JOIN(SN1,SN2) == BOOST_PP_NIL END
BEGIN WG_PP_SEQ_CAT( WG_PP_SEQ_JOIN(SN1,S1) ) == 1 END
BEGIN WG_PP_SEQ_CAT( WG_PP_SEQ_JOIN3(SN1, S1, S2) ) == 123 END
BEGIN WG_PP_SEQ_CAT( WG_PP_SEQ_JOIN4(SN1, S1, S2, S3) ) == 123456 END

// SEQ_REPLACE
BEGIN WG_PP_SEQ_REPLACE(SN1, 0, foo) == BOOST_PP_NIL END
BEGIN WG_PP_SEQ_REPLACE(S1, BOOST_PP_NIL, bar) == 1 END
BEGIN WG_PP_SEQ_CAT( WG_PP_SEQ_REPLACE(S2, 1, 5) ) == 25 END

// SEQ_SIZE
BEGIN WG_PP_SEQ_SIZE(SN1) == 0 END
BEGIN WG_PP_SEQ_SIZE(S3) == 3 END

//TODO:
//WG_PP_SEQ_TRANSFORM
