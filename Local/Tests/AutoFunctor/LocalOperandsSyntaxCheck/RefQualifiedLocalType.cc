#include <WG/Local/AutoFunctor.hh>

int main()
{
  struct SomeLocalType
  {
    int value;
  } obj = {0};

  WG_AUTOFUNCTOR(assign, assignto (local(SomeLocalType &) obj) )
  {
    SomeLocalType toRet = {1};
    return toRet;
  }
  WG_AUTOFUNCTOR_END;

  return 0;
}
