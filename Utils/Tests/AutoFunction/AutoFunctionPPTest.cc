//******************************************************************************
//Note: this file is not meant to be compiled.
//  It is to be used for preprocessing tests only.
//******************************************************************************

#include <WG/Utils/AutoFunction.hh>

//TESTS Begin

#define TEST_SEQ (w)(x) (y)(z) (a)(b) (c)(d) (class)(this_)
#define ASEQ (T1)(t, foo.bar) (T2)(q, this->foo())
#define HUH (int)(age) (char)(c)
#define WTF (w)(x)

//WG_AUTOFUNCTION(foo, TEST_SEQ, ASEQ)
//{
//}
//WG_AUTOFUNCTION_END;

void int main()
{
  WG_AUTOFUNCTION(noParamsArg, (void), (void))
  {
  }WG_AUTOFUNCTION_END;
  __LINE__
  
  WG_AUTOFUNCTION(oneBoundArg, (bool)(didArgumentBind), (void))
  {
  } WG_AUTOFUNCTION_END;
  __LINE__
  
  WG_AUTOFUNCTION(oneAssignedArg, (void), (int)(age, 10))
  {
  } WG_AUTOFUNCTION_END;
  __LINE__
  
  WG_AUTOFUNCTION(
    generalAutoFunction, 
    (bool)(didArgumentBind), 
    (int)(age, 10))
  {
  } WG_AUTOFUNCTION_END;
  __LINE__;
  
  WG_AUTOFUNCTION(keywordBoundArg, (MyClass)(this_), (void))
  {
  }WG_AUTOFUNCTION_END;
  __LINE__;

  return 0;
}

