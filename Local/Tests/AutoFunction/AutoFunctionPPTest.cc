//******************************************************************************
//Note: this file is not meant to be compiled.
//  It is to be used for preprocessing tests only.
//******************************************************************************

#include <boost/preprocessor.hpp>
//#include <WG/Local/AutoFunction.hh>
#include <WG/Local/AutoFunction2.hh>
//#include <boost/type_traits/add_const.hpp>
//#include <boost/type_traits/add_reference.hpp>
//#include <boost/local_function.hpp>
//TESTS Begin

int main()
{
/*
  WG_AUTOFUNCTION(noParamsArg, (void), (void))
  {
  }WG_AUTOFUNCTION_END;
//  __LINE__
*/
  
/*
  WG_AUTOFUNCTION(oneBoundArg, (bool)(didArgumentBind) (int)(y2), (void))
  {
  } WG_AUTOFUNCTION_END;
//  __LINE__

  WG_AUTOFUNCTION(oneAssignedArg, (void), (int)(age, 10))
  {
  } WG_AUTOFUNCTION_END;
//  __LINE__

  WG_AUTOFUNCTION(
    generalAutoFunction, 
    (bool)(didArgumentBind), 
    (int)(age, 10))
  {
  } WG_AUTOFUNCTION_END;
//  __LINE__
  
  WG_AUTOFUNCTION(keywordBoundArg, (MyClass)(this_), (void))
  {
  }WG_AUTOFUNCTION_END;
//  __LINE__
*/

  return 0;
}

