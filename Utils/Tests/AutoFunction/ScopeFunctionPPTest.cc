//Note: this file is not meant to be compiled.
//  It is to be used for preprocessing tests only.

#include <WG/AutoFunction.hh>

//TESTS Begin

#define TEST_SEQ (w)(x) (y)(z) (a)(b) (c)(d) (class)(this_)
#define ASEQ (T1)(t, foo.bar) (T2)(q, this->foo())

WG_AUTOFUNCTION(foo, TEST_SEQ, ASEQ)
{
}
//WG_AUTOFUNCTION_END()
WG_AUTOFUNCTION(foo, (void), (void))
{
}
//WG_AUTOFUNCTION_END()
